#include <game_ui.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

GameUi::GameUi()
    : mp_healthBar(new HealthBar())
    , mp_continue(new AE::Sprite())
    , m_windowResized(
          [this](AE::Vector2 windowSize)
          {
              setSize(windowSize);
              setContinuePosition();
          })
{
    addChild(mp_healthBar);
    addChild(mp_continue);
    mp_continue->setTexture("assets/continue.png");
    mp_continue->setScale({ 4.0, 4.0 });
    mp_continue->setEnabled(false);
    setIsUi(true);

    AE::Vector2 windowSize{ AE::Window::size() };
    setSize(windowSize);

    AE::Window::resized.connect(m_windowResized);

    addInputCb([this](AE::Shared<AE::InputEvent> inputEvent) { inputUpdate(inputEvent); });
}

//------------------------------------------------------------------//

void GameUi::openContinue()
{
    setContinuePosition();
    mp_continue->setEnabled(true);
}

//------------------------------------------------------------------//

void GameUi::connectPlayer(Player *p_player)
{
    p_player->healthUpdated.connect(mp_healthBar->update);
}

//------------------------------------------------------------------//

void GameUi::closeContinue()
{
    mp_continue->setEnabled(false);
}

//------------------------------------------------------------------//

void GameUi::setContinuePosition()
{
    AE::Vector2 windowSize{ AE::Window::size() };
    mp_continue->setGlobalPosition({ (windowSize.x - mp_continue->size().x * mp_continue->scale().x) / 2.0,
                                     windowSize.y - 2.0 * mp_continue->size().y * mp_continue->scale().y });
}

//------------------------------------------------------------------//

void GameUi::inputUpdate(AE::Shared<AE::InputEvent> inputEvent)
{
    AE::Shared<AE::MouseClickEvent> mouseClickEvent{ AE::InputEvent::GetType<AE::MouseClickEvent>(inputEvent) };
    if (mp_continue->enabled() && mouseClickEvent)
    {
        bool pressed{ mouseClickEvent->pressed };
        if (pressed)
        {
            closeContinue();
            continueRequest.emit();
        }
    }
}

//------------------------------------------------------------------//
