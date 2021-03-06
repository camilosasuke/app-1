#include "framework.h" 
#include "aura/user/menu/user_menu_central.h"
#include "core/user/userex/userex.h"
// pgraphics->GetTextExtent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"





namespace lite

{


   theme::theme(::layered * pobjectContext):
      object(pobject),
      ::user::style(pobject),
      ::user::theme(pobject)
   {

      create_translucency(::user::element_none, ::user::translucency_present);

      create_point_font(::user::font_default,"Segoe UI", 12.0);

      userstyle()->m_mapFont->operator[](::user::font_default)->m_etextrenderinghint = ::draw2d::text_rendering_hint_clear_type_grid_fit;

      create_color(::user::color_text, ARGB(255, 0, 0, 0));
      create_color(::user::color_edit_text, ARGB(255, 0, 0, 0));
      create_color(::user::color_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_face, ARGB(192, 192, 192, 192));
      create_color(::user::color_list_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_edit_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_tree_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_view_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_scrollbar_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_tab_layout_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_tab_client_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_split_layout_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_background_selected, ARGB(255, 155, 185, 255));
      create_color(::user::color_list_header, ARGB(255, 255, 255, 255));
      create_color(::user::color_list_header_background, ARGB(255, 0x58, 0x5C, 0x5D));
      create_color(::user::color_list_item_text, ARGB(255, 0, 0, 0));
      create_color(::user::color_list_item_text_hover, ARGB(255, 100, 150, 200));
      create_color(::user::color_list_item_background, ARGB(30, 0, 0, 0));
      create_color(::user::color_list_item_background_hover, ARGB(50, 0, 0, 0));
      create_color(::user::color_list_item_background_selected, ARGB(255, 160, 210, 235));
      create_color(::user::color_list_item_background_selected_hover, ARGB(255, 160, 220, 255));
      create_color(::user::color_list_header_separator, 0);
      create_color(::user::color_toolbar_background, ARGB(255, 0xF3, 0XF5, 0xF5));
      create_color(::user::color_button_background_disabled, ARGB(255, 128, 128, 128));
      create_color(::user::color_button_background_hover, ARGB(255, 0x55, 0x99, 0xC2));
      create_color(::user::color_button_background, ARGB(255, 0x30, 0x75, 0xA0));
      create_color(::user::color_button_background_press, ARGB(255, 0x07, 0x6D, 0x91));
      create_color(::user::color_button_text_disabled, ARGB(255, 0xD0, 0xD0, 0xD0));
      create_color(::user::color_button_text_hover, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text_press, ARGB(255, 255, 255, 255));
      create_color(::user::color_text_selected_highlight, ARGB(255, 150, 200, 250));
      create_color(::user::color_text_highlight, ARGB(255, 100, 150, 200));



      create_rect_coord(::user::rect_tab_padding, 0.4, 0.4, 0.4, 0.4);

      create_int(::user::int_button_press_shift_cx, 4);
      create_int(::user::int_button_press_shift_cy, 4);


   }


   theme::~theme()
   {

   }


   bool theme::_001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab)
   {

      ::rect rect;
      ::rect rectBorder;
      ::rect rectText;
      ::rect rectClient;
      ::rect rectIcon;
      ::rect rectClose;

      ::rect r1;
      ptab->get_client_rect(r1);

      pgraphics->fill_rect(r1, ARGB(255, 255, 255, 255));

      ptab->get_data()->m_pen->create_solid(1,RGB(32,32,32));

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rcTab;

      rcTab = ptab->get_data()->m_rectTab;

      ::rect rcTabs(rcTab);

      ::rect rcClient;

      rcClient = ptab->get_data()->m_rectTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectBorder.bottom;

      rcClient.top = rcTabs.bottom;

      color32_t crbk = ptab->_001GetColor(::user::color_tab_layout_background);

      pgraphics->fill_rect(rcTabs, crbk);

      crbk= ptab->_001GetColor(::user::color_tab_client_background);

      pgraphics->fill_rect(rcClient, crbk);

      i32 iTab = -1;

      ::draw2d::brush_pointer brushText;

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

         if(!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if(!ptab->get_element_rect(iTab,rect,::user::element_tab))
            continue;

         if(!ptab->get_element_rect(iTab,rectBorder, ::user::element_border))
            continue;

         if(!ptab->get_element_rect(iTab,rectClient, ::user::element_client))
            continue;

         if(ptab->get_data()->m_bVertical)
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
/*               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }

            ::draw2d::path_pointer path(e_create);

            if(true)
            {

               if(ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  //path->add_line(rectClient.right, rectBorder.top);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(rectClient.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);

                  path->end_figure(false);

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,235,235,230),ARGB(250,255,255,250));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && (ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100)))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));

                  }

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right,rectBorder.bottom,rectBorder.left + 1,rectBorder.bottom);
                  path->add_line(rectBorder.left,rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(rectText.left,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.top);
                  path->add_line(rectBorder.right,rectBorder.bottom);

                  path->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && (ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100)))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,175,175,170),ARGB(250,195,195,190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     brushText = ptab->get_data()->m_brushText;

                  }

               }

            }

         }
         else
         {

            if(ptab->get_element_rect(iTab,rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

/*               pane.m_pimage->bitmap_blend(pgraphics,rectIcon);

            }
            if (iPane == 0)
            {

               if (rcTab.left < rectBorder.left)
               {

                  pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                  pgraphics->draw_line(rcTab.left, rectClient.bottom, rectBorder.left, rectClient.bottom);

               }

            }

            if(true)
            {

               ::draw2d::path_pointer path(e_create);

               if(ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  if (iPane > 0)
                  {

                     path->add_line(rect.left, rectClient.bottom, rectBorder.left, rectClient.bottom);

                  }

                  path->add_line(rectBorder.left,rectClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectClient.right));

                  path->add_line(rectBorder.right - 1,rectClient.bottom);

                  path->end_figure(false);

                  //pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,235,235,230),ARGB(250,255,255,250));

                  pane.m_brushFillSel->create_solid(ARGB(255, 255, 255, 255));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  ptab->get_data()->m_penBorderSel->create_solid(1.0,ARGB(255,0,0,0));

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button &&( ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100)))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));

                  }

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {

                  //path->begin_figure(true, ::draw2d::fill_mode_winding);

                  if (iPane > 0)
                  {

                     path->add_line(rect.left, rectClient.bottom, rectBorder.left, rectClient.bottom);

                  }

                  path->add_line(rectBorder.left,rectClient.bottom,rectBorder.left,rectBorder.top);

                  path->add_line(rectClient.right,rectBorder.top);

                  path->add_line(rectBorder.right,rectBorder.top + (rectBorder.right - rectClient.right));

                  path->add_line(rectBorder.right - 1,rectClient.bottom);

                  path->end_figure(true);

                  if(iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && (ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100)))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,215,215,210),ARGB(250,235,235,230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(),rectBorder.bottom_left(),ARGB(230,175,175,170),ARGB(250,195,195,190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     brushText = ptab->get_data()->m_brushTextSel;

                  }

               }

            }

            if (iPane == ptab->get_data()->m_panea.get_upper_bound())
            {

               if (rectBorder.right - 1 < rcTab.right)
               {

                  pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                  pgraphics->draw_line(rectBorder.right - 1, rectClient.bottom, rcTab.right, rectClient.bottom);

               }

            }


         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectText, ::user::element_text))
            {

               _001OnTabPaneDrawTitle(pane,ptab,pgraphics,rectText,brushText);

            }

         }

         if(true)
         {

            if(ptab->get_element_rect(iTab,rectClose, ::user::element_close_tab_button))
            {

               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));

               if(iTab == ptab->m_iHover && ptab->m_eelementHover == ::user::element_close_tab_button)
               {

                  brushText = ptab->get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = ptab->get_data()->m_brushClose;

               }

               pgraphics->SelectObject(brushText);

               pgraphics->draw_text("x",rectClose,e_align_center);

            }

         }

      }

      return true;

   }


   void theme::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,LPCRECT32 lpcrect,::draw2d::brush_pointer & brushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->SelectObject(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(),*lpcrect,e_align_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rect rectText(lpcrect);

         ::draw2d::font_pointer font;
         font = pgraphics->get_current_font();
         size sSep = ptab->get_data()->m_sizeSep;
         ::rect rectEmp;
         for(index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size s = pane.m_sizeaText[i];
            rectText.right =rectText.left + s.cx;
            pgraphics->_DrawText(str,rectText,e_align_bottom_left, e_draw_text_no_prefix);
            rectText.left += s.cx;
            if(i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1,1);
               ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
               if(ptab->m_eelementHover == (int)::user::element_split + i)
               {
                  pgraphics->fill_rect(rectEmp,ARGB(128,149,184,255));
                  pgraphics->SelectObject(ptab->get_data()->m_brushTextHover);
               }
               else
               {
                  //pgraphics->FillSolidRect(rectEmp,ARGB(128,208,223,233));
                  pgraphics->SelectObject(ptab->get_data()->m_brushText);
               }
               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText, e align_center, e_draw_text_no_prefix);
               rectText.left += sSep.cx;
               pgraphics->selectFont(font);
               pgraphics->SelectObject(brushText);
            }
         }

      }

   }



   bool theme::_001OnTabLayout(::user::tab * ptab)
   {


      {

         //         ::u32 dwTime2= ::millis::now();

         //TRACE("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //TRACE("usertab::on_layout call time1= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
      }
      if(!ptab->get_data()->m_bCreated)
         return false;

      ::user::tab::data * pdata = ptab->get_data();

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      auto pgraphics = create_memory_graphics();

      pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

      ptab->select(pgraphics);

      pdata->m_rectMargin = ptab._001GetRect(::user::rect_tab_margin);

      pdata->m_rectBorder = ptab._001GetRect(::user::rect_tab_border);

      pdata->m_rectTextMargin = ptab._001GetRect(::user::rect_tab_padding);

      if (pdata->m_bVertical)
      {

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata.m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata.m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata.m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata.m_rectMargin.right;

      }
      else
      {

         pdata->m_iTabHeight += pdata->m_rectBorder.top + pdata.m_rectBorder.bottom +
                                pdata->m_rectMargin.top + pdata.m_rectMargin.bottom;

         pdata->m_iTabWidth += pdata->m_rectBorder.left + pdata.m_rectBorder.right +
                               pdata->m_rectMargin.left + pdata.m_rectMargin.right;

      }


      ptab->m_dcextension.GetTextExtent(pgraphics,MAGIC_PALACE_TAB_SIZE,ptab->get_data()->m_sizeSep);



      if(ptab->get_data()->m_bVertical)
      {
         i32 iTabWidth = 16;
         i32 iTabHeight = 8;
         i32 cx;
         i32 cy;
         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               continue;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            ::size size;

            ptab->m_dcextension.GetTextExtent(pgraphics,str,size);



/*            if(tab_pane.m_pimage->is_set())
            {
/*               size.cx += tab_pane.m_pimage->width() + 2;
/*               size.cy = max(size.cy,tab_pane.m_pimage->height());
            }
            cx = size.cx + 2;

            if(!tab_pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if(cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy + 2;
            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabWidth += ptab->get_data()->m_rectBorder.left + ptab->get_data().m_rectBorder.right +
                      ptab->get_data()->m_rectMargin.left + ptab->get_data().m_rectMargin.right +
                      ptab->get_data()->m_rectTextMargin.left + ptab->get_data().m_rectTextMargin.right;

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data().m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data().m_rectMargin.bottom +
                       ptab->get_data()->m_rectTextMargin.top + ptab->get_data().m_rectTextMargin.bottom;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         ::rect rectClient;
         ptab->get_client_rect(rectClient);

         ptab->get_data()->m_rectTab.left       = rectClient.left;
         ptab->get_data()->m_rectTab.top        = rectClient.top;
         ptab->get_data()->m_rectTab.right      = ptab->get_data()->m_rectTab.left + ptab->get_data().m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom     = rectClient.bottom;

         /*      m_puserinteraction->set_window_pos(
         zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left       = ptab->m_bShowTabs ? ptab->get_data().m_rectTab.right : rectClient.left;
         ptab->get_data()->m_rectTabClient.top        = ptab->get_data().m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right      = rectClient.right;
         ptab->get_data()->m_rectTabClient.bottom     = ptab->get_data().m_rectTab.bottom;

      }
      else
      {
         i32 iTabHeight = 16;
         i32 cy;
         ::draw2d::graphics_pointer graphics(e_create);
         pgraphics->CreateCompatibleDC(nullptr);
         ::draw2d::graphics_pointer & pgraphics = graphics;

         pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

         ::rect rectClient;
         ptab->get_client_rect(rectClient);
         int x = rectClient.left;

         i32 ixAdd;
         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if(!tab_pane.m_bTabPaneVisible)
               return false;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension,graphics);

            size size;

            ptab->m_dcextension.GetTextExtent(pgraphics,str,size);

/*            if(tab_pane.m_pimage)
            {

/*               size.cy = max(size.cy,tab_pane.m_pimage->height());

            }

            cy = size.cy + 2;

            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            tab_pane.m_point.x = x;
            tab_pane.m_point.y = rectClient.top;


            //            string str = tab_pane.get_title();

            //            size size;

            ixAdd = 5;

/*            if(tab_pane.m_pimage->is_set())
            {
               //::image_list::info ii;
/*               ixAdd += tab_pane.m_pimage->width() + 2;
            }

            if(!tab_pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            tab_pane.m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data().m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data().m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data().m_rectTextMargin.right;

            x += tab_pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data().m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom + ptab->get_data().m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            tab_pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left       = rectClient.left;
         ptab->get_data()->m_rectTab.top        = rectClient.top;
         ptab->get_data()->m_rectTab.right      = rectClient.right;
         ptab->get_data()->m_rectTab.bottom     = ptab->get_data()->m_rectTab.top + ptab->get_data().m_iTabHeight;

         /*      set_window_pos(
         zorder_top,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         rect & rectTabClient = ptab->get_data()->m_rectTabClient;

         rectTabClient.left       = ptab->get_data()->m_rectTab.left;
         rectTabClient.top        = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.bottom : rectClient.top;
         rectTabClient.right      = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom     = rectClient.bottom;

         //TRACE0("rectTabClient");

      }

      for(i32 iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         if(iPane != ptab->_001GetSel())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->_001GetSel(), ptab->is_window_visible());

      return true;

   }


   bool theme::on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow)
   {

      if (eevent == ::user::event_calc_item_height)
      {

         pframewindow->m_iItemHeight += 8;

         return true;

      }

      return false;

   }


   bool theme::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar)
   {

      _001DrawLiteToolbarItem(pgraphics, iItem, ptoolbar);

      return true;

   }


   void theme::_001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rectItem;

      ::rect rectImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      __pointer(::user::menu_central) pmenucentral = psession->userex()->menu();

/*      ::u32 uImage = pmenucentral->command_image(item.m_id);

      ::user::toolbar::e_element eelement = ::user::toolbar::element_item;
/*      ::user::toolbar::e_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::e_element eelementText = ::user::toolbar::element_text;
      if ((nStyle & e_toolbar_button_style_separator) == 0)
      {
         if ((nStyle & e_toolbar_button_style_disabled) == 0)
         {
            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::element_item_press;
                     eelementImage = ::user::toolbar::element_image_press;
                     eelementText = ::user::toolbar::element_text_press;
                  }
                  else
                  {
                     eelement = ::user::toolbar::element_item_hover;
                     eelementImage = ::user::toolbar::element_image_hover;
                     eelementText = ::user::toolbar::element_text_hover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::element_item_hover;
               eelementImage = ::user::toolbar::element_image_hover;
               eelementText = ::user::toolbar::element_text_hover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::element_item;
/*            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::element_item;
/*         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

      ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

      if ((nStyle & e_toolbar_button_style_separator) != 0)
      {
         ::rect rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;
         pgraphics->draw3d_rect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));
      }
      else
      {
         if (eelement == ::user::toolbar::element_item_hover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

/*               ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  System.imaging().color_blend(
                  pgraphics,
                  rectItem.left,
                  rectItem.top,
                  rectItem.width(),
                  rectItem.height(),
                  RGB(255, 255, 250), 208);

                  pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));
               }

               if (uImage != 0xffffffffu)
               {

                  if ((nStyle & e_toolbar_button_style_disabled) == 0)
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rect rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::element_item_hover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1, ARGB(184, 92, 184, 92));
                  ::draw2d::brush_pointer brush(e_create);

                  brush->create_solid(ARGB(123, 177, 184, 255));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

/*               if (item.m_pimage->is_set())
               {

                  ::rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image_hover);

/*                  System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 0->84);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_item_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rect.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::element_item_press)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ARGB(255, 92, 92, 92));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ARGB(255, 255, 255, 255));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

/*            if (item.m_pimage->is_set())
            {

               ::rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image_press);

/*               System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 1->0);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & e_toolbar_button_style_disabled) == 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               pgraphics->fill_rect(rectItem, ARGB(184, 255, 255, 255));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

            }

/*            if (item.m_pimage->is_set())
            {

               ::rect rect;

/*               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image);

/*               System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 0->23);

            }
            else if (uImage != 0xffffffff)
            {

               if ((nStyle & e_toolbar_button_style_disabled) == 0)
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         ::rect rectText;

         ::draw2d::brush_pointer brushText(e_create);

         if ((nStyle & e_toolbar_button_style_disabled) == 0)
         {

            brushText->create_solid(ARGB(255, 0, 0, 0));

         }
         else
         {

            brushText->create_solid(ARGB(255, 123, 123, 118));

         }

         pgraphics->SelectObject(brushText);

         if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
         {

            pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }

   void theme::_001DrawLiteToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rectItem;

      ::rect rectImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      ::u32 nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      __pointer(::user::menu_central) pmenucentral = psession->userex()->menu();

/*      ::u32 uImage = pmenucentral->command_image(item.m_id);

      ::user::toolbar::e_element eelement = ::user::toolbar::element_item;
/*      ::user::toolbar::e_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::e_element eelementText = ::user::toolbar::element_text;

      if ((nStyle & e_toolbar_button_style_separator) == 0)
      {

         if ((nStyle & e_toolbar_button_style_disabled) == 0)
         {

            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::element_item_press;
                     eelementImage = ::user::toolbar::element_image_press;
                     eelementText = ::user::toolbar::element_text_press;
                  }
                  else
                  {
                     eelement = ::user::toolbar::element_item_hover;
                     eelementImage = ::user::toolbar::element_image_hover;
                     eelementText = ::user::toolbar::element_text_hover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::element_item_hover;
               eelementImage = ::user::toolbar::element_image_hover;
               eelementText = ::user::toolbar::element_text_hover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::element_item;
/*            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::element_item;
/*         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

      ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

      if (item.m_id.compare_ci("separator") == 0)
      {
         /*::rect rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;*/
         //pgraphics->Draw3dRect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));
      }
      else
      {
         if (eelement == ::user::toolbar::element_item_hover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

/*               ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  System.imaging().color_blend(
                  pgraphics,
                  rectItem.left,
                  rectItem.top,
                  rectItem.width(),
                  rectItem.height(),
                  RGB(255, 255, 250), 208);

                  pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));
               }

               if (uImage != 0xffffffffu)
               {

                  if ((nStyle & e_toolbar_button_style_disabled) == 0)
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               ::rect rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::element_item_hover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_pointer pen(e_create);

                  pen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_hover));
                  ::draw2d::brush_pointer brush(e_create);

                  brush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_hover));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

/*               if (item.m_pimage->is_set())
               {

                  ::rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image_hover);

/*                  System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 0->84);

               }
               else if (uImage != 0xffffffffu)
               {

                  ::rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_item_hover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uImage, rect.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::element_item_press)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ptoolbar->_001GetColor(::user::color_button_background_press));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ptoolbar->_001GetColor(::user::color_button_background_press));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

/*            if (item.m_pimage->is_set())
            {

               ::rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image_press);

/*               System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 1->0);

            }
            else if (uImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & e_toolbar_button_style_disabled) == 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               pgraphics->fill_rect(rectItem, _001GetColor(::user::color_button_background));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

            }

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_pointer pen(e_create);

               pen->create_solid(1, ptoolbar->_001GetColor(
                                 (nStyle & e_toolbar_button_style_disabled) == 0 ?
                                 ::user::color_button_background :
                                 ::user::color_button_background_disabled));
               ::draw2d::brush_pointer brush(e_create);

               brush->create_solid(ptoolbar->_001GetColor(
                                   (nStyle & e_toolbar_button_style_disabled) == 0 ?
                                   ::user::color_button_background :
                                   ::user::color_button_background_disabled));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

/*            if (item.m_pimage->is_set())
            {

               ::rect rect;

/*               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image);

/*               System.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_pimage->g(), ::point(), 0->23);

            }
            else if (uImage != 0xffffffff)
            {

               if ((nStyle & e_toolbar_button_style_disabled) == 0)
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         ::rect rectText;

         ::draw2d::brush_pointer brushText(e_create);

         if ((nStyle & e_toolbar_button_style_disabled) == 0)
         {

            brushText->create_solid(ARGB(255, 255, 255, 255));

            pgraphics->set_text_color(ARGB(255, 255, 255, 255));

         }
         else
         {

            brushText->create_solid(ptoolbar->_001GetColor(

                                    ::user::color_button_text_disabled));

            pgraphics->set_text_color(ptoolbar->_001GetColor(

                                      ::user::color_button_text_disabled));

         }

         if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
         {

            pgraphics->SelectObject(brushText);

            pgraphics->draw_text(item.m_str, item.m_str.get_length(), rectText, e_align_bottom_left, e_draw_text_no_prefix);

         }

      }

   }


   bool theme::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      ::rect rectClient;

      psplitlayout->get_client_rect(rectClient);

      pgraphics->fill_rect(rectClient, ARGB(255, 255, 255, 255));

      return true;

   }


   bool theme::get_font(::draw2d::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext)
   {

      return ::user::theme::get_font(sp, efont, pcontext);

   }


   bool theme::get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext)
   {

      if (edouble == ::user::double_list_item_height_rate)
      {

         d = 1.65;

         return true;

      }

      return ::user::style::get_double(d, edouble, pcontext);

   }


} // namespace lite




