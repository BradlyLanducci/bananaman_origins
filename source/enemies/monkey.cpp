#include <enemies/monkey.h>
#include <common/platform.h>
#include <player/player.h>

#include <utilities/type_checking.h>
#include <physics/aabb.h>

//------------------------------------------------------------------//

Monkey::Monkey()
    : Enemy(new AE::Collision())
    , mp_meleeTimer(new AE::Timer(MeleeCooldown))
    , mp_meleeCollision(new AE::Collision(true))
    , m_collisionResolved(
          [this](const AE::Vector2 &offset)
          {
              if (offset.x != 0.0)
              {
                  m_facingRight = offset.x > 0.0;
              }
          })
    , m_meleeFinished(
          [this]
          {
              m_isAttacking = false;
              mp_meleeCollision->setEnabled(false);
          })
    , m_meleeCollided(
          [this](AE::Collision *p_collision)
          {
              if (m_isAttacking)
              {
                  Player *p_player{ dynamic_cast<Player *>(p_collision->parent()) };
                  if (p_player)
                  {
                      m_isAttacking = false;
                      mp_meleeCollision->setEnabled(false);
                      p_player->setHealth(p_player->health() - 1);
                  }
              }
          })
{
    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    AE::Collision *p_collision{ collision() };
    resolvedCollision.connect(m_collisionResolved);

    addChild(p_collision);
    addChild(mp_meleeCollision);

    const int rows{ 1 };
    const int fps{ 8 };
    auto idleLeft{ std::make_shared<AE::Spritesheet>("assets/monkey_idle_left.png", 3, rows, 3, fps, true) };
    auto idleRight{ std::make_shared<AE::Spritesheet>("assets/monkey_idle_right.png", 3, rows, 3, fps, true) };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/monkey_walk_left.png", 5, rows, 5, fps, true) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/monkey_walk_right.png", 5, rows, 5, fps, true) };
    auto attackLeft{ std::make_shared<AE::Spritesheet>("assets/monkey_attack_left.png", 11, rows, 11, fps, true) };
    auto attackRight{ std::make_shared<AE::Spritesheet>("assets/monkey_attack_right.png", 11, rows, 11, fps, true) };

    attackLeft->animationFinished.connect(m_meleeFinished);
    attackRight->animationFinished.connect(m_meleeFinished);

    mp_sprite->addAnimation("idleLeft", idleLeft);
    mp_sprite->addAnimation("idleRight", idleRight);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
    mp_sprite->addAnimation("attackLeft", attackLeft);
    mp_sprite->addAnimation("attackRight", attackRight);

    mp_sprite->playAnimation("idleRight");

    AE::Vector2 spriteSize{ mp_sprite->size() };
    setSize(spriteSize);
    p_collision->setPosition({ spriteSize.x / 4, 0 });
    p_collision->setSize({ spriteSize.x / 2, spriteSize.y });

    mp_meleeCollision->collided.connect(m_meleeCollided);
    mp_meleeCollision->setSize({ 50, spriteSize.y });
    mp_meleeCollision->setEnabled(false);
    mp_meleeCollision->setSolid(false);
}

//------------------------------------------------------------------//

void Monkey::physicsUpdate(double deltaTime)
{
    if (mp_meleeTimer->running())
    {
        return;
    }
    AE::Vector2 vel;

    double distanceToPlayer{ globalPosition().distanceTo(mp_player->globalPosition()) };

    bool shouldAttack{ distanceToPlayer < AttackDistance };

    if (shouldAttack && !mp_meleeTimer->running())
    {
        m_isAttacking = true;
        mp_meleeTimer->start();
        mp_meleeCollision->setEnabled(true);
        AnimationHelpers::playAnimation(mp_sprite, "attack", m_facingRight);
    }
    else if (!m_isAttacking)
    {
        bool shouldSurround{ distanceToPlayer < SurroundDistance };
        if (shouldSurround)
        {
            AE::Vector2 directionToPlayer{ globalPosition().directionTo(mp_player->globalPosition()) };
            bool facingRight{ directionToPlayer.x > 0.0 ? true : false };
            vel.x = facingRight ? WalkSpeed : -WalkSpeed;
            m_facingRight = facingRight;
        }
        else
        {
            vel.x = m_facingRight ? WalkSpeed : -WalkSpeed;
        }

        AnimationHelpers::playAnimation(mp_sprite, "walk", m_facingRight);
    }

    vel.y = GravityForce;
    mp_meleeCollision->setPosition({ m_facingRight ? 100.0 : -25.0, 0.0 });

    setVelocity(vel);
}

//------------------------------------------------------------------//
