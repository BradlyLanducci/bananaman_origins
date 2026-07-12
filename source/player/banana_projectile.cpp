#include <player/banana_projectile.h>
#include <enemies/enemy.h>
#include <player/player.h>

#include <utilities/type_checking.h>
#include <memory/memory_manager.h>

//------------------------------------------------------------------//

BananaProjectile::(AE::Vector2 direction, double speed)
    : mp_collision(new AE::Collision())
    , m_collided(
          [this](AE::Collision *p_collision)
          {
              AE::Object *p_parent{ p_collision->parent() };
              bool isPlayer{ AE::TypeChecking::isType<Player *>(p_parent) };

              if (isPlayer)
              {
                  return;
              }

              bool isProjectile{ AE::TypeChecking::isType<BananaProjectile *>(p_parent) };

              if (isProjectile)
              {
                  return;
              }

              Enemy *p_enemy{ dynamic_cast<Enemy *>(p_parent) };
              if (p_enemy)
              {
                  int health{ p_enemy->health() };
                  health -= 1;
                  if (health > 0)
                  {
                      p_enemy->setHealth(health);
                  }
              }

              queueDelete();
          })
{
    mp_collision->setSolid(false);
    addChild(mp_collision);
    addPhysicsCb([this, direction, speed](double deltaTime)
                 { setGlobalPosition(globalPosition() + direction * speed * deltaTime); });
    mp_collision->collided.connect(m_collided);

    setTexture("assets/banana.png");
    mp_collision->setSize({ m_texture.size() });
}

//------------------------------------------------------------------//