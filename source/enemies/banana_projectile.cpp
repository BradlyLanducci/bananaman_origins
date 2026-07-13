#include <enemies/banana_projectile.h>
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
              AE::Object *p_parent{ p_collision->parent() };

              bool isEnemy{ AE::TypeChecking::isType<Enemy *>(p_parent) };
              if (isEnemy)
              {
                  return;
              }

              bool isProjectile{ AE::TypeChecking::isType<BananaProjectile *>(p_parent) };
              if (isProjectile)
              {
                  return;
              }

              Player *p_player{ dynamic_cast<Player *>(p_parent) };
              if (p_player)
              {
                  p_player->setHealth(p_player->health() - 1);

                  if (p_player->health() > 0)
                  {
                      queueDelete();
                  }
              }
              else
              {
                  queueDelete();
              }
          })
{
    mp_collision->setSolid(false);
    addChild(mp_collision);
    addPhysicsCb([this, direction, speed](double deltaTime)
                 { setGlobalPosition(globalPosition() + direction * speed * deltaTime); });
    mp_collision->collided.connect(m_collided);

    std::string animation;
    if (direction.x > 0)
    {
        animation = "assets/banana_fly_right.png";
    }
    else
    {
        animation = "assets/banana_fly_left.png";
    }
    auto banana{ std::make_shared<AE::Spritesheet>(animation, 4, 1, 4, 8, true) };

    addAnimation("banana", banana);
    mp_collision->setSize({ 20, 20 });

    playAnimation("banana");
}

//------------------------------------------------------------------//