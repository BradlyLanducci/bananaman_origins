#pragma once

#include <enemies/enemy.h>
#include <common/animation_helpers.h>

#include <utilities/timer.h>

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
    static constexpr double MeleeCooldown{ 2.0 };

    bool m_facingRight{ true };
    bool m_isAttacking{ false };
    AE::Timer *mp_meleeTimer{ nullptr };
    AE::Collision *mp_meleeCollision{ nullptr };

    AE::Slot<AE::Collision *> m_collided;
    AE::Slot<> m_meleeFinished;
    AE::Slot<AE::Collision *> m_meleeCollided;
    static constexpr double StateChangeSeconds{ 2.0 };
};

//------------------------------------------------------------------//
