#pragma once
#include <EGL/egl.h>
#include <iostream>

static void EGL_CHECK_ERROR(const char* location) {
    EGLint error = eglGetError();
    if (error != EGL_SUCCESS) {
        std::cerr << "EGL Error at " << location << ": 0x" 
                  << std::hex << error << std::dec << std::endl;
    }
}
