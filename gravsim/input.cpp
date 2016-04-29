#include "input.h"

CInput::CInput()
{
}

CInput::~CInput()
{
}

void CInput::Initialise()
{

   for (int i = 0; i < 256; ++i)
   {
      m_keys[i] = false;
   }
}

void CInput::KeyDown(unsigned int input)
{
   m_keys[input] = true;
}

void CInput::KeyUp(unsigned int input)
{
   m_keys[input] = false;
}

bool CInput::IsKeyDown(unsigned int key)
{
   return m_keys[key];
}
