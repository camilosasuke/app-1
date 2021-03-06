﻿#pragma once


#define _System System
#define _Platform Platform
#define _Application Application
#define _Session Session


CLASS_DECL_APEX bool __initialize(bool bDLL, ::u32 dwVersion);

CLASS_DECL_APEX uptr keycode_to_char(uptr n);

CLASS_DECL_APEX uptr virtualkey_to_char(VirtualKey e);

CLASS_DECL_APEX::user::e_key virtualkey_to_userkey(VirtualKey e, bool& bSpecialKey);

CLASS_DECL_APEX uptr virtualkey_to_code(VirtualKey e);



