#pragma once

#include <player/player.h>

#include <utilities/signal.h>
#include <objects/sprite.h>

//------------------------------------------------------------------//

class CoconutBar : public AE::Object
{
public:
    CoconutBar();

    AE::Slot<int> update;

private:
    std::array<AE::Sprite *, Player::PlayerMaxCoconuts> m_coconuts;
};

//------------------------------------------------------------------//
