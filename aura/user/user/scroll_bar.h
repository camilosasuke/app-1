#pragma once


namespace user
{


   class CLASS_DECL_AURA scroll_bar :
      virtual public ::user::control
   {
   public:


      e_orientation                    m_eorientation;
      scroll_info                      m_scrollinfo;
      bool                             m_bTracking;




      scroll_bar();
      virtual ~scroll_bar();

      virtual i32 _001GetScrollPos() = 0;
      virtual i32 _001SetScrollPos(i32 iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;


      virtual bool create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id);

      virtual void send_scroll_message(UINT nSBCode);

      virtual ::point get_parent_viewport_offset() const override;
      virtual ::point get_ascendant_viewport_offset() const override;
      
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool GetTrackRect(RECT* prect);


      virtual ::color scrollbar_color_strong(::user::style* pstyle, ::user::e_element eelement);
      virtual ::color scrollbar_color(::user::style* pstyle, ::user::e_element eelement);
      virtual ::color scrollbar_border_color(::user::style* pstyle, ::user::e_element eelement);
      virtual ::color scrollbar_lite_border_color(::user::style* pstyle, ::user::e_element eelement);
      virtual ::color scrollbar_draw_color(::user::style* pstyle, ::user::e_element eelement);

   };


} // namespace user


