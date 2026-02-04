#pragma once

#include "Graphics/RenderTarget/IRenderTarget.hpp"
#include "Graphics/Texture/TextureFormats.hpp"
template <TextureFormats... Fmts> struct RenderTargetColorAttachments
{
};

// Wrap a list of depth/stencil attachments (usually one, but can extend)
template <TextureFormats format> struct RenderTargetDepthStencilAttachment
{
};

template <typename ColorList, typename DepthList>
class IRenderTargetHard : public IRenderTarget
{
};
void test()
{
    // Hard defined
    IRenderTargetHard<
        RenderTargetColorAttachments<TextureFormats::eRGBA,
                                     TextureFormats::eRG>,
        RenderTargetDepthStencilAttachment<TextureFormats::eDepth32F>>
        defined_render_target;

    // Soft Defined
    IRenderTarget variatic_render_target;
}
