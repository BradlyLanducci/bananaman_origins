#include <game_ui.h>
#include <utilities/window.h>

//------------------------------------------------------------------//

GameUi::GameUi()
    : mp_continue(new AE::Sprite())
    , m_windowResized([this](AE::Vector2 windowSize) { setSize(windowSize); })
{
    addChild(mp_continue);
    mp_continue->setTexture("assets/continue.png");
    mp_continue->setScale({ 4.0, 4.0 });
    setIsUi(true);
    setSize(AE::Window::size());
    mp_continue->setGlobalPosition({ 600, 0 });
}

//------------------------------------------------------------------//
