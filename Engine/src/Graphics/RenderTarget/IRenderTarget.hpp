#pragma once

#include "Graphics/Texture/TextureFormats.hpp"
class IRenderTarget
{
template <TextureFormats... Fmts> struct ColorAttachments
{
};

// Wrap a list of depth/stencil attachments (usually one, but can extend)
template <TextureFormats format> struct DepthStencilAttachment
{
};

};

/*
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
*/