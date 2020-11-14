#include "framework.h"
#include "apex/message.h"
#include "acme/os/cross/windows/_windows.h"

namespace message
{

   class ::channel * CreateSignal()
   {
      return new class ::channel();
   }





   CLASS_DECL_APEX bool is_idle_message(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pbase == nullptr)
         return FALSE;

      // redundant e_message_mouse_move and e_message_non_client_mouse_move
      if(pbase->m_id == e_message_mouse_move || pbase->m_id == e_message_non_client_mouse_move)
      {
         return TRUE;
      }

      // e_message_paint and WM_SYSTIMER (caret blink)
      return pbase->m_id != e_message_paint && pbase->m_id != 0x0118;

   }



   CLASS_DECL_APEX bool is_idle_message(LPMESSAGE pmsg)

   {

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pmsg == nullptr)

         return false;

      // redundant e_message_mouse_move and e_message_non_client_mouse_move
      if(pmsg->message == e_message_mouse_move || pmsg->message == e_message_non_client_mouse_move)

      {
         return true;
      }

      // e_message_paint and WM_SYSTIMER (caret blink)
      return pmsg->message != e_message_paint && pmsg->message != 0x0118;


   }


//   ::u32 translate_to_os_message(const ::id & id)
//   {
//
////#ifdef WINDOWS
////
////      if (id.m_etype == ::id::e_type_message)
////      {
////
////         return (::u32) id.m_emessage;
////
////      }
////
////#elif defined(LINUX) ||  defined(__APPLE__) || defined(ANDROID)
////      switch (emessage)
////      {
////      case e_message_create:
////         return e_message_create;
////      default:
////         return emessage;
////      };
////
////#else
////      switch (emessage)
////      {
////      default:
////         return emessage;
////      };
////#endif
//
//   }


   e_prototype get_message_prototype(enum_message emessage, ::u32 uCode)
   {
      switch (emessage)
      {
      case e_message_size:
         return PrototypeSize;
      case e_message_hscroll:
      case e_message_vscroll:
         return PrototypeScroll;
      case e_message_create:
      case e_message_nccreate:
         return PrototypeCreate;
      case e_message_move:
         return PrototypeMove;
      case e_message_activate:
         return PrototypeActivate;
      case e_message_mouse_activate:
         return PrototypeMouseActivate;
      case WM_MEASUREITEM:
         return PrototypeMeasureItem;
#ifdef WINDOWS
      case WM_NOTIFY:
         return PrototypeNotify;
#endif
      case WM_COMMAND:
         return PrototypeCommand;
         //{
         //switch (uiCode)
         //{
         //case CN_UPDATE_::user::command:
         //    return PrototypeUpdateCommandUserInterface;
         //default:
         //return PrototypeCommand;
         //}
         //}
      case e_message_mouse_move:
      case e_message_lbutton_down:
      case e_message_lbutton_up:
      case WM_LBUTTONDBLCLK:
      case e_message_rbutton_down:
      case e_message_rbutton_up:
      case WM_RBUTTONDBLCLK:
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
      case WM_MBUTTONDBLCLK:
      case e_message_non_client_mouse_move:
      case WM_NCLBUTTONDOWN:
      case WM_NCLBUTTONUP:
         return PrototypeMouse;
#ifdef WINDOWS
      case e_message_mouse_wheel:
         return PrototypeMouseWheel;
#endif
      case e_message_ncactivate:
         return PrototypeNcActivate;
      case WM_TIMER:
         return PrototypeTimer;
      case e_message_key_down:
      case e_message_key_up:
      case e_message_char:
      case e_message_dead_char:
      case e_message_sys_key_down:
      case e_message_sys_key_up:
      case e_message_sys_char:
      case e_message_sys_dead_char:
#if(_WIN32_WINNT >= 0x0501)
      case e_message_uni_char:
#endif
         return PrototypeKey;
      case e_message_nchittest:
         return PrototypeNcHitTest;
      case WM_SETCURSOR:
         return PrototypeSetCursor;
      case WM_ERASEBKGND:
         return PrototypeEraseBkgnd;
      case WM_SHOWWINDOW:
         return PrototypeShowWindow;
      case WM_INITMENUPOPUP:
         return PrototypeInitMenuPopup;
      case WM_ENABLE:
         return PrototypeEnable;
         /*#ifdef WINDOWS
         case WM_CTLCOLOR:
         if(pba)
         return PrototypeCtlColor;
         case WM_CTLCOLOR + WM_REFLECT_AXIS:
         return PrototypeCtlColorReflect;
         #endif*/
      case e_message_kill_focus:
         return PrototypeKillFocus;
      case e_message_set_focus:
         return PrototypeSetFocus;
      case WM_WINDOWPOSCHANGING:
      case WM_WINDOWPOSCHANGED:
         return PrototypeWindowPos;
      case e_message_nccalcsize:
         return PrototypeNcCalcSize;
      case e_message_simple_command:
         return PrototypeSimpleCommand;
      case e_message_paint:
         return PrototypeNone;
      default:
         return PrototypeNone;
      }
   }


} // namespace message

