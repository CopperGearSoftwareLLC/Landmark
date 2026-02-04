#pragma once

#include "Graphics/Surface/IGraphicsSurface.hpp"
#include <memory>
class IGraphicsBackend
{
    public:
    struct SurfaceParams
    {
        void *nativeWindow = nullptr; // EGLSurface, HWND, VkSurfaceKHR
    };
    virtual std::shared_ptr<IGraphicsSurface>
    CreateSurface(const SurfaceParams &) = 0;
};