#pragma once


namespace userex
{


   class CLASS_DECL_CORE wait_message_dialog :
      virtual public dialog
   {
   public:


      millis            m_millisStart;
      millis            m_millisDelay;
      id                m_idResponse;
      int               m_iSecond;


      wait_message_dialog();
      virtual ~wait_message_dialog();


      //virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_show(const char * pszMatter) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      //virtual void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual bool on_timeout_check();
      virtual bool on_timeout();
      virtual void on_timer_soft_reload(millis tickTimeout);

      
      //virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;
      

   };


} // namespace userex


