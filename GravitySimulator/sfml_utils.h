#ifndef __SFML_UTILS_H__
#define __SFML_UTILS_H__

#include <SFML/Graphics/Color.hpp>
#include "Vector.h"

namespace sfmlutils
{
   sf::Color ToSfColor(CVector3 vector);
   CVector3 ToVector3(sf::Color);
}


#endif // __SFML_UTILS_H__
