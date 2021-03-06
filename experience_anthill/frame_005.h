#pragma once



namespace experience
{


   namespace anthill
   {


            class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_brushGrip;
               ::draw2d::brush_pointer                m_brushTextCaption;


               frame_005();
               virtual ~frame_005();


               virtual void on_initialize_experience_frame() override;

               virtual void on_style_change() override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, e_border eborder, color32_t crTopLeft, color32_t crBottomRight) override;
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_border eside);
               void GetBorderRect(const ::rect & rectClient, LPRECT32 lprect, e_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point) override;


            };



   } // namespace anthill


} // namespace experience




