#pragma once

#include "Graphics/Command/ICommandList.hpp"
#include "Render/RenderGraph.hpp"
#include "World/WorldView.hpp"
#include "fg/FrameGraph.hpp"
#include "fg/FrameGraphResource.hpp"
#include <memory>
#include <unordered_set>
class World
{

    std::shared_ptr<RenderGraph> render_graph;
    std::vector<std::weak_ptr<WorldView>> views;

  public:
    World();

    void RenderViews();
    std::shared_ptr<WorldView> MakeView();
};