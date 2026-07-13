#include <player/player.h>
#include <player/coconut_projectile.h>
#include <enemies/enemy.h>
#include <common/vine.h>

#include <physics/aabb.h>
#include <utilities/type_checking.h>
#include <input/keyboard.h>

//------------------------------------------------------------------//

Player::Player(Stats &stats)
    : AE::Character(new AE::Collision())
    , m_stats(stats)
    , mp_sprite(new AE::AnimatedSprite())
    , mp_jumper(new Jumper(this, collision()))
    , mp_meleeAttack(new PlayerMeleeAttack())
    , mp_bounceTimer(new AE::Timer(BounceCooldownSeconds))
    , mp_coconutTimer(new AE::Timer(CoconutCooldownSeconds, false))
    , m_onCollided(
          [this](AE::Collision *p_collision)
          {
              Object *p_parent{ p_collision->parent() };
              bool isVine{ AE::TypeChecking::isType<Vine *>(p_parent) };
              if (isVine)
              {
                  m_isClimbing = true;
                  return;
              }

              Enemy *p_enemy{ dynamic_cast<Enemy *>(p_parent) };
              if (p_enemy)
              {
                  AE::Rect r1{ collision()->rect() };
                  AE::Rect r2{ p_collision->rect() };

                  AE::Vector2 offset{ AE::AABB::collide(r1, r2) };
                  bool resolveHorizontal{ std::abs(offset.x) < std::abs(offset.y) };
                  if (resolveHorizontal)
                  {
                      offset.y = 0.0;
                  }
                  else
                  {
                      offset.x = 0.0;
                  }

                  if (std::abs(offset.y) > 0.0 && !mp_bounceTimer->running())
                  {
                      mp_bounceTimer->start();
                      setGlobalPosition(globalPosition() + offset);
                      int enemyHealth{ p_enemy->health() };
                      p_enemy->setHealth(enemyHealth - 1);
                      setHealth(health() - 1);
                      mp_jumper->begin(JumpSeconds, JumpForce / 2);
                  }
              }
          })
    , m_onMeleeFinished(
          [this]
          {
              mp_meleeAttack->endAttack();
              playAnimation("idle");
          })
    , m_coconutSpawned(
          [this]()
          {
              if (m_stats.hasCoconut && m_stats.numCoconuts < PlayerMaxCoconuts)
              {
                  m_stats.numCoconuts = std::clamp(m_stats.numCoconuts + 1, 0, PlayerMaxCoconuts);
                  coconutsUpdated.emit(m_stats.numCoconuts);
              }
          })
    , m_jumpSfx("assets/sfx/jump.wav")
    , m_walkSfx{ { "assets/sfx/walk_1.wav", "assets/sfx/walk_2.wav", "assets/sfx/walk_3.wav",
                   "assets/sfx/walk_4.wav" } }
{
    setMaxHealth(PlayerMaxHealth);
    setHealth(m_stats.health);

    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    AE::Collision *p_collision{ collision() };
    p_collision->collided.connect(m_onCollided);

    addChild(p_collision);
    addChild(mp_sprite);
    addChild(mp_jumper);
    addChild(mp_meleeAttack);
    addChild(mp_bounceTimer);
    addChild(mp_coconutTimer);
    mp_coconutTimer->finished.connect(m_coconutSpawned);
    mp_coconutTimer->start();

    const int rows{ 1 };
    const int fps{ 8 };
    auto idleLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_idle_left.png", 8, rows, 8, fps, true) };
    auto idleRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_idle_right.png", 8, rows, 8, fps, true) };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_walk_left.png", 4, rows, 4, fps, true) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_walk_right.png", 4, rows, 4, fps, true) };
    auto jumpLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_jump_left.png", 3, rows, 3, 24, false) };
    auto jumpRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_jump_right.png", 3, rows, 3, 24, false) };
    auto climbLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_climb_left.png", 2, rows, 2, fps, true) };
    auto climbRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_climb_right.png", 2, rows, 2, fps, true) };
    auto meleeLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_melee_left.png", 7, rows, 7, 16, false) };
    auto meleeRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_melee_right.png", 7, rows, 7, 16, false) };

    meleeLeft->animationFinished.connect(m_onMeleeFinished);
    meleeRight->animationFinished.connect(m_onMeleeFinished);

    mp_sprite->addAnimation("idleLeft", idleLeft);
    mp_sprite->addAnimation("idleRight", idleRight);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
    mp_sprite->addAnimation("jumpLeft", jumpLeft);
    mp_sprite->addAnimation("jumpRight", jumpRight);
    mp_sprite->addAnimation("climbLeft", climbLeft);
    mp_sprite->addAnimation("climbRight", climbRight);
    mp_sprite->addAnimation("meleeLeft", meleeLeft);
    mp_sprite->addAnimation("meleeRight", meleeRight);

    mp_sprite->playAnimation("idleRight");

    AE::Vector2 spriteSize{ mp_sprite->size() };
    setSize(spriteSize);
    p_collision->setPosition({ spriteSize.x / 4, 0 });
    p_collision->setSize({ spriteSize.x / 2, spriteSize.y });

    mp_meleeAttack->setSize({ spriteSize.x / 2, spriteSize.y });

    m_jumpSfx.setVolumeDb(-15.0);
    m_walkSfx.setVolumeDb(-12.0);
}

//------------------------------------------------------------------//

Json::Value Player::serialize()
{
    Json::Value root;
    root["globalPosition"] = globalPosition().toJson();
    return root;
}

//------------------------------------------------------------------//

void Player::deserialize(const Json::Value &data)
{
    auto gp{ data.get("globalPosition", Json::Value()) };
    double x{ gp.get("x", 0.0).asDouble() };
    double y{ gp.get("y", 0.0).asDouble() };
    setGlobalPosition({ x, y });
}

//------------------------------------------------------------------//

void Player::physicsUpdate(double deltaTime)
{
    handleInput();
}

//------------------------------------------------------------------//

void Player::handleInput()
{
    /*
        Apply velocity and set animation based on input
    */
    AE::Vector2 vel;
    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Left))
    {
        m_facingRight = false;
        vel.x = -WalkSpeed;
    }
    else if (AE::Keyboard::isPressed(AE::Keyboard::Key::Right))
    {
        m_facingRight = true;
        vel.x = WalkSpeed;
    }
    else
    {
        vel.x = 0.0;
        vel.y = 0.0;
    }

    auto jumpingState{ mp_jumper->state() };
    if (jumpingState != Jumper::State::Jumping)
    {
        vel.y = GravityForce;

        if (jumpingState == Jumper::State::Idle)
        {
            if (vel.x != 0.0)
            {
                playAnimation("walk");
                m_walkSfx.play();
            }
            else
            {
                playAnimation("idle");
            }
        }
    }

    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Space))
    {
        if (m_isClimbing)
        {
            vel.y = ClimbSpeed;
            playAnimation("climb");
        }
        else if (jumpingState == Jumper::State::Idle)
        {
            playAnimation("jump");

            m_jumpSfx.play();

            mp_jumper->begin(JumpSeconds, JumpForce);
        }
        else if (jumpingState != Jumper::State::Jumping)
        {
            playAnimation("idle");
        }
    }

    if (mp_meleeAttack->doAttack(m_facingRight))
    {
        playAnimation("melee", true);
    }

    if (m_stats.hasCoconut && AE::Keyboard::isPressed(AE::Keyboard::Key::C))
    {
        shootCoconut();
    }
    else if (m_stats.hasCoconut && !AE::Keyboard::isPressed(AE::Keyboard::Key::C))
    {
        m_shooting = false;
    }

    setVelocity(vel);

    m_isClimbing = false;
}

//------------------------------------------------------------------//

void Player::pickedUp(Pickupable::Type type)
{
    switch (type)
    {
    case Pickupable::Type::Coconut:
        m_stats.hasCoconut = true;
        coconutsUpdated.emit(PlayerMaxCoconuts);
        m_stats.numCoconuts = PlayerMaxCoconuts;
        break;
    case Pickupable::Type::Health:
        setHealth(health() + 1);
        break;
    default:
        break;
    }
}

void Player::playAnimation(std::string animation, bool force)
{
    if (!force && mp_meleeAttack->isAttacking())
    {
        return;
    }

    if (m_facingRight)
    {
        animation += "Right";
    }
    else
    {
        animation += "Left";
    }

    mp_sprite->playAnimation(animation);
}

//------------------------------------------------------------------//

void Player::healthChanged(int health)
{
    if (health <= 0)
    {
        m_stats.reset();
        died.emit();
    }
    else
    {
        healthUpdated.emit(health);
    }

    m_stats.health = health;
}

//------------------------------------------------------------------//

void Player::shootCoconut()
{
    if (!m_shooting && m_stats.numCoconuts > 0)
    {
        auto p_parent{ parent() };
        if (p_parent)
        {
            m_shooting = true;

            m_stats.numCoconuts -= 1;

            coconutsUpdated.emit(m_stats.numCoconuts);

            AE::Vector2 direction{ m_facingRight ? AE::Vector2(1.0, 0.0) : AE::Vector2(-1.0, 0.0) };
            double speed{ 1000.0 };
            CoconutProjectile *p_projectile{ new CoconutProjectile(direction, speed) };
            AE::Vector2 initialPosition{ globalPosition() + (m_facingRight ? AE::Vector2(60, 0) : AE::Vector2()) };
            p_projectile->setGlobalPosition(initialPosition);
            p_parent->addChild(p_projectile);
        }
    }
}

//------------------------------------------------------------------//
