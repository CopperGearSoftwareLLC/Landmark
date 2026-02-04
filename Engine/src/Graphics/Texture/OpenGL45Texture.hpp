#pragma once


#include "Graphics/Texture/IGraphicsTexture.hpp"
#include <GL/gl.h>
class OpenGL45Texture : public IGraphicsTexture
{
    GLuint gl_handle = -1;
    
};