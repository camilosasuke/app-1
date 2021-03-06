#pragma once


class CLASS_DECL_BASE simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   ::draw2d::pen_pointer            m_penDraw;
   ::draw2d::brush_pointer          m_brushDraw;
   ::image_pointer                  m_pimageDots;
   bool                             m_bTrackOffsetThumbAdjusted;
   point                            m_pointTrack;
   ::rect                           m_rectTrack;
   ::rect                           m_rectA;
   ::rect                           m_rectB;
   point                            m_ptaA[4]; // pontos da primeira seta
   point                            m_ptaB[4]; // pontos da segunda seta
   ::draw2d::region_pointer         m_rgnA; // região da primeira seta
   ::draw2d::region_pointer         m_rgnB; // região da segunda seta
   ::u32                             m_uiTimer;


   simple_scroll_bar();
   virtual ~simple_scroll_bar();



   virtual void pre_translate_message(::message::message * pmessage) override;
   virtual bool create_window(const char * pszClassName,const char * pszWindowName,u32 uStyle, ::user::interaction * puiParent, const ::id & id, ::create * pcreate = nullptr) override;

   virtual void install_message_routing(::channel * pchannel) override;

   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
   virtual void _001OnVerisimpleDraw(::draw2d::graphics_pointer & pgraphics);

   void update_drawing_objects();

   virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

   bool GetPageARect(RECT32 * pRectClient, RECT32 * lpRectTrack,  RECT32 * prect, ::draw2d::graphics_pointer & pgraphics);

   bool GetPageBRect(RECT32 * pRectClient, RECT32 * lpRectTrack,  RECT32 * prect, ::draw2d::graphics_pointer & pgraphics);

   void UpdateBitmaps();
   //void OnDisplayChange(i32 iBitsPerPixel, ::size sizeScreen);
   //virtual void OnDraw(::image * pimage);
   virtual i32 _001GetScrollPos() override;
   virtual i32 _001SetScrollPos(i32 iPos) override;
   virtual bool _001GetScrollInfo(::user::scroll_info * psi) override;
   virtual bool _001SetScrollInfo(::user::scroll_info * psi, bool bRedraw = true) override;

   virtual bool create_window(e_orientation eorientation, u32 uStyle, ::user::interaction * puiParent, ::id id) override;

   i32 SetTrackingPos(const ::point & point, ::draw2d::graphics_pointer & pgraphics);
   i32 GetTrackSize(::size & size, ::draw2d::graphics_pointer & pgraphics);
   bool GetTrackClientRect(RECT32 * prect, ::draw2d::graphics_pointer & pgraphics);

   bool GetTrackRect(RECT32 * prect, ::draw2d::graphics_pointer & pgraphics) override;

   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnHScroll);
   void _001OnTimer(::timer * ptimer) override;
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnDestroy);
   LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);

   void draw_mac_thumb_simple(::draw2d::graphics_pointer & pgraphics,const ::rect & rectDraw,const ::rect & lpcrectClip,byte uchAlpha);

   void draw_mac_thumb_dots(::draw2d::graphics_pointer & pgraphics,const ::rect & rectDraw,const ::rect & lpcrectClip,byte uchAlpha);



   virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

   virtual void on_hit_test(::user::item & item) override;
   //virtual ::user::e_element _001HitTest(const ::point & point, index & iItem, index & iSubItem, index & iListItem) override;

   virtual bool scrollbar_action(const ::user::item & item, ::draw2d::graphics_pointer & pgraphics);

   virtual bool scrollbar_lineA(::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_lineB(::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_pageB(const ::point & point, ::draw2d::graphics_pointer & pgraphics);
   virtual bool scrollbar_pageA(const ::point & point, ::draw2d::graphics_pointer & pgraphics);

   virtual ::color scrollbar_color_strong(::user::style * pstyle, ::user::e_element eelement) override;
   virtual ::color scrollbar_color(::user::style* pstyle, ::user::e_element eelement)override;
   virtual ::color scrollbar_border_color(::user::style* pstyle, ::user::e_element eelement)override;
   virtual ::color scrollbar_lite_border_color(::user::style* pstyle, ::user::e_element eelement)override;
   virtual ::color scrollbar_draw_color(::user::style* pstyle, ::user::e_element eelement)override;


};


