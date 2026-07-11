#include <player/banana_projectile.h>
#include <enemies/enemy.h>
#include <player/player.h>

#include <utilities/type_checking.h>
#include <memory/memory_manager.h>

//------------------------------------------------------------------//

BananaProjectile::BananaProjectile(AE::Vector2 direction, double speed)
    : mp_collision(new AE::Collision())
    , m_collided(
          [this](AE::Collision *p_collision)
          {
              AE::Object *mp_parent{ p_collision->parent() };
              bool isPlayer{ AE::TypeChecking::isType<Player *>(mp_parent) };

              if (isPlayer)
              {
                  return;
              }

              bool isProjectile{ AE::TypeChecking::isType<BananaProjectile *>(mp_parent) };

              if (!isProjectile)
              {
                  bool isEnemy{ AE::TypeChecking::isType<Enemy *>(mp_parent) };
                  if (isEnemy)
                  {
                      p_collision->parent()->queueDelete();
                  }

                  queueDelete();
              }
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