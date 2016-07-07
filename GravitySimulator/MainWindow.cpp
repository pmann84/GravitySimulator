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
   m_text.Draw(m_window, fps, m_sim.BodyCount());

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
   // Add first body
   m_sim.AddBody(500.0, 50.0);

   // Add second body
   m_sim.AddBody(1.0, 2.0, CVector2(150.0, 0.0), CVector2(0.0, 2.0));
   // Add third body
   //m_sim.AddBody(0.5, 0.01, CVector2(200, 0.0), CVector2(0.0, 3.0));
}
