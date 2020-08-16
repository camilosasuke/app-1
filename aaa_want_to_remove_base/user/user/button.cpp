#include "framework.h"


namespace user
{


   button::button()
   {

      user_button_construct();

   }


   //button::button(::object * pobject) :
   //   ::object(pobject),
   //   ::user::interaction(pobject)
   //{

   //   user_button_construct();

   //}


   button::~button()
   {

      if (m_pmenuitemThis.is_set())
      {

         m_pmenuitemThis->m_puserinteraction = nullptr;
         m_pmenuitemThis->m_pmenu = nullptr;

      }

      ::aura::del(m_pbitmap);
      ::aura::del(m_plist);
      set_button_style(style_none);

   }


   void button::user_button_construct()
   {

      m_erectMargin = rect_button_margin;
      m_erectBorder = rect_button_border;
      m_erectPadding = rect_button_padding;
      m_eintTextAlign = int_button_draw_text_flags;


      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_pbitmap = nullptr;
      m_plist = nullptr;
      m_iClick = 0;
      m_bIdBound = true;

   }


   void button::install_message_routing(::channel * pchannel)
   {

      ::user::control::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE    , pchannel, this, &button::_001OnCreate);
      IGUI_MSG_LINK(WM_KEYDOWN   , pchannel, this, &button::_001OnKeyDown);

      install_simple_ui_default_mouse_handling(pchannel);

   }


   void button::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_estyle == style_push)
      {

         _001OnButtonDrawPush(pgraphics);

      }
      else if (m_estyle == style_list)
      {

         _001OnButtonDrawList(pgraphics);

      }
      else if (m_estyle == style_bitmap)
      {

         _001OnButtonDrawBitmap(pgraphics);

      }
      else if (m_estyle == style_image_and_text)
      {

         _001OnButtonDrawImageAndText(pgraphics);

      }
      else
      {

         _001OnButtonDrawNormal(pgraphics);

      }

   }




   ::size button::calc_text_size()
   {

      auto pgraphics = create_memory_graphics();

      if (pgraphics.is_null())
      {

         return nullptr;

      }

      select_font(pgraphics, font_button);

      string strText(m_strWindowText);

      const ::size & size = pgraphics->GetTextExtent(strText);

      ::draw2d::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size sizeTotal;

      sizeTotal.cx = size.cx;

      sizeTotal.cy = tm.tmHeight;

      return sizeTotal;

   }


   void button::resize_to_fit()
   {

      if (m_estyle == style_simple)
      {

         auto pgraphics = create_memory_graphics();

         select_font(pgraphics, font_button);

         string str;
         get_window_text(str);
         const ::size & size = pgraphics->GetTextExtent(str);

         ::rect rect(0, 0, 0, 0);
         rect.right = LONG(size.cx * 1.6);
         rect.bottom = LONG(size.cy * 1.4);

         set_size(rect.size());


      }
      else if (m_estyle == style_bitmap)
      {

         ::size size = m_pbitmap->m_pimage->size();

         set_size(size);

      }
      else
      {

         ::size sizeTotal = calc_text_size();

         sizeTotal.cx = (LONG)(sizeTotal.cx * 1.6);

         sizeTotal.cy = (LONG)(sizeTotal.cy * 1.4);

         set_size(sizeTotal);

      }

   }

   //void button::_001SetButtonText(const char * pcszText)

   //{
   //   m_istrButtonText = pcszText;

   //}



   void button::_001SetCheck(::enum_check echeck, const ::action_context & context)
   {

      if (echeck != this->get_echeck())
      {

         check::_001SetCheck(echeck, context);

         set_need_redraw();

         post_redraw();

      }

   }


//   ::enum_check button::_001GetCheck()
//   {
//
//      return check::_001GetCheck();
//
//   }


   void button::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (m_estyle == style_none)
      {

         set_button_style(style_normal);

      }

      m_ppropertyCheck = fetch_property(m_id, false);

      if (m_ppropertyCheck)
      {

         bind_update(m_ppropertyCheck);

      }

   }


   void button::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      ::size sizeText = calc_text_size();

      ::rect rect;

      rect.left = rectClient.left + (rectClient.width() - sizeText.cx) / 2;

      rect.top = rectClient.top + (rectClient.height() - sizeText.cy) / 2;

      rect.right = rect.left + sizeText.cx;

      rect.bottom = rect.top + sizeText.cy;

      m_rectText = rect;

   }


   bool button::create_control(class control_descriptor * pdescriptor)
   {

      return control::create_control(pdescriptor);


   }


   void button::_002OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //if(m_puserstyle == nullptr)
      //   return;



      ::rect rectClient;

      get_client_rect(rectClient);

      COLORREF crBk;
      if (!is_window_enabled())
      {
         crBk = _001GetColor(color_button_background_disabled);
      }
      else if (is_left_button_pressed() || echeck() == ::check_checked)
      {
         crBk = _001GetColor(color_button_background_press);
      }
      else if (m_itemHover)
      {
         crBk = _001GetColor(color_button_background_hover);
      }
      else
      {
         crBk = _001GetColor(color_button_background);
      }


      if (_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(
         pgraphics,
         rectClient,
         crBk,
         127);
      }
      else
      {
         pgraphics->fill_rect(rectClient, crBk);
      }


      COLORREF crBorder;
      if (!is_window_enabled())
      {
         crBorder = ARGB(255, 127, 127, 127);
      }
      else if (is_left_button_pressed() || echeck() == ::check_checked)
      {
         crBorder = ARGB(255, 255, 255, 255);
      }
      else if (m_itemHover)
      {
         crBorder = ARGB(255, 100, 100, 200);
      }
      else
      {
         crBorder = ARGB(255, 10, 10, 100);
      }

      if (_001GetFlag(flag_border))
      {

         pgraphics->draw3d_rect(rectClient, crBorder, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectClient.left += 3;
      rectClient.top += 3;
      ::rect rectText = m_rectText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_pbitmap->m_pimage->is_set())
      {
         if (m_pbitmap->m_pimage->width() > 0 && m_pbitmap->m_pimage->height() > 0)
         {
            ::rect rectDib;
            rectDib = m_rectText;
            rectDib.bottom = MIN(rectText.top + m_pbitmap->m_pimage->width(), rectText.bottom);
            rectDib.right = MIN(rectText.left + m_pbitmap->m_pimage->height(), rectText.right);
            //m_pimage->to(pgraphics, rectDib);
            m_pbitmap->m_pimage->bitmap_blend(pgraphics, rectDib);
            rectText.left += m_pbitmap->m_pimage->width();
         }

      }

      ::draw2d::brush_pointer brushText(e_create);

      pgraphics->SelectObject(brushText);

      string strText(get_window_text());

      select_font(pgraphics, font_button);

      pgraphics->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }


   bool button::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && is_window_visible();

   }


   void button::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      ::user::e_key iKey = pkey->m_ekey;

      if (iKey == ::user::key_return || iKey == ::user::key_space)
      {

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         ev.m_pmessage = pmessage;
         on_control_event(&ev);
         pmessage->m_bRet = ev.m_bRet;
         if (pmessage->m_bRet)
         {
            pkey->m_lresult = 1;
         }

      }

   }


   COLORREF button::get_button_text_color()
   {

      COLORREF crText;

      if (!is_window_enabled())
      {

         crText = _001GetColor(color_button_text_disabled, ARGB(255, 0, 0, 0));

      }
      else if (is_left_button_pressed() || get_echeck() == ::check_checked)
      {

         crText = _001GetColor(color_button_text_press, ARGB(255, 0, 0, 0));

      }
      else if (m_itemHover)
      {

         crText = _001GetColor(color_button_text_hover, ARGB(255, 0, 0, 0));

      }
      else
      {

         crText = _001GetColor(color_button_text, ARGB(255, 0, 0, 0));

      }

      return crText;

   }


   COLORREF button::_001GetButtonBackgroundColor() 
   {

      COLORREF crBackground;

      if (!is_window_enabled())
      {

         crBackground = _001GetColor(color_button_background_disabled, ARGB(255, 180, 180, 180));

      }
      else if (is_left_button_pressed() || get_echeck() == ::check_checked)
      {

         crBackground = _001GetColor(color_button_background_press, ARGB(255, 240, 240, 240));

      }
      else if (m_itemHover)
      {

         crBackground = _001GetColor(color_button_background_hover, ARGB(255, 240, 240, 240));

      }
      else
      {

         crBackground = _001GetColor(color_button_background, ARGB(255, 240, 240, 240));

      }

      return crBackground;

   }


   void button::update(::update * pupdate)
   {

      control::update(pupdate);

   }


   void button::_001OnButtonDrawBackground(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      COLORREF crBackground = _001GetButtonBackgroundColor();

      if(get_echeck() == ::check_checked)
      {

         color colorBack(crBackground);

         colorBack.hls_rate(0.0, -0.1, 0.0);

         if (colorref_get_a_value(crBackground) > 0)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->fill_rect(rectClient, colorBack);

         }

         color colorTopLeft(colorBack);

         color colorBottomRight(colorBack);

         colorTopLeft.hls_rate(0.0, -0.2, 0.0);

         colorBottomRight.hls_rate(0.0, 0.2, 0.0);

         ::rect rectPush(rectClient);

         pgraphics->draw3d_rect(rectPush, colorTopLeft, colorBottomRight);

         rectPush.deflate(1, 1);

         pgraphics->draw3d_rect(rectPush, colorTopLeft, colorBottomRight);

      }
      else
      {

         if (colorref_get_a_value(crBackground) > 0)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->fill_rect(rectClient, crBackground);

         }

      }

   }


   void button::_001OnButtonDrawTextLayer(::draw2d::graphics_pointer & pgraphics, RECT * prectText)

   {

      ::rect rectText(prectText);


      if (m_estockicon == stock_icon_none)
      {

         string strText;

         get_window_text(strText);

         if (strText.has_char())
         {

            COLORREF crText = get_button_text_color();

            pgraphics->set_text_color(crText);

            int iDrawTextFlags;

            if (m_estyle == style_image_and_text)
            {

               iDrawTextFlags = _001GetInt(int_button_draw_text_and_image_flags, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

            }
            else
            {

               iDrawTextFlags = _001GetInt(m_eintTextAlign, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            }

            pgraphics->draw_text(strText, rectText, iDrawTextFlags);

         }

      }
      else
      {

         COLORREF crText = get_button_text_color();

         pgraphics->set_text_color(crText);

         ::draw2d::pen_pointer pen(e_create);

         pen->m_color = crText;

         pen->m_dWidth = 1.0;

         pgraphics->SelectObject(pen);

         ::rect rectIcon(rectText);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

      }

   }


   void button::_001OnButtonDrawNormal(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      select_font(pgraphics, font_button);

      ::rect rectMargin = _001GetRect(m_erectMargin);

      ::rect rectBorder = _001GetRect(m_erectBorder);

      rectClient.deflate(rectMargin);

      rectClient.deflate(rectBorder);

      _001OnButtonDrawBackground(pgraphics);

      ::rect rectPadding = _001GetRect(m_erectPadding);

      rectClient.deflate(rectPadding);

      _001OnButtonDrawTextLayer(pgraphics, rectClient);

   }


   void button::_001OnButtonDrawBitmap(::draw2d::graphics_pointer & pgraphics)
   {

      select_font(pgraphics, font_button);

      _001OnButtonDrawBackground(pgraphics);

      if (!m_pbitmap->m_pimage)
      {

         return;

      }

      ASSERT(m_pbitmap->m_pimage); // required

      // use the main bitmap for up, the selected bitmap for down
      ::image_pointer pimage = m_pbitmap->m_pimage;

      if(echeck() == ::check_checked && m_pbitmap->m_pimageSel->is_set() && m_pbitmap->m_pimageSel->area() > 0)
         pimage = m_pbitmap->m_pimageSel;
      else if(m_itemHover && is_window_enabled() && m_pbitmap->m_pimageHover->is_set() && m_pbitmap->m_pimageHover->area() > 0)
         pimage = m_pbitmap->m_pimageHover;
      else if(Session.get_focus_ui() == this && m_pbitmap->m_pimageFocus->is_set() && m_pbitmap->m_pimageFocus->area() > 0)
         pimage = m_pbitmap->m_pimageFocus;   // third image for focused
      else if(!is_window_enabled() && m_pbitmap->m_pimageDisabled->is_set() && m_pbitmap->m_pimageDisabled->area() > 0)
         pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

      ::rect rectClient;

      get_client_rect(rectClient);

      ::rect rectMargin = _001GetRect(m_erectMargin);

      ::rect rectBorder = _001GetRect(m_erectBorder);

      rectClient.deflate(rectMargin);

      rectClient.deflate(rectBorder);

      ::rect rectPadding = _001GetRect(m_erectPadding);

      rectClient.deflate(rectPadding);

      if (pimage->area() > 0 && rectClient.area() > 0)
      {

         ::rect rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double) rectClient.width() / (double)pimage->width();

         double dH = (double) rectClient.height() / (double) pimage->height();

         double dMin = MIN(MIN(dW, dH), 1.0);

         rectAspect.right = (LONG) (pimage->width() * dMin);

         rectAspect.bottom = (LONG) (pimage->height() * dMin);

         rectAspect.Align(align_center, rectClient);

         pgraphics->SetStretchBltMode(HALFTONE);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->draw(rectAspect, pimage->g(), ::rect(pimage->get_size()));

      }

   }


   void button::_001OnButtonDrawImageAndText(::draw2d::graphics_pointer & pgraphics)
   {

      select_font(pgraphics, font_button);

      _001OnButtonDrawBackground(pgraphics);

      ::rect rectClient;

      get_client_rect(rectClient);

      ::rect rectPadded(rectClient);

      int iPadding = _001GetInt(::user::int_element_padding);

      rectPadded.deflate(iPadding, iPadding);

      ::rect rectAspect(rectPadded);

      if (m_pbitmap->m_pimage)
      {

         ASSERT(m_pbitmap->m_pimage); // required

         // use the main bitmap for up, the selected bitmap for down
         ::image_pointer pimage = m_pbitmap->m_pimage;

         if (echeck() == ::check_checked && m_pbitmap->m_pimageSel->is_set() && m_pbitmap->m_pimageSel->area() > 0)
            pimage = m_pbitmap->m_pimageSel;
         else if (m_itemHover && is_window_enabled() && m_pbitmap->m_pimageHover->is_set() && m_pbitmap->m_pimageHover->area() > 0)
            pimage = m_pbitmap->m_pimageHover;
         else if (Session.get_focus_ui() == this && m_pbitmap->m_pimageFocus->is_set() && m_pbitmap->m_pimageFocus->area() > 0)
           pimage = m_pbitmap->m_pimageFocus;   // third image for focused
         else if (!is_window_enabled() && m_pbitmap->m_pimageDisabled->is_set() && m_pbitmap->m_pimageDisabled->area() > 0)
            pimage = m_pbitmap->m_pimageDisabled;   // last image for disabled

         if (pimage->area() > 0 && rectClient.area() > 0)
         {

            rectAspect.left = 0;

            rectAspect.top = 0;

            double dW = (double)rectPadded.width() / (double)pimage->width();

            double dH = (double)rectPadded.height() / (double)pimage->height();

            double dMin = MIN(MIN(dW, dH), 1.0);

            rectAspect.right = (LONG) (pimage->width() * dMin);

           rectAspect.bottom = (LONG) (pimage->height() * dMin);

            rectAspect.Align(align_bottom_left, rectPadded);

            pgraphics->SetStretchBltMode(HALFTONE);

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pgraphics->draw(rectAspect, pimage->g(), ::rect(pimage->get_size()));

            rectAspect.left = rectAspect.right + iPadding;
            rectAspect.right = rectPadded.right;
            rectAspect.top = rectPadded.top;
            rectAspect.bottom = rectPadded.bottom;

         }

      }

      _001OnButtonDrawTextLayer(pgraphics, rectAspect);

   }


   void button::_001OnButtonDrawPush(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      color color;

      color.set_rgb(_001GetColor(::user::color_button_background));

      COLORREF cr;

      if(echeck() == ::check_checked)
      {

         color.hls_rate(0.0,- 0.2,- 0.3);

      }

      if(m_itemHover)
      {

         color.hls_rate(0.0,0.2,0.0);

      }

      cr = color;

      class color colorExt1TL;
      class color colorExt2TL;
      class color colorExt1BR;
      class color colorExt2BR;

      colorExt1TL.set_rgb(cr);
      colorExt2TL.set_rgb(cr);
      colorExt1BR.set_rgb(cr);
      colorExt2BR.set_rgb(cr);

      if(echeck() == ::check_checked)
      {

         colorExt1TL.hls_rate(0.0,- 0.5,0.0);
         colorExt2TL.hls_rate(0.0,- 0.2,0.0);
         colorExt2BR.hls_rate(0.0,0.2,0.0);
         colorExt1BR.hls_rate(0.0,0.85,0.0);

      }
      else
      {

         colorExt1TL.hls_rate(0.0,0.85,0.0);
         colorExt2TL.hls_rate(0.0,0.2,0.0);
         colorExt2BR.hls_rate(0.0,- 0.2,0.0);
         colorExt1BR.hls_rate(0.0,- 0.5,0.0);

      }

      class imaging & imaging = System.imaging();

      ::rect rect = rectClient;
      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,215,colorExt1BR,215);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,210,colorExt1BR,210);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt2TL,205,colorExt2BR,205);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt2TL,200,colorExt2BR,200);
      rect.deflate(1,1,1,1);
      imaging.color_blend(pgraphics,rect.left,rect.top,rect.width(),rect.height(),cr,200);
      rect.deflate(1,1,1,1);

      i32 x1 = rect.left;
      i32 x2 = x1 + rect.width() / 3;

      rect.left = x1;
      rect.right = x2;
      rect.bottom = rect.top + 5;

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1, colorExt1TL);

      pgraphics->SelectObject(pen);

      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,220,colorExt1BR,220);


   }


   void button::set_button_style(e_style estyle)
   {

      if(m_estyle == estyle)
         return;

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         m_pbitmap = new bitmap();

      }
      else if(estyle == style_list)
      {

         m_plist = new list();

         m_plist->m_pimagelistNormal         = nullptr;
         m_plist->m_pimagelistItemHover      = nullptr;
         m_plist->m_pimagelistSubItemHover   = nullptr;

      }
      else if(estyle == style_push)
      {

         SetTimer(16384,100,nullptr);

      }


   }


   void button::on_exit_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         ::aura::del(m_pbitmap);

      }
      else if(estyle == style_list)
      {

         ::aura::del(m_plist);

      }
      else if(estyle == style_push)
      {

         KillTimer(16384);

      }

   }





   bool button::LoadBitmaps(::var var,::var varSel,::var varFocus,::var varDisabled,::var varHover)
   {

      if (m_estyle != style_bitmap &&
            m_estyle != style_image_and_text)
      {

         set_button_style(style_bitmap);

      }

      if(!var.is_empty())
      {

         m_pbitmap->m_pimage = load_image(var);

      }

      if(!varSel.is_empty())
      {

         m_pbitmap->m_pimageSel = load_image(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_pbitmap->m_pimageFocus = load_image(varFocus);

      }


      if(!varDisabled.is_empty())
      {

         m_pbitmap->m_pimageDisabled = load_image(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_pbitmap->m_pimageHover = load_image(varHover);

      }

      return m_pbitmap->m_pimage->is_set() && m_pbitmap->m_pimage->area() > 0;

   }






   void button::pre_translate_message(::message::message * pmessage)
   {

      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pmessage);

      return ::user::control::pre_translate_message(pmessage);

   }


   void button::BaseToolTipGetRect(RECT * prect)

   {
      // use window client rect as the tool rect
      get_client_rect(prect);

   }

   i32 button::BaseToolTipGetIndex()
   {
      // use window dialog control id as the index
      return (i32)GetDlgCtrlId();
   }


   void button::_001OnButtonDrawList(::draw2d::graphics_pointer & pgraphics)
   {
      ::rect rectClient;
      bool bItemHover;
      bool bSubItemHover;



      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain < ::aura::draw_context >::get_last();

      if(pdrawcontext != nullptr)
      {
         rectClient     = pdrawcontext->m_rectClient;
         bItemHover     = pdrawcontext->m_bListItemHover;
         bSubItemHover  = pdrawcontext->m_bListSubItemHover;
      }
      else
      {
         if(get_form() != nullptr)
            return;
         get_client_rect(rectClient);
         bItemHover     = m_itemHover;
         bSubItemHover  = bItemHover;
      }

      ::point point = rectClient.top_left();
      point += ::size(1, 1);

      if(bSubItemHover)
      {
         pgraphics->draw3d_rect(
         rectClient,
         RGB(255,255,255),
         RGB(155,155,105));

         if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else if(bItemHover)
      {
         if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
      }
      else
      {
         if(m_plist->m_pimagelistNormal != nullptr)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            point,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != nullptr)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            point,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != nullptr)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            point,
            0);
         }
      }

   }


   void button::BaseToolTipRelayEvent(class ::message::message *)
   {
   }


   bool button::is_custom_draw()
   {

      return m_estyle == style_list;

   }


   //bool button::m_itemHover
   //{

   //   return m_itemHover;

   //}

   void button::set_stock_icon(e_stock_icon eicon)
   {

      m_estockicon = eicon;

   }


   e_stock_icon button::get_stock_icon()
   {

      return m_estockicon;

   }


} // namespace user



