#include <ui/coconut_bar.h>

#include <utilities/window.h>

//------------------------------------------------------------------//

CoconutBar::CoconutBar()
    : update(
          [this](int coconuts)
          {
              for (size_t i = 0; i < m_coconuts.size(); i++)
              {
                  if ((i + 1) > coconuts)
                  {
                      m_coconuts[i]->setEnabled(false);
                  }
                  else
                  {
                      m_coconuts[i]->setEnabled(true);
                  }
              }
          })
{
    setIsUi(true);

    for (size_t i = 0; i < m_coconuts.size(); i++)
    {
        auto &p_coconut{ m_coconuts[i] };
        p_coconut = new AE::Sprite();
        addChild(p_coconut);
        p_coconut->setEnabled(false);
        p_coconut->setTexture("assets/coconut.png");
        p_coconut->setScale({ 2.0, 2.0 });
        p_coconut->setGlobalPosition(
            AE::Vector2{ AE::Window::size().x - static_cast<double>(i) * 100.0 - 100.0, AE::Window::size().y - 100.0 });
    }
}

//------------------------------------------------------------------//
