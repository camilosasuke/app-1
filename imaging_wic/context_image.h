#pragma once


namespace imaging_wic
{


   class CLASS_DECL_IMAGING_WIC context_image :
      virtual public ::context_image
   {
   public:


      class CLASS_DECL_IMAGING_WIC load_image :
         virtual public ::object
      {
      public:


         payload                        m_varFile;
         ::image_pointer            m_pimage;
         __pointer(context_image)   m_pcontextimage;


         load_image(context_image* pcontextimage);
         virtual ~load_image();


         virtual ::estatus run() override;


         virtual void on_os_load_image(memory_pointer pmemory);


      };


      __composite(handler_manager)        m_pmanagerImageLoad;


      context_image();
      virtual ~context_image();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      //virtual ::estatus _load_image(::context_image * pcontextimage, ::image * pimageParam, const payload & varFile, bool bSync, bool bCreateHelperMaps) override;
      virtual ::estatus _load_image(image* pimage, const ::payload& varFile, bool bSync = true, bool bCreateHelperMaps = false);

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory);
      virtual ::estatus save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage) override;

      //virtual ::estatus _load_image(::image* pimage, const payload& varFile, bool bSync, bool bCreateHelperMaps);


      //virtual ::estatus _load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory);
      //virtual ::estatus save_image(memory& memory, const ::image* pimage, ::save_image* psaveimage);


      //virtual ::estatus load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bCache = true) override;

      //virtual ::estatus load_svg(::image* pimage, ::memory_pointer pmemory);


#ifdef _UWP
      virtual bool _desk_to_image(::image* pimage);
      virtual bool _desk_has_image();
      virtual bool _image_to_desk(const ::image* pimage);
#endif


   };


} // namespace imaging_wic



