#include "LandmarkEditor.hpp"
int main(int argc, char **argv) {

  LandmarkEditor::Make(argc, argv);
  return LandmarkEditor::Get().exec();
}