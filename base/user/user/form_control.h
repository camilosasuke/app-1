#pragma once


namespace user
{


   class CLASS_DECL_BASE form_control:
      virtual public ::user::form
   {
   public:


      string                     m_strPath;
      bool                       m_bOnEditUpdate;
      bool                       m_bOnLanguageChange;
      ::u32                       m_uiId;
      control_descriptor_set     m_controldescriptorset;
      bool                       m_bInitialized;
      ::file::path               m_pathDefaultDocument;


      //__pointer(form_control)    m_pformChild;


      form_control();
      virtual ~form_control();


      //ref_array < CTransparentStatic > m_staticpa;


      virtual string get_path();
      virtual ::estatus open_document(const payload & varFile) override;
      //::type controltype_to_typeinfo(::user::e_control_type econtroltype);

      virtual ::estatus open_html(const ::string & str) override;


      //using ::user::interaction::_001IsPointInside;
      virtual bool _001IsPointInside(::user::interaction * pinteraction,point64 point);
      virtual void control_get_window_rect(::user::interaction * pinteraction,RECT32 * prect);

      virtual void control_get_client_rect(::user::interaction * pinteraction,RECT32 * prect);

      
      virtual ::user::form * get_form() override;
      virtual void soft_reload() override;


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(::user::interaction * pinteraction);
      virtual void _001OnInitializeForm(::user::interaction * pinteraction);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(::user::interaction * pinteraction);
      virtual void _001RemoveControls();
      bool _001Validate(::user::interaction * pinteraction,payload & payload);
      bool _001SaveEdit(::user::interaction * pinteraction);
      virtual void on_command(::user::command * pcommand) override;
      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key,::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uId,bool bData);
      bool _001GetData(id uId,bool & bData);
//      index _001AddControl(class control_descriptor  * pdescriptor) override;
      __pointer(class control_descriptor) new_form_control() override;
      void _001FillCombo(::user::interaction * pinteraction);

      virtual void WfiOnClose() override;

      DECL_GEN_SIGNAL(_000OnPosCreate);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData();
      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;
      virtual bool update_data(bool bSaveAndValidate) override;
      virtual void _001Update(::user::interaction * pinteraction);
      virtual void _001UpdateCheckBox(::user::interaction * pinteraction);
      virtual void _001UpdateComboBox(::user::interaction * pinteraction);
      virtual void _001UpdateEdit(::user::interaction * pinteraction);
      virtual void _001UpdateSimpleList(::user::interaction * pinteraction);

      virtual void _001UpdateDbFlags(::user::interaction * pinteraction);
      virtual void _001UpdateDbFlagsCheckBox(::user::interaction * pinteraction);

      DECL_GEN_SIGNAL(_001OnAppLanguage);

      bool OnCommand(WPARAM wparam,LPARAM lparam);

      bool OnCommandButton(::user::interaction * pinteraction,::u32 uNotificationCode,LPARAM lparam);

      bool OnCommandCheckBox(::user::interaction * pinteraction,::u32 uNotificationCode,LPARAM lparam);

      bool OnCommandComboBox(::user::interaction * pinteraction,::u32 uNotificationCode,LPARAM lparam);

      bool OnCommandEdit(::user::interaction * pinteraction,::u32 uNotificationCode,LPARAM lparam);



      virtual void data_on_after_change(::database::client* pclient, const ::database::key& key, const payload& payload, ::promise::subject * psubject = nullptr);


      virtual bool create_control(class control_descriptor * pdescriptor, index iItem) override;
      virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor);

      void on_control_event(::user::control_event * pevent) override;
      void _001SetControlFactory();


      virtual bool _001OnControlSetFocus(::user::interaction * pinteraction);
      virtual bool _001OnControlKillFocus(::user::interaction * pinteraction);


      //        ::user::form_window(::layered * pobjectContext);
      //    virtual ~::user::form_window();

      //virtual void install_message_routing(::channel * pchannel);

      //      DECL_GEN_SIGNAL(_001OnCreate);


      //      ::user::form_window(::layered * pobjectContext);

      //virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;
      //      virtual void on_control_event(::user::control_event * pevent);
      //      DECL_GEN_SIGNAL(_001OnCreate);
      virtual void _001OnTimer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnUser123);
      //      virtual void install_message_routing(::channel * pchannel);


//      virtual void soft_reload();

      //virtual ::form_property_set * get_form_property_set() override;

//      virtual bool _001IsPointInside(::user::interaction * pinteraction,point64 point);

      //    virtual void control_get_window_rect(::user::interaction * pinteraction,RECT32 * prect);

      //  virtual void control_get_client_rect(::user::interaction * pinteraction,RECT32 * prect);



      //virtual bool open_document(const payload & varFile) override;


   };


} // namespace user


