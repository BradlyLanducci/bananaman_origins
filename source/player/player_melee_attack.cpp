#include <player/player_melee_attack.h>
#include <enemies/enemy.h>

#include <input/keyboard.h>

//------------------------------------------------------------------//

PlayerMeleeAttack::PlayerMeleeAttack()
    : mp_meleeCollision(new AE::Collision())
    , m_onMeleeCollided(
          [this](AE::Collision *p_collision)
          {
              Enemy *p_enemy{ dynamic_cast<Enemy *>(p_collision->parent()) };
              if (p_enemy)
              {
                  int health{ p_enemy->health() };
                  health -= 1;
                  if (health <= 0)
                  {
                      p_collision->parent()->queueDelete();
                  }
                  else
                  {
                      p_enemy->setHealth(health);
                  }

                  mp_meleeCollision->setEnabled(false);
              }
          })
    , m_onPlayerResized([this](AE::Vector2 newSize) { mp_meleeCollision->setSize(newSize); })
{
    addChild(mp_meleeCollision);

    mp_meleeCollision->setSolid(false);
    mp_meleeCollision->setEnabled(false);
    mp_meleeCollision->collided.connect(m_onMeleeCollided);

    resized.connect(m_onPlayerResized);
}

//------------------------------------------------------------------//

bool PlayerMeleeAttack::doAttack(bool isFacingRight)
{
    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Enter) && !m_meleeing)
    {
        m_meleeing = true;

        mp_meleeCollision->setEnabled(true);
        if (isFacingRight)
        {
            setPosition({ 75, 0 });
        }
        else
        {
            setPosition({ -25, 0 });
        }
    }
    else if (!AE::Keyboard::isPressed(AE::Keyboard::Key::Enter))
    {
        m_meleeing = false;
    }

    return m_meleeing;
}

//------------------------------------------------------------------//
