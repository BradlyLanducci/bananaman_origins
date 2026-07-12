#pragma once

#include <scenes/level.h>
#include <enemies/monkey.h>
#include <common/cloud_spawner.h>

//------------------------------------------------------------------//

namespace AE
{
    class Sprite;
}

class Platform;
class Vine;

//------------------------------------------------------------------//

class Level1 final : public Level
{
public:
    Level1();

    void setPlayer(Player *p_player) override;

private:
    AE::Sprite *mp_skybox{ nullptr };
    CloudSpawner *mp_cloudSpawner{ nullptr };

    Platform *mp_islandGround{ nullptr };
    Platform *mp_entranceTop{ nullptr };
    Platform *mp_entranceBottom{ nullptr };
    Platform *mp_ground1{ nullptr };
    Platform *mp_tower{ nullptr };
    Platform *mp_towerTopLeft{ nullptr };
    Platform *mp_towerTopRight{ nullptr };
    AE::AnimatedSprite *mp_leaves1{ nullptr };
    AE::AnimatedSprite *mp_leaves2{ nullptr };
    Vine *mp_vine1{ nullptr };
    Vine *mp_vine2{ nullptr };
    Platform *mp_ground2{ nullptr };
    Platform *mp_ground3{ nullptr };
    Platform *mp_ground4{ nullptr };
    Platform *mp_canopy1{ nullptr };

    Player *mp_player{ nullptr };

    Monkey *mp_monkey1{ nullptr };
    Monkey *mp_monkey2{ nullptr };
    AE::Slot<AE::Vector2> m_windowSizeChanged;
};

//------------------------------------------------------------------//
