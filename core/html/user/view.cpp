#include "framework.h"
#include "_user.h"


html_view::html_view()
{

   auto pform = m_pform;

   output_debug_string("html_view::_001OnCreate");

}


html_view::~html_view()
{

}


void html_view::install_message_routing(::channel * pchannel)
{

   html_form::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_destroy, pchannel, this, &html_view::_001OnDestroy);
   MESSAGE_LINK(e_message_create, pchannel, this, &html_view::_001OnCreate);
   MESSAGE_LINK(e_message_context_menu, pchannel, this, &html_view::_001OnContextMenu);
   MESSAGE_LINK(e_message_set_cursor, pchannel, this, &html_view::_001OnSetCursor);

}


void html_view::assert_valid() const
{

   ::user::impact::assert_valid();

}


void html_view::dump(dump_context & dumpcontext) const
{

   ::user::impact::dump(dumpcontext);

}


bool html_view::pre_create_window(::user::create_struct& cs)
{

#ifdef WINDOWS_DESKTOP

   cs.style &= ~WS_EX_CLIENTEDGE;

#endif

   return ::user::impact::pre_create_window(cs);

}


void html_view::_001OnDestroy(::message::message * pmessage)
{

   ::user::impact::_001OnDestroy(pmessage);

}


void html_view::_001OnCreate(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

   auto pform = m_pform;

   output_debug_string("html_view::_001OnCreate");

}


void html_view::_001OnContextMenu(::message::message * pmessage)
{

}


void html_view::_001OnSetCursor(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse, pmouse, pmessage);

   pmouse->m_ecursor = cursor_arrow;

   pmessage->previous();

}


string html_view::GetLocationURL()
{

   return m_strLocationURL;

}


bool html_view::Refresh2(i32 i)
{

   UNREFERENCED_PARAMETER(i);

   get_document()->on_open_document(GetLocationURL());

   return true;

}


bool html_view::Navigate(const char * pszUrl)
{

   if (!get_document()->on_open_document(pszUrl))
   {

      return false;

   }

   m_strLocationURL = pszUrl;

   return true;

}


void html_view::on_document_complete(const char * pszUrl)
{

   UNREFERENCED_PARAMETER(pszUrl);

}


