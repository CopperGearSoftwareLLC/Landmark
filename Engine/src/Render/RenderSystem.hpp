#pragma once

#include "Render/RenderGraph.hpp"
#include "System/ISystem.hpp"
#include "System/RegisterSystem.hpp"
#include <memory>
class RenderSystem : public ISystem {

    void Init() override;
    void Update() override;

  public:
    std::shared_ptr<RenderGraph> NewRenderGraph();
    RenderSystem() = default;
    std::vector<std::weak_ptr<RenderGraph>> render_graphs;
};
LANDMARK_REGISTER_SYSTEM(RenderSystem)