#include <scenes/level_1/platform.h>

//------------------------------------------------------------------//

Platform::Platform(const AE::Vector2 &platformSize, const std::string &texturePath)
    : mp_sprite(new AE::Sprite())
    , mp_collision(new AE::Collision())
{
    addChild(mp_sprite);
    addChild(mp_collision);

    mp_sprite->setTexture(texturePath);
    mp_sprite->setSize(platformSize);

    mp_collision->setSize(mp_sprite->size());
}

//------------------------------------------------------------------//
