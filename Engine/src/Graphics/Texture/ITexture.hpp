#pragma once
#include "Graphics/GraphicsEnums.hpp"
#include "Graphics/IGraphicsResource.hpp"
#include "Math.hpp"
#include <variant>

class ITexture : public IGraphicsResource
{

  public:
    struct Desc
    {
        std::variant<ivec1, ivec2, ivec3> dimensions;
        bool IsArrayType = false;
    } desc;
    ITexture(IGraphicsAllocator &allocator, GraphicsResourceID &ID,
             const Desc &desc);

    const Desc &GetDesc() const { return desc; }
};