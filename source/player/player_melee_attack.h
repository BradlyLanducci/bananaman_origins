#pragma once

#include <objects/collision.h>

//------------------------------------------------------------------//

class PlayerMeleeAttack : public AE::Object
{
public:
    PlayerMeleeAttack();

    bool doAttack(bool isFacingRight);

private:
    AE::Collision *mp_meleeCollision{ nullptr };
    AE::Slot<AE::Collision *> m_onMeleeCollided;
    AE::Slot<AE::Vector2> m_onPlayerResized;

    bool m_meleeing{ false };
};

//------------------------------------------------------------------//
