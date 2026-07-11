#pragma once

#include <objects/character.h>
#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

class Player : public AE::Character
{
public:
    Player();

    void physicsUpdate(double deltaTime);

private:
    AE::AnimatedSprite *mp_sprite{ nullptr };
};

//------------------------------------------------------------------//
