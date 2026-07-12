#include <enemies/enemy.h>

//------------------------------------------------------------------//

Enemy::Enemy(AE::Collision *p_collision)
    : AE::Character(p_collision)
    , mp_sprite(new AE::AnimatedSprite())
{
    addChild(mp_sprite);
    mp_sprite->shader().setFragmentShader("assets/shaders/enemy_frag.glsl");
}

//------------------------------------------------------------------//

int Enemy::health() const
{
    return m_health;
}

//------------------------------------------------------------------//

void Enemy::setHealth(int health)
{
    m_health = health;

    if (m_health >= 0)
    {
        double percentLeft{ static_cast<double>(m_health / static_cast<double>(m_maxHealth)) };
        int healthIndex{ static_cast<int>(
            std::floor(percentLeft * static_cast<double>(magic_enum::enum_count<Health>()))) };
        mp_sprite->shader().p_fragmentShader->setVec4("healthTint", HealthTints.at(static_cast<Health>(healthIndex)));

        if (m_health <= 0)
        {
            queueDelete();
        }
    }
}

//------------------------------------------------------------------//

void Enemy::setMaxHealth(int maxHealth)
{
    m_maxHealth = maxHealth;
}

//------------------------------------------------------------------//
