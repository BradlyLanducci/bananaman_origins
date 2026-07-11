#include <player/player.h>
#include <scenes/level_1/level_1.h>
#include <scenes/level_1/platform.h>
#include <scenes/level_1/vine.h>

//------------------------------------------------------------------//

Level1::Level1()
    : mp_skybox(new AE::Sprite)
    , mp_islandGround(new Platform{ { 4000, 300 } })
    , mp_entranceTop(new Platform{ { { 300, 75 } } })
    , mp_entranceBottom(new Platform{ { { 250, 75 } } })
    , mp_ground1(new Platform{ { 300, 100 } })
    , mp_tower(new Platform{ { { 100, 500 } } })
    , mp_towerTopLeft(new Platform{ { { 100, 100 } } })
    , mp_vine1(new Vine{ 450 })
    , mp_towerTopRight(new Platform{ { { 100, 100 } } })
    , mp_vine2(new Vine{ 450 })
    , mp_ground2(new Platform{ { 2000, 100 } })
    , mp_ground3(new Platform{ { 200, 100 } })
    , mp_ground4(new Platform{ { 100, 100 } })
    , mp_canopy1(new Platform{ { 300, 50 } })
    , mp_monkey1(new Monkey())
{
    addChild(mp_skybox);
    addChild(mp_islandGround);
    addChild(mp_entranceTop);
    addChild(mp_entranceBottom);
    addChild(mp_ground1);
    addChild(mp_tower);
    addChild(mp_towerTopLeft);
    addChild(mp_vine1);
    addChild(mp_towerTopRight);
    addChild(mp_vine2);
    addChild(mp_ground2);
    addChild(mp_ground3);
    addChild(mp_ground4);
    addChild(mp_canopy1);
    addChild(mp_monkey1);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize({ 1600.0, 900.0 });
    mp_skybox->setScale({ 2.0, 2.0 });
    mp_skybox->setGlobalPosition({ -1600 * 2 / 2, -900 * 2 / 2 });

    mp_islandGround->setGlobalPosition(AE::Vector2{ 0, 300 });
    mp_entranceTop->setGlobalPosition(AE::Vector2{ 0, 150 });
    mp_entranceBottom->setGlobalPosition(AE::Vector2{ 0, 225 });
    mp_ground1->setGlobalPosition(AE::Vector2{ 600, 200 });
    mp_tower->setGlobalPosition(AE::Vector2{ 1200, -200 });
    mp_towerTopLeft->setGlobalPosition(AE::Vector2{ 1100, -475 });
    mp_vine1->setGlobalPosition(AE::Vector2{ 1145, -375 });
    mp_towerTopRight->setGlobalPosition(AE::Vector2{ 1300, -475 });
    mp_vine2->setGlobalPosition(AE::Vector2{ 1345, -375 });
    mp_ground2->setGlobalPosition(AE::Vector2{ 1500, 200 });
    mp_ground3->setGlobalPosition(AE::Vector2{ 1700, 100 });
    mp_ground4->setGlobalPosition(AE::Vector2{ 2300, 100 });
    mp_canopy1->setGlobalPosition(AE::Vector2{ 1500, -300 });

    mp_monkey1->setGlobalPosition({ 1900, 100 });
}

//------------------------------------------------------------------//

void Level1::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, 200 - mp_player->size().y });
}

//------------------------------------------------------------------//
