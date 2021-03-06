#pragma once


namespace apex
{


   class CLASS_DECL_APEX session:
      virtual public ::apex::context_thread,
      virtual public ::application_container
      //,
      //virtual public ::filemanager::item_action //,
      //virtual public ::filemanager::component,
      //virtual public ::user::document_manager_container
   {
   public:


      class CLASS_DECL_APEX map:
         virtual public isomap < index, __pointer(::apex::session) >
      {


      };


//#if defined _UWP
//
//      ::uwp::directx_framework_view ^                          m_frameworkview;
//
//#endif

#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      __composite(::layered)                      m_puiSession;

#endif


      ::aqua::session *       m_paquasession;
      ::aura::session *       m_paurasession;
      ::axis::session *       m_paxissession;
      ::base::session *       m_pbasesession;
      ::bred::session *       m_pbredsession;
      ::core::session *       m_pcoresession;

      // For Mobile systems it is particularly meaningful...
      // ... is is the "Main Window" (sometimes just a concept) holding the App.
      // For Desktop Applications a meaning should be given or this member could be ignored?
      // The Main Application window?
      __reference(::layered)                                m_puiHost;
      __pointer(::layered)     m_pimplLastSeed;
      //__pointer(::layered)                        m_puiMain2;

      // apex commented
      //__composite(::user::keyboard)                         m_pkeyboard;

      index                                                 m_iEdge;

      ::map < ::user::e_key, ::user::e_key, bool, bool > *  m_pmapKeyPressed;

      bool                                                  m_bProgrammerMode;

      bool                                                  m_bSystemSynchronizedCursor;
      point                                                 m_pointCursor;

      //comparable_array < __reference(::layered) > m_uiptraToolWindow;

      // apex commented
      //::user::interaction_impl *                            m_pimplPendingFocus2;
      //::layered *                                 m_puiLastUserInputPopup;
      //::draw2d::cursor *                                    m_pcursor;
      //::draw2d::cursor *                                    m_pcursorCursor;
      //e_cursor                                              m_ecursorDefault;
      //e_cursor                                              m_ecursor;

      // apex commented
      //::layered *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;

      //__pointer(::object)                                   m_pobjectCoreUser;

      // apex commented
      //__composite(::user::copydesk)                         m_pcopydesk;

      // apex commented
      //::layered *                                 m_puiMouseMoveCapture;
      //::layered *                                 m_puiLastLButtonDown;


      // apex commented
      //::draw2d::font_enum_item_array                        m_fontenumitema;

      //index                                               m_iEdge;

      //__composite(::account::department)                    m_paccount;
      //__pointer(::account::licensing)                     m_plicensing;
      //__composite(::layered)                      m_puserinteractionSystem;

      payload                                                   m_varTopicFile;
      payload                                                   m_varCurrentViewFile;
      bool                                                  m_bShowPlatform;

      __composite(::apex::str_context)                      m_puserstrcontext;


      bool                                                  m_bSystemSynchronizedScreen;

#ifdef WINDOWS_DESKTOP

      //#pragma message("at macos??")
      raw_array < MONITORINFO >                          m_monitorinfoa;
      raw_array < HMONITOR >                             m_hmonitora;
      raw_array < MONITORINFO >                          m_monitorinfoaDesk;

#else

      //rect_array                                         m_rectaMonitor;
      //rect_array                                         m_rectaWork;

      rect_array                                            m_rectaMonitor;
      rect_array                                            m_rectaWkspace;
#endif

      index                                                 m_iMainMonitor;
      index                                                 m_iMainWkspace;


      // apex commented
      //id_map < ::layered * >                      m_mapboundui;



      //__composite(::userpresence::department)               m_puserpresence;


      __composite(::ftpfs)                                  m_pftpfs;
      __composite(::fs::remote_native)                      m_premotefs;
      __composite(::fs::fs)                                 m_pfs;
      __composite(::fs::data)                               m_pfsdata;
      __composite(::ifs)                                    m_pifs;
      //ke
      bool                                                  m_bIfs;

      bool                                                  m_bMatterFromHttpCache;

      ::u32                                                 m_dwLongPhRESSingTime;


      session();
      virtual ~session();


      virtual ::estatus     initialize(::layered * pobjectContext) override;

      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      virtual bool is_session() const override;

      virtual void enum_display_monitors();

      //void construct(::object * pobject, int iPhase) override;

      virtual index get_main_monitor(RECT32* prect = nullptr);

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor, RECT32* prect);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor, RECT32* prect);


      virtual index get_main_wkspace(RECT32* prect = nullptr);

      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace, RECT32* prect);

      virtual ::count get_desk_wkspace_count();
      virtual bool  get_desk_wkspace_rect(index iWkspace, RECT32* prect);

      //virtual index get_ui_wkspace(::user::interaction * pinteraction);

      virtual ::estatus process_init();

      virtual ::estatus init1();

      virtual ::estatus init2();

      virtual ::estatus init_session();

      virtual ::estatus init();

      virtual void term();

      virtual void term_session();


      inline class ::fs::data * fs() { return m_pfsdata; }


      //inline ::sockets::sockets & sockets() { return *m_psockets; }


      virtual size get_window_minimum_size();


      //virtual void  get_cursor_pos(POINT32 * ppoint);

      virtual bool on_get_thread_name(string& strThreadName) override;


      virtual void on_request(::create * pcreate) override;


      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      //virtual string dir().matter(const char * pszMatter,const char * pszMatter2);

      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);

      // Long PhRESSing time
      // time in milliseconds that a pressing is considered a double click
      virtual ::u32 get_Long_PhRESSing_time();

      //virtual void defer_initialize_user_presence();

      //virtual ::estatus     interactive_credentials(::account::credentials * pcredentials) override;

      virtual bool on_create_frame_window();

      //virtual string account_get_user_sessid(const string & str) override;

      // apex commented
      //virtual void translate_os_key_message(::user::key * pkey);

      //virtual void on_user_logon(::account::user * puser);

      virtual void pre_translate_message(::message::message * pmessage) override;

      //session();
      //virtual ~session();


      //virtual ::user::style * get_user_style() const;


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual ::estatus     initialize(::layered * pobjectContext) override;


      virtual ::user::interaction * get_session_window();

      // apex commented
      ::apex::str_context * str_context() { return m_puserstrcontext; }

      //virtual bool is_session() const override;

      virtual ::estatus init_thread() override;

      //virtual ::estatus process_init();

      //virtual ::estatus init1();

      //virtual ::estatus init2();

      //virtual ::estatus init_session();

      //virtual ::estatus init();

      //virtual void term();
      virtual void term2();

      virtual void term1();

      virtual void term_thread() override;

      //virtual void term_session();

      virtual void process_term();

      // apex commented
      //::user::keyboard& keyboard();

      virtual bool open_by_file_extension(const char * pszPathName, ::create * pcreate = nullptr);

      virtual bool open_by_file_extension(::create * pcc);

      virtual color32_t get_default_color(u64 u);

      virtual void frame_pre_translate_message(::message::message * pmessage);

      virtual bool is_licensed(const char * pszId, bool bInteractive = true);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      ::apex::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual bool is_key_pressed(::user::e_key ekey);

      virtual void set_key_pressed(::user::e_key ekey, bool bPressed);


      // apex commented
      virtual void get_cursor_pos(POINT32 * ppoint);
      inline ::point get_cursor_pos() {::point point; get_cursor_pos(&point); return point;}

      // apex commented
      virtual void set_cursor_pos(const ::point & point);

      //virtual index get_main_monitor(RECT32 * prect = nullptr);

      virtual bool set_main_monitor(index iMonitor);
      //virtual ::count get_monitor_count();
      //virtual bool  get_monitor_rect(index iMonitor, RECT32 * prect);

      //virtual index get_main_wkspace(RECT32 * prect = nullptr);

      virtual bool set_main_wkspace(index iWkspace);
      //virtual ::count get_wkspace_count();
      //virtual bool  get_wkspace_rect(index iWkspace, RECT32 * prect);

      virtual bool wkspace_to_monitor(RECT32 * prect, index iMonitor, index iWkspace);

      virtual bool monitor_to_wkspace(RECT32 * prect, index iWkspace, index iMonitor);

      virtual bool wkspace_to_monitor(RECT32 * prect);

      virtual bool monitor_to_wkspace(RECT32 * prect);

      //virtual ::count get_desk_monitor_count();
      //virtual bool  get_desk_monitor_rect(index iMonitor, RECT32 * prect);

      virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const ::rect & rect);

      // apex commented
      //virtual index initial_frame_position(RECT32 * prect, const ::rect & rect, bool bMove, ::user::interaction * pinteraction);

      virtual index _get_best_zoneing(edisplay * pedisplay, ::rect * prect, const ::rect & rect, bool bPreserveSize = false);

      virtual index get_best_monitor(RECT32 * prect, const ::rect & rect, ::eactivation eactivation = e_activation_default);

      virtual index get_best_wkspace(::rect * prect, const ::rect& rect, ::eactivation eactivation = e_activation_default);

      virtual index get_good_iconify(RECT32 * prect, const ::rect & rect);

      // apex commented
      //virtual index get_window_restore_1(RECT32 * prect, const ::rect & rect, ::user::interaction * pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual index get_window_restore_2(RECT32* prect, const ::rect& rect, ::user::interaction* pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual index get_good_move(RECT32 * prect, const ::rect & rect, ::user::interaction * pinteraction);

      // apex commented
      //virtual index get_ui_wkspace(::user::interaction * pinteraction);


      //virtual void defer_instantiate_user_theme(const char * pszUiInteractionLibrary = nullptr);
      //__pointer(::user::theme) instantiate_user_theme(const char * pszExperienceLibrary, ::apex::application * papp = nullptr);
      //__pointer(::user::theme) get_user_theme(const char * pszExperienceLibrary, ::apex::application * papp = nullptr);


      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText);


      // apex commented
      //virtual void set_bound_ui(::id idView, ::user::interaction * pinteraction);
      //virtual ::user::interaction * get_bound_ui(::id idView);

      // apex commented
      //virtual void on_show_user_input_popup(::user::interaction * pinteraction);

      //virtual void on_user_logon(::account::user * puser);



      //virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual void install_message_routing(::channel* pchannel) override;

      //virtual ::estatus userex_process_init();
      //virtual ::estatus userex_init1();
      //virtual ::estatus init2() override;
      //virtual bool init3() override;
      //virtual bool initialize_filemanager();
      ///virtual ::estatus init_session() override;
      //virtual void add_document_template(::user::impact_system * ptemplate);

      //virtual void term_session() override;
      //virtual void term3() override;
      //virtual bool finalize_filemanager();

      virtual void finalize() override;

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


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle,::user::menu_item* pitem) override;




      virtual bool InitializeLocalDataCentral();

      //virtual ::estatus bergedge_start() override;

      void _001OnFileNew();

      //virtual void route_command_message(::user::command * pcommand) override;

      //virtual ::user::document* userex_on_request(::create* pcreate);

      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);

      //void load_string_table() override;

//      virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;

      //void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::create * pcreate);

      //virtual void will_use_view_hint(::id idView);

      //virtual void on_app_request_bergedge_callback(::layered * pobjectContext);

      // apex commented
      //virtual ::draw2d::font_list* get_single_column_font_list();

      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha);


      virtual ::estatus do_request(::create* pcreate) override;

      // apex commented
      //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);

      // apex commented
      //virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);

      virtual void request_topic_file(payload& varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();


      void launch_app(const char* psz);
      void install_app(const char* psz);



      //user __pointer(::user::document)                   get_document();
      //user __pointer(::user::impact)                     get_view();
      //user __pointer(::user::document)                   get_platform();
      //user __pointer(::user::document)                   get_nature();


      //inline ::userex::userex* userex() { return m_puserex; }


      //virtual ::estatus process_init() override;

      //virtual ::estatus init1() override;

      //virtual ::estatus init() override;

      //virtual ::estatus os_native_bergedge_start() override;

      virtual ::estatus main() override;

      virtual ::estatus defer_initialize_host_window(LPCRECT32 lpcrect = nullptr);

      __pointer(::apex::application) get_current_application();

      virtual void set_app_title(const char* pszAppId, const char* pszTitle);

      virtual __pointer(::apex::session) get_context_session();

      virtual bool is_remote_session();

      virtual string_array get_user_wallpaper();

      inline ::user::interaction* host() { return __user_interaction(m_puiHost); }


   };


} // namespace apex



