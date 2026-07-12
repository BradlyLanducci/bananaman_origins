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

    void setUi(GameUi *p_gameUi);

private:
    void loadNextLevel();

    GameUi *mp_gameUi{ nullptr };

    AE::Camera *mp_camera{ nullptr };

    Level::Type m_levelType;
    Level *mp_levelContainer{ nullptr };
    Player *mp_player{ nullptr };

    AE::AudioPlayer m_music;

    AE::Slot<> m_onContinueRequested;
};

//------------------------------------------------------------------//
