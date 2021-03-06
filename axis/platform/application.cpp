#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "axis/user/_user.h"
#endif
#include "aura/id.h"


namespace axis
{


   application::application(const char * pszAppId) :
      ::aura::application(pszAppId)
   {

      m_paxisapplication = this;

      m_bInitializeDataCentral = true;

   }


   application::~application()
   {

      m_paxisapplication = nullptr;

   }



   ::estatus     application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::aura::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void application::assert_valid() const
   {

      thread::assert_valid();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      thread::dump(dumpcontext);

//#ifdef WINDOWS
//
//      dumpcontext << "m_hinstance = " << (void *)m_hinstance;
//
//#endif

      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_bHelpMode = " << m_strAppName;

      dumpcontext << "\n";

   }


   string application::__get_text(string str)
   {

      if (!m_puserlanguagemap)
      {

         return str;

      }

      return m_puserlanguagemap->__get_text(str);

   }


   //::user::style* application::get_user_style() const
   //{

   //   if (m_psessionContext)
   //   {

   //      return m_psessionContext->user()->get_user_style();

   //   }

   //   return nullptr;

   //}


   //string application::dialog_box(const char * pszMatter, property_set & propertyset)
   //{

   //   throw_todo();

   //   return "";

   //}


   bool application::app_data_set(const ::id & id, stream & os)
   {

      return false;

   }


   bool application::app_data_get(const ::id & id, stream & is)
   {

      return false;

   }


   bool application::app_data_set(const ::id & id, ::object & obj)
   {

      return false;

   }


   bool application::app_data_get(const ::id & id, ::object & obj)
   {

      return false;

   }





   ::file::path command_find_path(const char * pszCommand)
   {

#ifdef _UWP

      return "";

#else

      string strPath = getenv("PATH");

      string_array straPath;

      straPath.explode(":", strPath);

      for (auto & str : straPath)
      {

         ::file::path path;

         path = str;

         path /= pszCommand;

         if (file_exists(path))
         {

            return path;

         }

      }

      return pszCommand;

#endif

   }
#ifdef WINDOWS_DESKTOP


   class open_browser_enum
   {
   public:

      string                           m_strWindowEnd;
      string                           m_strTopic;
      string                           m_strCounterTopic;
      oswindow                         m_hwnd;
      comparable_array < oswindow >    m_hwndaTopic;
      comparable_array < oswindow >    m_hwndaCounterTopic;

   };


   int_bool CALLBACK enum_proc(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strWindowEnd))
      {

         penum->m_hwnd = hwnd;

         return FALSE;

      }

      return TRUE;

   }


   int_bool CALLBACK enum_proc_ff_topic(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd);

      if (::str::ends_ci(str, penum->m_strTopic))
      {

         penum->m_hwndaTopic.add(hwnd);

      }

      return TRUE;

   }

   int_bool CALLBACK enum_proc_ff_counter_topic(oswindow hwnd, LPARAM lparam)

   {

      open_browser_enum * penum = (open_browser_enum *)lparam;


      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strCounterTopic))
      {

         penum->m_hwndaCounterTopic.add(hwnd);

      }

      return TRUE;

   }

#endif











   //void application::DoWaitCursor(i32 nCode) // 0 => restore, 1=> begin, -1=> end
   //{

   //   UNREFERENCED_PARAMETER(nCode);

   //}


//   void application::ShowWaitCursor(bool bShow)
//   {
//
//      if (m_pappimpl.is_null())
//         return;
//
//      m_pappimpl->ShowWaitCursor(bShow);
//
//
//   }
//
//

//   string CLASS_DECL_AXIS application::get_cred(const string & strRequestUrl, const ::rect & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
// {

//  __throw(not_implemented());

//}






   ::estatus     application::main()
   {

      INFO("aura::application::main");

      try
      {

         m_bReady = true;

         m_estatus = on_run();

//         if(m_iErrorCode != 0)
//         {
//
//            dappy(string(typeid(*this).name()) + " : on_run failure : " + __str(m_iErrorCode));
//
//            ::output_debug_string("application::main on_run termination failure\n");
//
//         }

      }
      catch (::exception_pointer pe)
      {

         if (!handle_exception(pe))
         {


         }

      }
      catch (...)
      {

         //dappy(string(typeid(*this).name()) + " : on_run general exception");

      }

      return m_estatus;

   }


   ::estatus application::init_instance()
   {

      auto estatus = ::aura::application::init_instance();

      if (!estatus)
      {

         return estatus;

      }



         string str;
         // if system locale has changed (compared to last recorded one by aura)
         // use the system locale
         if (data_get({ "system_locale", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_locale())
               {

                  try
                  {

                     data_set({ "system_locale", true }, get_locale());

                     data_set({ "locale", true }, get_locale());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_locale", true }, get_locale());

         }

         if (value("locale").get_count() > 0)
         {

            str = value("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (value("lang").get_count() > 0)
         {

            str = value("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::source_database);

            }

         }
         // if system schema has changed (compared to last recorded one by aura)
         // use the system schema
         if (data_get({ "system_schema", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_schema())
               {

                  try
                  {

                     data_set({ "system_schema", true }, get_schema());

                     data_set({ "schema", true }, get_schema());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_schema", true }, get_schema());

         }

         if (value("schema").get_count() > 0)
         {

            str = value("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::source_database);

            }

         }

         data_pulse_change({ "ca2.savings", true }, nullptr);

         System.appa_load_string_table();


         // if system locale has changed (compared to last recorded one by aura)
         // use the system locale
         if (data_get({ "system_locale", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_locale())
               {

                  try
                  {

                     data_set({ "system_locale", true }, get_locale());

                     data_set({ "locale", true }, get_locale());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_locale", true }, get_locale());

         }

         if (value("locale").get_count() > 0)
         {

            str = value("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (value("lang").get_count() > 0)
         {

            str = value("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::source_database);

            }

         }
         // if system schema has changed (compared to last recorded one by aura)
         // use the system schema
         if (data_get({ "system_schema", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_schema())
               {

                  try
                  {

                     data_set({ "system_schema", true }, get_schema());

                     data_set({ "schema", true }, get_schema());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_schema", true }, get_schema());

         }

         if (value("schema").get_count() > 0)
         {

            str = value("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::source_database);

            }

         }

         data_pulse_change({ "ca2.savings", true }, nullptr);

         System.appa_load_string_table();

      return true;

   }


   ::estatus application::application_pre_run()
   {

      auto estatus = ::aura::application::application_pre_run();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   bool application::InitApplication()
   {

      auto bOk = ::aura::application::InitApplication();

      if (!bOk)
      {

         return false;

      }

      return true;

   }



   ::estatus application::os_native_bergedge_start()
   {

      return ::aura::application::os_native_bergedge_start();

   }


   ::estatus     application::run()
   {

      return ::aura::application::run();

   }














   ::estatus application::process_init()
   {

      auto estatus = ::aura::application::process_init();

      if (!estatus)
      {

         return estatus;

      }

      //string_array stra;

      //stra.explode("/", m_strAppId);

      //m_strRoot = stra[0];

      //m_strDomain = stra.slice(1).implode("/");

      //add_matter_locator(this);


      //if (is_system() || is_session())
      //{

      //   on_update_matter_locator();

      //}
      //else
      //{


      //}

//      if (!m_bAppHasInstallerChangedProtected)
//      {
//
//#ifdef _UWP
//
//         set_has_installer(false);
//
//#else
//
//         //if (System.m_pappcore == nullptr)
//         //{
//
//         //   set_has_installer(false);
//
//         //}
//         //else
//         {
//
//            set_has_installer(!System.has_apex_application_factory());
//
//         }
//
//#endif
//
//      }

      //auto estatus = initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ////if (m_bAuraProcessInitialize)
      ////{

      ////   return m_bAuraProcessInitializeResult;

      ////}

      INFO("axis::application::process_init");

      //m_bAuraProcessInitialize = true;

      //m_bAuraProcessInitializeResult = false;

      ////if (!is_system())
      //{

      //   if (get_context_system() != nullptr)
      //   {

      //      m_bThreadToolsForIncreasedFps = System.m_bThreadToolsForIncreasedFps;

      //   }

      //}



      ////if (!__construct(m_spdir))
      ////{

      ////   return false;

      ////}

      ////if (!__construct(m_spfile))
      ////{

      ////   return false;

      ////}

      //if (::get_task() == nullptr)
      //{

      //   ::set_thread(dynamic_cast <thread *> (this));

      //}


      create_factory < ::database::field_array >();
      create_factory < ::database::row >();
      create_factory < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFO("axis::application::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      if (m_psimpledb.is_null())
      {

         __construct_new(m_psimpledb);

      }

      //if (!::aura::application::process_init())
      //{

      //   FATAL("axis::application::process_init .1");

      //   return false;

      //}


      //m_bAxisProcessInitializeResult = true;

      //INFO("axis::application::process_init success");

      //return true;

     /* estatus = userfs_process_init();

      if(!estatus && estatus != error_not_implemented)
      {

         ERR(".2");

         return false;

      }*/

      INFO("success");

      return true;

   }


   void application::process_term()
   {

      ::aura::application::process_term();

      //try
      //{

      //   impl_process_term();

      //}
      //catch(...)
      //{

      //}

      //try
      //{

      //   ca_process_term();

      //}
      //catch(...)
      //{

      //}

      try
      {

         release_exclusive();

      }
      catch(...)
      {

      }

      //try
      //{

      //   m_phttp->message_receiver_destruct();

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   m_phttp.release();

      //}
      //catch (...)
      //{

      //}

      //m_phandler.release();

//      try
//      {
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }

      try
      {

         if (!is_session() && !is_system())
         {

            if (get_context_system() != nullptr)
            {

               System.request({::command_check_exit});

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         m_stringtable.remove_all();

         m_stringtableStd.remove_all();

      }
      catch(...)
      {

      }

      //m_spfile.release();

      //m_spdir.release();

      //::acme::del(m_pimaging);


      /// commented out the code below
      /// reasoning: better leave to the session the responsability
      /// to do those checks/actions.
//      if (!is_session() && !is_system())
//      {
//
//         try
//         {
//
//            if (psession->appptra().get_count() <= 1)
//            {
//
//               if (System.thread::get_os_data() != nullptr)
//               {
//
//                  ::parallelization::finish(&System);
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }

   }


//   ::estatus application::init_application()
//   {
//
//      //if (m_bAuraInitializeInstance)
//      //{
//
//      //   return m_bAuraInitializeInstanceResult;
//
//      //}
//
//      INFO("aura::application::init_application");
//
//      //m_bAuraInitializeInstance = true;
//
//      //m_bAuraInitializeInstanceResult = false;
//
//      m_millisHeartBeat.Now();
//
//      if (!init1())
//      {
//
//         //dappy(string(typeid(*this).name()) + " : init1 failure : " + __str(m_iErrorCode));
//
//         return false;
//
//      }
//
//      System.install_progress_add_up(); // 2
//
//      //xxdebug_box("init1 ok", "init1 ok", MB_ICONINFORMATION);
//
//      m_millisHeartBeat.Now();
//
//      if (!init2())
//      {
//
//         //dappy(string(typeid(*this).name()) + " : init2 failure : " + __str(m_iErrorCode));
//
//         return false;
//
//      }
//
//      System.install_progress_add_up(); // 3
//
//      //xxdebug_box("init2 ok", "init2 ok", MB_ICONINFORMATION);
//
//      m_millisHeartBeat.Now();
//
//      if (!init3())
//      {
//
//         //dappy(string(typeid(*this).name()) + " : init3 failure : " + __str(m_iErrorCode));
//
//         return false;
//
//      }
//
//      System.install_progress_add_up(); // 4
//
//      //xxdebug_box("init3 ok", "init3 ok", MB_ICONINFORMATION);
//
//      m_millisHeartBeat.Now();
//
//      //dappy(string(typeid(*this).name()) + " : init3 ok : " + __str(m_iErrorCode));
//
//      try
//      {
//
//         if (!init())
//         {
//
//            //dappy(string(typeid(*this).name()) + " : initialize failure : " + __str(m_iErrorCode));
//
//            return false;
//
//         }
//
//      }
//      catch (const char * psz)
//      {
//
//         if (!strcmp(psz, "You have not logged in! Exiting!"))
//         {
//
//            return false;
//
//         }
//
//         return false;
//
//      }
//
//      System.install_progress_add_up(); // 5
//
////      m_bAuraInitializeInstanceResult = true;
//
//      return true;
//
//   }



   ::estatus application::init1()
   {

      ::estatus estatus = ::aura::application::init1();

      if (!estatus)
      {

         return estatus;

      }



      //if (System.value("locale").get_count() > 0)
      //{

      //   strLocale = System.value("locale").stra()[0];

      //}

      //if (System.value("schema").get_count() > 0)
      //{

      //   strSchema = System.value("schema").stra()[0];

      //}

      //if (Application.value("locale").get_count() > 0)
      //{

      //   strLocale = Application.value("locale").stra()[0];

      //}

      //if (Application.value("schema").get_count() > 0)
      //{

      //   strSchema = Application.value("schema").stra()[0];

      //}

      //set_locale(strLocale, ::source_database);

      //set_schema(strSchema, ::source_database);

      //if (!initialize_contextualized_theme())
      //{

      //   FATAL("Failed to initialize_contextualized_theme");

      //   return false;

      //}

      //INFO("start");

      ////if (!::aura::application::init1())
      ////{

      ////   ERR(".1");

      ////   return false;

      ////}

      ////if (!initialize1_experience())
      ////{

      ////   ERR(".2");

      ////   return false;

      ////}

      //m_millisHeartBeat.Now();

      ////estatus = __compose(m_puserfs);

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////if (!userfs_init1())
      ////{

      ////   ERR(".3");

      ////   return false;

      ////}



      ///*if(!m_spuser->init1())
      //return false;
      //if(!m_spuser->init2())
      //return false;*/

      if (m_bInitializeDataCentral)
      {

         ::file::path pathDatabase;

         ::file::path pathFolder = Context.dir().appdata();

         if (is_system())
         {

            pathDatabase = pathFolder / "system.sqlite";

         }
         else if (is_session())
         {

            pathDatabase = pathFolder / "session.sqlite";

         }
         else
         {

            pathDatabase = pathFolder / "app.sqlite";

         }

         //__throw(todo("database"));

         auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

         if (!estatus)
         {

            m_result.add(estatus);

            return false;

         }

         set_data_server(m_psimpledb);

      }


      return ::success;

   }


   void application::term1()
   {

      ::aura::application::term1();

      ////try
      ////{

      ////   impl_term1();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term1();

      //}
      //catch(...)
      //{

      //}

   }

   ::estatus application::init2()
   {

      //if (!impl_init2())
      //{

      //   return false;

      //}

      //if (!ca_init2())
      //{

      //   return false;

      //}



      return true;

   }

   void application::term2()
   {

      ::aura::application::term2();
      ////try
      ////{

      ////   impl_term2();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term2();

      //}
      //catch(...)
      //{

      //}

   }

   ::estatus application::init3()
   {

      string strFolder = m_strAppName;

      strFolder.replace(".", "_");
      strFolder.replace("::", "-");
      strFolder.replace(":", "_");

      m_strRelativeFolder = strFolder;

      //if (!impl_init3())
      //{

      //   return false;

      //}

      //if (!ca_init3())
      //{

      //   return false;

      //}

      return true;

   }


   void application::term3()
   {

      ::aura::application::term3();

      ////try
      ////{

      ////   impl_term3();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term3();

      //}
      //catch(...)
      //{

      //}

   }



   void application::term_application()
   {

      ::aura::application::term_application();

      //try
      //{

      //   m_spobjectUserFs.release();

      //}
      //catch (...)
      //{


      //}

      //m_puserfs = nullptr;

      //__release(m_pexperience);

      //try
      //{

      //   ::aura::application::term_application();

      //}
      //catch (...)
      //{

      //}

      release_exclusive();

      //::apex::application_message signal(::apex::application_message_term_instance);

      //try
      //{

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      try
      {

         if(::is_set(m_pappParent))
         {

            m_pappParent->app_remove(this);

         }

         if(::is_set(get_context_session()))
         {

            get_context_session()->app_remove(this);

         }

         //if(::is_set(get_context_system()))
         //{

         //   System.app_remove(this);

         //}

         //try
         //{

         //   m_pinterprocessintercommunication.release();

         //}
         //catch (...)
         //{

         //}

         try
         {

            term();

         }
         catch(...)
         {


         }

         try
         {

            term3();

         }
         catch(...)
         {


         }

         try
         {

            term2();

         }
         catch(...)
         {


         }

         try
         {

            term1();

         }
         catch(...)
         {


         }


      }
      catch (...)
      {

      }

      if (m_psimpledb.is_set())
      {

         try
         {

            m_psimpledb->finalize();

         }
         catch (...)
         {

            m_result.add(error_failed);

         }

      }

      m_psimpledb.release();

   }


   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }



   //string application::http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   //{

   //   ::exception::throw_interface_only();

   //   return "";

   //}





   //void application::set_locale(const string & pcsz, const ::action_context & context)

   //{

   //   string strLocale(pcsz);


   //   strLocale.trim();

   //   m_strLocale = strLocale;

   //   on_set_locale(m_strLocale, context);

   //}


   //void application::set_schema(const string & pcsz, const ::action_context & context)

   //{

   //   string strSchema(pcsz);


   //   strSchema.trim();

   //   m_strSchema = strSchema;

   //   on_set_schema(m_strSchema, context);

   //}


   //void application::on_set_locale(const string & pcsz, const ::action_context & context)

   //{
   //   UNREFERENCED_PARAMETER(context);
   //   UNREFERENCED_PARAMETER(pcsz);

   //   //System.appa_load_string_table();
   //}


   //void application::on_set_schema(const string & pcsz, const ::action_context & context)

   //{
   //   UNREFERENCED_PARAMETER(context);
   //   UNREFERENCED_PARAMETER(pcsz);

   //   //System.appa_load_string_table();
   //}





   void application::interactive_credentials(::account::credentials * pcredentials)
   {

      auto psession = Session;

      psession->interactive_credentials(pcredentials);

   }


   ::account::user * application::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      if(::is_null(get_context_session()))
      {

         return nullptr;

      }

      auto psession = Session;

      return psession->get_user(pathUrl, bFetch, bInteractive);

   }


   ::account::user * application::interactive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, true);

   }


   ::account::user * application::noninteractive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, false);

   }



   ::simpledb::server * application::simpledb()
   {

      return m_psimpledb;

   }


   ::database::server * application::dataserver()
   {

      return m_psimpledb;

   }


   ::estatus application::verb()
   {

      return true;

   }


   ::estatus application::on_run()
   {

      //try
      //{

      //   ::apex::application_message signal(::apex::application_message_begin);

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      ::thread * pthread = ::get_thread();

      install_message_routing(pthread);

      m_bReady = true;

      try
      {

         string strType = type_name();

         //if(::is_set(m_psystem))
         //{

         //   m_psystem->add_reference(this);

         //}

         //if(::is_set(m_psession))
         //{

         //   m_psession->add_reference(this);

         //}

         if (::is_set(m_pappParent))
         {

            m_pappParent->add_reference(this);

         }

      resume_on_exception:

         try
         {

            m_estatus = run();

         }
         catch (::exception::exception_pointer pe)
         {

            if (handle_exception(pe))
            {

               goto resume_on_exception;

            }

            m_estatus = pe->m_estatus;

         }

      }
      catch (::exception_pointer pe)
      {

      }


      try
      {

         thread * pthread = this;

         if (pthread != nullptr && pthread->m_pevReady != nullptr)
         {

            pthread->m_pevReady->SetEvent();

         }

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

      return m_estatus;

   }





   //::estatus application::application_pre_run()
   //{

   //   return ::aura::application::application_pre_run();

   //}



   //bool application::InitApplication()
   //{

   //   return true;

   //}


   //bool application::do_install()
   //{


   //   if (!::aura::application::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::do_uninstall()
   //{

   //   bool bOk = aura::application::do_uninstall();

   //   return bOk;

   //}


   //bool application::on_install()
   //{

   //   if (!aura::application::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::on_uninstall()
   //{

   //   if (!aura::application::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //::estatus application::os_native_bergedge_start()
   //{

   //   if (!::aura::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::on_request(::create * pcreate)
   //{

   //   aura::application::on_request(pcreate);

   //}


   //::estatus     application::run()
   //{

   //   return ::aura::application::run();

   //}


   //__pointer(::aura::application) application::assert_running(const char * pszAppId)
   //{

   //   __pointer(::aura::application) papp;

   //   papp = psession->m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      __pointer(::create) spcreate(e_create);

   //      papp = psession->start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}


   ::database::key application::calc_data_key()
   {

      return ::database::key("app://" + m_strAppName, is_local_data());

   }




   //::estatus application::init1()
   //{

   //   //if (m_bAxisInitialize1)
   //   //{

   //   //   return m_bAxisInitialize1Result;

   //   //}

   //   //m_bAxisInitialize1 = true;

   //   //m_bAxisInitialize1Result = false;

   //   m_millisHeartBeat.Now();

   //   if (!::aura::application::init1())
   //   {

   //      return false;

   //   }

   //   /*     if (!m_psystem->m_phtml->initialize())
   //        {

   //           return false;

   //        }*/



   //        //m_bAxisInitialize1Result = true;

   //   return true;

   //}


   //::estatus application::init2()
   //{

   //   if (!::aura::application::init2())
   //      return false;

   //   return true;

   //}


   //::estatus application::init3()
   //{

   //   if (!::aura::application::init3())
   //   {

   //      return false;

   //   }

   //   return true;

   //}

//


   ::estatus application::init()
   {

      auto estatus = ::aura::application::init();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//

   //void application::term_application()
   //{


   //   try
   //   {


   //      //destroy_message_queue();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //   release_exclusive();

   //   ::aura::application_message signal(::aura::application_message_term_instance);

   //   try
   //   {

   //      route_message(&signal);

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      try
   //      {

   //         aura::application::term_application();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   if (m_psimpledb.is_set())
   //   {

   //      try
   //      {

   //         m_psimpledb->finalize();

   //      }
   //      catch (...)
   //      {

   //         m_result.add(error_failed);

   //      }

   //   }

   //   m_psimpledb.release();

   //}


   void application::term()
   {

      ::aura::application::term();

   }


   bool application::assert_user_logged_in()
   {

      const char * pszRequestUrl = nullptr;

      string strRequestUrl;

      if (file_as_string(::dir::system() / "config\\system\\ignition_server.txt").has_char())
      {

         strRequestUrl = "https://" + file_as_string(::dir::system() / "config\\system\\ignition_server.txt") + "/api/spaignition";

         pszRequestUrl = strRequestUrl;

      }

      if (get_context_session() == nullptr)
      {

         return false;

      }

      auto psession = Session;

      if (psession->account() == nullptr)
      {

         return false;

      }

      if (interactive_get_user() == nullptr)
      {

         return false;

      }

      return true;

   }


   ::type application::control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype)
   {

      string str(id);

      if (str.begins_ci("still_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("label_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("combo_"))
      {

         econtroltype = ::user::control_type_combo_box;

         return __type(::user::combo_box);

      }
      else if (str.begins_ci("check_") || str.begins_ci("checkbox_"))
      {

         econtroltype = ::user::control_type_check_box;

         return __type(::user::check_box);

      }
      if (str.begins_ci("button_"))
      {

         econtroltype = ::user::control_type_button;

         return __type(::user::button);

      }

      return ::axis::application::control_type_from_id(id, econtroltype);

   }


   ::user::interaction* application::create_menu_interaction()
   {

      return new ::user::button;

   }


} // namespace axis



