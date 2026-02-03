#include "LandmarkEngine.hpp"
#include "Graphics/Backends/OpenGL45.hpp"
LandmarkEngine::LandmarkEngine() {}
void LandmarkEngine::init(const Settings &settings) {
  graphics_backend = std::make_shared<OpenGL45>(OpenGL45::Settings{});
}
