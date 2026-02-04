#pragma once
#include <QWidget>
#include <QString>
#include <qdockwidget.h>

#include <string>

class EditorWidget : public QWidget
{

public:
    EditorWidget(const std::string& title, QWidget* parent = nullptr)
        : QWidget(parent), m_title(title)
    {
        setStyleSheet("background-color: #3c3f41; color: white;");
        //setFeatures(
        //    DockWidgetMovable |
        //    DockWidgetFloatable |
        //    DockWidgetClosable);
            //setFloating(true);
    }
    ~EditorWidget() = default;

    std::string title() const { return m_title; }

    void show() {QWidget::show();}
private:
    std::string m_title;
};