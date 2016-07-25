#include "sfml_utils.h"

sf::Color sfmlutils::ToSfColor(CVector3 vector)
{
   return sf::Color(static_cast<sf::Uint8>(vector[0]), static_cast<sf::Uint8>(vector[1]), static_cast<sf::Uint8>(vector[2]));
}

CVector3 sfmlutils::ToVector3(sf::Color colour)
{
   return CVector3({ static_cast<double>(colour.r), static_cast<double>(colour.g), static_cast<double>(colour.b) });
}

std::vector<CVector2> sfmlutils::GenerateRandomPointsOnCircle(CVector2 centre, double radius, int numPoints)
{
   std::vector<CVector2> points;
   for (int i = 0; i < numPoints; ++i)
   {
      float pRadius = radius*sqrt(((double)rand() / (RAND_MAX)));
      float pAngle = 2.0*3.14159*((double)rand() / (RAND_MAX));
      points.push_back(CVector2({ pRadius*cos(pAngle) + centre[0], pRadius*sin(pAngle) + centre[1] }));
   }
   return points;
}
