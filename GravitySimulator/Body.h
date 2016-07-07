﻿#ifndef __BODY_H__
#define __BODY_H__

#include "Vector2.h"

class CBody
{
public:
   CBody(unsigned int id);
   CBody(unsigned int id, double mass, double radius);
   CBody(const CBody& body);
   ~CBody();

   CVector2 Position() const;
   void Position(const CVector2& rPos);

   CVector2 Velocity() const;
   void Velocity(const CVector2& rVel);

   unsigned int Id() const { return m_iBodyId; };

   double Mass() const { return m_dMass; };
   void Mass(double m) { m_dMass = m; };

   double Radius() const { return m_dRadius; };
   void Radius(double r) { m_dRadius = r; };

   bool Static() const { return m_bStatic; };
   void Static(bool s) { m_bStatic = s; };

   void operator=(const CBody& body)
   {
      m_dMass = body.Mass();
      m_dRadius = body.Radius();
      m_vPosition = body.Position();
      m_vVelocity = body.Velocity();
      m_bStatic = body.Static();
   }

private:
   const unsigned int m_iBodyId;
   double m_dMass;
   double m_dRadius;
   CVector2 m_vPosition;
   CVector2 m_vVelocity;
   bool m_bStatic;
};

#endif