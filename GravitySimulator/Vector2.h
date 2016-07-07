#ifndef __VECTOR2_H__
#define __VECTOR2_H__
#include <vector>

class CVector2
{
public:
   CVector2();
   CVector2(double x, double y);
   ~CVector2();

   double x() const { return m_fX; };
   void x(double value) { m_fX = value; };
   double y() const { return m_fY; };
   void y(double value) { m_fY = value; };

   double Distance(const CVector2& other) const;
   double Magnitude() const;
   double ModSquared() const;

   friend CVector2 operator+(CVector2 lhs, const CVector2& rhs) 
   { 
      return lhs += rhs;
   }

   CVector2& operator+=(const CVector2& rhs)
   {
      m_fX += rhs.x();
      m_fY += rhs.y();
      return *this;
   }

   friend CVector2 operator-(CVector2 lhs, const CVector2& rhs)
   {
      return CVector2(
         lhs.x() - rhs.x(),
         lhs.y() - rhs.y());
   }

   friend CVector2 operator*(CVector2 lhs, const float& rhs)
   {
      return CVector2(
         lhs.x() * rhs,
         lhs.y() * rhs);
   }

private:
   double m_fX, m_fY;
};

#endif