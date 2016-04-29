#ifndef __GRAPHICSCLASS_H__
#define __GRAPHICSCLASS_H__

#include <windows.h>
#include "d3dclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class CGraphics
{
public:
   CGraphics();
   ~CGraphics();

   bool Initialise(int, int, HWND);
   void Shutdown();
   bool Frame();

private:
   D3DClass *m_Direct3D;
   bool Render();
};

#endif