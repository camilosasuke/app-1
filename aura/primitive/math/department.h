﻿#pragma once


CLASS_DECL_AURA void generate_random_bytes(void* p, memsize s);
CLASS_DECL_AURA void transform_alphanumeric(void* p, memsize s);
CLASS_DECL_AURA void generate_random_alphanumeric(void * p, memsize s);

template < typename TYPE >
inline TYPE* __random_bytes(TYPE* p, memsize s);

template < typename TYPE >
TYPE& __random(TYPE& t);

template < typename TYPE >
TYPE __random();


float __random(float f1, float f2);
double __random(double d1, double d2);
i64 __random(i64 i1, i64 i2);
i32 __random(i32 i1, i32 i2);
template < typename INT >
INT __random_int(INT i1, INT i2);


namespace math
{

   struct math_os_data;

   class CLASS_DECL_AURA math :
      virtual public ::aura::department
   {
   private:


      double         dPi;
      float          fPi;
      u32            dwMode;
      BYTE           pbData[16];

   public:


      __composite(math_os_data)  m_posdata;


      math();
      virtual ~math();


      virtual ::estatus initialize(::object * pobjectContext) override;
      virtual void finalize() override;


      i32 LinearMap(i32 iMin, i32 iMax, i32 iValue, i32 iValueMin, i32 iValueMax);
      u64 gen_rand();
      void random_bytes(void * buf, memsize dwLen);
      void RandomBytes(void * buf, memsize dwLen);
      void gen_rand(void * buf, memsize dwLen);

      void gen_rand_alnum(char * buf, memsize dwLen);
      string gen_rand_alnum(strsize s);
      string random_string(strsize s);

      u32 rnd();
      i32 rand_max();

      double LinearMap(double dMin, double dMax, double dValue, double dValueMin, double dValueMax);
      double GetPi();
      float get_pi_f();

      static bool IsPowerOfTwo(u64 uiValue);
      static u32 ReverseBits(u32 index, u32 NumBits);
      static inline void MaxClip(double * pnClipValue, double nMaxValue);
      static inline void MinClip(double * pnClipValue, double nMinValue);

      i32 RangeRate(i32 iMin, i32 iMax, double dRate);


   };


   inline void math::MaxClip(double * pnClipValue, double nMaxValue)
   {

      if (*pnClipValue > nMaxValue)
      {

         *pnClipValue = nMaxValue;

      }

   }


   inline void math::MinClip(double * pnClipValue, double nMinValue)
   {
   
      if (*pnClipValue < nMinValue)
      {

         *pnClipValue = nMinValue;

      }

   }


} // namespace math




template < typename TYPE >
inline TYPE* __random_bytes(TYPE* p, memsize s)
{
   generate_random_bytes(p, s);
   return p;
}


template < typename TYPE >
inline TYPE& __random(TYPE& t)
{

   return *__random_bytes(&t, sizeof(TYPE));

}


template < typename TYPE >
inline TYPE __random()
{

   TYPE t;

   __random(t);

   return t;

}



inline float __random(float f1, float f2)
{

   if (f1 == f2) return f1;

   auto fMin = MIN(f1, f2);

   auto fMax = MAX(f1, f2);

   double dRange = fMax - fMin;

   u64 u;

   __random(u);

   return (float)(((double)u * dRange) / (double)MAXU64) + fMin;

}


inline double __random(double d1, double d2)
{

   if (d1 == d2) return d1;

   auto dMin = MIN(d1, d2);

   auto dMax = MAX(d1, d2);

   auto dRange = dMax - dMin;

   u64 u;

   __random(u);

   return (((double)u * dRange) / (double)MAXU64) + dMin;

}


template < typename INT >
INT __random_int(INT i1, INT i2)
{

   if (i1 == i2) return i1;

   auto iMin = MIN(i1, i2);

   auto iMax = MAX(i1, i2);

   auto iRange = iMax - iMin;

   u64 u;

   __random(u);

   return (INT)((u % ((u64)iRange + 1)) + (i64)iMin);

}


inline i64 __random(i64 i1, i64 i2)
{
   return __random_int(i1, i2);
}


inline i32 __random(i32 i1, i32 i2)
{
   return __random_int(i1, i2);
}



inline i64 __random(i32 i1, i64 i2)
{
   return __random_int((i64) i1, i2);
}


inline i64 __random(i64 i1, i32 i2)
{
   return __random_int(i1, (i64)i2);
}

