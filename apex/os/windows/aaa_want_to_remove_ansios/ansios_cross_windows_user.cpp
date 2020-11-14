#include "framework.h"


char char_to_upper(int32_t ch);


int_bool MessageBoxAForConsole(oswindow interaction_impl, const char * psz, const char * pszTitle, ::u32 uFlags);


//int_bool (* g_messageboxa)(oswindow interaction_impl, const char * psz, const char * pszTitle, ::u32 uFlags) = MessageBoxAForConsole;



int_bool MessageBoxAForConsole(oswindow interaction_impl, const char * psz, const char * pszTitle, ::u32 uFlags)
{

   string strLine;


   strLine = "\n";

   if(strlen(pszTitle) > 0)
   {

      strLine += pszTitle;

      strLine += " : ";

   }

   strLine += psz;

   int iDefaultButton = IDOK;


   string str;

   if((uFlags & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {
      str += "y/n/c";
   }
   else if((uFlags & MB_YESNO) == MB_YESNO)
   {
      str += "y/n";
   }

   bool bDefault = false;

   if((uFlags & MB_DEFBUTTON1) == MB_DEFBUTTON1 && str.get_length() >= 1)
   {
      str.set_at(0, char_to_upper(str[0]));
      iDefaultButton = IDYES;
      bDefault = true;
   }
   else if((uFlags & MB_DEFBUTTON2) == MB_DEFBUTTON2 && str.get_length() >= 3)
   {
      str.set_at(2, char_to_upper(str[2]));
      iDefaultButton = IDNO;
      bDefault = true;
   }
   else if((uFlags & MB_DEFBUTTON3) == MB_DEFBUTTON3 && str.get_length() >= 5)
   {
      str.set_at(4, char_to_upper(str[4]));
      iDefaultButton = IDCANCEL;
      bDefault = true;
   }

   if(str.has_char())
   {

      strLine += " : (" + str + ") ? ";

   }
   else
   {

      strLine += " : (OK) ";

   }

   int iRet = iDefaultButton;

   bool bAnswer = false;

repeat:

   if(uFlags & MB_ICONEXCLAMATION || uFlags & MB_ICONSTOP)
   {

      fputs(strLine, stderr);

   }
   else
   {

      fputs(strLine, stdout);

   }

   if((uFlags & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {

      int c = getc(stdin);

      switch(c)
      {
      case 'y':
      case 'Y':
         iRet = IDYES;
         bAnswer = true;
         break;
      case 'n':
      case 'N':
         iRet = IDNO;
         bAnswer = true;
         break;
      case 'c':
      case 'C':
         iRet = IDCANCEL;
         bAnswer = true;
         break;
      default:
         bAnswer = bDefault;
         break;

      }

   }
   else if((uFlags & MB_YESNO) == MB_YESNO)
   {

      int c = getc(stdin);

      switch(c)
      {
      case 'y':
      case 'Y':
         iRet = IDYES;
         bAnswer = true;
         break;
      case 'n':
      case 'N':
         iRet = IDNO;
         bAnswer = true;
         break;
      default:
         bAnswer = bDefault;
         break;
      }

   }
   else
   {

      getc(stdin);

   }


   if(!bAnswer)
      goto repeat;


   return iRet;

}

