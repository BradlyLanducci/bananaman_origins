#include <player/coconut_projectile.h>
#include <enemies/enemy.h>
#include <player/player.h>

#include <utilities/type_checking.h>
#include <memory/memory_manager.h>

//------------------------------------------------------------------//

CoconutProjectile::CoconutProjectile(AE::Vector2 direction, double speed)
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

              bool isProjectile{ AE::TypeChecking::isType<CoconutProjectile *>(p_parent) };

              if (isProjectile)
              {
                  return;
              }

              Enemy *p_enemy{ dynamic_cast<Enemy *>(p_parent) };
              if (p_enemy)
              {
                  int health{ p_enemy->health() };
                  health -= 1;
                  p_enemy->setHealth(health);
              }

              queueDelete();
          })
{
    mp_collision->setSolid(false);
    addChild(mp_collision);
    addPhysicsCb([this, direction, speed](double deltaTime)
                 { setGlobalPosition(globalPosition() + direction * speed * deltaTime); });
    mp_collision->collided.connect(m_collided);

    auto coconutAnimation{ std::make_shared<AE::Spritesheet>("assets/coconut_animation.png", 4, 1, 4, 8, true) };
    addAnimation("coconutAnimation", coconutAnimation);
    mp_collision->setSize({ m_texture.size() });

    playAnimation("coconutAnimation");
}

//------------------------------------------------------------------//