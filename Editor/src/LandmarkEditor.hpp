#pragma once

#include "EditorWindow.hpp"
#include <qapplication.h>
class LandmarkEditor : public QApplication {

public:
  LandmarkEditor(int &argc, char **argv)
      : QApplication(argc, argv),editorwindow(nullptr) {
        editorwindow.show();
        };

        int exec();

      private:
        EditorWindow editorwindow;
};