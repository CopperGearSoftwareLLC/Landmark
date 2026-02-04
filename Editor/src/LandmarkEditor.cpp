#include "LandmarkEditor.hpp"
#include "LandmarkEngine.hpp"
#include <QTimer>

int LandmarkEditor::exec() { 
     QTimer::singleShot(0, []() {
        LandmarkEngine::Get().init(LandmarkEngine::Settings{});
    });
    return QApplication::exec(); 
}
