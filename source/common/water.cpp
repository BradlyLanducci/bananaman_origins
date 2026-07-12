#include <common/water.h>

//------------------------------------------------------------------//

Water::Water(const AE::Vector2 &platformSize, const AE::Vector2 &gp)
    : mp_collision(new AE::Collision())
{
    int cols{ static_cast<int>(std::ceil(platformSize.x / 100.0)) };
    int rows{ static_cast<int>(std::ceil(platformSize.y / 100.0)) };

    mp_collision->setSize(platformSize);
    mp_collision->setGlobalPosition(gp);
    addChild(mp_collision);

    const AE::Vector2 ChunkSize{ 100.0, 100.0 };

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            AE::Sprite *p_sprite{ new AE::Sprite() };

            addChild(p_sprite);
            p_sprite->setTexture("assets/water.png");
            p_sprite->setSize(ChunkSize);
            p_sprite->setGlobalPosition(
                gp + AE::Vector2(static_cast<double>(col) * ChunkSize.x, static_cast<double>(row) * ChunkSize.y));
        }
    }
}

//------------------------------------------------------------------//

AE::Collision *Water::collision() const
{
    return mp_collision;
}

//------------------------------------------------------------------//
