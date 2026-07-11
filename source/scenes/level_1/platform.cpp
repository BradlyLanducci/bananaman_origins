#include <scenes/level_1/platform.h>

//------------------------------------------------------------------//

Platform::Platform(const AE::Vector2 &platformSize)
    : mp_sprite(new AE::Sprite())
    , mp_collision(new AE::Collision())
{
    addChild(mp_sprite);

    mp_sprite->setTexture("assets/grass.png");
    mp_sprite->setSize(platformSize);
    mp_sprite->addChild(mp_collision);

    mp_collision->setSize(mp_sprite->size());
}

//------------------------------------------------------------------//
