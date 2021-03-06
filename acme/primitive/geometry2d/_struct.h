#pragma once


struct POINT64
{
   i64    x;
   i64    y;
};


struct SIZE64
{
   i64     cx;
   i64     cy;
};


struct RECT64
{
   i64     left;
   i64     top;
   i64     right;
   i64     bottom;
};


#ifndef WINDOWS_DESKTOP

struct POINTF
{
   float  x;
   float  y;
};

#endif


struct SIZEF
{
   float        cx;
   float        cy;
};


struct RECTF
{
   float  left;
   float  top;
   float  right;
   float  bottom;
};


struct POINTD
{
   double  x;
   double  y;
};


struct SIZED
{
   double        cx;
   double        cy;
};


struct RECTD
{
   double  left;
   double  top;
   double  right;
   double  bottom;
};


struct Q4
{
   double w;
   double x;
   double y;
   double z;
};



