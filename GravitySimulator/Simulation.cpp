#include "Simulation.h"

CSimulation::CSimulation() : m_nextId(0)
{
   InitSimBounds();
}

CSimulation::~CSimulation()
{
}

void CSimulation::InitSimBounds()
{
   SetSimBounds(-3.0, 3.0, -3.0, 3.0);
}

void CSimulation::SetSimBounds(double xMin, double xMax, double yMin, double yMax)
{
   m_simBounds.x_axis.Min = xMin;
   m_simBounds.x_axis.Max = xMax;
   m_simBounds.y_axis.Min = yMin;
   m_simBounds.y_axis.Max = yMax;
}

void CSimulation::AddBody(CBody& body)
{
   m_bodies.push_back(body);
   m_bodies_original.push_back(body);
}

void CSimulation::AddBody(double mass, double radius, bool isStatic)
{
   CBody newBody(m_nextId++, mass, radius);
   newBody.Static(isStatic);
   AddBody(newBody);
}

void CSimulation::AddBody(double mass, double radius, CVector2 position, bool isStatic)
{
   CBody newBody(m_nextId++, mass, radius);
   newBody.Position(position);
   newBody.Static(isStatic);
   AddBody(newBody);
}

void CSimulation::AddBody(double mass, double radius, CVector2 position, CVector2 velocity, bool isStatic)
{
   CBody newBody(m_nextId++, mass, radius);
   newBody.Position(position);
   newBody.Velocity(velocity);
   newBody.Static(isStatic);
   AddBody(newBody);
}

void CSimulation::AddBody(double mass, double radius, CVector2 position, CVector2 velocity, CVector3 colour, bool isStatic)
{
   CBody newBody(m_nextId++, mass, radius);
   newBody.Position(position);
   newBody.Velocity(velocity);
   newBody.Colour(colour);
   newBody.Static(isStatic);
   AddBody(newBody);
}

int CSimulation::BodyCount() const
{
   return m_bodies.size();
}

void CSimulation::Update()
{
   auto intMethod = IntegrationMethod::Euler;

   CVector2 force_agg;
   if (m_bodies.size() > 0)
   {
      // Loop over each body to calculate new position
      for (auto& body : m_bodies)
      {
         // Only calculate new position if body is not statics
         if (!body.Static())
         {
            //std::cout << "Calculating Total Force on Body " << body.Id() << std::endl;
            // Loop over all the bodies again
            for (auto forceFromBody : m_bodies)
            {
               // Only add force contributions of other bodies, not itself
               if (body.Id() != forceFromBody.Id())
               {
                  // Calculate the contribution of the force between the two bodies
                  //std::cout << "\tAdding force contribution from Body " << forceFromBody.Id() << std::endl;
                  auto distVector = forceFromBody.Position() - body.Position();
                  auto distMag = distVector.Norm()*distVector.Norm()*distVector.Norm();
                  auto forceAdd = CVector2({ (G()*forceFromBody.Mass()*distVector[0]) / distMag, (G()*forceFromBody.Mass()*distVector[1]) / distMag });
                  force_agg += forceAdd;
               }
            }

            double dt;
            CVector2 new_vel, new_pos;
            switch (intMethod)
            {
            case IntegrationMethod::Euler:
               dt = 0.01;
               new_vel = body.Velocity() + force_agg*dt;
               new_pos = body.Position() + new_vel*dt;
               body.Velocity(new_vel);
               body.Position(new_pos);
               break;
            case IntegrationMethod::Verlet:
               break;
            }
            
            // Update position and velocity
            // m_i d^2 p_i / dt^2 = - G m_i m_j (p_j - p_i) / || p_j - p_i ||^3

            // d v_i / dt = - sum{ G m_j (p_j - p_i) / || p_j - p_i ||^3 }
            // d p_i / dt = v_i
            

            // Euler
            // v_n+1 = v_n + sum(F)*dt
            // p_n+1 = p_n + v_n+1 *dt

            // v_n+1 = v_n + sum(F)*dt
            // p_n+1 = p_n + v_n+1 *dt + 0.5*sum(F)*dt*dt

            // Vertlet
            // 
            // 
            
         }
      }
   }
}

void CSimulation::Reset()
{
   m_bodies.clear();
   m_bodies = m_bodies_original;
}

void CSimulation::Draw(sf::RenderWindow& window)
{
   if (m_bodies.size() > 0)
   {
      for (auto b : m_bodies)
      {
         sf::CircleShape shape(static_cast<float>(b.Radius()));
         //shape.setFillColor(sfmlutils::ToSfColor(b.Colour()));
         shape.setFillColor(sf::Color::Yellow);
         auto screenCoords = toSfVector2(b.Position(), window);
         // Draw at the centre
         shape.setPosition(static_cast<float>(screenCoords.x), static_cast<float>(screenCoords.y));
         // adjust for radius of circle
         shape.move(static_cast<float>(-b.Radius()), static_cast<float>(-b.Radius()));
         
         window.draw(shape);
      }
   }
}

double CSimulation::G() const
{
   return m_gravConst;
}

void CSimulation::G(double g)
{
   m_gravConst = g;
}

void CSimulation::G(double massScale, double timeScale, double lengthScale)
{
   m_gravConst = (GCONST * massScale * timeScale * timeScale) / (lengthScale*lengthScale*lengthScale);
}

sf::Vector2f CSimulation::toSfVector2(CVector2 coord, sf::RenderWindow& window)
{
   // Get conversion delta
   double deltax = (m_simBounds.x_axis.Max - m_simBounds.x_axis.Min) / window.getSize().x;
   double deltay = (m_simBounds.y_axis.Max - m_simBounds.y_axis.Min) / window.getSize().y;
   // Convert sim space to screen space
   double xpos = (coord[0] - m_simBounds.x_axis.Min) / deltax;
   double ypos = (m_simBounds.y_axis.Max - coord[1]) / deltay;

   return sf::Vector2f(static_cast<float>(xpos),
                       static_cast<float>(ypos));
}
