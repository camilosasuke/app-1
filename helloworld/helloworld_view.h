#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD view :
      virtual public hellobase::view,
      virtual public hellobase::impact_base
   {
   public:




      string                  m_strServer;
      ::image_pointer        m_pimageAi1;
      ::image_pointer        m_pimageAi2;

      string                  m_strImage;
      ::image_pointer        m_pimageColor;

      bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      view(::layered * pobjectContext);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

      virtual void install_message_routing(::channel * pchannel);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      ::user::document * get_document();



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual string get_helloworld();

      virtual string get_processed_helloworld();



      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld





















