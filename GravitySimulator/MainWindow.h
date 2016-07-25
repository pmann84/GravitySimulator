#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <SFML/Graphics.hpp>

#include "Text.h"
#include "Fps.h"
#include "Simulation.h"

enum InsertMode
{
   Single,
   RandomDisc
};

inline std::string InsertModeStr(InsertMode mode)
{
   switch (mode)
   {
   case Single:
      return "Single";
   case RandomDisc:
      return "Random Disc";
   }
   return "";
}

class CMainWindow
{
public:
   CMainWindow();
   ~CMainWindow();

   bool Init();
   bool Run();

   void SetupSim();

private:
   sf::Vector2f m_vInitClickPos;
   bool m_bIsLeftMousePressed;
   double m_dMassInsertValue;
   double m_dMassInsertIncrement;
   InsertMode m_eInsertMode;

   bool Draw(sf::Event event);
   void OnResize();
   void DrawVelocityVector(sf::Event event, sf::RenderWindow& window);
   sf::Vector2f GetCurrentClickPosition(sf::Event event);
   sf::Vector2f GetScreenVelocityFromInitClick(sf::Event event);
   CVector2 GetSimVelocityFromInitClick(sf::Event event);

   sf::RenderWindow m_window;
   sf::View m_view;

   CText m_text;
   CFps m_fps;
   CSimulation m_sim;
};

#endif // __MAINWINDOW_H__