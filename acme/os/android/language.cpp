#include "framework.h"


CLASS_DECL_ACME string load_podata(string strLang, bool bOnlyHeader)
{

   ::file::path path = ::dir::module() / "po" / (strLang + ".po");

   return file_as_string(path, bOnlyHeader ? 4096 : -1);

}



