#pragma once

#include "Graphics/GraphicsEnums.hpp"
#include "Math.hpp"
#include <cstdint>
#include <string_view>
using GraphicsResourceID = uint64_t;
const static GraphicsResourceID GPURESOURCE_INVALID = 0;
class IGraphicsAllocator;
class IGraphicsResource
{
    IGraphicsAllocator &allocator;
    GraphicsResourceID ID;
    GraphicsResourceType resourceType;

  protected:
    IGraphicsAllocator &GetAllocator() const { return allocator; }

  public:
    using NativeHandle = uint64;
    IGraphicsResource(IGraphicsAllocator &allocator, GraphicsResourceID &ID,
                      GraphicsResourceType resourceType)
        : allocator(allocator) {

          };
    virtual ~IGraphicsResource() = default; // <-- virtual destructor!
    constexpr GraphicsResourceID GetResourceID() const { return ID; }
    constexpr GraphicsResourceType GetResourceType() const
    {
        return resourceType;
    }
    virtual NativeHandle GetNativeHandle() const = 0;
    virtual void Destroy() = 0;
};