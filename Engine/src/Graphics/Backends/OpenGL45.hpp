#pragma once

#include "Graphics/Backends/IGraphicsBackend.hpp"
#include "EGL/egl.h"
class OpenGL45 : public IGraphicsBackend {

public:
  struct Settings {};

  OpenGL45(const Settings &_settings);

private:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLConfig config = nullptr;
    EGLContext headlessContext = EGL_NO_CONTEXT;
  Settings settings;
};