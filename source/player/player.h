#pragma once

#include <player/jumper.h>
#include <player/player_melee_attack.h>

#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>

#include <json/json.h>

//------------------------------------------------------------------//

class Player : public AE::Character
{
public:
    Player();

    enum class State
    {
        Idle,
        Walking,
        Jumping,
        Climbing
    } state;

    void physicsUpdate(double deltaTime);

    Json::Value serialize();
    void deserialize(const Json::Value &data);

private:
    void handleInput();
    AE::Slot<> m_onMeleeFinished;

    static constexpr double GravityForce{ 400.0 };
    static constexpr double ClimbSpeed{ -300.0 };
    static constexpr double WalkSpeed{ 200.0 };
    static constexpr double JumpSeconds{ 0.4 };
    static constexpr double JumpForce{ 1000.0 };

    AE::AnimatedSprite *mp_sprite{ nullptr };
    Jumper *mp_jumper{ nullptr };
    PlayerMeleeAttack *mp_meleeAttack;

    bool m_facingRight{ true };

    AE::Slot<AE::Collision *> m_onCollided;
};

//------------------------------------------------------------------//
