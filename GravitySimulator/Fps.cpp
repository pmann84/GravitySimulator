#include "Fps.h"

CFps::CFps()
{
}

CFps::~CFps()
{
}

int CFps::GetFps()
{
   sf::Time time = m_clock.getElapsedTime();
   int fps = static_cast<int>(1.f / time.asSeconds());
   m_clock.restart().asSeconds();
   return fps;
}
