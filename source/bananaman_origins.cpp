#include <bananaman_origins.h>
#include <scenes/level_1/level_1.h>

#include <utilities/file_io.h>

//------------------------------------------------------------------//

BananaManOrigins::BananaManOrigins()
    : mp_camera(new AE::Camera())
    , mp_levelContainer(new Level1())
    , mp_player(new Player())
    , m_music("assets/sfx/banana_theme.wav")
{
    addChild(mp_camera);
    addChild(mp_levelContainer);

    mp_levelContainer->setPlayer(mp_player);

    constexpr double CameraZoom{ 2.0 };
    constexpr double FollowSpeed{ 0.5 };
    mp_camera->setZoom({ CameraZoom, CameraZoom });
    mp_camera->follow(mp_player, FollowSpeed);
    AE::CameraManager::get().setCurrent(mp_camera);

    mp_player->deserialize(AE::FileIO::readJson("save_file.json"));

    m_music.setVolumeDb(-9.0);
    m_music.play(true);
}

//------------------------------------------------------------------//

BananaManOrigins::~BananaManOrigins()
{
    Json::Value data{ mp_player->serialize() };
    (void)AE::FileIO::writeJson("save_file.json", data);
}

//------------------------------------------------------------------//
