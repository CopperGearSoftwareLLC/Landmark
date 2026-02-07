#pragma once

#include "Graphics/Texture/ITexture.hpp"
#include "glad/gl.h"
#include <GL/gl.h>
class OpenGL45Texture : public ITexture
{
    GLuint gl_handle = -1;

  public:
    OpenGL45Texture(IGraphicsAllocator &allocator, GraphicsResourceID &ID,
                    const Desc &desc)
        : ITexture(allocator, ID, desc)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &gl_handle);
    }
    NativeHandle GetNativeHandle() const { return gl_handle; }
    void Destroy() override { glDeleteTextures(1, &gl_handle); };
};