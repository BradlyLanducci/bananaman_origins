#pragma once

#include <enemies/enemy.h>
#include <common/animation_helpers.h>

#include <utilities/signal.h>

//------------------------------------------------------------------//

class Player;

//------------------------------------------------------------------//

class Monkey final : public Enemy
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
    static constexpr double SurroundDistance{ 200.0 };
    static constexpr double AttackDistance{ 50.0 };

    bool m_facingRight{ true };

    AE::Slot<const AE::Vector2 &> m_collisionResolved;

    static constexpr double StateChangeSeconds{ 2.0 };
};

//------------------------------------------------------------------//
