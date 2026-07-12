#include <common/animation_helpers.h>

#include <objects/animated_sprite.h>

//------------------------------------------------------------------//

void AnimationHelpers::playAnimation(AE::AnimatedSprite *p_animator, std::string animation, bool isFacingRight)
{
    if (isFacingRight)
    {
        animation += "Right";
    }
    else
    {
        animation += "Left";
    }

    p_animator->playAnimation(animation);
}

//------------------------------------------------------------------//
