#include <player/player.h>
#include <scenes/level_1/vine.h>
#include <player/banana_projectile.h>

#include <utilities/type_checking.h>
#include <input/keyboard.h>

//------------------------------------------------------------------//

Player::Player()
    : AE::Character(new AE::Collision())
    , mp_sprite(new AE::AnimatedSprite())
    , mp_jumper(new Jumper(this, collision()))
    , mp_meleeAttack(new PlayerMeleeAttack())
    , m_onCollided(
          [this](AE::Collision *p_collision)
          {
              bool isVine{ AE::TypeChecking::isType<Vine *>(p_collision->parent()) };
              if (isVine)
              {
                  state = State::Climbing;
              }
          })
{
    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    AE::Collision *p_collision{ collision() };
    p_collision->collided.connect(m_onCollided);

    addChild(p_collision);
    addChild(mp_sprite);
    addChild(mp_jumper);
    addChild(mp_meleeAttack);

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

    mp_sprite->addAnimation("idleLeft", idleLeft);
    mp_sprite->addAnimation("idleRight", idleRight);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
    mp_sprite->addAnimation("jumpLeft", jumpLeft);
    mp_sprite->addAnimation("jumpRight", jumpRight);
    mp_sprite->addAnimation("climbLeft", climbLeft);
    mp_sprite->addAnimation("climbRight", climbRight);

    mp_sprite->playAnimation("idleRight");

    AE::Vector2 spriteSize{ mp_sprite->size() };
    setSize(spriteSize);
    p_collision->setPosition({ spriteSize.x / 4, 0 });
    p_collision->setSize({ spriteSize.x / 2, spriteSize.y });

    mp_meleeAttack->setSize({ spriteSize.x / 2, spriteSize.y });
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
        // state = State::Walking;
    }
    else if (AE::Keyboard::isPressed(AE::Keyboard::Key::Right))
    {
        m_facingRight = true;
        vel.x = WalkSpeed;
        // state = State::Walking;
    }
    else
    {
        vel.x = 0.0;
        vel.y = 0.0;
        // state = State::Idle;
    }

    auto jumpingState{ mp_jumper->state() };
    if (jumpingState != Jumper::State::Jumping)
    {
        vel.y = GravityForce;

        if (jumpingState == Jumper::State::Idle)
        {
            if (vel.x != 0.0)
            {
                if (m_facingRight)
                {
                    mp_sprite->playAnimation("walkRight");
                }
                else
                {
                    mp_sprite->playAnimation("walkLeft");
                }
            }
            else
            {
                if (m_facingRight)
                {
                    mp_sprite->playAnimation("idleRight");
                }
                else
                {
                    mp_sprite->playAnimation("idleLeft");
                }
            }
        }
    }

    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Up))
    {
        if (state == State::Climbing)
        {
            vel.y = ClimbSpeed;
            if (m_facingRight)
            {
                mp_sprite->playAnimation("climbRight");
            }
            else
            {
                mp_sprite->playAnimation("climbLeft");
            }
        }
        else if (jumpingState == Jumper::State::Idle)
        {
            mp_sprite->stopAnimation();
            if (m_facingRight)
            {
                mp_sprite->playAnimation("jumpRight");
            }
            else
            {
                mp_sprite->playAnimation("jumpLeft");
            }

            mp_jumper->begin(JumpSeconds, JumpForce);
        }
        else if (jumpingState != Jumper::State::Jumping)
        {
            if (m_facingRight)
            {
                mp_sprite->playAnimation("idleRight");
            }
            else
            {
                mp_sprite->playAnimation("idleLeft");
            }
        }
    }

    if (mp_meleeAttack->doAttack(m_facingRight))
    {
    }
    else
    {
    }

    setVelocity(vel);

    state = State::Idle;
}

//------------------------------------------------------------------//
