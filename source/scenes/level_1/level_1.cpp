#include <player/player.h>
#include <scenes/level_1/level_1.h>
#include <common/platform.h>
#include <common/vine.h>

//------------------------------------------------------------------//

Level1::Level1()
    : mp_skybox(new AE::Sprite)
    , mp_cloudSpawner(new CloudSpawner(this))
    , mp_islandGround(new Platform{ { 4000, 300 }, { 0, 300 } })
    , mp_entranceTop(new Platform{ { { 300, 100 } }, { 0, 100 } })
    , mp_entranceBottom(new Platform{ { { 200, 200 } }, { 0, 200 } })
    , mp_ground1(new Platform{ { 300, 100 }, { 600, 200 } })
    , mp_tower(new Platform{ { { 100, 500 } }, { 1200, -200 }, "assets/tree_trunk.png" })
    , mp_towerTopLeft(new Platform{ { { 100, 100 } }, { 1100, -475 } })
    , mp_towerTopRight(new Platform{ { { 100, 100 } }, { 1300, -475 } })
    , mp_leaves1(new AE::AnimatedSprite())
    , mp_leaves2(new AE::AnimatedSprite())
    , mp_vine1(new Vine{ 450 })
    , mp_vine2(new Vine{ 450 })
    , mp_ground2(new Platform{ { 2000, 100 }, { 1500, 200 } })
    , mp_ground3(new Platform{ { 200, 100 }, { 1700, 100 } })
    , mp_ground4(new Platform{ { 100, 100 }, { 2300, 100 } })
    , mp_canopy1(new Platform{ { 300, 50 }, { 1500, -300 } })
    , mp_monkey1(new Monkey())
    , mp_monkey2(new Monkey())
{
    addChild(mp_skybox);
    addChild(mp_islandGround);
    addChild(mp_entranceTop);
    addChild(mp_entranceBottom);
    addChild(mp_ground1);
    addChild(mp_tower);
    addChild(mp_towerTopLeft);
    addChild(mp_towerTopRight);
    addChild(mp_leaves1);
    addChild(mp_leaves2);
    addChild(mp_vine1);
    addChild(mp_vine2);
    addChild(mp_ground2);
    addChild(mp_ground3);
    addChild(mp_ground4);
    addChild(mp_canopy1);
    addChild(mp_monkey1);
    addChild(mp_monkey2);
    addChild(mp_cloudSpawner);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize({ 1600.0 * 2.0, 900.0 });
    mp_skybox->setScale({ 2.0, 2.0 });
    mp_skybox->setGlobalPosition({ -1600 * 2 / 2, -900 * 2 / 2 });

    const int rows{ 1 };
    const int fps{ 2 };
    auto leaves1{ std::make_shared<AE::Spritesheet>("assets/leaves.png", 2, rows, 2, fps, true) };
    auto leaves2{ std::make_shared<AE::Spritesheet>("assets/leaves.png", 2, rows, 2, fps, true) };

    mp_leaves1->setGlobalPosition({ 1100, -475 });
    mp_leaves2->setGlobalPosition({ 1300, -475 });
    mp_leaves1->addAnimation("leaves", leaves1);
    mp_leaves2->addAnimation("leaves", leaves2);
    mp_leaves1->playAnimation("leaves");
    mp_leaves2->playAnimation("leaves");

    mp_vine1->setGlobalPosition(AE::Vector2{ 1145, -375 });
    mp_vine2->setGlobalPosition(AE::Vector2{ 1345, -375 });

    mp_monkey1->setGlobalPosition({ 1900, 100 });
    mp_monkey2->setGlobalPosition({ 2200, 100 });
}

//------------------------------------------------------------------//

void Level1::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, 200 - mp_player->size().y });

    mp_monkey1->setPlayer(mp_player);
    mp_monkey2->setPlayer(mp_player);
}

//------------------------------------------------------------------//
