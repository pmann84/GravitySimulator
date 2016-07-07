#ifndef __TEXT_H__
#define __TEXT_H__

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

class CText
{
public:
   CText();
   ~CText();

   void Font(const std::string fontName);
   sf::Font& Font();

   bool Init();
   bool Draw(sf::RenderWindow& window, int fps, int bCount);

private:
   std::string m_fontPath;
   sf::Font m_font;

   std::string GetFrameRateString(int fps) const;
   std::string GetBodyCountString(int count) const;
   std::string GetWindowResString(sf::RenderWindow& window) const;
   std::string GetStringForIntValue(std::string text, int value) const;
   std::string AddNewline() const;
};

#endif
