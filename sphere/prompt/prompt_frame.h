#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:


      
      ::user::message_queue_pointer   m_spqueue;

      bool                       m_bAutoHideOnOutClick;
      i32                 m_iAnimateStep;
      __pointer(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      e_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

      frame(::layered * pobjectContext);
      virtual ~frame();

      virtual void install_message_routing(::channel * pchannel);

      void ShowControlBars(bool bShow);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      bool m_bHoverMouse;
      millis m_millisLastHover;

      void OnHoverAction(bool bShowWinActionArea);

      void ToFront();

      virtual void on_command(::user::command * pcommand);
      virtual void on_command_probe(::user::command * pcommand);



      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);

      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnApp2000);


      virtual void message_queue_message_handler(::message::message * pmessage);
   };


} // namespace prompt


