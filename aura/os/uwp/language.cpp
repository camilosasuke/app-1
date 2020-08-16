#include "framework.h"


CLASS_DECL_AURA string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::aura::system::g_p->dir().module() / "po" / (strLang + ".po");

   return file_as_string(path, bOnlyHeader ? 4096 : -1);

}


