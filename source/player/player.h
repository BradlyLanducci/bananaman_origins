#pragma once

#include <common/jumper.h>

#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

class Player : public AE::Character
{
public:
    Player();

    void physicsUpdate(double deltaTime);

private:
    void handleInput();

    static constexpr double GravityForce{ 300.0 };
    static constexpr double walkSpeed{ 100.0 };
    static constexpr double JumpSeconds{ 0.4 };
    static constexpr double JumpForce{ 750.0 };

    AE::AnimatedSprite *mp_sprite{ nullptr };

    Jumper *mp_jumper{ nullptr };

    bool m_facingRight{ true };
};

//------------------------------------------------------------------//
