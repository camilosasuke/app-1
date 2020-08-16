/*
 Copyright (ca) 2001
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 14:47:20
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/

#pragma once

#ifdef WINDOWS
#include <eh.h>
#endif


#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
#define EXCEPTION_TRANSLATOR_USE_SIGNAL
#endif


extern CLASS_DECL_AURA bool g_bExiting;


namespace exception
{


   class CLASS_DECL_AURA translator :
      virtual public context_object
   {
   public:

#ifdef EXCEPTION_TRANSLATOR_USE_SIGNAL

      void *      m_psig;

#endif

      translator();
      virtual ~translator();

#ifdef WINDOWS
      void filter(u32 uiCode, _EXCEPTION_POINTERS * point);
      static void __cdecl filter2(u32 uiCode, _EXCEPTION_POINTERS * point);
      //void filter( _EXCEPTION_POINTERS * point);
#endif

      static string name(u32 uiCode);
      static string description(u32 uiCode);


      bool attach();
      bool detach();



   private:
      bool                      m_bSet;
      //LPTOP_LEVEL_EXCEPTION_FILTER m_pfn;
#ifdef WINDOWS
      _se_translator_function   m_pfn;
#endif
   };


} // namespace exception

