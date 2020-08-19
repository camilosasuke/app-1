#include "framework.h"
#include "aura/message.h"
#include "aura/update.h"

namespace user
{


   form_window::form_window()
   {

      m_bOnEditUpdate         = false;
      m_bOnLanguageChange     = false;
      m_bInitialized          = false;

   }


   form_window::~form_window()
   {

   }


   index form_window::_001AddControl(class control_descriptor * pdescriptor)
   {

      //index indexNew = m_controldescriptorset.add(new class control_descriptor(descriptorParam));

      m_controldescriptorset.add(pdescriptor);

      ///descriptorParam.clear();

      pdescriptor->m_puserinteractionParent = this;

      if(pdescriptor->m_bTransparent)
      {

         switch(pdescriptor->m_econtroltype)
         {
         case control_type_static:
         {
            /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) window::FromHandlePermanent(pform->get_child_by_id(pcontrol->m_id)->GetSafeoswindow_());
                        if(pstatic == nullptr || !base_class < CTransparentStatic >::bases(pstatic))
                        {
                           pstatic = new CTransparentStatic;
                           VERIFY(pstatic->subclass_window(pform->get_child_by_id(pcontrol->m_id)->GetSafeoswindow_()));
                        }
                        pcontrol->m_unionwndptr.m_pstatic = pstatic;*/
         }
         break;
         default:
            break;

         }
      }

//      if(pdescriptor->m_type)
//      {
//
//         if(pdescriptor->m_bCreated && pdescriptor->m_pcontrol != nullptr)
//         {
//
//            pdescriptor->m_bCreated = false;
//
//            pdescriptor->m_pcontrol.release();
//
//            pdescriptor->m_pcontrol.release();
//
//         }
//
//         if( (pdescriptor->m_pcontrol.m_p) != nullptr)
//         {
//         }
//         else
//         {
//
//            if(create_control(pdescriptor))
//            {
//            }
//            else
//            {
//               // Failed creation
//               ASSERT(FALSE);
//            }
//         }
//
//      }
//      else if(create_control(pdescriptor))
//      {
//      }
//      if(pdescriptor->m_pcontrol != nullptr)
//      {
//         //::type ti = typeid(pdescriptor->m_pcontrol);
///*         if(ti == __type(::user::list))
//         {
//            if(pdescriptor->m_etype == control_type_simple_list)
//            {
//               ::user::list * plist = dynamic_cast <::user::list *>(pdescriptor->m_pcontrol);
//               plist->m_dataid = pdescriptor->m_idPrivateDataSection;
//               plist->_001SetSingleColumnMode(false);
//            }
//         }*/
//         /*else if(ti == __type(simple_static))
//         {
//            simple_static * pstatic = (simple_static *) pcontrol->m_puserinteraction;
//            pstatic->m_bTransparent = pcontrol->m_bTransparent;
//         }*/
//

      //}

      return m_controldescriptorset.get_upper_bound();

   }


   bool form_window::OnCommand(WPARAM wparam, LPARAM lparam)
   {

      UINT uiNotificationCode = HIWORD(wparam);

      ::id id(LOWORD(wparam));

      __pointer(control) pcontrol = m_controldescriptorset.get_control(this, id);

      if(pcontrol == nullptr)
      {

         return false;

      }

      switch(pcontrol->descriptor().get_control_type())
      {
      case control_type_button:
         OnCommandButton(pcontrol, uiNotificationCode, lparam);

         break;
      case control_type_check_box:
         OnCommandCheckBox(pcontrol, uiNotificationCode, lparam);

         break;
      case control_type_combo_box:
         OnCommandComboBox(pcontrol, uiNotificationCode, lparam);

         break;
      case control_type_edit:
         OnCommandEdit(pcontrol, uiNotificationCode, lparam);

         break;
      default:
         break;
      }

      return false;

   }


   bool form_window::OnCommandButton(::user::control * pcontrol, UINT uiNotificationCode, LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pcontrol != nullptr);

      if(pcontrol == nullptr)
         return false;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_button);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         if(pcontrol->descriptor().has_function(control_function_action))
         {
            _001OnButtonAction(pcontrol);
            return true;
         }
      }
      break;
      default:
         break;
      }

#endif

      return false;
   }


   bool form_window::OnCommandCheckBox(::user::control * pcontrol, UINT uiNotificationCode, LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pcontrol != nullptr);

      if(pcontrol == nullptr)
         return false;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_check_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case BN_CLICKED:
      {
         /*      linux   ::user::button * pbutton = (::user::button *) get_child_by_id(pcontrol->m_id);
                  i32 i = pbutton->get_check() != 0;
                  VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, i);*/
      }
      break;
      default:
         break;
      }

#endif

      return false;

   }


   bool form_window::OnCommandComboBox(::user::control * pcontrol, UINT uiNotificationCode, LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pcontrol != nullptr);

      if(pcontrol == nullptr)
         return false;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_combo_box);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case CBN_SELCHANGE:
      {
         /* linux         __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) get_child_by_id(pcontrol->m_id);
                  i32 iSel = pcombo->current_item();
                  if(iSel != CB_ERR)
                  {
                     u32 dwData = pcontrol->GetComboBox()->m_dwaData[iSel];
                     VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, (i32) dwData);
                  }*/
      }
      break;
      case EN_KILLFOCUS:
      {
         //_001SaveEdit(control);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form_window::OnCommandEdit(::user::control * pcontrol, UINT uiNotificationCode, LPARAM lparam)

   {

      UNREFERENCED_PARAMETER(lparam);


      ASSERT(pcontrol != nullptr);

      if(pcontrol == nullptr)
         return false;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_edit);

#ifdef WINDOWS

      switch(uiNotificationCode)
      {
      case EN_CHANGE:
      {
         if(pcontrol->descriptor().has_function(control_function_save_on_change))
         {
            _001SaveEdit(pcontrol);
         }
      }
      break;
      case EN_KILLFOCUS:
      {
         _001SaveEdit(pcontrol);
      }
      default:
         break;
      }

#endif

      return false;

   }


   bool form_window::_001SaveEdit(::user::control * pcontrol)
   {

      if(pcontrol == nullptr)
         return false;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_edit || pcontrol->descriptor().get_control_type() == control_type_edit_plain_text);

      auto pinteraction = get_child_by_id(pcontrol->m_id);

      if(!pinteraction)
      {

         pinteraction = pcontrol;

      }

      if(!pinteraction)
      {

         return false;

      }

      string str;

      pinteraction->_001GetText(str);

      if(!pcontrol->Validate(str))
      {
         // que tal um balão para indicar o erro
         return false;
      }

      var var;

      if(!pcontrol->get_data(pinteraction, var))
      {

         return false;

      }

      if(!_001Validate(pcontrol, var))
      {
         return false;
      }

      if(pcontrol->descriptor().has_function(control_function_vms_data_edit))
      {

         ::database::selection selection;

         _001GetSelection(pcontrol->descriptor().m_datakey, selection);

         auto pupdate = new_update();

         pupdate->set_handled_by(this);

         throw_todo();

         //_data_set(selection, var, &update);

      }

      return true;

   }


   void form_window::update(::update * pupdate)
   {
      UNREFERENCED_PARAMETER(pupdate);
      //for(i32 i = 0; i < m_controldescriptorset.get_size(); i++)
      //{
      //   ::user::control * pcontrol = m_controldescriptorset[i]->m_pcontrol;
      //   if(pcontrol == nullptr)
      //      continue;
      //   _001Update(pcontrol);
      //}
   }

   void form_window::_001Update(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      switch(pcontrol->descriptor().get_control_type())
      {
      case control_type_check_box:
         _001UpdateCheckBox(pcontrol);
         break;
      case control_type_combo_box:
         _001UpdateComboBox(pcontrol);
         break;
      case control_type_edit:
      case control_type_edit_plain_text:
         _001UpdateEdit(pcontrol);
         break;
      case control_type_simple_list:
         _001UpdateSimpleList(pcontrol);
         break;
      default:
         break;
      }
   }

   void form_window::_001UpdateDbFlags(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      switch(pcontrol->descriptor().get_control_type())
      {
      case control_type_check_box:
         _001UpdateDbFlagsCheckBox(pcontrol);
         break;
      /*   case control_type_combo_box:
            _001UpdateComboBox(control);
            break;
         case control_type_edit:
         case control_type_edit_plain_text:
            _001UpdateEdit(control);
            break;
         case control_type_simple_list:
            _001UpdateSimpleList(control);
            break;*/
      default:
         break;
      }
   }

   void form_window::_001UpdateDbFlagsCheckBox(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      ASSERT(pcontrol->descriptor().get_control_type() == control_type_check_box);
      ASSERT(pcontrol->descriptor().m_eddx == control_ddx_dbflags);
      iptr_array ia;
      //try
      //{
      //   pcontrol->data_get(pcontrol->descriptor().m_datakey, ia);

      //}
      //catch(...)
      //{
      //   return;
      //}
      {
         /*         check_box * pcheck = dynamic_cast < check_box * > (pcontrol);
                  if(pcheck != nullptr)
                  {
                     index i = 0;
                     if(ia.BaseSortFind(pcontrol->descriptor().m_ddx.m_pdbflags->m_value, i))
                     {
                        pcheck->_001SetCheck(check_checked, false);
                     }
                     else
                     {
                        pcheck->_001SetCheck(check_unchecked, false);
                     }
                  }*/
      }
   }


   void form_window::_001UpdateCheckBox(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      ASSERT(pcontrol->descriptor().get_control_type() == control_type_check_box);
      //i32 i;
      //if(data_get(pcontrol->descriptor().m_datakey, i))
      //{
      //   /* linux      ::user::button * pbutton = (::user::button *) get_child_by_id(pcontrol->m_id);
      //         pbutton->SetCheck((i != 0) ? 1 : 0); */
      //}
   }

   void form_window::_001UpdateComboBox(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      /* linux   ASSERT(pcontrol->descriptor().get_control_type() == control_type_combo_box);
         i32 i;
         if(VmsDataGet(pcontrol->descriptor().m_dataid, 0, 0, i))
         {
            iptr iSel = pcontrol->GetComboBox()->m_dwaData.find_first((u32) i);
            if(iSel >= 0)
            {
               __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) get_child_by_id(pcontrol->m_id);
               pcombo->set_current_item(iSel);
            }
         }*/
   }

   void form_window::_001UpdateEdit(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;

      __task_guard(m_bOnEditUpdate);

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_edit
             || pcontrol->descriptor().get_control_type() == control_type_edit_plain_text);

      if(pcontrol->descriptor().has_function(control_function_vms_data_edit))
      {

         var var;
         ::database::selection selection;
         _001GetSelection(pcontrol->descriptor().m_datakey, selection);
         if(selection.get_item_count() > 0)
         {

            //::database::selection_item & item = selection.get_item(0);

            auto pinteraction = get_child_by_id(pcontrol->m_id);

            if(!pinteraction)
            {

               pinteraction = pcontrol;

            }

            if(!pinteraction)
            {

               return;

            }

            //if(data_get(pcontrol->descriptor().m_datakey + item.m_datakey, var))
            //{

            //   switch(var.get_type())
            //   {
            //   case ::type_string:
            //   {
            //      string str;
            //      str = var.m_str;
            //      pinteraction->_001SetText(str, ::source_database);
            //   }
            //   break;
            //   case ::type_i32:
            //   {
            //      string str;
            //      str.Format("%d", var.i32());
            //      pinteraction->_001SetText(str, ::source_database);
            //   }
            //   break;
            //   default:
            //      ASSERT(FALSE);
            //      break;
            //   }
            //}
         }
      }
   }

   void form_window::_001UpdateSimpleList(::user::control * pcontrol)
   {
      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;

      ASSERT(pcontrol->descriptor().get_control_type() == control_type_simple_list);

      /*      ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pcontrol->m_id));

            if(typeid(plist->GetDataInterface()) == __type(::user::simple_mesh_data))
            {
               ::user::simple_mesh_data * pdata = dynamic_cast < ::user::simple_mesh_data * > (plist->GetDataInterface());
               string_array stra;
               data_get(pcontrol->descriptor().m_dataid, stra);
               ASSERT(plist != nullptr);
               pdata->set_data(plist, stra);
            }*/
   }

   void form_window::_000OnPosCreate(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
//      SCAST_PTR(::message::base, pbase, pmessage);
   }

   void form_window::_001InitializeFormPreData()
   {
      if(m_pcallback != nullptr)
      {
         m_pcallback->_001InitializeFormPreData(this);
      }

      /*
         if(GetOwner() != nullptr)
         {
            GetOwner()->SendMessage(
               WM_USER + 723,
               GetDlgCtrlId(),
               (LPARAM) this);
         }
      */

   }


   bool form_window::_001GetData(id uiId, bool &bData)
   {

      sync_lock sl(mutex());

      __pointer(control) pcontrol = m_controldescriptorset.get_control(this, uiId);

      if(pcontrol == nullptr)
         return false;

      //i32 i;

      //if(!data_get(pcontrol->descriptor().m_datakey, i))
      //   return false;

//      bData = (i != 0) ? 1 : 0;

      return true;

   }


   bool form_window::_001SetData(id uiId, bool bData)
   {

      __pointer(control) pcontrol = m_controldescriptorset.get_control(this, uiId);

      if(pcontrol == nullptr)
         return false;

      //i32 i = bData ? 1 : 0;
      //data_set(pcontrol->descriptor().m_datakey, i);
      return true;

   }

   void form_window::Update(bool bSave)
   {
      if(bSave)
      {

      }
      else
      {
         //for(i32 i = 0; i < m_controldescriptorset.get_size(); i++)
         //{
         //   __pointer(control) pcontrol = m_controldescriptorset[i]->m_pcontrol;
         //   if(pcontrol == nullptr)
         //      continue;
         //   _001Update(pcontrol);
         //}
      }
   }



   void form_window::_001GetSelection(::database::key & id, ::database::selection &selection)
   {
      selection.add_item(id);
   }


   void form_window::on_command(::user::command * pcommand)
   {

      control::on_command(pcommand);

   }


   void form_window::_001OnNotify(::message::message * pmessage)
   {

#ifdef WINDOWS_DESKTOP

      SCAST_PTR(::message::notify, pnotify, pmessage);

      pnotify->m_bRet = false;

#else

      __throw(todo());

#endif

   }


   void form_window::_001OnMessageNotify(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      // revamp pbase->set_lresult(user::NotifyRetContinue);

      pbase->m_bRet = false;

   }


   bool form_window::_001Validate(::user::control * pcontrol, var & var)
   {

      UNREFERENCED_PARAMETER(pcontrol);
      UNREFERENCED_PARAMETER(var);

      return true;

   }


   void form_window::_001RemoveControls()
   {

      sync_lock sl(mutex());

      m_controldescriptorset.remove_all();

   }


   bool form_window::_001OnBeforeSave(::user::control * pcontrol)
   {

      UNREFERENCED_PARAMETER(pcontrol);

      return true;

   }

   
   void form_window::data_on_after_change(::database::client* pclient, const ::database::key& key, const var& var, ::update* pupdate)
   {

      //SCAST_PTR(::database::change_event, pchange, pmessage);

      sync_lock sl(mutex());

      if(pupdate != nullptr)
      {

         if(pupdate->handled_by(this))
         {

            return;

         }

      }

      for(i32 iControl = 0; iControl < m_controldescriptorset.get_size(); iControl++)
      {

         auto pdescriptor = m_controldescriptorset[iControl];

         if (!pdescriptor)
         {

            continue;

         }

         auto pcontrol = pdescriptor->m_pusercontrol;

         if (!pcontrol)
         {

            continue;

         }

         if(pdescriptor->m_eddx == control_ddx_dbflags)
         {

            _001UpdateDbFlags(pcontrol);

         }
         else if(pdescriptor->m_datakey == key)
         {

            _001Update(pcontrol);

         }

      }

   }


   void form_window::_001UpdateFunctionStatic()
   {

      sync_lock sl(mutex());

      for(i32 i = 0; i < m_controldescriptorset.get_size(); i++)
      {

         class control_descriptor & descriptor = m_controldescriptorset(i);

         if(descriptor.has_function(control_function_static))
         {

            string str;

            str.load_string(get_context_application(), descriptor.m_id);

            descriptor.m_pusercontrol->set_window_text(str);

         }
         else if(descriptor.has_function(control_function_static2))
         {

            string str;

            str.load_string(get_context_application(), descriptor.m_uiText);

            descriptor.m_pusercontrol->set_window_text(str);

         }

      }

   }


   void form_window::WfiOnClose()
   {

      post_message(WM_CLOSE);

   }


   void form_window::_001OnInitializeControl(::user::control * pcontrol)
   {

      if (m_pcallback)
      {

         m_pcallback->_001OnInitializeControl(pcontrol);

      }

      ::user::control_event ev;

      ev.m_puie         = pcontrol;
      ev.m_actioncontext = ::source_database;
      ev.m_eevent       = ::user::event_initialize_control;
      ev.m_uiEvent      = 0;

      on_control_event(&ev);

   }


   void form_window::_001OnButtonAction(::user::control * pcontrol)
   {

      UNREFERENCED_PARAMETER(pcontrol);

   }


   void form_window::_001OnInitializeForm()
   {

      if (m_pcallback)
      {

         m_pcallback->_001OnInitializeForm();

      }

   }


   //void form_window::_001OnInitializeControl(::user::control * pcontrol)
   //{


   //}



   void form_window::_001OnAppLanguage(::message::message * pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      __keep(m_bOnLanguageChange);

      _017OnAppLanguage();

      pbase->m_bRet = false;

   }


   void form_window::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();
      
      if(pmessage->m_bRet)
      {

         return;

      }

   }


   void form_window::_001FillCombo(::user::control * pcontrol)
   {

      ASSERT(pcontrol != nullptr);
      if(pcontrol == nullptr)
         return;
      /* linux  if(pcontrol->GetComboBox() != nullptr)
         {
            if(!pcontrol->GetComboBox()->m_datakeyFill.IsNull())
            {
               pcontrol->GetComboBox()->m_wstra.remove_all();
               pcontrol->GetComboBox()->m_dwaData.remove_all();
               var var;
               var.m_etype = ::type_element;
               var.m_pca2 = pcontrol->GetComboBox();
               VmsDataGet(
                  pcontrol->GetComboBox()->m_datakeyFill,
                  0, 0,
                  var);
               __pointer(::user::combo_box) pcombo = (__pointer(::user::combo_box)) pcontrol->m_puserinteraction;
               pcombo->ResetContent();
               string str;
               for(i32 i = 0; i < pcontrol->GetComboBox()->m_wstra.get_size(); i++)
               {
                  str = pcontrol->GetComboBox()->m_wstra[i];
                  pcombo->AddString(str);
               }

            }
         } */
   }


   void form_window::_017OnAppLanguage()
   {

//      for(i32 i = 0; i < m_controldescriptorset.get_size() ; i++)
//      {
//         class control_descriptor & descriptor = m_controldescriptorset(i);
//         if(descriptor.m_type)
//         {
//            if(descriptor.m_bCreated && descriptor.m_pcontrol != nullptr)
//            {
//            }
//            else if(descriptor.m_bSubclassed && descriptor.m_pcontrol != nullptr)
//            {
//   //            if(::IsWindow(pcontrol->m_puserinteraction->GetSafeoswindow_()))
//               {
//                  //xxx pcontrol->m_puserinteraction->unsubclass_window();
//               }
//   //            ASSERT(pcontrol->m_type->IsDerivedFrom(__type(window)));
//               if(descriptor.m_pcontrol.is_set())
//               {
//                  //window_id wndidTemp = get_child_by_id(pcontrol->m_id)->GetSafeoswindow_();
//                  //if(wndidTemp != nullptr)
//                  {
//             //xxx        VERIFY(pcontrol->m_puserinteraction->subclass_window(wndidTemp));
//                  }
//               }
//            }
//            if(descriptor.m_pcontrol != nullptr)
//            {
////               ::type ti = typeid(descriptor.m_pcontrol);
///*               if(ti == __type(::user::list))
//               {
//                  if(descriptor.m_etype == control_type_simple_list)
//                  {
//                     ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
//                     plist->m_dataid = descriptor.m_idPrivateDataSection;
//                     plist->_001SetSingleColumnMode(false);
//                  }
//               }*/
//   /*            else if(pcontrol->m_type->IsDerivedFrom(__type(simple_static)))
//               {
//                  simple_static * pstatic = (simple_static *) pcontrol->m_puserinteraction;
//                  pstatic->m_bTransparent = pcontrol->m_bTransparent;
//               }*/
//               _001OnInitializeForm(descriptor.m_pcontrol);
//            }
//         }
//      }

   }


   bool form_window::create_control(class control_descriptor * pdescriptor, index iItem)
   {

      if(!normalize_control_descriptor_typeinfo(pdescriptor))
      {

         TRACE("form_window::create_control: failed to create control, could not find proper type for allocation");

         return false;

      }

      auto pinteraction = Application.__id_create <::user::interaction>(pdescriptor->m_type);

      if(!pinteraction)
      {

         TRACE("form_window::create_control: failed to create control, allocation error");

         return false;

      }

      __pointer(class control) pcontrol = pinteraction;

      if(!pcontrol)
      {

         TRACE("form_window::create_control: failed to create control, object is not derived from user::control_descriptor");

         return false;

      }


      if(!pcontrol->create_control(pdescriptor))
      {

         pcontrol.release();

         return false;

      }

      pcontrol->m_iEditItem = iItem;

      _001OnInitializeControl(pcontrol);

      pdescriptor->m_pusercontrol = pcontrol;

      return true;

   }


   void form_window::_001SetControlFactory()
   {

   }


   string form_window::get_path()
   {
      return "";
   }


   bool form_window::open_document(const var & varFile)
   {

      if(!::user::form_control::open_document(varFile))
         return false;

      return true;

   }

   //if (pevent->m_eevent == ::user::event_form_initialize)
   //{

   //   call_sync(get_document()->m_mapRunnablea["load"]);

   //}

   void form_window::on_control_event(::user::control_event * pevent)
   {

      ::user::form_control::on_control_event(pevent);

      if (pevent->m_bRet)
      {

         return;

      }

      if(pevent->m_eevent == ::user::event_tab_key)
      {

         __pointer(::user::primitive) pfocus = pevent->m_puie->keyboard_get_next_focusable();

         if(pfocus != nullptr)
         {

            Session.set_keyboard_focus(pfocus);

         }

      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {

         control * pcontrol = dynamic_cast <control *> (pevent->m_puie);

         if(pcontrol == nullptr)
            return;

         class control_descriptor * pdescriptor = pcontrol->m_pdescriptor;

         if(pdescriptor == nullptr)
            return;

         if(pdescriptor->has_function(control_function_action))
         {

            if(pcontrol != nullptr)
            {

               _001OnButtonAction(pcontrol);

               pevent->m_bRet = true;

            }

            return;

         }

      }
      else if(pevent->m_eevent == ::user::event_set_check && pevent->m_actioncontext.is_user_source())
      {

         control * pcontrol = dynamic_cast <control *> (pevent->m_puie);

         if(pcontrol == nullptr)
            return;

         class control_descriptor * pdescriptor = pcontrol->m_pdescriptor;

         if(pdescriptor == nullptr)
            return;

         if(pdescriptor->m_eddx == control_ddx_dbflags)
         {

            iptr_array ia;

            //pcontrol->data_get(pdescriptor->m_datakey, ia);

            __pointer(check) pcheck = pevent->m_puie;

            if(pcheck->echeck() == ::check_checked)
            {

               ia.add_unique(pdescriptor->m_iDataValue);

            }
            else
            {

               ia.remove(pdescriptor->m_iDataValue);

            }

            //pcontrol->data_get(pdescriptor->m_datakey, ia);

         }

      }

   }


   bool form_window::_001Initialize()
   {

      if(m_bInitialized)
         return true;

      sync_lock sl(mutex());

      _001InitializeFormPreData();

      _001UpdateFunctionStatic();

      for(auto & pdescriptor : m_controldescriptorset.ptra())
      {

         __pointer(control) pcontrol = pdescriptor->m_pusercontrol;

         if (pcontrol == nullptr)
         {

            continue;

         }

         _001Update(pcontrol);

      }

      m_bInitialized = true;

      return true;

   }


   bool form_window::_001IsPointInside(::user::control * pcontrol, point64 point)
   {

      if(pcontrol == nullptr)
      {

         return false;

      }

      return pcontrol->_001IsPointInside(point);

   }


   bool form_window::normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor)
   {

      if(pdescriptor->m_type)
      {

         return true;

      }

      pdescriptor->m_type = Session.user()->controltype_to_typeinfo(pdescriptor->get_control_type());

      if(pdescriptor->m_type)
      {

         return true;

      }

      return false;

   }


   //void form_window::on_before_navigate(var & varFile, u32 nFlags, const char * pszTargetFrameName, byte_array& baPostedData, const char * pszHeaders, bool* pbCancel)

   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nFlags);
   //   UNREFERENCED_PARAMETER(pszTargetFrameName);

   //   UNREFERENCED_PARAMETER(baPostedData);
   //   UNREFERENCED_PARAMETER(pszHeaders);

   //   UNREFERENCED_PARAMETER(pbCancel);

   //}
   //
   
   //::form_property_set * form_window::get_form_property_set()
   //{
   //   
   //   auto pset = form_callback::get_form_property_set();
   //   
   //   if(pset)
   //   {
   //    
   //      return pset;
   //      
   //   }
   //   
   //   pset = form_control::get_form_property_set();
   //   
   //   if(pset)
   //   {
   //      
   //      return pset;
   //      
   //   }
   //   
   //   return nullptr;
   //   
   //}


   void form_window::control_get_window_rect(::user::control * pcontrol, RECT * prect)

   {

      pcontrol->get_window_rect(prect);


   }


   void form_window::control_get_client_rect(::user::control * pcontrol, RECT * prect)
   {

      pcontrol->get_client_rect(prect);

   }

   
   void form_window::install_message_routing(::channel * pchannel)
   {
      ::user::form_control::install_message_routing(pchannel);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &form_window::_001OnCreate);
      IGUI_MSG_LINK(::message_pos_create, pchannel, this, &form_window::_000OnPosCreate);
      MSG_TYPE_LINK(::message::type_language, pchannel, this, &form_window::_001OnAppLanguage);
      //IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &::user::interaction::_001OnKeyDown);
      //IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &::user::interaction::_001OnKeyUp);

   }


} // namespace user


