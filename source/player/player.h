#pragma once

#include <common/jumper.h>

#include <json/json.h>
#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>

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
    void shoot();

    static constexpr double GravityForce{ 400.0 };
    static constexpr double WalkSpeed{ 200.0 };
    static constexpr double JumpSeconds{ 0.4 };
    static constexpr double JumpForce{ 1000.0 };

    AE::AnimatedSprite *mp_sprite{ nullptr };

    Jumper *mp_jumper{ nullptr };

    bool m_facingRight{ true };
    bool m_shooting{ false };

    AE::Slot<AE::Collision *> m_onCollided;
};

//------------------------------------------------------------------//
