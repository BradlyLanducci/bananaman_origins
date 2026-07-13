#pragma once

#include <scenes/level.h>
#include <player/player.h>

#include <utilities/camera_manager.h>

//------------------------------------------------------------------//

class GameUi;

//------------------------------------------------------------------//

class BananaManOrigins : public AE::Object
{
public:
    BananaManOrigins();
    ~BananaManOrigins();

private:
    void loadNextLevel();

    GameUi *mp_gameUi{ nullptr };

    AE::AnimatedSprite *mp_introSequence{ nullptr };
    AE::Slot<> m_introFinished;

    AE::Camera *mp_camera{ nullptr };

    Level::Type m_levelType{ Level::Type::Level2 };
    Level *mp_levelContainer{ nullptr };

    Player::Stats m_playerStats;
    Player *mp_player{ nullptr };

    AE::AudioPlayer m_music;

    AE::Slot<> m_onContinueRequested;
    AE::Slot<> m_playerDied;

    bool m_loading{ false };
};

//------------------------------------------------------------------//
