﻿#include "framework.h"


namespace browser
{


   switcher_view::switcher_view(::layered * pobjectContext):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

      m_pview = nullptr;

      m_ptopview = nullptr;

   }


   switcher_view::~switcher_view()
   {

   }


   void switcher_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void switcher_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void switcher_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void switcher_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < ::userex::top_view >(nullptr, get_pane_holder(0),"top_view");

      if(m_ptopview == nullptr)
      {

         System.message_box(nullptr,"Could not create folder edit view");

      }

      //SetPane(0,m_ptopview,false);

      m_pview = create_view < view >(nullptr,get_pane_holder(1),"browser_switcher_view");

      if(m_pview == nullptr)
      {

         System.message_box(nullptr,"Could not create file list ::user::impact");

      }

   }



   void switcher_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "switcher_toggle")
         {

            __pointer(view) pview = m_pview;

            pview->m_prender->m_bLite = !pview->m_prender->m_bLite;

            pevent->m_bRet = true;
            return;

         }
         else if(pevent->m_puie->m_id == "browser_toggle")
         {

            m_pview->m_prender->m_bLite = !m_pview->m_prender->m_bLite;


            m_pview->on_layout(::draw2d::graphics_pointer & pgraphics);

            pevent->m_bRet = true;
            return;

         }

      }

      ::user::split_view::on_control_event(pevent);

   }

   void switcher_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void switcher_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnDraw(pgraphics);

   }


} // namespace browser



