#include "framework.h"
#include "acme/node/windows/_windows.h"
#include "acme/os/windows_common/cotaskptr.h"


namespace windows
{


   CLASS_DECL_ACME::file::path user_appdata_local()
   {

      return shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

   }


} // namespace windows








CLASS_DECL_ACME::file::path get_known_folder(REFKNOWNFOLDERID kfid)
{

   ::file::path str;

   ::cotaskptr < PWSTR > pwszPath;

   HANDLE hToken = nullptr;

   ::OpenProcessToken(::GetCurrentProcess(), TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE, &hToken);

   HRESULT hr = SHGetKnownFolderPath(kfid, 0, hToken, &pwszPath);

   return pwszPath;

}



::file::path dir::bookmark()
{

   return ::dir::localconfig() / "bookmark";

}


::file::path dir::home()
{

   return ::get_known_folder(FOLDERID_Profile);

}


namespace dir
{


   bool _mk(const ::file::path & path)
   {

      if (is(path))
      {

         return true;

      }

      string strName;

      ::file::path pathDir;

      strsize iLastPo = -1;

      ::file::patha stra;

      path.ascendants_path(stra);

      index i = stra.get_upper_bound();

      for (; i >= 0; i--)
      {

         string strDir = stra[i];

         if (is(strDir))
         {

            break;

         }

      }

      if (i < 0)
      {

         return true;

      }

      for (; i < stra.get_count(); i++)
      {

         string strDir = stra[i];

         if (::dir::mkdir(strDir))
         {

         }
         else
         {

            DWORD dwError = ::GetLastError();

            if (dwError == ERROR_ALREADY_EXISTS)
            {

               try
               {

                  file_delete(strDir);

               }
               catch (...)
               {

               }

               string str = stra[i];

               str.trim_right("\\/");

               try
               {

                  file_delete(str);

               }
               catch (...)
               {

               }

               if (::dir::mkdir(stra[i]))
               {

                  continue;

               }
               else
               {

                  dwError = ::GetLastError();

               }

            }

#ifdef WINDOWS_DESKTOP

            WCHAR * pwszError;

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (WCHAR *)&pwszError, 8, nullptr);

            //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);

            ::LocalFree(pwszError);

            //m_isdirmap.set(stra[i], false);

#endif

            return false;

         }

      }

      return true;

   }



} // namespace dir




