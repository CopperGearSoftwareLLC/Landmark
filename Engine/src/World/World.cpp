#include "World.hpp"
#include "LandmarkEngine.hpp"
#include "Render/RenderSystem.hpp"

World::World()
    : render_graph(
          LandmarkEngine::Get().GetSystem<RenderSystem>()->NewRenderGraph())
{
}
