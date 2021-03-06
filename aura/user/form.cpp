#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   form::form()
   {

      m_pform = this;

   }


   form::~form()
   {

   }


   bool form::create_control(class control_descriptor * pdescriptor, index iItem)
   {

      return false;

   }


   __pointer(control_descriptor) form::new_form_control()
   {

      return nullptr;

   }


   ::estatus form::open_html(const ::string& str)
   {

      return ::error_interface_only;

   }


   ::estatus form::open_document(const payload& varFile)
   {

      return ::error_interface_only;

   }


   void form::soft_reload()
   {

   }


//   ::form_property_set * form::get_form_property_set()
//   {
//
//      if (::is_set(m_pformpropertyset))
//      {
//
//         return m_pformpropertyset;
//
//      }
//
//      return this;
//
//   }
   ::estatus form::set_form_callback(::user::form_callback* pcallback)
   {

      auto estatus = __refer(m_pcallback, pcallback);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus form::set_parent_form(::user::form* pform)
   {

      auto estatus = __refer(m_pformParent, pform);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   ::user::form_callback* form::get_form_callback()
   {

      return m_pcallback.get();

   }


   ::user::callback* form::get_user_callback()
   {

      return get_form_callback();

   }


   ::user::form * form::get_parent_form()
   {

      return m_pformParent.get();

   }


} // namespace user







