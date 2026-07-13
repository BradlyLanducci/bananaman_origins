#include <common/pickupable.h>

#include <player/player.h>

//------------------------------------------------------------------//

Pickupable::Pickupable(Type type)
    : mp_sprite(new AE::Sprite())
    , mp_collision(new AE::Collision())
    , m_onCollided(
          [this, type](AE::Collision *p_collision)
          {
              Player *p_player{ dynamic_cast<Player *>(p_collision->parent()) };
              if (p_player)
              {
                  p_player->pickedUp(type);
                  queueDelete();
              }
          })
{
    addChild(mp_sprite);
    addChild(mp_collision);

    switch (type)
    {
    case Pickupable::Type::Coconut:
        mp_sprite->setTexture("assets/coconut.png");
        break;
    case Pickupable::Type::Health:
        mp_sprite->setTexture("assets/health.png");
        break;
    default:
        break;
    }

    mp_collision->setSize(mp_sprite->size());
    mp_collision->setSolid(false);
    mp_collision->collided.connect(m_onCollided);
}

//------------------------------------------------------------------//
