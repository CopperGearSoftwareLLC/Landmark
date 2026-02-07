#include "IGraphicsAllocator.hpp"
#include "Graphics/GPUHandle.hpp"
GPUHandle<eTexture>
IGraphicsAllocator::CreateTexture(const ITexture::Desc &desc)
{
    GraphicsResourceID ID = ReserveID();
    std::unique_ptr<ITexture> texture = impl_CreateTexture(ID, desc);

    objects.insert(std::move(texture));
    GPUHandle<eTexture> handle(ID, this);
    return handle;
}
