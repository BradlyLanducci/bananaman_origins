#pragma once

#include <utilities/signal.h>

//------------------------------------------------------------------//

class Damageable
{
public:
    virtual ~Damageable() = default;

    int health() const;
    int maxHealth() const;
    void setHealth(int health);
    void setMaxHealth(int maxHealth);

    virtual void healthChanged(int health);

private:
    int m_health{ 2 };
    int m_maxHealth{ 2 };
};

//------------------------------------------------------------------//
