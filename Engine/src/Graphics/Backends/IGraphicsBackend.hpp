#pragma once

#include "Graphics/Allocator/IGraphicsAllocator.hpp"
#include "Graphics/Surface/IGraphicsSurface.hpp"
#include <memory>
class IGraphicsBackend
{
    std::unique_ptr<IGraphicsAllocator> allocator;

  private:
    virtual std::unique_ptr<IGraphicsAllocator>
    impl_MakeAllocator() = 0;

  public:
    IGraphicsBackend() {}
    virtual ~IGraphicsBackend() = default;
    struct SurfaceParams
    {
        void *nativeWindow = nullptr; // EGLSurface, HWND, VkSurfaceKHR
    };
    virtual std::shared_ptr<IGraphicsSurface>
    CreateSurface(const SurfaceParams &) = 0;

    IGraphicsAllocator &GetAllocator()
    {
        if (!allocator)
            allocator = impl_MakeAllocator();
        return *allocator;
    }
};