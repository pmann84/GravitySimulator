#include "system.h"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[])
{
   // Initialise variables
   CSystem *system;
   bool result;

   // Create new system object
   system = new CSystem;
   if (!system)
   {
      return 0;
   }

   // Initialise system and run
   result = system->Initialise();
   if (result)
   {
      system->Run();
   }

   // Now shut down and release resources
   system->Shutdown();
   delete system;
   system = nullptr;

   return 0;
}
