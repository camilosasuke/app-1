#include "framework.h"
#include "aura/node/android/_android.h"
#include "_android.h"

#include <sys/file.h>


// gone to ansios_file.cpp/.h
/*

//#include <sys/stat.h>


void fd_ensure_file_size(i32 fd, i64 iSize)
{

   if(ftruncate(fd, iSize) == -1)
      __throw(::exception::exception("fd_ensure_file_size exception"));

}


i64 fd_get_file_size(i32 fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}

*/




CLASS_DECL_CORE void dll_processes(u32_array & dwa, string_array & straProcesses, const char * pszDll)
{



}



::file::path dir::sys_temp()
{

   return ::file::path(getenv("HOME")) /  ".aura" / "time";

}



::file::path dir::home()
{

   //return getenv("HOME");
   return "/data/home";

}


// ::file::path dir::bookmark()
// {

//    return ::dir::localconfig() / "favorites";

// }


bool __node_further_file_is_equal(const ::file::path &, const ::file::path &)
{

   return false;

}





// The lockf() function is not available on Android; we translate to flock().
//#define F_LOCK LOCK_EX
//#define F_ULOCK LOCK_UN
int lockf(int fd, int cmd, off_t ignored_len) 
{
   
   return ::flock(fd, cmd);

}


 CLASS_DECL_CORE bool _os_may_have_alias(const char * psz)
 {

    return true;

 }



//
//extern "C"
//void android_set_cache_dir(const char* pszDir)
//{
//
//   ::aura::system::g_p->m_pathCacheDir = pszDir;
//
//}
//
//extern "C"
//const char* android_get_cache_dir()
//{
//
//   return ::aura::system::g_p->m_pathCacheDir;
//
//}