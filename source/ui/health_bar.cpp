#include <ui/health_bar.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

HealthBar::HealthBar()
    : update(
          [this](int health)
          {
              for (size_t i = 0; i < m_hearts.size(); i++)
              {
                  if ((i + 1) > health)
                  {
                      m_hearts[i]->setEnabled(false);
                  }
              }
          })
{
    setIsUi(true);

    for (size_t i = 0; i < m_hearts.size(); i++)
    {
        auto &p_heart{ m_hearts[i] };
        p_heart = new AE::Sprite();
        addChild(p_heart);
        p_heart->setTexture("assets/health.png");
        p_heart->setScale({ 2.0, 2.0 });
        p_heart->setGlobalPosition(AE::Vector2{ static_cast<double>(i) * 100.0 + 100.0, AE::Window::size().y - 100.0 });
    }
}

//------------------------------------------------------------------//
