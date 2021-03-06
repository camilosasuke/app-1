#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"



namespace filemanager
{


   form::form()
   {

   }


   void form::install_message_routing(::channel * pchannel)
   {

      ::filemanager::impact::install_message_routing(pchannel);
      ::user::form_view::install_message_routing(pchannel);

   }


   void form::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::filemanager::impact::on_subject(psubject, pcontext);

      ::user::form_view::on_subject(psubject, pcontext);

   }


   void form::on_control_event(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "lfs")
         {

            auto psubject = subject(BROWSE_ID);

            psubject->value(id_form) = "filemanager_add_location_lfs.xhtml";

            get_document()->update_all_views(psubject);

            auto pinteraction = get_child_by_name("lfs");

            pinteraction->_001SetText(filemanager_item()->m_filepathUser,::source_user);

         }
         else if(pevent->m_puie->m_id == "ftp")
         {

            auto psubject = subject(id_browse);

            psubject->value(id_form) = "filemanager_add_location_ftp.xhtml";

            get_document()->update_all_views(psubject);

         }
         else if(pevent->m_puie->m_id == "submit")
         {
            if(m_strPath == "filemanager_add_location_lfs.xhtml")
            {
               string_array stra;
               Application.data_get(filemanager_data()->m_dataidStatic,stra);

               auto pinteraction = get_child_by_name("lfs");

               string str;

               pinteraction->_001GetText(str);

               stra.add_unique(str);
               Application.data_set(filemanager_data()->m_dataidStatic,stra);

            }
            else if(m_strPath == "filemanager_add_location_ftp.xhtml")
            {
            }
            else if(m_idCreator == "replace_name")
            {

               auto psubject = subject(id_replace_name);

               auto pinteraction = get_child_by_name("find");

               pinteraction->_001GetText(psubject->value(id_find));

               pinteraction = get_child_by_name("replace");

               pinteraction->_001GetText(psubject->value(id_replace));

               auto pdocument =  filemanager_document();

               pdocument->update_all_views(psubject);

            }
            else if (m_idCreator == "new_folder")
            {
               
               auto psubject = subject(id_new_folder);

               auto pinteraction = get_child_by_name("name");

               pinteraction->_001GetText(psubject->value(id_text));

               auto pdocument = filemanager_document();

               pdocument->update_all_views(psubject);

            }

         }

      }

   }


} // namespace filemanager




