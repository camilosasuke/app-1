﻿#pragma once


#undef System
#undef Platform
#undef Application
#undef Session


CLASS_DECL_AXIS bool __initialize(bool bDLL, ::u32 dwVersion);

CLASS_DECL_AXIS uptr keycode_to_char(uptr n);

CLASS_DECL_AXIS uptr virtualkey_to_char(::Windows::System::VirtualKey e);

CLASS_DECL_AXIS::user::e_key virtualkey_to_userkey(::Windows::System::VirtualKey e, bool& bSpecialKey);

CLASS_DECL_AXIS uptr virtualkey_to_code(::Windows::System::VirtualKey e);



