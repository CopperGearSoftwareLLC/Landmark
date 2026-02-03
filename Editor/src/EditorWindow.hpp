#pragma once
#include "EditorWidget.hpp"
#include <QDockWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QVector>
#include <QWidget>
#include <memory>
#include <qmainwindow.h>
#include <type_traits>
#include <utility>

class EditorWindow : public QMainWindow {

public:
  EditorWindow(QWidget *parent) : QMainWindow(parent){}
  ~EditorWindow() override = default;
  template <
      typename WidgetType, typename... ARGS,
      typename = std::enable_if_t<std::is_base_of_v<EditorWidget, WidgetType>>>
  std::shared_ptr<WidgetType> CreateWidget(ARGS &&...args) {
    auto widget = std::make_shared<WidgetType>(std::forward<ARGS>(args)...);
    widgets.push_back(widget);
    return widget;
  }
  // Add a custom widget (window/popup/object)

  void show() {return QMainWindow::show();}
private:
  //QWidget *centralArea;
  std::vector<std::shared_ptr<EditorWidget>> widgets;
};
