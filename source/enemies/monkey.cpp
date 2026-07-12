#include <enemies/monkey.h>
#include <scenes/level_1/platform.h>

#include <utilities/type_checking.h>
#include <physics/aabb.h>

//------------------------------------------------------------------//

Monkey::Monkey()
    : Enemy(new AE::Collision())
    , m_collisionResolved(
          [this](const AE::Vector2 &offset)
          {
              if (offset.x != 0.0)
              {
                  m_facingRight = offset.x > 0.0;
              }
          })
{
    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    AE::Collision *p_collision{ collision() };
    resolvedCollision.connect(m_collisionResolved);

    addChild(p_collision);

    const int rows{ 1 };
    const int fps{ 8 };
    auto idleLeft{ std::make_shared<AE::Spritesheet>("assets/monkey_idle_left.png", 3, rows, 3, fps, true) };
    auto idleRight{ std::make_shared<AE::Spritesheet>("assets/monkey_idle_right.png", 3, rows, 3, fps, true) };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/monkey_walk_left.png", 5, rows, 5, fps, true) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/monkey_walk_right.png", 5, rows, 5, fps, true) };

    mp_sprite->addAnimation("idleLeft", idleLeft);
    mp_sprite->addAnimation("idleRight", idleRight);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);

    mp_sprite->playAnimation("idleRight");

    AE::Vector2 spriteSize{ mp_sprite->size() };
    setSize(spriteSize);
    p_collision->setPosition({ spriteSize.x / 4, 0 });
    p_collision->setSize({ spriteSize.x / 2, spriteSize.y });
}

//------------------------------------------------------------------//

void Monkey::physicsUpdate(double deltaTime)
{
    AE::Vector2 vel;
    if (m_facingRight)
    {
        mp_sprite->playAnimation("walkRight");
        vel.x = WalkSpeed;
    }
    else
    {
        mp_sprite->playAnimation("walkLeft");
        vel.x = -WalkSpeed;
    }

    vel.y = GravityForce;

    setVelocity(vel);
}

//------------------------------------------------------------------//
