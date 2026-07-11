#include <player/player.h>
#include <common/gravity.h>
#include <scenes/level_1/vine.h>
#include <player/banana_projectile.h>

#include <utilities/type_checking.h>
#include <input/keyboard.h>

//------------------------------------------------------------------//

Player::Player()
    : AE::Character(new AE::Collision())
    , mp_sprite(new AE::AnimatedSprite())
    , mp_jumper(new Jumper(this, collision()))
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
    auto jumpLeft{ std::make_shared<AE::Spritesheet>("assets/banana_boy_jump_left.png", 3, rows, 3, 24, false) };
    auto jumpRight{ std::make_shared<AE::Spritesheet>("assets/banana_boy_jump_right.png", 3, rows, 3, 24, false) };

    mp_sprite->addAnimation("idle", idle);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
    mp_sprite->addAnimation("jumpLeft", jumpLeft);
    mp_sprite->addAnimation("jumpRight", jumpRight);

    mp_sprite->playAnimation("idle");

    AE::Vector2 spriteSize{ mp_sprite->size() };
    setSize(spriteSize);
    p_collision->setPosition({ spriteSize.x / 4, 0 });
    p_collision->setSize({ spriteSize.x / 2, spriteSize.y });
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
                mp_sprite->playAnimation("idle");
            }
        }
    }

    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Enter) && !m_shooting)
    {
        shoot();
    }
    else if (!AE::Keyboard::isPressed(AE::Keyboard::Key::Enter))
    {
        m_shooting = false;
    }

    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Up))
    {
        if (state == State::Climbing)
        {
            vel.y = -300;
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
    }

    setVelocity(vel);

    state = State::Idle;
}

//------------------------------------------------------------------//

void Player::shoot()
{
    if (!m_shooting)
    {
        m_shooting = true;
        auto p_parent{ parent() };
        if (p_parent)
        {
            AE::Vector2 direction{ m_facingRight ? AE::Vector2(1.0, 0.0) : AE::Vector2(-1.0, 0.0) };
            double speed{ 500.0 };
            BananaProjectile *p_projectile{ new BananaProjectile(direction, speed) };
            AE::Vector2 initialPosition{ globalPosition() +
                                         (m_facingRight ? AE::Vector2(80, 42.5) : AE::Vector2(0, 42.5)) };
            p_projectile->setGlobalPosition(initialPosition);
            p_parent->addChild(p_projectile);
        }
    }
}

//------------------------------------------------------------------//
