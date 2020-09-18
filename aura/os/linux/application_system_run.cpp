#include "framework.h"
#include "_user.h"
#include <gio/gio.h>
#include "third/sn/sn.h"
#include "apex/platform/app_core.h"
#include "bloat_pad.h"

extern ::app_core * g_pappcore;

void os_post_quit();
Display * x11_get_display();

CLASS_DECL_AURA i32 ca2_main();



gboolean linux_start_system(gpointer data);



void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

   __throw(::exception::exception());

}


void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
{

   UNREFERENCED_PARAMETER(uiCode);

   UNREFERENCED_PARAMETER(ppointers);

}


string ca2_command_line()
{

   return "";

}




#ifndef RASPBIAN

SnLauncheeContext* g_psncontext = nullptr;

void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);

namespace aura{

bool system::sn_start_context()
{


   Display * dpy = x11_get_display();

   SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);

   int iScreen = DefaultScreen(dpy);

   g_psncontext = sn_launchee_context_new(pd, iScreen, ::g_pappcore->m_strProgName);

   return true;

}


} // namespace aura

#endif // !RASPBIAN





//::estatus app_core::system_start()
//{
//
//   ::estatus estatus = system_pre_run();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   auto psystem = get_context_system();
//
//   psystem->add_ref(OBJ_REF_DBG_ARGS);
//
//   if (m_pmainstruct->m_bConsole)
//   {
//
//      psystem->get_context_session()->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->set_context_app(psystem->m_papplicationStartup);
//
//      psystem->get_context_session()->set_context(psystem->m_papplicationStartup);
//
//      psystem->set_context(psystem->m_papplicationStartup);
//
//   }
//
//
//
//   return estatus;
//
//}
#ifdef LINUX
i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
#endif


::estatus os_application_system_run(::aura::system * psystem)
{


//   ::estatus estatus = psystem->begin_synch();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//

   const char * pszName = psystem->m_strAppId;

   g_set_application_name(pszName);

   const char * pszPrgName = psystem->m_strProgName;

   g_set_prgname(pszPrgName);

   //auto idle_source = g_idle_source_new();

   //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);

   //g_source_attach(idle_source, g_main_context_default());

   //int c = 2;

   //const char * argv[]={"app", "--g-fatal-warnings"};

#if !defined(__SANITIZE_ADDRESS__)

   if(!gtk_init_check(&psystem->m_argc, &psystem->m_argv))
   {

      return ::error_failed;

   }

#endif

   if(!psystem->begin_synch())
   {

      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");

      return error_failed;

   }

   if(psystem->m_bUser)
   {

      if(!XInitThreads())
      {

         return false;

      }

      XSetErrorHandler(_c_XErrorHandler);

   }

   if(psystem->m_bGtkApp)
   {

      bloat_pad_run(psystem->m_strAppId, psystem->m_strProgName);

   }
   else
   {

//      g_set_application_name(psystem->m_strAppId);
//
//      g_set_prgname(psystem->m_strProgName);
//
//      //auto idle_source = g_idle_source_new();
//
//      //g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, nullptr);
//
//      //g_source_attach(idle_source, g_main_context_default());
//
//      //int c = 2;
//
//      //const char * argv[]={"app", "--g-fatal-warnings"};
//
//#if !defined(__SANITIZE_ADDRESS__)
//
//      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
//
//#endif

      gtk_main();

   }

   //::multithreading::post_quit_and_wait(get_context_system(), one_minute());

   return ::success;

}


void sn_start_context();


bool os_init_application()
{

   #ifndef RASPBIAN

    sn_start_context();

   #endif

   return true;

}


void os_term_application()
{

//   if(g_pappBloatPad != nullptr)
//   {
//
//      g_application_quit(G_APPLICATION(g_pappBloatPad));
//
//   }

}


gboolean gtk_quit_callback(gpointer data)
{

   gtk_main_quit();

   return FALSE;

}


void os_post_quit()
{

   auto idle_source = g_idle_source_new();

   g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);

   g_source_attach(idle_source, g_main_context_default());

}

::estatus     run_runnable(::generic * pobjectTask);


gboolean gdk_callback_run_runnable(gpointer pdata)
{

   run_runnable((generic *) pdata);

   return FALSE;

}


void gdk_branch(generic * prunnable, e_priority epriority)
{

   prunnable->add_ref(OBJ_REF_DBG_P_NOTE(nullptr, "gdk_branch"));

   auto idle_source = g_idle_source_new();

   g_source_set_priority(idle_source, G_PRIORITY_DEFAULT);

   g_source_set_callback(idle_source, &gdk_callback_run_runnable, prunnable, nullptr);

   g_source_attach(idle_source, g_main_context_default());

}


CLASS_DECL_AURA void main_branch(::generic * prunnable, e_priority epriority)
{

   prunnable->add_ref(OBJ_REF_DBG_P_NOTE(nullptr, "main_branch"));

   gdk_branch(prunnable, epriority);

}

namespace aura
{

   bool system::init_x11()
   {

      if(!XInitThreads())
      {

         return false;

      }

      XSetErrorHandler(_c_XErrorHandler);

      return true;

   }


 } // namespace aura
