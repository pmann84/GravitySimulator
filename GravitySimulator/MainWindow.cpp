#include "MainWindow.h"

CMainWindow::CMainWindow()
{
}

CMainWindow::~CMainWindow()
{
}

bool CMainWindow::Init()
{
   m_text.Init();
   m_text.Font("Consola");
   
   sf::ContextSettings windowSettings;
   windowSettings.antialiasingLevel = 8;

   m_window.create(sf::VideoMode(800, 600), "SFML Window", sf::Style::Default, windowSettings);
   m_window.setVerticalSyncEnabled(true);
   //m_window.setFramerateLimit(60);
   
   m_view = sf::View(m_window.getDefaultView());

   SetupSim();

   return true;
}

bool CMainWindow::Draw(sf::Event event)
{
   m_window.clear(sf::Color::Black);
   m_sim.Draw(m_window);

   int fps = m_fps.GetFps();
   m_text.Draw(m_window, fps, m_sim);

   if (m_bIsLeftMousePressed)
   {
      DrawVelocityVector(event, m_window);
   }

   m_window.setView(m_view);
   m_window.display();
   return true;
}

void CMainWindow::DrawVelocityVector(sf::Event event, sf::RenderWindow& window)
{
   sf::Vector2f initVel = GetScreenVelocityFromInitClick(event);
   // Draw velocity vectors
   sf::VertexArray lines(sf::LinesStrip, 2);
   lines[0].position = m_vInitClickPos;
   auto finalVelVectorPos = m_vInitClickPos - initVel;
   lines[1].position = finalVelVectorPos;
   window.draw(lines);
}

void CMainWindow::OnResize()
{
   sf::Vector2u size = m_window.getSize();
   m_view = sf::View(sf::FloatRect(0.f, 
                                   0.f, 
                                   static_cast<float>(size.x), 
                                   static_cast<float>(size.y)));
}

sf::Vector2f CMainWindow::GetCurrentClickPosition(sf::Event event)
{
   if (event.type == sf::Event::MouseMoved)
   {
      return sf::Vector2f({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
   }
   return sf::Vector2f({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) });
}

sf::Vector2f CMainWindow::GetScreenVelocityFromInitClick(sf::Event event)
{
   sf::Vector2f currClickPos = GetCurrentClickPosition(event);
   return currClickPos - m_vInitClickPos;
}

CVector2 CMainWindow::GetSimVelocityFromInitClick(sf::Event event)
{
   sf::Vector2f currClickPos = GetCurrentClickPosition(event);
   auto currSim = m_sim.fromSfVector2(currClickPos, m_window);
   auto initSim = m_sim.fromSfVector2(m_vInitClickPos, m_window);
   return currSim - initSim;
}


bool CMainWindow::Run()
{
   while (m_window.isOpen())
   {
      sf::Event event;
      while (m_window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            m_window.close();
         }
         else if (event.type == sf::Event::KeyPressed)
         {
            switch (event.key.code)
            {
            case sf::Keyboard::R:
               m_sim.Reset();
               break;
            case sf::Keyboard::Space:
               m_sim.Pause();
               break;
            case sf::Keyboard::V:
               m_sim.DrawVelVectors();
               break;
            }
         }
         else if (event.type == sf::Event::MouseButtonPressed)
         {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
               m_vInitClickPos = sf::Vector2f({ static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) });
               m_bIsLeftMousePressed = true;
            }
         }
         else if (event.type == sf::Event::MouseButtonReleased)
         {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
               // Get the sim position for new body 
               auto pos = m_sim.fromSfVector2(m_vInitClickPos, m_window);
               std::cout << "New Body Position (x, y) = ( " << pos[0] << ", " << pos[1] << ")" << std::endl;
               // Get the sim velocity for the new body
               CVector2 vel = GetSimVelocityFromInitClick(event);
               vel *= 3.0;
               vel = vel.Opposite();
               std::cout << "New Body Velocity (x, y) = ( " << vel[0] << ", " << vel[1] << ")" << std::endl;
               // Add body with calculated vel
               m_sim.AddBody(0.0003, 1.0, pos, vel, CVector3({ 255.0, 255.0, 0.0 }));
               m_bIsLeftMousePressed = false;
            }
         }
         else if (event.type == sf::Event::Resized)
         {
            OnResize();
         }
      }
      if (!m_sim.IsPaused())
      {
         m_sim.Update();
         Draw(event);
      }
   }
   return true;
}

void CMainWindow::SetupSim()
{
   // Set up a "real" earth sun like situation, using Solar Masses, AU, and 1yr timescale
   
   // Actual values - temporal
   double oneYearInSeconds = 3.1536e7;
   // Distances
   double sunMercuryRadius = 5.791e10;
   double sunVenusRadius = 1.082e11;
   double sunEarthRadius = 1.496e11;
   double sunMarsRadius = 2.279e11;
   // Masses
   double massSun = 1.989e30;
   double massMercury = 3.285e23;
   double massVenus = 4.867e24;
   double massEarth = 5.972e24;
   double massMars = 6.39e23;
   // Orbital Speeds
   double velocityMercury = 5.66e4; //56.6 km/s
   double velocityVenus = 3.502e4; // 35.02 km/s
   double velocityEarth = 3e4; // 30 km/s
   double velocityMars = 2.4e4; //24 km/s

   // Scaled values - Distances
   double scaledDistMercury = sunMercuryRadius / sunEarthRadius;
   double scaledDistVenus = sunVenusRadius / sunEarthRadius;
   double scaledDistEarth = sunEarthRadius / sunEarthRadius;
   double scaledDistMars = sunMarsRadius / sunEarthRadius;
   // Masses
   double scaledMassSun = massSun / massSun;
   double scaledMassMercury = massMercury / massSun;
   double scaledMassVenus = massVenus / massSun;
   double scaledMassEarth = massEarth / massSun;
   double scaledMassMars = massMars / massSun;
   // Orbital speeds
   double scaledVelMercury = (velocityMercury * oneYearInSeconds) / sunEarthRadius;
   double scaledVelVenus = (velocityVenus * oneYearInSeconds) / sunEarthRadius;
   double scaledVelEarth = (velocityEarth * oneYearInSeconds) / sunEarthRadius;
   double scaledVelMars = (velocityMars * oneYearInSeconds) / sunEarthRadius;

   m_sim.G(massSun, oneYearInSeconds, sunEarthRadius);

   m_sim.AddBody(scaledMassSun, 10.0, CVector2({ 0.0, 0.0 }), CVector2({ 0.0, 0.0 }), CVector3({ 255.0, 255.0, 0.0 })); // Sun
   m_sim.AddBody(scaledMassMercury, 1.0, CVector2({ scaledDistMercury, 0.0 }), CVector2({ 0.0, scaledVelMercury }), CVector3({ 0.0, 204.0, 0.0 })); // Mercury
   m_sim.AddBody(scaledMassVenus, 1.0, CVector2({ scaledDistVenus, 0.0 }), CVector2({ 0.0, scaledVelVenus }), CVector3({ 153.0, 76.0, 0.0 })); // Venus
   m_sim.AddBody(scaledMassEarth, 2.0, CVector2({ scaledDistEarth, 0.0 }), CVector2({ 0.0, scaledVelEarth }), CVector3({ 0.0, 0.0, 255.0 })); // Earth
   m_sim.AddBody(scaledMassMars, 1.0, CVector2({ scaledDistMars, 0.0 }), CVector2({ 0.0, scaledVelMars }), CVector3({ 255.0, 0.0, 0.0 })); // Mars

   // Simulate a binary star system
   //double binarySeparation = 2.0;
   //double binaryVelX = 1.0;
   //double binaryVelY = 2.5;
   //m_sim.AddBody(scaledMassSun, 10.0, CVector2({ binarySeparation / 2.0, 0.0 }), CVector2({ -binaryVelX, binaryVelY }), CVector3({ 255.0, 255.0, 0.0 })); // Sun #1
   //m_sim.AddBody(scaledMassSun, 10.0, CVector2({ -binarySeparation / 2.0, 0.0 }), CVector2({ binaryVelX, -binaryVelY }), CVector3({ 255.0, 255.0, 0.0 })); // Sun #2
}
