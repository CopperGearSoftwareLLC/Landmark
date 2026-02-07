#pragma once

#include "Graphics/Allocator/IGraphicsAllocator.hpp"
#include "Graphics/GraphicsEnums.hpp"
#include "IGraphicsResource.hpp"
#include <cstdint>

template <GraphicsResourceType TYPE> class GPUHandle
{
    friend IGraphicsAllocator;
    IGraphicsAllocator *allocator;

    GraphicsResourceID ID = 0;

  protected:
    GPUHandle(GraphicsResourceID _ID, IGraphicsAllocator *a)
        : ID(_ID), allocator(a)
    {
    }

  public:
    GPUHandle &operator=(const GPUHandle & o)
    {
        ID = o.ID;
        allocator = o.allocator;
        return *this;
    };
    GPUHandle &operator=(GPUHandle && o)
    {
        ID = o.ID;
        allocator = o.allocator;
        o.ID = 0;
        o.allocator = nullptr;
        return *this;
    }
    GPUHandle(const GPUHandle &o) : allocator(o.allocator), ID(o.ID) {};

    GPUHandle(GPUHandle &&o) : allocator(o.allocator), ID(o.ID) {o.ID = 0;o.allocator = nullptr;};
    ITexture *operator->() { &allocator->Get<TYPE>(ID); }
};