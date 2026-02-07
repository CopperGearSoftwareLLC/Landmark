#pragma once

#include "Editor/EditorWidget.hpp"
#include "Viewport/ViewportWindow.hpp"
#include "World/WorldView.hpp"
#include <QVBoxLayout>
#include <qboxlayout.h>
class Viewport : public EditorWidget
{
  std::shared_ptr<WorldView> world_view;
  public:
    Viewport(QWidget *parent);
    ViewportWindow *window() const { return m_window; }

  private:
    ViewportWindow *m_window = nullptr;
};