#include <common/vine.h>

//------------------------------------------------------------------//

Vine::Vine(double vineHeight)
    : mp_sprite(new AE::Sprite())
    , mp_collision(new AE::Collision())
{
    addChild(mp_sprite);
    addChild(mp_collision);

    mp_sprite->setTexture("assets/vine.png");
    mp_sprite->setSize({ 10, vineHeight });

    mp_collision->setSize(mp_sprite->size());
    mp_collision->setSolid(false);
}

//------------------------------------------------------------------//
