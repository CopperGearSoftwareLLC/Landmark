#pragma once

#include "Graphics/Command/Commands/RenderCommands.hpp"
#include "Graphics/Command/ICommand.hpp"
#include "Graphics/Command/ICommandList.hpp"
#include <GL/gl.h>
#include <cstdint>
#define GENERATE_CMD_FUNC(CMD_TYPE)                                            \
    template <typename... Args> void CMD_TYPE(Args &&...args)                  \
    {                                                                          \
        CMD_TYPE cmd(std::forward<Args>(args)...);                             \
    }
enum GraphicsCmdPipeline
{
    eGraphics,
    eCompute,
    eTransfer,
    ePresent
};
struct CmdRenderPass : CmdPass
{
};
class IGraphicsCommandList : protected ICommandList
{
};
template <GraphicsCmdPipeline... PIPELINES> class GraphicsCmdListHelpers
{
  public:
    template <GraphicsCmdPipeline PIPE> static constexpr bool containsPipeline()
    {
        return ((PIPE == PIPELINES) || ...);
    }

    // helper: check that all requested pipelines exist
    template <GraphicsCmdPipeline... PASS_PIPELINES>
    static constexpr bool allPipelinesAvailable()
    {
        return (containsPipeline<PASS_PIPELINES>() && ...);
    }
};
template <typename Derived, GraphicsCmdPipeline... PIPELINES>
class GraphicsOps : public GraphicsCmdListHelpers<PIPELINES...>
{

    using Base = GraphicsCmdListHelpers<PIPELINES...>;
    using Base::containsPipeline; //

    friend Derived;
    Derived &self() { return static_cast<Derived &>(*this); }

  public:
    /* COMPUTE */
    Derived &DispatchCompute(uint32_t x, uint32_t y, uint32_t z)
        requires(
            Base::template containsPipeline<GraphicsCmdPipeline::eCompute>())
    {
        printf("DispatchCompute(%u,%u,%u)\n", x, y, z);
        return self();
    }

    /* TRANSFER */
    Derived &Blit(uint32_t from, uint32_t to)
        requires(
            Base::template containsPipeline<GraphicsCmdPipeline::eTransfer>())
    {
        printf("Blit(%u -> %u)\n", from, to);
        return self();
    }

    /* PRESENT */
    Derived &Present(uint32_t something)
        requires(
            Base::template containsPipeline<GraphicsCmdPipeline::ePresent>())
    {
        printf("Present(%u)\n", something);
        return self();
    }
};

// ============================================================================
// Graphics operations (only inside render pass)
// ============================================================================

template <typename Derived>
class RenderPassOps : public GraphicsCmdListHelpers<eGraphics>
{

    friend Derived;
    Derived &self() { return static_cast<Derived &>(*this); }
    using Base = GraphicsCmdListHelpers<eGraphics>;
    using Base::containsPipeline; //

  public:
    /* GRAPHICS */
    Derived &DrawElements(uint32_t element_count)

    {
        printf("DrawElements(%u)\n", element_count);
        return self();
    }
};

// ============================================================================
// Render Pass
// ============================================================================

class TGraphicsRenderPass : public CmdPass,
                            public RenderPassOps<TGraphicsRenderPass>
{
};

// ============================================================================
// Command List
// ============================================================================

template <GraphicsCmdPipeline... PIPELINES>
class TGraphicsCommandList
    : public IGraphicsCommandList,
      public GraphicsOps<TGraphicsCommandList<PIPELINES...>, PIPELINES...>
{
    using Ops = GraphicsOps<TGraphicsCommandList<PIPELINES...>, PIPELINES...>;
    using Base = GraphicsCmdListHelpers<PIPELINES...>;
    using Base::allPipelinesAvailable;
    using Base::containsPipeline; //

  public:
    using ICommandList::Fork;

    template <typename F>
        requires(std::invocable<F, TGraphicsRenderPass &>)
    TGraphicsCommandList &RenderPass(F &&f)
    {
        Push<RenderPassBeginCmd>();

        auto pass = std::make_unique<TGraphicsRenderPass>();
        std::invoke(std::forward<F>(f), *pass);
        children.push_back(std::move(pass));

        Push<RenderPassEndCmd>();
        return *this;
    }
};

// ============================================================================
// Test
// ============================================================================

static void Test512()
{
    TGraphicsCommandList<eGraphics, eCompute, eTransfer, ePresent> allList;

    allList.DispatchCompute(2, 2, 2)
        .RenderPass(
            [](TGraphicsRenderPass &rp)
            {
                rp.DrawElements(5); // Only Graphics commands only allowed
                                    // within a Render Pass
            })
        .RenderPass([](auto &rp) { rp.DrawElements(5); })
        .Blit(2, 2)
        .Present(2);

    TGraphicsCommandList<eTransfer, ePresent> TransPresList;
    TransPresList.Present(2).Blit(2, 2).Blit(4, 5);
}