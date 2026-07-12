#include <common/level_exit.h>

#include <game_ui.h>

//------------------------------------------------------------------//

LevelExit::LevelExit(Level::Type type)
    : mp_sprite(new AE::Sprite())
    , mp_collision(new AE::Collision())
    , m_onCollided(
          [this](AE::Collision *)
          {
              if (mp_gameUi)
              {
                  mp_gameUi->openContinue();
              }
          })
{
    addChild(mp_sprite);
    addChild(mp_collision);

    mp_sprite->setTexture("assets/full_grass.png");
    mp_sprite->setSize({ 300, 400 });
    mp_collision->setSize(mp_sprite->size());
    mp_collision->setSolid(false);

    mp_collision->collided.connect(m_onCollided);
}

//------------------------------------------------------------------//

void LevelExit::setUi(GameUi *p_gameUi)
{
    mp_gameUi = p_gameUi;
}

//------------------------------------------------------------------//
