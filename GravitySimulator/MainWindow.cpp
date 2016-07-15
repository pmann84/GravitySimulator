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

bool CMainWindow::Draw()
{
   m_window.clear(sf::Color::Black);
   m_sim.Draw(m_window);

   int fps = m_fps.GetFps();
   m_text.Draw(m_window, fps, m_sim);

   m_window.setView(m_view);
   m_window.display();
   return true;
}

void CMainWindow::OnResize()
{
   sf::Vector2u size = m_window.getSize();
   m_view = sf::View(sf::FloatRect(0.f, 
                                   0.f, 
                                   static_cast<float>(size.x), 
                                   static_cast<float>(size.y)));
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
            }
         }
         //else if (event.type == sf::Event::MouseButtonPressed)
         //{
         //   if (event.mouseButton.button == sf::Mouse::Left)
         //   {
         //      std::cout << "Init mouse coordinates (x, y) = (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
         //      m_vInitClickPos = CVector2({ static_cast<double>(event.mouseButton.x), static_cast<double>(event.mouseButton.y) });
         //   }
         //}
         //else if (event.type == sf::Event::MouseButtonReleased)
         //{
         //   if (event.mouseButton.button == sf::Mouse::Left)
         //   {
         //      CVector2 finalClickPos({ static_cast<double>(event.mouseButton.x), static_cast<double>(event.mouseButton.y) });
         //      std::cout << "Final mouse coordinates (x, y) = (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
         //      CVector2 initVel = (finalClickPos - m_vInitClickPos);
         //      std::cout << "Velocity (x, y) = (" << initVel[0] << ", " << initVel[1] << ")" << std::endl;
         //      initVel.Normalise();

         //      m_sim.AddBody(1.0, 1.0, m_vInitClickPos, initVel);
         //   }
         //}
         else if (event.type == sf::Event::Resized)
         {
            OnResize();
         }
      }
      m_sim.Update();
      Draw();
   }
   return true;
}

void CMainWindow::SetupSim()
{
   // Set up a "real" earth sun like situation, using Solar Masses, Earth-Sun Radii, and 1yr timescale
   double massSun = 1.989e30;
   double massEarth = 5.972e24;
   double massMars = 6.39e23;
   double sunEarthRadius = 3.1536e7;
   double oneYearInSeconds = 1.496e11;
   m_sim.G(massSun, sunEarthRadius, oneYearInSeconds);
   m_sim.AddBody(1.0, 10.0, CVector2({ 0.0, 0.0 }), CVector2({ 0.0, 0.0 }), CVector3({ 255.0, 255.0, 0.0 })); // Sun
   m_sim.AddBody(massEarth/massSun, 2.0, CVector2({ 1.0, 0.0 }), CVector2({ 0.0, 6.5 }), CVector3({ 0.0, 204.0, 0.0 })); // Earth
   m_sim.AddBody(massMars/massSun, 1.0, CVector2({ 1.524, 0.0 }), CVector2({ 0.0, 6.5 }), CVector3({ 255.0, 0.0, 0.0 })); // Mars
}
