#pragma once

#include "Graphics/Allocator/IGraphicsAllocator.hpp"
#include "Graphics/GraphicsEnums.hpp"
class OpenGL45Allocator : public IGraphicsAllocator
{
  public:
    OpenGL45Allocator(IGraphicsBackend &backend) : IGraphicsAllocator(backend)
    {
    }
    //GraphicsAPI GetGraphicsAPI() const { return GraphicsAPI::eOpenGL45; }
    std::unique_ptr<ITexture>
    impl_CreateTexture(GraphicsResourceID ID,
                       const ITexture::Desc &desc) override;
};