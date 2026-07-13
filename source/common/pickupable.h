#pragma once

#include <objects/sprite.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Pickupable : public AE::Object
{
public:
    enum class Type
    {
        Coconut,
        Health
    };

    Pickupable(Type type);

    AE::Signal<Type> pickedUp;

private:
    AE::Sprite *mp_sprite{ nullptr };
    AE::Collision *mp_collision{ nullptr };

    AE::Slot<AE::Collision *> m_onCollided;
};

//------------------------------------------------------------------//
