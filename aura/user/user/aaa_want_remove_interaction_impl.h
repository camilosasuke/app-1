#pragma once

using window_pointer = __pointer(::user::interaction_impl);

#include "user_interaction_impl_base.h"


#ifdef __DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 180

#else //__DEBUG

#define PRODEVIAN_QUIT_TIMEOUT_SECONDS 5

#endif //!__DEBUG

#if defined _UWP && defined(__cplusplus_winrt)


namespace user
{


   class CLASS_DECL_AURA native_window
   {
   public:


      ::aura::system_window ^ m_pwindow;


   };


} // namespace user



//#define interaction_impl ::user::interaction

#elif defined(APPLE_IOS)

class CLASS_DECL_AURA native_window
{
public:

};

//#define interaction_impl ::user::interaction

#else

class native_window;

#endif


namespace user
{


   class prodevian;
   class window_thread;


   class CLASS_DECL_AURA interaction_impl:
      virtual public ::user::primitive
   {
   public:


      prodevian *                   m_pprodevian;
      window_thread *               m_pwindowthread;
      simple_object_ptra            m_ptraProdevian;
      bool                          m_bTransparentMouseEvents;
      bool                          m_bOfflineRender;
      bool                          m_bFocus;
      bool                          m_bCursorRedraw;
      double                        m_dConfigFps;
      double                        m_dOutputFps;
      bool                          m_bLockWindowUpdate;
      point                         m_pointCursor;
      bool                          m_bOkToUpdateScreen;

      object_ptra                   m_ptraRedraw;

      bool                          m_bPointInside;
      ::point                       m_pointInside;
      ::user::primitive *           m_pprimitiveFocus;

      oswindow                      m_oswindow;
      bool                          m_bScreenRelativeMouseMessagePosition;
      bool                          m_bTranslateMouseMessageCursor;
      bool                          m_bComposite;
      bool                          m_bUpdateGraphics;

      point                         m_point;
      size                          m_size;

      native_window *               m_pwindow;

      __pointer(window_graphics)           m_spgraphics;

      __pointer(::mutex)                     m_pmutexDraw;
      __pointer(::mutex)                     m_pmutexRedraw;

      ::user::interaction_ptra      m_guieptraMouseHover;

      UINT                          m_uiMessage;
      wparam                        m_wparam;
      lparam                        m_lparam;
      lparam                        m_lparamLastMouseMove;


      interaction_impl();
      virtual ~interaction_impl();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void set_config_fps(double dConfigFps) override;
      virtual double get_config_fps() override;
      virtual double get_output_fps() override;

      virtual void SetWindowDisplayChanged() override;

      void user_common_construct();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual ::mutex * draw_mutex();

      virtual ::user::interaction_impl * get_user_interaction_impl() override;



      virtual bool has_pending_focus();

      virtual bool set_pending_focus();

      virtual bool clear_pending_focus();

      virtual bool create_message_queue(::user::interaction * pinteraction, const char * lpszName) override;

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
      virtual bool initialize_native_window(::user::native_window_initialize * pinitialize) override = 0;
#endif


      virtual void _000OnMouseLeave(::message::message * pmessage) override;
      virtual void _008OnMouse(::message::mouse * pmouse);
      virtual void _001BaseWndInterfaceMap();

      virtual void prio_install_message_routing(::channel * pchannel) override;
      virtual void last_install_message_routing(::channel * pchannel) override;

      bool operator==(const interaction_impl& wnd) const;
      bool operator!=(const interaction_impl& wnd) const;

      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;
      virtual bool ModifyStyle(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove,u32 dwAdd,UINT nFlags = 0) override;


      virtual void mouse_hover_add(::user::interaction * pinterface) override;
      virtual bool mouse_hover_remove(::user::interaction * pinterface) override;

      virtual bool add_prodevian(::context_object * pobject) override;
      virtual bool remove_prodevian(::context_object * pobject) override;
      inline bool has_prodevian() const noexcept { return m_ptraProdevian.has_element(); }

      virtual void prodevian_stop() override;


      //virtual ::user::interaction * get_owner();
      virtual void set_owner(::user::interaction * pOwnerWnd);

      virtual bool has_pending_redraw_flags() override;


      virtual ::user::interaction_impl * from_os_data(void * pdata);
      virtual void * get_os_data() const;

      bool attach(oswindow oswindow_New) override;
      oswindow detach() override;

      virtual void set_finish() override;

      virtual void route_command_message(::user::command * pcommand) override;

      DECL_GEN_SIGNAL(_002OnDraw);

      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnApplyVisual);
      DECL_GEN_SIGNAL(_001OnDestroyWindow);
      DECL_GEN_SIGNAL(_001OnRedraw);
      DECL_GEN_SIGNAL(_001OnDoShowWindow);


#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)

      bool GetWindowInfo(PWINDOWINFO pwi) const;
      bool GetTitleBarInfo(PTITLEBARINFO pti) const;

#endif   // WINVER >= 0x0500

      // subclassing/unsubclassing functions
      virtual void pre_subclass_window() override;
      virtual bool subclass_window(oswindow oswindow) override;
      virtual bool SubclassDlgItem(UINT nID,::user::interaction_impl * pParent);
      virtual oswindow unsubclass_window() override;

      // handling of RT_DLGINIT resource (extension to RT_DIALOG)
      virtual bool ExecuteDlgInit(const char * pszResourceName);

      virtual bool ExecuteDlgInit(LPVOID pResource);





      using ::user::primitive::create_window;
      using ::user::primitive::create_window_ex;

      // for child windows, views, panes etc
      virtual bool create_window(::user::interaction * pinteraction, const char * pszClassName,const char * pszWindowName,u32 uStyle,const ::rect & rect,::user::interaction * puiParent,id id, ::create * pcreate = nullptr) override;


      // advanced creation (allows access to extended styles)
      virtual bool create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, ::user::interaction * puiParent, id id) override;


      virtual bool native_create_window_ex(::user::interaction * pinteraction, ::user::create_struct & cs, oswindow oswindowParent = nullptr, id id = ::id());

      virtual bool _native_create_window_ex(::user::create_struct & cs);


      virtual bool destroy_impl_only() override;
      virtual bool DestroyWindow() override;
      virtual void destroy_window() override;

      // special pre-creation and interaction_impl rect adjustment hooks
      virtual bool pre_create_window(::user::create_struct& cs) override;

      // Advanced: virtual AdjustWindowRect
//      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(RECT * pClientRect,UINT nAdjustType = adjustBorder) override;




      virtual bool _is_window() const override;

#if(WINVER >= 0x0500)

      virtual ::user::interaction_impl * GetAncestor(UINT gaFlags) const;

#endif   // WINVER >= 0x0500

      virtual LRESULT send_message(UINT message, WPARAM wParam = 0, lparam lParam = 0) override;


#ifdef LINUX

      virtual LRESULT send_x11_event(void * pevent); // XEvent *

#endif


      virtual bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0) override;


      virtual bool SendNotifyMessage(UINT message,WPARAM wParam,lparam lParam);

      //virtual bool SendChildNotifyLastMsg(LRESULT* pResult = nullptr);

      virtual bool DragDetect(const ::point & point) const;



      // Window Text Functions
      virtual void set_window_text(const char * pszString) override;

      virtual strsize GetWindowText(char * pszStringBuf,i32 nMaxCount);

      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();


      // Window size and position Functions
      //virtual bool window_is_iconic() override;
      //virtual bool window_is_zoomed() override;
      //virtual i32 SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual i32 GetWindowRgn(HRGN hRgn);

      //using ::user::primitive::set_window_pos;
      //virtual bool set_window_pos(class zorder zorder, i32 x, i32 y, i32 cx,i32 cy, UINT nFlags = SWP_SHOWWINDOW) override;
      virtual UINT ArrangeIconicWindows() override;
      //virtual bool BringWindowToTop() override;

#ifdef WINDOWS_DESKTOP
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);

#endif

      // Coordinate Mapping Functions
      virtual void MapWindowPoints(::user::interaction_impl * pwndTo,LPPOINT pPoint,UINT nCount);

      virtual void MapWindowPoints(::user::interaction_impl * pwndTo,RECT * prect);


      virtual void Print(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;
      virtual void PrintClient(::draw2d::graphics_pointer & pgraphics,u32 dwFlags) const;

      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = TRUE) override;
      virtual bool GetUpdateRect(RECT * prect,bool bErase = FALSE) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE) override;
      virtual void Invalidate(bool bErase = TRUE) override;
      virtual void InvalidateRect(const ::rect & rect,bool bErase = TRUE) override;

      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE) override;
      virtual void ValidateRect(const ::rect & rect) override;

      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      //virtual bool display(::edisplay edisplay) override;
      //virtual bool _is_window_visible() override;
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;

      virtual ::draw2d::graphics * GetDCEx(::draw2d::region* prgnClip,u32 flags);
      virtual bool LockWindowUpdate();
      virtual void UnlockWindowUpdate();

      virtual bool prodevian_update_screen() override;

      virtual void prodevian_redraw() override;

#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,UINT flags = RDW_INVALIDATE | RDW_ERASE);

#else

      virtual bool RedrawWindow(const ::rect & rectUpdate = nullptr, ::draw2d::region* prgnUpdate = nullptr,UINT flags = 0) override;

#endif


#ifdef WINDOWS_DESKTOP

      virtual bool EnableScrollBar(i32 nSBFlags,UINT nArrowFlags = ESB_ENABLE_BOTH);

#else

      virtual bool EnableScrollBar(i32 nSBFlags,UINT nArrowFlags = 3);

#endif


      //virtual bool DrawAnimatedRects(i32 idAni,CONST LPRECTprcFrom,CONST LPRECTlprcTo);


      virtual bool DrawCaption(::draw2d::graphics_pointer & pgraphics,const rect & prc,UINT uFlags);


#if(WINVER >= 0x0500)

      virtual bool AnimateWindow(tick tick,u32 dwFlags);

#endif


#if(_WIN32_WINNT >= 0x0501)

      virtual bool PrintWindow(::draw2d::graphics_pointer & pgraphics,UINT nFlags) const;

#endif


#if(_WIN32_WINNT >= 0x0500)

      virtual bool SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,u32 dwFlags);
      virtual bool UpdateLayeredWindow(::draw2d::graphics * pDCDst,POINT *pptDst,SIZE *psize,::draw2d::graphics * pDCSrc,POINT *pptSrc,COLORREF crKey,BLENDFUNCTION *pblend,u32 dwFlags);

#endif   // _WIN32_WINNT >= 0x0500

#if(_WIN32_WINNT >= 0x0501)

      virtual bool GetLayeredWindowAttributes(COLORREF *pcrKey,BYTE *pbAlpha,u32 *pdwFlags) const;

#endif   // _WIN32_WINNT >= 0x0501



      virtual bool is_window_enabled() override;
      virtual bool enable_window(bool bEnable = TRUE) override;

      virtual ::user::interaction * GetActiveWindow() override;
      virtual ::user::interaction * SetActiveWindow() override;

      virtual bool SetForegroundWindow() override;

      virtual id SetDlgCtrlId(id id) override;
      virtual id GetDlgCtrlId() const override;



      virtual bool SetCapture(::user::interaction * pinteraction = nullptr) override;
      virtual bool ReleaseCapture() override;
      virtual ::user::interaction * GetCapture() override;
      virtual bool SetFocus() override;

      virtual void CloseWindow();
      virtual bool OpenIcon();

      virtual void CheckDlgButton(i32 nIDButton,UINT nCheck);
      virtual void CheckRadioButton(i32 nIDFirstButton,i32 nIDLastButton,
                                    i32 nIDCheckButton);
      virtual i32 GetCheckedRadioButton(i32 nIDFirstButton,i32 nIDLastButton);
      virtual i32 DlgDirList(LPTSTR pPathSpec,i32 nIDListBox,

                             i32 nIDStaticPath,UINT nFileType);
      virtual i32 DlgDirListComboBox(LPTSTR pPathSpec,i32 nIDComboBox,

                                     i32 nIDStaticPath,UINT nFileType);
      virtual bool DlgDirSelect(LPTSTR pString,i32 nSize,i32 nIDListBox);

      virtual bool DlgDirSelectComboBox(LPTSTR pString,i32 nSize,i32 nIDComboBox);


      virtual UINT GetChildByIdInt(i32 nID,bool* pTrans = nullptr,bool bSigned = TRUE) const;

      virtual i32 GetChildByIdText(i32 nID,LPTSTR pStr,i32 nMaxCount) const;

      virtual i32 GetChildByIdText(i32 nID,string & rString) const;
      virtual ::user::interaction_impl * GetNextDlgGroupItem(::user::interaction_impl * pWndCtl,bool bPrevious = FALSE) const;
      virtual ::user::interaction_impl * GetNextDlgTabItem(::user::interaction_impl * pWndCtl,bool bPrevious = FALSE) const;
      virtual UINT IsDlgButtonChecked(i32 nIDButton) const;
      virtual LRESULT SendDlgItemMessage(i32 nID,UINT message,WPARAM wParam = 0,LPARAM lParam = 0);
      virtual void SetDlgItemInt(i32 nID,UINT nValue,bool bSigned = TRUE);
      virtual void SetDlgItemText(i32 nID,const char * pszString);


      virtual i32 GetScrollPos(i32 nBar) const;
      virtual void GetScrollRange(i32 nBar,LPINT pMinPos,LPINT lpMaxPos) const;
      virtual void ScrollWindow(i32 xAmount,i32 yAmount,
         LPCRECT rect = nullptr,
         LPCRECT pClipRect = nullptr);

      virtual i32 SetScrollPos(i32 nBar,i32 nPos,bool bRedraw = TRUE);
      virtual void SetScrollRange(i32 nBar, i32 nMinPos, i32 nMaxPos, bool bRedraw = TRUE);
      virtual void ShowScrollBar(UINT nBar,bool bShow = TRUE);
      virtual void EnableScrollBarCtrl(i32 nBar,bool bEnable = TRUE);

      virtual i32 ScrollWindowEx(i32 dx,i32 dy, LPCRECT prectScroll, LPCRECT lprectClip, ::draw2d::region* prgnUpdate, RECT * prectUpdate, UINT flags);


#ifdef WINDOWS_DESKTOP

      virtual bool SetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, bool bRedraw = TRUE);
      virtual bool GetScrollInfo(i32 nBar, LPSCROLLINFO pScrollInfo, UINT nMask = SIF_ALL);

#endif


      virtual i32 GetScrollLimit(i32 nBar);

#if (WINVER >= 0x0500) && defined(WINDOWS_DESKTOP)

      virtual bool GetScrollBarInfo(LONG idObject,PSCROLLBARINFO psbi) const;

#endif   // WINVER >= 0x0500

      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point) override;
      virtual ::user::interaction * ChildWindowFromPoint(const ::point & point,UINT nFlags) override;

#ifdef WINDOWS_DESKTOP
      virtual ::user::interaction * get_next_window(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction * get_next_window(UINT nFlag = 0) override;
#endif

      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * GetLastActivePopup() override;

      bool FlashWindow(bool bInvert);

      //virtual i32 message_box(const char * pszText,const char * pszCaption = nullptr,UINT nType = MB_OK);


#if(WINVER >= 0x0500)

      virtual bool FlashWindowEx(u32 dwFlags,UINT  uCount,tick tickTimeout);

#endif   // WINVER >= 0x0500

      virtual bool ChangeClipboardChain(oswindow oswindow_Next);
      virtual oswindow SetClipboardViewer();
      virtual bool OpenClipboard();

      virtual void HideCaret();
      virtual void ShowCaret();

      virtual void DragAcceptFiles(bool bAccept = TRUE);

      virtual bool SetWindowContextHelpId(u32 dwContextHelpId);
      virtual u32 GetWindowContextHelpId() const;


      virtual bool update_data(bool bSaveAndValidate = true) override;


      virtual void UpdateDialogControls(channel* pTarget,bool bDisableIfNoHndler);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = nullptr) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnPrint);
      DECL_GEN_SIGNAL(_001OnCaptureChanged);


#ifdef WINDOWS_DESKTOP

      DECL_GEN_SIGNAL(_001OnWindowPosChanged);

#endif




      virtual void BeginModalState();
      virtual void EndModalState();

      virtual void pre_translate_message(::message::message * pmessage) override;

      virtual void message_handler(::message::base * pbase) override;
      virtual LRESULT Default() override;
      virtual LRESULT DefWindowProc(UINT message,WPARAM wParam,lparam lParam) override;


      virtual void PostNcDestroy() override;
      virtual bool OnChildNotify(::message::base * pbase) override;
      virtual bool ReflectChildNotify(::message::base * pbase);
      virtual bool CheckAutoCenter() override;


      virtual bool HandleFloatingSysCommand(UINT nID,LPARAM lParam);
      virtual bool IsTopParentActive() override;
      virtual void ActivateTopParent() override;
      virtual void on_final_release();


      virtual bool _EnableToolTips(bool bEnable,UINT nFlag);
      virtual void PrepareForHelp();


      // for creating dialogs and dialog-like windows
      //virtual bool CreateDlg(const char * pszTemplateName, ::user::interaction_impl * puiParent);

      //virtual bool CreateDlgIndirect(LPCDLGTEMPLATE pDialogTemplate, ::user::interaction_impl * puiParent,

      // HINSTANCE hInst);



      //// standard message implementation
      //LRESULT OnNTCtlColor(WPARAM wParam,LPARAM lParam);
      //LRESULT OnDisplayChange(WPARAM,LPARAM);
      //LRESULT OnDragList(WPARAM,LPARAM);

/*      virtual void _001DeferPaintLayeredWindowBackground(::image * pimage);

/*      virtual void _001OnDeferPaintLayeredWindowBackground(::image * pimage);

      virtual LONG get_window_long(i32 nIndex) const override;
      virtual LONG set_window_long(i32 nIndex,LONG lValue) override;
      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex,LONG_PTR lValue) override;



      virtual interaction_impl * get_impl() const override;


      virtual void _001UpdateWindow() override;


      virtual bool start_window_visual() override;
      virtual bool prodevian_update_visual() override;
      virtual void _001UpdateBuffer();
      virtual void _001UpdateScreen();
      //virtual void window_apply_visual(const window_state & windowstate) override;


      virtual void window_thread_apply_visual();


      virtual void update_graphics_resources();


      virtual void set_handle(oswindow oswindow);
      virtual oswindow get_handle() const override;

      virtual window_graphics * get_window_graphics() override;

      virtual bool is_composite() override;


      virtual ::user::primitive * get_focus_elemental() override;
      virtual bool set_focus_elemental(::user::primitive * pelemental) override;
      virtual bool impl_set_focus_elemental(::user::primitive * pelemental);

      virtual void redraw_add(::object * point) override;
      virtual void redraw_remove(::object * point) override;
      virtual bool has_redraw() override;
      virtual ::mutex * mutex_redraw();

      virtual void _001OnTriggerMouseInside() override;

      virtual bool has_pending_graphical_update() override;

      virtual void on_after_graphical_update() override;

      virtual void _do_show_window() override;


      virtual bool ShowWindow(int iShow);

      //virtual bool check_need_layout() override;
//virtual void clear_need_layout() override;
      virtual void set_need_layout() override;

      //virtual bool check_show_flags() override;

      virtual void on_visual_applied();

      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void post_redraw(bool bAscendants = true) override;


   };


   class CLASS_DECL_AURA guie_message_wnd:
      virtual public interaction_impl
   {
   public:


      ::user::interaction * m_puiForward;


      guie_message_wnd(::object * pobject);


      virtual void message_handler(::message::base * pbase);

   }; // guie_message_wnd


} // namespace user


namespace user
{

   CLASS_DECL_AURA void __reposition_window(SIZEPARENTPARAMS * pLayout, ::user::interaction * pinteraction, const rect & rect);

} // namespace user

