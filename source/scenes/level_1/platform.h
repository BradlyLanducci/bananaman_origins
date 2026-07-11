#pragma once

#include <objects/sprite.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Platform : public AE::Object
{
public:
    Platform(const AE::Vector2 &platformSize);

private:
    AE::Sprite *mp_sprite{ nullptr };
    AE::Collision *mp_collision{ nullptr };
};

//------------------------------------------------------------------//
