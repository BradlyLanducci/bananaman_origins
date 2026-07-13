#pragma once

//------------------------------------------------------------------//

#include <objects/animated_sprite.h>

#include <objects/collision.h>

//------------------------------------------------------------------//

class BananaProjectile final : public AE::AnimatedSprite
{
public:
    BananaProjectile(AE::Vector2 direction, double speed);

private:
    AE::Collision *mp_collision{ nullptr };
    AE::Slot<AE::Collision *> m_collided;
};

//------------------------------------------------------------------//
