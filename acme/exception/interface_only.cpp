#include "framework.h"


interface_only_exception::interface_only_exception(const char * pszMessage) :
   not_implemented(pszMessage)
{

}



interface_only_exception::~interface_only_exception()
{

}





CLASS_DECL_ACME void throw_interface_only_exception(const char * psz)
{

   __throw(interface_only_exception(psz));

}






