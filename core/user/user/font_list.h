#pragma once


namespace user
{


   class font_list;


   class CLASS_DECL_CORE font_list :
      virtual public combo_list
   {
   public:



      enum timer
      {

         timer_update_font = USER_TIMER,

      };


      __pointer(::draw2d::font_list)   m_pfontlist;
      ::rect                           m_rectMargin;
      bool                             m_bEnsureVisible;
      bool                             m_bFirstShown;



      font_list();
      virtual ~font_list();


      void user_font_list_common_construct();


      virtual void on_font_change();


      virtual void on_change_combo_sel(index iSel) override;

      //void attach_visual_font_list(::draw2d::font_list * pdata);
      //virtual void on_update_data(::draw2d::font_list * pdata, i32 iHint);

      //virtual void font_list_update();

      //virtual void assert_valid() const;
      //virtual void dump(dump_context & dumpcontext) const;

      //virtual bool get_color(COLORREF & cr, e_color ecolor, ::user::interaction * pinteraction) override;


      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      virtual void update(::update * pupdate) override;


      virtual ::user::item current_item() override;

      virtual ::user::item hover_item() override;

      string get_cur_sel_face_name();

      string get_cur_hover_face_name();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001EnsureVisible(index iItem) override;


      virtual void _001OnTimer(::timer * ptimer) override;

      virtual void on_hit_test(::user::item & item) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool set_sel_by_name(string str);

      virtual void ensure_sel_visible();

      virtual void __on_draw_ensure_sel_visible();

      virtual void query_full_size(::draw2d::graphics_pointer& pgraphics, LPSIZE psize) override;


      virtual bool update_data(bool bSaveAndValidate) override;

      virtual void set_font_list_type(::draw2d::font_list::e_type etype);


   };


   typedef ::user::show < ::user::font_list > font_list_view;


} // namespace user


