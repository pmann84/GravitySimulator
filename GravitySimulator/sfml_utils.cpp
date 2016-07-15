#include "sfml_utils.h"

sf::Color sfmlutils::ToSfColor(CVector3 vector)
{
   return sf::Color(vector[0], vector[1], vector[2]);
}

CVector3 sfmlutils::ToVector3(sf::Color colour)
{
   return CVector3({ static_cast<double>(colour.r), static_cast<double>(colour.g), static_cast<double>(colour.b) });
}
