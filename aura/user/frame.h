#pragma once


namespace userex
{


   class font_format_tool;


} // namespace userex


#ifndef TBSTYLE_FLAT
#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
#endif

/////////////////////////////////////////////////////////////////////////////
// General style bits etc

// ControlBar styles
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
#define CBRS_FLYBY          0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define CBRS_GRIPPER        0x00400000L
#define CBRS_LEAVEONFULLSCREEN     0x10000000L

#define CBRS_ORIENT_HORZ    (CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)
#define CBRS_ORIENT_VERT    (CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ORIENT_ANY     (CBRS_ORIENT_HORZ|CBRS_ORIENT_VERT)

#define CBRS_ALL            0x0040FFFFL
//#define CBRS_ALL            0x1140FFFFL

// the CBRS_ style is made up of an alignment style and a draw border style
//  the alignment styles are mutually exclusive
//  the draw border styles may be combined
#define CBRS_NOALIGN        0x00000000L
#define CBRS_LEFT           (CBRS_ALIGN_LEFT|CBRS_BORDER_RIGHT)
#define CBRS_TOP            (CBRS_ALIGN_TOP|CBRS_BORDER_BOTTOM)
#define CBRS_RIGHT          (CBRS_ALIGN_RIGHT|CBRS_BORDER_LEFT)
#define CBRS_BOTTOM         (CBRS_ALIGN_BOTTOM|CBRS_BORDER_TOP)


// Frame interaction_impl styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size to size of contained bars

namespace user
{


   class CLASS_DECL_AURA frame:
      virtual public interaction
   {
   public:


      bool                                         m_bDefaultNotifyIcon;
      string                                       m_strFrameTitle;
      ::size                                       m_sizeMinimum;
      //address_array < ::user::impact * >           m_viewptraCommandHandlers;       // current active ::user::impact
      bool                                         m_bCloseApplicationIfLastVisibleFrame;
      __pointer(::user::style)                     m_puserstyle;

  
      frame();
      virtual ~frame();

      
      virtual style * _get_style() const override;


      virtual void set_frame_title(const string& strFrameTitle);
      virtual string get_frame_title() const;


      virtual ::color get_border_main_body_color();

//      virtual bool window_is_full_screen() = 0;
      virtual ::user::interaction * GetActiveView() const = 0;           // active ::user::impact or nullptr
      virtual void SetActiveView(::user::interaction* pViewNew, bool bNotify = TRUE) = 0;

      virtual ::userex::font_format_tool * font_format_tool(bool bCreate = false);

      virtual void ActivateFrame(::edisplay edisplay = display_undefined) = 0;

      virtual bool LoadToolBar(id idToolBar, const char * pszToolBar, u32 dwCtrlStyle = TBSTYLE_FLAT, u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) = 0;

      virtual bool is_frame_window() override;

      virtual void InitialFramePosition(bool bForceRestore = false);

      virtual ::size get_window_minimum_size() override;





   };


} // namespace aura


