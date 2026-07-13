#include <bananaman_origins.h>
#include <scenes/levels/level_1.h>
#include <scenes/levels/level_2.h>
#include <scenes/levels/level_3.h>
#include <game_ui.h>

#include <idle/idle_manager.h>
#include <utilities/file_io.h>

//------------------------------------------------------------------//

BananaManOrigins::BananaManOrigins()
    : mp_camera(new AE::Camera())
    , m_music("assets/sfx/banana_theme.wav")
    , m_onContinueRequested([this]() { loadNextLevel(); })
    , m_playerDied(
          [this]()
          {
              if (!m_loading)
              {
                  m_levelType = Level::Type::None;
                  loadNextLevel();
              }
          })
{
    loadNextLevel();

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
}

//------------------------------------------------------------------//

void BananaManOrigins::loadNextLevel()
{
    constexpr double CameraFollowSpeed{ 0.005 };

    m_loading = true;

    AE::IdleManager::get().callNextFrame([this]() { m_loading = false; });

    if (mp_levelContainer)
    {
        removeChild(mp_levelContainer);

        mp_levelContainer->queueDelete();
        mp_camera->follow(nullptr, CameraFollowSpeed);
    }

    if (mp_gameUi)
    {
        mp_gameUi->queueDelete();
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

    addChild(mp_levelContainer);
    mp_player = new Player();
    mp_player->died.connect(m_playerDied);
    mp_levelContainer->setPlayer(mp_player);

    mp_gameUi = new GameUi();
    addChild(mp_gameUi);

    mp_gameUi->continueRequest.connect(m_onContinueRequested);

    mp_gameUi->connectPlayer(mp_player);
    mp_levelContainer->setUi(mp_gameUi);

    mp_camera->follow(mp_player, CameraFollowSpeed);
}

//------------------------------------------------------------------//
