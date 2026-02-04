#pragma once

#include "Editor/Editor.hpp"
#include "Singleton.hpp"
#include <qapplication.h>
class LandmarkEditor : public QApplication,public Singleton<LandmarkEditor>
{

  public:
    LandmarkEditor(int &argc, char **argv)
        : QApplication(argc, argv), editorwindow(nullptr)
    {
        editorwindow.show();
    };

    int exec();

    Editor &GetEditor() { return editorwindow; }
    const Editor &GetEditor() const { return editorwindow; }

  private:
    Editor editorwindow;
};