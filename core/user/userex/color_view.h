#pragma once


namespace userex
{


   class CLASS_DECL_CORE color_view :
      virtual public ::user::impact
   {
   public:


      bool                             m_bCompact;
      bool                             m_bLButtonPressed;
      ::user::plain_edit_view          m_editRed;
      ::user::plain_edit_view          m_editGreen;
      ::user::plain_edit_view          m_editBlue;
      ::user::plain_edit_view          m_editHex;

      ::image_pointer                  m_pimageTemplate;
      ::image_pointer                  m_pimage;
      ::image_pointer                  m_pimageLuminance;

      ::hls                            m_hls;

      ::rect                           m_rectColors;


      color_view();
      virtual ~color_view();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void draw_beam(::draw2d::graphics_pointer & pgraphics, const ::point & point);
      virtual void draw_level(::draw2d::graphics_pointer & pgraphics, const ::rect & rectW, int y);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_mouse(const ::point & point);
      virtual void rebuild_luminance();

      virtual color get_color();
      virtual void set_color(color color);

   };


} // namespace userex



namespace flag
{


   CLASS_DECL_CORE void dk(::draw2d::graphics_pointer & pgraphics, double x, double y, double w, double h);


} // namespace flag


namespace visual
{


   CLASS_DECL_CORE void gay_with_shades_of_grey(::image * pimage);

   CLASS_DECL_CORE void shades_of_luminance(::image * pimage, double dH, double dS);


} // namespace visual



