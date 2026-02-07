#pragma once

#include "Graphics/RenderTarget/IRenderTarget.hpp"
#include <memory>
class WorldView
{
    std::shared_ptr<IRenderTarget> render_target;

  public:
    void Render() {}
    
    void setTarget(std::shared_ptr<IRenderTarget> target)
    {
        render_target = target;
    }
};