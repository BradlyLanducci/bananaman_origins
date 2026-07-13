#include <player/player.h>
#include <scenes/levels/level_2.h>
#include <common/platform.h>
#include <common/vine.h>
#include <game_ui.h>
#include <common/water.h>
#include <common/damageable.h>
#include <common/pickupable.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

Level2::Level2()
    : mp_skybox(new AE::Sprite)
    , mp_cloudSpawner(new CloudSpawner(this))
    , mp_islandGround1(new Platform{ { 2000, 300 }, { -1500, 300 } })
    , mp_islandGround2(new Platform{ { 400, 200 }, { 500, 400 } })
    , mp_islandGround3(new Platform{ { 1000, 300 }, { 900, 300 } })
    , mp_water(new Water({ 500, 300 }, { 1900, 325 }))
    , mp_platform1(new Platform{ { 400, 100 }, { 2000, -300 } })
    , mp_vine1(new Vine(400.0))
    , mp_vine2(new Vine(200.0))
    , mp_vine3(new Vine(150.0))
    , mp_trunk1(new Platform{ { 100, 300 }, { 2400, 0 }, "assets/tree_trunk.png" })
    , mp_trunk3(new Platform{ { 100, 300 }, { -100, 0 }, "assets/tree_trunk.png" })
    , mp_platform2(new Platform{ { 100, 100 }, { 2500, -200 } })
    , mp_platform3(new Platform{ { 100, 100 }, { 1800, -300 } })
    , mp_platform4(new Platform{ { 100, 100 }, { 1500, -150 } })
    , mp_platform5(new Platform{ { 100, 100 }, { 1300, -250 } })
    , mp_platform6(new Platform{ { 300, 100 }, { 900, -300 } })
    , mp_coconut(new Pickupable(Pickupable::Type::Coconut))
    , mp_islandGround4(new Platform{ { 3500, 300 }, { 2400, 300 }, "assets/full_grass.png", "assets/half_grass.png" })
    , mp_islandGround5(new Platform{ { 3000, 100 }, { 2900, 200 }, "assets/full_grass.png" })
    , mp_islandGround6(new Platform{ { 100, 100 }, { 2900, 100 }, "assets/full_grass.png" })
    , mp_islandGround7(new Platform{ { 500, 100 }, { 3400, 100 }, "assets/full_grass.png" })
    , mp_islandGround8(new Platform{ { 1500, 100 }, { 4400, 100 }, "assets/full_grass.png" })
    , m_windowSizeChanged([this](AE::Vector2 newSize) { mp_skybox->setSize(newSize); })
    , mp_levelExit(new LevelExit())
    , mp_trunk2(new Platform{ { 100, 300 }, { 4900, -200 }, "assets/tree_trunk.png" })
    , m_onWaterCollision(
          [this](AE::Collision *p_collision)
          {
              Enemy *p_enemy{ dynamic_cast<Enemy *>(p_collision->parent()) };
              if (p_enemy)
              {
                  p_enemy->queueDelete();
              }
              else
              {
                  Player *p_player{ dynamic_cast<Player *>(p_collision->parent()) };
                  if (p_player)
                  {
                      p_player->died.emit();
                  }
              }
          })
    , mp_monkey1(new Monkey())
    , mp_monkey2(new Monkey())
    , mp_monkey3(new Monkey())
    , mp_monkey4(new Monkey())
    , mp_monkey5(new Monkey())
{
    addChild(mp_skybox);
    addChild(mp_islandGround1);
    addChild(mp_islandGround2);
    addChild(mp_islandGround3);
    addChild(mp_water);
    addChild(mp_platform1);
    addChild(mp_vine1);
    addChild(mp_vine2);
    addChild(mp_vine3);
    addChild(mp_trunk1);
    addChild(mp_trunk2);
    addChild(mp_trunk3);
    addChild(mp_platform2);
    addChild(mp_platform3);
    addChild(mp_platform4);
    addChild(mp_platform5);
    addChild(mp_platform6);
    addChild(mp_coconut);
    addChild(mp_islandGround4);
    addChild(mp_islandGround5);
    addChild(mp_islandGround6);
    addChild(mp_islandGround7);
    addChild(mp_islandGround8);
    addChild(mp_cloudSpawner);
    addChild(mp_monkey1);
    addChild(mp_monkey2);
    addChild(mp_monkey3);
    addChild(mp_monkey4);
    addChild(mp_monkey5);
    addChild(mp_levelExit);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize(AE::Window::size());
    AE::Window::resized.connect(m_windowSizeChanged);
    mp_skybox->setIsUi(true);

    mp_water->collision()->collided.connect(m_onWaterCollision);

    mp_coconut->setGlobalPosition({ 950, -320 });

    mp_vine1->setGlobalPosition({ 2045, -200 });
    mp_vine2->setGlobalPosition({ 2145, -200 });
    mp_vine3->setGlobalPosition({ 2245, -200 });

    mp_monkey1->setGlobalPosition({ 500, 200 });
    mp_monkey2->setGlobalPosition({ 2800, 200 });
    mp_monkey3->setGlobalPosition({ 3200, 100 });
    mp_monkey4->setGlobalPosition({ 4000, 100 });
    mp_monkey5->setGlobalPosition({ 4200, 100 });

    mp_levelExit->setGlobalPosition({ 4600, -300 });
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

    mp_monkey1->setPlayer(mp_player);
    mp_monkey2->setPlayer(mp_player);
    mp_monkey3->setPlayer(mp_player);
    mp_monkey4->setPlayer(mp_player);
    mp_monkey5->setPlayer(mp_player);
}

//------------------------------------------------------------------//
