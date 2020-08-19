#pragma once


class prodevian;


namespace user
{

   
   class control_bar;


   enum e_interaction
   {

      interaction_wfi_up_down_loading = 1 << 0,
      interaction_wfi_up_tool_window = 1 << 1,

   };


   class CLASS_DECL_AURA interaction :
      virtual public layout,
      virtual public ::timer_callback
   {
   public:


      enum e_non_client
      {

         non_client_background = 1,
         non_client_focus_rect = 2,

      };

      enum e_updown
      {
         updown_normal_frame,
         updown_none,
         updown_up,
         updown_down,
      };

      // updown
      __pointer(::user::interaction)         m_pupdowntarget;
      ::user::interaction::e_updown          m_eupdown;
      //end updown

      //class draw_select
      //{
      //public:

      //   interaction* m_puserinteraction;
      //   ::draw2d::graphics* m_pgraphics;

      //   draw_select(interaction* pinteraction, ::draw2d::graphics_pointer & pgraphics) :
      //      m_puserinteraction(pinteraction),
      //      m_pgraphics(pgraphics)
      //   {

      //      m_puserinteraction->select(pgraphics);

      //      pgraphics->m_puserinteraction = pinteraction;

      //   }

      //   ~draw_select()
      //   {
      //      m_puserinteraction->select(nullptr);
      //   }

      //};

      __pointer_array(::user::item)                m_itema;
      bool                                         m_bOverdraw;
      ::user::frame *                              m_pframe;
      ::user::item                                 m_itemLButtonDown;
      ::index                                      m_iIndex;
      item                                         m_itemCurrent;
      item                                         m_itemHover;
      item                                         m_itemHoverMouse;
      ::size                                       m_sizeRestoreBroad;
      ::size                                       m_sizeRestoreCompact;
      //e_control_type                               m_econtroltype;
      flags < e_non_client >                       m_flagNonClient;
      bool                                         m_bTrackMouseLeave;
      bool                                         m_bMouseHover;
      bool                                         m_bSimpleUIDefaultMouseHandling;
      int                                          m_iMouseMoveSkipCount;
      int                                          m_iMouseMoveSkipSquareDistance;
      ::tick                                       m_tickMouseMoveSkip;
      ::point                                      m_pointMouseMoveSkip;
      ::tick                                       m_tickMouseMovePeriod;
      bool                                         m_bMouseMovePending;
      ::point                                      m_pointMouseMove;
      bool                                         m_bRedraw;
      bool                                         m_bNeedLoadFormData;
      bool                                         m_bNeedSaveFormData;
      tick                                         m_tickLastRedraw;
      ::id                                         m_idView;
      ::user::form *                               m_pform;
      ::user::form *                               m_pformParent;
      ::user::layout *                             m_playout;
      //e_color                                      m_ecolorBackground;
      ::color                                      m_colorBackground;
      bool                                         m_bWorkspaceFullScreen;
      point                                        m_pointScroll;
      bool                                         m_bHideOnTransparentFrame;
      bool                                         m_bOffScreenRender;
      bool                                         m_bMoveWindow;
      bool                                         m_bVoidPaint;
      bool                                         m_bRedrawing;
      bool                                         m_bLockWindowUpdate;
      bool                                         m_bLayoutEnable;
      bool                                         m_bNeedLayout;
      bool                                         m_bReposition;
      bool                                         m_bRedrawOnVisible;
      bool                                         m_bSaveWindowRect;
      bool                                         m_bEnableSaveWindowRect2;
      bool                                         m_bShowSoftwareKeyboard;
      bool                                         m_bUserInteractionSetFinish;
      //bool                                         m_bFreeHandMouseMove; this is the default
      // if high frequency mouse move notification is required
      // create a fast path/low latency callback system
      ::tick                                       m_tickMouseMove;
      ::tick                                       m_tickMouseMoveIgnore;
      alpha_source *                               m_palphasource;
      i32                                          m_iItemHeight;
      point                                        m_pointMoveCursor;
      bool                                         m_bDefaultWalkPreTranslateParentTree;
      ::aura::drawable *                           m_pdrawableBackground;
      bool                                         m_bBackgroundBypass;
      tick                                         m_tickLastFullUpdate;
      bool                                         m_bSizeMove;
      tick                                         m_tickLastVisualChange;
      __reference(::file::insert_item)             m_pitemComposing;
      __pointer(primitive_impl)                    m_pimpl;
      __pointer(interaction_impl)                  m_pimpl2;
      interaction *                                m_puserinteraction;
      interaction_ptra                             m_uiptraOwned;
      interaction_pointer_array                    m_uiptraChild;
      string                                       m_strName;
      interaction *                                m_puiOwner;
      u64                                          m_uiUserInteractionFlags;
      bool                                         m_bCursorInside;
      e_cursor                                     m_ecursor;
      bool                                         m_bRectOk;
      bool                                         m_bParentScroll;
      bool                                         m_bMessageWindow;
      string                                       m_strWindowText;
      bool                                         m_bModal;
      ::thread *                                   m_pthreadModal;
      __reference(::thread)                        m_pthreadUserInteraction;
      id                                           m_idModalResult; // for return values from interaction_impl::RunModalLoop
      i32                                          m_nModalResult; // for return values from ::interaction_impl::RunModalLoop
      __pointer(interaction)                       m_ptooltip;


      ::draw2d::path_pointer                       m_pathFocusRect1;
      ::draw2d::path_pointer                       m_pathFocusRect2;
      ::draw2d::path_pointer                       m_pathFocusRect3;
      ::draw2d::path_pointer                       m_pathFocusRect4;


      /// The menu_item this user_interaction (window)
      /// represents (this window is a button [a menu button],
      /// this window is a checkbox [a menu checkbox],
      /// this window is a player/view [a menu picture/video/chat?!])
      __pointer(menu_item)                      m_pmenuitemThis;
      __pointer_array(menu)                     m_menuaGuest;
      bool                                      m_bWfiUpDownTarget;
      __pointer_array(::thread)                 m_threada;



      interaction();
      virtual ~interaction();


      void user_interaction_common_construct();

      virtual void on_create_user_interaction();

      ::user::item* get_user_item(const ::user::item& item);

      bool is_ok()
      {

         return ::is_set(this)
            && m_pimpl.is_set()
            && (m_ewindowflag & window_flag_is_window)
            && !m_pimpl->m_bDestroying;

      }

      virtual e_element get_default_element() const;
      virtual ::draw2d::font_pointer get_font(style * pstyle, e_element eelement, estate estate = e_state_none) const;
      inline ::draw2d::font_pointer get_font(style* pstyle, estate estate = e_state_none) const { return get_font(pstyle, get_default_element(), estate); }
      virtual e_translucency get_translucency(style* pstyle) const;
      virtual int get_int(style* pstyle, enum_int eint, int iDefault = 0) const;
      virtual double get_double(style* pstyle, enum_double edouble, double dDefault = 0.) const;
      virtual ::rect get_border(style* pstyle, e_element eelement, estate estate = e_state_none) const;
      inline ::rect get_border(style* pstyle, estate estate = e_state_none) const { return get_border(pstyle, get_default_element(), estate); }
      virtual ::rect get_padding(style* pstyle, e_element eelement, estate estate = e_state_none) const;
      inline ::rect get_padding(style* pstyle, estate estate = e_state_none) const { return get_padding(pstyle, get_default_element(), estate); }
      virtual ::rect get_margin(style* pstyle, e_element eelement, estate estate = e_state_none) const;
      inline ::rect get_margin(style* pstyle, estate estate = e_state_none) const { return get_margin(pstyle, get_default_element(), estate); }
      virtual ::color get_color(style* pstyle, e_element eelement, estate estate = e_state_none) const;
      inline ::color get_color(style* pstyle, estate estate = e_state_none) const { return get_color(pstyle, get_default_element(), estate); }

      virtual eflag get_draw_flags(style* pstyle) const;

      virtual estate get_state() const;


      virtual style* _get_style() const;

      inline style* get_style(::draw2d::graphics_pointer& pgraphics) const
      {

         return pgraphics ? get_style(pgraphics->m_puserstyle) : ((pgraphics = ::draw2d::create_memory_graphics())->m_puserstyle = _get_style()).m_p;

      }

      inline style * get_style(::user::style_pointer & pstyle) const
      {

         return pstyle ? pstyle : pstyle = _get_style();

      }

      virtual void on_tsf_activate(bool bActivate);

      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      virtual bool create_control(class control_descriptor* pdescriptor);


      virtual bool add_control(arguments arguments);


      inline bool is_graphical() const { return !m_bMessageWindow && m_ewindowflag & window_flag_graphical; }


      virtual ::sync * mutex_draw();


      virtual bool AddControlBar(::user::control_bar* pcontrolbar);
      virtual bool RemoveControlBar(::user::control_bar* pcontrolbar);

      // updown
      virtual bool wfi_is_up();
      virtual bool wfi_is_down();
      virtual bool wfi_is_up_down();
      // end updown


      virtual bool child_set_unique_id(::user::interaction* pinteraction);

      virtual string default_id_prefix() const;

      interaction * get_tooltip();

      virtual double get_rotate();
      virtual ::user::form * get_form();
      virtual ::user::form * get_parent_form();


      virtual void set_place_child_title(const char* pszTitle);

      virtual ::user::interaction* get_bind_ui();

      virtual void on_finalize() override;
      virtual void delete_this() override;


      virtual bool window_move(i32 x, i32 y) override;


      auto prodevian() { return __new(::prodevian(this)); }

      virtual bool should_save_window_rect();
      virtual bool WindowDataSaveWindowRect();
      virtual bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false);


      virtual void on_defer_display();

      virtual bool defer_display();
      virtual bool prodevian_display();
      virtual bool prodevian_appearance();
      virtual bool prodevian_zorder();
      virtual bool prodevian_reposition();
      virtual bool prodevian_layout();


      virtual void prodevian_stop() override;

      virtual void prodevian_redraw(bool bUpdateBuffer) override;

      virtual void _001OnAfterAppearance();


      virtual void defer_restore(const ::rect& rectRequest);
      ::object * parent_property_set_holder() const override;

      virtual void set_reposition(bool bSetThis = true) override;
      virtual void _set_reposition(bool bSetThis = true) override;
      virtual void set_need_layout(bool bAscendants = true);
      virtual void set_need_redraw(bool bAscendants = true) override;
      virtual void set_need_load_form_data() override;
      virtual void set_need_save_form_data() override;
      virtual void post_redraw(bool bAscendants = true) override;
      virtual void show_window();

      virtual void prodevian_update_visual(bool & bUpdateBuffer, bool & bUpdateWindow) override;
      virtual void _001UpdateWindow() override;
      virtual void window_apply_visual(const struct window_state& windowstate) override;


      virtual void prodevian_prepare_window_minimize(::eactivation eactivation) override;
      virtual void prodevian_prepare_window_maximize() override;
      virtual void prodevian_prepare_window_full_screen(const ::rect& rectHint = nullptr) override;
      virtual void prodevian_prepare_window_restore(edisplay edisplay) override;
      virtual void prodevian_prepare_window_dock(edisplay edisplay) override;



      inline bool set_prodevian() { return add_prodevian(this); }
      inline bool clear_prodevian() { return remove_prodevian(this); }

      virtual bool add_prodevian(::context_object* pobject) override;
      virtual bool remove_prodevian(::context_object* pobject) override;
      inline bool has_prodevian() const noexcept;


      virtual bool is_frame_window();
      virtual bool is_this_visible() override;


      virtual bool create_message_queue(const char* lpszName) override;

      //virtual bool create_native_window(::user::native_window_initialize* pinitialize) override;

    virtual bool setWMClass(const char * psz);


      virtual bool has_text_input();
      //virtual COLORREF get_action_hover_border_color();

      virtual bool kick_queue();

      virtual bool contains_user_interaction(::user::interaction* pinteraction, bool bRecursive = true) const;


      virtual void on_select() override;

      virtual bool is_place_holder() override;

      virtual e_cursor get_cursor();
      virtual bool set_cursor(e_cursor ecursor);


      virtual bool is_left_button_pressed() const;


      virtual void set_current_item(const ::user::item & item, const ::action_context & action_context);
      virtual ::user::item current_item();


      virtual ::user::item hover_item();


      virtual bool _is_window() const override;
      inline bool is_window() const { return m_ewindowflag & window_flag_is_window; }

      virtual void ExitHelpMode();

      virtual LONG get_window_long(i32 nIndex) const override;
      virtual LONG set_window_long(i32 nIndex, LONG lValue) override;

      virtual LONG_PTR get_window_long_ptr(i32 nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(i32 nIndex, LONG_PTR lValue) override;

      virtual bool on_before_set_parent(::user::interaction* pinterface);
      virtual bool on_set_parent(::user::interaction* pinterface);
      virtual void on_after_set_parent();

      virtual ::user::primitive * first_child_user_primitive() override;
      virtual ::user::primitive * top_user_primitive() override;
      virtual ::user::primitive * under_user_primitive() override;
      virtual ::user::primitive * above_user_primitive() override;
      virtual ::user::primitive * next_user_primitive() override;
      virtual ::user::primitive * previous_user_primitive() override;



      virtual ::user::interaction* first_child() override;
      virtual ::user::interaction* last_child() override;
      virtual ::user::interaction* last_sibling() override;
      virtual ::user::interaction* next_sibling() override;
      virtual ::user::interaction* previous_sibling() override;
      virtual ::user::interaction* first_sibling() override;
      virtual ::user::interaction* next_sibling(::user::interaction* pinteraction) override;
      virtual ::user::interaction* previous_sibling(::user::interaction* pinteraction) override;


      virtual void mouse_hover_add(::user::interaction* pinterface) override;
      virtual bool mouse_hover_remove(::user::interaction* pinterface) override;


      template < typename TYPE >
      TYPE* typed_descedant(::user::interaction* puiExclude = nullptr)
      {

         for (auto& pinteraction : m_uiptraChild.ptra())
         {

            if (pinteraction != puiExclude)
            {

               TYPE* point = dynamic_cast <TYPE*> (pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         for (auto& pinteraction : m_uiptraChild.ptra())
         {

            if (pinteraction != puiExclude)
            {

               TYPE* point = pinteraction->typed_descedant < TYPE >(pinteraction.m_p);

               if (point != nullptr)
               {

                  return point;

               }

            }


         }

         return nullptr;

      }


      template < typename TYPE >
      __pointer(TYPE)& _001TypedWindow(__pointer(TYPE)& sp)
      {

         return sp = _001TypedWindow<TYPE>();

      }


      template < typename TYPE >
      TYPE* _001TypedWindow() // search descedants first, then ascendants descedants.
      {

         ::user::interaction* pinteraction = this;

         ::user::interaction* puiExclude = nullptr;

         while (pinteraction != nullptr)
         {

            TYPE* point = pinteraction->typed_descedant < TYPE >(puiExclude);

            if (point != nullptr)
            {

               return point;

            }

            puiExclude = pinteraction;

            pinteraction = pinteraction->GetParent();

            if (pinteraction == nullptr)
            {

               return nullptr;

            }

            point = dynamic_cast <TYPE*> (pinteraction);

            if (point != nullptr)
            {

               return point;

            }

         }

         return nullptr;

      }


      virtual bool CheckAutoCenter() override;

      virtual void track_mouse_hover() override;
      virtual void track_mouse_leave() override;


      virtual void update_dialog_controls(channel* ptarget) override;
      virtual void CenterWindow(::user::interaction* pAlternateOwner = nullptr) override;
      virtual void _001Emphasize(int cx, int cy);
      virtual id   run_modal_loop(::user::interaction* pinteraction, u32 dwFlags = 0) override;
      virtual id   RunModalLoop(u32 dwFlags = 0) override;
      virtual id   _001RunModalLoop(u32 dwFlags = 0) override;
      virtual bool ContinueModal() override;
      virtual void EndModalLoop(id nResult) override;


      virtual void route_control_event(::user::control_event* pevent) override;

      virtual void on_control_event(::message::base* pbase);

      virtual void on_notify_control_event(control_event* pevent);

      virtual void on_control_event(::user::control_event* pevent) override;


      virtual bool update_data(bool bSaveAndValidate = true) override;


      virtual ::user::interaction* get_os_focus_uie();


      virtual bool on_keyboard_focus(::user::primitive* pfocus) override;

      virtual void get_child_rect(RECT* prect);

      inline auto get_child_rect() { ::rect rect(no_init); get_child_rect(&rect); return rect; }

      virtual bool scroll_bar_get_client_rect(RECT* prect);

      virtual void on_visual_applied();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;
      virtual void on_reposition() override;
      virtual void on_show_window() override;
      virtual void _on_show_window();

      virtual void _do_show_window() override;

      virtual void defer_save_window_placement();

#ifdef WINDOWS_DESKTOP

      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);

#endif


      virtual bool pre_create_window(::user::create_struct& cs) override;


      virtual bool subclass_window(oswindow posdata) override;
      virtual oswindow unsubclass_window() override;


      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      //virtual bool create_control(class ::user::control_descriptor * pdescriptor);

      virtual bool create_window(::user::interaction* pparent, const ::id& id) override;
      virtual bool create_window(const char* pszClassName, const char* pszWindowName, u32 uStyle, ::user::interaction* puiParent, const ::id& id, ::create* pcreate = nullptr) override;

      virtual bool create_window_ex(::user::create_struct& cs, ::user::interaction* puiParent = nullptr, const ::id& id = ::id()) override;
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(RECT* pClientRect, UINT nAdjustType = adjustBorder) override;


      virtual bool IsTopParentActive() override;
      virtual void ActivateTopParent() override;



      virtual bool DestroyWindow() override;

      virtual void destroy_window() override;

      virtual void set_finish() override;

      virtual void on_set_finish();

      virtual void finalize() override;


#ifdef WINDOWS

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
         ::draw2d::region* prgnUpdate = nullptr,
         UINT flags = RDW_INVALIDATE | RDW_ERASE) override;

#else

      virtual bool RedrawWindow(const ::rect& rectUpdate = nullptr,
         ::draw2d::region* prgnUpdate = nullptr,
         UINT flags = 0) override;

#endif


      virtual void register_drop_target();




      virtual void UpdateWindow() override;
      virtual void SetRedraw(bool bRedraw = TRUE) override;
      virtual bool GetUpdateRect(RECT* prect, bool bErase = FALSE) override;

      virtual i32 GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE) override;
      virtual void Invalidate(bool bErase = TRUE) override;
      virtual void InvalidateRect(const ::rect& rect, bool bErase = TRUE) override;

      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE) override;
      virtual void ValidateRect(const ::rect& rect) override;

      virtual void ValidateRgn(::draw2d::region* pRgn) override;
      virtual void ShowOwnedPopups(bool bShow = TRUE) override;


      virtual u32 GetStyle() const override;
      virtual u32 GetExStyle() const override;
      virtual bool ModifyStyle(u32 dwRemove, u32 dwAdd, UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(u32 dwRemove, u32 dwAdd, UINT nFlags = 0) override;


      virtual LRESULT send(::message::base* pbase) override;
      virtual bool post(::message::base* pbase) override;
      virtual LRESULT send_message(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0) override;

      virtual LRESULT message_call(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0) override;
      virtual LRESULT message_call(message::base* base) override;


#ifdef LINUX

      virtual LRESULT send_x11_event(void* pevent) override; // XEvent *

#endif

      virtual bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0) override;

      virtual bool post_object(UINT message, WPARAM wParam, lparam lParam);


      virtual void SetWindowDisplayChanged() override;


      virtual bool call_and_set_timer(uptr nIDEvent, ::duration durationElapse, PFN_TIMER pfnTimer = nullptr);
      virtual bool set_timer(uptr nIDEvent, ::duration durationElapse, PFN_TIMER pfnTimer = nullptr);
      virtual bool SetTimer(uptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer = nullptr) override;
      virtual bool KillTimer(uptr nIDEvent) override;

      virtual bool is_this_enabled() const override;
      virtual bool enable_window(bool bEnable = TRUE) override;

      virtual void _001PrintBuffer(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001Print(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool _000OnBeforeDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000CallOnDraw1(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _000OnDraw1(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _008CallOnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _008OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics);
      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool is_custom_draw();

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;


      virtual bool SetCapture(::user::interaction* pinteraction = nullptr) override;
      virtual bool ReleaseCapture() override;
      virtual ::user::interaction* GetCapture() override;


      virtual bool has_focus() override;
      virtual bool SetFocus() override;
      virtual ::user::interaction* GetFocus() override;
      virtual bool SetForegroundWindow() override;
      virtual bool is_active() override;
      virtual interaction* GetActiveWindow() override;
      virtual interaction* SetActiveWindow() override;


      virtual void on_calc_size(calc_size* pcalcsize);

      virtual void walk_pre_translate_tree(::message::message* pmessage, ::user::interaction* puiStop = nullptr);


      virtual bool edit_undo();

      virtual void edit_on_text(string str) override;
      virtual void edit_on_sel(strsize iBeg, strsize iEnd) override;

      virtual void get_text_composition_area(::rect & r);
      virtual void on_text_composition(string str) override;
      virtual void on_text_composition_done() override;

      virtual bool is_text_composition_active() override;

      virtual int on_text_composition_message(int iMessage);

      virtual void insert_text(string str, bool bForceNewStep);

      virtual void set_window_text(const char* pszString) override;

#ifdef WINDOWS
      strsize _009GetWindowText(wchar_t * pwsz, int n) override;
#else
      strsize _009GetWindowText(char * psz, int n) override;
#endif
      virtual strsize _009GetWindowTextLength() override;

      virtual strsize get_window_text(char* pszStringBuf, strsize nMaxCount) override;

      virtual string get_window_text() override;
      virtual void get_window_text(string& rectString) override;
      virtual strsize get_window_text_length() override;


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void _000OnMouseLeave(::message::message* pmessage) override;

      virtual void _000OnMouse(::message::mouse* pmouse);
      virtual void _000OnThisMouse(::message::mouse* pmouse);
      virtual void _000OnChildrenMouse(::message::mouse* pmouse);
      virtual void _000OnKey(::message::key* pkey);
      virtual void _000OnDrag(::message::drag_and_drop* pdrag);


      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseEnter);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);


      virtual void _001OnTimer(::timer* ptimer) override;
      virtual bool on_timer(::timer* ptimer) override;
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnCommand);
      DECL_GEN_SIGNAL(_001OnSimpleCommand);
      DECL_GEN_SIGNAL(_001OnNeedLoadFormData);
      DECL_GEN_SIGNAL(_001OnNeedSaveFormData);
      DECL_GEN_SIGNAL(_001OnDisplayChange);


      virtual DECL_GEN_SIGNAL(_002OnLButtonDown);
      virtual DECL_GEN_SIGNAL(_002OnLButtonUp);
      virtual DECL_GEN_SIGNAL(_002OnMouseMove);
      virtual DECL_GEN_SIGNAL(_002OnMouseEnter);
      virtual DECL_GEN_SIGNAL(_002OnMouseLeave);
      virtual DECL_GEN_SIGNAL(_002OnKeyDown);
      virtual DECL_GEN_SIGNAL(_002OnKeyUp);
      virtual DECL_GEN_SIGNAL(_002OnTimer);

      DECL_GEN_SIGNAL(_001OnTextComposition);


      virtual bool _001IsPointInside(::point point) override;
      virtual ::user::interaction* _001FromPoint(::point point, bool bTestedIfParentVisible = false) override;

      virtual void OnLinkClick(const char* psz, const char* pszTarget = nullptr) override;

      virtual void pre_translate_message(::message::message* pmessage) override;


      ::user::interaction* get_child_by_name(const char* lpszName, i32 iLevel = -1);
      ::user::interaction* get_child_by_id(id id, i32 iLevel = -1);


      virtual bool is_ascendant(const primitive * puiIsAscendant) const override;
      virtual bool is_parent(const primitive * puiIsParent) const override;
      virtual bool is_child(const primitive * puiIsChild) const override;
      virtual bool is_descendant(const primitive * puiIsDescendant) const override;

      virtual ::user::interaction* get_wnd() const override;
      virtual ::user::interaction* get_wnd(UINT nCmd) const override;

      virtual ::user::interaction* SetParent(::user::interaction* pinteraction) override;
      virtual ::user::interaction* SetOwner(::user::interaction* pinteraction) override;

      virtual ::user::interaction* get_parent() const override;

      virtual bool is_host_top_level() const;

      virtual ::user::interaction* GetTopWindow() const override;
      virtual ::user::interaction* GetParent() const override;
      virtual ::user::interaction* GetTopLevel() const override;
      virtual ::user::interaction* GetParentTopLevel() const override;
      virtual ::user::interaction* EnsureTopLevel() override;
      virtual ::user::interaction* EnsureParentTopLevel() override;
      virtual ::user::interaction* GetOwner() const override;
      virtual ::user::interaction* GetParentOwner() const override;
      virtual ::user::interaction* GetParentOrOwner() const override;
      virtual ::user::interaction* GetTopLevelOwner() const override;
      virtual ::user::frame* GetFrame() const override;
      virtual ::user::frame* GetParentFrame() const override;
      virtual ::user::frame* GetTopLevelFrame() const override;
      virtual ::user::frame* GetParentTopLevelFrame() const override;
      virtual ::user::frame* EnsureParentFrame() override;
      virtual ::user::frame* GetOwnerFrame() const override;

      virtual void send_message_to_descendants(UINT message, WPARAM wParam = 0, lparam lParam = 0, bool bDeep = TRUE, bool bOnlyPerm = FALSE) override;

      virtual void route_message_to_descendants(::message::message* pmessage) override;


      virtual i32 get_descendant_level(::user::interaction* pinteraction) override;
      virtual bool is_descendant(::user::interaction* pinteraction, bool bIncludeSelf = false) override;

      virtual oswindow GetParentHandle() const;

      virtual ::user::interaction* get_focusable_descendant(::user::interaction* pinteraction = nullptr) override;

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, ::id idLeftOver, UINT nFlag = reposDefault, RECT* prectParam = nullptr, const ::rect& rectClient = nullptr, bool bStretch = true) override;

      virtual ::user::interaction* ChildWindowFromPoint(const ::point& point) override;
      virtual ::user::interaction* ChildWindowFromPoint(const ::point& point, UINT nFlags) override;

#ifdef WINDOWS_DESKTOP
      virtual ::user::interaction* get_next_window(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction* get_next_window(UINT nFlag = 0) override;
#endif

      virtual ::user::interaction* GetTopWindow();

      virtual ::user::interaction* get_next(bool bIgnoreChildren = false, i32* piLevel = nullptr) override;

      virtual ::user::interaction* GetLastActivePopup() override;

      virtual bool is_message_only_window() const override;

      virtual void pre_subclass_window() override;

      virtual void PostNcDestroy() override;


      virtual void default_message_handler(::message::message * pmessage) override;


      virtual void message_handler(::message::base* pbase) override;
      virtual LRESULT message_handler(LPMESSAGE pmessage) override;

      virtual void GuieProc(::message::message* pmessage) override;

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics) override;


      virtual oswindow get_handle() const override;
      virtual bool attach(oswindow oswindow_New) override;
      virtual oswindow detach() override;

      virtual void* get_os_data() const;


      virtual bool can_merge(::user::interaction* pinteraction) override;
      virtual bool merge(::user::interaction* pinteraction) override;


      virtual void _001OnTriggerMouseInside() override;


      virtual bool window_is_notify_icon_enabled();
      virtual void set_viewport_org(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool set_icon(::draw2d::icon * picon, bool bSmall) override;

      virtual void viewport_screen_to_client(POINT* ppt) override;
      virtual void viewport_client_to_screen(POINT* ppt) override;
      virtual void viewport_client_to_screen(RECT* ppt) override;
      virtual void viewport_screen_to_client(RECT* ppt) override;


      virtual string get_window_default_matter() override;
      virtual string get_window_icon_matter() override;
      virtual u32 get_window_default_style() override;
      virtual e_type get_window_type() override;


      virtual void on_simple_command(::message::simple_command* psimplecommand) override;
      virtual void on_command(::user::command* pcommand) override;


      virtual bool OnCommand(::message::base* pbase) override;
      virtual bool OnNotify(::message::base* pbase) override;
      virtual bool OnChildNotify(::message::base* pbase) override;


      virtual bool is_selected(::data::item* pitem) override;

      virtual __pointer(place_holder) place_hold(::user::interaction* pinteraction) override;

#if defined(_UWP) && defined(__cplusplus_winrt)
      static Agile<Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction* pinteraction);
      Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window(interaction* pinteraction)
      {
         return (*s_get_os_window)(pinteraction);
      }
      static Agile<Windows::UI::Core::CoreWindow> get_os_window_default(interaction* pinteraction)
      {
         UNREFERENCED_PARAMETER(pinteraction);
         return nullptr;
      }
#endif
      virtual bool has_command_handler(::user::command* pcommand) override;



      virtual bool track_popup_menu(::user::menu_item* pitem, i32 iFlags, const ::point& point) override;
      virtual __pointer(::user::menu) track_popup_xml_menu(const var & varXml, i32 iFlags, const ::point& pointScreen = nullptr, const ::size& sizeMinimum = nullptr) override;


      virtual void _001OnExitIconic() override;
      virtual void _001OnExitFullScreen() override;


      virtual bool _001OnBeforeAppearance();
      virtual bool _001OnExitAppearance();


      virtual void on_start_layout_experience(e_layout_experience elayoutexperience) override;
      virtual void on_end_layout_experience(e_layout_experience elayoutexperience) override;


      virtual void show_keyboard(bool bShow = true) override;


      virtual void keep_alive(::object* pliveobject = nullptr) override;

      virtual ::user::interaction* best_top_level_parent(RECT* prect);

      virtual void get_window_rect(RECT * prect) const override;

      virtual index get_zoneing(::rect* prect, const ::rect& rect, edisplay edisplay);

      virtual edisplay initial_restore_display();

      virtual index calculate_broad_and_compact_restore(RECT* prectWkspace = nullptr, SIZE* psizeMin = nullptr, const ::rect& rectHint = nullptr);

      virtual void reset_window_state();

      virtual index make_zoneing(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::edisplay* pedisplay = nullptr, ::eactivation eactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_zoneing(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::edisplay* pedisplay = nullptr, ::eactivation eactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_monitor(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index best_wkspace(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index good_restore(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top, edisplay edisplay = display_restore);
      virtual index good_iconify(RECT* prect, const ::rect& rect = nullptr, bool bSet = false, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);

      virtual index good_move(RECT* prect, const ::rect& rect = nullptr, ::eactivation eeactivation = activation_none, ::zorder zorder = zorder_top);
      virtual index get_best_zoneing(edisplay& edisplay, ::rect* prect, const ::rect& rectRequest = ::rect(), bool bPreserveSize = false);
      virtual index get_best_wkspace(::rect* prect, const ::rect& rect, ::eactivation eactivation = activation_none);

      virtual bool get_rect_normal(RECT* prect);



      virtual void set_viewport_offset_x(int x);
      virtual void set_viewport_offset_y(int y);
      virtual void set_viewport_offset(int x, int y);
      virtual void offset_viewport_offset_x(int x);
      virtual void offset_viewport_offset_y(int y);
      virtual void offset_viewport_offset(int x, int y);
      virtual bool validate_viewport_offset(point& point);
      virtual void on_change_viewport_offset();
      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics);
      virtual ::point get_viewport_offset();
      virtual ::size get_total_size();
      virtual void on_change_view_size();
      virtual ::size get_page_size();
      virtual ::point get_parent_accumulated_scroll() const override;
      virtual ::point get_parent_viewport_offset() const;
      virtual ::point get_ascendant_viewport_offset() const;
      virtual void get_margin_rect(RECT* prectMargin);

      virtual int get_final_x_scroll_bar_width();
      virtual int get_final_y_scroll_bar_width();


      virtual bool is_system_message_window();


      virtual ::graphics::graphics * get_window_graphics() override;

      virtual bool is_composite() override;

      virtual ::size get_window_minimum_size();


      virtual void UpDownTargetAttach(::user::interaction* pupdown);
      virtual void UpDownTargetDetach(::user::interaction* pupdown);

      virtual bool OnUpDownTargetAttach(::user::interaction* pupdown);
      virtual bool OnUpDownTargetDetach(::user::interaction* pupdown);


      virtual string calc_window_class();


      virtual void user_interaction_on_destroy();
      virtual void user_interaction_on_hide();





      virtual void on_remove_child(::user::interaction* pinteraction);
      virtual void on_remove_place_holder_child(::user::interaction* pinteraction);
      virtual void on_hide_child(::user::interaction* pinteraction);
      virtual void on_hide_place_holder_child(::user::interaction* pinteraction);


      virtual void _001GetSel(strsize& iBeg, strsize& iEnd) const override;


      virtual void _001GetXScrollInfo(scroll_info& info);
      virtual void _001GetYScrollInfo(scroll_info& info);
      virtual void layout_scroll_bar();


      using primitive::update;
      virtual void update(::update * pupdate) override;


      virtual void keyboard_focus_OnKeyDown(::message::message* pmessage) override;
      virtual bool keyboard_focus_OnKillFocus(oswindow oswindowNew) override;
      virtual bool keyboard_focus_OnChildKillFocus() override;

      virtual bool get_child(__pointer(::user::interaction)& pinteraction);
      virtual bool rget_child(__pointer(::user::interaction)& pinteraction);


      template < typename CHILD >
      inline bool get_typed_child(CHILD*& pchild);

      template < typename CHILD >
      inline __pointer(CHILD) get_typed_child();


      virtual ::user::primitive* get_focus_primitive();
      virtual bool set_focus_primitive(::user::primitive* pprimitive);


      virtual bool is_descendant_of(::user::interaction* puiAscendantCandidate, bool bIncludeSelf);
      virtual bool is_ascendant_of(::user::interaction* puiDescendantCandidate, bool bIncludeSelf);

      virtual bool is_descendant_of_or_owned_by(::user::interaction* puiAscendantCandidate, bool bIncludeSelf);
      virtual bool is_ascendant_or_owner_of(::user::interaction* puiDescendantCandidate, bool bIncludeSelf);

      virtual bool show_tooltip(const string& str, bool bError);

      virtual bool layout_tooltip(bool bForceShow = false);

      virtual bool hide_tooltip();

      virtual bool frame_is_transparent();

      virtual double get_alpha();



      virtual void destruct() override;



      virtual void defer_notify_mouse_move();

      virtual void defer_notify_mouse_move(bool& bPointInside, point& pointLast);

      virtual bool has_pending_graphical_update() override;

      virtual bool enable_transparent_mouse_events(bool bEnable = true);

      virtual void check_transparent_mouse_events();


      virtual void redraw_add(::context_object * pobject);

      virtual void redraw_remove(::context_object * pobject);

      virtual bool has_redraw();

      virtual void on_after_graphical_update() override;


      virtual void _001OnDeiconify(edisplay edisplay);


      virtual bool on_click(const ::user::item & item);
      virtual bool on_right_click(const ::user::item & item);


      virtual int width();
      virtual int height();

      virtual int client_width();
      virtual int client_height();

      virtual ::sized get_size();
      virtual ::sized get_client_size();

      virtual void resize_to_fit(::draw2d::graphics_pointer& pgraphics);

      virtual void wait_redraw();

      virtual bool has_pending_redraw_flags() override;


      virtual void set_bitmap_source(string strBitmapFileTitle) override;
      virtual void clear_bitmap_source() override;


      void install_simple_ui_default_mouse_handling(::channel* pchannel);
      void install_update_data_message_routing(::channel * pchannel);


      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnMButtonUp);


      virtual void edit_on_set_focus(::user::interaction* pinteraction) override;
      virtual void edit_on_kill_focus(::user::interaction* pinteraction) override;


      virtual void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);


      virtual void simple_ui_draw_auth_box(::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_frame_window_rect(::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_dark_glass(::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_pestana(::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(::draw2d::graphics_pointer & pgraphics);

      virtual void simple_ui_draw_back_01_old(rect m_rect, ::draw2d::graphics_pointer & pgraphics);
      virtual void simple_ui_draw_back_01_new(rect m_rect, ::draw2d::graphics_pointer & pgraphics);

      virtual bool on_action(const char* pszId);

      virtual bool keyboard_focus_is_focusable() override;

      virtual bool simple_on_control_event(::message::message* pmessage, ::user::e_event eevent);

      using ::aura::drawable::hit_test;
      virtual void hit_test(::user::item& item, const ::point & point) override;

      using ::aura::drawable::on_hit_test;
      virtual void on_hit_test(::user::item & item) override;

      virtual void update_hover(::message::mouse* pmouse = nullptr, bool bAvoidRedraw = true);

      virtual bool get_rect(::user::item& item);

      inline auto rect(const ::user::item& item) { get_rect((::user::item &) item); return item.m_rect; }

      virtual __pointer(::user::item) add_user_item(const ::user::item & item);

      virtual void _001DrawItems(::draw2d::graphics_pointer & pgraphics);


      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::user::item * pitem);

      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      // virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency);


      //using style::select_text_color;
      //virtual bool select_text_color(::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
      //using style::select_solid_brush;
      //virtual bool select_solid_brush(::draw2d::graphics_pointer & pgraphics, e_color ecolor);
      //using style::set;
      //virtual bool set(::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);


      //virtual bool select_text_color(e_color ecolor = color_text);
      //virtual bool select_solid_brush(e_color ecolor);
      //virtual bool set(e_font efont = font_default);


      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd) override;


      virtual void set_stock_icon(e_stock_icon eicon);
      virtual e_stock_icon get_stock_icon();


      virtual e_control_type get_control_type() const;


      virtual void post_task(::generic_object * pobjectTask);
      virtual void prodevian_schedule(::generic_object * pobjectTask);


      virtual void send_task(::generic_object * pobjectTask, ::duration durationTimeout = ::duration::infinite());


      template < typename PRED >
      void post_pred(PRED pred)
      {

         post_task(__task_procedure(pred, this));

      }


      template < typename PRED >
      void prodevian_pred(PRED pred)
      {

         prodevian_schedule(__task_procedure(pred, this));

      }


      template < typename PRED >
      void pred(PRED pred)
      {

         post_pred(pred);

      }


      template < typename PRED >
      void send_pred(PRED pred, ::duration durationTimeout = ::duration::infinite())
      {

         send_task(__task_procedure(pred, this), durationTimeout);

      }

      bool _001InitialFramePosition();

      bool _001InitialFramePosition(LPRECT lprect, const rectd & rectOptionalRateOrSize = {0., 0., 0., 0.});

      virtual double _001GetTopLeftWeightedOccludedOpaqueRate() override;



   };


   inline bool layout::is_window_visible() const noexcept
   {

      if (m_pdescriptor.is_null())
      {

         return false;

      }

      return m_pdescriptor->m_puserinteractionParent != NULL && !m_pdescriptor->m_puserinteractionParent->is_window_visible() ? false : is_this_visible();

   }


   inline bool layout::is_window_screen_visible() const noexcept
   {

      return m_pdescriptor->m_puserinteractionParent != NULL && !m_pdescriptor->m_puserinteractionParent->is_window_screen_visible() ? false : is_this_screen_visible();

   }


} // namespace user


// timer_ui works correctly when timer is originated from SetTimer call
//inline ::user::interaction * timer_ui(::timer * ptimer)
//{
//
//   return (::user::interaction *) ptimer->m_pvoidData;
//
//}



CLASS_DECL_AURA::user::interaction* oswindow_interaction(oswindow oswindow);


