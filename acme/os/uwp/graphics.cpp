﻿#include "framework.h"


bool os_init_imaging()
{

   return true;

}


void os_term_imaging()
{


}





//HCURSOR CreateAlphaCursor(oswindow window, const ::image* pimage, int xHotSpot, int yHotSpot)
//{
//
//   return FALSE;
//
//}


HCURSOR load_default_cursor(e_cursor ecursor)
{

   return nullptr;

}


int_bool delete_hcursor(HCURSOR hcursor)
{

   return TRUE;

}


namespace draw2d
{


   string default_font_name()
   {

      return "Arial";

   }


} // namespace draw2d



