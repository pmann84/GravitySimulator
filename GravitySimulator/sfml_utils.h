#ifndef __SFML_UTILS_H__
#define __SFML_UTILS_H__

#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "Vector.h"

namespace sfmlutils
{
   sf::Color ToSfColor(CVector3 vector);
   CVector3 ToVector3(sf::Color);
   std::vector<CVector2> GenerateRandomPointsOnCircle(CVector2 centre, double radius, int numPoints);
}


#endif // __SFML_UTILS_H__
