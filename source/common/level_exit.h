#pragma once

#include <objects/collision.h>
#include <objects/sprite.h>

//------------------------------------------------------------------//

class GameUi;

//------------------------------------------------------------------//

class LevelExit : public AE::Object
{
public:
    explicit LevelExit();

    void setUi(GameUi *p_gameUi);

private:
    AE::Sprite *mp_sprite{ nullptr };
    AE::Collision *mp_collision{ nullptr };

    GameUi *mp_gameUi{ nullptr };

    AE::Slot<AE::Collision *> m_onCollided;
};

//------------------------------------------------------------------//
