#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#endif
#include "aura/update.h"


namespace user
{


   namespace rich_text
   {


      document::document()
      {

         m_strSaveFileExtension = "rtf";

      }


      document::~document()
      {

      }





      void document::assert_valid() const
      {

         ::user::document::assert_valid();

      }


      void document::dump(dump_context & dumpcontext) const
      {

         ::user::document::dump(dumpcontext);

      }


      bool document::on_new_document()
      {

         return ::user::document::on_new_document();

      }


      bool document::on_open_document(::file::file * pfile)
      {

         string str;

         pfile->full_read_string(str);

         parse_rtf_text(str);

         return true;

      }


      bool document::on_save_document(::file:: file * pfile)
      {

         auto pedit = get_typed_view<::user::rich_text::edit_impl>();

         auto pdata = pedit->m_pdata;

         auto ptextformat = __id_create< ::user::rich_text::text_format >("text_format::rtf");

         ptextformat->text_format_save(pfile, pdata);

         return true;

      }



      bool document::parse_rtf_text(string str)
      {

//         Application.m_ppaneview->set_cur_tab_by_id(::impact_rich_edit);

         return true;

      }

#ifdef DEBUG

      i64 document::add_ref(OBJ_REF_DBG_PARAMS_DEF)
      {

         return  ::user::document::add_ref(OBJ_REF_DBG_ARGS);

      }

      i64 document::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
      {

         return  ::user::document::dec_ref(OBJ_REF_DBG_ARGS);

      }

#endif

   
   } // namespace rich_text


} // namespace user



