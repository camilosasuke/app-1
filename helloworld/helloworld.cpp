#include "framework.h"


#ifndef CUBE

#ifdef _UWP
[MTAThread]
#endif
WINBOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::output_debug_string("app_core_helloworld.dll :: initializing!\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::output_debug_string("app_core_helloworld.dll :: terminating!\n");

   }

   return 1;   // ok

}


#endif