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
   int fontSize = 12;
   sf::Text screenText;
   screenText.setFont(Font());
   screenText.setCharacterSize(fontSize);

   std::string windowStr = GetFrameRateString(fps);
   windowStr += AddNewline();
   windowStr += GetWindowResString(window);
   windowStr += AddNewline();
   windowStr += GetBodyCountString(sim.BodyCount());
   windowStr += AddNewline();
   windowStr += GetGravConstValueString(sim.G());
   windowStr += AddNewline();
   windowStr += GetSimTotalEnergyString(sim.Energy());

   screenText.setString(windowStr);
   window.draw(screenText);

   DrawInstructionsText(window);
   return true;
}

void CText::DrawInstructionsText(sf::RenderWindow& window)
{
   int fontSize = 12;
   sf::Text screenText;
   screenText.setFont(Font());
   screenText.setCharacterSize(fontSize);

   int instructionLines;
   std::string windowStr = GetInstructionsString(instructionLines);

   screenText.setString(windowStr);
   screenText.setPosition(0,static_cast<float>(window.getSize().y - (instructionLines + 1) * fontSize));
   window.draw(screenText);
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

std::string CText::GetSimTotalEnergyString(double val) const
{
   return GetStringForValue("Total Energy: ", val);
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

std::string CText::GetInstructionsString(int& numLines)
{
   numLines = 4;
   return "Controls\nR: Reset Simulation\nSpace: Pause/Unpause Simulation\nV: Toggle Draw Velocity Vectors";
}
