#pragma once

//------------------------------------------------------------------//

#include <objects/sprite.h>

#include <objects/collision.h>

//------------------------------------------------------------------//

class BananaProjectile final : public AE::Sprite
{
public:
    BananaProjectile(AE::Vector2 direction, double speed);

private:
    AE::Collision *mp_collision{ nullptr };
    AE::Slot<AE::Collision *> m_collided;
};

//------------------------------------------------------------------//
