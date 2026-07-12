#include <scenes/level_1/cloud_spawner.h>

#include <scenes/level.h>

//------------------------------------------------------------------//

CloudSpawner::CloudSpawner(Level *p_level)
{
    for (auto &cloud : m_clouds)
    {
        cloud.speed = std::uniform_real_distribution<double>{ 10.0, 20.0 }(m_engine);

        cloud.p_sprite = new AE::Sprite();
        cloud.p_sprite->setTexture("assets/cloud_1.png");
        double rx{ std::uniform_real_distribution<double>{ 0, 3500.0 }(m_engine) };
        double ry{ std::uniform_real_distribution<double>{ -1000, 0.0 }(m_engine) };

        double rsx{ std::uniform_real_distribution<double>{ 0.5, 1.0 }(m_engine) };
        double rsy{ std::uniform_real_distribution<double>{ 0.5, 1.0 }(m_engine) };
        cloud.p_sprite->setScale({ rsx, rsy });
        cloud.p_sprite->setGlobalPosition({ rx, ry });
        p_level->addChild(cloud.p_sprite);
    }

    addIdleCb([&](double deltaTime) { idleUpdate(p_level, deltaTime); });
}

//------------------------------------------------------------------//

void CloudSpawner::idleUpdate(Level *p_level, double deltaTime)
{
    for (auto &cloud : m_clouds)
    {
        if (cloud.p_sprite->globalPosition().x > 4000)
        {
            double rx{ std::uniform_real_distribution<double>{ 0, 1000.0 }(m_engine) };
            double ry{ std::uniform_real_distribution<double>{ -500, 0.0 }(m_engine) };
            cloud.p_sprite->setGlobalPosition({ rx, ry });
        }
        else
        {
            cloud.p_sprite->setGlobalPosition(cloud.p_sprite->globalPosition() +
                                              AE::Vector2(deltaTime * cloud.speed, 0.0));
        }
    }
}

//------------------------------------------------------------------//
