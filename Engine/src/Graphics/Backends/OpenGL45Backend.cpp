#include "OpenGL45Backend.hpp"

#include "Graphics/Allocator/OpenGL45Allocator.hpp"
#include "glad/gl.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <cstdio>
#include <cstring>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
OpenGL45Backend::OpenGL45Backend(const Settings &_settings)
    : settings(_settings)
{
    // 1. Get EGL display
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY)
    {
        std::printf("Failed to get EGL display\n");
    }

    // 2. Initialize EGL
    if (!eglInitialize(display, nullptr, nullptr))
    {
        std::printf("Failed to initialize EGL");
    }

    // 3. Choose config
    const EGLint configAttribs[] = {EGL_SURFACE_TYPE,
                                    EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
                                    EGL_RENDERABLE_TYPE,
                                    EGL_OPENGL_BIT,
                                    EGL_RED_SIZE,
                                    8,
                                    EGL_GREEN_SIZE,
                                    8,
                                    EGL_BLUE_SIZE,
                                    8,
                                    EGL_DEPTH_SIZE,
                                    8,
                                    EGL_NONE};

    EGLint numConfigs;
    if (!eglChooseConfig(display, configAttribs, &config, 1, &numConfigs) ||
        numConfigs == 0)
    {
        std::printf("Failed to choose EGL config");
    }

    // 4. Create headless PBuffer surface
    const EGLint pbufferAttribs[] = {EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE};
    EGLSurface pbuffer =
        eglCreatePbufferSurface(display, config, pbufferAttribs);
    if (pbuffer == EGL_NO_SURFACE)
    {
        std::printf("Failed to create headless PBuffer surface");
    }
    eglBindAPI(EGL_OPENGL_API);
    // 5. Create headless context
    const EGLint contextAttribs[] = {EGL_CONTEXT_MAJOR_VERSION, 4,
                                     EGL_CONTEXT_MINOR_VERSION, 5, EGL_NONE};
    headlessContext =
        eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    if (headlessContext == EGL_NO_CONTEXT)
    {
        std::printf("Failed to create headless EGL context");
    }

    // 6. Make it current
    if (!eglMakeCurrent(display, pbuffer, pbuffer, headlessContext))
    {
        std::printf("Failed to make headless context current");
    }

    // 7. Load GL functions
    if (!gladLoadGL((GLADloadfunc)eglGetProcAddress))
    {
        std::printf("Failed to initialize GLAD");
        throw std::runtime_error("failed to init glad");
    }
    const char *exts = eglQueryString(display, EGL_EXTENSIONS);
    std::string extensionString = exts;
    std::cout << "EGL Extensions:\n" << extensionString << std::endl;

    std::cout << "EGL debug functions found\n";
    PFNEGLDEBUGMESSAGECONTROLKHRPROC eglDebugMessageControlKHR =
        (PFNEGLDEBUGMESSAGECONTROLKHRPROC)eglGetProcAddress(
            "eglDebugMessageControlKHR");

    PFNEGLQUERYDEBUGKHRPROC eglQueryDebugKHR =
        (PFNEGLQUERYDEBUGKHRPROC)eglGetProcAddress("eglQueryDebugKHR");

    eglDebugMessageControlKHR(
        [](EGLenum error, const char *command, EGLint messageType,
           EGLLabelKHR threadLabel, EGLLabelKHR objectLabel,
           const char *message)
        {
            std::printf(
                std::format("EGL ERROR:\nError {}\nCommand {}\nmessageType "
                            "{}\nthreadlabel {}\nobjectLabel {}\nmessage {}",
                            error, command, messageType, threadLabel,
                            objectLabel, message)
                    .c_str());
        },
        nullptr);

    std::cout << "Headless OpenGL initialized:" << glGetString(GL_VERSION)
              << " on: " << glGetString(GL_RENDERER) << std::endl;
};
std::unique_ptr<IGraphicsAllocator> OpenGL45Backend::impl_MakeAllocator()
{
    std::unique_ptr<OpenGL45Allocator> allocator =
        std::make_unique<OpenGL45Allocator>(*this);
    return allocator;
}
