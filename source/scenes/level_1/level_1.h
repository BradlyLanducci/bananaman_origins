#pragma once

#include <scenes/level.h>
#include <scenes/level_1/platform.h>

//------------------------------------------------------------------//

class Level1 : public Level
{
public:
    Level1();

    void setPlayer(Player *p_player) override;

private:
    AE::Sprite *mp_skybox{ nullptr };
    Platform *mp_platform{ nullptr };
    Player *mp_player{ nullptr };
};

//------------------------------------------------------------------//
