#pragma once

#include <objects/character.h>
#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

class Enemy : public AE::Character
{
public:
    Enemy() = default;
    Enemy(AE::Collision *p_collision);

    virtual ~Enemy() = default;

    int health() const;
    void setHealth(int health);
    void setMaxHealth(int maxHealth);

protected:
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

    int m_health{ 2 };
    int m_maxHealth{ 2 };
};

//------------------------------------------------------------------//
