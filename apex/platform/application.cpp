#include "framework.h"
#include "apex/message/application.h"
#include "apex/id.h"
#include "acme/platform/version.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/app_core.h"
#include "acme/platform/profiler.h"
#include "apex/compress/zip/_.h"
#ifndef WINDOWS
#include "acme/os/cross/windows/_windows.h"
#endif


#include "apex/node/_node.h"
#include "apex/os/_os.h"

#ifdef WINDOWS_DESKTOP

int windows_desktop1_main(HINSTANCE hInstance, int nCmdShow);



#include "apex/os/windows/_.h"

#endif


extern ::app_core * g_pappcore;


//extern "C"
//{
//
//   typedef void FN_factory_exchange();
//
//   typedef FN_factory_exchange * PFN_factory_exchange;
//
//}

//PFN_factory_exchange g_pfnfactoryDraw2d = nullptr;
//
//
//PFN_factory_exchange get_draw2d_factory_exchange()
//{
//
//   return g_pfnfactoryDraw2d;
//
//}

//
//void set_draw2d_factory_exchange(PFN_factory_exchange pfnfactoryDraw2d)
//{
//
//   g_pfnfactoryDraw2d = pfnfactoryDraw2d;
//
//}



#ifdef WINDOWS_DESKTOP

CLASS_DECL_ACME void windows_install_crash_dump_reporting(const string & strModuleNameWithTheExeExtension);

#endif


#ifdef MACOS
::file::path macos_app_path(string strApp);
//void ns_app_terminate();
// 0x00010000 NSWorkspaceLaunchAsync
// 0x00080000 NSWorkspaceLaunchNewInstance
void ns_launch_app(const char * psz, const char ** argv, int iFlags);
#endif

#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE

//#include "apex/node/ansios/ansios.h"
#include "apex/node/linux/_linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include <pthread.h>

#endif
#define _GNU_SOURCE
//#include <link.h>
#elif defined(__APPLE__)
//#include <dlfcn.h>
#elif defined(ANDROID)

//#include "apex/node/ansios/ansios.h"
#include "apex/node/android/_.h"

//#elif defined(WINDOWS_DESKTOP)

//#include "apex/node/windows/windows_registry.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP)
CLASS_DECL_APEX int ui_open_url(const char * psz);
#endif


//extern void * g_pf1;


namespace apex
{


   application::application(const char * pszAppId) :
      m_strAppId(::is_set(pszAppId) ? pszAppId : "")
   {

      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pcoreapplication = nullptr;

#ifdef LINUX
      m_bSnLauncheeSetup = false;
#endif

      //m_pappParent = nullptr;
      m_bMessageThread = true;
      m_bSimpleMessageLoop = false;
      m_ethreadClose = thread_none;

      //m_puiMainContainer = nullptr;

      m_bRequiresInstallation = false;
      m_bReadStringTable = true;

      //m_puiCurrent = nullptr;

      //m_bInitializeDataCentral = true;

      m_bInitializeDataCentral = false;

      m_bContextTheme = false;



      if(::get_global_application() == nullptr)
      {

         set_global_application(this);

      }

      m_strLocale = "_std";
      m_strSchema = "_std";


      // default value for acid apps
      // (but any acid app can have installer, just machine this flag to true in the derived application class constructor).
      m_bAppHasInstallerProtected = true;
      m_bAppHasInstallerChangedProtected = false;

      m_strHttpUserAgentToken = "ca2";
      m_strHttpUserAgentVersion = "1.0";

      //m_http.set_app(this);

      m_eexclusiveinstance = ExclusiveInstanceNone;

      //m_pevAppBeg = nullptr;
      //m_pevAppEnd = nullptr;

      m_bAgreeExit = true;
      m_bAgreeExitOk = true;
      m_bFranceExit = true;

      m_bLicense = false;

      m_bInterprocessIntercommunication = false;

      //m_pimaging = nullptr;


      //m_phandler = __new(::handler(this));


      //m_bAuraProcessInitialize = false;
      //m_bAuraProcessInitializeResult = false;

      //m_bAuraInitialize1 = false;
      //m_bAuraInitialize1Result = false;

      //m_bAuraInitialize = false;
      //m_bAuraInitializeResult = false;

      //m_bAuraInitializeInstance = false;
      //m_bAuraInitializeInstanceResult = false;

      //create_factory < ::user::user >();
      //create_factory < ::userfs::userfs >();

      //m_pmainpane = nullptr;

      //m_ppaneviewMain = nullptr;

      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      //::add_ref(this);

      srand((u32) ::get_tick());

      m_bService = false;

      m_iResourceId = 8001;

      ::acme::profiler::initialize();

      //m_pdocmanager = nullptr;

      m_eexclusiveinstance = ExclusiveInstanceNone;
      m_strLocale = "_std";
      m_strSchema = "_std";

      m_durationGcomBackgroundUpdate = 30_s;

   }


   ::estatus application::initialize(::layered * pobjectContext)
   {

      auto estatus = ::thread::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      set_context_object(this OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      set_context_app(this);

      set_context(this);

      if (::is_set(m_pappParent))
      {

         set_context_session(m_pappParent->get_context_session());

         //set_context_system(m_pappParent->get_context_system());

      }

      {

#include "build.h"

         m_strBuild = pszBuild;

      }

      if (m_strBuild.is_empty())
      {

         m_strBuild = "(unknown build version)";

      }

      return estatus;

   }


   application::~application()
   {

   }




   application_menu & application::applicationmenu()
   {

      if(m_papplicationmenu.is_null())
      {

         __own(this, m_papplicationmenu, __new(application_menu));

      }

      return *m_papplicationmenu;

   }


   ::file::path application::local_application_path()
   {

      return ::dir::localconfig() / "application" / m_strAppName ;


   }


   ::file::path application::local_application_home_path()
   {

      return local_application_path() / "home";


   }


   void application::application_menu_update()
   {

#ifdef LINUX

      if(System.m_bGtkApp)
      {

         apex_application_set_application_menu(m_papplicationmenu, this);

      }

#endif

   }


   void application::finalize()
   {

      ::application_container::m_applicationa.remove_all();

      __unbind(this, m_puserlanguagemap OBJ_REF_DBG_COMMA_THIS);

      ::apex::context_thread::finalize();

   }


   ::object * application::parent_property_set_holder() const
   {

      return nullptr;

   }


   void application::on_change_theme()
   {


   }


   //string application::get_theme()
   //{

   //   return "lite";

   //}


   //bool application::is_set_finish() const
   //{

   //   return ::thread::is_set_finish() || m_ethreadClose != thread_none;

   //}


   void application::set_has_installer(bool bSet)
   {

      m_bAppHasInstallerProtected = bSet;

      m_bAppHasInstallerChangedProtected = true;

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

   //      return m_psessionContext->get_user_style();

   //   }

   //   return nullptr;

   //}


   //string application::dialog_box(const char * pszMatter, property_set & propertyset)
   //{

   //   throw_todo();

   //   return "";

   //}


   void application::install_message_routing(::channel * pchannel)
   {

      ::thread::install_message_routing(pchannel);

      connect_command("app_exit", &application::_001OnAppExit);
      connect_command("switch_context_theme", &application::_001OnSwitchContextTheme);

   }


   //imaging & application::imaging()
   //{

   //   return *m_pimaging;

   //}


   bool application::enable_application_events(::object * pobject, bool bEnable)
   {

      sync_lock sl(mutex());

      if(bEnable)
      {

         if(pobject == this)
         {

            return true;

         }

         m_objectptraEventHook.add_unique(pobject);

      }
      else
      {

         m_objectptraEventHook.remove(pobject);

      }

      return true;

   }


   string application::get_title()
   {

      if(m_strAppTitle.has_char())
      {

         return m_strAppTitle;

      }

      string_array stra;

      stra.explode("/", m_strAppName);

      string strTitle;

      if(stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if(strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if(m_strAppName.has_char())
      {

         return m_strAppName;

      }

      stra.explode("/", m_strAppId);

      if(stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if(strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if(m_strAppId.has_char())
      {

         return m_strAppId;

      }

      return Context.file().module().title();

   }


   string_array application::get_categories()
   {

      return m_straAppCategory;

   }


   ::file::path application::get_app_localconfig_folder()
   {

      ::file::path pathFolder = ::dir::localconfig() / m_strAppName;

      return pathFolder;

   }


   ::handle::ini application::get_ini()
   {

      ::handle::ini ini;

      auto pathFolder = get_app_localconfig_folder();

      auto preader = Context.file().get_reader(pathFolder / "this.ini");

      if (preader)
      {

         string str;

         preader->full_read_string(str);

         ini.parse_ini(str);

      }

      return ini;

   }


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


   ::estatus     application::do_request(::create * pcreate)
   {

      return ::thread::do_request(pcreate);

   }


   ::estatus application::call_request(::create * pcreate)
   {

      if (pcreate->m_ecommand == ::command_protocol)
      {

         string str = pcreate->m_varFile;

            // apex commented
            //__throw(todo("interaction"));

         /*if (!m_pinterprocessintercommunication)
         {

            __pointer(::user::interaction) pinteraction;

            get_frame(pinteraction);

            if (pinteraction == nullptr)
            {

               return error_failed;

            }

            auto papp = pinteraction->get_context_application();

            if (papp == nullptr)
            {

               return error_failed;

            }

            if (papp->m_pinterprocessintercommunication == nullptr)
            {

               return error_failed;

            }

         }*/

         if (::str::begins_eat_ci(str, m_pinterprocessintercommunication->m_prx->m_strBaseChannel))
         {

            if (::str::begins_eat_ci(str, ":///"))
            {

               if (::str::begins_eat_ci(str, "send?message="))
               {

                  m_pinterprocessintercommunication->on_interprocess_receive(m_pinterprocessintercommunication->m_prx, System.url().url_decode(str));

               }
               else if (::str::begins_eat_ci(str, "send?messagebin="))
               {

                  strsize iFind = str.find(',');

                  if (iFind >= 0)
                  {

                     int message = atoi(str.Left(iFind));

                     memory m;

                     System.base64().decode(m, System.url().url_decode(str.Mid(iFind + 1)));

                     m_pinterprocessintercommunication->on_interprocess_receive(m_pinterprocessintercommunication->m_prx, message, m.get_data(), m.get_size());

                  }

               }

            }

         }


      }
      else if (pcreate->m_ecommand == ::command_on_agree_exit)
      {

         m_bAgreeExit = _001OnAgreeExit();

         m_bAgreeExitOk = true;

         return ::success;

      }
      else if (pcreate->m_ecommand == ::command_france_exit)
      {

         _001FranceExit();

         return ::success;

      }
      else
      {

         on_request(pcreate);

      }

      return ::success;

   }


   void application::on_request(::create * pcreate)
   {

      if (is_serviceable())
      {

         ::apex::application::on_service_request(pcreate);

      }
      else
      {

         try
         {

            do_request(pcreate);

         }
         // catch (not_installed * pexception)
         // {

         //    ::exception_pointer esp(pexception);

         //    System.on_run_exception(esp);

         //    __throw(exit_exception(esp->get_context_application(), ::exit_application));

         // }
         catch (::exception_pointer pe)
         {

            handle_exception(pe);

         }

         // Verry Sory for the per request overhead here for the needed information of only first request
         if (::is_set(get_context_system()) && System.m_millisAfterApplicationFirstRequest == 0)
         {

            System.m_millisAfterApplicationFirstRequest.Now(); // cross your fingers that the first recorded is not 0, it will be cleaned up by other requests.

         }

         try
         {

            pcreate->m_pcommandline->m_varQuery.unset("document");

         }
         catch (...)
         {

         }

         //__pointer(::apex::session) pbergedge = pcreate->m_pcommandline->m_varQuery["bergedge_callback"].cast < ::apex::session >();
         // todobergedge
         /*if(pbergedge != nullptr)
         {
         pbergedge->on_app_request_bergedge_callback(this);
         }*/
         pcreate->m_pcommandline->m_eventReady.SetEvent();

      }

   }


   //::estatus application::os_message_box(::user::primitive * puiOwner, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::callback callback)
   //{

   //   return ::os_message_box(puiOwner->get_safe_handle(), pszMessage, pszTitle, emessagebox, callback);

   //}


   //::estatus application::ui_message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
   //{

   //   if (!Session || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box(this, puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //::estatus application::ui_message_box_timeout(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::duration& durationTimeout, ::emessagebox emessagebox, ::callback callback)
   //{

   //   if (!Session || !psession->userex())
   //   {

   //      return ::error_failed;

   //   }

   //   return psession->userex()->ui_message_box_timeout(this, puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);

   //}


   //::estatus application::message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //   if(!estatus)
   //   {

   //      return estatus;

   //   }

   //   return os_message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //::estatus application::message_box_timeout(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, const ::duration & durationTimeout, ::emessagebox emessagebox, ::callback callback)
   //{

   //   auto estatus = ui_message_box_timeout(puiOwner, pszMessage, pszTitle, durationTimeout, emessagebox, callback);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return os_message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);

   //}


   //::estatus application::message_box(const payload & payload)
   //{

   //   __pointer(::user::primitive) puiOwner;

   //   string strMessage;

   //   string strTitle;

   //   u64 uFlags = 0;

   //   ::duration durationTimeout;

   //   ::function_arg function;

   //   if (payload.get_type() != type_propset)
   //   {

   //      strMessage = payload;

   //   }
   //   else
   //   {

   //      puiOwner = payload["owner"].cast < ::user::primitive >();
   //      strMessage = payload["message"];
   //      strTitle = payload["title"];
   //      uFlags = payload["flags"];
   //      durationTimeout = payload["duration"];
   //      function = payload["function_arg"];

   //   }

   //   if (durationTimeout.is_null())
   //   {

   //      return message_box(puiOwner, strMessage, strTitle, (::u32) uFlags, function);

   //   }
   //   else
   //   {

   //      return message_box_timeout(puiOwner, strMessage, strTitle, durationTimeout, (::u32) uFlags, function);

   //   }

   //}


   // lang string
   // load string
   string application::lstr(const ::id & id, string strDefault)
   {

      string str;

      if (!load_string(str, id))
      {

         if (strDefault.has_char())
            return strDefault;

         return "";

      }

      return str;

   }




   void application::on_file_new()
   {

   }


   //string application::load_string(const ::id & id)
   //{
   //   string str;
   //   if (!load_string(str, id))
   //   {
   //      return (const string &)id;
   //   }
   //   return str;
   //}

   //bool application::load_string(string & str, const ::id & id)
   //{
   //   if (!load_cached_string(str, id, true))
   //   {
   //      return false;
   //   }
   //   return true;
   //}

   /*bool application::load_cached_string(string & str, const ::id & id, bool bLoadStringTable)
   {

      ::xml::document doc;

      if (!doc.load(id))
      {

         if (load_cached_string_by_id(str, id, bLoadStringTable))
         {

            return true;

         }

      }

      if (doc.get_name() == "string")
      {

         string strId = doc.attribute("id");

         if (load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            return true;
         }

         str = doc.get_value();

         return true;

      }

      return false;

   }*/


   bool application::load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable)
   {

      string strId(id.str());

      string strTable;

      string strString;

      __pointer(string_to_string) pmap;

      index iFind = 0;

      if ((iFind = strId.find(':')) <= 0)
      {

         strTable = "";

         strString = strId;

      }
      else
      {

         strTable = strId.Mid(0, iFind);

         strString = strId.Mid(iFind + 1);

      }

      sync_lock sl(&m_mutexStr);

      if (m_stringtableStd.lookup(strTable, pmap))
      {

         if (pmap->lookup(strString, str))
         {

            return true;

         }

      }
      else if (m_stringtable.lookup(strTable, pmap))
      {

         if (pmap->lookup(strString, str))
         {

            return true;

         }

      }
      else if (bLoadStringTable)
      {

         sl.unlock();

         load_string_table(strTable, "");

         return load_cached_string_by_id(str, id, false);

      }

      return false;

   }


   //void application::load_string_table(const string & pszApp, const string & pszId)
   //{

   //}




   void application::load_string_table()
   {
      load_string_table("", "");
   }





   //object * application::alloc(::type info)
   //{

   //   return System.alloc(this, info);

   //}


   //object * application::alloc(const  id & idType)
   //{

   //   return System.alloc(this, idType);

   //}


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return false;

   }


   bool application::is_serviceable() const
   {

      return false;

   }


   bool application::is_user_service() const
   {

      bool bIsUserService = true;

      bool bIsService = is_serviceable();

      return bIsUserService && bIsService;

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




   //::file::path application::defer_process_path(::file::path path)
   //{

   //   return System.defer_process_path(path, this);

   //}


   //::file::path application::full_process_path(::file::path path)
   //{

   //   if (!(path & ::file::flag_dont_resolve_alias))
   //   {

   //      path |= ::file::flag_resolve_alias;

   //   }

   //   return System.full_process_path(path, this);

   //}




   //void application::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
   //{

   //   browser(strUrl, "", strProfile, strTarget);

   //}


   //bool application::open_link(string strLink, string strProfile, string strTarget)
   //{

   //   if (is_system())
   //   {

   //      if (strLink.begins_ci("mailto:"))
   //      {

   //         return Context.os().file_open(this, strLink);

   //      }

   //      open_profile_link(strLink, strProfile, strTarget);

   //      return true;

   //   }
   //   else
   //   {

   //      return psession->open_link(strLink, strProfile, strTarget);

   //   }

   //   return false;

   //}


#ifdef WINDOWS


   void application::TermThread(HINSTANCE hInstTerm)
   {

      ::exception::throw_interface_only();

   }


#endif


   bool application::_001OnDDECommand(const char * pcsz)

   {

      ::exception::throw_interface_only();

      return false;

   }



   /*::user::document *  application::_001OpenDocumentFile(payload varFile)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }*/


   //void application::_001OnFileNew(::message::message * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //}


//bool application::update_module_paths()
//{


//   if(is_system())
//   {

//      if(!m_pimpl->update_module_paths())
//         return false;


//   }

//   return true;


//}





   //void application::_001CloseApplication()
   //{

   //   __throw(todo());

   //}












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

//   string CLASS_DECL_APEX application::get_cred(const string & strRequestUrl, const ::rect & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
// {

//  __throw(not_implemented());

//}




   ::estatus application::get_temp_file_name_template(string & strRet, const char * lpszName, const char * pszExtension, const char * pszTemplate)
   {

      __throw(not_implemented());

      return false;

   }


   ::estatus application::get_temp_file_name(string & strRet, const char * lpszName, const char * pszExtension)
   {

      return get_temp_file_name_template(strRet, lpszName, pszExtension, nullptr);

   }


   ::estatus application::process_exception(::exception_pointer pe)
   {

      return ::thread::process_exception(pe);

   }


   //bool application::final_handle_exception(::exception::exception * pe)
   //{

   //   UNREFERENCED_PARAMETER(pe);

   //   //linux      exit(-1);

   //   if (!is_system())
   //   {

   //      // get_context_application() may be it self, it is ok...
   //      if (System.final_handle_exception(pe))
   //         return true;


   //   }

   //   return false;
   //}


   ::estatus     application::main()
   {

      INFO("apex::application::main");

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


   ::estatus application::init_thread()
   {

      try
      {

         if (!pre_run())
         {

            return false;

         }

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void application::term_thread()
   {

      INFO("apex::application::term_thread");

      m_millisHeartBeat.Now();

      try
      {

         pos_run();

      }
      catch (...)
      {

      }

      ::thread::term_thread();

   }


   ::estatus application::pre_run()
   {

      INFO("apex::application::pre_run");

      try
      {

         m_millisHeartBeat.Now();

         if(!application_pre_run())
         {

            m_bReady = true;

            return false;

         }

         //    if(!check_install())
         //    {

         //       m_bReady = true;

         //       return false;

         //    }

//         if(!is_system() && !is_session())
//         {
//
//            if(!is_installed())
//            {
//
//
//            }
//
//         }

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

         auto estatus = on_before_launching();

         if(!estatus)
         {

            m_bReady = true;

            return estatus;

         }

         m_millisHeartBeat.Now();

         if (!os_native_bergedge_start())
         {

            m_bReady = true;

            return false;

         }

         INFO("apex::application::pre_run success");

         return true;

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

      }
      catch (...)
      {

         INFO("apex::application::pre_run exception.4");

      }

      return false;

   }


//   ::estatus application::on_run()
//   {
//
//      ::estatus     estatus = ::success;
//
//      try
//      {
//
//         ::message::application message(::message::application_begin);
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //thisstart << m_iErrorCode;
//
//      thread * pthread = ::get_task();
//
//      install_message_routing(pthread);
//
//      //thisok << 1 << m_iErrorCode;
//
//      //try
//      //{
//
//      m_bReady = true;
//
//      //   if (m_pevAppBeg != nullptr)
//      //   {
//
//      //      m_pevAppBeg->SetEvent();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //if(::is_set(get_context_system()))
//      //{
//
//      //   System.add_reference(this);
//
//      //}
//
//      //if(::is_set(get_context_session()))
//      //{
//
//      //   get_context_session()->add_reference(this);
//
//      //}
//
//      //if(::is_set(m_pappParent))
//      //{
//
//      //   m_pappParent->__add_reference(this);
//
//      //}
//
//      if (::is_set(m_pappParent))
//      {
//
//         m_pappParent->add_reference(this);
//
//      }
//
//      try
//      {
//
//resume_on_exception:
//
//         try
//         {
//
//            estatus = run();
//
//         }
//         catch (::exception_pointer pe)
//         {
//
//            if (handle_exception(e))
//            {
//
//               goto resume_on_exception;
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //try
//      //{
//
//      //   if (m_pevAppEnd != nullptr)
//      //   {
//
//      //      m_pevAppEnd->SetEvent();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      return estatus;
//
//   }


   void application::on_pos_run_thread()
   {

      ::thread::on_pos_run_thread();

      sync_lock sl(mutex());

      //try
      //{

      //   for (auto & papp : m_applicationa)
      //   {

      //      try
      //      {

      //         if (papp != this && papp->get_context_application() == this)
      //         {

      //            set_context_object(nullptr);

      //         }

      //         if (is_session())
      //         {

      //            ::apex::session * psessionThis = dynamic_cast <::apex::session *>(this);

      //            if (papp->get_context_session() == psessionThis && papp != this)
      //            {

      //               papp->get_context_session() = nullptr;

      //            }

      //         }

      //         if (is_system())
      //         {

      //            ::apex::system * psystemThis = dynamic_cast <::apex::system *>(this);

      //            if (papp->get_context_system() == psystemThis && papp != this)
      //            {

      //               papp->get_context_system() = nullptr;

      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   void application::pos_run()
   {

      INFO("apex::application::pos_run");

      try
      {

         m_millisHeartBeat.Now();

         application_pos_run();

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

      }
      catch (...)
      {

         INFO("apex::application::pos_run exception.4");

      }

   }


   ::estatus application::init_instance()
   {

      //xxdebug_box("check_exclusive", "check_exclusive", MB_ICONINFORMATION);

      if (m_bInterprocessIntercommunication)
      {

         try
         {

            __own(this, m_pinterprocessintercommunication, create_interprocess_intercommunication() OBJ_REF_DBG_COMMA_THIS_NOTE("::apex::application::init_instance"));

         }
         catch (...)
         {

         }

         if (!m_pinterprocessintercommunication)
         {

            return ::error_failed;

         }

         auto estatus = m_pinterprocessintercommunication->initialize(this);

         if (!estatus)
         {

            return estatus;

         }

      }

      INFO("apex::application::init_application .1");

      bool bHandled = false;

      if (!check_exclusive(bHandled))
      {

         if (!bHandled &&
            (!has_property("install")
            && !has_property("uninstall")))
         {

            duration durationTimeout;

//#ifdef __DEBUG
//
//          durationTimeout = minutes(5);
//
//#else //__DEBUG

            durationTimeout = 5_s;

//#endif //!__DEBUG

            payload payload;

            payload["message"] = "Another instance of \"" + m_strAppName + "\" is already running (and some exclusivity policy is active).";

//          payload["prefix_html"] = "<img src=\"matter://system/exclusive.png\" width=80 height=80 style=\"display:block;\"><br/><br/>";

            message_box_timeout(payload, m_strAppName, durationTimeout, e_message_box_icon_asterisk);

            INFO("apex::application::init_application exit");

            __throw(exit_exception(this));

         }

      }

      INFO("apex::application::init_application .2");

      if (m_pinterprocessintercommunication)
      {

         m_pinterprocessintercommunication->on_new_instance(Context.file().module(), Context.os().get_pid());

      }

      //xxdebug_box("check_exclusive ok", "check_exclusive ok", MB_ICONINFORMATION);

      //if (m_bInitializeDataCentral)
      //{


      //   ::file::path pathDatabase;

      //   ::file::path pathFolder = Context.dir().appdata();

      //   if (is_system())
      //   {

      //      pathDatabase = pathFolder / "system.sqlite";

      //   }
      //   else if (is_session())
      //   {

      //      pathDatabase = pathFolder / "session.sqlite";

      //   }
      //   else
      //   {

      //      pathDatabase = pathFolder / "app.sqlite";

      //   }

      //   //__throw(todo("database"));

      //   //auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

      //   //if (!estatus)
      //   //{

      //   //   m_result.add(estatus);

      //   //   return false;

      //   //}

      //   //set_data_server(m_psimpledb);

      //}

      //m_bAxisInitializeInstanceResult = true;

      INFO("axis::application::init_instance success");

      auto estatus = create_impact_system();

      if (failed(estatus))
      {

         return false;

      }


      if (!is_system() && !is_session())
      {

         string str;
         // if system locale has changed (compared to last recorded one by apex)
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
         // if system schema has changed (compared to last recorded one by apex)
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

         Sys(this).appa_load_string_table();

      }
      if (!is_system() && !is_session())
      {

         string str;
         // if system locale has changed (compared to last recorded one by apex)
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
         // if system schema has changed (compared to last recorded one by apex)
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

         Sys(this).appa_load_string_table();

      }
      return true;

   }


   void application::term_instance()
   {


   }


   void application::TermApplication()
   {


   }


   ::estatus application::application_pre_run()
   {

      INFO("apex::application::application_pre_run");

#ifdef WINDOWS_DESKTOP

      MESSAGE msg;

      // Create Windows Message Queue
      ::PeekMessageA(&msg, nullptr, 0, 0xffff, 0);

      if (!is_system() && is_true("SessionSynchronizedInput"))
      {

         ::AttachThreadInput(GetCurrentThreadId(), (u32)System.get_ithread(), TRUE);

      }

#endif

      m_millisHeartBeat.Now();

      try
      {

         if (!InitApplication())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         //thisexc << 1 << m_iErrorCode;

         ::acme::del(pe);

         return false;

      }
      catch (...)
      {

         //thisexcall << 1 << m_iErrorCode;

         return false;

      }

      m_millisHeartBeat.Now();

      try
      {

         if (!process_init())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         ::acme::del(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      System.install_progress_add_up();

      m_millisHeartBeat.Now();

      try
      {

         if (!init_application())
         {

            return false;

         }

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      m_millisHeartBeat.Now();

      try
      {

         //if (!is_system() && !is_session())
         {

            if (System.is_true("uninstall"))
            {

               do_uninstall();

               return false;

            }
            else if (System.is_true("install"))
            {

               do_install();

               return false;

            }

         }

         if (!init_instance())
         {

            return false;

         }

         on_update_matter_locator();

      }
      catch (exit_exception * pexception)
      {

         __rethrow(pexception);

      }
      catch(::exception::exception * pexception)
      {

         ::exception_pointer esp(pexception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void application::application_pos_run()
   {

      try
      {

         //if (!is_installing() && !is_unstalling())
         {

            term_instance();

         }

      }
      catch (...)
      {

      }

      try
      {

         term_application();

      }
      catch (...)
      {

      }

      m_millisHeartBeat.Now();

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      try
      {

         TermApplication();

      }
      catch (...)
      {

      }



   }

   bool application::InitApplication()
   {

      LoadSysPolicies();

      return true;

   }



   bool application::do_install()
   {

      if (!on_install())
      {

         ::output_debug_string("Failed at on_install : " + m_strAppId + "\n\n");

         System.m_result.add(error_failed);

         return false;

      }

      string strBuild = m_strBuild;

      string strAppId = m_strAppId;

      //xxdebug_box("on_install1", strAppId, 0);

      system_add_app_install(strAppId, strBuild);


      return true;

   }


   ::estatus application::on_before_launching()
   {

      string strLicense = get_license_id();

      //payload & varTopicQuey = System.m_varTopicQuery;

      bool bHasInstall = System.is_true("install");

      bool bHasUninstall = System.is_true("uninstall");

      if (!(bHasInstall || bHasUninstall)
            && m_bLicense
            && strLicense.has_char())
      {

         if (!assert_user_logged_in())
         {
            return false;
         }

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.

         i32 iRetry = 1;

         auto psession = Session;

retry_license:

         iRetry--;

         if (!psession->is_licensed(strLicense))
         {

            if (iRetry > 0)
               goto retry_license;

            return false;

         }

      }

      INFO("initial_check_directrix : ok (%s)%s\n\n", typeid(*this).name(), m_strAppId.c_str());

      return true;

   }



   bool application::do_uninstall()
   {

      if (!on_uninstall())
      {

         return false;

//         System.install().remove_spa_start(m_strAppId);

      }

      return true;

   }




   bool application::on_install()
   {

      if (is_serviceable())
      {

         if (!init_service())
         {

            return false;

         }

         os_start_service();

      }
      else
      {

#ifdef WINDOWS_DESKTOP

         windows_install_crash_dump_reporting(Context.file().module().name());

#endif

      }
      return true;

   }


   bool application::on_uninstall()
   {

      //bool bOk = axis::application::on_uninstall();

      bool bOk = true;


      if (is_serviceable())
      {

         if (!os_remove_service())
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool application::system_add_app_install(const char * pszId, const char * pszBuild)
   {

      // cool install

      string strBuild(pszBuild);

      if (strBuild.is_empty())
      {

         strBuild = "0000-00-00 00:00:00";

      }

      sync_lock sl(System.m_spmutexSystemAppData);

      string strId(pszId);
      string strSystemLocale = System.m_strLocale;
      string strSystemSchema = System.m_strSchema;
      string_array straLocale;
      string_array straSchema;

      straLocale = value("locale");
      straSchema = value("schema");

      ::file::path pathExe = ::file::app_module();

      straLocale.insert_at(0, strSystemLocale);
      straSchema.insert_at(0, strSystemSchema);
      straLocale.insert_at(0, "_std");
      straSchema.insert_at(0, "_std");


      for (index i = 0; i < straLocale.get_count() && i < straSchema.get_count(); i++)
      {

         string strLocale = straLocale[i];

         string strSchema = straSchema[i];

         set_application_installed(pathExe, strId, strBuild, System.get_system_platform(), System.get_system_configuration(), strLocale, strSchema);

      }

      //System.install().remove_spa_start(strId);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, m_strSchema);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, strSystemSchema);
      //System.install().add_app_install(strId, strBuild, m_strLocale, m_strSchema);

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], m_strSchema);

      //}

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, m_strLocale, straSchema[iSchema]);

      //}

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //   {

      //      System.install().add_app_install(strId, strBuild, straLocale[iLocale], straSchema[iSchema]);

      //   }

      //}

      //System.install().add_app_install(strId, strBuild, strSystemLocale, "");
      //System.install().add_app_install(strId, strBuild, m_strLocale, "");

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], "");

      //}

      //System.install().add_app_install(strId, strBuild, "", m_strSchema);
      //System.install().add_app_install(strId, strBuild, "", strSystemSchema);

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, "", straSchema[iSchema]);

      //}

      //System.install().add_app_install(strId, strBuild, "", "");

      return true;

   }


   ::estatus application::os_native_bergedge_start()
   {

      return true;

   }


   ::estatus     application::run()
   {

      //if (is_system())
      //{



      //}

      return ::thread::run();

   }


   bool application::safe_is_running()
   {

      bool bRunning = false;

      try
      {

         if (is_running())
         {

            bRunning = true;

         }

      }
      catch (...)
      {

         bRunning = false;

      }


      return bRunning;

   }


   service_base* application::get_service()
   {

      return m_pservice;

   }


   service_base* application::allocate_new_service()
   {

      return nullptr;

   }


   ::estatus application::init_service()
   {

      if (!is_serviceable())
      {

         __throw(::exception::exception(error_unsupported_function));

      }

      if (m_pservice)
      {

         return false;

      }

      __own(this, m_pservice, allocate_new_service() OBJ_REF_DBG_COMMA_THIS_NOTE("::apex::application::int_service") );

      if (!m_pservice)
      {

         return false;

      }

      auto estatus = m_pservice->initialize(this);

      if (!estatus)
      {

         return false;

      }

      System.m_serviceptra.add(m_pservice);

      return true;

   }

   ::estatus application::os_create_service()
   {

      return Context.os().create_service();

   }


   ::estatus application::os_remove_service()
   {

      return Context.os().remove_service();

   }


   ::estatus application::os_start_service()
   {

      return Context.os().start_service();

   }


   ::estatus application::os_stop_service()
   {

      return Context.os().stop_service();

   }


   void application::on_service_request(::create * pcreate)
   {

      if (!is_serviceable())
      {

         return;

      }

      if (pcreate->m_pcommandline->m_varQuery.has_property("create_service"))
      {

         os_create_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("start_service"))
      {

         os_start_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("stop_service"))
      {

         os_stop_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("remove_service"))
      {

         os_remove_service();

      }
      else if (has_property("service"))
      {

         init_service();

         ::service_base::serve(*m_pservice);

      }
      else if (has_property("run"))
      {

         init_service();

         m_pservice->Start(0);

      }

   }


   //void application::on_update_matter_locator()
   //{



   //}

   ::estatus application::process_init()
   {


      string_array stra;

      stra.explode("/", m_strAppId);

      m_strRoot = stra[0];

      m_strDomain = stra.slice(1).implode("/");

      add_matter_locator(this);


      //if (is_system() || is_session())
      //{

      //   on_update_matter_locator();

      //}
      //else
      //{


      //}

      if (!m_bAppHasInstallerChangedProtected)
      {

#ifdef _UWP

         set_has_installer(false);

#else

         //if (System.m_pappcore == nullptr)
         //{

         //   set_has_installer(false);

         //}
         //else
         {

            set_has_installer(!System.has_apex_application_factory());

         }

#endif

      }

      auto estatus = initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      //if (m_bAuraProcessInitialize)
      //{

      //   return m_bAuraProcessInitializeResult;

      //}

      INFO("apex::application::process_init");

      //m_bAuraProcessInitialize = true;

      //m_bAuraProcessInitializeResult = false;

      //if (!is_system())
      {

         if (get_context_system() != nullptr)
         {

            m_bThreadToolsForIncreasedFps = System.m_bThreadToolsForIncreasedFps;

         }

      }



      //if (!__construct(m_spdir))
      //{

      //   return false;

      //}

      //if (!__construct(m_spfile))
      //{

      //   return false;

      //}

      if (::get_task() == nullptr)
      {

         ::set_task(dynamic_cast <task *> (this));

      }

      if (!notify_process_init())
      {

         FATAL("apex::application::process_init .1");

         return false;

      }

      //if (!impl_process_init())
      //{

      //   FATAL("apex::application::process_init .2");

      //   return false;

      //}

//      m_bAuraProcessInitializeResult = true;

      INFO("apex::application::process_init success");

      //create_factory < ::database::field_array >();
      //create_factory < ::database::row >();
      //create_factory < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFO("axis::application::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      //if (m_psimpledb.is_null())
      //{

      //   __construct_new(m_psimpledb);

      //}

      //if (!::apex::application::process_init())
      //{

      //   FATAL("axis::application::process_init .1");

      //   return false;

      //}


      //m_bAxisProcessInitializeResult = true;

      INFO("axis::application::process_init success");

      //return true;

      estatus = userfs_process_init();

      if(!estatus && estatus != error_not_implemented)
      {

         ERR(".2");

         return false;

      }

      INFO("success");

      return true;

   }


   void application::process_term()
   {


      try
      {

         notify_process_term();

      }
      catch(...)
      {

      }

      try
      {

         release_exclusive();

      }
      catch(...)
      {

      }

      
      try
      {


         if (get_context_system() != nullptr)
         {

            System.request({::command_check_exit});

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

   }


   ::estatus application::init_application()
   {

      INFO("apex::application::init_application");

      m_millisHeartBeat.Now();

      if (!init1())
      {

         //dappy(string(typeid(*this).name()) + " : init1 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 2

      //xxdebug_box("init1 ok", "init1 ok", MB_ICONINFORMATION);

      m_millisHeartBeat.Now();

      if (!init2())
      {

         //dappy(string(typeid(*this).name()) + " : init2 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 3

      //xxdebug_box("init2 ok", "init2 ok", MB_ICONINFORMATION);

      m_millisHeartBeat.Now();

      if (!init3())
      {

         //dappy(string(typeid(*this).name()) + " : init3 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 4

      //xxdebug_box("init3 ok", "init3 ok", MB_ICONINFORMATION);

      m_millisHeartBeat.Now();

      //dappy(string(typeid(*this).name()) + " : init3 ok : " + __str(m_iErrorCode));

      try
      {

         if (!init())
         {

            //dappy(string(typeid(*this).name()) + " : initialize failure : " + __str(m_iErrorCode));

            return false;

         }

      }
      catch (const char * psz)
      {

         if (!strcmp(psz, "You have not logged in! Exiting!"))
         {

            return false;

         }

         return false;

      }

      System.install_progress_add_up(); // 5

//      m_bAuraInitializeInstanceResult = true;

      return true;

   }


   __pointer(::interprocess_intercommunication) application::create_interprocess_intercommunication()
   {

      try
      {

         return __new(::interprocess_intercommunication(m_strAppName));

      }
      catch (...)
      {

         return nullptr;

      }

   }


   ::estatus application::init1()
   {

      ::estatus estatus = __own(this, m_puserlanguagemap, __new(::user::language_map) OBJ_REF_DBG_COMMA_THIS_NOTE("::apex::application::init1") );

      if (!estatus)
      {

         return estatus;

      }

      if (get_context_system())
      {

         if (System.m_pintstringLanguageResourceMap != nullptr)
         {

            m_puserlanguagemap->set_language_resource_map(System.m_pintstringLanguageResourceMap);

         }

      }

      if (System.m_bLocalization)
      {

         string strLang = System.get_user_language();

         if (!m_puserlanguagemap->set_language(this, strLang))
         {

            m_puserlanguagemap->set_default_language(this);

         }

      }

      m_millisHeartBeat.Now();

      if (!notify_init1())
      {

         return ::error_failed;

      }

      if (System.m_bLocalization)
      {

         string strLocale;

         string strSchema;

         if (System.get_user_language().has_char())
         {

            m_strLocale = System.get_user_language();

            m_strSchema = m_strLocale;

         }
         else
         {

#ifdef _UWP

            string_array stra;

            try
            {

               stra.explode("-", ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

            }
            catch (long)
            {

            }

            strLocale = stra[0];

            strSchema = stra[0];

#elif defined(WINDOWS)

            LANGID langid = ::GetUserDefaultLangID();

            string strIso = ::windows::langid_to_iso(langid);

            strLocale = strIso;

            strSchema = strIso;

#endif

         }

         if (strLocale.is_empty())
         {

            strLocale = "_std";

         }

         if (strSchema.is_empty())
         {

            strSchema = strLocale;

         }

         if (System.value("locale").get_count() > 0)
         {

            strLocale = System.value("locale").stra()[0];

         }

         if (System.value("schema").get_count() > 0)
         {

            strSchema = System.value("schema").stra()[0];

         }

         if (Application.value("locale").get_count() > 0)
         {

            strLocale = Application.value("locale").stra()[0];

         }

         if (Application.value("schema").get_count() > 0)
         {

            strSchema = Application.value("schema").stra()[0];

         }

         set_locale(strLocale, ::source_database);

         set_schema(strSchema, ::source_database);

      }

      if (!initialize_contextualized_theme())
      {

         FATAL("Failed to initialize_contextualized_theme");

         return false;

      }

      INFO("start");

      m_millisHeartBeat.Now();

      return ::success;

   }


   void application::term1()
   {

      //try
      //{

      //   impl_term1();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term1();

      }
      catch(...)
      {

      }

   }

   ::estatus application::init2()
   {

      //if (!impl_init2())
      //{

      //   return false;

      //}

      if (!notify_init2())
      {

         return false;

      }



      return true;

   }

   void application::term2()
   {

      //try
      //{

      //   impl_term2();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term2();

      }
      catch(...)
      {

      }

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

      if (!notify_init3())
      {

         return false;

      }

      return true;

   }


   void application::term3()
   {

      //try
      //{

      //   impl_term3();

      //}
      //catch (...)
      //{

      //}

      try
      {

         notify_term3();

      }
      catch(...)
      {

      }

   }


   void application::term_application()
   {


      try
      {

         close(::apex::e_end_app);

      }
      catch (...)
      {

      }

      release_exclusive();

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

         try
         {

            __unbind(this, m_pinterprocessintercommunication OBJ_REF_DBG_COMMA_THIS);

         }
         catch (...)
         {

         }

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


   }




   __pointer(::acme::exclusive) application::get_exclusive(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      auto & pexclusive = m_mapExclusive[strId];

      if(!pexclusive)
      {

         auto pexclusiveNew = __new(::acme::exclusive(strId, psa));

         __m_own(this, pexclusive, pexclusiveNew OBJ_REF_DBG_COMMA_THIS_NOTE("::apex::application::get_exclusive") );

      }

      return pexclusive;

   }


   bool application::exclusive_fails(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      auto pexclusive = get_exclusive(strId, psa);

      if(!pexclusive)
      {

         return false;

      }

      return pexclusive->exclusive_fails();

   }


   bool application::check_exclusive(bool & bHandled)
   {

#ifdef _UWP

      return true;

#endif

      bool bSetOk;

      LPSECURITY_ATTRIBUTES psa = nullptr;

      bool bResourceException = false;

#ifdef WINDOWS_DESKTOP

      bSetOk = false;

      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory(&MutexAttributes, sizeof(MutexAttributes));
      MutexAttributes.nLength = sizeof(MutexAttributes);
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if (bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)nullptr" here
         bSetOk = SetSecurityDescriptorDacl(&SD,
                                            TRUE,
                                            (PACL)nullptr,
                                            FALSE) != FALSE;
      }

      if (bSetOk)
      {

         MutexAttributes.lpSecurityDescriptor = &SD;


         psa = &MutexAttributes;


      }

#else

      bSetOk = true;

#endif


      if (bSetOk)
      {

         bool bGlobalExclusiveFail = exclusive_fails(get_global_mutex_name(), psa);

         if(bGlobalExclusiveFail && m_eexclusiveinstance == ExclusiveInstanceGlobal)
         {

            TRACE("A instance of the application:<br><br> - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");

            try
            {

               if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceGlobal, ""))
               {

                  return false;

               }

            }
            catch(...)
            {

               return false;

            }

         }

         if (m_eexclusiveinstance == ExclusiveInstanceGlobalId)
         {

            bool bGlobalIdExclusiveFail = exclusive_fails(get_global_id_mutex_name(), psa);

            if (bGlobalIdExclusiveFail)
            {

               TRACE("A instance of the application:<br><br>-" + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");

               try
               {

                  if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceGlobalId, get_global_mutex_id()))
                  {

                     return false;

                  }

               }
               catch(...)
               {

                  return false;

               }

            }

         }

         bool bLocalExclusiveFail = exclusive_fails(get_local_mutex_name(), psa);

         if (bLocalExclusiveFail && m_eexclusiveinstance == ExclusiveInstanceLocal)
         {

            try
            {

               TRACE("A instance of the application:<br><br>-" + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");

               if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceLocal, ""))
               {

                  return false;

               }

            }
            catch (...)
            {

               return false;

            }

         }

         if (m_eexclusiveinstance == ExclusiveInstanceLocalId)
         {

            bool bLocalIdExclusiveFail = exclusive_fails(get_local_id_mutex_name(), psa);

            if (bLocalIdExclusiveFail)
            {

               try
               {

                  // Should in some way activate the other instance
                  TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same ac::count with the same id.<br><br>Exiting this new instance.");

                  if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceLocalId, get_local_mutex_id()))
                  {

                     return false;

                  }

               }
               catch (...)
               {

                  return false;

               }

            }

         }

      }

      return true;

   }


   bool application::release_exclusive()
   {

      m_mapExclusive.remove_all();

      return true;

   }


   ::estatus application::notify_process_init()
   {

      ::message::application message(::message::application_process_init);

      route_message(&message);

      return true;

   }


   ::estatus application::notify_init1()
   {

      ::message::application message(::message::application_init1);

      route_message(&message);

      return message.m_bOk;

   }


   ::estatus application::notify_init2()
   {

      ::message::application message(::message::application_init2);

      route_message(&message);

      return message.m_bOk;

   }
   ::estatus application::notify_init3()
   {

      ::message::application message(::message::application_init3);

      route_message(&message);

      return message.m_bOk;

   }




   void application::notify_term3()
   {

      ::message::application message(::message::application_init3);

      route_message(&message);

      //      if (!message.m_bOk)
      //         return false;
      //
      //      return true;

   }


   void application::notify_term2()
   {

      ::message::application message(::message::application_term2);

      route_message(&message);

   }


   void application::notify_term1()
   {

      ::message::application message(::message::application_term1);

      try
      {

         route_message(&message);

      }
      catch (...)
      {

      }

      //return message.m_bOk;

   }


   void application::notify_process_term()
   {

      ::message::application message(::message::application_process_term);

      route_message(&message);

      //return message.m_bOk;

   }







   string application::get_local_mutex_name()
   {
      return System.get_local_mutex_name(get_mutex_name_gen());
   }


   string application::get_local_id_mutex_name()
   {

      return System.get_local_id_mutex_name(get_mutex_name_gen(), get_local_mutex_id());

   }


   string application::get_global_mutex_name()
   {
      return System.get_global_mutex_name(get_mutex_name_gen());
   }

   string application::get_global_id_mutex_name()
   {
      return System.get_global_id_mutex_name(get_mutex_name_gen(), get_global_mutex_id());
   }




   ::estatus application::on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId)
   {

      if (eexclusive == ExclusiveInstanceLocal)
      {

         return on_exclusive_instance_local_conflict(bHandled);

      }
      else if (eexclusive == ExclusiveInstanceLocalId)
      {

         return on_exclusive_instance_local_conflict_id(bHandled, strId);

      }

      return false;

   }


   ::estatus application::on_exclusive_instance_local_conflict(bool & bHandled)
   {

      bool bContinue = false;

      try
      {

         if (m_pinterprocessintercommunication)
         {

            auto pcall = m_pinterprocessintercommunication->create_call("application", "on_additional_local_instance");

            pcall->add_arg(Context.file().module());

            pcall->add_arg(Context.os().get_pid());

            pcall->add_arg(System.command_line_text());

            string strId;

            pcall->add_arg(strId);

            pcall->announce();

            pcall->wait();

            for(auto & pair : pcall->m_mapTask)
            {

               auto & pobjectTask = pair.element2();

               if(bContinue && pobjectTask->has_property("continue"))
               {

                  bContinue = pobjectTask->m_var["continue"];

               }

               if(!bHandled && pobjectTask->has_property("handled"))
               {

                  bHandled = pobjectTask->m_var["handled"];

               }

            }

         }

      }
      catch (...)
      {

      }

      return bContinue;

   }


   ::estatus application::on_exclusive_instance_local_conflict_id(bool & bHandled, string strId)
   {

      bool bContinue = false;

      try
      {

         if (m_pinterprocessintercommunication)
         {

            auto pcall = m_pinterprocessintercommunication->create_call("application", "on_additional_local_instance");

            pcall->add_arg(Context.file().module());

            pcall->add_arg(Context.os().get_pid());

            pcall->add_arg(System.command_line_text());

            pcall->add_arg(strId);

            for(auto & ptask : pcall->m_mapTask.values())
            {

               if(!bHandled)
               {

                  bHandled = ptask->is_true("handled");

                  if(bHandled)
                  {

                     bContinue = ptask->is_true("continue");

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      return bContinue;

   }


   ::estatus application::on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine)
   {

      auto pcommandline = __create_new < command_line >();

      pcommandline->initialize_command_line(strCommandLine);

      request({pcommandline});

      bHandled = true;

      return false;

   }


   void application::on_new_instance(string strModule, const ::id & iPid)
   {

   }


   //string application::get_mutex_name_gen()
   //{
   //   return m_strAppName;
   //}


   string application::get_local_mutex_id()
   {

      return value("local_mutex_id");

   }


   string application::get_global_mutex_id()
   {

      return value("global_mutex_id");

   }


   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   void application::on_set_scalar(e_scalar escalar, i64 iValue, int iFlags)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

      }

   }


   void application::get_scalar_minimum(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   void application::get_scalar(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         ::int_scalar_source::get_scalar(escalar, i);

      }

   }

   void application::get_scalar_maximum(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }


   //i32 application::sync_message_box_timeout(::user::primitive * pwndOwner, payload payload, const char * pszTitle, ::duration durationTimeOut, ::u32 fuStyle)
   //{

   //   UNREFERENCED_PARAMETER(durationTimeOut);

   //   return sync_message_box(pwndOwner, payload, pszTitle, fuStyle);

   //}






   string application::http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      ::exception::throw_interface_only();

      return "";

   }




   void application::message_handler(::message::base * pbase)
   {

      ::thread::message_handler(pbase);

   }


   void application::set_locale(const string & pcsz, const ::action_context & context)

   {

      string strLocale(pcsz);


      strLocale.trim();

      m_strLocale = strLocale;

      on_set_locale(m_strLocale, context);

   }


   void application::set_schema(const string & pcsz, const ::action_context & context)

   {

      string strSchema(pcsz);


      strSchema.trim();

      m_strSchema = strSchema;

      on_set_schema(m_strSchema, context);

   }


   void application::on_set_locale(const string & pcsz, const ::action_context & context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //System.appa_load_string_table();
   }


   void application::on_set_schema(const string & pcsz, const ::action_context & context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //System.appa_load_string_table();
   }





   string application::get_locale_schema_dir()
   {

      return ::str::_001Concat(get_locale(), "/", get_schema());

   }


   string application::get_locale_schema_dir(const string & strLocale)
   {

      return ::str::_001Concat(strLocale.is_empty() ? get_locale() : strLocale, "/", get_schema());

   }


   void application::matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {

      if (strLocale.is_empty() || strSchema.is_empty())
      {

         return;

      }

      for (auto & strMatterLocator : straMatterLocator)
      {

         string strLs = get_locale_schema_dir(strLocale, strSchema);

         stra.add_unique(::file::path(strMatterLocator) / strLs);

      }

   }


   void application::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      auto psession = Session;

      ::apex::str_context * pcontext = psession->str_context();

      for (i32 i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
      {

         string strLocale = pcontext->localeschema().m_idaLocale[i];

         string strSchema = pcontext->localeschema().m_idaSchema[i];

         matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, "en", "en");

      matter_locator_locale_schema_matter(stra, straMatterLocator, "_std", "_std");

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("404", "404"));

      }

   }


   string application::get_locale_schema_dir(const string & strLocale, const string & strSchema)
   {

      return ::str::_001Concat(strLocale, "/", strSchema);

   }


   void application::fill_locale_schema(::str::international::locale_schema & localeschema, const string & pszLocale, const string & pszSchema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_idLocale = pszLocale;
      localeschema.m_idSchema = pszSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant(__id(std), strSchema);
      localeschema.add_locale_variant(__id(en), strSchema);

      localeschema.finalize();

   }


   void application::fill_locale_schema(::str::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      string_array straLocale;
      string_array straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      string_array stra;

      stra = value("locale").stra();

      stra.remove_ci("_std");

      straLocale.add_unique(value("locale").stra());

      stra.empty();

      stra = value("schema").stra();

      stra.remove_ci("_std");

      straSchema.add_unique(value("schema").stra());

      localeschema.m_idLocale = straLocale[0];
      localeschema.m_idSchema = straSchema[0];

      for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(std), straSchema[iSchema]);

      }


      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(en), straSchema[iSchema]);

      }

      localeschema.finalize();

   }


   bool application::platform_open_by_file_extension(index iEdge, const char * pszPathName, ::create * pcreate)
   {

      return false;

   }


   bool application::platform_open_by_file_extension(index iEdge, ::create * pcc)
   {

      return false;

   }




   //i32 application::hotplugin_host_starter_start_sync(const char * pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   //{

   //   return -1;

   //}


   bool application::is_application() const
   {

      return !is_session() && !is_system();

   }



   //bool application::_001OnAgreeExit()
   //{

   //   return true;

   //}


   void application::_001OnFranceExit()
   {

      //if (System.m_pmultimedia)
      //{

      //   System.m_pmultimedia->_001OnFranceExit();

      //}


      HideApplication();

      //close(::apex::e_end_app);

      finish(get_context());

   }


   void application::_001FranceExit()
   {

      _001OnFranceExit();

      m_bFranceExit = true;

   }


   //void application::dispatch_user_message(::user::message * pusermessage)
   //{

   //   pusermessage->send();

   //}


   //void application::play_audio(payload varFile, bool bSynch)
   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(bSynch);

   //}

   void application::post_critical_error_message(const char * pszMessage, bool bShowLog)
   {

      string strMessage;

      strMessage = System.datetime().international().get_gmt_date_time();
      strMessage += " ";
      strMessage += pszMessage;
      strMessage += "\n";

      {

         sync_lock sl(mutex());

         Context.file().add_contents(Context.dir().appdata() / (Context.file().module().name() + "_log_error.txt"), strMessage);

      }

      if (bShowLog)
      {

         show_critical_error_log();

      }

   }


   string application::get_app_user_friendly_task_bar_name()
   {

      ::file::path path = m_strAppName;

      string strTitle = path.title();

      return strTitle;

   }



   void application::show_critical_error_log()
   {

      static int g_iCount = 0;

      string strFile = Context.dir().appdata() / (Context.file().module().name() + "_log_error.txt");

      g_iCount++;

      if (g_iCount == 1)
      {

         Context.os().file_open(strFile);

      }

//#ifdef _UWP
//
//      output_debug_string(strFile);
//
//#elif defined(WINDOWS)
//
//      call_async("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", "\"" + strFile + "\"", "", e_display_normal, false);
//
//#elif defined(LINUX)
//
//      call_async("gedit", "\"" + strFile + "\"", "", e_display_normal, false);
//
//#else
//
//      ::fork(this, [=]()
//      {
//
//         system("open \"" + strFile + "\"");
//
//      });
//
//
//#endif




   }


   void application::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {


   }


   //bool application::compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed)
   //{

   //   return System.compress().ungz(this, pfileUncompressed, pfileCompressed);

   //}


   //bool application::compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel)
   //{

   //   return System.compress().gz(this, pfileCompressed, pfileUncompressed, iLevel);


   //}

   //void application::interactive_credentials(::account::credentials * pcredentials)
   //{

   //   psession->interactive_credentials(pcredentials);

   //}


   ::file::path application::get_executable_path()
   {

      return ::dir::module() / (get_executable_title() + get_executable_extension());


   }


   string application::get_executable_extension()
   {

#ifdef WINDOWS

      return ".exe";

#else

      return "";

#endif

   }


   string application::get_executable_title()
   {

      return executable_title_from_appid(get_executable_appid());

   }


   string application::get_executable_appid()
   {

      return m_strAppId;

   }


   ::estatus application::app_set(string strPath, string strValue)
   {

      return Context.sys_set(::file::path(m_strAppName) / strPath, strValue);

   }


   string application::app_get(string strPath, string strDefault)
   {

      return Context.sys_get(::file::path(m_strAppName) / strPath, strDefault);

   }


   bool application::on_open_document_file(payload varFile)
   {

      request_file(varFile);

      return varFile["document"].cast < ::object > () != nullptr;

   }



   void application::install_trace(const string & str)
   {

      sync_lock sl(mutex());

      //::install::trace_file(this, m_strInstallTraceLabel).print(str);

   }


   void application::install_trace(double dRate)
   {

      sync_lock sl(mutex());

      //::install::trace_file(this, m_strInstallTraceLabel).print(dRate);

   }


   bool application::register_spa_file_type()
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkey;

      wstring extension = L".spa";                     // file extension
      wstring desc = L"spafile";          // file type description
      wstring content_type = L"application/x-spa";

      wstring app(::dir::stage(m_strAppId, process_platform_dir_name(), process_configuration_dir_name()));

      wstring icon(app);

      app = L"\"" + app + L"\"" + L" \"%1\"";
      icon = L"\"" + icon + L"\",107";

      wstring action = L"Open";

      wstring sub = L"\\shell\\";

      wstring path = L"spafile\\shell\\open\\command";


      // 1: Create subkey for extension -> HKEY_CLASSES_ROOT\.002
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, extension.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte*)desc.c_str(), ::u32 (desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (byte*)content_type.c_str(), ::u32 (content_type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegCloseKey(hkey);



      // 2: Create Subkeys for action ( "Open with my program" )
      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte*)app.c_str(), ::u32(app.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);


      path = L"spafile\\DefaultIcon";

      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (byte*)icon.c_str(), ::u32 (icon.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);

      wstring wstr(dir::stage(m_strAppId, process_platform_dir_name(), process_configuration_dir_name()) / "spa_register.txt");

      int iRetry = 9;

      while (!file_exists(utf8(wstr.c_str())) && iRetry > 0)
      {

         dir::mk(dir::name(utf8(wstr.c_str())).c_str());

         file_put_contents(utf8(wstr.c_str()).c_str(), "");

         iRetry--;

         millis_sleep(100);

      }

#endif

      return true;

   }


   bool application::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
   {

      ::install::admin_mutex smutex(strPlatform);

      return smutex.already_exists();

   }


   void application::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

      if (low_is_app_app_admin_running(strPlatform, strConfiguration))
      {

         return;

      }

      start_program_files_app_app_admin(strPlatform, strConfiguration);

   }


   void application::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS_DESKTOP

      SHELLEXECUTEINFOW sei = {};

      string str = ::path::app_app_admin(strPlatform, strConfiguration);

      if (!::file_exists(str))
      {

         return;

      }

      ::install::admin_mutex mutexStartup("-startup");

      wstring wstr(str);

      sei.cbSize = sizeof(SHELLEXECUTEINFOW);
      sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
      sei.lpVerb = L"RunAs";

      sei.lpFile = wstr.c_str();

      ::ShellExecuteExW(&sei);

      DWORD dwGetLastError = GetLastError();

#endif

   }


   string application::get_app_id(string wstr)
   {

      if (wstr.length() <= 0)
      {

         return "";

      }

      wstr.trim();

      ::str::trim_any_quotes(wstr);

      wstr.trim();

      if (wstr.length() <= 0)
      {

         return "";

      }


      ::string strPath = wstr.c_str();

      ::string strContents = file_as_string(strPath.c_str());

      __throw(todo("xml"));

      //::xml::document doc;

      //if (!doc.load(strContents.c_str()))
      //{

      //   return "";

      //}

      //const char * psz = doc.GetChildAttrValue("launch", "app");

      //if (psz == nullptr || *psz == '\0')
      //{

      //   return "";

      //}

      //return psz;

      return nullptr;

   }


   //LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   //{

   //   __throw(interface_only_exception(nullptr));

   //   return nullptr;

   //}


   void application::defer_create_keyboard()
   {

      //set_keyboard_layout(nullptr,::source_database);

   }


   bool application::keyboard_focus_is_focusable(::user::primitive * pue)
   {

      return false;

   }


   bool application::keyboard_focus_OnSetFocus(::user::primitive * pue)
   {

      return true;

   }


   bool application::send_message_to_windows(const ::id & id, WPARAM wparam, LPARAM lparam) // with tbs in <3
   {

      //__pointer(::user::interaction) pwnd;

      //try
      //{

      //   while (get_frame(pwnd))
      //   {

      //      try
      //      {

      //         if (pwnd && pwnd->is_window())
      //         {

      //            try
      //            {

      //               pwnd->send_message(message, wparam, lparam);


      //            }
      //            catch (...)
      //            {

      //            }

      //            try
      //            {

      //               pwnd->send_message_to_descendants(message, wparam, lparam);


      //            }
      //            catch (...)
      //            {


      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

      __throw(interface_only_exception);

      return false;

   }


   bool application::route_message_to_windows(::message::message * pmessage) // with tbs in <3
   {

      __throw(interface_only_exception);

      //__pointer(::user::interaction) pwnd;

      //try
      //{

      //   while (get_frame(pwnd))
      //   {

      //      try
      //      {

      //         if (pwnd && pwnd->is_window())
      //         {

      //            try
      //            {

      //               pwnd->route_message(pmessage);

      //            }
      //            catch (...)
      //            {

      //            }

      //            try
      //            {

      //               pwnd->route_message_to_descendants(pmessage);

      //            }
      //            catch (...)
      //            {


      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{


      //}

      return false;

   }


   void application::send_language_change_message()
   {

      ::message::message message(e_message_language);

      route_message_to_windows(&message);

   }


   //::user::interaction * application::main_window()
   //{

   //   if (!m_puiMain1)
   //   {

   //      return nullptr;

   //   }

   //   return m_puiMain1->m_puiThis;

   //}


   string application::preferred_experience()
   {

      string strExperience;

      strExperience = value("experience");

      if (strExperience.has_char())
      {

         return strExperience;

      }

      return "core";

   }

   //::user::document *application::place_hold(::user::interaction * pinteraction)
   //{

   //   return nullptr;

   //}


   bool application::post_message(const ::id & id, WPARAM wparam, lparam lparam )
   {

      return ::thread::post_message(id, wparam, lparam);

   }


   //::draw2d::icon * application::set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   ::draw2d::icon * piconOld = get_icon(pobject, bBigIcon);

   //   if (bBigIcon)
   //   {

   //      pobject->value("big_icon") = (__pointer(object)) picon;

   //   }
   //   else
   //   {

   //      pobject->value("small_icon") = (__pointer(object)) picon;

   //   }

   //   return piconOld;

   //}


   //::draw2d::icon * application::get_icon(object * pobject, bool bBigIcon) const
   //{

   //   if (bBigIcon)
   //   {

   //      return ((object *)pobject)->cast < ::draw2d::icon >("big_icon");

   //   }
   //   else
   //   {

   //      return ((object *)pobject)->cast <::draw2d::icon>("small_icon");

   //   }

   //}


   void application::_001OnAppExit(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      _001TryCloseApplication();

   }


   bool application::is_equal_file_path(const ::file::path & path1Param, const ::file::path & path2Param)
   {

      ::file::path path1;

      ::file::path path2;

      path1 = Context.defer_process_path(path1Param);

      path2 = Context.defer_process_path(path2Param);

      path1 = node_full_file_path(path1);

      path2 = node_full_file_path(path2);

      return strcmp(path1, path2) == 0;

   }


//   void application::on_event(::u64 u, ::object * pobject)
//   {
//
//      object_ptra ptra;
//
//      {
//
//         sync_lock sl(mutex());
//
//         ptra = m_objectptraEventHook;
//
//      }
//
//      for(auto & pobject : ptra)
//      {
//
//         pobject->on_event(u, pobject);
//
//      }
//
//
//   }


   ::file::path application::appconfig_folder()
   {

      return ::dir::config() / m_strAppName;

   }


   //::account::user * application::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   //{

   //   if(::is_null(get_context_session()))
   //   {

   //      return nullptr;

   //   }

   //   return get_context_session()->get_user(pathUrl, bFetch, bInteractive);

   //}


   //::account::user * application::interactive_get_user(::file::path pathUrl)
   //{

   //   return get_user(pathUrl, true, true);

   //}


   //::account::user * application::noninteractive_get_user(::file::path pathUrl)
   //{

   //   return get_user(pathUrl, true, false);

   //}


   void application::on_initial_frame_position(::user::frame * pframe)
   {

      System.on_initial_frame_position(pframe);

   }


   void application::on_graphics_ready()
   {

   }


   //__pointer(::user::document) application::defer_create_view(string strView, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::id & id)
   //{

   //   //auto pcontroller = Multimedia.defer_create_view(strView, puiParent, ewindowflag, id);

   //   //if (pcontroller)
   //   //{

   //   //   return pcontroller;

   //   //}

   //   return nullptr;

   //}

   void application::process_message(::message::base * pbase)
   {

      return ::thread::process_message(pbase);

   }


//   ::account::user * application::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_context_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_context_session()->interactive_get_user();
//
//   }
//
//
//   ::account::user * application::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_context_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_context_session()->noninteractive_get_user();
//
//   }


   //::type application::user_default_controltype_to_typeinfo(::user::e_control_type econtroltype)
   //{

   //   return __type(::user::interaction);

   //}


   //::type application::control_type_from_id(const ::id & id, ::user::e_control_type & econtroltype)
   //{

   //   econtroltype = ::user::control_type_none;

   //   return __type(::user::interaction);

   //}


   ::id application::translate_property_id(const ::id & id)
   {

      //if(!is_system())
      //{

        // if(!is_session())
         //{

           // return psession->translate_property_id(id);

         //}
         //else
         //{

           // return System.translate_property_id(id);

         //}

      //}

      return id;

   }


   //void application::record(::create * pcommand)
   //{

   //   sync_lock sl(mutex());

   //   get_command()->m_createa.add(pcommand);

   //}


   bool application::on_start_application()
   {

      string strAppId = m_strAppId;

      auto& file = System.file();

      string strJson = file.as_string(::dir::config() / strAppId / +"http.json");

      if (strJson.has_char())
      {

         try
         {

            System.http().m_setHttp.parse_json(strJson);

         }
         catch (...)
         {

         }

      }

      set_last_run_application_path(strAppId);

      if (!os_on_start_application())
      {

         return false;

      }

      return true;

   }


   bool application::start_application(bool bSynch, ::create * pcreate)
   {

//      try
//      {
//
//         if (pbias != nullptr)
//         {
//
//            if (pbias->m_pcallback != nullptr)
//            {
//
//               pbias->m_pcallback->connect_to(this);
//
//            }
//
//         }
//      }
//      catch (...)
//      {
//      }

//      if (pbias != nullptr)
//      {
//
//         m_biasCalling = *pbias;
//
//      }

      if (bSynch)
      {

         if (!begin_synch())
         {

            return false;

         }

      }
      else
      {

         begin();

      }


      return true;

   }


   void application::HideApplication()
   {


      //try
      //{
      __throw(todo("interaction"));

      //   if (m_puiMain1)
      //   {

      //      m_puiMain1->display(::e_display_hide);

      //      m_puiMain1->set_need_redraw();

      //      m_puiMain1->post_redraw();

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   string application::load_string(const ::id & id)
   {

      sync_lock sl(&m_mutexStr);

      string str;

      if (m_stringmap.lookup(id, str))
      {

         return str;

      }

      if (!load_string(str, id))
      {

         id.to_string(str);

         return str;

      }

      m_stringmap.set_at(id, str);

      return str;

   }


   bool application::load_string(string & str, const ::id & id)
   {

      if (!load_cached_string(str, id, true))
      {

         return false;

      }

      return true;

   }


   bool application::load_cached_string(string & str, const ::id & id, bool bLoadStringTable)
   {


      //__throw(todo("xml"));

      //auto pdocument = __new(::xml::document);

      //if (!pdocument->load(id) || !*pdocument)
      //{

      //   return load_cached_string_by_id(str, id, bLoadStringTable);

      //}

      //auto pnodeRoot = pdocument->root();

      //if (pnodeRoot->get_name() == "string")
      //{

      //   string strId = pnodeRoot->attribute("id");

      //   if (!load_cached_string_by_id(str, strId, bLoadStringTable))
      //   {

      //      str = pnodeRoot->get_value();

      //   }

      //   return true;

      //}

      return false;

   }


   //bool application::load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable)
   //{

   //   string strId(id.str());

   //   string strTable;

   //   string strString;

   //   index iFind = 0;

   //   if ((iFind = strId.find(':')) <= 0)
   //   {

   //      strTable = "";

   //      strString = strId;

   //   }
   //   else
   //   {

   //      strTable = strId.Mid(0, iFind);

   //      strString = strId.Mid(iFind + 1);

   //   }

   //   sync_lock sl(&m_mutexStr);

   //   __pointer(string_to_string) pmap;

   //   if (m_stringtableStd.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (m_stringtable.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (bLoadStringTable)
   //   {

   //      load_string_table(strTable, "");

   //      return load_cached_string_by_id(str, id, false);

   //   }

   //   return false;

   //}


   void application::load_string_table(const string & pszApp, const string & pszId)
   {


   }




   //void application::load_string_table()
   //{

   //   load_string_table("", "");

   //}


   //bool application::is_system() const
   //{

   //   return false;

   //}


   //bool application::is_session() const
   //{

   //   return false;

   //}


   //bool application::is_serviceable() const
   //{

   //   return false;

   //}


   //::simpledb::server * application::simpledb()
   //{

   //   return m_psimpledb;

   //}


   ::database::server * application::dataserver()
   {

      //return simpledb();

      return nullptr;

   }


   ::estatus application::verb()
   {

      return true;

   }


   //void application::SetCurrentHandles()
   //{

   //   ::apex::application::SetCurrentHandles();

   //}


   void application::_001TryCloseApplication()
   {

      if (_001CanCloseApplication())
      {

#ifdef _UWP
         Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(
            Windows::UI::Core::CoreDispatcherPriority::Normal,
            ref new Windows::UI::Core::DispatchedHandler([this]()
               {
                  Windows::UI::ViewManagement::ApplicationView::GetForCurrentView()->TryConsolidateAsync();
      }));

#else

         finish();

#endif

      }

   }


   bool application::_001CanCloseApplication()
   {

      return true;

   }


   //bool application::process_exception(::exception_pointer pe)
   //{

   //   return apex::application::process_exception(e);

   //}


   //::estatus     application::main()
   //{

   //   return ::apex::application::main();

   //}


   ::estatus application::on_run()
   {

      //try
      //{

      //   ::apex::::message::application signal(::apex::::message::application_begin);

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      thread * pthread = ::get_thread();

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


   //::estatus application::init_application()
   //{

   //   return ::apex::application::init_application();

   //}


   //::estatus application::application_pre_run()
   //{

   //   return ::apex::application::application_pre_run();

   //}



   //bool application::InitApplication()
   //{

   //   return true;

   //}


   //bool application::do_install()
   //{


   //   if (!::apex::application::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::do_uninstall()
   //{

   //   bool bOk = apex::application::do_uninstall();

   //   return bOk;

   //}


   //bool application::on_install()
   //{

   //   if (!apex::application::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::on_uninstall()
   //{

   //   if (!apex::application::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //::estatus application::os_native_bergedge_start()
   //{

   //   if (!::apex::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::on_request(::create * pcreate)
   //{

   //   apex::application::on_request(pcreate);

   //}


   //::estatus     application::run()
   //{

   //   return ::apex::application::run();

   //}


   //__pointer(::apex::application) application::assert_running(const char * pszAppId)
   //{

   //   __pointer(::apex::application) papp;

   //   papp = psession->m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      __pointer(::create) spcreate(e_create);

   //      papp = psession->start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}


   //::estatus application::process_init()
   //{

   //   create_factory < ::database::field_array >();
   //   create_factory < ::database::row >();
   //   create_factory < ::database::row_array >();

   //   //if (m_bAxisProcessInitialize)
   //   //{

   //   //   return m_bAxisProcessInitializeResult;

   //   //}

   //   INFO("axis::application::process_init");

   //   //m_bAxisProcessInitialize = true;

   //   //m_bAxisProcessInitializeResult = false;

   //   if (m_psimpledb.is_null())
   //   {

   //      __construct_new(m_psimpledb);

   //   }

   //   if (!::apex::application::process_init())
   //   {

   //      FATAL("axis::application::process_init .1");

   //      return false;

   //   }


   //   //m_bAxisProcessInitializeResult = true;

   //   FATAL("axis::application::process_init success");

   //   return true;

   //}


   //::estatus application::init_instance()
   //{

   //   //if (m_bAxisInitializeInstance)
   //   //{

   //   //   return m_bAxisInitializeInstanceResult;

   //   //}

   //   INFO("axis::application::init_instance .1");

   //   //m_bAxisInitializeInstance = true;

   //   //m_bAxisInitializeInstanceResult = false;

   //   if (!::apex::application::init_instance())
   //   {

   //      FATAL("axis::application::init_instance .2");

   //      return false;

   //   }


   //   if (m_bInitializeDataCentral)
   //   {


   //      ::file::path pathDatabase;

   //      if (is_system())
   //      {

   //         pathDatabase = Context.dir().appdata() / "system.sqlite";

   //      }
   //      else if (is_session())
   //      {

   //         pathDatabase = Context.dir().appdata() / "session.sqlite";

   //      }
   //      else
   //      {

   //         pathDatabase = Context.dir().appdata() / "app.sqlite";

   //      }

   //      auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

   //      if (!estatus)
   //      {

   //         m_result.add(estatus);

   //         return false;

   //      }

   //      set_data_server(m_psimpledb);

   //   }



   //   //m_bAxisInitializeInstanceResult = true;

   //   INFO("axis::application::init_instance success");

   //   return true;

   //}


   //::database::key application::calc_data_key()
   //{

   //   return ::database::key("app://" + m_strAppName, is_local_data());

   //}




   //::estatus application::init1()
   //{

   //   //if (m_bAxisInitialize1)
   //   //{

   //   //   return m_bAxisInitialize1Result;

   //   //}

   //   //m_bAxisInitialize1 = true;

   //   //m_bAxisInitialize1Result = false;

   //   m_millisHeartBeat.Now();

   //   if (!::apex::application::init1())
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

   //   if (!::apex::application::init2())
   //      return false;

   //   return true;

   //}


   //::estatus application::init3()
   //{

   //   if (!::apex::application::init3())
   //   {

   //      return false;

   //   }

   //   return true;

   //}

//


   ::estatus application::init()
   {

      m_millisHeartBeat.Now();

      if (has_property("install"))
      {

         // apex level app install
         if (!Ex2OnAppInstall())
         {

            return false;

         }

      }
      else if (has_property("uninstall"))
      {

         // apex level app uninstall
         if (!Ex2OnAppUninstall())
         {

            return false;

         }

      }
      else
      {
#ifdef WINDOWS_DESKTOP
         // when this process is started in the context of a system account,
         // for example, this code ensure that the process will
         // impersonate a loggen on ::account::user
         HANDLE hprocess;
         HANDLE htoken;

         hprocess = ::GetCurrentProcess();

         if (!OpenProcessToken(
            hprocess,
            TOKEN_ALL_ACCESS,
            &htoken))
            return false;

         if (!ImpersonateLoggedOnUser(htoken))
         {
            TRACELASTERROR();
            return false;
         }
#endif
      }

      m_millisHeartBeat.Now();

      ensure_app_interest();

      INFO(".2");

      if (is_true("install"))
      {

         if (is_user_service())
         {


         }

      }

      ERR("1.1");

      index i = applicationmenu().get_count();

      applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");

      application_menu_update();

      INFO("success");

      return true;

   }


   void application::term()
   {



   }


   bool application::is_running()
   {

      return is_alive();

   }


   //bool application::Ex2OnAppInstall()
   //{
   //   return true;
   //}


   //bool application::Ex2OnAppUninstall()
   //{

   //   return true;

   //}


   bool application::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative)
   {

      auto plocaleschema = __create_new < ::str::international::locale_schema >();

      //psession->fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_idLocale, plocaleschema->m_idSchema);

      ::count iCount = plocaleschema->m_idaLocale.get_count();

      for (index i = 0; i < iCount; i++)
      {

         if (plocaleschema->m_idaLocale[i] == __id(std) && plocaleschema->m_idaSchema[i] == __id(std) && bIgnoreStdStd)
            continue;

         string strLocale;

         plocaleschema->m_idaLocale[i].to_string(strLocale);

         string strSchema;

         plocaleschema->m_idaSchema[i].to_string(strSchema);

         update_appmatter(handler, psession, pszRoot, pszRelative, strLocale, strSchema);

         System.install_progress_add_up();

      }


      return true;

   }

   bool application::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const string & pszLocale, const string & pszStyle)
   {

      string strLocale;
      string strSchema;
      TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)", pszRoot.c_str(), pszRelative.c_str(), pszLocale.c_str(), pszStyle.c_str());
      ::file::path strRelative = ::file::path(pszRoot) / "_matter" / pszRelative / get_locale_schema_dir(pszLocale, pszStyle) + ".zip";
      ::file::path strFile = Context.dir().install() / strRelative;
      ::file::path strUrl(::file::path_url);

      if (framework_is_basis())
      {
         strUrl = "http://basis-server.ca2.cc/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl = "http://stage-server.ca2.cc/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);

      if (psession == nullptr)
      {

         while (true)
         {

            property_set setEmpty;

            if (Context.http().open(handler, psession, System.url().get_server(strUrl), System.url().get_protocol(strUrl), setEmpty, nullptr))
            {

               break;

            }

            millis_sleep(200);

         }

      }

      property_set set;

      set["get_memory"] = "";

      if (!Context.http().request(handler, psession, strUrl, set))
      {

         return false;

      }

      ::memory_file file;

      if (set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->get_size() > 0)
      {

         zip_context zip(get_context_object());

         string strDir = strFile;

         ::str::ends_eat_ci(strDir, ".zip");

         try
         {

            zip.extract_all(strDir, &file);

         }
         catch (...)
         {

            // spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //System.compress().extract_all(strFile, this);

      }

      return true;

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

      //if (get_context_session()->account() == nullptr)
      //{

      //   return false;

      //}

      //if (interactive_get_user() == nullptr)
      //{

      //   return false;

      //}

      return true;

   }




   string application::matter_as_string(const char * pszMatter, const char * pszMatter2)
   {

      payload varFile;

      varFile["disable_ca2_sessid"] = true;

      string strMatter = Context.dir().matter(::file::path(pszMatter) / pszMatter2);

      varFile["url"] = strMatter;

      return Context.file().as_string(varFile);

   }

   //string application::dir().matter(const char * pszMatter,const char * pszMatter2)
   //{

   //   return dir().matter(pszMatter,pszMatter2);

   //}

   //bool application::is_inside_time_dir(const char * pszPath)
   //{
   //   return dir().is_inside_time(pszPath);
   //}


   //bool application::file_is_read_only(const char * pszPath)
   //{

   //   return false;
   //   //return file().is_read_only(pszPath);

   //}



   //void application::process_message_filter(i32 code, ::message::message * pmessage)
   //{

   //   //SCAST_PTR(::message::base,pbase,pmessage);

   //   UNREFERENCED_PARAMETER(code);

   //   UNREFERENCED_PARAMETER(pmessage);


   //}







   void application::DoWaitCursor(i32 nCode)
   {

      if (nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if (nCode == 0)
      {

         if (m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if (m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if (m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   //void application::ShowWaitCursor(bool bShow)
   //{

   //}



   //void application::TermThread(HINSTANCE hInstTerm)
   //{

   //   ::exception::throw_interface_only();

   //}




   //string application::get_version()
   //{

   //   ::exception::throw_interface_only();

   //   return "";

   //}




//   void application::set_env_var(const string & payload,const string & value)
//   {
//
//      ::exception::throw_interface_only();
//
//   }



   //::draw2d::printer * application::get_printer(const char * pszDeviceName)
   //{

   //   ::exception::throw_interface_only();

   //   return nullptr;

   //}


   estatus application::userfs_init1()
   {

      return error_not_implemented;

   }

   estatus application::userfs_process_init()
   {

      return error_not_implemented;

   }


   string application::dialog_box(const char* pszMatter, property_set& propertyset)
   {

      __throw(todo("core and os"));

      return"";

   }

   //bool application::do_prompt_file_name(payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nIDSTitle);

   //   return false;

   //}






   //bool application::get_temp_file_name_template(string & strRet,const char * lpszName,const char * pszExtension,const char * pszTemplate)
   //{

   //   __throw(not_implemented());

   //   return false;

   //}


   //bool application::get_temp_file_name(string & strRet,const char * lpszName,const char * pszExtension)
   //{

   //   return get_temp_file_name_template(strRet,lpszName,pszExtension,nullptr);

   //}








   //::draw2d::icon * application::set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   return nullptr;

   //}


   //::draw2d::icon * application::get_icon(object * pobject, bool bBigIcon) const
   //{

   //   return nullptr;

   //}


   //void application::on_service_request(::create * pcreate)
   //{

   //   ::apex::application::on_service_request(pcreate);

   //}


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }



   string application::get_license_id()
   {

      if (m_strLicense.has_char())
         return m_strLicense;

      if (m_strInstallToken.has_char())
         return m_strInstallToken;

      return m_strAppId;

   }






   //bool application::assert_user_logged_in()
   //{

   //   return axis::application::assert_user_logged_in();

   //}





   i32 application::hotplugin_host_starter_start_sync(const char * pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      {

         ::install::mutex mutex(process_platform_dir_name2());

         if (mutex.already_exists())
         {

            //            message_box("Could not launch spa installer. It is already running.", e_message_box_ok);

            return -35;

         }

      }

      string strValue;

      if (get_command_line_param(strValue, pszCommandLine, "enable_desktop_launch"))
      {

#ifdef _UWP

         return -1;

#else

         ::property_set set;

         return ::call_sync(::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()), pszCommandLine, ::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()), e_display_normal, 2_min, set);

#endif

      }
      else
      {

         return hotplugin_host_host_starter_start_sync(pszCommandLine, get_context_application(), nullptr);

      }

   }

   i32 application::hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::apex::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      return -1;

   }



   //void application::on_control_event(::user::control_event * pevent)
   //{

   //}


   //bool application::on_open_document(::user::document * pdocument, payload varFile)
   //{

   //   UNREFERENCED_PARAMETER(pdocument);
   //   UNREFERENCED_PARAMETER(varFile);
   //   return true;

   //}


   //bool application::on_save_document(::user::document * pdocument, payload varFile)
   //{

   //   UNREFERENCED_PARAMETER(pdocument);
   //   UNREFERENCED_PARAMETER(varFile);
   //   return true;

   //}


   //void application::on_update_view(::user::impact * pview, ::user::impact * pviewSender, LPARAM lHint, object * pHint)
   //{


   //}

   //void application::on_control_event(::user::control_event* pevent)
   //{

   //}


   //void application::on_notify_control_event(::user::control_event* pevent)
   //{


   //}


   //void application::route_control_event(::user::control_event* pevent)
   //{

   //   on_control_event(pevent);

   //   if (pevent->m_bRet)
   //   {

   //      return;

   //   }

   //   on_notify_control_event(pevent);

   //   if (pevent->m_bRet)
   //   {

   //      return;

   //   }

   //}



   //   ::estatus     application::interactive_credentials(::account::credentials * pcredentials)
   //   {
   //
   //      return ::apex::applciation::interactive_credentials(pcredentials);
   //
   //   }
   //
   //
   //   string application::interactive_get_credentials(string & strUsername, string & strPassword, string strToken)
   //   {
   //
   //      return ::account::get_cred(this, strUsername, strPassword, strToken);
   //
   //   }
   //
   //   void application::set_cred(string strToken, const char * pszUsername, const char * pszPassword)
   //   {
   //
   //      ::account::set_cred(this,strToken, pszUsername, pszPassword);
   //
   //   }
   //
   //   void application::set_cred_ok(string strToken, bool bOk)
   //   {
   //
   //      ::account::set_cred_ok(this, strToken, bOk);
   //
   //   }

      //::html::html * application::create_html()
      //{

      //   return new ::html::html(get_context_application());

      //}


      //string application::http_get(const string & strUrl, ::property_set & set)
      //{

      //   return http().get(strUrl, set);

      //}

      //bool application::app_data_set(::const ::id & id, stream & stream)
      //{

      //   return data_save(id, stream);

      //}


      //bool application::app_data_get(::const ::id & id, stream & stream)
      //{

      //   return data_get(id, stream);

      //}


      //bool application::app_data_set(::const ::id & id, ::object & obj)
      //{

      //   return data_set(id, obj);

      //}


      //bool application::app_data_get(::const ::id & id, ::object & obj)
      //{

      //   return data_get(id, obj);

      //}


      //bool application::compress_ungz(const ::stream & os, const ::stream & is)
      //{

      //   return System.compress().ungz(this, os, is);


      //}


      //bool application::compress_ungz(memory_base & mem)
      //{

      //   return System.compress().ungz(this, mem);

      //}


      //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)

      //{

      //   return System.compress().gz(this, os, is, iLevel);


      //}


      //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)
      //{

      //   return System.compress().gz(this, os, is, iLevel);

      //}


   bool application::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }





} // namespace apex







namespace apex
{


   const char application::gen_FileSection[] = "Recent File List";
   const char application::gen_FileEntry[] = "File%d";
   const char application::gen_PreviewSection[] = "Settings";
   const char application::gen_PreviewEntry[] = "PreviewPages";


   //application::application()
   //{

   //   create_factory < ::user::user >();
   //   create_factory < ::userfs::userfs >();

   //   m_pmainpane = nullptr;

   //   m_ppaneviewMain = nullptr;

   //   // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
   //   //::add_ref(this);

   //   srand((u32) ::get_tick());

   //   m_bService = false;

   //   m_iResourceId = 8001;

   //   ::apex::profiler::initialize();

   //   m_pdocmanager = nullptr;

   //   m_eexclusiveinstance = ExclusiveInstanceNone;
   //   m_strLocale = "_std";
   //   m_strSchema = "_std";

   //   m_iGcomBackgroundUpdateMillis = -1;

   //}


   //application::~application()
   //{

   //}


   //::estatus application::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::apex::application::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   bool application::on_application_menu_action(const char* pszCommand)
   {

      if (m_puiMain1 != nullptr)
      {

         ::user::command command;

         command.m_id = ::id(pszCommand);

         __channel(m_puiMain1)->route_command_message(&command);

         if (command.m_bRet)
         {

            return true;

         }

      }

      return false;

   }


   //::apex::application * application::get_context_application() const
   //{

   //   return (application *) this;

   //}








   //bool application::is_system() const
   //{

   //   return false;

   //}


   //bool application::is_session() const
   //{

   //   return false;

   //}


   u32 application::guess_code_page(const string& str)
   {

      return 0;

   }


   LRESULT application::GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam)
   {

      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);

      return 0;

   }


   bool application::CreateFileFromRawResource(::u32 nID, const char* pcszType, const char* pcszFilePath)
   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);
      UNREFERENCED_PARAMETER(pcszFilePath);

      return false;

   }


#ifdef WINDOWS

   bool application::OnMessageWindowMessage(LPMESSAGE pmsg)

   {

      UNREFERENCED_PARAMETER(pmsg);


      return false;

   }

#elif defined(LINUX)

   bool application::OnX11WindowMessage(void* pXevent) // XEvent *
   {

      UNREFERENCED_PARAMETER(pXevent);

      return false;

   }

#endif

   void application::OnUpdateRecentFileMenu(::user::command* pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   bool application::GetResourceData(::u32 nID, const char* pcszType, memory& storage)

   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);

      UNREFERENCED_PARAMETER(storage);

      return false;

   }


#ifdef WINDOWS_DESKTOP

   HENHMETAFILE application::LoadEnhMetaFile(::u32 uResource)
   {

      memory storage;

      if (!GetResourceData(uResource, "EnhMetaFile", storage))
      {

         return nullptr;

      }

      return SetEnhMetaFileBits((::u32)storage.get_size(), storage.get_data());

   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // WinApp UI related functions

   void application::EnableModelessEx(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif


   }



  /* ::estatus     application::run()
   {

      return ::apex::application::run();

   }*/


   bool application::on_idle(::i32 lCount)
   {

      return false;

   }


   void application::process_window_procedure_exception(::exception_pointer pe, ::message::message* pmessage)
   {

      ENSURE_ARG(pe != nullptr);

      ENSURE_ARG(pmessage != nullptr);

      SCAST_PTR(::message::base, pbase, pmessage);

      // handle certain messages in thread

      switch (pbase->m_id)
      {
      case e_message_create:
      case e_message_paint:

         return thread::process_window_procedure_exception(pe, pmessage);

      }

      // handle all the rest
      //linux ::u32 nIDP = __IDP_INTERNAL_FAILURE;   // matter message string
      const char* nIDP = "Internal Failure";
      pbase->m_lresult = 0;        // sensible default
      if (pbase->m_id == e_message_command)
      {
         if (pbase->m_lparam == 0)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
         pbase->m_lresult = (LRESULT)TRUE;        // pretend the command was handled
      }

      if (pe.is < memory_exception >())
      {

         report_error(pe, e_message_box_icon_exclamation | e_message_box_system_modal, nIDP);

      }
      else if (pe.is < user_exception >())
      {

         // ::account::user has not been alerted yet of this catastrophic problem

         report_error(pe, e_message_box_icon_stop, nIDP);

      }

   }


   void application::route_command_message(::user::command* pcommand)
   {

      ::thread::route_command_message(pcommand);

   }


   /*
   bool application::hex_to_memory(memory & memory, const char * pszHex)
   {
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.set_size(count);
   index i = 0;
   byte b;
   while(*pszHex != '\0')
   {
   char ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b = ch - '0';
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b = ch - 'a' + 10;
   }
   else
   {
   return false;
   }
   pszHex++;
   if(*pszHex == '\0')
   {
   memory.get_data()[i] = b;
   return true;
   }
   b = b << 4;
   ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b |= (ch - '0');
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b |= (ch - 'a' + 10);
   }
   else
   {
   return false;
   }
   pszHex++;
   memory.get_data()[i] = b;
   i++;
   }
   return true;
   }


   void application::memory_to_hex(string & strHex, memory & memory)
   {
   ::count count = memory.get_size();
   char * psz = strHex.get_string_buffer(count * 2);

   for(index i = 0; i < count; i++)
   {
   *psz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));

   *psz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));

   }
   strHex.ReleaseBuffer(count * 2);
   }
   */











   // // BEGIN_MESSAGE_MAP(application, channel)
   //{{__MSG_MAP(application)
   // Global File commands
   //   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
   // MRU - most recently used file menu
   //   ON_UPDATE_::user::command(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
   //   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
   //}}__MSG_MAP
   // // END_MESSAGE_MAP()

   /*#ifdef WINDOWS


   typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
   typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


   class CActivationContext
   {
   protected :
   HANDLE m_hCtxt;
   uptr m_uCookie;

   // If pointers are nullptr then we are on a platform that does not support WinSXS.
   typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
   static PFNCreateActCtx s_pfnCreateActCtx;

   typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
   static PFNReleaseActCtx s_pfnReleaseActCtx;

   typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, uptr*);
   static PFNActivateActCtx s_pfnActivateActCtx;

   typedef bool (WINAPI * PFNDeactivateActCtx)(u32, uptr);
   static PFNDeactivateActCtx s_pfnDeactivateActCtx;

   static bool s_bPFNInitialized;

   public:
   CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
   {
   // Multiple threads initializing is fine since they will initialize the pointers to the
   // same value.
   if (!s_bPFNInitialized)
   {
   HMODULE hKernel = GetModuleHandle("KERNEL32");
   ENSURE (hKernel != nullptr);
   #ifdef _UNICODE
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
   #else
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
   #endif
   s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
   s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
   s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
   if (s_pfnCreateActCtx != nullptr)
   {
   // If one of the functions is present then all the functions have to be present.
   ENSURE( s_pfnReleaseActCtx != nullptr &&
   s_pfnActivateActCtx != nullptr &&
   s_pfnDeactivateActCtx != nullptr);
   }
   else
   {
   // If one of the functions is not present then all the functions should not be present.
   ENSURE( s_pfnReleaseActCtx == nullptr &&
   s_pfnActivateActCtx == nullptr &&
   s_pfnDeactivateActCtx == nullptr);
   }
   s_bPFNInitialized = true;
   }
   };

   ~CActivationContext()
   {
   Release();
   }

   bool create( PCACTCTX pactctx )
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnCreateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( pactctx != nullptr );
   if ( pactctx == nullptr )
   {
   return false;
   }

   ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   return false;
   }

   return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
   }

   void Release()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnReleaseActCtx == nullptr)
   {
   return;
   }

   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   Deactivate();
   s_pfnReleaseActCtx( m_hCtxt );
   }
   }

   bool Activate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnActivateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
   if ( m_hCtxt == INVALID_HANDLE_VALUE )
   {
   return false;
   }

   ASSERT( m_uCookie == 0 );
   if ( m_uCookie != 0 )
   {
   return false;
   }

   return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
   }

   bool Deactivate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnDeactivateActCtx == nullptr)
   {
   return true;
   }

   if ( m_uCookie != 0 )
   {
   uptr uCookie = m_uCookie;
   m_uCookie = 0;
   return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
   }
   return true;
   }
   };


   CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = nullptr;
   CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = nullptr;
   CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = nullptr;
   CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = nullptr;
   bool CActivationContext::s_bPFNInitialized = false;


   // HINSTANCE of the module
   extern "C" IMAGE_DOS_HEADER __ImageBase;

   */


   bool application::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }

   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   // To reduce risk of leaks, I've declared the whole function noexcept. This despite the fact that its callers have
   // no dependency on non-throwing.
   bool application::_LoadSysPolicies() noexcept
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkPolicy = nullptr;
      ::u32 dwValue = 0;
      ::u32 dwDataLen = sizeof(dwValue);
      ::u32 dwType = 0;

      //// clear current policy settings.
      //m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

      //static __system_policy_data rgExplorerData[] =
      //{
      //   {"NoRun",___SYSPOLICY_NORUN},
      //   {"NoDrives",___SYSPOLICY_NODRIVES},
      //   {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
      //   {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
      //   {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
      //   {"NoClose",___SYSPOLICY_NOCLOSE},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgNetworkData[] =
      //{
      //   {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgComDlgData[] =
      //{
      //   {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
      //   {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
      //   {"NoFileMru",___SYSPOLICY_NOFILEMRU},
      //   {nullptr,0}
      //};

      //static __system_policies rgPolicies[] =
      //{
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
      //      rgExplorerData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
      //      rgNetworkData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
      //      rgComDlgData
      //   },
      //   {nullptr,0}
      //};

      //__system_policies *pPolicies = rgPolicies;
      //__system_policy_data *pData = nullptr;

      //while (pPolicies->szPolicyKey != nullptr)
      //{

      //   if (ERROR_SUCCESS == ::RegOpenKeyEx(
      //            HKEY_CURRENT_USER,
      //            pPolicies->szPolicyKey,
      //            0,
      //            KEY_QUERY_VALUE,
      //            &hkPolicy
      //         ))
      //   {
      //      pData = pPolicies->pData;
      //      while (pData->szPolicyName)
      //      {
      //         if (ERROR_SUCCESS == ::RegQueryValueEx(
      //                  hkPolicy,
      //                  pData->szPolicyName,
      //                  nullptr,
      //                  &dwType,
      //                  (byte*)&dwValue,
      //                  &dwDataLen))
      //         {
      //            if (dwType == REG_DWORD)
      //            {
      //               if (dwValue != 0)
      //                  m_dwPolicies |= pData->dwID;
      //               else
      //                  m_dwPolicies &= ~pData->dwID;
      //            }
      //         }
      //         dwValue = 0;
      //         dwDataLen = sizeof(dwValue);
      //         dwType = 0;
      //         pData++;
      //      }
      //      ::RegCloseKey(hkPolicy);
      //      hkPolicy = nullptr;
      //   }
      //   pPolicies++;
      //};

#endif

      return TRUE;


   }

   bool application::GetSysPolicyValue(u32 dwPolicyID, bool* pbValue)
   {
      if (!pbValue)
         return FALSE; // bad pointer
      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
      return TRUE;
   }

   //bool application::InitApplication()
   //{


   //   LoadSysPolicies();

   //   return TRUE;


   //}



   /*   void application::LoadStdProfileSettings(::u32 nMaxMRU)
   {
   UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
   }*/

   /*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (i32 i = 1; i < __argc; i++)
   {
   const char * pszParam = __targv[i];
   bool bFlag = FALSE;
   bool bLast = ((i + 1) == __argc);
   if (pszParam[0] == '-' || pszParam[0] == '/')
   {
   // remove flag specifier
   bFlag = TRUE;
   ++pszParam;
   }
   rCmdInfo.ParseParam(pszParam, bFlag, bLast);
   }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
   m_bShowSplash = TRUE;
   m_bRunEmbedded = FALSE;
   m_bRunAutomated = FALSE;
   m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
   {
   if (bFlag)
   {
   const astring strParam(pszParam);
   ParseParamFlag(strParam.GetString());
   }
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }*/

   /*
   #ifdef UNICODE
   void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
   {
   if (bFlag)
   ParseParamFlag(pszParam);
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }
   #endif // UNICODE
   */

   /*
   void CCommandLineInfo::ParseParamFlag(const char* pszParam)
   {
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "point") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "point") == 0)
   m_nShellCommand = FilePrint;
   else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
   ::__invariant_stricmp(pszParam, "Regserver") == 0)
   m_nShellCommand = AppRegister;
   else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
   ::__invariant_stricmp(pszParam, "Unregserver") == 0)
   m_nShellCommand = AppUnregister;
   else if (lstrcmpA(pszParam, "dde") == 0)
   {
   m_nShellCommand = FileDDE;
   }
   else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
   {
   m_bRunEmbedded = TRUE;
   m_bShowSplash = FALSE;
   }
   else if (::__invariant_stricmp(pszParam, "Automation") == 0)
   {
   m_bRunAutomated = TRUE;
   m_bShowSplash = FALSE;
   }
   }

   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }

   #ifdef UNICODE
   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }
   #endif

   void CCommandLineInfo::ParseLast(bool bLast)
   {
   if (bLast)
   {
   if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
   m_nShellCommand = FileOpen;
   m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
   }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // App termination

   void application::SaveStdProfileSettings()
   {
      ASSERT_VALID(this);


      //      if (m_nNumPreviewPages != 0)
      //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
   }


   //
   //
   //
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // WinHelp helper
   //
   //
   //   void application::WinHelp(uptr dwData, ::u32 nCmd)
   //   {
   //      UNREFERENCED_PARAMETER(dwData);
   //      UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle task
   //
   //      //trans pMainWnd->WinHelp(dwData, nCmd);
   //   }
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // HtmlHelp helper
   //
   //   void application::HtmlHelp(uptr dwData, ::u32 nCmd)
   //   {
   //
   //      UNREFERENCED_PARAMETER(dwData);
   //
   //      UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle task
   //
   //      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   //   }
   //
   //
   //   void application::WinHelpInternal(uptr dwData, ::u32 nCmd)
   //   {
   //      UNREFERENCED_PARAMETER(dwData);
   //      UNREFERENCED_PARAMETER(nCmd);
   //      //   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
   //      //   ENSURE_VALID(pMainWnd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle task
   //      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   //   }
   //
   //
   //#endif
   //




      /////////////////////////////////////////////////////////////////////////////
      // application idle processing

   void application::DevModeChange(char * pDeviceName)

   {
      UNREFERENCED_PARAMETER(pDeviceName);


#ifdef WINDOWS
      if (m_hDevNames == nullptr)
         return;

#endif

   }


   //bool application::process_exception(::exception_pointer pe)
   //{

   //   return ::apex::application::on_run_exception(pexception))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::final_handle_exception(::exception::exception * pexception)
   //{

   //   UNREFERENCED_PARAMETER(pexception);

   //   if (!is_system())
   //   {

   //      if (System.final_handle_exception(pexception))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   /*   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
   UNREFERENCED_PARAMETER(pszLink);
   UNREFERENCED_PARAMETER(pszTarget);
   return false;
   }
   */










   void application::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if (strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      /*      if (m_pdocmanager != nullptr)
      document_manager()->_001OnFileNew();*/
   }

   void application::on_file_open()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //document_manager()->on_file_open();
   }


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::apex::FormatString1(string & rString, ::u32 nIDS, const char * psz1)

   {
   __format_strings(rString, nIDS, &psz1, 1);

   }

   void ::apex::FormatString2(string & rString, ::u32 nIDS, const char * psz1,

   const char * psz2)

   {
   const char * rgpsz[2];
   rgpsz[0] = psz1;

   rgpsz[1] = psz2;

   __format_strings(rString, nIDS, rgpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Basic Help support (for backward compatibility to apex API 2.0)

   void application::OnHelp()  // use context to derive help context
   {
      if (m_dwPromptContext != 0)
      {
         // do not call WinHelp when the error is failing to lauch help
         //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
         //          WinHelpInternal(m_dwPromptContext);
         return;
      }

      // otherwise, use window::OnHelp implementation
      /* trans ::user::interaction_impl * pwindow = System.m_puiMain;
      ENSURE_VALID(pwindow);
      if (!pwindow->is_frame_window())
      pwindow->OnHelp();
      else
      ((pwindow))->OnHelp();*/
   }


   void application::OnHelpIndex()
   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_INDEX);
      //
      //#endif
      //
   }


   void application::OnHelpFinder()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_FINDER);
      //
      //#endif

   }


   void application::OnHelpUsing()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_HELPONHELP);
      //
      //#endif
      //
   }


   /////////////////////////////////////////////////////////////////////////////
   // Context Help Mode support (backward compatibility to apex API 2.0)

   void application::OnContextHelp()
   {
      // just use frame_window::OnContextHelp implementation
      /* trans   m_bHelpMode = HELP_ACTIVE;
      __pointer(::user::frame_window) pMainWnd = (System.m_puiMain);
      ENSURE_VALID(pMainWnd);
      ENSURE(pMainWnd->is_frame_window());
      pMainWnd->OnContextHelp();
      m_bHelpMode = pMainWnd->m_bHelpMode;
      pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle task */
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /////////////////////////////////////////////////////////////////////////////
   // WinApp support for printing

   /*bool application::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
   {
   UpdatePrinterSelection(m_hDevNames == nullptr); //force default if no current
   if (m_hDevNames == nullptr)
   return FALSE;               // no printer defaults

   ENSURE_ARG(pPrintDlg != nullptr);
   pPrintDlg->hDevNames = m_hDevNames;
   pPrintDlg->hDevMode = m_hDevMode;

   ::GlobalUnlock(m_hDevNames);
   ::GlobalUnlock(m_hDevMode);
   return TRUE;
   }*/

   void application::UpdatePrinterSelection(bool bForceDefaults)
   {
      UNREFERENCED_PARAMETER(bForceDefaults);
   }


   void application::OnFilePrintSetup()
   {
   }


#ifdef WINDOWS

   void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   {
      UNREFERENCED_PARAMETER(hDevNames);
      UNREFERENCED_PARAMETER(hDevMode);
      UNREFERENCED_PARAMETER(bFreeOld);
      ::exception::throw_not_implemented();
   }


#endif

   ::draw2d::graphics* application::CreatePrinterDC()
   {
      ::exception::throw_not_implemented();
      return nullptr;
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // application User Interface Extensions

   void application::OnAppExit()
   {

      // same as double-clicking on main window close box

      //ASSERT(m_puiMain1 != nullptr);

      //m_puiMain1->m_puiThis->send_message(e_message_close);

   }


   //void application::HideApplication()
   //{

   //   try
   //   {

   //      if (m_puiMain1 == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_puiMain1->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(FALSE);


   //      m_puiMain1->m_puiThis->order(zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puiMain1->m_puiThis->display(e_display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //}





   bool application::save_all_modified()
   {
      /*      if (m_pdocmanager != nullptr)
      return document_manager()->save_all_modified();*/
      return TRUE;
   }



   //   bool application::OnDDECommand(char * pszCommand)
   //
   //   {
   //      /*      if (m_pdocmanager != nullptr)
   //      return document_manager()->OnDDECommand(pszCommand);
   //
   //      else*/
   //      return FALSE;
   //   }



   void application::EnableModeless(bool bEnable)
   {
      DoEnableModeless(bEnable);
   }

   void application::DoEnableModeless(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif

      // no-op if main window is nullptr or not a frame_window
      /*   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
      if (pMainWnd == nullptr || !pMainWnd->is_frame_window())
      return;*/

#ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
      /*xxx
      ASSERT_KINDOF(frame_window, pMainWnd);
      __pointer(::user::frame_window) pFrameWnd = (__pointer(::user::frame_window))pMainWnd;
      if (pFrameWnd->m_pNotifyHook != nullptr)
      pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
      */
#endif
   }












   void application::RegisterShellFileTypes(bool bCompat)
   {
      //ENSURE(m_pdocmanager != nullptr);
      //      document_manager()->RegisterShellFileTypes(bCompat);
   }

   void application::UnregisterShellFileTypes()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //    document_manager()->UnregisterShellFileTypes();
   }


   i32 application::get_open_document_count()
   {
      //ENSURE(m_pdocmanager != nullptr);
      //  return document_manager()->get_open_document_count();
      return 0;
   }


   // This is apex API library.
   //
   //
   //
   //
   //
   //
   //
   //

   /////////////////////////////////////////////////////////////////////////////
   // application Settings Helpers


   void application::SetRegistryKey(const char* pszRegistryKey)

   {
      //ASSERT(m_pszRegistryKey == nullptr);
      //ASSERT(pszRegistryKey != nullptr);

      //ASSERT(m_strAppName.has_char());

      ////bool bEnable = __enable_memory_tracking(FALSE);
      //free((void *)m_pszRegistryKey);
      //m_pszRegistryKey = strdup(pszRegistryKey);

      //free((void *)m_pszProfileName);
      //m_pszProfileName = strdup(m_strAppName);
      ////__enable_memory_tracking(bEnable);
   }

   void application::SetRegistryKey(::u32 nIDRegistryKey)
   {
      //UNREFERENCED_PARAMETER(nIDRegistryKey);
      //ASSERT(m_pszRegistryKey == nullptr);
      //::exception::throw_not_implemented();
      ///*char szRegistryKey[256];
      //VERIFY(::apex::LoadString(nIDRegistryKey, szRegistryKey));
      //SetRegistryKey(szRegistryKey);*/
   }


#ifdef WINDOWS_DESKTOP

   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   // creating it if it doesn't exist
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetAppRegistryKey()
   {
      //ASSERT(m_pszRegistryKey != nullptr);
      //ASSERT(m_pszProfileName != nullptr);

      //HKEY hAppKey = nullptr;
      //HKEY hSoftKey = nullptr;
      //HKEY hCompanyKey = nullptr;
      //if(RegOpenKeyEx(HKEY_CURRENT_USER,"software",0,KEY_WRITE | KEY_READ,
      //   &hSoftKey) == ERROR_SUCCESS)
      //{
      //   ::u32 dw;
      //   if(RegCreateKeyEx(hSoftKey,m_pszRegistryKey,0,REG_NONE,
      //      REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //      &hCompanyKey,&dw) == ERROR_SUCCESS)
      //   {
      //      RegCreateKeyEx(hCompanyKey,m_pszProfileName,0,REG_NONE,
      //         REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //         &hAppKey,&dw);
      //   }
      //}
      //if(hSoftKey != nullptr)
      //   RegCloseKey(hSoftKey);
      //if(hCompanyKey != nullptr)
      //   RegCloseKey(hCompanyKey);

//      return hAppKey;
      return nullptr;
   }

   // returns key for:
   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\pszSection

   // creating it if it doesn't exist.
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY application::GetSectionKey(const char* pszSection)
   {

      ASSERT(pszSection != nullptr);

      HKEY hSectionKey = nullptr;

      HKEY hAppKey = GetAppRegistryKey();

      if (hAppKey == nullptr)
      {

         return nullptr;

      }

      DWORD dw;

      RegCreateKeyExW(hAppKey, wstring(pszSection), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, nullptr, &hSectionKey, &dw);

      RegCloseKey(hAppKey);

      return hSectionKey;

   }

#endif

   /*   ::u32 application::GetProfileInt(const char * pszSection, const char * pszEntry,

   i32 nDefault)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr) // use registry
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return nDefault;
   u32 dwValue;
   u32 dwType;
   u32 dwCount = sizeof(u32);
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (byte *)&dwValue, &dwCount);
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_DWORD);
   ASSERT(dwCount == sizeof(dwValue));
   return (::u32)dwValue;
   }
   return nDefault;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   return ::GetPrivateProfileInt(pszSection, pszEntry, nDefault,

   m_pszProfileName);
   }
   }

   string application::GetProfileString(const char * pszSection, const char * pszEntry,

   const char * pszDefault)

   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return pszDefault;

   string strValue;
   u32 dwType=REG_NONE;
   u32 dwCount=0;
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   nullptr, &dwCount);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   (byte *)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
   strValue.ReleaseBuffer();
   }
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   return strValue;
   }
   return pszDefault;

   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   if (pszDefault == nullptr)

   pszDefault = "";   // don't pass in nullptr

   char szT[4096];
   u32 dw = ::GetPrivateProfileString(pszSection, pszEntry,

   pszDefault, szT, _countof(szT), m_pszProfileName);

   ASSERT(dw < 4095);
   return szT;
   }
   }

   bool application::GetProfileBinary(const char * pszSection, const char * pszEntry,

   byte** ppData, ::u32* pBytes)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   ASSERT(ppData != nullptr);
   ASSERT(pBytes != nullptr);
   *ppData = nullptr;
   *pBytes = 0;
   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   {
   return FALSE;
   }

   // ensure destruction

   // linux ::apex::CRegKey rkSecKey(hSecKey);

   u32 dwType=0;
   u32 dwCount=0;
   ::i32 lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType, nullptr, &dwCount);

   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = new byte[*pBytes];
   lResult = RegQueryValueEx(hSecKey, (char *)pszEntry, nullptr, &dwType,

   *ppData, &dwCount);
   }
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   return TRUE;
   }
   else
   {
   delete [] *ppData;
   *ppData = nullptr;
   }
   return FALSE;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   string str = GetProfileString(pszSection, pszEntry, nullptr);

   if (str.is_empty())
   return FALSE;
   ASSERT(str.get_length()%2 == 0);
   iptr nLen = str.get_length();
   *pBytes = ::u32(nLen)/2;
   *ppData = new byte[*pBytes];
   for (i32 i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (byte)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return TRUE;
   }
   }


   bool application::WriteProfileInt(const char * pszSection, const char * pszEntry,

   i32 nValue)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   ::i32 lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_DWORD,

   (byte *)&nValue, sizeof(nValue));
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   char szT[16];
   _stprintf_s(szT, _countof(szT), "%d", nValue);
   return ::WritePrivateProfileString(pszSection, pszEntry, szT,

   m_pszProfileName);
   }
   }

   bool application::WriteProfileString(const char * pszSection, const char * pszEntry,

   const char * pszValue)

   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
   if (pszEntry == nullptr) //delete whole department

   {
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == nullptr)
   return FALSE;
   lResult = ::RegDeleteKey(hAppKey, pszSection);

   RegCloseKey(hAppKey);
   }
   else if (pszValue == nullptr)

   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   // necessary to cast away const below
   lResult = ::RegDeleteValue(hSecKey, (char *)pszEntry);

   RegCloseKey(hSecKey);
   }
   else
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_SZ,

   (byte *)pszValue, (lstrlen(pszValue)+1)*sizeof(char));

   RegCloseKey(hSecKey);
   }
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
   return ::WritePrivateProfileString(pszSection, pszEntry, pszValue,

   m_pszProfileName);
   }
   }

   bool application::WriteProfileBinary(const char * pszSection, const char * pszEntry,

   byte * pData, ::u32 nBytes)
   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   ::i32 lResult;
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_BINARY,

   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   char * psz = new char[nBytes*2+1];

   ::u32 i;
   for (i = 0; i < nBytes; i++)
   {
   psz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble

   psz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble

   }
   psz[i*2] = 0;


   ASSERT(m_pszProfileName != nullptr);

   bool bResult = WriteProfileString(pszSection, pszEntry, psz);

   delete[] psz;

   return bResult;
   }

   #include "framework.h"*/




   /*   property_set & application::propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   return m_mapObjectSet[pobject];
   }

   property_set * application::existing_propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   auto point = m_mapObjectSet.plookup(pobject);
   if(point == nullptr)
   return nullptr;
   return &point->m_value;
   }*/



   bool application::does_launch_window_on_startup()
   {

      return true;

   }


   bool application::activate_app()
   {

      //if (m_puiMain1 != nullptr)
      //{

      //   m_puiMain1->m_puiThis->display(SW_SHOWNORMAL);

      //}

      return true;

   }


   //void application::term()
   //{


   //   try
   //   {

   //      if (m_puiMain1 == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the application's windows before closing all the documents
   //      m_puiMain1->m_puiThis->display(e_display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(FALSE);


   //      m_puiMain1->m_puiThis->order(zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puiMain1->m_puiThis->display(e_display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //   try
   //   {

   //      ::apex::application::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   //::user::interaction* application::get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate)
   //{

   //   ::user::interaction* puiParent = nullptr;

   //   if (puiParent == nullptr)
   //   {
   //      puiParent = dynamic_cast <::user::interaction*> (pcreate->m_puserinteractionParent);
   //   }

   //   //      if (puiParent == nullptr && pcreate->m_papplicationbias.is_set())
   //   //      {
   //   //         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_papplicationbias->m_puserinteractionParent);
   //   //      }

   //         //if(puiParent == nullptr && m_psession != nullptr && m_psession->m_psession != nullptr && !pcreate->m_bClientOnly
   //         /*if (puiParent == nullptr && m_psession != nullptr && m_psession != nullptr
   //               && !pcreate->m_bOuterPopupAlertLike && m_psession != dynamic_cast < session * > (this))
   //         {
   //            puiParent = psession->get_request_parent_ui(pinteraction, pcreate);
   //         }*/

   //   return puiParent;

   //}







   void application::_001OnFileNew(::message::message* pmessage)
   {

      payload varFile;

      payload varQuery;

      varQuery["command"] = "new_file";

      request_file(varFile, varQuery);

      pmessage->m_bRet = true;

   }



   //   bool application::on_open_document_file(payload varFile)
   //   {
   //
   //      return _001OpenDocumentFile(varFile);
   //
   //   }

   //::user::document* application::_001OpenDocumentFile(payload varFile)
   //{

   //   request_file(varFile);

   //   return varFile["document"].cast < ::user::document >();

   //}


   //bool application::_001OnDDECommand(const char* pcsz)

   //{
   //   ::exception::throw_not_implemented();
   //   //return m_pimpl->_001OnDDECommand(pcsz);


   //   return false;
   //}

   //   ::apex::file_system & application::file_system()
   // {
   //  return m_spfilesystem;
   //}







//   ::user::interaction * application::get_desktop_window()
//   {
//#if defined(_UWP) || defined(APPLEOS)
//      __throw(todo());
//      /*#elif defined(LINUX)
//
//      //      sync_lock sl(&user_mutex());
//
//      xdisplay pdisplay.
//      pdisplay.open(nullptr) = x11_get_display();
//
//      oswindow window(pdisplay, DefaultRootWindow(pdisplay));
//
//      XCloseDisplay(pdisplay);
//
//      return window_from_os_data(window);
//      */
//#else
//
//      return System.ui_from_handle(::get_desktop_window());
//
//#endif
//
//   }





   //void application::assert_valid() const
   //{
   //   thread::assert_valid();


   //   if (::get_task() != (thread*)this)
   //      return;     // only do subset if called from different thread

   //   ASSERT(::get_task() == this);
   //   //ASSERT(afxCurrentInstanceHandle == m_hInstance);

   //   /*      if (m_pdocmanager != nullptr)
   //   ASSERT_VALID(m_pdocmanager);*/
   //}

//   void application::dump(dump_context& dumpcontext) const
//   {
//
//      ::apex::application::dump(dumpcontext);
//
//      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
//      dumpcontext << "\nm_pszHelpFilePath = " << m_strHelpFilePath;
//      dumpcontext << "\nm_pszProfileName = " << m_strProfileName;
//
//#ifdef WINDOWS
//      dumpcontext << "\nm_hDevMode = " << (void*)m_hDevMode;
//      dumpcontext << "\nm_hDevNames = " << (void*)m_hDevNames;
//#endif
//
//      dumpcontext << "\nm_dwPromptContext = " << (::u32)m_dwPromptContext;
//      //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;
//
//
//      /*      if (m_pdocmanager != nullptr)
//      document_manager()->dump(dumpcontext);*/
//
//      dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
//      dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;
//
//      dumpcontext << "\n";
//   }


   //void application::install_message_routing(::channel* pchannel)
   //{

   //   apex::application::install_message_routing(pchannel);

   //   connect_command("switch_context_theme", &application::_001OnSwitchContextTheme);

   //}


   bool application::base_support()
   {

      //if(!application::base_support())
      // return false;

      if (m_strBaseSupportId.is_empty())
      {

         property_set propertyset;

         dialog_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);

         return false;

      }

      return true;
   }


   //string application::sync_message_box(const string & pszMatter, property_set & propertyset)
   //{
   //
   //   UNREFERENCED_PARAMETER(propertyset);
   //
   //   UNREFERENCED_PARAMETER(pszMatter);
   //
   //   return "";

   //}


   //::estatus application::bergedge_start()
   //{

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}


#ifdef WINDOWS_DESKTOP


   bool Is_Vista_or_Later()
   {
      OSVERSIONINFOEX osvi;
      DWORDLONG dwlConditionMask = 0;
      byte op = VER_GREATER_EQUAL;

      // Initialize the OSVERSIONINFOEX structure.

      ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      osvi.dwMajorVersion = 6;
      //   osvi.dwMinorVersion = 1;
      //   osvi.wServicePackMajor = 0;
      //   osvi.wServicePackMinor = 0;

      // Initialize the condition mask.

      VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

      // Perform the test.

      return VerifyVersionInfo(
         &osvi,
         VER_MAJORVERSION | VER_MINORVERSION |
         VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
         dwlConditionMask) != FALSE;
   }


#endif


   void application::pre_translate_message(::message::message* pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (pbase->m_id == WM_USER + 124 && pbase->m_playeredUserPrimitive == nullptr)
      {

         /*

         OnMachineEvent((flags < machine_event::e_flag> *) pmsg->lParam);
         delete (flags < machine_event::e_flag> *) pmsg->lParam;

         */

         pbase->m_bRet = true;

         return;

      }

      return thread::pre_translate_message(pmessage);

   }


   //void application::on_create_split_view(::user::split_view* psplit)
   //{

   //}


   void application::EnableShellOpen()
   {

#ifdef WINDOWS

      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once

      if (m_atomApp != 0 || m_atomSystemTopic != 0)
      {

         return;

      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // i16 file name so we need to use the i16 file name.
      string strShortName;

      strShortName = Context.file().module();

      // strip out path
      //string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      //char * pszFileName = strFileName.GetBuffer();
      //::PathRemoveExtension(pszFileName);
      //strFileName.ReleaseBuffer();

      //      m_atomApp = ::GlobalAddAtom(strFileName);
      //    m_atomSystemTopic = ::GlobalAddAtom("system");

#endif

   }


   //__pointer(::user::interaction) application::uie_from_point(const ::point& point)
   //{

   //   user::interaction_pointer_array wnda = *m_puiptraFrame;

   //   user::oswindow_array oswindowa;

   //   oswindowa = wnda.get_hwnda();

   //   user::window_util::SortByZOrder(oswindowa);

   //   for (i32 i = 0; i < oswindowa.get_count(); i++)
   //   {

   //      __pointer(::user::interaction) puieWindow = wnda.find_first(oswindowa[i]);

   //      __pointer(::user::interaction) puie = puieWindow->_001FromPoint(point);

   //      if (puie != nullptr)
   //      {

   //         return puie;

   //      }

   //   }

   //   return nullptr;

   //}


   //bool application::on_install()
   //{

   //   if (!::apex::application::on_install())
   //   {

   //      return false;

   //   }

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}


   bool application::on_run_install()
   {

      if (m_strId == "session" || m_strAppName == "session")
      {

         if (is_false("session_start"))
         {

            ::parallelization::finish(&System);

         }

      }
      else
      {

         ::parallelization::finish(&System);

      }

      return true;

   }


   //bool application::on_uninstall()
   //{

   //   bool bOk = ::apex::application::on_uninstall();

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return bOk;

   //}


   bool application::on_run_uninstall()
   {

      if (m_strId == "session")
      {

         if (is_false("session_start"))
         {

            ::parallelization::finish(&System);

         }

      }
      else
      {

         ::parallelization::finish(&System);

      }

      return true;

   }


   void application::on_application_signal(::message::message* pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   //::apex::printer* application::get_printer(const char* pszDeviceName)
   //{

   //   return nullptr;

   //}


   //bool application::set_keyboard_layout(const char* pszPath, const ::action_context& context)
   //{

   //   return psession->keyboard().load_layout(pszPath, context);

   //}


   //i32 application::track_popup_menu(const char* pszMatter, const ::point& point, __pointer(::user::interaction) puie)
   //{

   //   UNREFERENCED_PARAMETER(pszMatter);
   //   UNREFERENCED_PARAMETER(point);
   //   UNREFERENCED_PARAMETER(puie);

   //   return 1;

   //}


   bool application::get_fs_size(string& strSize, const char* pszPath, bool& bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.Empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.Format("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.Format("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.Format("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.Format("1 KB");

      }
      else
      {

         strSize.Format("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool application::get_fs_size(i64& i64Size, const char* pszPath, bool& bPending)
   {
      return false;
      //db_server * pcentral = dynamic_cast <db_server *> (&System.m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

   }


   void application::set_title(const char* pszTitle)
   {

      auto psession = Session;

      psession->set_app_title(m_strAppName, pszTitle);

   }


   //bool application::_001CloseApplicationByUser(__pointer(::user::interaction) pwndExcept)
   //{

   //   // Closing just this application.
   //   // It is different of a system exit.
   //   // System (a single ca2 process) can host
   //   // multiple ca2 application objects.

   //   // attempt to save all documents
   //   if (!save_all_modified())
   //   {

   //      return false;     // don't close it

   //   }

   //   // hide the application's windows before closing all the documents
   //   HideApplication();

   //   close(::apex::end_app);

   //   return true;

   //}


   oswindow application::get_ca2_app_wnd(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

      return nullptr;

   }


   i32 application::send_simple_command(const char* psz, void* osdataSender)
   {
      string strApp;
      string_array stra;
      stra.add_tokens(psz, "::", true);
      if (stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if (oswindow != nullptr)
         {
            return send_simple_command((void*)oswindow, psz, osdataSender);
         }
      }
      return -1;
   }


   i32 application::send_simple_command(void* osdata, const char* psz, void* osdataSender)
   {
#ifdef WINDOWS_DESKTOP
      ::oswindow oswindow = (::oswindow) osdata;
      if (!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      __memset(&cds, 0, sizeof(cds));
      cds.dwData = 888888;
      cds.cbData = (u32)strlen(psz);
      cds.lpData = (PVOID)psz;

      return (i32)SendMessage(oswindow, WM_COPYDATA, (WPARAM)osdataSender, (LPARAM)&cds);
#else
      __throw(todo());
#endif
   }


   void application::ensure_app_interest()
   {

//#ifndef _UWP
//
//      for (i32 i = 0; i < m_straAppInterest.get_count(); i++)
//      {
//         if (m_straAppInterest[i] != m_strAppName && !::is_window(m_mapAppInterest[m_straAppInterest[i]]))
//         {
//            System.assert_running_local(m_straAppInterest[i]);
//         }
//      }
//
//#else
//
//      //__throw(todo());
//
//#endif

   }




   //::apex::application * application::get_context_system()
   //{

   //   return ::object::get_context_system();

   //}


















   /*
   __pointer(::apex::application) application::assert_running(const char * pszAppId)
   {


   __pointer(::apex::application) papp = nullptr;


   try
   {

   bool bFound = false;

   for(i32 i  = 0; i < System.m_appptra.get_count(); i++)
   {
   try
   {

   papp = System.m_appptra(i);

   if(papp->m_strAppName == pszAppId)
   {
   bFound = true;
   break;
   }

   }
   catch(...)
   {
   }

   }

   bool bCreate = !bFound;

   if(bFound)
   {

   bool bRunning = false;

   try
   {
   if(papp->is_running())
   {
   bRunning = true;
   }
   }
   catch(...)
   {
   }


   if(bCreate)
   {

   __pointer(::create) spcreate(e_create);

   papp = psession->start_application("application", pszAppId, spcreate);

   }

   }
   catch(const ::exit_exception & e)
   {

   __throw(e);

   }
   catch(const ::exception_pointer pe)
   {

   if(!Application.on_run_exception((::exception::exception &) e))
   __throw(exit_exception());

   }
   catch(...)
   {

   papp = nullptr;

   }


   return papp;

   }
   */





   //typedef  void (* PFN_factory_exchange)();
















   void application::data_on_after_change(::database::client* pclient, const ::database::key& key, const payload& payload, ::promise::subject * psubject)
   {


   }


   __pointer(::apex::application) application::create_platform(::apex::session* psession)
   {

      return __new(::apex::session);

   }


   //void application::on_change_cur_sel(::user::tab* ptab)
   //{



   //}


   bool application::_001OnAgreeExit()
   {

      if (!save_all_modified())
      {

         return false;

      }

      return true;

   }


   //void application::_001OnFranceExit()
   //{

   //   ::apex::application::_001OnFranceExit();

   //}


   //void application::prepare_form(id id, ::form_document* pdocument)
   //{



   //}


   void application::report_error(::exception::exception* pexception, int iMessageFlags, const char* pszTopic)
   {

      string strMessage;

      strMessage += pszTopic;

      strMessage += " : ";

      strMessage += pexception->get_message();

      __throw(todo("interaction"));

      //m_puiMain1->message_box(strMessage + ::enum_message_box(iMessageFlags));

   }


   bool application::on_close_frame_window(::user::frame* pframe)
   {

      __throw(todo("interaction"));

      //if (pframe->m_bCloseApplicationIfLastVisibleFrame)
      //{

      //   if (GetVisibleTopLevelFrameCountExcept(pframe) <= 0)
      //   {

      //      pframe->DestroyWindow();

      //      _001CloseApplication();

      //   }
      //   else
      //   {

      //      pframe->hide();

      //   }

      //}
      //else
      //{

      //   pframe->DestroyWindow();

      //}

      return true;

   }


   //::type application::control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype)
   //{

   //   string str(id);

   //   if (str.begins_ci("combo_"))
   //   {

   //      econtroltype = ::user::control_type_combo_box;

   //      return __type(::user::combo_box);

   //   }
   //   else if (str.begins_ci("check_") || str.begins_ci("checkbox_"))
   //   {

   //      econtroltype = ::user::control_type_check_box;

   //      return __type(::user::check_box);

   //   }
   //   else if (str.begins_ci("still_"))
   //   {

   //      econtroltype = ::user::control_type_static;

   //      return __type(::user::still);

   //   }
   //   else if (str.begins_ci("label_"))
   //   {

   //      econtroltype = ::user::control_type_static;

   //      return __type(::user::still);

   //   }
   //   else if (str.begins_ci("edit_"))
   //   {

   //      econtroltype = ::user::control_type_edit_plain_text;

   //      return __type(::user::plain_edit);

   //   }
   //   else if (str.begins_ci("button_"))
   //   {

   //      econtroltype = ::user::control_type_button;

   //      return __type(::user::button);

   //   }

   //   return ::apex::application::control_type_from_id(id, econtroltype);

   //}


   string application::get_theme()
   {

      return "";

   }


   estatus application::initialize_contextualized_theme()
   {

      return ::success;

   }


   //void application::on_change_theme()
   //{


   //}


   void application::_001OnSwitchContextTheme(::message::message* pmessage)
   {

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      //if (!m_ptheme)
      //{

      //   return;

      //}

      //if (m_bContextTheme)
      //{

      //   m_ptheme->switch_context_theme();

      //}

   }


   //application::application()
   //{

   //   create_factory < ::user::user >();

   //   //m_bBaseProcessInitialize         = false;
   //   //m_bBaseProcessInitializeResult   = false;

   //   //m_bBaseInitialize1               = false;
   //   //m_bBaseInitialize1Result         = false;

   //   //m_bBaseInitialize                = false;
   //   //m_bBaseInitializeResult          = false;

   //   //m_bBaseInitializeInstance        = false;
   //   //m_bBaseInitializeInstanceResult  = false;




   //}

   //application::~application()
   //{

   //}


   //::estatus application::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::apex::application::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}

   //   void application::install_message_routing(::channel * pchannel)
   //   {
   //
   //
   //
   //   }


      //void application::task(::machine * pchange)
      //{

      //   ::apex::application::task(ptask);

      //   if (ptask->m_bRet)
      //   {
      //
      //      return;

      //   }
      //
      //   ::user::form_callback::task(ptask);

      //   if (ptask->m_bRet)
      //   {

      //      return;

      //   }

      //}


   //::estatus application::process_init()
   //{

   //   if (::apex::application::process_init())
   //   {

   //      return true;

   //   }

   //   return true;

   //}


   //::estatus application::init_instance()
   //{

   //   if (!::apex::application::init_instance())
   //   {

   //      return false;

   //   }

   //   auto estatus = create_impact_system();

   //   if (failed(estatus))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   ::estatus     application::create_impact_system()
   {

      return ::success;

   }


   void application::process_message_filter(i32 code, ::message::message* pmessage)
   {

      //if (pmessage == nullptr)
      //   return;   // not handled

      //SCAST_PTR(::message::base, pbase, pmessage);

      //__pointer(::user::frame_window) pTopFrameWnd;
      ////::user::interaction * pMainWnd;
      //::user::interaction* pMsgWnd;
      //switch (code)
      //{
      //   //case MSGF_DDEMGR:
      //   // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //   //  never call the next hook.
      //   // By returning FALSE, the message will be dispatched
      //   //  instead (the default behavior).
      //   //return;

      //case MSGF_MENU:

      //   pMsgWnd = dynamic_cast <::user::interaction*> (pbase->m_puserinteraction);

      //   if (pMsgWnd != nullptr)
      //   {
      //      pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
      //      if (pTopFrameWnd != nullptr && pTopFrameWnd->IsTracking() &&
      //         pTopFrameWnd->m_bHelpMode)
      //      {
      //         //pMainWnd = __get_main_window();
      //         //if((m_puiMain != nullptr) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
      //         //{
      //         //   //                  pMainWnd->SendMessage(e_message_command, ID_HELP);
      //         //   pbase->m_bRet = true;
      //         //   return;
      //         //}
      //      }
      //   }
      //   // fall through...

      //case MSGF_DIALOGBOX:    // handles message boxes as well.
      //   //pMainWnd = __get_main_window();
      //   if (code == MSGF_DIALOGBOX && m_puiActive != nullptr &&
      //      pbase->m_id >= e_message_key_first && pbase->m_id <= e_message_key_last)
      //   {
      //   }
      //   break;
      //}
      //// default to not handled

   }





















   /*string application::get_cred(const string & strRequestUrlParam,const ::rect & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::account::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_char() && strPassword.has_char())
         return "ok";

      if(!bInteractive)
         return "failed";

      __pointer(::account::simple_ui) pinteraction;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string(::dir::system() / "config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

         strRequestUrl = "https://account.ca2.cc/";

      }

      pinteraction = __new(::account::simple_ui(this,strRequestUrl));

      pinteraction->m_login.m_peditUser->set_window_text(strUsername);

      pinteraction->m_login.m_ppassword->set_window_text("");

      string strResult = pinteraction->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pinteraction->DestroyWindow();

      ::account::set_cred(this,strToken,strUsername,strPassword);

      return strResult;

   }*/


   //__pointer(::user::user) application::create_user()
   //{

   //   return __new(::user::user);

   //}


   ::estatus application::on_thread_on_idle(::thread* pthread, ::i32 lCount)
   {

      __throw(todo("interaction"));
      //if (lCount <= 0)
      //{

      //   __pointer(::user::interaction) pinteraction;

      //   while (get_frame(pinteraction))
      //   {
      //      //::user::interaction * pinteraction = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
      //      bool bOk = false;
      //      try
      //      {

      //         bOk = pinteraction != nullptr && pinteraction->is_window_visible();
      //      }
      //      catch (...)
      //      {
      //      }
      //      if (!bOk)
      //      {
      //         //   try
      //         //   {
      //         //      Application.remove_frame(pinteraction);
      //         //   }
      //         //   catch(...)
      //         //   {
      //         //   }
      //         //   try
      //         //   {
      //         //      psession->remove_frame(pinteraction);
      //         //   }
      //         //   catch(...)
      //         //   {
      //         //   }
      //         //   try
      //         //   {
      //         //      System.remove_frame(pinteraction);
      //         //   }
      //         //   catch(...)
      //         //   {
      //         //   }
      //      }
      //      else
      //      {
      //         //               sl.unlock();
      //         try
      //         {
      //            pinteraction->send_message(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
      //         }
      //         catch (...)
      //         {

      //         }
      //         //             sl.lock();
      //      }
      //   }


      //}
      //else if (lCount >= 0)
      //{
      //}

      //return lCount < 0;  // nothing more to do if lCount >= 0

   }





   //void application::on_create_impact(::user::impact_data* pimpactdata)
   //{


   //}


   ::estatus application::process_message()
   {

      return ::thread::process_message();

   }


   //void application::SetCurrentHandles()
   //{

   //   ::apex::application::SetCurrentHandles();

   //}


   //void application::term_application()
   //{

   //   try
   //   {

   //      apex::application::term_application();

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   //::draw2d::icon* application::set_icon(object* pobject, ::draw2d::icon* picon, bool bBigIcon)
   //{

   //   ::draw2d::icon* piconOld = get_icon(pobject, bBigIcon);

   //   if (bBigIcon)
   //   {

   //      pobject->value("big_icon") = (__pointer(object)) picon;

   //   }
   //   else
   //   {

   //      pobject->value("small_icon") = (__pointer(object)) picon;

   //   }

   //   return piconOld;

   //}


   //::draw2d::icon* application::get_icon(object* pobject, bool bBigIcon) const
   //{

   //   if (bBigIcon)
   //   {

   //      return const_cast <object*> (pobject)->cast < ::draw2d::icon >("big_icon");

   //   }
   //   else
   //   {

   //      return const_cast <object*> (pobject)->cast < ::draw2d::icon >("small_icon");

   //   }

   //}


   //void application::on_control_event(::user::control_event* pevent)
   //{

   //   if (pevent->m_eevent == ::user::event_initialize_control)
   //   {

   //      if (pevent->m_puie->m_id == __id(system_startup_checkbox))
   //      {

   //         try
   //         {
   //            __pointer(::user::check) pcheck = pevent->m_puie;

   //            if (pcheck.is_set())
   //            {

   //               pcheck->_001SetCheck(
   //                  Context.os().is_user_auto_start(get_executable_appid()),
   //                  ::source_initialize);

   //            }
   //         }
   //         catch (...)
   //         {

   //         }

   //      }

   //   }
   //   else if (pevent->m_eevent == ::user::event_set_check)
   //   {

   //      if (pevent->m_puie->m_id == __id(system_startup_checkbox)
   //         && pevent->m_actioncontext.is_user_source())
   //      {

   //         try
   //         {

   //            __pointer(::user::check) pcheck = pevent->m_puie;

   //            if (pcheck.is_set())
   //            {

   //               Context.os().register_user_auto_start(
   //                  get_executable_appid(),
   //                  get_executable_path(),
   //                  pcheck->echeck() == ::check_checked);

   //            }

   //            pevent->m_bRet = true;

   //            return;

   //         }
   //         catch (...)
   //         {

   //         }

   //      }

   //   }

   //}


   //::user::interaction* application::create_menu_interaction()
   //{

   //   return __new(::user::button);

   //}


   //__pointer(::user::document) application::defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   //{

   //   auto pcontroller = ::apex::application::defer_create_view(strView, puiParent, ewindowflag, id);

   //   if (pcontroller)
   //   {

   //      return pcontroller;

   //   }

   //   return nullptr;

   //}


   void application::on_song_added(const string& str)
   {

   }


   //::type application::control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype)
   //{

   //
   //}


   //::form_property_set * application::get_form_property_set()
   //{

   //   auto pset = ::user::form_callback::get_form_property_set();

   //   if (::is_set(pset))
   //   {

   //      return pset;

   //   }

   //   return this;

   //}

   string application::get_visual_studio_build()
   {

      ::file::path path = dir::config() / "programming/vs_build.txt";

      string strBuild = Context.file().as_string(path);

      strBuild.trim();

      return strBuild;

   }


   string application::as_string(const payload& payload)
   {

      if (payload.get_type() == ::type_string)
      {

         if (is_url(payload))
         {

            return file().as_string(payload.get_file_path());

         }

      }

      return payload.get_string();

   }


   string application::sound_path(const char* psz)
   {

      string strFileName = string(psz) + string(".wav");

      string strFilePath = dir().matter(strFileName);

      return strFilePath;

   }


   string application::get_default_playlist_path()
   {

      return "playlist/default";

   }


   //bool application::do_prompt_file_name(payload& varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument)
   //{

   //   __throw(todo("core and os"));

   //   return false;

   //}




   void application::close(::apex::enum_end eend)
   {

      if (eend == ::apex::e_end_close)
      {

         return;

      }

      m_ethreadClose = thread_application;

      //if (get_context_session())
      //{

      //   if (psession->m_pdocmanager)
      //   {

      //      psession->m_pdocmanager->close_all_documents(true);

      //   }

      //}

      if (eend == ::apex::e_end_app)
      {

         finish(get_context());

         return;

      }

      if (eend == ::apex::e_end_session)
      {

         try
         {

            if (get_context_session())
            {

               auto psession = Session;

               psession->finish(get_context());

            }

         }
         catch (...)
         {

         }

         return;

      }


      if (eend == ::apex::e_end_system)
      {

         try
         {

            if (get_context_system())
            {

               System.finish(get_context());

            }

         }
         catch (...)
         {

         }

      }

   }


} // namespace apex
