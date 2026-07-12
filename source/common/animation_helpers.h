#pragma once

#include <string>

//------------------------------------------------------------------//

namespace AE
{
    class AnimatedSprite;
}

//------------------------------------------------------------------//

class AnimationHelpers
{
public:
    static void playAnimation(AE::AnimatedSprite *p_animator, std::string animation, bool isFacingRight);
};

//------------------------------------------------------------------//
