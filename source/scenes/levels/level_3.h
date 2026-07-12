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

//------------------------------------------------------------------//

class Level3 final : public Level
{
public:
    Level3();

    void setUi(GameUi *p_gameUi) override;
    void setPlayer(Player *p_player) override;

private:
    AE::Sprite *mp_skybox{ nullptr };
    CloudSpawner *mp_cloudSpawner{ nullptr };
    Platform *mp_islandGround{ nullptr };

    Platform *mp_trunk1{ nullptr };
    Platform *mp_trunk2{ nullptr };

    GameUi *mp_gameUi{ nullptr };
    Player *mp_player{ nullptr };

    AE::Slot<AE::Vector2> m_windowSizeChanged;

    LevelExit *mp_levelExit{ nullptr };
};

//------------------------------------------------------------------//
