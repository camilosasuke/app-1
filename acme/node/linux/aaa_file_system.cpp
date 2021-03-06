#include "framework.h"
#include "_linux.h"


namespace linux
{


   file_system::file_system()
   {

   }


   file_system::~file_system()
   {

   }


   ::estatus file_system::initialize(::matter * pobjectContext)
   {

      auto estatus = ::file_system::initialize(pobjectContext);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus file_system::init_system()
   {

      if(!update_module_path())
      {

         return ::error_failed;

      }

      return ::success;

   }


   ::estatus file_system::update_module_path()
   {

      auto estatus = ::file_system::update_module_path();

      if(!estatus)
      {

         return estatus;

      }

      ::file::path pathAppModule = ::file::app_module();

      m_pathModule = pathAppModule;

      ::file::path pathCa2AppModule = ::path::module();

      m_pathCa2Module = pathCa2AppModule;

      return estatus;

   }


} // namespace linux



