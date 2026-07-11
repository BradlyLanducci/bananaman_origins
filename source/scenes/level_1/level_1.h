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

    Platform *mp_islandGround{ nullptr };
    Platform *mp_entranceTop{ nullptr };
    Platform *mp_entranceBottom{ nullptr };
    Platform *mp_ground1{ nullptr };
    Platform *mp_tower{ nullptr };
    Platform *mp_towerTopLeft{ nullptr };
    Platform *mp_towerTopRight{ nullptr };
    Platform *mp_ground2{ nullptr };
    Platform *mp_ground3{ nullptr };
    Platform *mp_ground4{ nullptr };
    Platform *mp_canopy1{ nullptr };

    Player *mp_player{ nullptr };
};

//------------------------------------------------------------------//
