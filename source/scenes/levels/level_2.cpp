#include <player/player.h>
#include <scenes/levels/level_2.h>
#include <common/platform.h>
#include <common/vine.h>
#include <game_ui.h>
#include <common/water.h>
#include <common/damageable.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

Level2::Level2()
    : mp_skybox(new AE::Sprite)
    , mp_cloudSpawner(new CloudSpawner(this))
    , mp_islandGround1(new Platform{ { 2000, 300 }, { -1500, 300 } })
    , mp_islandGround2(new Platform{ { 400, 200 }, { 500, 400 } })
    , mp_islandGround3(new Platform{ { 1000, 300 }, { 900, 300 } })
    , mp_water(new Water({ 500, 300 }, { 1900, 325 }))
    , mp_islandGround4(new Platform{ { 1000, 300 }, { 2400, 300 } })
    , m_windowSizeChanged([this](AE::Vector2 newSize) { mp_skybox->setSize(newSize); })
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
    , mp_levelExit(new LevelExit())
{
    addChild(mp_skybox);
    addChild(mp_islandGround1);
    addChild(mp_islandGround2);
    addChild(mp_islandGround3);
    addChild(mp_water);
    addChild(mp_islandGround4);
    addChild(mp_cloudSpawner);
    addChild(mp_levelExit);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize(AE::Window::size());
    AE::Window::resized.connect(m_windowSizeChanged);
    mp_skybox->setIsUi(true);

    mp_water->collision()->collided.connect(m_onWaterCollision);

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
