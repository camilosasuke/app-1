#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_cache::script_cache()
   {

      defer_create_mutex();

   }


   script_cache::~script_cache()
   {

   }


   ::estatus script_cache::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pmanager = pobjectContext;

      return estatus;

   }


   ds_script * script_cache::create_new_ds_script(const string & strName)
   {

      auto pscript = __create_new< ds_script >();

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      cache(pscript);

      return pscript;

   }


   script * script_cache::get(const char * lpcszName)
   {

      string strName(lpcszName);

#ifdef WINDOWS

      strName.replace("/", "\\");

#endif

      sync_lock sl(mutex());

      auto ppair = m_map.plookup(strName);

      if (::is_set(ppair) 
         && ppair->element2().is_set()
         && ppair->element2()->m_strName == strName)
      {

         return ppair->element2();

      }

      return create_new_ds_script(strName);

   }


   script * script_cache::register_script(const char * lpcszName, script * pscript)
   {

      string strName(lpcszName);

#ifdef WINDOWS
      strName.replace("/", "\\");
#endif

      single_lock sl(mutex(), TRUE);

      strsp(script)::pair * ppair = m_map.plookup(strName);

      if(ppair != nullptr)
      {

         ppair->element2() = pscript;

         return pscript;

      }

      pscript->m_pmanager = m_pmanager;

      pscript->m_strName = strName;

      cache(pscript);

      return pscript;

   }

   __pointer(script_instance) script_cache::create_instance(const char * lpcszName, __pointer(script) & pscript)
   {

      pscript = nullptr;

      if(::str::begins(lpcszName, "netnode://"))
      {
         
         single_lock sl(mutex(), TRUE);

         pscript  = get(lpcszName);

         sl.unlock();

         return pscript->create_instance();

      }

      string strName(lpcszName);
      
      strName = m_pmanager->real_path(lpcszName);
      
      if (strName.is_empty())
      {

         strName = m_pmanager->real_path(string(lpcszName) + ".ds");

      }
      
      strName.replace("\\", "/");

      m_pmanager->include_has_script(strName);

      pscript = get(strName);

      if (::is_null(pscript))
      {

         return nullptr;

      }

      sync_lock slScript(pscript->mutex());

      if(!pscript->m_bNew && pscript->ShouldBuild())
      {

         slScript.unlock();

         pscript = create_new_ds_script(strName);

      }

      return pscript->create_instance();

   }


   void script_cache::cache(script * pscript)
   {

      single_lock sl(mutex(), true);

      m_map.set_at(pscript->m_strName, pscript);

   }


   void script_cache::uncache(script * pscript)
   {

      single_lock sl(mutex(), true);

      m_map.remove_key(pscript->m_strName);

   }


   void script_cache::set_all_out_of_date()
   {
      return;
//   single_lock sl(mutex(), TRUE);
//   __pointer(script) pscript;
//   string strName;
//   POSITION pos = m_map.get_start_position();
//   while(pos != nullptr)
//   {
//      m_map.get_next_assoc(pos, strName, pscript);
//
//      ds_script * pdsscript = dynamic_cast < ds_script * > (pscript.m_p);
//      if(pdsscript != nullptr)
//      {
//         pdsscript->m_bShouldBuild = true;
//      }
//
//   }
   }


   void script_cache::set_out_of_date(string str)
   {

      if (str.is_empty())
      {

         return;

      }

      ::file::path pathChanged = str;

      single_lock sl(mutex(), TRUE);

      for (auto & pair : m_map)
      {

         __pointer(ds_script) pdsscript = pair.element2();

         if (pdsscript != nullptr)
         {

            ::file::path path = pdsscript->m_strSourcePath;

            if (path.ends_ci(pathChanged))
            {

               pdsscript->m_bShouldBuild = true;

            }

         }

      }

   }

} // namespace dynamic_source


