#pragma once

#include "Graphics/Command/ICommand.hpp"
#include "boost/describe.hpp"
#include "boost/describe/enum.hpp"
#include "boost/describe/enum_to_string.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
enum class CmdNodeKind
{
    eCommand,
    eSequence,
    ePass,
    eFork
};
BOOST_DESCRIBE_ENUM(CmdNodeKind, eCommand, eSequence, ePass, eFork);
struct CmdNode
{
    CmdNodeKind kind;
    virtual ~CmdNode() = default;
};
template <typename CmdType>
concept CommandType = std::derived_from<CmdType, ICommand>;

// Use the concept in your class template
template <CommandType CmdType> struct CmdCommand : CmdNode
{
    CmdType cmd;

    // Constructor must take CmdType, not base ICommand
    CmdCommand(CmdType c) : cmd(std::move(c)) { kind = CmdNodeKind::eCommand; }
};
struct CmdSequence;
struct CmdFork : CmdNode
{
    std::vector<std::unique_ptr<CmdSequence>> branches;

    CmdFork(size_t n)
    {
        kind = CmdNodeKind::eFork;
        branches.resize(n);
        for (auto &b : branches)
            b = std::make_unique<CmdSequence>();
    }
};
struct CmdPass : CmdNode
{
    std::vector<std::unique_ptr<CmdNode>> children;

    CmdPass() { kind = CmdNodeKind::ePass; }

    template <typename CMD, typename... Args>
        requires std::derived_from<CMD, ICommand>
    void Push(Args &&...args)
    {
        children.push_back(std::make_unique<CmdCommand<CMD>>(
            CMD(std::forward<Args>(args)...)));
    }
};
struct CmdSequence : CmdPass
{
    CmdSequence() { kind = CmdNodeKind::eSequence; }
    template <typename F>
        requires std::invocable<F, CmdPass &>
    void Pass(F &&f)
    {
        auto seq = std::make_unique<CmdPass>();
        std::invoke(std::forward<F>(f), *seq); // <-- just forward f directly
        children.push_back(std::move(seq));
    }
    template <typename F>
        requires std::invocable<F, CmdSequence &>
    void Sequence(F &&f)
    {
        auto seq = std::make_unique<CmdSequence>();
        std::invoke(std::forward<F>(f), *seq); // <-- just forward f directly
        children.push_back(std::move(seq));
    }
    template <size_t N, std::invocable<CmdSequence &>... Fs>
    void Fork(Fs &&...fs)
    {
        static_assert(sizeof...(Fs) == N, "Fork<N> requires exactly N lambdas");

        auto fork = std::make_unique<CmdFork>(N); // create the fork node

        // call each lambda into its corresponding branch
        size_t i = 0;
        ((std::invoke(std::forward<Fs>(fs), *fork->branches[i++])), ...);

        // add fork node to this sequence
        children.push_back(std::move(fork));
    }

    template <std::invocable<CmdSequence &>... Fs> void Fork(Fs &&...fs)
    {

        static_assert(sizeof...(Fs) > 0, "Fork requires at least one lambda");
        Fork<sizeof...(Fs)>(std::forward<Fs>(fs)...);
    }
};

class ICommandList : public CmdSequence
{
  public:
};

static void test345()
{

    /*
         ⌜ --------------C-------------⌝
    --C--*                             *-------------
         |   ⌜ ---------C----------⌝   |
         ⌞ --*                     *---⌟
             ⌞ --*          * -----⌟
                 ⌞ --C--C-- ⌟
    */
    ICommandList cmdlist;
    cmdlist.Push<ICommand>();
    cmdlist.Fork(
        [](CmdSequence &seq1)
        {
            seq1.Push<ICommand>();
            seq1.Fork<2>([](CmdSequence &f1) { f1.Push<ICommand>(); },
                         [](CmdSequence &f2)
                         {
                             f2.Pass(
                                 [](CmdPass &seq1)
                                 {
                                     seq1.Push<ICommand>();
                                     seq1.Push<ICommand>();
                                 });
                         });
        },
        [](CmdSequence &seq2) { seq2.Push<ICommand>(); });
    cmdlist.Push<ICommand>();
}