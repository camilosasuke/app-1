#pragma once


namespace user
{


   class CLASS_DECL_AURA main_window :
      virtual public ::user::frame
   {
   public:


      ::rectd                                   m_rectInitialRateOrSize;




      main_window();
      virtual ~main_window();


      virtual void install_message_routing(::channel* pchannel) override;


      virtual void on_create_user_interaction() override;


      virtual ::estatus create_main_window();

   };



} // namespace user



