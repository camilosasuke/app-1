#include "framework.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7





   namespace experience
   {


      


         namespace tranquillum

         {


            frame_005::frame_005() :
               m_brushGrip(e_create),
               m_brushTextCaption(e_create)
            {

               set_style(StyleLightGreen);

               //      SetStyle(StyleLightBlue);

            }

            frame_005::~frame_005()
            {

            }


            void frame_005::on_initialize_experience_frame()
            {

               frame::on_initialize_experience_frame();

               m_brushGrip->create_solid(ARGB(0xff, 0x60, 0x65, 0x55));

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               auto pgraphics = pframewindow->create_memory_graphics();

               auto pstyle = pframewindow->get_style(pgraphics);

               auto colorCaptionText = pframewindow->get_color(pstyle, ::user::element_window_title);

               m_brushTextCaption->create_solid(colorCaptionText);
}


            e_hittest frame_005::_001HitTest(const ::point & pointCursor)
            {
               e_hittest etest = hittest_client;
               {
                  //      m_pframewindow->GetEventWindow()->_001ScreenToClient(point);
                  ::rect rectEvent;
                  m_pframewindow->get_window_rect(rectEvent);
                  ::rect rect;
                  ::point pointCenter = rectEvent.center();
                  e_grip egrip = m_pframewindow->size_manager()->GetGripMask();

                  ::point pointHitTest = pointCursor;

                  if(rectEvent.left < 0)
                     pointHitTest.x -= rectEvent.left;
                  if(rectEvent.top < 0)
                     pointHitTest.y -= rectEvent.top;

                  if(egrip & grip_top_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_top_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom_right)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_right;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom_left)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_top)
                  {
                     rect.top = rectEvent.top;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_top;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_bottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = pointCenter.x - 8;
                     rect.right = pointCenter.x + 8;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_bottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_left)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_left;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & grip_right)
                  {
                     rect.top = pointCenter.y - 8;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = pointCenter.y + 8;
                     if(rect.contains(pointHitTest))
                     {
                        etest = hittest_sizing_right;
                        goto SizingSuccess;
                     }
                  }
                  goto SizingNone;
SizingSuccess:
                  return etest;
SizingNone:;
               }
               return hittest_client;
            }




            void frame_005::draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient,

                  e_border eside)
            {

               auto pframewindow = m_pframewindow;

               if (pframewindow == nullptr)
               {

                  return;

               }

               auto psession = Session;

               color32_t    crMoveableBorder;
               color32_t    crMoveableBorderHilight;
               color32_t    crMoveableBorderShadow;

               if(pframewindow->is_active())
               {
                  crMoveableBorder = m_crMoveableBorder;
                  crMoveableBorderHilight = m_crMoveableBorderHilight;
                  crMoveableBorderShadow = m_crMoveableBorderShadow;
               }
               else
               {

                  auto psession = Session;

                  auto pstyle = pframewindow->get_style(pgraphics);

                  crMoveableBorder = pframewindow->get_color(pstyle, ::user::element_button_background);

                  crMoveableBorderHilight = pframewindow->get_color(pstyle, ::user::element_button_hilite);

                  crMoveableBorderShadow = pframewindow->get_color(pstyle, ::user::element_button_shadow);

}

               e_dock edock = m_pframewindow->dock_manager()->get_dock_mask();
               ::rect rectA(rectClient);


               if(m_estyle == StyleTranslucidWarmGray
                     || m_estyle == StyleTranslucidLightBlue
                     || m_estyle == StyleTranslucidLightGreen)
               {

                  ::rect rect;

                  GetBorderRect(rectClient, rect, eside);


                  ColorGlass(pgraphics, rect, crMoveableBorder, 127);

               }
               else if(m_estyle == StyleLightBlue)
               {
                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, 0);//m_crMoveableBorderDkShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorderHilight, crMoveableBorderShadow);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  rectA.deflate(1, 1, 1, 1);
                  Draw3dRectSide(pgraphics, rectA, eside, crMoveableBorder, crMoveableBorder);

                  ::rect rect;
                  GetBorderRect(rectClient, rect, eside);

                  class imaging & imaging = System.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  ::rect rect;
                  GetBorderRect(rectClient, rect, eside);


                  ColorGlass(pgraphics, rect, crMoveableBorder, 230);

                  ::rect rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == dock_none)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }
               }

            }

            void frame_005::on_draw_frame(::draw2d::graphics_pointer & pgraphics)
            {

               auto pframewindow = m_pframewindow;

               if(pframewindow == nullptr)
                  return;

               if(!pframewindow->is_frame_experience_enabled())
                  return;

               bool bZoomed = pframewindow->layout().is_zoomed();

               ::rect rectClient;
               pframewindow->get_client_rect(rectClient);


               string str;


               ::rect rectNClient;

               pframewindow->get_window_rect(rectNClient);

               rectNClient -= rectNClient.top_left();

               ////////////////////
               //
               // Routine:
               // draw frame border
               //
               ////////////////////


               if(!pframewindow->layout().is_full_screen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }


               ///////////////////////
               //
               // Routine:
               // draw resize grip set
               //
               ///////////////////////

               if(!bZoomed && !pframewindow->layout().is_full_screen())
               {
                  DrawGripSet(pgraphics, rectNClient);
               }

               //          pgraphics->SetBkMode(iOriginalBkMode);
               //            pgraphics->set_text_color(crOriginalTextColor);

            }


            void frame_005::DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)

            {
               auto pmovemanager = m_pframewindow->move_manager();

               e_border eborder = pmovemanager->GetBorderMask();

               if(m_pframewindow->layout().is_zoomed())
               {
                  eborder = (e_border)
                            (eborder &
                             ~(border_right
                               | border_bottom
                               | border_left));
               }

               if(eborder & border_top)
               {
                  draw_border_side(pgraphics, rectClient, border_top);

               }
               if(eborder & border_right)
               {
                  draw_border_side(pgraphics, rectClient, border_right);

               }
               if(eborder & border_bottom)
               {
                  draw_border_side(pgraphics, rectClient, border_bottom);

               }
               if(eborder & border_left)
               {
                  draw_border_side(pgraphics, rectClient, border_left);

               }

            }

            void frame_005::GetBorderRect(
            const ::rect & rectClient,

            RECT32 * prect,

            e_border eside)
            {
               ::rect rectBig(rectClient);

               ::rect rectSmall;
               get_window_client_rect(rectSmall);
               ::rect rect;
               if(eside == border_top)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectBig.top;
                  rect.bottom = rectSmall.top;
               }
               else if(eside == border_left)
               {

                  rect.left = rectBig.left;
                  rect.right = rectSmall.left;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;

               }
               else if(eside == border_right)
               {

                  rect.left = rectSmall.right;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;

               }
               else if(eside == border_bottom)
               {

                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.bottom;
                  rect.bottom = rectBig.bottom;

               }

               *prect = rect;


            }


            void frame_005::Draw3dRectSide(::draw2d::graphics_pointer & pgraphics,const rect & rectParam,e_border eborder,color32_t crTopLeft,color32_t crBottomRight)
            {

               auto psession = Session;



               ::rect rect(rectParam);
               i32 x = rect.left;
               i32 y = rect.top;
               i32 cx = rect.width();
               i32 cy = rect.height();

               ::rect rectDraw;

               if(eborder & border_top)
               {

                  rectDraw = ::rect_dim(x, y, cx, 1);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rect(rectDraw, crTopLeft);

                  }
                  else
                  {
                     ColorGlass(pgraphics, rectDraw, crTopLeft, 127);

                  }

               }

               if(eborder & border_left)
               {

                  rectDraw = ::rect_dim(x, y + 1, 1, cy - 2);

                  if(psession->savings().is_trying_to_save(::e_resource_processing))
                  {

                     pgraphics->fill_rect(rectDraw, crTopLeft);

                  }
                  else
                  {

                     ColorGlass(pgraphics, rectDraw, crTopLeft, 127);

                  }

               }

               if(eborder & border_right)
               {

                  rectDraw = ::rect_dim(x + cx - 1, y + 1, 1, cy - 2);

                  if(psession->savings().is_trying_to_save(e_resource_processing))
                  {

                     pgraphics->fill_rect(rectDraw, crBottomRight);

                  }
                  else
                  {

                     ColorGlass(pgraphics, rectDraw, crBottomRight, 127);

                  }

               }

               if(eborder & border_bottom)
               {

                  rectDraw = ::rect_dim(x, y + cy - 1, cx, 1);

                  if(psession->savings().is_trying_to_save(e_resource_processing))
                  {

                     pgraphics->fill_rect(rectDraw, crBottomRight);

                  }
                  else
                  {

                     ColorGlass(pgraphics, rectDraw, crBottomRight, 127);

                  }

               }

            }

            void frame_005::on_style_change()
            {

               on_style_change_001_and_002();


            }

#define BEVEL_SMALL 2
#define BEVEL_LARGE 5
#define GRIP_SMALL 8
#define GRIP_LARGE 30

            void frame_005::DrawGrip(
            ::draw2d::graphics_pointer & pgraphics,
            const ::rect & rectClientParam,

            e_grip egrip)
            {

               const i32 size = 16;

               ::rect rectClient(rectClientParam);

               //            ::rect rectClientB(rectClient);
               ::rect rectA;
               ::point pointA;
               ::point pointB;
               ::point pointC;
               //            ::rect rect(rectClient);
               switch(egrip)
               {
               case grip_top_left:
               {

                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.bottom = size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

                  rectA.right = size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);

               }
               break;
               case grip_top_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.bottom = size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

                  rectA.left = rectA.right - size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);
               }
               break;
               case grip_bottom_left:
               {
                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

                  rectA.right = size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);
               }
               break;
               case grip_bottom_right:
               {
                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.bottom - size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

                  rectA.left = rectA.right - size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);
               }
               break;
               case grip_top:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.bottom = 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);

               }
               break;
               case grip_bottom:
               {
                  rectA = rectClient;

                  rectA.left = rectA.left + rectA.width() / 2 - size / 2;
                  rectA.right = rectA.left + size;
                  rectA.top = rectA.bottom - 4;

                  pgraphics->fill_rect(rectA, m_brushGrip);
               }
               break;
               case grip_left:
               {

                  rectA = rectClient;

                  rectA.right = 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

               }
               break;
               case grip_right:
               {

                  rectA = rectClient;

                  rectA.left = rectA.right - 4;
                  rectA.top = rectA.top + rectA.height() / 2 - size / 2;
                  rectA.bottom = rectA.top + size;

                  pgraphics->fill_rect(rectA, m_brushGrip);

               }
               break;
               default:
                  break;
               }


            }


            void frame_005::DrawRectGrip(::draw2d::graphics_pointer & pgraphics,const rect & rectParam)
            {

               auto psession = Session;

               auto pframewindow = m_pframewindow;

               auto pstyle = pframewindow->get_style(pgraphics);

               auto crButtonHilite = pframewindow->get_color(pstyle, ::user::element_button_hilite);

               auto crButtonDarkShadow = pframewindow->get_color(pstyle, ::user::element_button_dark_shadow);

               auto crButtonFace = pframewindow->get_color(pstyle, ::user::element_button_background);

               auto crButtonShadow = pframewindow->get_color(pstyle, ::user::element_button_shadow);

               ::rect rect(rectParam);

               pgraphics->draw_3drect(rect, crButtonFace, crButtonDarkShadow);

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->draw_3drect(rect, crButtonHilite, crButtonShadow);

               rect.top++;
               rect.bottom--;
               rect.left++;
               rect.right--;

               pgraphics->fill_rect(rect, crButtonFace);

            }


            void frame_005::DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient)

            {

               size_manager * psizemanager = m_pframewindow->size_manager();

               if(psizemanager == nullptr)
                  return;

               e_grip egrip = psizemanager->GetGripMask();

               if(egrip & grip_top)
               {
                  DrawGrip(pgraphics, rectClient, grip_top);

               }
               if(egrip & grip_top_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_right);

               }
               if(egrip & grip_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_right);

               }
               if(egrip & grip_bottom_right)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_right);

               }
               if(egrip & grip_bottom)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom);

               }
               if(egrip & grip_bottom_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_bottom_left);

               }
               if(egrip & grip_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_left);

               }
               if(egrip & grip_top_left)
               {
                  DrawGrip(pgraphics, rectClient, grip_top_left);

               }

            }


         } // namespace tranquillum

   } // namespace experience



