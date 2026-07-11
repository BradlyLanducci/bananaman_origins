#include <scenes/level_1/level_1.h>

#include <player/player.h>

//------------------------------------------------------------------//

Level1::Level1()
    : mp_skybox(new AE::Sprite)
    , mp_platform(new Platform{
          AE::Vector2{ 1000, 100 }
})
{
    addChild(mp_platform);
    addChild(mp_skybox);

    mp_skybox->setTexture("assets/skybox.png");
    mp_skybox->setSize({ 1600.0, 900.0 });
    mp_skybox->setScale({ 2.0, 2.0 });
    mp_skybox->setGlobalPosition({ -1600 * 2 / 2, -900 * 2 / 2 });
}

//------------------------------------------------------------------//

void Level1::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, -mp_player->size().y });
}

//------------------------------------------------------------------//
