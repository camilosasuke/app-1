#include "framework.h"
#include "acme/os/console.h"
#include "console.h"


namespace graphics
{

   int next_char(char & ch, const char * & psz, int & x, int & y, int cx, int cy)
   {

      if (!*psz)
      {

         return 0;

      }

      int iAdvance = 0;

      if (*psz == '\n')
      {

         psz++;

         iAdvance++;

         if (*psz == '\r')
         {

            psz++;

            iAdvance++;

         }

         y++;

         x = 0;

      }
      else if (*psz == '\r')
      {

         psz++;

         iAdvance++;

         if (*psz == '\n')
         {

            psz++;

            iAdvance++;

         }

         y++;

         x = 0;

      }
      else
      {

         x++;

      }

      if (y >= cy)
      {

         return false;

      }

      ch = *psz;

      psz++;

      iAdvance++;

      return iAdvance;

   }


   color32_t console::console_COLORREF(int iColor)
   {
      switch (iColor)
      {
      case ::console::WHITE:
         return ARGB(255, 255, 255, 255);
      case ::console::BLUE:
         return ARGB(255, 127, 127, 255);
      case ::console::DARKBLUE:
         return ARGB(255, 0, 0, 255);
      case ::console::RED:
         return ARGB(255, 255, 0, 0);
      case ::console::CYAN:
         return ARGB(255, 0, 255, 255);
      case ::console::MAGENTA:
         return ARGB(255, 255, 0, 255);
      case ::console::YELLOW:
         return ARGB(255, 255, 255, 0);
      }
      return ARGB(255, 0, 0, 0);
   }


   console::console(size sizeTile) :
      m_sizeTile(sizeTile)
   {

      cout.m_p = this;
      m_x = 0;
      m_y = 0;
      m_iBorder = 23;

   }

   
   console::~console()
   {


   }


   void console::assert_valid() const
   {


   }



   void console::dump(dump_context& dump) const
   {


   }



   void console::SetWindowSize(int iHeight, int iWidth)
   {

      sync_lock sl(mutex());

      m_sizeWindow.cx = iWidth;

      m_sizeWindow.cy = iHeight;

      ::size sizeImage(m_sizeTile.cx * m_sizeWindow.cx + m_iBorder * 2, m_sizeTile.cy * m_sizeWindow.cy + m_iBorder * 2);

      m_pimage = create_image(sizeImage);

      m_pimage->g()->m_pfont.create();

#ifdef LINUX

      m_pimage->g()->m_pfont->create_pixel_font("Ubuntu Mono", m_sizeTile.cy * 0.92);

#else

      m_pimage->g()->m_pfont->create_pixel_font("Lucida Console", m_sizeTile.cy * 0.92);

#endif

      SetScreenColor(::console::BLACK);

   }


   void console::SetCursorVisibility(bool show)
   {
   }

   void console::SetCursorPosition(int y, int x)
   {

      m_x = x;
      m_y = y;

   }

   void console::SetTextColor(int color)
   {
      m_iColor = color;
      m_iTextColor = color;

   }


   void console::SetScreenColor(int color, int iLineStart, int iLineCount)
   {

      m_iScreenColor = color;
      //sync_lock sl(&m_mutex);

      //m_pimage->g()->FillSolidRect(0,iLineStart * m_sizeTile.cy,m_pimage->width(),m_pimage->height() - iLineStart * m_sizeTile.cy,console_COLORREF(color));

      //update_image();

   }

   void console::write(const char * psz)
   {
      sync_lock sl(mutex());
      string str;
      //int i2 = 2;
      while (*psz)
      {
         char ch = *psz;
         while (m_stra.element_at_grow(m_y).get_length() < m_x + 1)
         {
            m_stra.element_at_grow(m_y) += ' ';
         }
         m_stra.element_at_grow(m_y).set_at(m_x, ch);
         m_i2aColor.element_at_grow(m_y).element_at_grow(m_x) = m_iColor;

         m_x++;

         if (m_x >= (m_pimage->width() / m_sizeTile.cx))
         {
            m_x = 0;
            m_y++;
         }

         psz++;
      }

   }


   void console::write(const void * pdata, memsize nCount)
   {

#ifdef WINDOWS

      string str((const char *)pdata, __min(strnlen_s((const char *)pdata, (size_t)nCount), nCount));

#else
      string str((const char *)pdata, min(strnlen((const char *)pdata, (size_t)nCount), nCount));

#endif
      write(str);
   }


   void console::update_image()
   {

      sync_lock sl(mutex());

      if (m_pimage.nok())
      {

         return;

      }

      color32_t crScreen = console_COLORREF(m_iScreenColor);

      m_pimage->fill(crScreen);

      for (int y = 0; y < m_stra.get_count(); y++)
      {

         string & str = m_stra[y];

         for (int x = 0; x < str.get_length(); x++)
         {

            draw_write(str[x], x, y, m_i2aColor[y][x]);

         }

      }

   }


   bool console::defer_write(char ch, int x, int y, int cx, int cy, int iColor)
   {

      return false;

   }

   ::draw2d::pen_pointer & console::get_pen2(int iColor)
   {

      ::draw2d::pen_pointer & pen2 = m_mappen2[iColor];

      if (pen2.is_null())
      {

         pen2.create(this);

         pen2->create_solid(2.0, console_COLORREF(iColor));

      }

      return pen2;

   }

   ::draw2d::pen_pointer & console::get_pen1(int iColor)
   {

      ::draw2d::pen_pointer & pen1 = m_mappen1[iColor];

      if (pen1.is_null())
      {

         pen1.create(this);

         pen1->create_solid(1.0, console_COLORREF(iColor));

      }

      return pen1;

   }

   void console::draw_write(char ch, int x, int y, int iColor)
   {
      if (ch == ' ')
      {
         return;
      }
      string str;
      int i2 = 2;

      if (!defer_write(ch, m_iBorder + x * m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy, m_sizeTile.cx, m_sizeTile.cy, iColor))
      {

         m_pimage->g()->set_smooth_mode(::draw2d::smooth_mode_none);

         if (ch == (char)209)// horizontal double / down simple
         {

            ::draw2d::pen_pointer & point2 = get_pen2(iColor);
            ::draw2d::pen_pointer & point = get_pen1(iColor);

            m_pimage->g()->set(point2);

            m_pimage->g()->draw_line(
               ::point(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );

            m_pimage->g()->set(point);

            m_pimage->g()->draw_line(
               ::point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               ::point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)205)// horizontal double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

            m_pimage->g()->draw_line(
               point(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)196) // horizontal simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

               m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               point(m_iBorder + x * m_sizeTile.cx,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2),
               point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2)
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)186) // vertical double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

            m_pimage->g()->draw_line(
               point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy),
               point(m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
                  m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1)
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)199) // vertical double / right simple
         {
            ::draw2d::pen_pointer & point2 = get_pen2(iColor);
            ::draw2d::pen_pointer & point = get_pen1(iColor);
            m_pimage->g()->set(point2);

           m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );
            m_pimage->g()->set(point);

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)182) // vertical double / left simple
         {
            ::draw2d::pen_pointer & point2 = get_pen2(iColor);
            ::draw2d::pen_pointer & point = get_pen1(iColor);
            m_pimage->g()->set(point2);

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );
            m_pimage->g()->set(point);

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)179) // vertical simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

               m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)218) // top-left simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

               m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)201) // top-left double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)200) // bottom-left double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 - i2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)192) // bottom-left simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

               m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx + 1, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)188) // bottom-right double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

           m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)217) // bottom-right simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

               m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else if (ch == (char)187) // top-right double
         {

            if (m_iLastPen != 2 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point2 = get_pen2(iColor);

               m_pimage->g()->set(point2);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2 + i2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 2;

         }
         else if (ch == (char)191) // top-right simple
         {

            if (m_iLastPen != 1 || m_iLastPenColor != iColor)
            {

               ::draw2d::pen_pointer & point = get_pen1(iColor);

              m_pimage->g()->set(point);

            }

            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2
            );
            m_pimage->g()->draw_line(
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2,
               m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy / 2,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx / 2, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy + 1
            );

            m_iLastPenColor = iColor;
            m_iLastPen = 1;

         }
         else
         {

            string str;

            ::str::international::multibyte_to_utf8(437, str, string(ch));

            //str = ch;

            m_pimage->g()->set_text_color(console_COLORREF(iColor));

           m_pimage->g()->draw_text(str, rect(m_iBorder + x * m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy,
               m_iBorder + x * m_sizeTile.cx + m_sizeTile.cx, m_iBorder + y * m_sizeTile.cy + m_sizeTile.cy), e_align_center);

         }

      }

   }


   void console::to_string(const string_exchange & str) const
   {

      __throw(not_implemented());

   }


} // namespace graphics




