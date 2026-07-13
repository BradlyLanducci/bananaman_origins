#pragma once

//------------------------------------------------------------------//

#include <objects/animated_sprite.h>

#include <objects/collision.h>

//------------------------------------------------------------------//

class CoconutProjectile final : public AE::AnimatedSprite
{
public:
    CoconutProjectile(AE::Vector2 direction, double speed);

private:
    AE::Collision *mp_collision{ nullptr };
    AE::Slot<AE::Collision *> m_collided;
};

//------------------------------------------------------------------//
