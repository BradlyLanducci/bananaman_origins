#include "bananaman_origins.h"

#include <scenes/level_1.h>

//------------------------------------------------------------------//

BananaManOrigins::BananaManOrigins()
    : mp_camera(new AE::Camera())
    , mp_levelContainer(new Level1())
    , mp_player(new Player())
{
    addChild(mp_camera);
    addChild(mp_levelContainer);

    mp_levelContainer->setPlayer(mp_player);

    mp_camera->setZoom({ 2.0, 2.0 });
    mp_camera->follow(mp_player);
    AE::CameraManager::get().setCurrent(mp_camera);
}

//------------------------------------------------------------------//