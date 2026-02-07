#pragma once

#include "Graphics/Backends/IGraphicsBackend.hpp"
#include "Graphics/Surface/IGraphicsSurface.hpp"
#include "LandmarkEngine.hpp"
#include <EGL/eglplatform.h>
#include "glad/gl.h"
#include <GL/gl.h>
#include <QWindow>
#include <cstdlib>
#include <iostream>
#include <memory>
class ViewportWindow : public QWindow
{
  public:
    ViewportWindow()
    {
        setSurfaceType(QSurface::OpenGLSurface);
        resize(800, 600);
    }

    WId nativeHandle() const { return winId(); }

  private:
    std::shared_ptr<IGraphicsSurface> surface;


    void exposeEvent(QExposeEvent *) override;
    void GLTriangleTest();
};
