#include "framework.h"


namespace user
{


   impact::impact()
   {

      m_puiViewNotify = nullptr;

      m_pdocument = nullptr;

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      //IGUI_MSG_LINK(WM_VIEW, pchannel, this, &impact::_001OnView);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pchannel, this, &impact::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pchannel, this, &impact::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &impact::_001OnMouseMove);
      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &impact::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &impact::_001OnDestroy);
      //      IGUI_MSG_LINK(WM_LBUTTONDOWN    , pchannel, this, &impact::_001OnRButtonDown);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, pchannel, this, &impact::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_RBUTTONDOWN, pchannel, this, &impact::_001OnRButtonDown);


      IGUI_MSG_LINK(WM_MOUSEACTIVATE, pchannel, this, &impact::_001OnMouseActivate);
      //      IGUI_MSG_LINK(WM_DESTROY        , pchannel, this, &impact::_001OnDestroy);
      //    IGUI_MSG_LINK(WM_CREATE        , pchannel, this, &impact::_001OnCreate);

      // Standard commands for split pane
      //  //      connect_command(ID_WINDOW_SPLIT , &impact::_001OnSplitCmd);
      //    connect_command_probe(ID_WINDOW_SPLIT ,  &impact::_001OnUpdateSplitCmd);

      // Standard commands for next pane
      //  connect_command_probe(ID_NEXT_PANE    , &impact::_001OnUpdateNextPaneMenu);
      //connect_command(ID_NEXT_PANE   , &impact::_001OnNextPaneCmd);
      //      connect_command_probe(ID_PREV_PANE    , &impact::_001OnUpdateNextPaneMenu);
      //    connect_command(ID_PREV_PANE    , &impact::_001OnNextPaneCmd);

      //}}__MSG_MAP
      // special command for Initial Update


      /* ON_WM_MOUSEACTIVATE()

      // Standard commands for split pane
      ON_COMMAND_EX(ID_WINDOW_SPLIT, &impact::OnSplitCmd)
      ON_UPDATE_::user::command(ID_WINDOW_SPLIT, &impact::OnUpdateSplitCmd)

      // Standard commands for next pane
      ON_UPDATE_::user::command(ID_NEXT_PANE, &impact::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_NEXT_PANE, &impact::OnNextPaneCmd)
      ON_UPDATE_::user::command(ID_PREV_PANE, &impact::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_PREV_PANE, &impact::OnNextPaneCmd)
      //}}__MSG_MAP
      // special command for Initial Update
      ON_MESSAGE_VOID(WM_INITIALUPDATE, impact::OnInitialUpdate) */

   }


   ////////////////////////////////////////////////////////////////////////////
   //
   // ::user::impact second phase construction - bind to ::user::document

   bool impact::pre_create_window(::user::create_struct & cs)
   {

      ASSERT(cs.style & WS_CHILD);

      if (cs.style & WS_BORDER)
      {
#ifdef WINDOWS_DESKTOP
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
#endif
         cs.style &= ~WS_BORDER;
      }

      return TRUE;

   }


   void impact::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pmessagecreate, pmessage);

      if (!(m_ewindowflag & window_flag_window_created))
      {

         // if ok, wire in the current ::user::document
         ASSERT(::user::impact::get_document() == nullptr);

         __pointer(class ::create) pcreate((::create*) pmessagecreate->m_lpcreatestruct->lpCreateParams);


         // A ::user::impact should be created in a given context!
         if (pcreate != nullptr && pcreate->m_pusercreate->m_pdocumentCurrent != nullptr)
         {

            __pointer(::user::document) pdocument = pcreate->m_pusercreate->m_pdocumentCurrent;

            pdocument->add_view(this);

            ASSERT(::user::impact::get_document() != nullptr);

         }
         else
         {
            TRACE(trace_category_appmsg, trace_level_warning, "Warning: Creating a pane with no ::user::document.\n");
         }

         ::user::frame_window* pframe = GetTypedParent < ::user::frame_window >();

         if (pframe != nullptr && pframe->m_pviewMain == nullptr)
         {

            pframe->m_pviewMain = this;

         }

      }

      if(pmessagecreate->previous())
         return;

      {

         ::user::control_event ev;

         ev.m_puie      = this;

         ev.m_eevent    = ::user::event_on_create_impact;

         ev.m_pmessage  = pmessage;

         on_control_event(&ev);

      }

      pmessagecreate->m_lresult = 0;

   }


   void impact::_001OnDestroy(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      __pointer(::user::frame_window) pFrame = GetParentFrame();

      if (pFrame != nullptr && pFrame->GetActiveView() == this)
      {

         pFrame->SetActiveView(nullptr, false);    // deactivate during death

      }

      if (GetTopLevelFrame() != nullptr)
      {

         GetTopLevelFrame()->m_viewptraCommandHandlers.remove(this);

      }

      if (m_pdocument != nullptr)
      {

         m_pdocument->remove_view(this);

      }

      //   ::user::interaction::OnDestroy();
   }


   void impact::PostNcDestroy()
   {

      ::user::interaction::PostNcDestroy();

   }


   ::estatus impact::initialize_view(::user::document * pdocument)
   {

      auto estatus = ::user::box::initialize(pdocument);

      if (!estatus)
      {

         return estatus;

      }

      m_pdocument = pdocument;

      return estatus;

   }


   void impact::CalcWindowRect(RECT * pClientRect, UINT nAdjustType)

   {
      /* trans   ENSURE_ARG(pClientRect != nullptr);

      if (nAdjustType != 0)
      {
      // allow for special client-edge style
      ::AdjustWindowRectEx(pClientRect, 0, FALSE, GetExStyle());


      // default behavior for in-place editing handles scrollbars
      u32 uStyle = GetStyle();
      if (uStyle & WS_VSCROLL)
      {
      i32 nAdjust = afxData.cxVScroll;
      if (uStyle & WS_BORDER)
      nAdjust -= CX_BORDER;
      pClientRect->right += nAdjust;

      }
      if (uStyle & WS_HSCROLL)
      {
      i32 nAdjust = afxData.cyHScroll;
      if (uStyle & WS_BORDER)
      nAdjust -= CY_BORDER;
      pClientRect->bottom += nAdjust;

      }
      return;
      }*/

      // call default to place borders outside of client rect
      ::user::interaction::CalcWindowRect(pClientRect, nAdjustType);

   }

   /////////////////////////////////////////////////////////////////////////////
   // Command routing

   void impact::route_command_message(::user::command * pcommand)
   {

      ::user::box::route_command_message(pcommand);

      if(pcommand->m_bRet)
      {

         return;

      }

      if (::user::impact::get_document() != nullptr)
      {

         ::user::impact::get_document()->route_command_message(pcommand);

         if(pcommand->m_bRet)
         {

            return;

         }

      }

      __pointer(::user::interaction) puiParent = GetParent();

      while (puiParent.is_set() && puiParent->is_place_holder())
      {

         puiParent = puiParent->get_parent();

      }

      if (puiParent.is_set() && !puiParent->is_frame_window())
      {

         puiParent->route_command_message(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

      Application.route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }


   //void impact::update(::update * pupdate)
   //{

   //   //call_update(INITIAL_UPDATE);        // initial update

   //}


   //void impact::update(::update * pupdate)
   //{

   //   ::user::box::update(pupdate);

   //   //if (pHint != nullptr)
   //   //{
   //   //   if (base_class < ::update > ::bases(pHint))
   //   //   {
   //   //      ::update * pupdate = dynamic_cast < ::update * > (pHint);
   //   //      OnViewUpdateHint(pSender, lHint, pupdate);
   //   //   }
   //   //}

   //   //if(pupdate->m_id == id_set_edit_file)
   //   //{

   //   //   post_simple_command(simple_command_set_edit_file, pobject);

   //   //}

   //   //if (lHint> update_begin && lHint < update_end)
   //   //{
   //   //   on_simple_view_update_hint(pSender, (e_hint)lHint, pHint);
   //   //}
   //   //ASSERT(pimpact != this);
   //   //UNUSED(pSender);     // unused in release builds

   //   // invalidate the entire pane, erase background too
   //   //Invalidate(TRUE);

   //   //Application.on_update_view(this,pSender,lHint,pHint);

   //}

   //void impact::on_simple_view_update_hint(__pointer(::user::impact) pviewSender, e_hint ehint, object * pupdate)
   //{

   //   switch (ehint)
   //   {
   //      break;
   //   default:
   //      break;
   //   };

   //}

   //void impact::OnViewUpdateHint(__pointer(::user::impact) pSender, LPARAM lHint, ::update * pHint)
   //{
   //   UNREFERENCED_PARAMETER(pimpact);
   //   UNREFERENCED_PARAMETER(eupdate);
   //   UNREFERENCED_PARAMETER(pHint);
   //}


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact selection support

   bool impact::IsSelected(const object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
      //  UNUSED(pDocItem);    // unused in release builds

      return FALSE;   // not implemented, so not selected
   }

   void impact::OnActivateView(bool bActivate, __pointer(::user::impact) pActivateView, __pointer(::user::impact))
   {
      //    UNUSED(pActivateView);   // unused in release builds

      if (bActivate)
      {
         //ASSERT(pActivateView == this);

         // take the focus if this frame/::user::impact/pane is now active
         if (IsTopParentActive())
            SetFocus();
      }
   }

   void impact::OnActivateFrame(UINT /*nState*/, __pointer(::user::frame_window) /*pFrameWnd*/)
   {
   }

   /* trans
   i32 impact::OnMouseActivate(::user::interaction_impl * pDesktopWnd, UINT nHitTest, UINT message)
   {
   i32 nResult = ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
   return nResult;   // frame does not want to activate

   __pointer(::user::frame_window) pParentFrame = GetParentFrame();
   if (pParentFrame != nullptr)
   {
   // eat it if this will cause activation
   ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

   // either re-activate the current ::user::impact, or set this ::user::impact to be active
   __pointer(::user::impact) pview = pParentFrame->GetActiveView();
   oswindow oswindow_Focus = ::GetFocus();
   if (pview == this &&
   get_handle() != oswindow_Focus && !::IsChild(get_handle(), oswindow_Focus))
   {
   // re-activate this ::user::impact
   OnActivateView(TRUE, this, this);
   }
   else
   {
   // activate this ::user::impact
   pParentFrame->SetActiveView(this);
   }
   }
   return nResult;
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact scrolling support

   bool impact::OnScroll(UINT /*nScrollCode*/, UINT /*nPos*/, bool /*bDoScroll*/)
   {
      return FALSE;
   }

   //bool impact::OnScrollBy(size /*sizeScroll*/, bool /*bDoScroll*/)
   //{
   //   return FALSE;
   //}

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact drag/drop support

   ///*DROPEFFECT impact::OnDragScroll(u32 /*dwKeyState*/, point /*point*/)
   //{
   //#ifndef ___NO_OLE_SUPPORT
   // return DROPEFFECT_SCROLL; // this means do the default
   //#else
   // return 0;
   //#endif
   //}

   //DROPEFFECT impact::OnDragEnter(COleDataObject* /*pDataObject*/,
   // u32 /*dwKeyState*/, point /*point*/)
   //{
   // return 0;   // DROPEFFECT_NONE
   //}

   //DROPEFFECT impact::OnDragOver(COleDataObject* /*pDataObject*/,
   //u32 /*dwKeyState*/, point /*point*/)
   //{
   //return 0;   // DROPEFFECT_NONE
   //}

   //bool impact::OnDrop(COleDataObject* /*pDataObject*/,
   //DROPEFFECT /*dropEffect*/, point /*point*/)
   //{
   // return FALSE;
   //}

   //DROPEFFECT impact::OnDropEx(COleDataObject* /*pDataObject*/,
   // DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, point /*point*/)
   //{
   // return (DROPEFFECT)-1;  // not implemented
   //}

   //void impact::OnDragLeave()
   //{
   //}

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact splitting commands


   /*   CScrollBar* impact::GetScrollBarCtrl(i32 nBar) const
      {

         ///ASSERT(nBar == SB_HORZ || nBar == SB_VERT);
         // trans   if (GetStyle() & ((nBar == SB_HORZ) ? WS_HSCROLL : WS_VSCROLL))
         //   {
         // it has a regular windows style scrollbar (no control)
         //      return nullptr;
         //   }


         return nullptr;
      }*/

   
   void impact::set_impact_title(const string& strImpactTitle)
   {

      m_strImpactTitle = strImpactTitle;

   }


   string impact::get_impact_title() const
   {

      return m_strImpactTitle;

   }


   void impact::OnUpdateSplitCmd(::user::command* pCmdUI)
   {
      UNREFERENCED_PARAMETER(pCmdUI);
      /*ENSURE_ARG(pCmdUI != nullptr);
      CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      pCmdUI->Enable(pSplitter != nullptr && !pSplitter->IsTracking());*/
   }

   bool impact::OnSplitCmd(UINT)
   {
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      if (pSplitter == nullptr)
      return FALSE;

      ASSERT(!pSplitter->IsTracking());
      pSplitter->DoKeyboardSplit();*/
      return TRUE;    // attempted at least
   }

   void impact::OnUpdateNextPaneMenu(::user::command* pCmdUI)
   {
      UNREFERENCED_PARAMETER(pCmdUI);
      /*ASSERT(pCmdUI->m_nID == ID_NEXT_PANE ||
      pCmdUI->m_nID == ID_PREV_PANE);
      CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      pCmdUI->Enable(pSplitter != nullptr &&
      pSplitter->CanActivateNext(pCmdUI->m_nID == ID_PREV_PANE));*/
   }

   bool impact::OnNextPaneCmd(UINT nID)
   {
      UNREFERENCED_PARAMETER(nID);
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, FALSE);
      if (pSplitter == nullptr)
      return FALSE;

      ASSERT(nID == ID_NEXT_PANE || nID == ID_PREV_PANE);
      pSplitter->ActivateNext(nID == ID_PREV_PANE);*/
      return TRUE;
   }

   ///////////////////////////////////////////////////////////////////////////////
   //// Printing support virtual functions (others in viewpr.cpp)

   //void impact::OnPrepareDC(::draw2d::graphics_pointer & pgraphics, CPrintInfo* pInfo)
   //{
   //   UNREFERENCED_PARAMETER(pInfo);
   //   ASSERT_VALID(pgraphics);
   //   UNUSED(pgraphics); // unused in release builds

   //   // Default to one page printing if doc length not known
   //}




   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact diagnostics

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::interaction::dump(dumpcontext);

      if (((impact *) this)->::user::impact::get_document() != nullptr)
         dumpcontext << "with ::user::document: ";
      else
         dumpcontext << "with no ::user::document\n";
   }

   void impact::assert_valid() const
   {
      ::user::interaction::assert_valid();
   }


   //void impact::update(::update * pupdate)
   //{

   //   SCAST_PTR(::message::base, pbase, pmessage);

   //   //if (pbase->m_wparam == ::user::impact_message_update)
   //   //{

   //   //   ::user::document::update * pupdate = (::user::document::update *) pbase->m_lparam.m_lparam;

   //   //   on_update(pupdate->m_pSender, pupdate->m_lHint, pupdate->m_pHint);

   //   //}
   //   if (pbase->m_wparam == ::user::impact_message_close_document)
   //   {

   //      get_document()->close_document();

   //   }

   //}


   __pointer(::user::interaction) impact::create_view(::user::interaction * pimpactAlloc, ::user::impact_data * pimpactdata, ::user::interaction * pviewLast)
   {

      __pointer(::create) pcreate(e_create);

      pcreate->m_pusercreate = __new(::user::create);

      pcreate->m_pusercreate->m_puiNew = pimpactAlloc;

      pcreate->m_pusercreate->m_puiLastView = pviewLast;

      pcreate->m_pusercreate->m_pdocumentCurrent = get_document();

      return ::user::create_view(pcreate, pimpactdata->m_pplaceholder, pimpactdata->m_id);

   }


   __pointer(::user::interaction) impact::create_view(const ::type & type, ::user::document * pdocument, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast, ::user::impact_data * pimpactdata)
   {

      __pointer(::create) pcreate(e_create);

      auto estatus = __construct_new(pcreate->m_pusercreate);

      if (!estatus)
      {

         return nullptr;

      }

      if (::is_set(pimpactdata))
      {

         pcreate->m_pusercreate->m_pimpactdata = pimpactdata;

      }

      pcreate->m_pusercreate->m_typeNewView = type;

      pcreate->m_pusercreate->m_puiLastView = pviewLast;

      if (pdocument == nullptr)
      {

         pcreate->m_pusercreate->m_pdocumentCurrent = get_document();

      }
      else
      {

         pcreate->m_pusercreate->m_pdocumentCurrent = pdocument;

      }

      if (pwndParent == nullptr)
      {

         pwndParent = this;

      }

      if (id.is_empty())
      {

         id = (const ::id &) pcreate->m_pusercreate->m_typeNewView.name();

      }

      return ::user::create_view(pcreate, pwndParent, id);

   }


   __pointer(::user::interaction) create_view(const ::type & type, ::user::document * pdocument, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast)
   {

      __pointer(::create) pcreate(e_create_new, pdocument);

      pcreate->m_pusercreate = __new(::user::create);

      pcreate->m_pusercreate->m_typeNewView = type;

      pcreate->m_pusercreate->m_puiLastView = pviewLast;

      pcreate->m_pusercreate->m_pdocumentCurrent = pdocument;

      return ::user::create_view(pcreate, pwndParent, id);

   }


   __pointer(::user::interaction) create_view(::create * pcreate, ::user::interaction * pwndParent, id id)
   {

      ASSERT(pcreate != nullptr);

      ASSERT(pcreate->m_pusercreate->m_typeNewView || pcreate->m_pusercreate->m_puiNew != nullptr);

      ::aura::application * papp = pwndParent->get_context_application();

      __pointer(::user::interaction) pinteraction;

      ::estatus estatus = ::success;

      if (pcreate->m_pusercreate->m_puiNew != nullptr)
      {

         pinteraction = pcreate->m_pusercreate->m_puiNew;

      }
      else
      {

         __pointer(::object) pobject = pcreate->m_pusercreate->m_pdocumentCurrent;

         if(pobject.is_null())
         {

            pobject = papp;

         }

         if (pobject.is_null() || ::is_null(pobject->get_context_application()))
         {

            return nullptr;

         }

         estatus = pobject->__id_construct(pinteraction, pcreate->m_pusercreate->m_typeNewView);

      }

      if (pinteraction.is_null())
      {

         return nullptr;

      }

      if (!pinteraction->create_window(nullptr, nullptr, WS_VISIBLE | WS_CHILD, pwndParent, id, pcreate))
      {

         return nullptr;

      }

      __pointer(::user::impact) pview = pinteraction;

      if (pview.is_set())
      {

         pview->call_update(INITIAL_UPDATE);

      }

      if (pinteraction.is_set())
      {

         if (pinteraction->GetParent() != nullptr)
         {

            if (pinteraction->GetParent()->is_place_holder())
            {

               pinteraction->GetParent()->place_hold(pinteraction);

            }

         }

      }

      return pinteraction;

   }


   void impact::_001OnLButtonDown(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      pmessage->previous();

      if (GetParentFrame() != nullptr)
      {

         GetParentFrame()->SetActiveView(this);

      }

   }

   void impact::_001OnLButtonUp(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::mouse, pmouse, pmessage);
   }

   void impact::_001OnMouseMove(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //   SCAST_PTR(::message::mouse, pmouse, pmessage);
   }


   ::user::document * impact::get_document() const
   {

      ASSERT(::is_set(this));
      return ((::user::impact *) this)->m_pdocument;

   }


   void impact::collaborate(::job * pjob)
   {
      {
         ::user::job * puserjob = (dynamic_cast < ::user::job * > (pjob));
         if (puserjob != nullptr)
         {
            puserjob->m_puserinteraction = this;
         }
      }
   }



   i32 impact::get_total_page_count(::job * pjob)
   {
      UNREFERENCED_PARAMETER(pjob);
      return 1;
   }


   ::user::interaction::e_type impact::get_window_type()
   {
      return type_view;
   }


   //void impact::on_draw_view_nc(::image * pimage)
   //{

   //   UNREFERENCED_PARAMETER(pgraphics);

   //}

   //void impact::on_draw_view(::draw2d::graphics_pointer & pgraphics, __pointer_array(::data::data) spadata)
   //{

   //   UNREFERENCED_PARAMETER(pgraphics);
   //   UNREFERENCED_PARAMETER(spadata);

   //}

   //void impact::defer_draw_view(::image * pimage)
   //{

   //   if (get_document() == nullptr)
   //      return;

   //   __pointer_array(::data::data) spadata = get_document()->m_dataa;

   //   //spadata.add(get_document()->m_spdata);

   //   object_spa sync;

   //   for (index i = 0; i < spadata.get_count(); i++)
   //   {

   //      sync.add(spadata[i].data_mutex());

   //   }

   //   retry_multi_lock sl(sync, millis(1), millis(1));

   //   try
   //   {
   //      on_draw_view(pgraphics, spadata);
   //   }
   //   catch (...)
   //   {
   //   }

   //}

   //void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   on_draw_view_nc(pgraphics);

   //   i32 iTry = 0;

   //   bool bOk;

   //retry:

   //   bOk = true;

   //   try
   //   {
   //      defer_draw_view(pgraphics);
   //   }
   //   catch (...)
   //   {
   //      bOk = false;
   //   }

   //   iTry++;
   //   if (!bOk && iTry < 9)
   //      goto retry;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact second phase construction - bind to document

   //const CHAR _vfxWndFrameOrView[] = __WNDFRAMEORVIEW;




   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact drawing support


   /*void impact::update(::update * pupdate)
   {
   call_update(INITIAL_UPDATE);        // initial update
   }*/

   /*   void impact::on_update(::user::impact * pSender, LPARAM lHint, object * pHint)
   {
   ::user::impact::update(pupdate);
   }
   */
   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact selection support

   /*   bool impact::IsSelected(const object* pDocItem) const
   {
   ASSERT_VALID(pDocItem);
   //      UNUSED(pDocItem);    // unused in release builds

   return FALSE;   // not implemented, so not selected
   }*/


   void impact::_001OnMouseActivate(::message::message * pmessage)
   {
      SCAST_PTR(::message::mouse_activate, pmouseactivate, pmessage);
      pmessage->previous();
      //i32 nResult = pmouseactivate->get_lresult();

      if (pmouseactivate->get_message() == MA_NOACTIVATE
            || pmouseactivate->get_message() == MA_NOACTIVATEANDEAT)
      {
         
         pmouseactivate->m_lresult = pmouseactivate->get_message(); // frame does not want to activate

         pmouseactivate->m_bRet = true;

      }

      __pointer(::user::frame_window) pParentFrame = (GetParentFrame());
      if (pParentFrame != nullptr)
      {
         // eat it if this will cause activation
         ASSERT(pParentFrame == pmouseactivate->get_desktop_window()
                || pmouseactivate->get_desktop_window()->is_child(pParentFrame));

         // either re-activate the current ::user::impact, or set this ::user::impact to be active
         __pointer(::user::impact) pview = pParentFrame->GetActiveView();
         __pointer(::user::interaction) oswindow_Focus = Session.get_focus_ui();
         if (pview == this &&
               this != oswindow_Focus && !is_child(oswindow_Focus))
         {
            // re-activate this ::user::impact
            OnActivateView(TRUE, this, this);
         }
         else
         {
            // activate this ::user::impact
            pParentFrame->SetActiveView(this);
         }
      }

      pmouseactivate->m_lresult = pmouseactivate->get_message();

      pmouseactivate->m_bRet = true;

   }


   void impact::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::box::_001CallOnDraw(pgraphics);
      //on_viewport_offset(pgraphics);

      //sync_lock slView(mutex());

      ////sync_lock slDocument(get_document()->mutex());.

      //{

      //   draw_select ds(this, pgraphics);

      //   _001OnDraw(pgraphics);

      //}

   }


   void impact::on_select()
   {
      __pointer(::user::frame_window) pParentFrame = (GetParentFrame());
      if (pParentFrame != nullptr)
      {
         // eat it if this will cause activation
         /*      ASSERT(pParentFrame == pmouseactivate->get_desktop_window()
         || pmouseactivate->get_desktop_window()->IsChild(pParentFrame));*/

         // either re-activate the current ::user::impact, or set this ::user::impact to be active
         __pointer(::user::impact) pview = pParentFrame->GetActiveView();
         __pointer(::user::interaction) oswindow_Focus = Session.get_focus_ui();
         if (pview == this &&
               this != oswindow_Focus && !is_child(oswindow_Focus))
         {
            // re-activate this ::user::impact
            OnActivateView(TRUE, this, this);
         }
         else
         {
            // activate this ::user::impact
            pParentFrame->SetActiveView(this);
         }
      }
   }


//#ifndef ANDROID
//
//   /////////////////////////////////////////////////////////////////////////////
//   // ::user::impact drag/drop support
//
//   DROPEFFECT impact::OnDragScroll(u32 /*dwKeyState*/, point /*point*/)
//   {
//#if !defined(___NO_OLE_SUPPORT) && !defined(_UWP) && !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID) && !defined(SOLARIS)
//      return DROPEFFECT_SCROLL; // this means do the default
//#else
//      return 0;
//#endif
//   }
//
//   DROPEFFECT impact::OnDragEnter(COleDataObject* /*pDataObject*/,
//      u32 /*dwKeyState*/, point /*point*/)
//   {
//      return 0;   // DROPEFFECT_NONE
//   }
//
//   DROPEFFECT impact::OnDragOver(COleDataObject* /*pDataObject*/,
//      u32 /*dwKeyState*/, point /*point*/)
//   {
//      return 0;   // DROPEFFECT_NONE
//   }
//
//   bool impact::OnDrop(COleDataObject* /*pDataObject*/,
//      DROPEFFECT /*dropEffect*/, point /*point*/)
//   {
//      return FALSE;
//   }
//
//   DROPEFFECT impact::OnDropEx(COleDataObject* /*pDataObject*/,
//      DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, point /*point*/)
//   {
//      return (DROPEFFECT)-1;  // not implemented
//   }
//
//   void impact::OnDragLeave()
//   {
//   }
//
//
//#endif // ANDROID




   void impact::_001OnUpdateSplitCmd(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnSplitCmd(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnUpdateNextPaneMenu(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnNextPaneCmd(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


   // // IMPLEMENT_DYNAMIC for ::user::impact is in wincore.cpp for .OBJ granularity reasons

   //// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for __swap tuning
   //// IMPLEMENT_DYNAMIC(CCtrlView, ::user::impact)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact's OnPrintPreview.  Here to force linkage

   void impact::_001OnFilePrintPreview(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }


   void impact::_001OnFilePrint(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
   }



   /*
   __pointer(::user::interaction) impact::CreateView(__pointer(::create) pContext, UINT nID)
   {
   ASSERT(is_window());
   ASSERT(pContext != nullptr);
   ASSERT(pContext->m_typeNewView != nullptr);

   // Note: can be a ::user::interaction with PostNcDestroy self cleanup
   __pointer(::user::interaction) pview =  (System.alloc(pContext->m_typeNewView));
   if (pview == nullptr)
   {
   TRACE1("Warning: Dynamic create of ::user::impact type %hs failed.\n",
   pContext->m_typeNewView.name());
   return nullptr;
   }
   ASSERT_KINDOF(::user::interaction, pview);

   // views are always created with a border!
   if (!pview->create(nullptr, nullptr, __WS_DEFAULT_VIEW,
   rect(0,0,0,0), this, nID, (__pointer(::create)) pContext))
   {
   TRACE0("Warning: could not create ::user::impact for frame.\n");
   return nullptr;        // can't continue without a ::user::impact
   }

   __pointer(::user::impact) pview =  (pview);
   pview->update(::update * pupdate);
   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // remove the 3d style from the frame, since the ::user::impact is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   /*   return pview;
   }*/


   /*__pointer(::user::interaction) impact::CreateView(__pointer(::create) pContext, UINT nID, ::user::interaction  * pwndParent)
   {
   ASSERT(pwndParent->is_window());
   ASSERT(pContext != nullptr);
   ASSERT(pContext->m_typeNewView != nullptr);

   // Note: can be a interaction_impl with PostNcDestroy self cleanup
   ::user::interaction_impl * pview = (pwndParent->System.alloc(pContext->m_typeNewView));
   if (pview == nullptr)
   {
   TRACE1("Warning: Dynamic create of ::user::impact type %hs failed.\n",
   pContext->m_typeNewView.name());
   return nullptr;
   }
   ASSERT_KINDOF(interaction_impl, pview);

   // views are always created with a border!
   if (!pview->create(nullptr, nullptr, __WS_DEFAULT_VIEW,
   rect(0,0,0,0), pwndParent, nID, (__pointer(::create)) pContext))
   {
   TRACE0("Warning: could not create ::user::impact for frame.\n");
   return nullptr;        // can't continue without a ::user::impact
   }

   ( (pview))->update(::update * pupdate);
   if (afxData.bWin4 && (pview->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // remove the 3d style from the frame, since the ::user::impact is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   //   return pview;
   //}


   void impact::_001OnRButtonDown(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //SCAST_PTR(::message::mouse, pmouse, pmessage);

      GetParentFrame()->SetActiveView((this));
   }

   void impact::_001OnMButtonDown(::message::message * pmessage)
   {
      UNREFERENCED_PARAMETER(pmessage);
      //      SCAST_PTR(::message::mouse, pmouse, pmessage);

      GetParentFrame()->SetActiveView((this));
   }


   bool impact::has_command_handler(::user::command * pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

      if (get_document() != nullptr)
      {

         if (get_document()->has_command_handler(pcommand))
         {

            return true;

         }

      }

      if (get_parent() != nullptr)
      {

         if (get_parent()->has_command_handler(pcommand))
         {

            return true;

         }

      }

      return false;

   }


   void impact::walk_pre_translate_tree(::message::message * pmessage,__pointer(::user::interaction) puiStop)
   {


      try
      {

         GetParentFrame()->pre_translate_message(pmessage);

      }
      catch(...)
      {

      }

      if(pmessage->m_bRet)
         return;

      pre_translate_message(pmessage);

   }


   //string impact::calc_parent_data_key()
   //{

   //   return get_document()->calc_data_key();

   //}


   //bool impact::is_local_data()
   //{

   //   if(::user::box::is_local_data())
   //   {

   //      return true;

   //   }

   //   if(get_document() != nullptr && get_document()->is_local_data())
   //   {

   //      return true;

   //   }

   //   return false;

   //}
/*

   ::user::document * get_document(::user::interaction * pinteraction)
   {

      __pointer(::user::impact) pview = pinteraction;

      if (pview != nullptr)
      {

         return nullptr;

      }

      return pview->get_document();

   }
*/

} // namespace user


