﻿#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_tab_view::simple_tab_view()
{

}


simple_tab_view::~simple_tab_view()
{
}


// simple_tab_view diagnostics


void simple_tab_view::assert_valid() const
{
   ::user::impact::assert_valid();
}


void simple_tab_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}


void simple_tab_view::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::on_layout(pgraphics);

}








bool simple_tab_view::get_client_rect(RECT32 * prect)
{

   ::user::impact::get_client_rect(prect);

   return true;

}





void simple_tab_view::_001OnCreate(::message::message * pmessage)
{

   SCAST_PTR(::message::create, pcreate, pmessage);

   if(pcreate->previous())
      return;

   if(!::user::interaction::create_window(this, 1))
   {
      pcreate->m_lresult = -1;
      return;
   }

}


void simple_tab_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   ::user::tab::_001OnDraw(pgraphics);

}


void simple_tab_view::install_message_routing(::channel * pchannel)
{
   
   ::user::impact::install_message_routing(pchannel);
   
   ::user::tab::install_message_routing(pchannel);

}


void simple_tab_view::_001OnLButtonUp(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);
   
   ::user::tab::_001OnLButtonUp(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_view::_001OnMouseMove(::message::message * pmessage)
{
   
   SCAST_PTR(::message::mouse, pmouse, pmessage);
   
   ::user::tab::_001OnMouseMove(pmessage);
   
   if (pmouse->m_bRet)
   {

      return;

   }

}


void simple_tab_view::_001OnMouseLeave(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   ::user::tab::_001OnMouseLeave(pmessage);

   if (pmouse->m_bRet)
   {

      return;

   }

}

