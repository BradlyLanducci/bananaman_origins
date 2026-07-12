#pragma once

#include <scenes/level.h>
#include <enemies/monkey.h>
#include <common/cloud_spawner.h>
#include <common/level_exit.h>

//------------------------------------------------------------------//

namespace AE
{
    class Sprite;
}

class Platform;
class Vine;
class Water;

//------------------------------------------------------------------//

class Level2 final : public Level
{
public:
    Level2();

    void setUi(GameUi *p_gameUi) override;
    void setPlayer(Player *p_player) override;

private:
    AE::Sprite *mp_skybox{ nullptr };
    CloudSpawner *mp_cloudSpawner{ nullptr };
    Platform *mp_islandGround1{ nullptr };
    Platform *mp_islandGround2{ nullptr };
    Platform *mp_islandGround3{ nullptr };
    Water *mp_water{ nullptr };
    Platform *mp_platform1{ nullptr };
    Vine *mp_vine1{ nullptr };
    Vine *mp_vine2{ nullptr };
    Vine *mp_vine3{ nullptr };
    Platform *mp_trunk1{ nullptr };
    Platform *mp_platform2{ nullptr };
    Platform *mp_platform3{ nullptr };
    Platform *mp_platform4{ nullptr };
    Platform *mp_platform5{ nullptr };
    Platform *mp_platform6{ nullptr };
    Platform *mp_islandGround4{ nullptr };
    Platform *mp_islandGround5{ nullptr };
    Platform *mp_islandGround6{ nullptr };
    Platform *mp_islandGround7{ nullptr };
    Platform *mp_islandGround8{ nullptr };
    Platform *mp_trunk2{ nullptr };

    GameUi *mp_gameUi{ nullptr };
    Player *mp_player{ nullptr };

    AE::Slot<AE::Vector2> m_windowSizeChanged;
    AE::Slot<AE::Collision *> m_onWaterCollision;

    Monkey *mp_monkey1{ nullptr };
    Monkey *mp_monkey2{ nullptr };
    Monkey *mp_monkey3{ nullptr };
    Monkey *mp_monkey4{ nullptr };
    Monkey *mp_monkey5{ nullptr };

    LevelExit *mp_levelExit{ nullptr };
};

//------------------------------------------------------------------//
