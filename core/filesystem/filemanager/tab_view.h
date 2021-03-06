#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tab_view :
      virtual public ::userex::pane_tab_view
   {
   public:


      

      tab_view();
      virtual ~tab_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void on_create_impact(::user::impact_data * pimpactdata) override;
      virtual void install_message_routing(::channel * pchannel) override;
      void FileManagerBrowse(const char * pcwstr, const ::action_context & action_context);



      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      __pointer(document) get_document();

   };


} // namespace filemanager




