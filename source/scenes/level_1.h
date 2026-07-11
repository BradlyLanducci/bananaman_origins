#pragma once

#include <objects/sprite.h>

#include <scenes/level.h>

//------------------------------------------------------------------//

class Level1 : public Level
{
public:
    Level1();

    void setPlayer(Player *p_player) override;

private:
    AE::Sprite *mp_grass{ nullptr };
    Player *mp_player{ nullptr };
};

//------------------------------------------------------------------//
