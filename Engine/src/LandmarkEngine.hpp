

#pragma once

#include "Graphics/Backends/IGraphicsBackend.hpp"
#include "Singleton.hpp"
#include "System/ISystem.hpp"
#include <atomic>
#include <cassert>
#include <memory>
#include <thread>
#include <typeindex>
#include <unordered_map>
#include <vector>
class LandmarkEngine : public Singleton<LandmarkEngine>
{

  public:
    struct Settings
    {
    };

    LandmarkEngine();
    void init(const Settings &settings);
    template <typename T> std::shared_ptr<T> AddSystem()
    {
        auto system = std::make_shared<T>();
        assert(!systems.contains(typeid(T)) &&
               "Tried to register the same system twice");
        systems.insert(std::pair<std::type_index, std::shared_ptr<ISystem>>(
            typeid(T), system));
        return system;
    }
    template <typename T> std::shared_ptr<T> GetSystem() const
    {
        assert(systems.contains(typeid(T)) && "System does not exist");
        return std::static_pointer_cast<T>(systems.at(typeid(T)));
    }
    IGraphicsBackend &GetGraphicsBackend() { return *graphics_backend; }

  private:
    void UpdateLoop();
    std::jthread LoopThread;
    std::shared_ptr<IGraphicsBackend> graphics_backend;
    std::unordered_map<std::type_index, std::shared_ptr<ISystem>> systems;
    std::atomic_bool ShouldShutdown = false;
};
