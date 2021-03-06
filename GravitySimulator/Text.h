﻿#ifndef __TEXT_H__
#define __TEXT_H__

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Simulation.h"

class CText
{
public:
   CText();
   ~CText();

   void Font(const std::string fontName);
   sf::Font& Font();

   bool Init();
   bool Draw(sf::RenderWindow& window, int fps, const CSimulation& sim, double massInsert, std::string insMode);
   void DrawInstructionsText(sf::RenderWindow& window);

private:
   std::string m_fontPath;
   sf::Font m_font;

   std::string GetFrameRateString(int fps) const;
   std::string GetBodyCountString(int count) const;
   std::string GetGravConstValueString(double val) const;
   std::string GetSimTotalEnergyString(double val) const;
   std::string GetWindowResString(sf::RenderWindow& window) const;
   std::string GetMassInsertString(double val) const;
   std::string GetInsertModeString(std::string ins) const;
   std::string GetStringForValue(std::string text, int value) const;
   std::string GetStringForValue(std::string text, double value) const;
   std::string GetStringForValue(std::string text, std::string value) const;
   std::string AddNewline() const;

   std::string GetInstructionsString(int& numLines);
};

#endif
