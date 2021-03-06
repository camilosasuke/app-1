#pragma once


#ifdef WINDOWS_DESKTOP


namespace user
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_AURA system_interaction_impl :
      virtual public ::user::interaction
   {
      public:

         
         system_interaction_impl();
         virtual ~system_interaction_impl();


         virtual void install_message_routing(::channel * pchannel) override;

         DECL_GEN_SIGNAL(_001OnMessage);
         DECL_GEN_SIGNAL(_001OnDestroy);


         virtual bool DestroyWindow() override;
         
         virtual bool is_system_message_window() override;
   

   };


} // namespace base


#endif


