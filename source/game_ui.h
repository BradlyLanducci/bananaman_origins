#pragma once

#include <player/player.h>
#include <ui/health_bar.h>
#include <ui/coconut_bar.h>

#include <input/input_event.h>

//------------------------------------------------------------------//

class GameUi : public AE::Object
{
public:
    GameUi();

    void openContinue();
    void openGameWon();

    void connectPlayer(Player *p_player);

    AE::Signal<> continueRequest;

private:
    void setContinuePosition();
    void closeContinue();

    void inputUpdate(AE::Shared<AE::InputEvent> inputEvent);

    HealthBar *mp_healthBar{ nullptr };
    CoconutBar *mp_coconutBar{ nullptr };
    AE::Sprite *mp_continue{ nullptr };
    AE::Sprite *mp_gameComplete{ nullptr };

    AE::Slot<AE::Vector2> m_windowResized;
};

//------------------------------------------------------------------//
