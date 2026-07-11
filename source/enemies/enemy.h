#pragma once

#include <objects/character.h>

//------------------------------------------------------------------//

class Enemy : public AE::Character
{
public:
    Enemy() = default;
    Enemy(AE::Collision *p_collision);

    virtual ~Enemy() = default;
};

//------------------------------------------------------------------//
