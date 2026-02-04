#pragma once

#include "System/ISystem.hpp"

#include "System/RegisterSystem.hpp"
#include "World/World.hpp"
#include <optional>
class WorldSystem : public ISystem
{
    std::optional<World> test_world;
    void Init() override {}
    void Update() override
    {
        if (test_world.has_value())
        {
            test_world->RenderViews();
        }
    }

  public:
    World &GetTestWorld()
    {
        if (!test_world.has_value())
            test_world.emplace();
        return *test_world;
    }
};
LANDMARK_REGISTER_SYSTEM(WorldSystem)