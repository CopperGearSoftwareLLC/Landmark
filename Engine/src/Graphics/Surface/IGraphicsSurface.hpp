#pragma once
#include "Math.hpp"

class IGraphicsSurface
{

    public:
    virtual ivec2 GetSurfaceSize() const = 0;

    virtual void MakeCurrent() const  = 0;
    virtual void SwapBuffers() const = 0;
};