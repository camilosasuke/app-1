#pragma once


#include "base_file.h"
#include "multithreading.h"


//#ifdef __cplusplus
//#include "aura/os/windows_common/comptr.h"
//#endif


#ifndef _UWP

CLASS_DECL_AURA void WINAPI Sleep(::u32 dwMilliseconds);

#endif

/*#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r,g,b)          ((color32_t)(((byte)(r)|((::u16)((byte)(g))<<8))|(((::u32)(byte)(b))<<16)|(((::u32)(byte)(a))<<24)))*/


//CLASS_DECL_AURA int_bool os_initialize();
//CLASS_DECL_AURA int_bool os_finalize();


//CLASS_DECL_AURA int_bool main_initialize();
//CLASS_DECL_AURA int_bool main_finalize();
//
//
//CLASS_DECL_AURA void set_main_hthread(hthread_t hthread);
//CLASS_DECL_AURA void set_main_ithread(ithread_t ithread);
//
//
//CLASS_DECL_AURA hthread_t get_main_hthread();
//CLASS_DECL_AURA ::u32 get_main_ithread();
//
//CLASS_DECL_AURA oswindow get_focus();
//CLASS_DECL_AURA oswindow set_focus(oswindow oswindow);
//
//CLASS_DECL_AURA oswindow get_window(oswindow oswindow, int iWindow);
//
//CLASS_DECL_AURA void attach_thread_input_to_main_thread(int_bool bAttach);
//

//CLASS_DECL_AURA ::u32 WINAPI WaitForSingleObject( _In_ HANDLE hHandle, _In_ ::u32 dwMilliseconds );




//CLASS_DECL_AURA char* getenv(const char* name);
//CLASS_DECL_AURA HANDLE WINAPI CreateMutex(_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes, _In_ BOOL bInitialOwner, _In_opt_ const char * lpName  );

//CLASS_DECL_AURA HANDLE WINAPI CreateMutexW(    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,    _In_ BOOL bInitialOwner,    _In_opt_ const widechar * lpName    );


//CLASS_DECL_AURA HANDLE create_file(const char * lpcszFileName, ::u32 dwDesiredAcces, ::u32 dwShareMode, LPSECURITY_ATTRIBUTES lpSA, ::u32 dwCreationDisposition, ::u32 dwFlagsAndAttributes, HANDLE hTemplateFile);


