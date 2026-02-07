#include "OpenGL45Allocator.hpp"
#include "Graphics/Texture/OpenGL45Texture.hpp"
#include <memory>
std::unique_ptr<ITexture>
OpenGL45Allocator::impl_CreateTexture(GraphicsResourceID ID,
                                      const ITexture::Desc &desc)
{
    std::unique_ptr<OpenGL45Texture> texture =
        std::make_unique<OpenGL45Texture>(*this, ID, desc);
    return std::move(texture);
}
