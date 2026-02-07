#include "Viewport.hpp"
#include "LandmarkEngine.hpp"
#include "World/WorldSystem.hpp"
Viewport::Viewport(QWidget *parent)
    : EditorWidget("Viewport", parent), world_view(LandmarkEngine::Get()
                                                       .GetSystem<WorldSystem>()
                                                       ->GetTestWorld()
                                                       .MakeView())
{
    m_window = new ViewportWindow();
    QWidget *container = QWidget::createWindowContainer(m_window, this);

    container->setFocusPolicy(Qt::StrongFocus);

    // Make it fill the entire QWidget
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);
    setLayout(layout);
}
