#include <enemies/monkey.h>
#include <common/gravity.h>
#include <scenes/level_1/platform.h>

#include <utilities/type_checking.h>
#include <physics/aabb.h>

//------------------------------------------------------------------//

Monkey::Monkey()
    : AE::Character(new AE::Collision())
    , mp_sprite(new AE::AnimatedSprite())
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
    addChild(mp_sprite);

    const int numFrames{ 4 };
    const int rows{ 1 };
    const int columns{ 4 };
    const int fps{ 8 };
    const bool loops{ true };
    auto idle{ std::make_shared<AE::Spritesheet>("assets/banana_boy_walk_right.png", numFrames, rows, columns, fps,
                                                 loops) };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_walk_left.png", numFrames, rows, columns, fps,
                                                     loops) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_walk_right.png", numFrames, rows, columns, fps,
                                                      loops) };

    mp_sprite->addAnimation("idle", idle);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);

    mp_sprite->playAnimation("idle");

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
