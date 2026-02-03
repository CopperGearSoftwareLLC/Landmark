#pragma once
#include <QWidget>
#include <QString>
#include <string>

class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    EditorWidget(const std::string& title, QWidget* parent = nullptr)
        : QWidget(parent), m_title(title)
    {
        setStyleSheet("background-color: #3c3f41; color: white;");
    }
    ~EditorWidget() = default;

    std::string title() const { return m_title; }

private:
    std::string m_title;
};