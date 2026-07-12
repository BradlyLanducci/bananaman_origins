#pragma once

#include <player/jumper.h>
#include <player/player_melee_attack.h>
#include <player/random_sfx.h>

#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>
#include <utilities/timer.h>

#include <json/json.h>

//------------------------------------------------------------------//

class Player : public AE::Character
{
public:
    Player();

    void physicsUpdate(double deltaTime);

    Json::Value serialize();
    void deserialize(const Json::Value &data);

private:
    void handleInput();
    void playAnimation(std::string animation, bool force = false);

    AE::Slot<> m_onMeleeFinished;

    static constexpr double GravityForce{ 600.0 };
    static constexpr double ClimbSpeed{ -300.0 };
    static constexpr double WalkSpeed{ 200.0 };
    static constexpr double JumpSeconds{ 0.3 };
    static constexpr double JumpForce{ 800.0 };
    static constexpr double BounceCooldownSeconds{ 0.25 };

    AE::AnimatedSprite *mp_sprite{ nullptr };
    Jumper *mp_jumper{ nullptr };
    PlayerMeleeAttack *mp_meleeAttack;

    bool m_facingRight{ true };
    bool m_isClimbing{ false };

    AE::Timer *mp_bounceTimer{ nullptr };

    AE::Slot<AE::Collision *> m_onCollided;

    AE::AudioPlayer m_jumpSfx;
    RandomSfx m_walkSfx;
};

//------------------------------------------------------------------//
