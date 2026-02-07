#include "Graphics/Allocator/IGraphicsAllocator.hpp"
#include "Graphics/GPUHandle.hpp"
#include "Graphics/GraphicsEnums.hpp"
#include "LandmarkEngine.hpp"
#pragma
#include "Graphics/Texture/ITexture.hpp"
#include "LandmarkEngine.hpp"
class FGTexture
{
    std::optional<GPUHandle<eTexture>> tex;

  public:
    FGTexture() = default;
    FGTexture(FGTexture &&) = default;
    struct Desc : ITexture::Desc
    {
    };

    void create(const Desc &desc, void *a)
    {
        IGraphicsAllocator *allocaltor = (IGraphicsAllocator *)a;
        tex = allocaltor->CreateTexture(desc);
    };
    Desc GetDesc() const { return Desc(); }
    void destroy(const Desc &, void *) {
      
    }
    void preRead(const Desc &, uint32_t flags, void *context) {}
    void preWrite(const Desc &, uint32_t flags, void *context) {}
};