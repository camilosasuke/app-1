#include "framework.h"


#ifdef Application
#undef Application
#endif

#define Application System



namespace plugin
{


   host_interaction::host_interaction(::matter * pobject) :
      ::matter(pobject)
   {

      m_pframe = nullptr;

      m_id = "plugin::host_interaction";

   }


   host_interaction::~host_interaction()
   {

   }

   void host_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &host_interaction::_001OnMouseMove);
      MESSAGE_LINK(message_check, pchannel, this, &host_interaction::_001OnCheck);
      MESSAGE_LINK(e_message_create, pchannel, this, &host_interaction::_001OnCreate);

      /*
      MESSAGE_LINK(e_message_window_position_changed  , pchannel, this, &host_interaction::on_ignore_message);
      MESSAGE_LINK(e_message_size              , pchannel, this, &host_interaction::on_ignore_message);
      MESSAGE_LINK(e_message_move              , pchannel, this, &host_interaction::on_ignore_message);
      //MESSAGE_LINK(e_message_timer             , pchannel, this, &host_interaction::on_ignore_message);
      MESSAGE_LINK(WM_IME_SETCONTEXT    , pchannel, this, &host_interaction::on_ignore_message);
      MESSAGE_LINK(e_message_window_position_changing , pchannel, this, &host_interaction::on_ignore_message);
      MESSAGE_LINK(WM_CHILDACTIVATE     , pchannel, this, &host_interaction::on_ignore_message);
      */

   }


   void host_interaction::_001OnMouseMove(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   void host_interaction::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      psession->m_bSystemSynchronizedCursor = false;

   }


   void host_interaction::_001OnCheck(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam != 0)
         {
            m_pplugin->ready_on_main_thread();
         }
      }
      else if(pbase->m_wparam == 2)
      {
         string * pstrLink = (string *) pbase->m_lparam.m_lparam;
         string strLink(*pstrLink);
         property_set setQuery;
         //setQuery.parse_url_query(strLink);
         if(setQuery.has_property("karfile_url"))
         {
            System.url().string_set(strLink, "karfile_url", (const char *) m_pplugin->get_host_location_url());
         }
         // do the following if desired on calling System open linnk, will try to create plugin::system::get_host_location_url
         // else if(setQuery["ruri"].get_string().get_length() <= 0)
         //{
         //System.url().string_set(strLink, "ruri", (const char *) m_pplugin->get_host_location_url());
         //}
         m_pplugin->open_link(strLink, "");
         delete pstrLink;
      }
   }

   void host_interaction::_001OnTimer(::timer * ptimer)
   {
      ::user::box::_001OnTimer(ptimer);;
      if(ptimer->m_uEvent == 88881115)
      {
         KillTimer(19841115);
         m_pplugin->ready_on_main_thread();
      }
   }



   void host_interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //::rect rectWindow;
      //m_puserinteraction->get_window_rect(rectWindow);
      //const ::point & pointPreviousViewportOrg = pgraphics->GetViewportOrg();
      //pgraphics->SetViewportOrg(rectWindow.top_left());

      //::rect rectClient;
      //get_client_rect(rectClient);

      _001DrawChildren(pgraphics);

      //pgraphics->SetViewportOrg(pointPreviousViewportOrg);
      //pgraphics->SelectClipRgn(nullptr);
      
      auto pointCursor = psession->get_cursor_pos();

      _001ScreenToClient(pointCursor);

      ::draw2d::cursor * pcursor = psession->get_cursor();

      if(pcursor != nullptr)
      {

         pcursor->to(pgraphics, pointCursor);

      }

   }

   bool host_interaction::defer_check(enum_check echeck)
   {

      if(!m_pplugin->is_ok())
         return false;

      return send_message((::u32)message_check, 0, (LPARAM) echeck) != 0;

   }


   void host_interaction::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if(m_pframe != nullptr)
      {

         ::rect rect;

         get_client_rect(rect);

         m_pframe->place(rect);

         m_pframe->display();

      }
      else
      {
         __pointer(::user::interaction) pinteraction = top_child();
         if(pinteraction != nullptr)
         {
            ::rect rectClient;
            get_client_rect(rectClient);
            ::rect rectWindow;
            pinteraction->get_window_rect(rectWindow);
            _001ScreenToClient(rectWindow);
            if(rectWindow != rectClient)
            {

               pinteraction->order(zorder_none);

               pinteraction->place(rectClient);

               pinteraction->display();

            }

            //else
            //{
            // pinteraction->display(e_display_normal);
            //pinteraction->on_layout(::draw2d::graphics_pointer & pgraphics);
            //}
         }
      }
   }

   bool host_interaction::is_window_visible()
   {
      // it is a regular operational system invisible window whose visibility should be controlled by plugin.
      // So, do not let children be invisible because this invisible host is invisible...
      return true;
   }


//   bool host_interaction::get_window_rect(RECT64 * prect)
//
//   {
//
//      if(m_pplugin == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::rect rect = m_pplugin->get_window_rect()
//
//      if(!m_pplugin->get_window_rect(&rect))
//      {
//
//         return false;
//
//      }
//
//      ::copy(prect, &rect);
//
//
//      return true;
//
//   }
//
//
//   bool host_interaction::get_client_rect(RECT64 * prect)
//
//   {
//
//      if(m_pplugin == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::rect rect;
//
//      if(!m_pplugin->get_client_rect(&rect))
//      {
//
//         return false;
//
//      }
//
//      ::copy(prect,&rect);
//
//
//      return true;
//
//   }


   bool host_interaction::RedrawWindow(const ::rect & rectUpdate,::draw2d::region * prgnUpdate, ::u32 flags)
   {

      UNREFERENCED_PARAMETER(rectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);

      return TRUE;

   }


   ::user::interaction * host_interaction::get_os_focus_uie()
   {

      return System.ui_from_handle(m_pplugin->get_host_window());

   }


   void host_interaction::_user_message_handler(::message::base * pbase)
   {

      ::user::interaction::message_handler(pbase);

      pbase->m_bRet = true;

   }


   void host_interaction::on_ignore_message(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

   }


   void host_interaction::_000OnMouse(::message::mouse * pmouse)
   {

      if(!is_null_ref(Session))
      {

         psession->m_pointCursor = pmouse->m_point;

      }
      else
      {

         if(m_uiptraChild.get_size() > 0 && m_uiptraChild[0]->get_context_application() != nullptr && m_uiptraChild[0]->get_context_application()->get_context_session() != nullptr)
         {

            set_context_object(m_uiptraChild[0]);

         }

      }

      ::user::interaction::_000OnMouse(pmouse);

   }


   LRESULT host_interaction::DefWindowProc(const ::id & id, WPARAM wparam, lparam lparam)

   {

      if (emessage == e_message_nccreate || emessage == e_message_create)
         /*      || emessage == e_message_size
               || emessage == e_message_move
               || emessage == e_message_window_position_changing
               || emessage == e_message_window_position_changed)*/
      {

         //return ::user::interaction::default_window_procedure(emessage, wparam, lparam);
         return 0;

      }
      else
      {

         return 0;

      }

   }


} // namespace plugin


#undef Application
#define Application App(get_context_application())


