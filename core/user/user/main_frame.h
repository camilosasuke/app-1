#pragma once


namespace user
{


   class CLASS_DECL_CORE main_frame : 
      public simple_frame_window
   {
   public:


      bool           m_bPlacing;
      
      
      main_frame();
      virtual ~main_frame();

      virtual void install_message_routing(::channel * pchannel);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace user


