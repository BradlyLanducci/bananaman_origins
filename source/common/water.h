#pragma once

#include <objects/sprite.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Water final : public AE::Object
{
public:
    Water(const AE::Vector2 &waterSize, const AE::Vector2 &gp);

    AE::Collision *collision() const;

private:
    AE::Collision *mp_collision{ nullptr };
};

//------------------------------------------------------------------//
