#pragma once

#include <objects/sprite.h>
#include <utilities/signal.h>

#include <input/input_event.h>

//------------------------------------------------------------------//

class GameUi : public AE::Object
{
public:
    GameUi();

    void openContinue();

    AE::Signal<> continueRequest;

private:
    void setContinuePosition();
    void closeContinue();

    void inputUpdate(AE::Shared<AE::InputEvent> inputEvent);

    AE::Sprite *mp_continue{ nullptr };

    AE::Slot<AE::Vector2> m_windowResized;
};

//------------------------------------------------------------------//
