#include <common/platform.h>

//------------------------------------------------------------------//

Platform::Platform(const AE::Vector2 &platformSize, const AE::Vector2 &gp, const std::string &topTexturePath,
                   const std::string &bottomTexturePath)
{
    int cols{ static_cast<int>(std::ceil(platformSize.x / 100.0)) };
    int rows{ static_cast<int>(std::ceil(platformSize.y / 100.0)) };

    AE::Collision *p_collision{ new AE::Collision() };
    p_collision->setSize(platformSize);
    p_collision->setGlobalPosition(gp);
    addChild(p_collision);

    const AE::Vector2 ChunkSize{ 100.0, 100.0 };

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            AE::Sprite *p_sprite{ new AE::Sprite() };

            addChild(p_sprite);

            if (row == (rows - 1) && !bottomTexturePath.empty())
            {
                p_sprite->setTexture(bottomTexturePath);
            }
            else
            {
                p_sprite->setTexture(topTexturePath);
            }

            p_sprite->setSize(ChunkSize);
            p_sprite->setGlobalPosition(
                gp + AE::Vector2(static_cast<double>(col) * ChunkSize.x, static_cast<double>(row) * ChunkSize.y));
        }
    }
}

//------------------------------------------------------------------//
