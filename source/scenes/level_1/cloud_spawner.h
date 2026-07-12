#pragma once

#include <objects/sprite.h>

#include <array>
#include <random>

//------------------------------------------------------------------//

class Level;

//------------------------------------------------------------------//

class CloudSpawner : public AE::Object
{
public:
    CloudSpawner(Level *p_level);

private:
    void idleUpdate(Level *p_level, double deltaTime);

    static constexpr size_t NumClouds{ 10 };
    static constexpr double CloudSpeed{ 1000.0 };

    std::random_device m_rd;
    std::minstd_rand m_engine{ m_rd() };

    struct Cloud
    {
        AE::Sprite *p_sprite;
        double speed{};
    };

    std::array<Cloud, NumClouds> m_clouds;
};

//------------------------------------------------------------------//
