#include "framework.h"





CLASS_DECL_AURA i32 mkint32(u32 ui)
{
   if (ui >= 0x7fffffff)
      throw_cast_overflow();
   return (i32)ui;
}

CLASS_DECL_AURA  i64 mkint64(u64 ull)
{
   if (ull >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (i64)ull;
}


CLASS_DECL_AURA u32 natural32(i32 i)
{
   if (i < 0)
      return 0;
   return (u32)i;
}

CLASS_DECL_AURA  u64 natural64(i64 ll)
{
   if (ll < 0)
      return 0;
   return (u64)ll;
}




