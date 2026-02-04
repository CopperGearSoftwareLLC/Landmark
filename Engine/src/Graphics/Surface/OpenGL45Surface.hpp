#pragma once

#include "Graphics/EGL/EGLCheckError.hpp"
#include "IGraphicsSurface.hpp"

#include <EGL/egl.h>

class OpenGL45Surface : public IGraphicsSurface
{
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display;

  public:
    OpenGL45Surface(EGLDisplay dpy, EGLContext config, EGLNativeWindowType win,
                    const EGLint *attrib_list = nullptr);

    ivec2 GetSurfaceSize() const override
    {
        ivec2 size;
        eglQuerySurface(display, surface, EGL_WIDTH, &size.x);
        eglQuerySurface(display, surface, EGL_HEIGHT, &size.y);
        return size;
    }
    void MakeCurrent() const override
    {
        eglMakeCurrent(display, surface, surface, context);
    }
    void SwapBuffers() const override { eglSwapBuffers(display, surface); }
};