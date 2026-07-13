#pragma once

#include <player/jumper.h>
#include <player/player_melee_attack.h>
#include <player/random_sfx.h>
#include <common/damageable.h>
#include <common/pickupable.h>

#include <utilities/signal.h>
#include <objects/character.h>
#include <objects/animated_sprite.h>
#include <utilities/timer.h>

#include <json/json.h>

//------------------------------------------------------------------//

class Player final
    : public AE::Character
    , public Damageable
{
public:
    Player();

    void pickedUp(Pickupable::Type type);

    void physicsUpdate(double deltaTime);

    Json::Value serialize();
    void deserialize(const Json::Value &data);

    AE::Signal<int> healthUpdated;
    AE::Signal<int> coconutsUpdated;
    AE::Signal<> died;

    static constexpr int PlayerMaxHealth{ 4 };
    static constexpr int PlayerMaxCoconuts{ 4 };

private:
    void handleInput();
    void playAnimation(std::string animation, bool force = false);
    void healthChanged(int health) override;

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

    bool m_hasCoconut{ false };

    AE::Timer *mp_bounceTimer{ nullptr };

    AE::Slot<AE::Collision *> m_onCollided;

    AE::AudioPlayer m_jumpSfx;
    RandomSfx m_walkSfx;

    int m_numCoconuts{};
};

//------------------------------------------------------------------//
