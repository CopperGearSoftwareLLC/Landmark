#include "ITexture.hpp"
#include <iostream>
ITexture::ITexture(IGraphicsAllocator &allocator, GraphicsResourceID &ID,
                   const Desc &desc)
    : IGraphicsResource(allocator, ID, GraphicsResourceType::eTexture),
      desc(desc)
{
    std::cout << "Texture created\n";
}
