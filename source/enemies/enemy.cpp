#include <enemies/enemy.h>
#include <player/player.h>

//------------------------------------------------------------------//

Enemy::Enemy(AE::Collision *p_collision)
    : AE::Character(p_collision)
    , mp_sprite(new AE::AnimatedSprite())
{
    addChild(mp_sprite);
    mp_sprite->shader().setFragmentShader("assets/shaders/enemy_frag.glsl");
}

//------------------------------------------------------------------//

void Enemy::setPlayer(Player *p_player)
{
    mp_player = p_player;
}

//------------------------------------------------------------------//

void Enemy::healthChanged(int health)
{
    if (health >= 0)
    {
        double percentLeft{ static_cast<double>(health / static_cast<double>(maxHealth())) };
        int healthIndex{ static_cast<int>(
            std::floor(percentLeft * static_cast<double>(magic_enum::enum_count<Health>()))) };
        mp_sprite->shader().p_fragmentShader->setVec4("healthTint", HealthTints.at(static_cast<Health>(healthIndex)));

        if (health <= 0)
        {
            queueDelete();
        }
    }
}

//------------------------------------------------------------------//
