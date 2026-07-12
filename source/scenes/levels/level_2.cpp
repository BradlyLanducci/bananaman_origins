#include <player/player.h>
#include <scenes/levels/level_2.h>
#include <common/platform.h>
#include <common/vine.h>
#include <game_ui.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

Level2::Level2()
    : mp_skybox(new AE::Sprite)
    , mp_cloudSpawner(new CloudSpawner(this))
    , mp_islandGround(new Platform{ { 5000, 300 }, { -1000, 300 } })
    , m_windowSizeChanged([this](AE::Vector2 newSize) { mp_skybox->setSize(newSize); })
    , mp_levelExit(new LevelExit())
{
    addChild(mp_skybox);
    addChild(mp_islandGround);
    addChild(mp_cloudSpawner);
    addChild(mp_levelExit);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize(AE::Window::size());
    AE::Window::resized.connect(m_windowSizeChanged);
    mp_skybox->setIsUi(true);

    mp_levelExit->setGlobalPosition({ 2700, -200 });
    mp_levelExit->setSize({ 100, 500 });
}

//------------------------------------------------------------------//

void Level2::setUi(GameUi *p_gameUi)
{
    mp_gameUi = p_gameUi;
    mp_levelExit->setUi(p_gameUi);
}

//------------------------------------------------------------------//

void Level2::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, -200 });
}

//------------------------------------------------------------------//
