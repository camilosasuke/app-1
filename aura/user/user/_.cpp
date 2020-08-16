﻿#include "framework.h"


CLASS_DECL_AURA::estatus message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   ::estatus estatus = ::error_failed;

   auto psystem = ::aura::system::g_p;

   if(psystem)
   {

      psystem->message_box(puiOwner, pszMessage, pszTitle, emessagebox, callback);
      
   }
   
   return estatus;

}


