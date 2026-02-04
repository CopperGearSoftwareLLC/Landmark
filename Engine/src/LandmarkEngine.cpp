#include "LandmarkEngine.hpp"
#include "Graphics/Backends/OpenGL45Backend.hpp"
#include "System/ISystem.hpp"
#include "System/RegisterSystem.hpp"
#include <stop_token>
#include <string_view>
#include <thread>
#include <unordered_set>
LandmarkEngine::LandmarkEngine() {}
void LandmarkEngine::init(const Settings &settings)
{
    graphics_backend =
        std::make_shared<OpenGL45Backend>(OpenGL45Backend::Settings{});

    std::unordered_set<std::string_view> visitedSystems;
    for (const auto &[key, systemInsertFunc] : GetSystemRegistrationList())
    {
        if (visitedSystems.contains(key))
        {
            continue;
        }
        else
        {
            systemInsertFunc();
            visitedSystems.insert(key);
        }
    }
    for (const auto &[key, system] : systems)
    {
        system->Init();
    }
    LoopThread = std::jthread(
        [&](const std::stop_token &stop_token)
        {
            while (!ShouldShutdown || !stop_token.stop_requested())
            {
                for (const auto &[key, system] : systems)
                {
                    system->Update();
                }
            }
        });
}
