#include <common/damageable.h>

#include <algorithm>

//------------------------------------------------------------------//

int Damageable::health() const
{
    return m_health;
}

//------------------------------------------------------------------//

int Damageable::maxHealth() const
{
    return m_maxHealth;
}

//------------------------------------------------------------------//

void Damageable::setHealth(int health)
{
    m_health = std::clamp(health, 0, m_maxHealth);
    healthChanged(m_health);
}

//------------------------------------------------------------------//

void Damageable::setMaxHealth(int maxHealth)
{
    m_maxHealth = maxHealth;
    m_health = m_maxHealth;
}

//------------------------------------------------------------------//

void Damageable::healthChanged(int health)
{
}

//------------------------------------------------------------------//
