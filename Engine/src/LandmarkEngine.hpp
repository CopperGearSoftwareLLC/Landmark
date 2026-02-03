

#pragma once

#include "Graphics/Backends/IGraphicsBackend.hpp"
#include "misc/Singleton.hpp"
#include <memory>
class LandmarkEngine : public Singleton<LandmarkEngine> {

public:
  struct Settings {};

  LandmarkEngine();
  void init(const Settings &settings);

private:
  std::shared_ptr<IGraphicsBackend> graphics_backend;
};