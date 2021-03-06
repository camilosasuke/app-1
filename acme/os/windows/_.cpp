﻿#include "framework.h"
#include "acme/node/_node.h"
#include "acme/id.h"
#include <VersionHelpers.h>

#ifndef USE_OS_IMAGE_LOADER

#include "FreeImage/FreeImage.h"

#endif

#undef new
#include "gdiplus.h"
#include <ddeml.h>
#define new ACME_NEW


void __term_threading();
void __term_windowing();

CLASS_DECL_ACME bool is_verbose();


//::acme::system * app_common_prelude(int & iError, ::create * & pmaininitdata, app_core & appcore,  HINSTANCE hinstance = nullptr, HINSTANCE hinstancePrev = nullptr, const char * pszCmdLine = nullptr, int nShowCmd = e_display_normal);
//int app_common_term(int iError, ::acme::system * psystem, app_core & appcore);



CLASS_DECL_ACME i32 __cdecl _memory_type(const void * p);


// typedef int
// (WINAPI * LPFN_ChangeWindowMessageFilter)(
// const ::id & id,
// ::u32 dwFlag);


//LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter = nullptr;


// bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE)
// {

//    auto pthread = ::get_task();

//    if(!pthread)
//    {

//       return false;

//    }

//    HRESULT hr = pthread->m_hresultCoInitialize;

//    if(!pthread->m_bCoInitialize)
//    {

//       pthread->m_bCoInitialize = true;
   
//       if (bMultiThread)
//       {

//          hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

//       }
//       else
//       {

//          hr = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | (bDisableOleDDE ? COINIT_DISABLE_OLE1DDE : 0));

//       }

//       pthread->m_hresultCoInitialize = hr;

//    }

//    if(FAILED(hr))
//    {

//       ::output_debug_string("Failed to ::CoInitializeEx(nullptr, COINIT_MULTITHREADED) at __node_pre_init");

//       return false;

//    }

//    return true;

// }



bool __node_acme_pre_init()
{

   //xxdebug_box("__node_acme_pre_init","box",e_message_box_ok);

   //g_pgdiplusStartupInput     = new Gdiplus::GdiplusStartupInput();

   //g_pgdiplusStartupOutput    = new Gdiplus::GdiplusStartupOutput();

   //g_gdiplusToken             = NULL;

   //g_gdiplusHookToken         = NULL;

   //g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   //Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken,g_pgdiplusStartupInput,g_pgdiplusStartupOutput);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   message_box("Gdiplus Failed to Startup. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

   //statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   //if(statusStartup != Gdiplus::Ok)
   //{

   //   os_message_box(nullptr,"Gdiplus Failed to Hook. ca cannot continue.","Gdiplus Failure",MB_ICONERROR);

   //   return 0;

   //}

// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_Initialise(FALSE);

//    }
//    catch (...)
//    {

//       ::message_box(nullptr, "Failure to initialize FreeImage (::acme::init_core)", "FreeImage_Initialise failure", e_message_box_icon_exclamation);

//       return false;

//    }

// #endif // SMALLCODE



   return true;

}


void windows_registry_init();



bool __node_acme_pos_init()
{

   _set_purecall_handler(_ca2_purecall);

   //HMODULE hmoduleUser32 = ::LoadLibraryW(L"User32");
   //g_pfnChangeWindowMessageFilter = (LPFN_ChangeWindowMessageFilter) ::GetProcAddress(hmoduleUser32, "ChangeWindowMessageFilter");


   windows_registry_init();



   return true;

}


bool __node_acme_pre_term()
{



   return true;

}

bool __node_acme_pos_term()
{


// #ifndef USE_OS_IMAGE_LOADER

//    try
//    {

//       FreeImage_DeInitialise();

//    }
//    catch (...)
//    {

//    }

// #endif // USE_OS_IMAGE_LOADER


   //if (g_pgdiplusStartupOutput != nullptr)
   //{

   //   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);


   //   ::Gdiplus::GdiplusShutdown(g_gdiplusToken);


   //   ::acme::del(g_pgdiplusStartupInput);
   //   ::acme::del(g_pgdiplusStartupOutput);
   //}

   if (is_verbose())
   {

      output_debug_string(L"acme terminating!\n");

   }

   //::CoUninitialize();


   WSACleanup();


   return true;

}






string key_to_char(WPARAM wparam, LPARAM lparam)

{



   unichar wsz[32];

   byte baState[256];

   for(int i = 0; i < 256; i++)
   {
      baState[i] = (byte) GetAsyncKeyState(i);
   }

   if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
   {
      baState[VK_SHIFT] |= 0x80;
   }


   i32 iRet = ToUnicodeEx((::u32) wparam, (::u32) lparam, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));


   if(iRet > 0)
   {

      wsz[iRet] = L'\0';

      string str;

      str = ::str::international::unicode_to_utf8(wsz);

      if((GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0)
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_lower();
         }
         else
         {
            str.make_upper();
         }
      }
      else
      {
         if((GetAsyncKeyState(VK_SHIFT) & 0x80000000) != 0)
         {
            str.make_upper();
         }
         else
         {
            str.make_lower();
         }
      }



      return str;

   }

   return "";

}


//string get_system_error_message(u32 dwError)
//{
//
//   LPWSTR pBuffer;
//
//   HMODULE Hand = nullptr;
//
//   if(!FormatMessageW(
//         FORMAT_MESSAGE_ALLOCATE_BUFFER |
//         FORMAT_MESSAGE_FROM_SYSTEM,
//         nullptr,
//         dwError,
//         0,
//         (LPWSTR) &pBuffer,
//
//         1,
//         nullptr))
//   {
//
//      HMODULE Hand = ::LoadLibraryW(L"NTDLL.DLL");
//
//      if(!FormatMessageW(
//            FORMAT_MESSAGE_ALLOCATE_BUFFER |
//            FORMAT_MESSAGE_FROM_SYSTEM |
//            FORMAT_MESSAGE_FROM_HMODULE,
//            Hand,
//            dwError,
//            0,
//            (LPWSTR) &pBuffer,
//
//            1,
//            nullptr))
//      {
//         FreeLibrary(Hand);
//         return "";
//      }
//
//   }
//
//   string str(pBuffer);
//
//
//   LocalFree(pBuffer);
//
//
//   if(Hand != nullptr)
//   {
//      FreeLibrary(Hand);
//   }
//
//   return str;
//
//}
//
//


/*

// This example checks if the operating system is of "NT-type"
// (which means Windows NT, 2000, XP).
int GetVersion_ex1()
{
   ::u32    dwVersion = GetVersion();
   // Get major and minor version numbers of Windows
   ::u16 loword = LOWORD(dwVersion);
   int lowbyte = LOBYTE(loword);
   int hibyte = HIBYTE(loword);

   debug_print("Window major version = %d and minor version = %d\n", lowbyte, hibyte);

   if (!(dwVersion & 0x80000000))                // Windows NT, 2000, XP
      return 1;
   else         // Windows 95, 98, ME
      return 0;
}


*/





int_bool is_windows_98_or_lesser()
{

//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WIN7) // Windows 7 or greater
#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN) // Windows 7 or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
      return 0;

   return
   osversioninfo.dwPlatformId == VER_PLATFORM_WIN32s
   || (osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS && ((osversioninfo.dwMajorVersion == 4 && osversioninfo.dwMinorVersion <= 10) || osversioninfo.dwMajorVersion < 4));

#endif

}

int_bool is_windows_nt()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindowsXPOrGreater();

#else

   return !(GetVersion() & 0x80000000);

#endif

}


int_bool is_windows_7_or_lower()
{

   return !IsWindows8OrGreater();

}


int_bool is_windows_8_or_greater()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return IsWindows8OrGreater();

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if(!GetVersionEx(&osversioninfo))
      return 0;

   __throw(todo());

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6 && osversioninfo.dwMinorVersion >= 2;

#endif

}


//int_bool is_windows_vista_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsVistaOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 6;
//
//#endif
//
//}


//int_bool is_windows_xp_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && (osversioninfo.dwMajorVersion > 5 || (osversioninfo.dwMajorVersion == 5 && osversioninfo.dwMinorVersion >= 1);
//
//#endif
//
//}
//
//
//int_bool is_windows_2000_or_greater()
//{
//
//#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater
//
//   return IsWindowsXPOrGreater();
//
//#else
//
//   OSVERSIONINFO osversioninfo;
//
//   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//
//   if (!GetVersionEx(&osversioninfo))
//      return 0;
//
//   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion >= 5;
//
//#endif
//
//}


int_bool is_windows_nt_lesser_than_2000()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return FALSE;

#else

   OSVERSIONINFO osversioninfo;

   osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   if (!GetVersionEx(&osversioninfo))
   {

      return 0;

   }

   return osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT && osversioninfo.dwMajorVersion < 5;

#endif

}


int_bool is_windows_native_unicode()
{

#if defined(_WIN32_WINNT) && (_WIN32_WINNT >= _WIN32_WINNT_WINXP) // winxp or greater

   return TRUE;

#else

   static int_bool s_bNativeUnicode = -1;

   if (bNativeUnicode == -1)
   {

      ::u32 dwVersion = GetVersion();

      // get the Windows version.

      ::u32 dwWindowsMajorVersion = (::u32)(LOBYTE(LOWORD(dwVersion)));
      ::u32 dwWindowsMinorVersion = (::u32)(HIBYTE(LOWORD(dwVersion)));

      // get the build number.

      ::u32 dwBuild;

      if (dwVersion < 0x80000000)              // Windows NT
         dwBuild = (::u32)(HIWORD(dwVersion));
      else if (dwWindowsMajorVersion < 4)      // Win32s
         dwBuild = (::u32)(HIWORD(dwVersion) & ~0x8000);
      else                                     // Windows Me/98/95
         dwBuild = 0;

      if (dwVersion < 0x80000000)              // Windows NT
         s_bNativeUnicode = TRUE;
      else if (dwWindowsMajorVersion < 4)      // Win32s
         s_bNativeUnicode = FALSE;
      else                                     // Windows Me/98/95
         s_bNativeUnicode = FALSE;

   }

   return bNativeUnicode;

#endif

}


// __is_valid_atom() returns TRUE if the passed parameter is
// a valid local or global atom.
bool __is_valid_atom(ATOM nAtom)
{
   
   wchar_t sBuffer[256];

   if(GetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {
      
      return TRUE;

   }
   
   DWORD dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return TRUE;

   }

   if(GlobalGetAtomNameW(nAtom,sBuffer,_countof(sBuffer)))
   {

      return TRUE;

   }

   dwError = ::GetLastError();

   if(dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {

      return TRUE;

   }

   return FALSE;

}


// __is_valid_address() returns TRUE if the passed parameter is
// a valid representation of a local or a global atom within a const char *.

bool __is_valid_atom(const char * psz)
{

   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


bool __is_valid_atom(const wchar_t * psz)
{
   
   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));

}


int_bool IsWow64()
{

   int_bool bIsWow64 = FALSE;

   if (!IsWow64Process(GetCurrentProcess(), &bIsWow64))
   {
      return FALSE;
   }

   return bIsWow64 != FALSE;

}


int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege)
{
   
   // do it only once
   static int_bool bEnabled = FALSE;

   if (bEnabled)
   {
      
      return TRUE;

   }

   bEnabled = TRUE;

   HANDLE hToken = 0;

   TOKEN_PRIVILEGES tkp = { 0 };

   // Get a token for this process.
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
   {

      return FALSE;

   }

   // Get the LUID for the privilege.
   if (LookupPrivilegeValue(nullptr, pszPrivilege, &tkp.Privileges[0].Luid))
   {
      
      tkp.PrivilegeCount = 1;  // one privilege to set
      
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // set the privilege for this process.
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)nullptr, 0);

      DWORD dwError = ::GetLastError();

      if (dwError != ERROR_SUCCESS)
      {

         return FALSE;

      }

      return TRUE;

   }

   return FALSE;

}


CLASS_DECL_ACME string get_last_error_string()
{

   DWORD dwError = ::GetLastError();

   return get_error_string(dwError);

}


CLASS_DECL_ACME string get_error_string(DWORD dwError)
{

   WCHAR * pszError;

   FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pszError, 0, nullptr);

   string strError(pszError);

   ::LocalFree(pszError);

   return strError;

}




bool __node_pos_init()
{

   return true;

}


bool __node_pre_term()
{

   return true;

}


bool __node_pos_term()
{

   return true;

}


CLASS_DECL_ACME string executable_get_app_id(HINSTANCE hinstance)
{

   return read_resource_as_string(hinstance, 1, "APPID");

}







int os_get_system_update_poll_time(const ::id & id)
{

   if (id == id_os_dark_mode)
   {

      return 0;

   }
   else if (id == id_os_font_change)
   {

      return 0;

   }
   else if (id == id_font_enumeration)
   {

      return 0;

   }

   return 0;

}


::estatus os_error_to_status(DWORD dwError)
{

   // NT Error codes
   switch (dwError)
   {
   case NO_ERROR:
      return ::success;
   case ERROR_FILE_NOT_FOUND:
      return ::error_file_not_found;
   case ERROR_PATH_NOT_FOUND:
      return ::error_bad_path;
   case ERROR_TOO_MANY_OPEN_FILES:
      return ::error_too_many_open_files;
   case ERROR_ACCESS_DENIED:
      return ::error_file_access_denied;
   case ERROR_INVALID_HANDLE:
      return ::error_file_not_found;
   case ERROR_BAD_FORMAT:
      return ::error_invalid_file;
   case ERROR_INVALID_ACCESS:
      return ::error_file_access_denied;
   case ERROR_INVALID_DRIVE:
      return ::error_bad_path;
   case ERROR_CURRENT_DIRECTORY:
      return ::error_remove_current_dir;
   case ERROR_NOT_SAME_DEVICE:
      return ::error_bad_path;
   case ERROR_NO_MORE_FILES:
      return ::error_file_not_found;
   case ERROR_WRITE_PROTECT:
      return ::error_file_access_denied;
   case ERROR_BAD_UNIT:
      return ::error_hard_io;
   case ERROR_NOT_READY:
      return ::error_hard_io;
   case ERROR_BAD_COMMAND:
      return ::error_hard_io;
   case ERROR_CRC:
      return ::error_hard_io;
   case ERROR_BAD_LENGTH:
      return ::error_bad_seek;
   case ERROR_SEEK:
      return ::error_bad_seek;
   case ERROR_NOT_DOS_DISK:
      return ::error_invalid_file;
   case ERROR_SECTOR_NOT_FOUND:
      return ::error_bad_seek;
   case ERROR_WRITE_FAULT:
      return ::error_file_access_denied;
   case ERROR_READ_FAULT:
      return ::error_bad_seek;
   case ERROR_SHARING_VIOLATION:
      return ::error_file_sharing_violation;
   case ERROR_LOCK_VIOLATION:
      return ::error_file_lock_violation;
   case ERROR_WRONG_DISK:
      return ::error_bad_path;
   case ERROR_SHARING_BUFFER_EXCEEDED:
      return ::error_too_many_open_files;
   case ERROR_HANDLE_EOF:
      return ::error_end_of_file;
   case ERROR_HANDLE_DISK_FULL:
      return ::error_disk_full;
   case ERROR_DUP_NAME:
      return ::error_bad_path;
   case ERROR_BAD_NETPATH:
      return ::error_bad_path;
   case ERROR_NETWORK_BUSY:
      return ::error_file_access_denied;
   case ERROR_DEV_NOT_EXIST:
      return ::error_bad_path;
   case ERROR_ADAP_HDW_ERR:
      return ::error_hard_io;
   case ERROR_BAD_NET_RESP:
      return ::error_file_access_denied;
   case ERROR_UNEXP_NET_ERR:
      return ::error_hard_io;
   case ERROR_BAD_REM_ADAP:
      return ::error_invalid_file;
   case ERROR_NO_SPOOL_SPACE:
      return ::error_directory_full;
   case ERROR_NETNAME_DELETED:
      return ::error_file_access_denied;
   case ERROR_NETWORK_ACCESS_DENIED:
      return ::error_file_access_denied;
   case ERROR_BAD_DEV_TYPE:
      return ::error_invalid_file;
   case ERROR_BAD_NET_NAME:
      return ::error_bad_path;
   case ERROR_TOO_MANY_NAMES:
      return ::error_too_many_open_files;
   case ERROR_SHARING_PAUSED:
      return ::error_bad_path;
   case ERROR_REQ_NOT_ACCEP:
      return ::error_file_access_denied;
   case ERROR_FILE_EXISTS:
      return ::error_file_access_denied;
   case ERROR_CANNOT_MAKE:
      return ::error_file_access_denied;
   case ERROR_ALREADY_ASSIGNED:
      return ::error_bad_path;
   case ERROR_INVALID_PASSWORD:
      return ::error_file_access_denied;
   case ERROR_NET_WRITE_FAULT:
      return ::error_hard_io;
   case ERROR_DISK_CHANGE:
      return ::error_file_not_found;
   case ERROR_DRIVE_LOCKED:
      return ::error_file_lock_violation;
   case ERROR_BUFFER_OVERFLOW:
      return ::error_bad_path;
   case ERROR_DISK_FULL:
      return ::error_disk_full;
   case ERROR_NO_MORE_SEARCH_HANDLES:
      return ::error_too_many_open_files;
   case ERROR_INVALID_TARGET_HANDLE:
      return ::error_invalid_file;
   case ERROR_INVALID_CATEGORY:
      return ::error_hard_io;
   case ERROR_INVALID_NAME:
      return ::error_bad_path;
   case ERROR_INVALID_LEVEL:
      return ::error_bad_path;
   case ERROR_NO_VOLUME_LABEL:
      return ::error_bad_path;
   case ERROR_NEGATIVE_SEEK:
      return ::error_bad_seek;
   case ERROR_SEEK_ON_DEVICE:
      return ::error_bad_seek;
   case ERROR_DIR_NOT_ROOT:
      return ::error_bad_path;
   case ERROR_DIR_NOT_EMPTY:
      return ::error_remove_current_dir;
   case ERROR_LABEL_TOO_LONG:
      return ::error_bad_path;
   case ERROR_BAD_PATHNAME:
      return ::error_bad_path;
   case ERROR_LOCK_FAILED:
      return ::error_file_lock_violation;
   case ERROR_BUSY:
      return ::error_file_access_denied;
   case ERROR_INVALID_ORDINAL:
      return ::error_invalid_file;
   case ERROR_ALREADY_EXISTS:
      return ::error_file_access_denied;
   case ERROR_INVALID_EXE_SIGNATURE:
      return ::error_invalid_file;
   case ERROR_BAD_EXE_FORMAT:
      return ::error_invalid_file;
   case ERROR_FILENAME_EXCED_RANGE:
      return ::error_bad_path;
   case ERROR_META_EXPANSION_TOO_LONG:
      return ::error_bad_path;
   case ERROR_DIRECTORY:
      return ::error_bad_path;
   case ERROR_OPERATION_ABORTED:
      return ::error_hard_io;
   case ERROR_IO_INCOMPLETE:
      return ::error_hard_io;
   case ERROR_IO_PENDING:
      return ::error_hard_io;
   case ERROR_SWAPERROR:
      return ::error_file_access_denied;
   default:
      return ::error_file;
   }
}






