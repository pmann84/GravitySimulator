#ifndef __FPS_H__
#define __FPS_H__

#include <SFML/System/Clock.hpp>

// TODO: Replace sf::Clock with the C++11 chrono library functions

class CFps
{
public:
   CFps();
   ~CFps();

   int GetFps();

private:
   sf::Clock m_clock;

};

#endif // __FPS_H__