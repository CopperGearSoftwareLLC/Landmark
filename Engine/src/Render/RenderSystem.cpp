#include "RenderSystem.hpp"
void RenderSystem::Update()
{
    for (auto it = render_graphs.begin(); it != render_graphs.end(); it++)
    {
        const auto &weak_graph = *it;
        if (weak_graph.expired())
        {
            render_graphs.erase(it);
            continue;
        }
    }
}

void RenderSystem::Init() {}
std::shared_ptr<RenderGraph> RenderSystem::NewRenderGraph()
{
    std::shared_ptr<RenderGraph> graph = std::make_shared<RenderGraph>();
    render_graphs.push_back(graph);
    return graph;
}
