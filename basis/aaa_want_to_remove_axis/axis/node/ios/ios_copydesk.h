#pragma once


namespace ios
{


   class CLASS_DECL_AXIS copydesk :
      virtual public ::user::copydesk
   {
   public:


      copydesk(::layered * pobjectContext);
      virtual ~copydesk();


      virtual bool initialize();
      virtual bool finalize();

      virtual void _set_filea(const ::file::patha & patha);

      virtual i32 _get_file_count();
      virtual void _get_filea(::file::patha & patha);

      virtual void _set_plain_text(const char * psz);
      virtual string _get_plain_text();


/*      virtual bool desk_to_image(::image * pimage);
      // todo
      //bool image_to_desk(::image * pimage);

   };


} // namespace ios



