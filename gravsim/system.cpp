#include "system.h"

CSystem::CSystem()
{
   m_input = nullptr;
   m_graphics = nullptr;
}

CSystem::CSystem(const CSystem &other)
{
}

CSystem::~CSystem()
{
}

bool CSystem::Initialise()
{
   int screenWidth = 0;
   int screenHeight = 0;
   bool result;

   InitialiseWindows(screenWidth, screenHeight);

   m_input = new CInput;
   if (!m_input)
   {
      return false;
   }

   m_input->Initialise();

   m_graphics = new CGraphics;
   if (!m_graphics)
   {
      return false;
   }

   result = m_graphics->Initialise(screenWidth, screenHeight, m_hwnd);
   if (!result)
   {
      return false;
   }
   return true;
}

void CSystem::Shutdown()
{
   if (m_graphics)
   {
      m_graphics->Shutdown();
      delete m_graphics;
      m_graphics = nullptr;
   }

   if (m_input)
   {
      delete m_input;
      m_input = nullptr;
   }

   ShutdownWindows();
}

LRESULT CSystem::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
   switch (umsg)
   {
      case WM_KEYDOWN:
      {
         m_input->KeyDown(static_cast<unsigned int>(wparam));
         return 0;
      }
      case WM_KEYUP:
      {
         m_input->KeyUp(static_cast<unsigned int>(wparam));
         return 0;
      }
      default:
      {
         return DefWindowProc(hwnd, umsg, wparam, lparam);
      }
   }
}

void CSystem::Run()
{
   MSG msg;
   bool done = false;
   bool result;

   ZeroMemory(&msg, sizeof(MSG));

   while (!done)
   {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      if (msg.message == WM_QUIT)
      {
         done = true;
      }
      else
      {
         result = Frame();
         if (!result)
         {
            done = true;
         }
      }
   }
}

bool CSystem::Frame()
{
   bool result;

   if (m_input->IsKeyDown(VK_ESCAPE))
   {
      return false;
   }

   result = m_graphics->Frame();
   if (!result)
   {
      return false;
   }

   return true;
}

void CSystem::InitialiseWindows(int& screenHeight, int& screenWidth)
{
   WNDCLASSEX wc;
   DEVMODE dmScreenSettings;
   int posX, posY;

   ApplicationHandle = this;

   m_hInstance = GetModuleHandle(nullptr);
   m_applicationName = L"GravSim";

   // Setup window style
   wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
   wc.lpfnWndProc = WndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = m_hInstance;
   wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
   wc.hIconSm = wc.hIcon;
   wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
   wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
   wc.lpszMenuName = nullptr;
   wc.lpszClassName = m_applicationName;
   wc.cbSize = sizeof(WNDCLASSEX);

   // Register window
   RegisterClassEx(&wc);

   // Determine screen res
   screenHeight = GetSystemMetrics(SM_CYSCREEN);
   screenWidth = GetSystemMetrics(SM_CXSCREEN);

   if (FULL_SCREEN)
   {
      memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
      dmScreenSettings.dmSize = sizeof(dmScreenSettings);
      dmScreenSettings.dmPelsHeight = static_cast<unsigned long>(screenHeight);
      dmScreenSettings.dmPelsWidth = static_cast<unsigned long>(screenWidth);
      dmScreenSettings.dmBitsPerPel = 32;
      dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

      ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

      // Set window pos - top left corner
      posX = posY = 0;
   }
   else
   {
      // If windowed then set it to 800x600 resolution.
      screenWidth = 800;
      screenHeight = 600;

      // Place the window in the middle of the screen.
      posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
      posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
   }

   // Create window
   m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, 
                           m_applicationName, 
                           m_applicationName, 
                           WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, 
                           posX, 
                           posY, 
                           screenWidth, 
                           screenHeight, 
                           nullptr,
                           nullptr,
                           m_hInstance, 
                           nullptr);

   // Bring window up on screen and set focus
   ShowWindow(m_hwnd, SW_SHOW);
   SetForegroundWindow(m_hwnd);
   SetFocus(m_hwnd);

   // Hide mouse cursor
   ShowCursor(false);
}

void CSystem::ShutdownWindows()
{
   ShowCursor(true);

   if (FULL_SCREEN)
   {
      ChangeDisplaySettings(nullptr, 0);
   }

   // Remove window
   DestroyWindow(m_hwnd);
   m_hwnd = nullptr;

   // Remove app instance
   UnregisterClass(m_applicationName, m_hInstance);
   m_hInstance = nullptr;

   // Release pointer to class
   ApplicationHandle = nullptr;
}

LRESULT __stdcall WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
   switch (umsg)
   {
      case WM_DESTROY:
      {
         PostQuitMessage(0);
         return 0;
      }
      case WM_CLOSE:
      {
         PostQuitMessage(0);
         return 0;
      }
      // Pass all other messags to the message handler in system class
      default:
      {
         return ApplicationHandle->MessageHandler(hwnd, umsg, wparam, lparam);
      }
   }
}
