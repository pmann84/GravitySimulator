#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics/CircleShape.hpp>

#include "Body.h"

class CSimulation
{
public:
   CSimulation();
   ~CSimulation();

   enum IntegrationMethod
   {
      Euler,
      Verlet
   };

   void AddBody(double mass, double radius, bool isStatic = false);
   void AddBody(double mass, double radius, CVector2 position, bool isStatic = false);
   void AddBody(double mass, double radius, CVector2 position, CVector2 velocity, bool isStatic = false);
   int BodyCount() const;
   void Update();
   void Reset();
   void Draw(sf::RenderWindow& window);

private:
   std::vector<CBody> m_bodies;
   std::vector<CBody> m_bodies_original;
   unsigned int m_nextId;

   void AddBody(CBody& body);
   sf::Vector2f toSfVector2(CVector2 coord);
};

#endif