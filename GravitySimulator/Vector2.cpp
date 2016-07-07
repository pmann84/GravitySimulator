#include "Vector2.h"

CVector2::CVector2() : m_fX(0.0), m_fY(0.0)
{
}

CVector2::CVector2(double x, double y) : m_fX(x), m_fY(y)
{
}

CVector2::~CVector2()
{
}

double CVector2::Distance(const CVector2& other) const
{
   return (other - CVector2(m_fX, m_fY)).Magnitude();
}

double CVector2::Magnitude() const
{
   return sqrt(ModSquared());
}

double CVector2::ModSquared() const
{
   return m_fX*m_fX + m_fY*m_fY;
}
