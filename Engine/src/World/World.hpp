#pragma once

#include "Render/RenderGraph.hpp"
#include "World/WorldView.hpp"
#include <memory>
#include <unordered_set>
class World
{

    std::shared_ptr<RenderGraph> render_graph;
    std::unordered_set<std::shared_ptr<WorldView>> views;

  public:
    World();

    void RenderViews()
    {
        for (const auto &view : views)
        {
            view->Render();
        }
    }
    std::shared_ptr<WorldView> MakeView()
    {
        std::shared_ptr<WorldView> view = std::make_shared<WorldView>();
        views.insert(view);
        return view;
    }
};