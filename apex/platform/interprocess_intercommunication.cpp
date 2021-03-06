#include "framework.h"
#include "apex/const/method.h"


interprocess_intercommunication::interprocess_intercommunication(const string & strApp) :
   m_strApp(strApp)
{

   m_iTaskSeed = 0;

   m_id = "::interprocess_intercommunication";

   defer_create_mutex();

#ifdef _UWP

   m_idApp = strApp;

#else

   m_idApp = (::i64) ::get_current_process_id();

#endif

}


interprocess_intercommunication::~interprocess_intercommunication()
{


}


::estatus interprocess_intercommunication::initialize(::layered * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   run_property("on_create");

   call_routine(CREATE_ROUTINE);

   estatus = __construct_new(m_prx);

   if (!estatus)
   {

      return estatus;

   }

   int iPid = Context.os().get_pid();

   //defer_add_module(Context.file().module(), iPid);

//      ::file::path path;
//
//#ifndef _UWP
//
//      path = module_path_from_pid(iPid);
//
//#endif
//
//      defer_add_module(path, iPid);

   m_prx->m_preceiver = this;

   string strKey = key(m_strApp, iPid);

   if (!m_prx->create(strKey))
   {

      __throw(::resource_exception());

   }



   return estatus;

}


void interprocess_intercommunication::finalize()
{

   ::object::finalize();

   if(m_prx)
   {

      m_prx->finalize();

   }

}



bool interprocess_intercommunication::start(const string & strApp)
{

   sync_lock sl1(mutex());

   auto & pmutex = m_mapAppMutex[strApp];

   if(pmutex.is_null())
   {

      pmutex = __new(::mutex());

   }

   sl1.unlock();

   sync_lock sl(pmutex);

   auto idaPid = get_pid(strApp);

   if(idaPid.get_count() > 0)
   {

      return true;

   }

   ::apex::app_launcher launcher(process_platform_dir_name2(), strApp);

   id idPid = -1;

   {

      auto ida = get_pid(strApp);

      if(ida.is_empty())
      {

         launcher.start();

         int iStep = 0;

         int iSubStep;

         while(iStep < 8 && ::thread_get_run())
         {

            iStep++;

            ida = get_pid(strApp);

            if(ida.has_element())
            {

               goto started;

            }

            for(iSubStep = 0; (iSubStep < (iStep + 1) * 10) && ::thread_get_run(); iSubStep++)
            {

               millis_sleep(100);

            }

         }

         return false;

      }

started:

      idPid = ida[0];

   }

   string strKey = strApp + ":" + __str(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __new(::interprocess_communication::tx);

   }

   return m_txmap[strKey]->open(key(strApp,idPid));

}


bool interprocess_intercommunication::connect(const string & strApp, const ::id & idPid)
{

   string strKey = strApp + ":" + __str(idPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __new(::interprocess_communication::tx);

   }

   if(m_txmap[strKey]->is_tx_ok())
   {

      return true;

   }
   else
   {

      return m_txmap[strKey]->open(key(strApp, idPid));

   }

}


::interprocess_communication::tx & interprocess_intercommunication::tx(const string & strApp, const ::id & iPid)
{

   string strKey = strApp + ":" + __str(iPid);

   if(m_txmap[strKey].is_null())
   {

      m_txmap[strKey] = __new(::interprocess_communication::tx);

   }

   if(!m_txmap[strKey]->is_tx_ok())
   {

      connect(strApp, iPid);

   }

   return *m_txmap[strKey];

}


string interprocess_intercommunication::key(const string &strApp, const ::id & idPid)
{

   string strKey;

#ifdef WINDOWS

#ifdef _UWP

   string strAppId(strApp);

   strAppId.replace("\\","-");

   strAppId.replace("/","-");

   strAppId.replace("-","-");

   strKey = strAppId;

#else

   strKey = "::ca2::account::ccwarehouse::" + strApp + ":" + __str(idPid);

#endif

#else

#ifdef LINUX

   strKey = ::dir::system() / "interprocess_intercommunication" / strApp / __str(idPid);

#elif defined(__APPLE__)

   string strAppId(strApp);

   strAppId.replace("\\","-");

   strAppId.replace("/","-");

   strAppId.replace("-","-");

   strKey = "apex-" + strAppId;

#ifdef MACOS

   strKey += "/" + __str(idPid.i32());

#endif

#else

   strKey = ::dir::system() / "interprocess_intercommunication" / strApp / __str(idPid);


#endif

#endif

   return strKey;

}


string interprocess_intercommunication::str_from_va(const var_array & vara)
{

   memory_stream stream;

   stream << vara;

   return stream->get_primitive_memory()->to_hex();

}


void interprocess_intercommunication::on_interprocess_receive(::interprocess_communication::rx * prx, const char * pszMessage)
{

   string str(pszMessage);

   INFO("::interprocess_intercommunication::on_receive %s", pszMessage);

   if(!::str::begins_eat(str, "call "))
   {

      return;

   }

   ::i64 iCall = ::str::consume_natural(str);

   if(!::str::begins_eat(str, " from "))
   {

      return;

   }

   string strFrom = ::str::consume_non_spaces(str);

   string strAppFrom = ::str::token(strFrom, ":");

   if(strAppFrom.is_empty())
   {

      return;

   }

   ::id idPidFrom = strFrom;

   if(idPidFrom.is_empty() || (idPidFrom.is_integer() && idPidFrom.i64() == 0))
   {

      return;

   }

   strsize iFind = str.find(":");

   string str1;

   string strObject;

   string strMember;

   string_array stra;

   var_array vara;

   if(iFind >= 0 && iFind <= 3)
   {

      return;

   }

   if(iFind > 3)
   {

      str1 = str.Left(iFind);

   }
   else
   {

      str1 = str;

   }

   str1.trim();

   strsize iFind2 = str1.find(".");

   if(iFind2 < 0)
   {

      return;

   }

   strObject = str1.Left(iFind2);

   strMember = str1.Mid(iFind2 + 1);

   if(iFind >= 0)
   {

      str1 = str.Mid(iFind + 1);

      str1.trim();

      memory_stream stream;

      stream->get_primitive_memory()->from_hex(str1);

      stream->seek_to_begin();

      stream.set_loading();

      __io_array(stream, vara);

   }

   payload varRet;

   on_interprocess_call(varRet, strObject, strMember, vara);

   if(!strMember.begins_ci("reply."))
   {

      auto pcall = create_call(strAppFrom, strObject, "reply." + strMember);

      pcall->add_arg(iCall);

      pcall->add_arg(varRet);

      pcall->set_timeout(1_min);

      pcall->post(idPidFrom);

   }

}


__pointer(interprocess_task) interprocess_intercommunication::create_task(interprocess_call * pcall, const ::id & idPid)
{

   auto pobjectTask = __new(interprocess_task(pcall, idPid, atomic_increment(&m_iTaskSeed)));

   sync_lock sl(mutex());

   m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   pcall->m_mapTask[pobjectTask->m_iTask] = pobjectTask;

   return pobjectTask;

}


__pointer(interprocess_task) interprocess_intercommunication::get_task(i64 iTask)
{

   sync_lock sl(mutex());

   return m_mapTask[iTask];

}


__pointer(interprocess_call) interprocess_intercommunication::create_call(const string & strApp, const string & strObject, const string & strMember)
{

   return __new(interprocess_call(this, strApp, strObject, strMember));

}


__pointer(interprocess_call) interprocess_intercommunication::create_call(const string & strObject, const string & strMember)
{

   return create_call(m_strApp, strObject, strMember);

}


void interprocess_intercommunication::on_interprocess_call(payload & payload, const string & strObject, const string & strMember, var_array & vara)
{

   if(strObject == "application")
   {

      if(::str::begins_ci(strMember, "reply."))
      {

         ::i64 iTask = vara[0].i64();

         auto pobjectTask = get_task(iTask);

         pobjectTask->m_var = vara[1];

         pobjectTask->m_pevReady->set_event();

      }
      else if(strMember == "on_additional_local_instance")
      {

         payload["continue"] = Application.on_additional_local_instance(payload["handled"], vara[0], vara[1], vara[2]);

      }
      else if (strMember == "on_new_instance")
      {

         on_new_instance(vara[0], vara[1]);

      }

   }

}


void interprocess_intercommunication::on_new_instance(const string & strModule, const ::id & idPid)
{

   defer_add_module(strModule, idPid);

   Application.on_new_instance(strModule, idPid);

}


id_array interprocess_intercommunication::get_pid(const string & strApp)
{

   id_array idaPid;

#if defined(LINUX) || defined(MACOS)


   idaPid = app_get_pid(strApp);


#else

#if defined(_UWP)

   idaPid.add(strApp);

#else

   string_array stra;

   ::file::path pathModule;

   pathModule = ::dir::system() / "interprocess_intercommunication";

   pathModule /= strApp + ".module_list";

   string strModuleList = file_as_string(pathModule);

   stra.add_lines(strModuleList);

repeat:

   if (stra.get_count() > 32)
   {

      stra.remove_at(0, 16);

   }

   string_array stra2;

   int_array iaPid2;

   for (auto & str : stra)
   {

      if (str.has_char())
      {

         string_array a;

         a.explode("|", str);

         if (a.get_size() >= 2)
         {

            stra2.add_unique_ci(a[0]);

            string strPath = module_path_from_pid(ansi_to_i32(a[1]));

            if (strPath.has_char())
            {

               if (strPath.compare_ci(a[0]) == 0)
               {

                  idaPid.add(ansi_to_i32(a[1]));

               }

            }

         }

      }

   }

   if (idaPid.get_count() <= 0 && stra.get_size() > 32)
   {

      goto repeat;

   }
   //for(auto & str : stra2)
   //{

   //   if(str.has_char())
   //   {

   //          iaPid.add_unique(module_path_get_pid(str));
//
   //   }

   //}

#endif
#endif
   return idaPid;

}


void interprocess_intercommunication::defer_add_module(const string & strModule, const ::id & idPid)
{

#ifndef _UWP

   ::file::path pathModule;

   m_straModule.remove_all();

   pathModule = ::dir::system() / "interprocess_intercommunication";

   pathModule /= m_strApp + ".module_list";

   ::file::path pathPid = module_path_from_pid((::u32)idPid.i64());

   string strModuleList = file_as_string(pathModule);

   m_straModule.add_lines(strModuleList);

   string_array stra2;

   int_array iaPid2;

   for (index i = 0; i < m_straModule.get_count();)
   {

      string str = m_straModule[i];

      str.trim();

      bool bOk = false;

      if (str.has_char())
      {

         string_array a;

         a.explode("|", str);

         if (a.get_size() >= 2)
         {

            stra2.add_unique_ci(a[0]);

            string strPath = module_path_from_pid(ansi_to_i32(a[1]));

            if (strPath.has_char())
            {

               if (strPath.compare_ci(a[0]) == 0)
               {

                  bOk = true;

               }

            }

         }

      }

      if (bOk)
      {

         i++;

      }
      else
      {

         m_straModule.remove_at(i);

      }

   }

   string_array straUnique;

   forallref(m_straModule)
   {

      straUnique.add_unique_ci(item);

   }

   m_straModule = straUnique;

   ::file::path pathThisModule = Context.file().module();

   string strItem;

   if (pathPid.has_char())
   {

      strItem = pathPid + "|" + __str(idPid);

   }
   else
   {

      strItem = strModule + "|" + __str(idPid);
   }


   m_straModule.add_unique_ci(strItem);

   strModuleList = m_straModule.implode("\n");

   Context.file().put_contents(pathModule,strModuleList);

#endif

}



