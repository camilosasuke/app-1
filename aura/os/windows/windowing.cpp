﻿#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "windowing.h"
#include "top_level_enum.h"


#define ___TEMP_CLASS_NAME_SIZE 4096


//CLASS_DECL_AURA void defer_dock_application(int_bool bDock)
//{
//
//   UNREFERENCED_PARAMETER(bDock);
//
//}



CLASS_DECL_AURA int_bool os_init_windowing()
{

   return TRUE;

}


CLASS_DECL_AURA void os_term_windowing()
{

}


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}


//CLASS_DECL_AURA i64 oswindow_id(HWND hwnd)
//{
//
//   return (i64)hwnd;
//
//}

//
//CLASS_DECL_AURA int_bool is_window(oswindow oswindow)
//{
//
//   return ::IsWindow(oswindow);
//
//}


//CLASS_DECL_AURA bool get_gui_thread_info(PGUITHREADINFO pinfo)
//{
//
//   HWND hwndForeground = ::GetForegroundWindow();
//
//   if (hwndForeground == nullptr)
//   {
//
//      return false;
//
//   }
//
//   ::u32 dwThread = GetWindowThreadProcessId(hwndForeground, nullptr);
//
//   xxf_zero_pointer(pinfo);
//
//   pinfo->cbSize = sizeof(GUITHREADINFO);
//
//   if (!::GetGUIThreadInfo(dwThread, pinfo))
//   {
//
//      ::u32 dwLastError = ::GetLastError();
//
//      return false;
//
//   }
//
//   return true;
//
//}


//CLASS_DECL_AURA oswindow get_focus()
//{
//
//   GUITHREADINFO info;
//
//   if (!get_gui_thread_info(&info))
//   {
//
//      return nullptr;
//
//   }
//
//   return info.hwndFocus;
//
//}

//
//CLASS_DECL_AURA oswindow set_focus(oswindow oswindow)
//{
//
//   return ::SetFocus(oswindow);
//
//}

//
//CLASS_DECL_AURA oswindow get_active_window()
//{
//
//   //attach_thread_input_to_main_thread(true);
//
//   auto oswindow = ::GetActiveWindow();
//
//   //attach_thread_input_to_main_thread(false);
//
//   return oswindow;
//
//}
//
//
//CLASS_DECL_AURA oswindow set_active_window(oswindow oswindow)
//{
//
//   return ::SetActiveWindow(oswindow);
//
//}
//
//
//CLASS_DECL_AURA oswindow get_capture()
//{
//
//   return ::GetCapture();
//
//}

//
//CLASS_DECL_AURA oswindow set_capture(oswindow oswindow)
//{
//
//   return ::SetCapture(oswindow);
//
//}
//
//
//CLASS_DECL_AURA int_bool release_capture()
//{
//
//   return ::ReleaseCapture();
//
//}
//
//
//CLASS_DECL_AURA int_bool destroy_window(oswindow oswindow)
//{
//
//   return ::DestroyWindow(oswindow);
//
//}
//
//
//CLASS_DECL_AURA oswindow get_desktop_window()
//{
//
//   return ::GetDesktopWindow();
//
//}
//
//
//CLASS_DECL_AURA oswindow get_window(oswindow oswindow, int iWindow)
//{
//
//   return ::GetWindow(oswindow, iWindow);
//
//}



// void update_session_cursor(class user::interaction_impl * puiimpl)
// {

//    __pointer(::windows::interaction_impl) pimpl = puiimpl;

//    if (pimpl.is_set())
//    {

//       return;

//    }

//    Sess(puiimpl->get_context_application()).get_cursor_pos(puiimpl->m_pointCursor);

// }

//CLASS_DECL_AURA int_bool show_window(oswindow oswindow, int iShowCmd)
//{
//
//   return ::ShowWindow(oswindow, iShowCmd);
//
//}


/// from top to bottom
CLASS_DECL_AURA __pointer(::user::oswindow_array) get_top_level_windows(bool bDesktop, bool bVisible)
{

   /// from top to bottom
   top_level_enum toplevelenum(bDesktop, bVisible);

   return toplevelenum.m_poswindowa;

}


top_level_enum::top_level_enum(bool bDesktop, bool bVisible) :
   m_bVisible(bVisible)
{

   __construct_new(m_poswindowa);

   if (bDesktop)
   {

      ::EnumDesktopWindows(nullptr, &::top_level_enum::EnumWindowsProc, (LPARAM)this);

   }
   else
   {

      ::EnumWindows(&::top_level_enum::EnumWindowsProc, (LPARAM)this);

   }


}


top_level_enum::~top_level_enum()
{


}


BOOL CALLBACK top_level_enum::EnumWindowsProc(oswindow oswindow, LPARAM lParam)
{

   top_level_enum * ptoplevelenum = (top_level_enum *) lParam;

   if (ptoplevelenum->m_bVisible && !IsWindowVisible(oswindow))
   {

      return true;

   }

   ptoplevelenum->m_poswindowa->add(oswindow);

   return true;

}


int_bool point_is_window_origin(POINT32 ptHitTest, oswindow oswindowExclude, int iMargin)
{

   auto poswindowa = get_top_level_windows();

   if (poswindowa->is_empty())
   {

      return false;

   }

   ::rect rectWindow;

   for(auto & oswindow : *poswindowa)
   {

      if(oswindow != oswindowExclude)
      {

         if (!IsWindowVisible(oswindow))
         {

            continue;

         }

         if (::GetWindowRect(oswindow, rectWindow))
         {

            ::rect rectHitTest;
            
            rectHitTest.set(rectWindow.origin(), ::size());

            rectHitTest.inflate(iMargin + 1);

            if (rectHitTest.contains(ptHitTest))
            {

               return true;

            }

            //return true;

         }

      }

   }

   return false;

}




void window_create_caret(oswindow oswindow, HBITMAP hbitmap)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, hbitmap, 0, 0);

}

void window_create_solid_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, (HBITMAP)nullptr, nWidth, nHeight);

}

void window_create_gray_caret(oswindow oswindow, i32 nWidth, i32 nHeight)
{

   ASSERT(::IsWindow(oswindow));

   ::CreateCaret(oswindow, (HBITMAP)1, nWidth, nHeight);

}


CLASS_DECL_AURA string message_box_result_to_string(int iResult);


// CLASS_DECL_AURA ::estatus _os_message_box(oswindow oswindow, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
// {

//    string strMessage(pszMessage);

//    strMessage.replace_ci("<br>", "\n");

//    string strTitle(pszTitle);

//    strTitle.replace_ci("<br>", "\n");

//    ::i32 iResult = ::MessageBoxW(oswindow, wstring(strMessage), wstring(strTitle), emessagebox);

//    string strResult = message_box_result_to_string(iResult);

//    callback.receive_response(strResult);

//    return ::success;

// }


// CLASS_DECL_AURA ::estatus os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::callback callback)
// {

//    if (System.is_dedicated_thread())
//    {

//       System.fork([=]()
//          {

//             _os_message_box(oswindow, pszMessage, pszTitle, emessagebox, callback);

//          });

//       return ::success;

//    }

//    return _os_message_box(oswindow, pszMessage, pszTitle, emessagebox, callback);

// }




void defer_term_ui()
{


}

//
//::user::interaction_impl* oswindow_interaction_impl(oswindow oswindow)
//{
//
//   if (::is_null(oswindow))
//   {
//
//      return nullptr;
//
//   }
//
//#ifndef WINDOWS_DESKTOP
//
//   if (::is_set(oswindow->m_pimpl))
//   {
//
//      return oswindow->m_pimpl;
//
//   }
//
//#endif
//
//   auto & system = System;
//
//   sync_lock slSystem(system.mutex());
//
//   auto pmap = system.m_pwindowmap;
//
//   if (!pmap)
//   {
//
//      return nullptr;
//
//   }
//
//   //sync_lock slMap(pmap->mutex());
//
//   ::user::primitive* pbase;
//
//   if (!pmap->m_map.lookup(oswindow, pbase))
//   {
//
//      auto pimpl = thread_value("wnd_init").cast < ::user::interaction_impl >();
//
//      if (::is_set(pimpl))
//      {
//
//         thread_value("wnd_init") = nullptr;
//
//         pimpl->attach(oswindow);
//
//         return oswindow_interaction_impl(oswindow);
//
//      }
//
//      return nullptr;
//
//   }
//
//   return dynamic_cast <::user::interaction_impl*>(pbase);
//
//}
//
//
//




int_bool get_cursor_pos(POINT32 * ppoint)
{

   return ::GetCursorPos(ppoint);

}



CLASS_DECL_AURA int erelative_get_window(enum_relative erelative)
{

   switch (erelative)
   {
   case e_relative_first_child:
      return GW_CHILD;
   default:
      return -1;

   };


}


CLASS_DECL_AURA oswindow get_window(oswindow oswindow, enum_relative erelative)
{

   int iGetWindow = erelative_get_window(erelative);

   if (iGetWindow < 0)
   {

      ::output_debug_string("Unknown Get Window (GW_*) for enum_relative");

      return nullptr;

   }

   return ::GetWindow(oswindow, iGetWindow);

}


