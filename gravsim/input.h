#ifndef __INPUT_H__
#define __INPUT_H__

class CInput
{
public:
   CInput();
   ~CInput();

   void Initialise();

   void KeyDown(unsigned int);
   void KeyUp(unsigned int);

   bool IsKeyDown(unsigned int);

private:
   bool m_keys[256];
};

#endif