#include <enemies/babboon.h>
#include <common/platform.h>
#include <player/player.h>
#include <enemies/banana_projectile.h>

#include <utilities/type_checking.h>
#include <physics/aabb.h>

//------------------------------------------------------------------//

Babboon::Babboon()
    : Enemy(new AE::Collision())
    , mp_meleeTimer(new AE::Timer(MeleeCooldown))
    , mp_rangedTimer(new AE::Timer(RangedCooldown))
    , mp_meleeCollision(new AE::Collision())
    , m_collisionResolved(
          [this](const AE::Vector2 &offset)
          {
              if (offset.x != 0.0)
              {
                  m_facingRight = offset.x > 0.0;
              }
          })
    , m_attackFinished(
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

    setMaxHealth(10);

    AE::Collision *p_collision{ collision() };
    resolvedCollision.connect(m_collisionResolved);

    addChild(p_collision);
    addChild(mp_meleeCollision);
    addChild(mp_meleeTimer);
    addChild(mp_rangedTimer);

    const int rows{ 1 };
    const int fps{ 8 };
    auto idleLeft{ std::make_shared<AE::Spritesheet>("assets/babboon_idle_left.png", 3, rows, 3, fps, true) };
    auto idleRight{ std::make_shared<AE::Spritesheet>("assets/babboon_idle_right.png", 3, rows, 3, fps, true) };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/babboon_walk_left.png", 5, rows, 5, fps, true) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/babboon_walk_right.png", 5, rows, 5, fps, true) };
    auto attackLeft{ std::make_shared<AE::Spritesheet>("assets/babboon_melee_left.png", 11, rows, 11, fps, true) };
    auto attackRight{ std::make_shared<AE::Spritesheet>("assets/babboon_melee_right.png", 11, rows, 11, fps, true) };
    auto rangedLeft{ std::make_shared<AE::Spritesheet>("assets/babboon_ranged_left.png", 11, rows, 11, fps, true) };
    auto rangedRight{ std::make_shared<AE::Spritesheet>("assets/babboon_ranged_right.png", 11, rows, 11, fps, true) };

    attackLeft->animationFinished.connect(m_attackFinished);
    attackRight->animationFinished.connect(m_attackFinished);
    rangedLeft->animationFinished.connect(m_attackFinished);
    rangedRight->animationFinished.connect(m_attackFinished);

    mp_sprite->addAnimation("idleLeft", idleLeft);
    mp_sprite->addAnimation("idleRight", idleRight);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
    mp_sprite->addAnimation("attackLeft", attackLeft);
    mp_sprite->addAnimation("attackRight", attackRight);
    mp_sprite->addAnimation("rangedLeft", rangedLeft);
    mp_sprite->addAnimation("rangedRight", rangedRight);

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

void Babboon::physicsUpdate(double deltaTime)
{
    if (m_isAttacking)
    {
        return;
    }
    AE::Vector2 vel;

    double distanceToPlayer{ globalPosition().distanceTo(mp_player->globalPosition()) };

    bool shouldRanged{ !mp_rangedTimer->running() && distanceToPlayer < RangedDistance };
    if (shouldRanged)
    {
        mp_rangedTimer->start();
        shootBanana();
    }
    else
    {
        bool shouldMelee{ distanceToPlayer < AttackDistance };

        if (shouldMelee && !mp_meleeTimer->running())
        {
            m_isAttacking = true;
            mp_meleeTimer->start();
            mp_meleeCollision->setEnabled(true);
            AnimationHelpers::playAnimation(mp_sprite, "attack", m_facingRight);
        }
        else if (!m_isAttacking)
        {
            AE::Vector2 directionToPlayer{ globalPosition().directionTo(mp_player->globalPosition()) };
            bool facingRight{ directionToPlayer.x > 0.0 ? true : false };
            vel.x = facingRight ? WalkSpeed : -WalkSpeed;
            m_facingRight = facingRight;

            AnimationHelpers::playAnimation(mp_sprite, "walk", m_facingRight);
        }
    }

    vel.y = GravityForce;
    mp_meleeCollision->setPosition({ m_facingRight ? 100.0 : -25.0, 0.0 });

    setVelocity(vel);
}

//------------------------------------------------------------------//

void Babboon::shootBanana()
{
    auto p_parent{ parent() };
    if (p_parent)
    {
        AE::Vector2 direction{ m_facingRight ? AE::Vector2(1.0, 0.0) : AE::Vector2(-1.0, 0.0) };
        double speed{ 1000.0 };
        BananaProjectile *p_projectile{ new BananaProjectile(direction, speed) };
        AE::Vector2 initialPosition{ globalPosition() + (m_facingRight ? AE::Vector2(60, 0) : AE::Vector2()) };
        p_projectile->setGlobalPosition(initialPosition);
        p_parent->addChild(p_projectile);
    }
}

//------------------------------------------------------------------//
