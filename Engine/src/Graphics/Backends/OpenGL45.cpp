#include "OpenGL45.hpp"
#include <GL/gl.h>
#include <cstdio>
OpenGL45::OpenGL45(const Settings &_settings) : settings(_settings) {
  // 1. Get EGL display
  display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (display == EGL_NO_DISPLAY) {
    std::printf("Failed to get EGL display\n");
  }

  // 2. Initialize EGL
  if (!eglInitialize(display, nullptr, nullptr)) {
    std::printf("Failed to initialize EGL");
  }

  // 3. Choose config
  const EGLint configAttribs[] = {EGL_SURFACE_TYPE,
                                  EGL_PBUFFER_BIT,
                                  EGL_RENDERABLE_TYPE,
                                  EGL_OPENGL_BIT,
                                  EGL_RED_SIZE,
                                  8,
                                  EGL_GREEN_SIZE,
                                  8,
                                  EGL_BLUE_SIZE,
                                  8,
                                  EGL_DEPTH_SIZE,
                                  24,
                                  EGL_NONE};

  EGLint numConfigs;
  if (!eglChooseConfig(display, configAttribs, &config, 1, &numConfigs) ||
      numConfigs == 0) {
    std::printf("Failed to choose EGL config");
  }

  // 4. Create headless PBuffer surface
  const EGLint pbufferAttribs[] = {EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE};
  EGLSurface pbuffer = eglCreatePbufferSurface(display, config, pbufferAttribs);
  if (pbuffer == EGL_NO_SURFACE) {
    std::printf("Failed to create headless PBuffer surface");
  }

  // 5. Create headless context
  const EGLint contextAttribs[] = {EGL_CONTEXT_MAJOR_VERSION, 4,
                                   EGL_CONTEXT_MINOR_VERSION, 5, EGL_NONE};
  headlessContext =
      eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
  if (headlessContext == EGL_NO_CONTEXT) {
    std::printf("Failed to create headless EGL context");
  }

  // 6. Make it current
  if (!eglMakeCurrent(display, pbuffer, pbuffer, headlessContext)) {
    std::printf("Failed to make headless context current");
  }

  // 7. Load GL functions
  if (!gladLoadGL()) {
    std::printf("Failed to initialize GLAD");
  }

  std::cout << "Headless OpenGL initialized:" << glGetString(GL_VERSION)
            << std::endl;
};