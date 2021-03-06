#pragma once


namespace core
{


   class CLASS_DECL_CORE user :
      virtual public ::base::user,
      virtual public ::filemanager::component
   {
   public:



      ::user::impact_system *                      m_ptemplateForm;
      ::user::impact_system *                      m_ptemplateChildForm;
      ::user::impact_system *                      m_ptemplatePlaceHolder;


      ::user::impact_system *                      m_ptemplateHtmlChildForm1;


      ::user::multiple_document_template *         m_ptemplateProgress2;


      __composite(::user::shell)                   m_pshell;





      keymap < ::type, ::user::impact_system * >   m_mapTemplate;

      id_map < ::user::impact_system * >           m_mapimpactsystem;


      //__composite(::userex::userex)              m_puserex;
      bool                                         m_bFontSelInitialized;


      


      string_array                                 m_straEscape;

      ::type                                       m_typeDefaultMeshData;
      ::type                                       m_typeDefaultListHeader;
      ::type                                       m_typeDefaultListData;

      __composite(::userfs::userfs)                m_puserfs;

      ::status::result                             m_result;

      //__composite(::user::keyboard)              m_pkeyboard;

      //index                                      m_iEdge;
      //::map < ::user::e_key, ::user::e_key, bool, bool > *  m_pmapKeyPressed;

      //bool                                       m_bProgrammerMode;

      //bool                                       m_bSystemSynchronizedCursor;
      //point                                      m_pointCursor;

      //__pointer_array(::user::interaction)         m_uiptraToolWindow;

      //::user::interaction_impl *                            m_pimplPendingFocus2;
      //::user::interaction *                                 m_puiLastUserInputPopup;
      //::draw2d::cursor *                                    m_pcursor;
      //::draw2d::cursor *                                    m_pcursorCursor;
      //e_cursor                                              m_ecursorDefault;
      //e_cursor                                              m_ecursor;

      //__composite(::user::theme)                            m_ptheme;
      //string_map < __composite(::user::theme) >             m_mapTheme;

      //::user::interaction *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;


      //__composite(::user::copydesk)                         m_pcopydesk;

      //::user::interaction *                                 m_puiMouseMoveCapture;
      //::user::interaction *                                 m_puiLastLButtonDown;


      //::draw2d::font_enum_item_array                        m_fontenumitema;

      ////index                                               m_iEdge;

      //__composite(::account::department)                    m_paccount;
      ////__pointer(::account::licensing)                     m_plicensing;
      ////__composite(::user::interaction)                      m_puserinteractionSystem;

      //payload                                                   m_varTopicFile;
      //payload                                                   m_varCurrentViewFile;
      //bool                                                  m_bShowPlatform;

      //__composite(::apex::str_context)                      m_puserstrcontext;


      //bool                                                  m_bSystemSynchronizedScreen;
      //rect_array                                            m_rectaMonitor;
      //rect_array                                            m_rectaWkspace;
      //index                                                 m_iMainMonitor;
      //index                                                 m_iMainWkspace;



      //id_map < ::user::interaction * >                      m_mapboundui;



      //__composite(::userpresence::department)               m_puserpresence;


      ////__composite(::ftpfs)                                  m_pftpfs;
      ////__composite(::fs::remote_native)                      m_premotefs;
      ////__composite(::fs::fs)                                 m_pfs;
      ////__composite(::fs::data)                               m_pfsdata;
      ////__composite(::ifs)                                    m_pifs;
      //////ke
      ////bool                                                  m_bIfs;

      //bool                                                  m_bMatterFromHttpCache;

      //::u32                                                 m_dwLongPhRESSingTime;


      //__composite(::userex::userex)                         m_puserex;
      //bool                                                  m_bFontSelInitialized;
      //__composite(::draw2d::font_list)                      m_pfontlistSingleColumn;
      //__composite(::user::user)                             m_puser;
      


      user();
      virtual ~user();


      virtual void finalize() override;


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style* pstyle, ::user::menu_item* pitem) override;


      // ::user::shell* shell();
      
      
      virtual ::estatus init1() override;
      virtual ::estatus init2() override;
      virtual ::estatus init() override;

      virtual ::user::shell* shell();

      virtual ::estatus dialog_box(::layered * pobjectContext, const char * pszMatter, property_set & propertyset, const ::promise::process & process = ::promise::process());


      virtual ::estatus ui_message_box(::layered * pobjectContext, ::user::primitive * puiOwner, const char * pszMessage, const char * pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, const ::promise::process & process = ::promise::process());
      virtual ::estatus ui_message_box_timeout(::layered * pobjectContext, ::user::primitive * puiOwner, const char* pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), ::emessagebox emessagebox = e_message_box_ok, const ::promise::process & process = ::promise::process());
      //virtual ::estatus ui_message_box_timeout(::object* pobjectContext, ::user::primitive* puiOwner, payload payload, ::duration durationTimeout, ::u32 fuStyle = e_message_box_ok, ::aura::application* papp = nullptr, const function_arg& functionargResult = function_arg());

      virtual void on_file_manager_open(::filemanager::data* pdata, ::file::item_array& itema);

      virtual i32 track_popup_menu(const char * pszMatter, const ::point & point, __pointer(::user::interaction) puie);


      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(i64 & i64Size, const char * pszPath, bool & bPending);

      virtual void data_on_after_change(::message::message * pmessage);

      class keyboard & keyboard();

      virtual bool modal_get_color(::user::interaction * puiOwner, ::hls & hls);

      virtual void AddToRecentFileList(const char * pszPathName);

      virtual ::estatus initialize_html();


      virtual void route_command_message(::user::command * pcommand);


      virtual void _001OnFileNew();


      __pointer(::user::list_header) default_create_list_header(::layered * pobjectContext);
      __pointer(::user::mesh_data) default_create_mesh_data(::layered * pobjectContext);
      __pointer(::user::list_data) default_create_list_data(::layered * pobjectContext);


      ::type default_type_mesh_data();
      ::type default_type_list_header();
      ::type default_type_list_data();


      virtual void will_use_view_hint(::id idView);


      virtual void term_instance() override;

      void LoadStdProfileSettings(::u32 nMaxMRU = 10);

      ::count get_template_count() const;
      __pointer(::user::impact_system) get_template(index index) const;


      __pointer(::form_document)   create_form(::object * pobject, ::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);
      __pointer(::form_document)   create_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);
      __pointer(::form_document)   create_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);
      __pointer(::form_document)   create_child_form(::object * pobject, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);
      __pointer(::form_document)   create_child_form(::object * pobject, ::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);
      __pointer(::form_document)   create_child_form(::object * pobject, __pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::type_empty_argument);

      template < typename FORM >
      __pointer(::form_document)   create_child_form(::object * pobject, ::user::impact_data * pimpactdata, payload payload = ::payload(::type_empty_argument))
      {

         return create_child_form(pobject, __type(FORM), pimpactdata->m_pplaceholder, payload);

      }

      ::user::document * hold(__pointer(::user::interaction) pinteraction);


      virtual ::estatus create_user_shell();


      virtual string get_wallpaper(index iScreen);
      virtual bool set_wallpaper(index iScreen, string strWallpaper);


      virtual string_array get_wallpaper();
      virtual void set_wallpaper(const string_array & strWallpaper);


      virtual string impl_get_wallpaper(index iScreen);
      virtual bool impl_set_wallpaper(index iScreen, string strWallpaper);


      virtual string os_get_user_theme();
      virtual bool set_os_desktop_theme(string strTheme);


      virtual string impl_get_os_desktop_theme();
      virtual bool impl_set_os_desktop_theme(string strTheme);


      virtual void enable_wallpaper_change_notification();





      virtual ::estatus     initialize(::layered * pobjectContext) override;


      virtual bool do_prompt_file_name(payload& varFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument);


      virtual ::estatus initialize_userex();

      virtual ::estatus userfs_init1();
      virtual ::estatus userfs_process_init();


      //virtual ::estatus create_html();

      //virtual __pointer(::userex::userex) create_userex();
      //virtual __pointer(::userfs::userfs) create_userfs();


      virtual ::type get_pane_tab_view_type_info();
      //virtual ::type get_simple_frame_window_type_info() override;
      virtual ::type get_simple_child_frame_type_info();


      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha) override;




      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      //virtual bool is_session() const override;

      ////void construct(::object * pobject, int iPhase) override;

      //virtual ::estatus process_init();

      //virtual ::estatus init1();

      //virtual ::estatus init2();

      //virtual ::estatus init_session();

      //virtual ::estatus init();

      //virtual void term();

      //virtual void term_session();


      //inline class ::fs::data * fs() { return m_pfsdata; }


      ////inline ::sockets::sockets & sockets() { return *m_psockets; }


      //virtual size get_window_minimum_size();


      ////virtual void  get_cursor_pos(POINT32 * ppoint);

      //virtual bool on_get_thread_name(string& strThreadName) override;


      //virtual void on_request(::create * pcreate) override;


      ////virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      ////virtual string dir().matter(const char * pszMatter,const char * pszMatter2);

      ////virtual bool is_inside_time_dir(const char * pszPath);
      ////virtual bool file_is_read_only(const char * pszPath);

      //// Long PhRESSing time
      //// time in milliseconds that a pressing is considered a double click
      //virtual ::u32 get_Long_PhRESSing_time();

      //virtual void defer_initialize_user_presence();

      ////virtual ::estatus     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual bool on_create_frame_window();

      ////virtual string account_get_user_sessid(const string & str) override;

      //virtual void translate_os_key_message(::user::key * pkey);

      //virtual void on_user_logon(::account::user * puser);

      //virtual void pre_translate_message(::message::message * pmessage) override;

      ////session();
      ////virtual ~session();


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;
      //virtual string get_locale_schema_dir() override;


      ////virtual ::estatus     initialize(::layered * pobjectContext) override;


      //virtual ::user::interaction * get_session_window();


      //::apex::str_context *                        str_context() { return m_puserstrcontext; }

      ////virtual bool is_session() const override;

      //virtual ::estatus init_thread() override;

      ////virtual ::estatus process_init();

      ////virtual ::estatus init1();

      ////virtual ::estatus init2();

      ////virtual ::estatus init_session();

      ////virtual ::estatus init();

      ////virtual void term();
      //virtual void term2();

      //virtual void term1();

      //virtual void term_thread() override;

      ////virtual void term_session();

      //virtual void process_term();

      //::user::keyboard& keyboard();

      //virtual bool open_by_file_extension(const char * pszPathName, ::create * pcreate = nullptr);

      //virtual bool open_by_file_extension(::create * pcc);

      ////__pointer(::aura::application) get_new_application(::layered * pobjectContext, const char * pszAppId);

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;

      //virtual color32_t get_default_color(u64 u);

      ////virtual ::size get_window_minimum_size();

      //virtual void frame_pre_translate_message(::message::message * pmessage);

      //virtual bool defer_create_session_frame_window();

      //inline ::account::department * account() { return m_paccount; }

      //::user::copydesk & copydesk();

      //virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      //virtual void on_remove_user(::account::user * puser);

      ////virtual void defer_initialize_user_presence();

      //virtual bool is_licensed(const char * pszId, bool bInteractive = true);

      //virtual void userstyle(::user::style_context * pcontext);

      //virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      //virtual void interactive_credentials(::account::credentials * pcredentials);

      ////virtual void on_request(::create * pcreate) override;

      //::aura::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      //virtual bool is_key_pressed(::user::e_key ekey);

      //virtual void set_key_pressed(::user::e_key ekey, bool bPressed);

      //virtual ::user::primitive * get_keyboard_focus();
      //virtual bool set_keyboard_focus(::user::primitive * pkeyboardfocus);
      //
      //virtual ::user::primitive * clear_focus();


      //virtual ::user::primitive * get_active_ui() override;
      //virtual ::user::primitive * get_focus_ui();

      //virtual void on_finally_focus_set(::user::primitive * pelementalFocus);

      //virtual oswindow get_capture();

      //virtual bool set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor);
      //virtual bool set_cursor(::user::interaction * pinteraction, e_cursor ecursor);
      //virtual bool set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor);
      //virtual ::draw2d::cursor * get_cursor();
      //virtual ::draw2d::cursor * get_default_cursor();

      //virtual bool on_ui_mouse_message(::message::mouse * pmouse);

      //virtual ::user::primitive * GetActiveWindow();
      //virtual ::user::primitive * GetFocus();

      //virtual bool ReleaseCapture();
      //virtual __pointer(::user::interaction) GetCapture();

      ////virtual void translate_os_key_message(::user::key * pkey);
      ////virtual bool on_create_frame_window();

      //virtual void get_cursor_pos(POINT32 * ppoint);
      //inline ::point get_cursor_pos() {::point point; get_cursor_pos(&point); return point;}

      //virtual void set_cursor_pos(const ::point & point);

      //virtual index get_main_monitor(RECT32 * prect = nullptr);

      //virtual bool set_main_monitor(index iMonitor);
      //virtual ::count get_monitor_count();
      //virtual bool  get_monitor_rect(index iMonitor, RECT32 * prect);

      //virtual index get_main_wkspace(RECT32 * prect = nullptr);

      //virtual bool set_main_wkspace(index iWkspace);
      //virtual ::count get_wkspace_count();
      //virtual bool  get_wkspace_rect(index iWkspace, RECT32 * prect);

      //virtual bool wkspace_to_monitor(RECT32 * prect, index iMonitor, index iWkspace);

      //virtual bool monitor_to_wkspace(RECT32 * prect, index iWkspace, index iMonitor);

      //virtual bool wkspace_to_monitor(RECT32 * prect);

      //virtual bool monitor_to_wkspace(RECT32 * prect);

      //virtual ::count get_desk_monitor_count();
      //virtual bool  get_desk_monitor_rect(index iMonitor, RECT32 * prect);

      //virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const ::rect & rect);

      //virtual index initial_frame_position(RECT32 * prect, const ::rect & rect, bool bMove, ::user::interaction * pinteraction);

      //virtual index _get_best_zoneing(edisplay * pedisplay, ::rect * prect, const ::rect & rect, bool bPreserveSize = false);

      //virtual index get_best_monitor(RECT32 * prect, const ::rect & rect, ::eactivation eactivation = e_activation_default);

      //virtual index get_best_wkspace(::rect * prect, const ::rect& rect, ::eactivation eactivation = e_activation_default);

      //virtual index get_good_iconify(RECT32 * prect, const ::rect & rect);

      //virtual index get_window_restore_1(RECT32 * prect, const ::rect & rect, ::user::interaction * pinteraction, edisplay edisplayRestore);

      //virtual index get_window_restore_2(RECT32* prect, const ::rect& rect, ::user::interaction* pinteraction, edisplay edisplayRestore);

      //virtual index get_good_move(RECT32 * prect, const ::rect & rect, ::user::interaction * pinteraction);

      //virtual index get_ui_wkspace(::user::interaction * pinteraction);




      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText);


      //virtual void set_bound_ui(::id idView, ::user::interaction * pinteraction);
      //virtual ::user::interaction * get_bound_ui(::id idView);

      //virtual void on_show_user_input_popup(::user::interaction * pinteraction);

      ////virtual void on_user_logon(::account::user * puser);



      ////virtual ::estatus initialize(::layered * pobjectContext) override;

      //virtual void install_message_routing(::channel* pchannel) override;

      ////virtual ::estatus userex_process_init();
      ////virtual ::estatus userex_init1();
      ////virtual ::estatus init2() override;
      ////virtual bool init3() override;
      ////virtual bool initialize_filemanager();
      /////virtual ::estatus init_session() override;
      ////virtual void add_document_template(::user::impact_system * ptemplate);

      ////virtual void term_session() override;
      ////virtual void term3() override;
      ////virtual bool finalize_filemanager();

      //template < typename VIEW >
      //__pointer(::user::document)   create_form(__pointer(::user::interaction) pwndParent = nullptr, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_form(::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_child_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      //template < typename VIEW >
      //__pointer(::user::document)   create_child_form(__pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_child_form(::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));
      //__pointer(::user::document)   create_child_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));


      ////virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, ::user::menu_item* pitem) override;




      //bool InitializeLocalDataCentral();

      ////virtual ::estatus bergedge_start() override;

      //void _001OnFileNew();

      ////virtual void route_command_message(::user::command * pcommand) override;

      //virtual ::user::document* userex_on_request(::create* pcreate);

      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);

      ////void load_string_table() override;

      //virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;

      //void initialize_bergedge_application_interface();

      ////virtual bool create_bergedge(::create * pcreate);

      //virtual void will_use_view_hint(::id idView);

      ////virtual void on_app_request_bergedge_callback(::layered * pobjectContext);

      //virtual ::draw2d::font_list* get_single_column_font_list();

      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha);


      //virtual ::estatus do_request(::create* pcreate) override;

      //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);

      //virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);

      //virtual void request_topic_file(payload& varQuery);

      //virtual void request_topic_file();

      //virtual void check_topic_file_change();


      //void launch_app(const char* psz);
      //void install_app(const char* psz);



      //__pointer(::user::document)                   get_document();
      //__pointer(::user::impact)                     get_view();
      //__pointer(::user::document)                   get_platform();
      //__pointer(::user::document)                   get_nature();


      //inline ::userex::userex* userex() { return m_puserex; }


      ////virtual ::estatus process_init() override;

      ////virtual ::estatus init1() override;

      ////virtual ::estatus init() override;

      ////virtual ::estatus os_native_bergedge_start() override;

      //virtual ::estatus     main() override;

      //virtual ::estatus defer_initialize_host_window(LPCRECT32 lprect = nullptr);

      ////virtual service_base * allocate_new_service() override;

      ////void on_request(::create* pcreate) override;

      //__pointer(::aura::application) get_current_application();



      //virtual void set_app_title(const char* pszAppId, const char* pszTitle);

      //virtual __pointer(::aura::session) get_context_session();

      ////virtual void term() override;

      ////virtual bool open_by_file_extension(const char* pszPathName, ::create* pcreate = nullptr) override;
      ////virtual bool open_by_file_extension(::create* pcc) override;

      ////virtual bool is_session() const override;

      //virtual bool is_mouse_button_pressed(::user::e_mouse emouse);

      //virtual bool is_remote_session();

      ////virtual ::draw2d::cursor * get_cursor() override;
      ////virtual ::draw2d::cursor* get_default_cursor() override;

      ////virtual ::count   get_monitor_count() override;
      ////virtual bool      get_monitor_rect(index iMonitor, RECT32* prect) override;


      ////virtual void on_user_logon(::account::user* puser) override;


      ////virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText) override;


      //virtual string_array get_user_wallpaper();



      ////virtual void interactive_credentials(::account::credentials* pcredentials) override;



      ////session();
      ////virtual ~session();

      //inline ::user::user* user() { return m_puser; }

      ////virtual __pointer(::user::impact)                      get_view();


      ////virtual ::estatus     initialize(::layered * pobjectContext) override;


      ////virtual void frame_pre_translate_message(::message::message* pmessage) override;

      ////virtual ::estatus process_init() override;

      ////virtual ::estatus init1() override;

      ////virtual ::estatus init() override;

      ////virtual void term_session() override;

      ////virtual void interactive_credentials(::account::credentials* pcredentials) override;

      ////virtual void on_finally_focus_set(::user::primitive* pelementalFocus) override;

      ////virtual ::user::menu_interaction * create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;

      ////virtual oswindow get_capture() override;


      ////virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText) override;


      //virtual bool prepare_menu_button(::user::menu_item* pitem) override;

      ////virtual bool on_ui_mouse_message(::message::mouse* pmouse) override;



      ::user::primitive* m_pmousefocusLButtonDown;
      ::user::primitive* m_pmousefocusRButtonDown;
      //string_array                       m_straEscape;
      //::user::style_pointer              m_puserstyle;


      //::user::style * get_user_style();


      //virtual ::estatus init1() override;
      //virtual ::estatus init2() override;
      //virtual ::estatus init() override;




      //virtual ::user::primitive* get_mouse_focus_LButtonDown();
      //virtual void set_mouse_focus_LButtonDown(::user::primitive* pmousefocus);
      //virtual ::user::primitive* get_mouse_focus_RButtonDown();
      //virtual void set_mouse_focus_RButtonDown(::user::primitive* pmousefocus);



      //virtual void SendMessageToWindows(const ::id & id, WPARAM wParam, LPARAM lParam);

      virtual void term() override;

      virtual ::type controltype_to_typeinfo(::user::e_control_type econtroltype) override;



   };


} // namespace aura



