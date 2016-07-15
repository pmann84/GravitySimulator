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

bool CText::Draw(sf::RenderWindow& window, int fps, const CSimulation& sim)
{
   sf::Text screenText;
   screenText.setFont(Font());
   screenText.setCharacterSize(12);

   std::string windowStr = GetFrameRateString(fps);
   windowStr += AddNewline();
   windowStr += GetWindowResString(window);
   windowStr += AddNewline();
   windowStr += GetBodyCountString(sim.BodyCount());
   windowStr += AddNewline();
   windowStr += GetGravConstValueString(sim.G());

   screenText.setString(windowStr);
   window.draw(screenText);
   return true;
}

std::string CText::GetFrameRateString(int fps) const
{
   return GetStringForValue("Framerate: ", fps);
}

std::string CText::GetBodyCountString(int count) const
{
   return GetStringForValue("Body Count: ", count);
}

std::string CText::GetGravConstValueString(double val) const
{
   return GetStringForValue("Gavitational Constant: ", val);
}

std::string CText::GetWindowResString(sf::RenderWindow& window) const
{
   sf::Vector2u size = window.getSize();
   std::stringstream ss;
   ss << "Res: " << std::to_string(size.x) << "x" << std::to_string(size.y);
   return ss.str();
}

std::string CText::GetStringForValue(std::string text, int value) const
{
   std::stringstream ss;
   ss << text << std::to_string(value);
   return ss.str();
}

std::string CText::GetStringForValue(std::string text, double value) const
{
   std::stringstream ss;
   ss << text << std::to_string(value);
   return ss.str();
}

std::string CText::AddNewline() const
{
   return "\n";
}
