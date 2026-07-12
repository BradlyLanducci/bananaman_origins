#pragma once

#include <common/damageable.h>

#include <objects/character.h>
#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

class Player;

//------------------------------------------------------------------//

class Enemy
    : public AE::Character
    , public Damageable
{
public:
    explicit Enemy(AE::Collision *p_collision);

    void setPlayer(Player *p_player);

    void healthChanged(int health) override;

protected:
    Player *mp_player{ nullptr };
    AE::AnimatedSprite *mp_sprite{ nullptr };

private:
    enum class Health
    {
        Critical,
        Injured,
        Healthy
    };

    static inline const std::unordered_map<Health, glm::vec4> HealthTints{
        { Health::Critical, glm::vec4{ 1.0 } },
        { Health::Injured, glm::vec4{ 1.0, 0.4, 0.4, 1.0 } },
        { Health::Healthy, glm::vec4{ 0.5, 0.0, 0.0, 1.0 } }
    };
};

//------------------------------------------------------------------//
