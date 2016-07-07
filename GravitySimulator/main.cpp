#include "MainWindow.h"

int main()
{
   CMainWindow window;
   if(!window.Init())
   {
      return 1;
   }

   if(!window.Run())
   {
      return 1;
   };
   return 0;
}
