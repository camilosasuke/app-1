#include "framework.h" 
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple_ui/_simple_ui.h"
#endif


namespace simple_ui
{


   label::label()
   {

   }

   label::~label()
   {
   }




   void label::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);


      color32_t c;

      //if(get_style()->m_eschema == ::hotplugin::plugin::schema_darker)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS
         c = ARGB(255, 1140, 149 + 49, 177 + 49);
#else
         c = ARGB(255, 149 + 49, 1140, 123 + 49);
#endif

      }
      //else
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS
         c = ARGB(255, 90, 50, 80);
#else
         c = ARGB(255, 49, 90, 23);
#endif

      }

      ::rect rectClient;

      get_client_rect(rectClient);

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(c);

      ::draw2d::font_pointer f(e_create);

      /*f->create_pixel_font(FONT_SANS_EX, (i32)rectClient.height() * 0.7);

      float fMargin = (rectClient.height() * ((1.0f - 0.7f) / 2.0f));*/

      f->create_pixel_font(FONT_SANS, (i32)rectClient.height() * .84);

      float fMargin = 0.0;

      pgraphics->set(f);

      pgraphics->set(b);

      string strText;

      get_window_text(strText);

      pgraphics->text_out(rectClient.left, (i32)(rectClient.top + fMargin), strText);

   }


} // namespace simple_ui
