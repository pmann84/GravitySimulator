#include "Text.h"

CText::CText()
{
}

CText::~CText()
{
}

void CText::Font(const std::string fontName)
{
   std::stringstream ss;
   ss << "C:\\Windows\\Fonts\\" << fontName << ".ttf";
   m_fontPath = ss.str();
   if (!m_font.loadFromFile(m_fontPath))
   {
      throw;
   }
}

sf::Font& CText::Font()
{
   return m_font;
}

bool CText::Init()
{
   return true;
}

bool CText::Draw(sf::RenderWindow& window, int fps, int bCount)
{
   sf::Text screenText;
   screenText.setFont(Font());
   screenText.setCharacterSize(12);

   std::string windowStr = GetFrameRateString(fps);
   windowStr += AddNewline();
   windowStr += GetWindowResString(window);
   windowStr += AddNewline();
   windowStr += GetBodyCountString(bCount);

   screenText.setString(windowStr);
   window.draw(screenText);
   return true;
}

std::string CText::GetFrameRateString(int fps) const
{
   return GetStringForIntValue("Framerate: ", fps);
}

std::string CText::GetBodyCountString(int count) const
{
   return GetStringForIntValue("Body Count: ", count);
}

std::string CText::GetWindowResString(sf::RenderWindow& window) const
{
   sf::Vector2u size = window.getSize();
   std::stringstream ss;
   ss << "Res: " << std::to_string(size.x) << "x" << std::to_string(size.y);
   return ss.str();
}

std::string CText::GetStringForIntValue(std::string text, int value) const
{
   std::stringstream ss;
   ss << text << std::to_string(value);
   return ss.str();
}

std::string CText::AddNewline() const
{
   return "\n";
}
