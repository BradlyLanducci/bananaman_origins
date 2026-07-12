#pragma once

#include <scenes/level.h>
#include <player/player.h>

#include <utilities/camera_manager.h>

//------------------------------------------------------------------//

class BananaManOrigins : public AE::Object
{
public:
    BananaManOrigins();
    ~BananaManOrigins();

private:
    AE::Camera *mp_camera{ nullptr };

    Level *mp_levelContainer{ nullptr };
    Player *mp_player{ nullptr };

    AE::AudioPlayer m_music;
};

//------------------------------------------------------------------//
