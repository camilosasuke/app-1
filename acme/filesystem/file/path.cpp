#include "framework.h"


#ifdef __APPLE__


char * ns_get_executable_path();


#endif


namespace path
{


   ::file::path app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

   }


   ::file::path app_app_admin(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

   }


   ::file::path app_app_nest(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

   }


   ::file::path app_app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

   }




   ::file::path vcredist(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

   }


#ifdef WINDOWS

   
   ::file::path module(HMODULE hmodule)
   {


#if defined(_UWP)

   return "m_app.exe";

#else

      wstring wstr(get_buffer, MAX_PATH * 8);

      ::GetModuleFileNameW(hmodule, wstr, (::u32)wstr.length());

      return solve_relative(string(wstr.release_string_buffer()));

#endif


   }


#else


   ::file::path module()
   {

      char * pszModuleFilePath = nullptr;

#if defined(__APPLE__)

      pszModuleFilePath = ns_get_executable_path();

#else

      pszModuleFilePath = br_find_exe("app");

#endif

      if(pszModuleFilePath == nullptr)
      {

         return "";

      }

      string strModuleFileName(pszModuleFilePath);

      free(pszModuleFilePath);

      return strModuleFileName;

   }


#endif


   ::file::path install_log(string strPlatform, string strConfiguration)
   {

      return dir::install() / ("install-" + strPlatform + ".log");

   }

   CLASS_DECL_ACME string from(string str)
   {

      string strFsSafe;

      for (index i = 0; i < str.length(); i++)
      {

         if (ansi_char_is_alphanumeric(str[i]))
         {

            strFsSafe += str[i];

         }
         else
         {

            strFsSafe += "-" + ::hex::lower_from(str[i]);

         }

      }

      return strFsSafe;

   }


} // namespace path




