#pragma once


namespace user
{


   class CLASS_DECL_AXIS combo_list :
      virtual public ::user::scroll_base
   {
   public:


      ::millis                              m_millisKillFocus;
      bool                                m_bPendingKillFocusHiding;
      bool                                m_bMovingComboBox;
      bool                                m_bComboList;
      __pointer(combo_box)                m_pcombo;
      int                                 m_iBorder;
      int                                 m_iPadding;
      int                                 m_iMinListItemCount;
      ::user::item                        m_itemLButtonDown;
      //::user::frame_window *            m_puiDeactivateTogether;
      ::user::interaction *               m_puiDeactivateTogether;

      millis                                m_millisLastVisibilityChange;


      combo_list();
      virtual ~combo_list();


      void user_combo_list_common_construct();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001OnDrawVerisimple(::draw2d::graphics_pointer & pgraphics);
      //virtual void _001OnDrawSimply(::draw2d::graphics_pointer & pgraphics);

      //virtual void _002OnDrawVerisimple(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawComboList(::draw2d::graphics_pointer & pgraphics);

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE32 psize);


      virtual ::draw2d::font_pointer get_font(style* pstyle, e_element eelement = element_none, estate estate = e_state_none) const override;


      virtual i32 _001GetItemHeight() const;

      virtual void on_change_combo_sel(index iSel);

      bool pre_create_window(::user::create_struct & cs) override;

      virtual void _001EnsureVisible(index iItem);

      //virtual void nextstyle(style_context* pcontext) override;

      virtual void _001OnTimer(::timer* ptimer) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual void on_hit_test(::user::item & item) override;


      virtual ::user::item current_item() override;
      virtual ::user::item hover_item() override;


      virtual bool keyboard_focus_is_focusable() override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;


      //virtual bool display(int nCmdShow) override;

      virtual bool has_pending_graphical_update() override;


      void on_drop_down(const ::rect & rectWindow, const ::size & sizeFull);


      //virtual bool get_font(::draw2d::font_pointer & spfont, e_font efont, ::user::interaction * pinteraction) override;

      virtual void _on_show_window() override;

   };


} //  namespace user



