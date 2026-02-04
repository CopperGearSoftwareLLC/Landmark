#include "OpenGL45Surface.hpp"
#include "Graphics/Backends/OpenGL45Backend.hpp"
#include "LandmarkEngine.hpp"
#include <EGL/eglplatform.h>
#include <format>
OpenGL45Surface::OpenGL45Surface(EGLDisplay dpy, EGLContext config,
                                 EGLNativeWindowType win,
                                 const EGLint *attrib_list):display(dpy)
{

    surface = eglCreateWindowSurface(display, config, win, attrib_list);

    OpenGL45Backend &glbackend =
        (OpenGL45Backend &)LandmarkEngine::Get().GetGraphicsBackend();
    context =
        eglCreateContext(display, config, glbackend.GetMainContext(), nullptr);

    if (!surface || !context)
    {
        std::printf("%s", std::format("display {} \nconfig {} \nwin{} "
                                      "\nattrib_list {}\n",
                                      (void *)display, (void *)config, (void *)win,
                                      (void *)attrib_list)
                              .c_str());
    }
}
