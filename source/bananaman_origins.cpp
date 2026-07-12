#include <bananaman_origins.h>
#include <scenes/levels/level_1.h>
#include <scenes/levels/level_2.h>
#include <scenes/levels/level_3.h>
#include <game_ui.h>

#include <utilities/file_io.h>

//------------------------------------------------------------------//

BananaManOrigins::BananaManOrigins()
    : mp_camera(new AE::Camera())
    , m_levelType(Level::Type::None)
    , m_music("assets/sfx/banana_theme.wav")
    , m_onContinueRequested([this]() { loadNextLevel(); })
{
    loadNextLevel();
    mp_player->deserialize(AE::FileIO::readJson("save_file.json"));

    addChild(mp_camera);

    constexpr double CameraZoom{ 2.0 };
    mp_camera->setZoom({ CameraZoom, CameraZoom });
    AE::CameraManager::get().setCurrent(mp_camera);

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

void BananaManOrigins::setUi(GameUi *p_gameUi)
{
    mp_gameUi = p_gameUi;
    mp_gameUi->continueRequest.connect(m_onContinueRequested);
    mp_levelContainer->setUi(mp_gameUi);
}

//------------------------------------------------------------------//

void BananaManOrigins::loadNextLevel()
{
    if (mp_levelContainer)
    {
        removeChild(mp_levelContainer);

        delete mp_levelContainer;
        mp_levelContainer = nullptr;
    }

    Level::Type nextLevel{ static_cast<Level::Type>(static_cast<int>(m_levelType) + 1) };

    m_levelType = nextLevel;

    switch (nextLevel)
    {
    case Level::Type::Level1:
        mp_levelContainer = new Level1();
        break;
    case Level::Type::Level2:
        mp_levelContainer = new Level2();
        break;
    case Level::Type::Level3:
        mp_levelContainer = new Level3();
        break;
    case Level::Type::None:
    case Level::Type::End:
    default:
        break;
    }

    if (mp_levelContainer)
    {
        addChild(mp_levelContainer);
        mp_player = new Player();
        mp_levelContainer->setPlayer(mp_player);
        mp_levelContainer->setUi(mp_gameUi);

        constexpr double FollowSpeed{ 0.005 };
        mp_camera->follow(mp_player, FollowSpeed);
    }
}

//------------------------------------------------------------------//
