#include "Body.h"

CBody::CBody(unsigned int id) : m_iBodyId(id), m_dMass(1.0), m_dRadius(1.0)
{
}

CBody::CBody(unsigned int id, double mass, double radius) : m_iBodyId(id), m_dMass(mass), m_dRadius(radius)
{
}

CBody::CBody(const CBody& body) : 
            m_iBodyId(body.Id()), 
            m_dMass(body.Mass()), 
            m_dRadius(body.Radius()), 
            m_vPosition(body.Position()), 
            m_vVelocity(body.Velocity()), 
            m_bStatic(body.Static())
{
}

CBody::~CBody()
{
}

CVector2 CBody::Position() const
{
   return m_vPosition;
}

void CBody::Position(const CVector2& rPos)
{
   m_vPosition = rPos;
}

CVector2 CBody::Velocity() const
{
   return m_vVelocity;
}

void CBody::Velocity(const CVector2& rVel)
{
   m_vVelocity = rVel;
}
