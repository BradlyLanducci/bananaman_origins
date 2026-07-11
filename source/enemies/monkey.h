#pragma once

#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

class Monkey : public AE::Character
{
public:
    Monkey();

    enum class State
    {
        Idle,
        Walking
    } state;

    void physicsUpdate(double deltaTime);

private:
    static constexpr double GravityForce{ 400.0 };
    static constexpr double WalkSpeed{ 100.0 };

    AE::AnimatedSprite *mp_sprite{ nullptr };

    bool m_facingRight{ true };

    AE::Slot<const AE::Vector2 &> m_collisionResolved;

    static constexpr double StateChangeSeconds{ 2.0 };
};

//------------------------------------------------------------------//
