#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   interaction_layout::interaction_layout()
   {

      m_iStateCount = 4;

      //m_pstate = nullptr;

      m_bFillParent = true;

      m_sizeSpan.cx = 1;

      m_sizeSpan.cy = 1;

      m_sizeWeight.cx = 1.0;

      m_sizeWeight.cy = 1.0;

      m_elayoutexperience = layout_experience_none;

      sketch() = display_none;
      window() = display_none;
      design() = display_none;

   }


   interaction_layout::~interaction_layout()
   {

      destroy_state();

   }


   void interaction_layout::create_state(int iStateCount)
   {

      sync_lock sl(mutex());

      if (iStateCount == m_iStateCount)
      {

         return;

      }

      destroy_state();

      if (iStateCount == layout_count_child || iStateCount == layout_count_owner)
      {

         m_iStateCount = iStateCount;

         //m_pstate = new window_state[m_iStateCount];

         //for (int iState = 0; iState < m_iStateCount; iState++)
         //{

         //   m_pstate[iState].set_interaction_layout(this);

         //}

      }

      design() = display_none;

      sketch() = display_none;

   }


   void interaction_layout::destroy_state()
   {

//      sync_lock sl(mutex());

      //if (::is_set(m_pstate))
      //{

      //   delete m_pstate;

      //}

      //m_pstate = nullptr;

   }



   //void interaction_layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{


   //}





   //void interaction_layout::set_placement(const ::rect & rectParam)
   //{

   //   ::rect rect(rectParam);

   //   rect.deflate(m_rectPadding);

   //   request() = rect;

   //}


   ::point interaction_layout::get_parent_accumulated_scroll(e_layout elayout) const
   {

      return ::point();

   }


   void interaction_layout::on_add_layout(::user::interaction_layout * playout)
   {

   }


   //void interaction_layout::move_to(i32 x, i32 y)
   //{
   //
   //   layout().sketch().m_point.set(x, y);
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::move_to(const point & point)
   //{

   //   move_to(point.x, point.y);

   //}


   //void interaction_layout::set_size(i32 cx, i32 cy)
   //{
   //
   //   layout().sketch().m_size.set(cx, cy);
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::set_size(const ::size& size)
   //{

   //   set_size(size.cx, size.cy);

   //}


   //void interaction_layout::set_dim(const ::point& point, const ::size& size)
   //{
   //
   //   layout().sketch().m_point = point;
   //
   //   layout().sketch().m_size = size;
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::place(const ::rect& rect)
   //{
   //
   //   set_dim(rect.origin(), rect.size());
   //
   //}


   //void interaction_layout::set_dim(i32 x, i32 y, i32 cx, i32 cy)
   //{
   //
   //   set_dim(::point(x, y), ::size(cx, cy));
   //
   //}


   //zorder interaction_layout::order(e_layout elayout)
   //{
   //
   //   return state(elayout).zorder();
   //
   //}


#undef INFO_LAYOUT_DISPLAY





   //bool interaction_layout::layout().sketch().is_visible() const
   //{
   //
   //   return ::is_visible(layout().sketch().display());
   //
   //}


//   bool interaction_layout::display(::edisplay edisplay, ::eactivation eactivation)
//   {
//
//      bool bToggle = false;
//
//      if (edisplay == display_normal)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_normal");
//
//         #endif
//
//      }
//      else if (edisplay == display_hide)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_hide");
//
//         #endif
//
//      }
//      else if (edisplay == display_default)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_default");
//
//         #endif
//
//      }
//      else if (edisplay == display_zoomed)
//      {
//
//         output_debug_string("display_zoomed");
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_zoomed");
//
//         #endif
//
//      }
//      else if (edisplay == display_iconic)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_iconic");
//
//         #endif
//
//      }
//      else if (edisplay == display_full_screen)
//      {
//
//         output_debug_string("display_full_screen");
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display display_full_screen");
//
//         #endif
//
//      }
//      else
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         INFO("interaction_layout::display (unknown)");
//
//         #endif
//
//      }
//
//#if DEBUG_LEVEL > 0
//
//      if (edisplay == display_normal)
//      {
//
//         if (m_pdescriptor.is_set() && m_pdescriptor->m_puserinteractionParent == nullptr)
//         {
//
//            INFO("Parent is Null. Display Request -> normal");
//
//         }
//
//      }
//      else if (edisplay == display_hide)
//      {
//
//         if (m_pdescriptor.is_set() && m_pdescriptor->m_puserinteractionParent == nullptr)
//         {
//
//            INFO("Parent is Null. Display Request -> hide");
//
//         }
//
//      }
//
//#endif
//
//      if (edisplay == display_default)
//      {
//
//         auto edisplayCurrent = m_stateRequest2.m_edisplay3;
//
//         auto edisplayStored = m_windowrect.m_edisplay;
//
//         auto edisplayPrevious = m_windowrect.m_edisplayPrevious;
//
//         if (edisplayCurrent == display_undefined)
//         {
//
//            edisplay = display_normal;
//
//         }
//         else if (::is_screen_visible(edisplayCurrent))
//         {
//
//            edisplay = edisplayCurrent;
//
//         }
//         else if (::is_screen_visible(edisplayStored))
//         {
//
//            edisplay = edisplayStored;
//
//         }
//         else if (::is_screen_visible(edisplayPrevious))
//         {
//
//            edisplay = edisplayPrevious;
//
//         }
//         else
//         {
//
//            edisplay = ::display_normal;
//
//         }
//
//         set_display_request(edisplay);
//
//      }
//      else
//      {
//
//         set_display_request(edisplay);
//
//      }
//
//      layout().sketch().m_eactivation = eactivation;
//
//      if (!sketch_on_display())
//      {
//
//         return false;
//
//      }
//
//      layout().set_need_redraw();
//
//      m_bPendingRequest = true;
//
//      return true;
//
//   }





   void interaction_layout::set_reposition(bool bSetThis)
   {

   }


   void interaction_layout::_set_reposition(bool bSetThis)
   {

      UNREFERENCED_PARAMETER(bSetThis);

   }


   //void interaction_layout::set_pending_request(bool bSet)
   //{

   //   m_bPendingRequest = bSet;

   //}


   void interaction_layout::post_redraw(bool bAscendants)
   {


   }


   //bool interaction_layout::window_move(i32 x, i32 y)
   //{

   //   layout().sketch().m_point = {x, y};

   //   layout().set_need_redraw();

   //   return true;

   //}


   //bool interaction_layout::is_this_visible()
   //{

   //   return m_ewindowflag & window_flag_is_window && ::is_visible(layout().design().display());

   //}





   //void interaction_layout::get_window_rect(RECT* prect) const
   //{

   //   ::set_rect_point_size(prect, ui_state().m_pointScreen, ui_state().m_size);

   //}




   //bool interaction_layout::is_this_screen_visible() const
   //{

   //   if(layout().sketch().display() == display_iconic)
   //   {

   //      return ::is_screen_visible(window_display());

   //   }

   //   return ::is_screen_visible(layout().sketch().display());

   //}


   void interaction_layout::set_initial_dim(const ::point & p, const ::size & s)
   {

      sketch() = ::rect(p, s);

      sketch().screen_origin() = p;

      design() = sketch();

      if (is_top_level())
      {

         //bitmap() = sketch();

         //window() = bitmap();

         window() = design();

         window().set_ready();

         window().clear_ephemeral();

      }

   }


} // namespace user


