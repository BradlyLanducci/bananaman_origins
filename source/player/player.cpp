#include <player/player.h>

//------------------------------------------------------------------//

Player::Player()
    : AE::Character(new AE::Collision())
    , mp_sprite(new AE::AnimatedSprite())
{
    addPhysicsCb([this](double deltaTimeTime) { physicsUpdate(deltaTimeTime); });

    addChild(collision());
    addChild(mp_sprite);

    auto idle{ std::make_shared<AE::Spritesheet>("assets/idle.png", 1, 1, 1, 1, true) };
    const int numFrames{ 24 };
    const int rows{ 4 };
    const int columns{ 6 };
    const int fps{ 8 };
    const bool loops{ false };
    auto walkLeft{ std::make_shared<AE::Spritesheet>("assets/walk_left.png", numFrames, rows, columns, fps, loops) };
    auto walkRight{ std::make_shared<AE::Spritesheet>("assets/walk_right.png", numFrames, rows, columns, fps, loops) };

    mp_sprite->addAnimation("idle", idle);
    mp_sprite->addAnimation("walkLeft", walkLeft);
    mp_sprite->addAnimation("walkRight", walkRight);
}

//------------------------------------------------------------------//

void Player::physicsUpdate(double deltaTime)
{
    mp_sprite->playAnimation("idle");
}

//------------------------------------------------------------------//
