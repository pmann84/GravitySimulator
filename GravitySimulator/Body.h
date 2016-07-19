#ifndef __BODY_H__
#define __BODY_H__

#include "Vector.h"

class CBody
{
public:
   CBody(unsigned int id);
   CBody(unsigned int id, double mass, double radius);
   CBody(const CBody& body);
   ~CBody();

   CVector2 Position() const;
   void Position(const CVector2& rPos);
   
   CVector2 InitialPosition() const;
   void InitialPosition(const CVector2& rPos);

   CVector2 Velocity() const;
   void Velocity(const CVector2& rVel);

   CVector2 InitialVelocity() const;
   void InitialVelocity(const CVector2& rVel);

   CVector2 Acceleration() const;
   void Acceleration(const CVector2& rAcc);

   CVector3 Colour() const;
   void Colour(const CVector3& rColour);

   unsigned int Id() const { return m_iBodyId; };

   double Mass() const { return m_dMass; };
   void Mass(double m) { m_dMass = m; };

   double Radius() const { return m_dRadius; };
   void Radius(double r) { m_dRadius = r; };

   bool Static() const { return m_bStatic; };
   void Static(bool s) { m_bStatic = s; };

   CVector2 DistVectToBody(const CBody& body) const;

   double GravitationalPotential(const CBody& body, double G) const;
   double GravitationalForce(const CBody& body, double G) const;
   CVector2 ForceExertedBy(const CBody& body, double G) const;

   void operator=(const CBody& body)
   {
      m_dMass = body.Mass();
      m_dRadius = body.Radius();
      m_vPosition = body.Position();
      m_vVelocity = body.Velocity();
      m_vAcceleration = body.Acceleration();
      m_bStatic = body.Static();
   }

private:
   const unsigned int m_iBodyId;
   double m_dMass;
   double m_dRadius;
   CVector2 m_vPosition;
   CVector2 m_vInitialPosition;
   CVector2 m_vVelocity;
   CVector2 m_vInitialVelocity;
   CVector2 m_vAcceleration;
   CVector3 m_vColour;
   bool m_bStatic;
};

#endif