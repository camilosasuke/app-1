//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 14/08/17.
//
//
#pragma once


namespace user
{


   class CLASS_DECL_AURA mouse
   {
   public:


      uptr                    m_nFlags;
      point                   m_point;
      point                   m_pointDesired;
      bool                    m_bTranslated;
      e_cursor                m_ecursor;
      ::draw2d::cursor *      m_pcursor;


      virtual unsigned int get_message()
      {
         return 0;
      }

   };


} // namespace user

