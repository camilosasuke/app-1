#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_list_control::simple_list_control()
{

}


simple_list_control::~simple_list_control()
{

}


__pointer(::user::interaction) simple_list_control::OnDrawInterfaceGetWnd()
{

   return this;

}


bool simple_list_control::pre_create_window(::user::create_struct& cs)
{

#ifdef WINDOWS_DESKTOP

   cs.style |= WS_CLIPCHILDREN;

#endif

   return ::user::interaction::pre_create_window(cs);

}


void simple_list_control::set_data(string_array &stra)
{
   
   m_psimplelistdata->set_data(this, stra);

}


void simple_list_control::get_data(string_array &stra)
{

   m_psimplelistdata->get_data(stra);

}


void simple_list_control::pre_subclass_window()
{
   PreSubClassWindow();

   if(!CreateHeaderCtrl())
   {
      return;
   }


   ::user::interaction::pre_subclass_window();


}


bool simple_list_control::remove_item(i32 iItem)
{
   
   if(!m_psimplelistdata->remove_item(iItem))
      return false;

   _001OnUpdateItemCount();

   return true;

}


bool simple_list_control::remove_item(::user::item_range & range)
{
   
   bool bOk = true;
   
   for(::index iItem = range.get_upper_bound(); iItem >= range.get_lower_bound(); iItem++)
   {

      if(!m_psimplelistdata->remove_item(iItem))
      {

         bOk = false;

      }

   }

   _001OnUpdateItemCount();

   return true;

}


bool simple_list_control::remove_item(::user::range & range)
{
   bool bOk = true;
   index_array iaRemove;
   for(::index iRange = 0; iRange < range.get_item_count(); iRange++)
   {
      auto & itemrange = range.ItemAt(iRange);
      for(::index iItem = itemrange.get_lower_bound(); iItem <= itemrange.get_upper_bound(); iItem++)
      {
         iaRemove.add_unique(iItem);
      }
   }
   ::sort::quick_sort(iaRemove, false);
   for(index i = 0; i < iaRemove.get_size(); i++)
   {
      if(!m_psimplelistdata->remove_item(iaRemove[i]))
         bOk = false;
   }
   _001OnUpdateItemCount();
   return bOk;
}


void simple_list_control::install_message_routing(::channel * pchannel)
{
   UNREFERENCED_PARAMETER(pchannel);
   ::user::list::install_message_routing(pchannel);
}

