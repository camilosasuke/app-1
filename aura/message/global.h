#pragma once


//#include "ace/_ace.h"


//#ifndef CLASS_DECL_AURA
//
//#define CLASS_DECL_AURA
//
//#endif
//

#ifdef __cplusplus

CLASS_DECL_AURA void c_post_system_event(::u64 u, void * pparam = 0);

#else

CLASS_DECL_AURA void c_post_system_event(i64 iId, void * pparam);

#endif


