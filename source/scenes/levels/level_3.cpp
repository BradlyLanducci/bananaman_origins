#include <player/player.h>
#include <scenes/levels/level_3.h>
#include <common/platform.h>
#include <common/vine.h>
#include <game_ui.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

Level3::Level3()
    : mp_skybox(new AE::Sprite)
    , mp_islandGround(new Platform{ { 3000, 300 }, { -1000, 300 }, "assets/full_grass.png", "assets/half_grass.png" })
    , mp_trunk1(new Platform{ { 600, 300 }, { -700, 0 }, "assets/tree.png", "", true, false })
    , mp_trunk2(new Platform{ { 600, 300 }, { 1200, 0 }, "assets/tree.png", "", true, false })
    , mp_boss(new Babboon)
    , m_windowSizeChanged([this](AE::Vector2 newSize) { mp_skybox->setSize(newSize); })
    , mp_levelExit(new LevelExit())
{
    addChild(mp_skybox);
    addChild(mp_islandGround);
    addChild(mp_trunk1);
    addChild(mp_trunk2);
    addChild(mp_boss);
    addChild(mp_levelExit);

    mp_skybox->setTexture("assets/jungle_skybox.png");
    mp_skybox->setSize(AE::Window::size());
    AE::Window::resized.connect(m_windowSizeChanged);
    mp_skybox->setIsUi(true);

    mp_boss->setGlobalPosition({ 500, 0 });

    mp_levelExit->setGlobalPosition({ 2700, 0 });
    mp_levelExit->setSize({ 100, 500 });
}

//------------------------------------------------------------------//

void Level3::setUi(GameUi *p_gameUi)
{
    mp_gameUi = p_gameUi;
    mp_levelExit->setUi(p_gameUi);
}

//------------------------------------------------------------------//

void Level3::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, 200 });

    mp_boss->setPlayer(mp_player);
}

//------------------------------------------------------------------//
