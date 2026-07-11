#include <player/player.h>
#include <common/gravity.h>

#include <input/keyboard.h>

//------------------------------------------------------------------//

Player::Player()
    : AE::Character(new AE::Collision())
    , mp_sprite(new AE::AnimatedSprite())
{
    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    AE::Collision *p_collision{ collision() };
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
    p_collision->setSize(spriteSize);
}

//------------------------------------------------------------------//

void Player::physicsUpdate(double deltaTime)
{
    Gravity::apply(deltaTime, 300.0, this);
    if (AE::Keyboard::isPressed(AE::Keyboard::Key::Right))
    {
        mp_sprite->playAnimation("walkRight");
    }
    else if (AE::Keyboard::isPressed(AE::Keyboard::Key::Left))
    {
        mp_sprite->playAnimation("walkLeft");
    }
    else
    {
        // mp_sprite->playAnimation("idle");
    }
}

//------------------------------------------------------------------//
