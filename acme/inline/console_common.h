#pragma once


#include "application_common.h"


int console_end(::estatus estatus)
{

   int iStatus = (int)estatus;

   int iError = 0;

   if (iStatus < 0)
   {

      iError = iStatus;

   }
   else if (iStatus > 1)
   {

      iError = 0;

      //if (System.is_true("show_application_information"))
      //{

      //   printf("return code is %d", iStatus);

      //}

   }

   //System.system_end();

   return iError;

}



