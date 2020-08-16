#include "framework.h"
#include "aura/message.h"


namespace user
{


   box::box()
   {

      m_databasekey.m_strDataKey = "WindowRect";

      m_databasekey.m_bLocalData = true;

      m_windowrectStore.m_edisplay = ::display_undefined;

   }


   box::~box()
   {

   }


   ::estatus box::initialize(::object * pobjectContext)
   {

      auto estatus = scroll::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      if (m_id.is_empty())
      {

         m_id = type_name();

      }

      m_databasekey.m_strDataKey = m_id;

      return estatus;

   }




   void box::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      scroll::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &box::_001OnCreate);
      IGUI_MSG_LINK(WM_SIZE, pchannel, this, &box::_001OnSize);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &box::_001OnShowWindow);

   }


   void box::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

   }


   void box::_001OnSize(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void box::_001OnShowWindow(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   bool box::should_save_window_rect()
   {
      
#if defined(_UWP) || defined(APPLE_IOS)
      
      return false;
      
#else
      
      return m_bSaveWindowRect && m_bEnableSaveWindowRect2;

#endif

   }


   bool box::WindowDataSaveWindowRect()
   {

      bool bSave = false;

      if (should_save_window_rect())
      {

         if (display_state() == ::display_none)
         {

            return false;

         }

         defer_update_display();

         bSave = SaveWindowRect_(m_databasekey + window_data_key_modifier());

      }

      return bSave;

   }


   string box::window_data_key_modifier()
   {

      if (GetParent() != nullptr)
      {

         return m_strDisplay + ".child";

      }
      else
      {

         return m_strDisplay;

      }

   }


   bool box::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
   {

      bool bLoad = false;

      defer_update_display();

      auto key = m_databasekey + window_data_key_modifier();

      bLoad = LoadWindowRect_(key, bForceRestore, bInitialFramePosition);

      if (!bLoad)
      {

         m_ewindowflag |= window_flag_loading_window_rect;

         bool bRestore = good_restore(nullptr, nullptr, true, activation_none, zorder_top, initial_restore_display()) >= 0;

         if (!bRestore)
         {

            set_need_layout();

            display();

         }

         return bRestore;

      }

      return bLoad;

   }


   bool box::LoadWindowRect_(const ::database::key & key, bool bForceRestore, bool bInitialFramePosition)
   {

      if (!(m_ewindowflag & window_flag_auto_store_window_rect))
      {

         return false;

      }

      try
      {

         window_rect windowrect;

         if (!Application.data_get(key, windowrect))
         {

            return false;

         }

         m_ewindowflag |= window_flag_loading_window_rect;

         m_windowrectStore = windowrect;

         m_windowrect = m_windowrectStore;

         e_display edisplay = windowrect.m_edisplay;

         set_appearance(windowrect.m_eappearance);

         if (edisplay == display_iconic && bInitialFramePosition)
         {

            edisplay = windowrect.m_edisplayPrevious;

         }

         order(zorder_top);

         if (m_ewindowflag & window_flag_disable_window_placement_snapping)
         {

            if (is_docking_appearance(edisplay))
            {

               edisplay = display_normal;

            }

         }

         if(!bForceRestore
            && (edisplay == display_zoomed
            || edisplay == display_full_screen
            || (edisplay == display_iconic && !bInitialFramePosition)))
         {

            if(bInitialFramePosition)
            {

               ui_state().m_edisplay3 = edisplay;

            }

            place(windowrect.m_rectWindow);

            request_state().m_edisplay3 = edisplay;

            m_bRequestReady = true;

         }
         else if (!bForceRestore && is_docking_appearance(edisplay))
         {

            if(bInitialFramePosition)
            {

               ui_state().m_edisplay3 = edisplay;

            }

            place(windowrect.m_rectSnapped);

            request_state().m_edisplay3 = edisplay;

            m_bRequestReady = true;

         }
         else
         {

            good_restore(nullptr, windowrect.m_rectRestored, true, activation_none, zorder_top, windowrect.m_edisplay);

         }

         return true;

      }
      catch (exception_pointer pe)
      {

         handle_exception(pe);

      }
      catch (...)
      {

      }

      return false;

   }


   bool box::SaveWindowRect_(const ::database::key & key)
   {

      if (!(m_ewindowflag & window_flag_auto_store_window_rect))
      {

         return false;

      }

      if (display_state() == ::display_none)
      {

         return false;

      }

      if (m_windowrectStore.m_edisplay == display_undefined)
      {

         Application.data_get(key, m_windowrectStore);

      }

      auto windowrect = m_windowrectStore;

      bool bGot = m_windowrectStore.m_edisplay != display_undefined;

      windowrect.m_edisplay = display_request();

      windowrect.m_eappearance = request_state().m_eappearance;

      get_window_rect(windowrect.m_rectWindow);

      auto edisplay = windowrect.m_edisplay;

      if (bGot &&
            (edisplay == ::display_zoomed
             || edisplay == ::display_full_screen
             || edisplay == ::display_iconic))
      {

      }
      else if (bGot && is_docking_appearance(windowrect.m_edisplay))
      {

         windowrect.m_rectSnapped = windowrect.m_rectWindow;

      }
      else if (windowrect.m_rectWindow.size() == m_sizeRestoreCompact)
      {

         windowrect.m_edisplay = display_compact;

      }
      else if (windowrect.m_rectWindow.size() == m_sizeRestoreBroad)
      {

         windowrect.m_edisplay = display_broad;

      }
      else
      {

         windowrect.m_rectRestored = windowrect.m_rectWindow;

      }

      if (windowrect.m_rectRestored.width() < get_window_minimum_size().cx
         || windowrect.m_rectRestored.height() < get_window_minimum_size().cy)
      {

         if (windowrect.m_rectWindow.width() > get_window_minimum_size().cx
            && windowrect.m_rectWindow.height() > get_window_minimum_size().cy)
         {

            windowrect.m_rectRestored = windowrect.m_rectWindow;

         }

      }

      if (!Application.data_set(key, windowrect))
      {

         return false;

      }

      m_windowrectStore = windowrect;

      return true;

   }


   void box::prodevian_prepare_window_restore(edisplay edisplay)
   {

      good_restore(NULL, window_request_rect(), true, request_state().m_eactivation, request_state().m_zorder, edisplay);

   }


   string box::calc_display()
   {

      sync_lock sl(mutex());

      string strDisplay;

      //::rect rectNormal;

      //get_rect_normal(rectNormal);

      ::rect rectMainMonitor;

      Session.get_main_monitor(rectMainMonitor);

      strDisplay.Format("Display(%d, %d)", rectMainMonitor.width(), rectMainMonitor.height());

      return strDisplay;

   }

   bool box::does_display_match()
   {

      single_lock sl(mutex(), true);

      if (m_strDisplay.is_empty())
         return false;

      return m_strDisplay == calc_display();

   }


   void box::defer_update_display()
   {

      sync_lock sl(mutex());

      m_strDisplay = calc_display();

   }




   void box::on_command(::user::command * pcommand)
   {

      ::user::interaction::on_command(pcommand);

   }


   bool box::on_before_set_parent(::user::interaction * puiParent)
   {

      if (!::user::interaction::on_before_set_parent(puiParent))
      {

         return false;

      }

      m_bEnableSaveWindowRect2 = false;

      return true;

   }


   bool box::on_set_parent(::user::interaction * puiParent)
   {

      if(!::user::interaction::on_set_parent(puiParent))
      {

         return false;

      }

      return true;

   }


   //bool box::is_local_data()
   //{

   //   return m_datakeyWindowRect.m_bLocalData;

   //}


   bool box::parent_is_local_data()
   {

      ::user::interaction * puiParent = GetParent();

      __pointer(::database::client) pclient = puiParent;

      if(pclient.is_set())
      {

         if(pclient->is_local_data())
         {

            return true;

         }
         else
         {

            return false;

         }

      }

      return false;

   }


   //bool box::is_local_data()
   //{

   //   if(::database::client::is_local_data())
   //   {

   //      return true;

   //   }

   //   if(parent_is_local_data())
   //   {

   //      return true;

   //   }

   //   return false;

   //}

   void box::on_simple_command(::message::simple_command * psimplecommand)
   {

      switch (psimplecommand->m_esimplecommand)
      {
         case simple_command_load_window_rect:

            WindowDataLoadWindowRect(psimplecommand->m_lparam != FALSE);

            psimplecommand->m_bRet = true;

            break;

         default:

            break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::interaction::on_simple_command(psimplecommand);

   }




} // namespace user















