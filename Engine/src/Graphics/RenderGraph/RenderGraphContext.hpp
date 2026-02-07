#pragma once

#include "Graphics/Command/IGraphicsCommandList.hpp"
#include <memory>
class RenderGraphContext
{
    std::vector<std::unique_ptr<IGraphicsCommandList>> cmd_lists;

  public:
    template <GraphicsCmdPipeline... PIPELINES>
    TGraphicsCommandList<PIPELINES...> &GetCommandList()
    {
        std::unique_ptr<TGraphicsCommandList<PIPELINES...>> cmd_list =
            std::make_unique<TGraphicsCommandList<PIPELINES...>>();
        TGraphicsCommandList<PIPELINES...> *list = cmd_list.get();
        cmd_lists.push_back(std::move(cmd_list));
        return *list;
    }
};