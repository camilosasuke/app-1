﻿#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif
#include "_tree.h"


namespace user
{


   tree_window::tree_window()
   {

   }


   tree_window::~tree_window()
   {

   }


   void tree_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);
      ::user::tree::install_message_routing(pchannel);

   }


} // namespace user


