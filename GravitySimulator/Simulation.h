#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>
#include <chrono>
#include <thread>


#include "sfml_utils.h"
#include "Body.h"

static double GCONST = 6.67408e-11;

struct SimulationAxis
{
   double Min;
   double Max;
};

struct SimulationBounds2D
{
   SimulationAxis x_axis;
   SimulationAxis y_axis;
};

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
   void AddBody(double mass, double radius, CVector2 position, CVector2 velocity, CVector3 colour, bool isStatic = false);
   int BodyCount() const;
   void Update();
   void Reset();
   void Draw(sf::RenderWindow& window);

   double G() const;
   void G(double g);
   void G(double massScale, double timeScale, double lengthScale);

private:
   double m_gravConst;

   std::vector<CBody> m_bodies;
   std::vector<CBody> m_bodies_original;
   unsigned int m_nextId;

   SimulationBounds2D m_simBounds;

   void InitSimBounds();
   void SetSimBounds(double xMin, double xMax, double yMin, double yMax);

   void AddBody(CBody& body);
   sf::Vector2f toSfVector2(CVector2 coord, sf::RenderWindow& window);
};

#endif