#pragma once

#include <enemies/enemy.h>
#include <common/animation_helpers.h>

#include <utilities/timer.h>

//------------------------------------------------------------------//

class Player;

//------------------------------------------------------------------//

class Babboon final : public Enemy
{
public:
    Babboon();

    enum class State
    {
        Idle,
        Walking
    } state;

    void physicsUpdate(double deltaTime);

private:
    static constexpr double GravityForce{ 400.0 };
    static constexpr double WalkSpeed{ 100.0 };
    static constexpr double AttackDistance{ 50.0 };
    static constexpr double RangedDistance{ 200.0 };
    static constexpr double MeleeCooldown{ 2.0 };
    static constexpr double RangedCooldown{ 2.0 };

    void shootBanana();

    bool m_facingRight{ true };
    bool m_isAttacking{ false };
    AE::Timer *mp_meleeTimer{ nullptr };
    AE::Timer *mp_rangedTimer{ nullptr };
    AE::Collision *mp_meleeCollision{ nullptr };

    AE::Slot<const AE::Vector2 &> m_collisionResolved;
    AE::Slot<> m_attackFinished;
    AE::Slot<AE::Collision *> m_meleeCollided;
    static constexpr double StateChangeSeconds{ 2.0 };
};

//------------------------------------------------------------------//
