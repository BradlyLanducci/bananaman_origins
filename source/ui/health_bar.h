#pragma once

#include <player/player.h>

#include <utilities/signal.h>
#include <objects/sprite.h>

//------------------------------------------------------------------//

class HealthBar : public AE::Object
{
public:
    HealthBar();

    AE::Slot<int> update;

private:
    std::array<AE::Sprite *, Player::PlayerMaxHealth> m_hearts;
};

//------------------------------------------------------------------//
