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
                  force_agg += body.ForceExertedBy(forceFromBody, G());
               }
            }

            double dt;
            CVector2 new_vel, new_pos;

            dt = 0.01;

            new_vel = body.Velocity() + force_agg*dt;
            new_pos = body.Position() + new_vel*dt;
            body.Acceleration(force_agg);
            body.Velocity(new_vel);
            body.Position(new_pos);
                       

            // Euler
            // v_n+1 = v_n + sum(F)*dt
            // p_n+1 = p_n + v_n+1 *dt

            // v_n+1 = v_n + sum(F)*dt
            // p_n+1 = p_n + v_n+1 *dt + 0.5*sum(F)*dt*dt

            // Improved Euler
            // a_n = sum(F(p_n))
            // p_temp = p_n + v_n * dt
            // a_temp = sum(F(p_temp))
            // v_n+1 = v_n + 0.5 * (a_n + a_temp) * dt
            // p_n+1 = p_n + 0.5 * (v_n+1 + v_n) * dt
         }
      }
   }
}

void CSimulation::Reset()
{
   for (auto& body : m_bodies)
   {
      body.Position(body.InitialPosition());
      body.Velocity(body.InitialVelocity());
   }
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

void CSimulation::Pause()
{
   m_bPaused = !m_bPaused;
}

bool CSimulation::IsPaused()
{
   return m_bPaused;
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
   m_gravConst = (GCONST * massScale * timeScale * timeScale) / (lengthScale * lengthScale * lengthScale);
}

double CSimulation::Energy() const
{
   // E = 0.5 * sum{i=1..N}(m_i v_i^2) - sum{i=1..N}(sum{j!=i}(Gm_im_j/|r_i - r_j|))
   double energy = 0.0;
   for (auto& body : m_bodies)
   {
      energy += 0.5*body.Mass()*body.Velocity().NormSquared(); // Kinetic energy
      // Get all bodies with 
      //energy -= 
   }
   return energy;
}

CVector2 CSimulation::AngularMomentum() const
{
   // J = sum{i=1..N}(r_i cross m_i v_i)
   return CVector2();
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
