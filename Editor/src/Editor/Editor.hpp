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

class Editor : public QMainWindow {

public:
  Editor(QWidget *parent) : QMainWindow(parent){
    resize({1280,720});
  }
  ~Editor() override = default;
  template <
      typename WidgetType, typename... ARGS,
      typename = std::enable_if_t<std::is_base_of_v<EditorWidget, WidgetType>>>
  std::shared_ptr<WidgetType> CreateWidget(ARGS &&...args) {
    auto widget = std::make_shared<WidgetType>(this,std::forward<ARGS>(args)...);
    widget->setParent(this);
    widget->setGeometry(this->rect()); // match parent's size
    widgets.push_back(widget);
    widget->show();
    return widget;
  }
  // Add a custom widget (window/popup/object)

  void show() {return QMainWindow::show();}
private:
  //QWidget *centralArea;
  std::vector<std::shared_ptr<EditorWidget>> widgets;
};
