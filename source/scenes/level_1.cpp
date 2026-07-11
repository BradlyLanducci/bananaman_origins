#include <scenes/level_1.h>

#include <player/player.h>

//------------------------------------------------------------------//

Level1::Level1()
    : mp_grass(new AE::Sprite)
{
    addChild(mp_grass);
    mp_grass->setTexture("assets/grass.png");
    mp_grass->setSize({ 1000, 100 });

    auto *p_collision{ new AE::Collision() };
    mp_grass->addChild(p_collision);
    p_collision->setSize({ 1000, 100 });
}

//------------------------------------------------------------------//

void Level1::setPlayer(Player *p_player)
{
    mp_player = p_player;
    addChild(mp_player);
    mp_player->setGlobalPosition({ 0, -mp_player->size().y });
}

//------------------------------------------------------------------//
