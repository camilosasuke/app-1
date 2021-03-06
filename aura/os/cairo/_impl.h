#pragma once


inline void copy(RECT32 * prectTarget, const cairo_rectangle_int_t * prectSource)
{

   prectTarget->left = prectSource->x;
   prectTarget->top = prectSource->y;
   prectTarget->right = prectSource->x + prectSource->width;
   prectTarget->bottom = prectSource->y + prectSource->height;

}


inline void copy(cairo_rectangle_int_t * prectTarget, const RECT32 * prectSource)
{

   prectTarget->x = prectSource->left;
   prectTarget->y = prectSource->top;
   prectTarget->width = width(prectSource);
   prectTarget->height = height(prectSource);


}



