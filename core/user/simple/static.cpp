﻿#include "framework.h"


simple_static::simple_static() :
   m_brushBkg(e_create)
{
   
   m_pimagelist = nullptr;
   
   m_bTransparent = false;
   
   m_brushBkg->m_etype = ::draw2d::brush::type_null;

}


simple_static::~simple_static()
{

}


void simple_static::pre_subclass_window()
{
   PreSubClassWindow();

   ::user::static_control::pre_subclass_window();
}


//LRESULT simple_static::OnSetIcon(WPARAM wparam, LPARAM lparam)
//{
//
//   if(m_pimagelist != nullptr)
//   {
//      
//      m_pimagelist->release();
//
//   }
//
//   return default_window_procedure(WM_SETICON, wparam, lparam);
//
//}


void simple_static::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if (get_type() == type_icon)
   {

      ::draw2d::icon * picon = static_get_icon();

      if (picon != nullptr)
      {

         pgraphics->DrawIcon(nullptr, picon);

      }

   }
   else if (get_type() == type_text)
   {

      auto pstyle = get_style(pgraphics);

      pgraphics->set(get_font(pstyle));

      pgraphics->set_text_color(get_color(pstyle));

      string str;

      get_window_text(str);

      pgraphics->text_out(0, 0, str);

   }

}
