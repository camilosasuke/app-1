#pragma once



namespace simple_ui
{


   class top :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style
   {
   public:


      bool                       m_bLButtonDown;
      ::point                    m_pointLButtonDown;
      ::size                     m_sizeLButtonDownOffset;

      bool                       m_bDrag;



      top();
      virtual ~top();


      void install_message_routing(::channel * pchannel) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnSysCommand);

   };


} // namespace simple_ui




