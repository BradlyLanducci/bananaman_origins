#pragma once

#include <objects/sprite.h>
#include <objects/collision.h>

//------------------------------------------------------------------//

class Platform : public AE::Object
{
public:
    Platform(const AE::Vector2 &platformSize, const AE::Vector2 &gp,
             const std::string &topTexturePath = "assets/sand.png", const std::string &bottomTexturePath = "");
};

//------------------------------------------------------------------//
