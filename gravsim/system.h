#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "input.h"
#include "graphics.h"

class CSystem
{
public:
   CSystem();
   CSystem(const CSystem&);
   ~CSystem();

   bool Initialise();
   void Run();
   void Shutdown();

   LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:
   bool Frame();
   void InitialiseWindows(int& screenHeight, int& screenWidth);
   void ShutdownWindows();

   LPCWSTR m_applicationName;
   HINSTANCE m_hInstance;
   HWND m_hwnd;

   CInput *m_input;
   CGraphics *m_graphics;
};

static LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);

static CSystem *ApplicationHandle = nullptr;

#endif