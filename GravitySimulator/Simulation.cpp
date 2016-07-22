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

CVector2 CSimulation::CalculateTotalForceOnBody(const CBody& body)
{
   CVector2 force_agg;
   for (auto forceFromBody : m_bodies)
   {
      // Only add force contributions of other bodies, not itself
      if (body.Id() != forceFromBody.Id())
      {
         // Calculate the contribution of the force between the two bodies
         force_agg += body.ForceExertedBy(forceFromBody, G());
      }
   }
   return force_agg;
}

void CSimulation::Update()
{
   auto intMethod = IntegrationMethod::Leapfrog;

   CVector2 force_agg, new_force_agg;
   if (m_bodies.size() > 0)
   {
      // Loop over each body to calculate new position
      for (auto& body : m_bodies)
      {
         // Only calculate new position if body is not statics
         if (!body.Static())
         {
            double dt;
            CVector2 new_vel, new_pos;
            CVector2 temp_vel, temp_pos;

            dt = 0.001;

            switch (intMethod)
            {
            case IntegrationMethod::Euler:
               // Euler
               // v_n+1 = v_n + sum(F)*dt
               // p_n+1 = p_n + v_n+1 *dt
               force_agg = CalculateTotalForceOnBody(body);
               new_vel = body.Velocity() + force_agg*dt;
               new_pos = body.Position() + new_vel*dt;
               body.Acceleration(force_agg);
               body.Velocity(new_vel);
               body.Position(new_pos);
               break;
            case IntegrationMethod::Taylor:
               // Taylor Series
               // v_n+1 = v_n + sum(F)*dt
               // p_n+1 = p_n + v_n+1 *dt + 0.5*sum(F)*dt*dt
               force_agg = CalculateTotalForceOnBody(body);
               new_vel = body.Velocity() + force_agg*dt;
               new_pos = body.Position() + new_vel*dt + 0.5*force_agg*dt*dt;
               body.Acceleration(force_agg);
               body.Velocity(new_vel);
               body.Position(new_pos);
               break;
            case IntegrationMethod::Leapfrog:
               // Leapfrog
               // r_n+0.5 = r_n + 0.5*dt*v_n
               // v_n+1 = v_n + dt*a(r_n+0.5)
               // r_n+1 = r_n+0.5 + 0.5*dt*v_n+1
               temp_pos = body.Position() + dt*0.5*body.Velocity();
               body.Position(temp_pos);
               force_agg = CalculateTotalForceOnBody(body);
               new_vel = body.Velocity() + dt*force_agg;
               new_pos = temp_pos + 0.5*dt*new_vel;
               body.Velocity(new_vel);
               body.Position(new_pos);
               break;
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
         shape.setFillColor(sfmlutils::ToSfColor(b.Colour()));
         auto screenCoords = toSfVector2(b.Position(), window);
         // Draw at the centre
         shape.setPosition(static_cast<float>(screenCoords.x), static_cast<float>(screenCoords.y));
         // adjust for radius of circle
         shape.move(static_cast<float>(-b.Radius()), static_cast<float>(-b.Radius()));

         if (m_bDrawVelVectors)
         {
            // Draw velocity vectors
            sf::VertexArray lines(sf::LinesStrip, 2);
            lines[0].position = toSfVector2(b.Position(), window);
            auto finalVelVectorPos = b.Position() + b.Velocity();
            finalVelVectorPos.Normalise();
            lines[1].position = toSfVector2(finalVelVectorPos, window);
            window.draw(lines);
         }

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

void CSimulation::DrawVelVectors()
{
   m_bDrawVelVectors = !m_bDrawVelVectors;
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
   // E = 0.5 * sum{i=1..N}(m_i v_i^2) + sum{i=1..N}(sum{j!=i}(Gm_im_j/|r_i - r_j|))
   double energy = 0.0;
   for (auto& body : m_bodies)
   {
      energy += 0.5*body.Mass()*body.Velocity().NormSquared(); // Kinetic energy
      // Get all bodies with 
      for (auto& potentialBody : m_bodies)
      {
         if (body.Id() != potentialBody.Id())
         {
            energy -= body.GravitationalPotential(potentialBody, m_gravConst);
         }
      }
   }
   return energy;
}

CVector2 CSimulation::AngularMomentum() const
{
   // J = sum{i=1..N}(r_i cross m_i v_i)
   return CVector2();
}

void GetTransformedPositions(double coord_x, double coord_y,
                             double xmin1, double xmax1, double ymin1, double ymax1,
                             double xmin2, double xmax2, double ymin2, double ymax2,
                             double& new_coord_x, double& new_coord_y)
{
   // Get percentage of x & y in sim space
   double x_percent = (coord_x - xmin1) / (xmax1 - xmin1);
   double y_percent = (coord_y - ymin1) / (ymax1 - ymin1);

   // Get values of same percent in screen space
   new_coord_x = x_percent * abs(xmax2 - xmin2) + xmin2;
   new_coord_y = y_percent * abs(ymax2 - ymin2) + ymin2;
}

sf::Vector2f CSimulation::toSfVector2(CVector2 coord, sf::RenderWindow& window)
{
   // Get min max values
   double screen_x_min = 0.0;
   double screen_x_max = window.getSize().x;
   double screen_y_min = 0.0;
   double screen_y_max = window.getSize().y;

   double sim_x_min = m_simBounds.x_axis.Min;
   double sim_x_max = m_simBounds.x_axis.Max;
   double sim_y_min = m_simBounds.y_axis.Min;
   double sim_y_max = m_simBounds.y_axis.Max;

   //// Normalise input
   //coord.Normalise();

   double xpos, ypos;
   GetTransformedPositions(coord[0], coord[1],
                           sim_x_min, sim_x_max, sim_y_min, sim_y_max,
                           screen_x_min, screen_x_max, screen_y_min, screen_y_max,
                           xpos, ypos);

   // return in sf vector
   return sf::Vector2f(static_cast<float>(xpos),
                       static_cast<float>(ypos));
}

CVector2 CSimulation::fromSfVector2(sf::Vector2f coord, sf::RenderWindow& window)
{
   // Get min max values
   double screen_x_min = 0.0;
   double screen_x_max = window.getSize().x;
   double screen_y_min = 0.0;
   double screen_y_max = window.getSize().y;

   double sim_x_min = m_simBounds.x_axis.Min;
   double sim_x_max = m_simBounds.x_axis.Max;
   double sim_y_min = m_simBounds.y_axis.Min;
   double sim_y_max = m_simBounds.y_axis.Max;

   //// Normalise input
   //double mag = sqrt(coord.x*coord.x + coord.y*coord.y);
   //auto norm_x = coord.x * (1.0 / mag);
   //auto norm_y = coord.y * (1.0 / mag);

   double xpos, ypos;
   GetTransformedPositions(coord.x, coord.y,
                           sim_x_min, sim_x_max, sim_y_min, sim_y_max,
                           screen_x_min, screen_x_max, screen_y_min, screen_y_max,
                           xpos, ypos);

   // return in sf vector
   return CVector2({ static_cast<float>(xpos),
                     static_cast<float>(ypos) });
}
