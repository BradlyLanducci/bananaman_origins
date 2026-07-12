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
    Platform *mp_islandGround4{ nullptr };

    GameUi *mp_gameUi{ nullptr };
    Player *mp_player{ nullptr };

    AE::Slot<AE::Vector2> m_windowSizeChanged;
    AE::Slot<AE::Collision *> m_onWaterCollision;

    LevelExit *mp_levelExit{ nullptr };
};

//------------------------------------------------------------------//
