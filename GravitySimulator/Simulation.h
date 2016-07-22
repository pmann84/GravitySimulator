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
      Taylor,
      Leapfrog
   };

   void AddBody(double mass, double radius, bool isStatic = false);
   void AddBody(double mass, double radius, CVector2 position, bool isStatic = false);
   void AddBody(double mass, double radius, CVector2 position, CVector2 velocity, bool isStatic = false);
   void AddBody(double mass, double radius, CVector2 position, CVector2 velocity, CVector3 colour, bool isStatic = false);
   int BodyCount() const;
   void Update();
   void Reset();
   void Draw(sf::RenderWindow& window);
   void Pause();
   bool IsPaused();
   void DrawVelVectors();

   double G() const;
   void G(double g);
   void G(double massScale, double timeScale, double lengthScale);
   double Energy() const;
   CVector2 AngularMomentum() const;
   CVector2 CSimulation::CalculateTotalForceOnBody(const CBody& body);

   sf::Vector2f toSfVector2(CVector2 coord, sf::RenderWindow& window);
   CVector2 fromSfVector2(sf::Vector2f coord, sf::RenderWindow& window);

private:
   double m_gravConst;
   bool m_bPaused;
   bool m_bDrawVelVectors;

   std::vector<CBody> m_bodies;
   unsigned int m_nextId;

   SimulationBounds2D m_simBounds;

   void InitSimBounds();
   void SetSimBounds(double xMin, double xMax, double yMin, double yMax);

   void AddBody(CBody& body);
};

#endif