#include "framework.h"


#ifdef WINDOWS_DESKTOP

string read_resource_as_string(HINSTANCE hinst, UINT nID, const char * pcszType, strsize iReadAtMostByteCount)
{

   HRSRC hrsrc = ::FindResourceW(hinst, MAKEINTRESOURCEW(nID), wstring(pcszType));


   if (hrsrc == nullptr)
      return "";

   HGLOBAL hres = ::LoadResource(hinst, hrsrc);

   if (hres == nullptr)
      return "";

   u32 dwResSize = ::SizeofResource(hinst, hrsrc);

   string str;
   char * psz = nullptr;

   if (hres != nullptr)
   {

      UINT FAR * pnRes = (UINT FAR *)::LockResource(hres);

      iReadAtMostByteCount = iReadAtMostByteCount < 0 ? dwResSize : MIN(iReadAtMostByteCount, (strsize) dwResSize);

      psz = str.get_string_buffer(iReadAtMostByteCount);

      ::memcpy_dup(psz, pnRes, iReadAtMostByteCount);

      psz[dwResSize] = '\0';

      str.release_string_buffer(iReadAtMostByteCount);

   }

   return str;

}


#endif


