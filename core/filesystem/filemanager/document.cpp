#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"


namespace filemanager
{


   document::document()
   {

      m_bInitialized = false;

      m_filewatchid = -1;

      m_bFullBrowse = false;

      //m_pfilewatcherlistenerthread = nullptr;

      //command_signalid id;

      connect_command_probe("levelup", &document::_001OnUpdateLevelUp);
      connect_command("levelup", &document::_001OnLevelUp);
      connect_command_probe("add_location", &document::_001OnUpdateAddLocation);
      connect_command("add_location", &document::_001OnAddLocation);
      connect_command_probe("replace_text_in_file_system", &document::_001OnUpdateReplaceText);
      connect_command("replace_text_in_file_system", &document::_001OnReplaceText);
      connect_command_probe("edit_paste", &document::_001OnUpdateEditPaste);
      connect_command("edit_paste", &document::_001OnEditPaste);
      connect_command_probe("file_save", &document::_001OnUpdateFileSaveAs);
      connect_command("file_save", &document::_001OnFileSaveAs);
      connect_command_probe("cancel", &document::_001OnUpdateEditPaste);
      connect_command("cancel", &document::_001OnEditPaste);
      connect_command_probe("new_manager", &document::_001OnUpdateNewManager);
      connect_command("new_manager", &document::_001OnNewManager);
      connect_command_probe("del_manager", &document::_001OnUpdateDelManager);
      connect_command("del_manager", &document::_001OnDelManager);
      connect_command_probe("new_folder", &document::_001OnUpdateNewFolder);
      connect_command("new_folder", &document::_001OnNewFolder);

   }


   document::~document()
   {

   }

   bool document::do_prompt_file_name(payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocumentOther)
   {

      UNREFERENCED_PARAMETER(nIDSTitle);
      UNREFERENCED_PARAMETER(lFlags);
      UNREFERENCED_PARAMETER(ptemplate);

      ASSERT(bOpenFileDialog == FALSE);

      __pointer(document) pdocument = this;

      tab_view * pview = pdocument->get_typed_view < tab_view >();

#ifdef WINDOWS_DESKTOP
      oswindow oswindowDesktop = ::get_desktop_window();
      ::rect rectOpen;
      ::GetWindowRect(oswindowDesktop, rectOpen);
      i32 iWidth = rectOpen.width();
      i32 iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      pview->GetParentFrame()->order(zorder_top);
      pview->GetParentFrame()->place(rectOpen);
      pview->GetParentFrame()->display();

#endif
      pview->set_cur_tab_by_id(1);
      pview->GetParentFrame()->set_need_redraw();
      pview->GetParentFrame()->RunModalLoop();
      varFile = pdocument->m_strTopic;
      pview->GetParentFrame()->DestroyWindow();
      return TRUE;

   }


   bool document::browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      if (m_pfsset->m_spafsdata.is_empty())
      {

         m_pfsset->m_spafsdata.remove_all();

         auto psession = Session;

         m_pfsset->m_spafsdata.add(psession->fs());

         ::file::listing listing;

         m_pfsset->root_ones(listing);

      }

      string strOldPath;

      if (m_pitem.is_set())
      {

         strOldPath = m_pitem->m_filepathUser;

      }

      try
      {

         m_pitem = __new(::file::item(*pitem));

         OnFileManagerBrowse(context + ::source_sync);

      }
      catch (string & str)
      {

         if (str == "uifs:// You have not logged in!")
         {

            message_box("You have not logged in! Cannot access your User Intelligent File System - uifs://");

            // assume can resume at least from this exception one time

            m_pitem = __new(::file::item(Context.defer_process_path(strOldPath), strOldPath));

            OnFileManagerBrowse(context + ::source_sync);

         }

         return false;

      }

      if (m_filewatchid >= 0)
      {

         Context.dir().watcher().remove_watch(m_filewatchid);

      }

      try
      {

         auto& context = Context;

         auto& dir = context.dir();

         auto& watcher = dir.watcher();

         m_filewatchid = watcher.add_watch(m_pitem->m_filepathFinal, this, false);

      }
      catch (...)
      {

         m_filewatchid = -1;

      }

      return true;

   }


   void document::on_file_manager_open_context_menu_folder(__pointer(::file::item)  item, string_array & straCommand, string_array & straCommandTitle, const ::action_context & context)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_open_context_menu_folder(filemanager_data(), item, straCommand, straCommandTitle, context);

      }

   }


   void document::on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & context)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_open_context_menu_file(filemanager_data(), itema, context);

      }

   }


   void document::on_file_manager_open_context_menu(const ::action_context & context)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_open_context_menu(filemanager_data(), context);

      }

   }


   void document::on_file_manager_open(const ::file::item_array & itema, const ::action_context & context)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->is_topic() && itema.get_count() == 1)
      {

         __pointer(document) pdocument = this;

         auto psubject = subject(TOPIC_OK_ID);

         psubject->value(DOCUMENT_ID) = pdocument;

         psubject->m_pfileitem = itema.get_first_pointer();

         pdocument->update_all_views(psubject);

         filemanager_data()->m_pdocumentTopic = nullptr;

      }
      else if (filemanager_data()->m_pcallback != nullptr)
      {

         payload varFile;

         payload varQuery;

         if (itema.get_count() == 2 && m_id == "filemanager::main::left")
         {

            {

               varFile = itema[0]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::left";

               filemanager_data()->m_pcallback->request_file(varFile, varQuery);

            }

            {

               varFile = itema[1]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::right";

               filemanager_data()->m_pcallback->request_file(varFile, varQuery);

            }

         }
         else if (itema.get_count() == 2 && m_id == "filemanager::main::right")
         {

            {

               varFile = itema[0]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::right";

               filemanager_data()->m_pcallback->request_file(varFile, varQuery);

            }

            {

               varFile = itema[1]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::left";

               filemanager_data()->m_pcallback->request_file(varFile, varQuery);

            }

         }
         else
         {

            varFile = itema.get_var_final_path();

            varQuery = itema.get_var_query();

            varQuery["::filemanager::id"] = m_id;

            auto pcallback = filemanager_data()->m_pcallback;

            pcallback->request_file(varFile, varQuery);

         }

      }

   }


   void document::on_file_manager_open_folder(__pointer(::file::item)  item, const ::action_context & context)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_open_folder(filemanager_data(), item, context);

      }

   }


   void document::on_file_manager_item_update(::user::command * pcommand, const ::file::item_array & itema)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_item_update(filemanager_data(), pcommand, itema);

      }

   }


   void document::on_file_manager_item_command(const char * pszId, const ::file::item_array & itema)
   {

      ASSERT(filemanager_data()->m_pcallback != nullptr);

      if (filemanager_data()->m_pcallback != nullptr)
      {

         filemanager_data()->m_pcallback->on_file_manager_item_command(filemanager_data(), pszId, itema);

      }

   }


   //void document::browse(__pointer(::file::item) item, const ::action_context & context)
   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_document()->browse(item, context);

   //   }

   //}

   //void data::browse(const char * pcsz, const ::action_context & context)

   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_document()->browse(pcsz, context);


   //   }

   //}


   void document::browse(const char * pszPath, const ::action_context & context)
   {

      ::file::path pathUser = pszPath;

      ::file::path pathFinal = Context.defer_process_path(pathUser);

      __pointer(::file::item) pitem = __new(::file::item(pathUser, pathFinal));

      browse(pitem, context);

   }


   void document::FileManagerOneLevelUp(const ::action_context & context)
   {

      if (filemanager_item()->m_filepathUser.is_empty())
         return;

      string strParent = filemanager_item()->m_filepathUser.up();

      browse(strParent, context + ::source_sync);

   }


   ::file::item * document::filemanager_item()
   {

      return m_pitem;

   }


   ::filemanager::data * document::filemanager_data()
   {

      return m_pfilemanagerdata;

   }


   ::fs::data * document::fs_data()
   {

      return m_pfsset;

   }


   document * document::get_main_document()
   {

      __pointer(tab_view) ptabview = get_typed_view < tab_view >();

      if (ptabview.is_set())
      {

         for (index i = 0; i < ptabview->get_pane_count(); i++)
         {

            ::user::tab_pane * ptabpane = ptabview->get_pane(i);

            if (ptabpane != nullptr && ptabpane->m_pplaceholder != nullptr)
            {

               __pointer(child_frame) pchildframe = ptabpane->m_pplaceholder->first_child();

               if (pchildframe.is_set())
               {

                  __pointer(document) pdocument = pchildframe->GetActiveDocument();

                  if (pdocument.is_set())
                  {

                     return pdocument;

                  }

               }

            }

         }

      }

      return this;

   }


   bool document::set_filemanager_data(::filemanager::data * pdata)
   {

      m_pfilemanagerdata = pdata;

      return true;

   }


   void document::defer_check_manager_id(string strManagerId)
   {

      auto puser = User;

      if(puser->m_pathFilemanagerProject.has_char())
      {

         if (!is_valid_manager_id(m_strManagerId) || is_valid_manager_id(strManagerId))
         {

            if (is_valid_manager_id(strManagerId))
            {

               m_strManagerId = strManagerId;

            }
            else
            {

               m_strManagerId = create_manager_id(get_context_object());

            }

            //set_data_key_modifier(m_strManagerId);

  /*          __pointer(main_frame) pframe = get_view()->GetTypedParent < main_frame >();

            if (pframe.is_set() && !pframe->m_id.to_string().contains("::frame"))
            {

               pframe->set_data_key_modifier(m_strManagerId);

            }*/

         }

         __pointer(document) pdocument = get_main_document();

         if (pdocument.is_set() && pdocument.m_p != this && pdocument->m_strManagerId != m_strManagerId)
         {

            pdocument->defer_check_manager_id(m_strManagerId);

         }

      }

   }


   //critical_section * document::GetItemIdListCriticalSection()
   //{
   //   return &m_csItemIdListAbsolute;
   //}


   void document::FileManagerTopicOK()
   {

   }


   void document::FileManagerTopicCancel()
   {

   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
      {

         return false;

      }

      defer_check_manager_id();

      if (!m_bInitialized)
      {

         filemanager_initialize(true, true);

      }

      return true;

   }



   bool document::on_open_document(const payload & varFile)
   {

      ::file::path path = varFile.get_file_path();

      path.trim();

      defer_check_manager_id();

      if (!m_bInitialized)
      {

         filemanager_initialize(true, false);

      }

      string strManagerId;

      m_path = filemanager_project_entry(strManagerId, varFile.get_string(), get_context());

      defer_check_manager_id(strManagerId);

      return true;

   }


   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }


   void document::start_full_browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      if (!fs_data()->is_zero_latency(pitem->m_filepathFinal))
      {

         auto psubject = subject(SYNCHRONIZE_PATH_ID);

         psubject->m_actioncontext = context + ::source_sync + ::source_system;

         psubject->m_pfileitem = pitem;

         update_all_views(psubject);

      }


      opt_fork(__routine([=]()
      {

         full_browse(pitem, context);

      }));


   }


   void document::full_browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      __task_guard(m_bFullBrowse);

#define DBG_BROWSE_LOOP 1
      for (index i = 0; i < DBG_BROWSE_LOOP; i++)
      {

         ::userfs::document::browse(pitem, context);

      }

      auto psubject = subject(SYNCHRONIZE_PATH_ID);

      psubject->m_actioncontext = context + ::source_sync;

      psubject->m_pfileitem = pitem;

      update_all_views(psubject);

   }


   void document::OnFileManagerBrowse(const ::action_context & context)
   {

      start_full_browse(m_pitem, context);

      if (context.is_user_source())
      {

         auto puser = User;

         if (puser->m_pathFilemanagerProject.is_empty())
         {

            filemanager_data()->set_last_browse_path(this, m_pitem->m_filepathUser);

         }
         else
         {

            auto puser = User;

            puser->filemanager_save_project();

         }

      }

   }


   void document::OpenSelectionProperties()
   {

      auto psubject = subject(id_open_selection_properties);

      update_all_views(psubject);

   }


   void document::on_command(::user::command * pcommand)
   {

      if (filemanager_data() != nullptr)
      {

         if (pcommand->m_id == filemanager_data()->m_strLevelUp)
         {

            FileManagerOneLevelUp(::source_user);

            pcommand->m_bRet = true;

            return;

         }

      }

      ::user::document::on_command(pcommand);

   }


   void document::on_command_probe(::user::command * pcommand)
   {
      /*if(pcommand->m_id == filemanager_template()->m_strLevelUp)
      {
      FileManagerOnUpdateLevelUp(pcommand);
      return true;
      }*/
      ::user::document::on_command_probe(pcommand);

   }



   void document::_001OnUpdateNewManager(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(TRUE);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewManager(::message::message * pmessage)
   {

      auto pcreate = __create_new <::create>();

      pcreate->finish_initialization();

      auto puser = User;

      puser->add_filemanager("", pcreate);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateDelManager(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(TRUE);

      pmessage->m_bRet = true;

   }


   void document::_001OnDelManager(::message::message * pmessage)
   {

      __pointer(document) pdocument = this;

      __pointer(view) pview = get_typed_view<view>();

      if (pview.is_set())
      {

         __pointer(tab_view) ptabview = pview->GetTypedParent <tab_view>();

         if (ptabview.is_set())
         {

            pdocument = ptabview->get_document();

         }

      }

      auto puser = User;

      puser->remove_filemanager(pdocument.m_p);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateLevelUp(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      if (m_pitem.is_null() || m_pitem->m_filepathUser.is_empty())
      {

         pcommand->enable(FALSE);

      }
      else
      {

         pcommand->enable(TRUE);

      }

      pmessage->m_bRet = true;

   }


   void document::_001OnLevelUp(::message::message * pmessage)
   {
      FileManagerOneLevelUp(::source_user);
      pmessage->m_bRet = true;
   }


   void document::_001OnUpdateAddLocation(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(TRUE);

      pmessage->m_bRet = true;

   }


   void document::_001OnAddLocation(::message::message * pmessage)
   {

      id_update_all_views(id_add_location);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateReplaceText(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(TRUE);

      pmessage->m_bRet = true;

   }


   void document::_001OnReplaceText(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      id_update_all_views(id_replace_name);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateNewFolder(::message::message * pmessage)
   {

      SCAST_PTR(::user::command, pcommand, pmessage);

      pcommand->enable(TRUE);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewFolder(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      id_update_all_views(id_new_folder);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateEditPaste(::message::message * pmessage)
   {
      //      SCAST_PTR(::user::command, pcommand, pmessage);

      //         pcommand->enable(System.m_strCopy.is_empty());
      pmessage->m_bRet = true;
   }

   void document::_001OnEditPaste(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //Context.file().paste(filemanager_data()->filemanager_item().m_strPath, System.m_strCopy);
      //update_all_views(nullptr, 123, nullptr);
      //pmessage->m_bRet = true;
   }

   void document::_001OnUpdateFileSaveAs(::message::message * pmessage)
   {
      SCAST_PTR(::user::command, pcommand, pmessage);
      pcommand->enable(TRUE);
   }

   void document::_001OnUpdateFileImport(::message::message * pmessage)
   {
      SCAST_PTR(::user::command, pcommand, pmessage);
      pcommand->enable(TRUE);
   }

   void document::_001OnUpdateFileExport(::message::message * pmessage)
   {
      SCAST_PTR(::user::command, pcommand, pmessage);
      pcommand->enable(TRUE);
   }


   void document::_001OnFileSaveAs(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_saving || m_emode == ::userfs::mode_export)
      {

         auto psubject = subject(id_topic_ok);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      pmessage->m_bRet = true;

   }


   void document::_001OnFileImport(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_import)
      {

         auto psubject = subject(id_topic_ok);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

   }


   void document::_001OnFileExport(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_saving)
      {

         auto psubject = subject(id_topic_ok);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

   }


   void document::filemanager_initialize(bool bMakeVisible, const ::file::path & path)
   {

      InitializeFileManager("filemanager");

      CreateViews();

      auto psubject = subject(id_create_bars);

      psubject->value(id_document) = this;

      browse(path, ::source_database);

      update_all_views(psubject);

      if (bMakeVisible)
      {

         auto psubject = subject(id_pop);

         update_all_views(psubject);

      }

   }


   void document::filemanager_initialize(bool bMakeVisible, bool bInitialBrowsePath)
   {

      CreateViews();

      auto psubject = subject(id_create_bars);

      psubject->value(id_document) = this;

      if (bInitialBrowsePath)
      {

         string str;

         auto path = filemanager_data()->get_last_browse_path(this, filemanager_data()->m_pathDefault);

            browse(path, ::source_initialize);

//         if (get_file.data_get({true, "last_browse_folder"}, str))
//         {
//
//            if (str == "machinefs://")
//            {
//
//               id idMachine;
//
//#ifdef LINUX
//               idMachine = "Linux";
//#elif defined(WINDOWS_DESKTOP)
//               idMachine = "WindowsDesktop";
//#elif defined(WINDOWS)
//               idMachine = "Metrowin";
//#elif defined(MACOS)
//               idMachine = "macOS";
//#elif defined(__APPLE__)
//               idMachine = "iOS";
//#endif
//
//               if (Application.data_get({true, "last_browse_folder." + __str(idMachine)}, str))
//               {
//
//                  browse(str, ::source_database);
//
//               }
//               else
//               {
//
//                  browse("", ::source_system);
//
//               }
//
//            }
//            else
//            {
//
               //browse(str, ::source_database);

//            }

         //}
         //else if (filemanager_data()->m_pathDefault.has_char())
         //{

         //   browse(filemanager_data()->m_pathDefault, ::source_initialize);

         //}
         //else
         //{

         //   browse("", ::source_system);

         //}

      }

      //psubject->id() = ;

      //update_all_views(pupdate);

   }


   void document::OpenFolder(::file::item * pitem, const ::action_context & context)
   {

      browse(pitem, context);

   }


   void document::CreateViews()
   {

      {

         auto psubject = subject(id_initialize);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = subject(id_synchronize_locations);

         psubject->m_actioncontext = ::source_sync;

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

   }


   void document::PopViews()
   {

      {

         auto psubject = fork_subject(id_create_bars);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = subject(id_pop);

         update_all_views(psubject);

      }

   }


   bool document::HandleDefaultFileManagerItemCmdMsg(::user::command * pcommand, ::file::item_array & itema)
   {

      if (pcommand->is_command_probe())
      {

         if (filemanager_data() != nullptr)
         {

            if (filemanager_data()->m_pcallback != nullptr)
            {

               if (filemanager_data()->m_pcallback->get_file_manager_item_callback(filemanager_data(), pcommand->m_id, itema))
               {

                  filemanager_data()->m_pcallback->on_file_manager_item_update(filemanager_data(), pcommand, itema);

                  return true;

               }

            }

         }

      }
      else if (pcommand->is_command())
      {

         if (filemanager_data() != nullptr)
         {

            auto pcallback = filemanager_data()->m_pcallback;

            if (::is_set(pcallback))
            {

               if (pcallback->get_file_manager_item_callback(filemanager_data(), pcommand->m_id, itema))
               {

                  pcallback->on_file_manager_item_command(filemanager_data(), pcommand->m_id, itema);

                  return true;

               }

            }

         }

      }

      return false;

   }


   operation_document * document::get_operation_doc(bool bSwitch)
   {

      //::filemanager::tab_view * ptabview = psession->m_pdocumenttemplateMain->get_document(0)->get_typed_view < ::filemanager::tab_view >();

      //if (ptabview == nullptr)
      //{

      //   return nullptr;

      //}

      //ASSERT(ptabview != nullptr);

      //if (ptabview != nullptr)
      //{

      //   if (bSwitch)
      //   {

      //      ptabview->set_cur_tab_by_id("filemanager::operation");

      //   }
      //   else
      //   {

      //      ptabview->create_tab_by_id("filemanager::operation");

      //   }

      //   return dynamic_cast < operation_document * > (ptabview->get("filemanager::operation")->m_pdocument);

      //}

      return nullptr;

   }


   void document::GetActiveViewSelection(::file::item_array & itema)
   {

      auto psubject = fork_subject(id_get_active_view_selection);

      update_all_views(psubject);

      itema = *psubject->cast < ::file::item_array>(id_selected);

   }


   void document::FileManagerSaveAs(::user::document * pdocument)
   {

      filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_saving;

      {

         auto psubject = fork_subject(id_topic_start);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = subject(id_create_bars);

         update_all_views(psubject);

      }

   }


   void document::FileManagerImport(::user::document * pdocument)
   {

      filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_import;

      {

         auto psubject = fork_subject(id_topic_start);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = subject(id_create_bars);

         update_all_views(psubject);

      }

   }


   void document::FileManagerExport(::user::document * pdocument)
   {

      filemanager_data()->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_export;

      {

         auto psubject = fork_subject(id_topic_start);

         psubject->value(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = subject(id_create_bars);

         update_all_views(psubject);

      }

   }



   void document::on_create(::create * pcreate)
   {

      ::user::document::on_create(pcreate);

      m_pfilemanagerdata = pcreate->cast < ::filemanager::data >("filemanager::data");

      if (m_pfilemanagerdata.is_null())
      {

         auto puser = User;

         m_pfilemanagerdata = puser->filemanager(FILEMANAGER_IMPACT);

      }
      ASSERT(m_pfilemanagerdata.is_set());

      //if (m_pfilemanagerdata.is_null())
      //{

      //   //__pointer(manager_template) ptemplate = pcreate->prop("filemanager::template").cast < manager_template >();

      //   //if (ptemplate.is_null())
      //   //{

      //   //   ptemplate = puser->filemanager().m_ptemplate;

      //   //}

      //   if (ptemplate.is_null())
      //   {

      //      m_pfilemanagerdata = __new(data(get_object()));

      //   }
      //   else
      //   {

      //      m_pfilemanagerdata = ptemplate->create_file_manager_data(pcreate);

      //   }

      //}

      m_pfilemanagerdata->m_pdocument = this;

   }


   void document::on_request(::create * pcreate)
   {

      //::filemanager::callback::on_request(pcreate);

      Application.call_request(pcreate);

   }


   __pointer(::filemanager::data) document::create_file_manager_data(::create * pcreate)
   {

      __pointer(::filemanager::data) pfilemanagerdata(__new(data));

      callback * pcallback = nullptr;

      if (pcreate != nullptr)
      {

         pcallback = pcreate->cast < callback >("department::callback");

      }

      pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : this;

      pfilemanagerdata->m_bTransparentBackground = pcreate == nullptr ? true : pcreate->m_bTransparentBackground;

      pfilemanagerdata->m_bFileSize = true;

      return pfilemanagerdata;

   }


   bool document::on_create_bars(::user::frame_window * pframe)
   {

      string strToolbar;

      strToolbar = filemanager_data()->m_setToolbar[m_emode];

      if(pframe->GetParent() != nullptr)
      {

         ::file::path path = strToolbar;

         strToolbar = path.folder() / ("child_" + string(path.name()));

      }

      if (!pframe->LoadToolBar(FILEMANAGER_IMPACT, strToolbar))
      {

         TRACE("Failed to create filemanager toolbar");

         return false;      // fail to create

      }

      return true;

   }


   void document::handle_file_action(::file::action * paction)
   {

      auto eaction = paction->m_eaction;

      if (eaction == ::file::action_delete
            || eaction == ::file::action_add
            || eaction == ::file::action_modify)
      {

         OnFileManagerBrowse(::source_sync);

      }

   }




} // namespace filemanager



