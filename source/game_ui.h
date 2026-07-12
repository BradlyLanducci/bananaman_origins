#pragma once

#include <objects/sprite.h>
#include <utilities/signal.h>

//------------------------------------------------------------------//

class GameUi : public AE::Object
{
public:
    GameUi();

private:
    AE::Sprite *mp_continue{ nullptr };

    AE::Slot<AE::Vector2> m_windowResized;
};

//------------------------------------------------------------------//
