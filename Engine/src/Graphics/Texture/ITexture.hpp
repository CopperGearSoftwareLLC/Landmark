#pragma once
#include "Math.hpp"
 
class ITexture
{
    public:
    using TextureHandle = uint64;


    virtual TextureHandle GetNativeHandle() const = 0;
};