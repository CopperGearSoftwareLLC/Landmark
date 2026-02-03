#include "LandmarkEditor.hpp"
#include "LandmarkEngine.hpp"

int LandmarkEditor::exec() { 
    LandmarkEngine::Get().init(LandmarkEngine::Settings{});
    return QApplication::exec(); 
}
