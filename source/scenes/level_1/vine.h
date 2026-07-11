#pragma once

#include <objects/sprite.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Vine : public AE::Object
{
public:
    Vine(double vineHeight);

private:
    AE::Sprite *mp_sprite{ nullptr };
    AE::Collision *mp_collision{ nullptr };
};

//------------------------------------------------------------------//
