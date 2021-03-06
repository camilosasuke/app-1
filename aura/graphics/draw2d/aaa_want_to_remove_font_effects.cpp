#include "framework.h"



namespace draw2d
{


   font::font(::layered * pobjectContext) :
      ::draw2d::font(pobject),
      m_pfont(e_create)
   {

      m_pDC       = nullptr;
      m_pfontOld  = nullptr;

   }


   font::~font()
   {

   }


   void font::clear()
   {

      m_glyphset.remove_all();

   }


   ::draw2d::font * font::GetFont()
   {

      return m_pfont;

   }


   void font::EmbossedTextOut(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, double dRateX, double dHeight, string & str)
   {


      System.draw2d().api().EmbossedTextOut(pgraphics, rect, dRateX, dHeight, str);

      return;



//      SetDC(pgraphics);
//      SelectFont();
//
//      ::rect rectOffset(rect);
//      const ::point & pointOffset(rectOffset.top_left());
//
//      glyph * pglyph;

//      strsize iSize = str.get_length();
//      for(i32 i = 0; i < iSize; i++)
//      {
//         pglyph = GetGlyph(str[i]);

//         if(pglyph != nullptr)

//         {
//            pointOffset.x = ::i32(pgraphics->GetTextExtent(str.Left(i)).cx);
//            pglyph->DrawGlyph(

//               pgraphics,
//               true,
//               (float) dRateX,
//               &pointOffset);
//         }
//      }
//
//
//
//      UnselectFont();
//      ClearDC();

      /*   SetDC(pgraphics);
         SelectFont();

         pgraphics->text_out(x, y, str);
         pgraphics->BeginPath();
         pgraphics->text_out(x, y, str);
         pgraphics->EndPath();
         pgraphics->StrokePath();

         UnselectFont();
         ClearDC();*/

   }

   void font::EmbossedTextOut(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, double dRateX, double dHeight, string & str, LPINT piCharsPositions, i32 iCharsPositions, i32 iOffset)

   {

      System.draw2d().api().EmbossedTextOut(pgraphics, rect, dRateX, dHeight, str, piCharsPositions, iCharsPositions, iOffset);


      return;



//      SetDC(pgraphics);
//      SelectFont();
//
//      const ::rect rectOffset(rect);
//      const ::point & pointOffset;
//
//
//      glyph * pglyph;

//      strsize iSize = str.get_length();
//      for(strsize i = 0; i < iSize; i++)
//      {
//         pglyph = GetGlyph(str[i]);

//         if(pglyph != nullptr)

//         {
//            pointOffset = rectOffset.top_left();
//            pointOffset.x += (long) ((piCharsPositions[iOffset + i] - lpiCharsPositions[iOffset]) * dRateX);

//            pglyph->DrawGlyph(

//               pgraphics,
//               true,
//               (float) dRateX,
//               &pointOffset);
//         }
//      }


      /*   draw2d::api::EmbossedTextOut(
            pgraphics,
            pcrect,

            floatRateX,
            floatHeight,
            str,
            piCharsPositions,

            iCharsPositions,
            iOffset);*/

//      UnselectFont();
//      ClearDC();
      /*   SetDC(pgraphics);
         SelectFont();

         ::rect clipRect;

         i32 iOldMapMode = pgraphics->GetMapMode();
         pgraphics->SetMapMode(MM_TEXT);
         pgraphics->text_out(x, y, str);
         pgraphics->BeginPath();
         pgraphics->text_out(x, y, str);
         pgraphics->EndPath();
         pgraphics->StrokePath();

         pgraphics->SetMapMode(iOldMapMode);
         UnselectFont();
         ClearDC();*/
   }

   void font::SimpleTextOut(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y, string & str, LPINT piCharsPositions, i32 iCharsPositions)


   {


      UNREFERENCED_PARAMETER(piCharsPositions);

      UNREFERENCED_PARAMETER(iCharsPositions);
      SetDC(pgraphics);
      SelectFont();

      ::rect clipRect;

      pgraphics->text_out(x, y, str);

      UnselectFont();

      ClearDC();

   }


   bool font::AddGlyph(WCHAR wchar)
   {

      return AddGlyph((::u32) wchar);

   }


   bool font::AddGlyph(char tch)
   {

      return AddGlyph((::u32) tch);

   }


   bool font::AddGlyph(::u32 user)
   {

      //   single_lock sl(&m_mutex);
      //   sl.lock(U32_INFINITE_TIMEOUT);

      return TRUE;

#ifdef WINDOWS_DESKTOP

      if(m_glyphset.find_first(user) >= 0)
         return TRUE;

      glyph glyph;
      glyph.m_ui = user;
      //m_glyphArray.add(pGlyph);
      MAT2 mat2;
      mat2.eM11.value = 1;
      mat2.eM11.fract = 0;
      mat2.eM12.value = 0;
      mat2.eM12.fract = 0;
      mat2.eM21.value = 0;
      mat2.eM21.fract = 0;
      mat2.eM22.value = 1;
      mat2.eM22.fract = 0;
      GLYPHMETRICS gm;

      u32 cbBuffer = m_pDC->GetGlyphOutline(user, GGO_NATIVE, &glyph.m_gm, 0, nullptr, &mat2);

      if(cbBuffer == GDI_ERROR)
         return FALSE;

      if(cbBuffer == 0)
      {

         m_glyphset.add(glyph);

         return TRUE;

      }

      LPTTPOLYGONHEADER pPH = (LPTTPOLYGONHEADER) malloc(cbBuffer);


      if(pPH == nullptr)

         return FALSE;

      m_pDC->GetGlyphOutline(user, GGO_NATIVE, &gm, cbBuffer, pPH, &mat2);


      glyph.Initialize(pPH, cbBuffer, m_iFontHiHeight);


      free(pPH);


      m_glyphset.add(glyph);

      return TRUE;

#endif

   }

   void font::SetDC(::draw2d::graphics_pointer & pgraphics)
   {
      ASSERT(m_pDC == nullptr);
      ASSERT(pgraphics != nullptr);
      m_pDC = pgraphics;
   }

   void font::SelectFont()
   {
      m_pfontOld = m_pDC->SelectObject(m_pfont);
   }

   void font::ClearDC()
   {
      m_pDC = nullptr;
   }

   void font::UnselectFont()
   {
      ASSERT(m_pfontOld != nullptr);
      m_pDC->SelectObject(m_pfontOld);
      m_pfontOld = nullptr;
   }



   glyph * font::GetGlyph(char ch)
   {
      return GetGlyph((::u32) ch);
   }

   glyph * font::GetGlyph(WCHAR wch)
   {
      return GetGlyph((::u32) wch);
   }

   glyph * font::GetGlyph(::u32 user)
   {
      return m_glyphset.GetGlyph(user);
   }


   void font::AddXFGlyphs(string2a  & str2aTokens)
   {
      char           ch;
      string         str;
      i32        i, j, k;
      bool           forceInsertion = FALSE;

      SelectFont();
      for(i = 0; i < str2aTokens.get_size(); i++)
      {
         string_array & straTokens = str2aTokens[i];
         for(j = 0; j < straTokens.get_size(); j++)
         {
            str = straTokens[j];
            for(k = 0; k < str.get_length(); k++)
            {
               ch = str.operator[](k);
               if(forceInsertion)
               {
                  forceInsertion = FALSE;
                  AddGlyph(ch);
               }
               else if(ch == '\\')
               {
                  forceInsertion = TRUE;
               }
               else if(ch == '^')
               {
                  AddGlyph(' ');
               }
               else if(ch == '/')
               {
               }
               else if(ch == '%')
               {
               }
               else if(ch == '<')
               {
               }
               else if(ch == '>')
               {
               }
               else
               {
                  AddGlyph(ch);
               }
            }
         }
      }
      UnselectFont();
   }

   void font::AddGlyphs(const char * pStr)

   {
      string str(pStr);

      SelectFont();
      for(i32 i = 0; i < str.get_length(); i++)
      {
         AddGlyph(str[i]);
      }

   }

   void font::TextOutEx(
   ::draw2d::graphics_pointer & pgraphics,
   const rect &               rect,
   double               dRateX,
   double               dHeight,
   string                 &str,
   LPINT                piCharsPositions,

   i32                     iCharsPositions,
   i32                  iOffset,
   i32                     iEffect)
   {

      switch(iEffect)
      {
      case EffectSimple:
         SimpleTextOut(pgraphics, rect.left, rect.top, str, piCharsPositions, iCharsPositions);

         break;
      case EffectEmbossed:
         EmbossedTextOut(
         pgraphics,
         rect,
         dRateX,
         dHeight,
         str,
         piCharsPositions,

         iCharsPositions,
         iOffset);
         break;
      default:
         ASSERT(FALSE);

      }

   }


   i32 font::GetMegaHeight()
   {

      return m_tm.tmHeight +
             m_tm.tmInternalLeading +
             m_tm.tmExternalLeading;

   }



   void font::OnSetFont()
   {
      OnUpdateFont();
   }

   void font::OnUpdateFont()
   {

      ::draw2d::graphics_pointer spgraphics(e_create);

      spgraphics->CreateCompatibleDC(nullptr);

      ::draw2d::font * pFontOld = spgraphics->SelectObject(m_pfont);

      spgraphics->get_text_metrics(&m_tm);

      m_iFontHiHeight = m_tm.tmAscent + m_tm.tmDescent;

      spgraphics->SelectObject(pFontOld);
      spgraphics->DeleteDC();

   }


} // namespace draw2d


bool CLASS_DECL_AURA TextOutU(HDC hdc, i32 x, i32 y, const char * pString, i32 ca)

{

#ifdef WINDOWS_DESKTOP

   if(pString == nullptr)

   {
      return ::TextOutW(hdc, x, y, nullptr, ca) != FALSE;

   }

   wstring wstr = ::str::international::utf8_to_unicode(pString, ca);


   bool bRet = ::TextOutW(hdc, x, y, wstr, (i32) wstr.get_length()) != FALSE;

   return bRet;

#else

   __throw(todo());

   /*

      if(pString == nullptr)

      {
         return ::text_out(hdc, x, y, nullptr, 0) != FALSE;
      }

      return ::text_out(hdc, x, y, wstr, (i32) wstr.get_length()) != FALSE;
   */

#endif

}


CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const char * pString, i32 ca, LPSIZE32 psizl)

{

#ifdef WINDOWS_DESKTOP

   if(pString == nullptr)

   {

      return ::GetTextExtentPoint32W(hdc, nullptr, ca, psizl) != FALSE;

   }

   wstring wstr = ::str::international::utf8_to_unicode(pString, ca);


   bool bRet = ::GetTextExtentPoint32W(hdc, wstr, (i32) wstr.get_length(), psizl) != FALSE;

   return bRet;

#else

   __throw(todo());

#endif

}


CLASS_DECL_AURA i32  DrawTextU(HDC hdc, const char * pchText, i32 cchText, RECT32 * lprc, ::u32 format)

{

#ifdef WINDOWS_DESKTOP

   if(pchText == nullptr)

   {

      return ::DrawTextW(hdc, nullptr, cchText, prc, format);


   }

   wstring wstr = ::str::international::utf8_to_unicode(pchText, cchText);


   bool bRet = ::DrawTextW(hdc, wstr, (i32) wcslen(wstr), prc, format) != FALSE;


   return bRet;

#else

   __throw(todo());

#endif

}


