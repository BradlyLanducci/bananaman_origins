#include <game_ui.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

GameUi::GameUi()
    : mp_healthBar(new HealthBar())
    , mp_coconutBar(new CoconutBar())
    , mp_continue(new AE::Sprite())
    , mp_gameComplete(new AE::Sprite())
    , m_windowResized(
          [this](AE::Vector2 windowSize)
          {
              setSize(windowSize);
              mp_gameComplete->setSize(windowSize);
              setContinuePosition();
          })
{
    addChild(mp_healthBar);
    addChild(mp_coconutBar);
    addChild(mp_continue);
    addChild(mp_gameComplete);

    mp_continue->setTexture("assets/continue.png");
    mp_continue->setScale({ 4.0, 4.0 });
    mp_continue->setEnabled(false);
    mp_continue->setIsUi(true);

    mp_gameComplete->setTexture("assets/game_complete.png");
    mp_gameComplete->setEnabled(false);
    mp_gameComplete->setIsUi(true);

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

void GameUi::openGameWon()
{
    mp_gameComplete->setEnabled(true);
    mp_gameComplete->setSize(AE::Window::size());
}

//------------------------------------------------------------------//

void GameUi::connectPlayer(Player *p_player)
{
    p_player->healthUpdated.connect(mp_healthBar->update);
    p_player->coconutsUpdated.connect(mp_coconutBar->update);
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
