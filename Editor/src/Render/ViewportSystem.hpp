#pragma once

#include "LandmarkEditor.hpp"
#include "Render/Viewport.hpp"
#include "System/ISystem.hpp"

#include "System/RegisterSystem.hpp"
class ViewportSystem : public ISystem
{
    void Init() override
    {

        LandmarkEditor::Get().GetEditor().CreateWidget<Viewport>();
    };
    void Update() override {

    };

  public:
    ViewportSystem() = default;
};
LANDMARK_REGISTER_SYSTEM(ViewportSystem)