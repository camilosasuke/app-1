#include "framework.h"


CLASS_DECL_AURA void __simple_tracev(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
CLASS_DECL_AURA void __simple_tracea(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);
CLASS_DECL_AURA void __simple_tracev(elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
CLASS_DECL_AURA void __simple_tracea(elemental * pobject, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);




//char os_trace_level_char(e_trace_level elevel)
//{
//
//   switch (elevel)
//   {
//   case level_info:
//      return 'I';
//   case level_warning:
//      return 'W';
//   case level_error:
//      return 'E';
//   default:
//      return 'D';
//   }
//
//}

#ifndef ANDROID

void os_trace(e_trace_level elevel, const char * pszTag, const char * psz)
{

   string strMessage;

   string strTag;

   strTag = strTag.Left(23);

   strTag = string(' ', max(0, 23 - strTag.get_length()));

   strMessage.Format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), psz);

   output_debug_string(strMessage);

}





void simple_debug_print(const char * psz)
{

   os_trace(trace_level_information, "simple_debug_string", psz);

}


#endif



CLASS_DECL_AURA void __tracea(::elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

      return;

   }

   ::get_context_system()->__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}

CLASS_DECL_AURA void __tracef(::elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list list;

   va_start(list, pszFormat);

   try
   {

      __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, list);

   }
   catch (...)
   {

   }

   va_end(list);

}


CLASS_DECL_AURA void __tracev(::elemental * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

      return;

   }

   ::get_context_system()->__tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

}





