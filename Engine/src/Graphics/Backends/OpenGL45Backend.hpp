#pragma once

#include "EGL/egl.h"
#include "Graphics/Backends/IGraphicsBackend.hpp"
#include "Graphics/Surface/IGraphicsSurface.hpp"
#include "Graphics/Surface/OpenGL45Surface.hpp"
#include <EGL/eglplatform.h>
class OpenGL45Backend : public IGraphicsBackend
{

  public:
    struct Settings
    {
    };

    OpenGL45Backend(const Settings &_settings);

    std::shared_ptr<IGraphicsSurface>
    CreateSurface(const SurfaceParams &params) override
    {
        EGLNativeWindowType win = *((EGLNativeWindowType *)params.nativeWindow);
        std::shared_ptr<OpenGL45Surface> context =
            std::make_shared<OpenGL45Surface>(display, config, win, nullptr);
            return context;
    }
    EGLContext GetMainContext() const {return headlessContext;}

  private:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLConfig config = nullptr;
    EGLContext headlessContext = EGL_NO_CONTEXT;
    Settings settings;
};