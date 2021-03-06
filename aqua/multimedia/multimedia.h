#pragma once


namespace multimedia
{


   class CLASS_DECL_AQUA information
   {
   public:


      string      m_strName;
      string      m_strAlbum;
      string      m_strArtist;


   };


}


namespace aqua
{


   class CLASS_DECL_AQUA multimedia :
      virtual public ::apex::department
   {
   public:

      
      multimedia();
      virtual ~multimedia();


      virtual ::estatus initialize_multimedia(::object* pobjectContext);

      virtual void on_song_added(const string& strId);

      virtual string get_media_call_title(const string& str);

      virtual void on_decoder_fill_title_info(::multimedia::decoder * pdecoder, string_array & straTitle, string2a & str2aTitle);

      virtual __pointer(::user::controller) defer_create_view(::object* pobjectContext, const string & strView, ::user::interaction* puiParent, ewindowflag ewindowflag = window_flag_none, const ::id& id = nullptr);

      virtual void _001OnFranceExit();

      virtual void on_command(::user::command* pcommand);

      string_array detect_language(const string& str);


      virtual ::estatus get_file_information(::file::file* pfile, ::multimedia::information& information);


   };


} // namespace aqua


extern "C"
typedef ::aqua::multimedia * GET_NEW_MULTIMEDIA();


typedef GET_NEW_MULTIMEDIA * PFUNCTION_GET_NEW_MULTIMEDIA;


CLASS_DECL_AQUA void set_get_new_multimedia(PFUNCTION_GET_NEW_MULTIMEDIA pfunction);


extern "C"
CLASS_DECL_AQUA ::aqua::multimedia * get_get_new_multimedia();


CLASS_DECL_AQUA ::aqua::multimedia * get_context_multimedia(::layered * pobjectContext);


CLASS_DECL_AQUA bool has_multimedia();


