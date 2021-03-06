﻿#include "framework.h"
#include <math.h>


struct FIBITMAP;


#ifndef WINDOWS


CLASS_DECL_ACME void cra_from_quada(colorref_array & colorrefa, RGBQUAD * prgbquad, int iCount)
{

   colorrefa.set_size(iCount);

   for (index i = 0; i < iCount; i++)
   {

#if defined(ANDROID) && defined(__arm__)
      colorrefa[i] = ARGB(255, prgbquad[i].rgbRed, prgbquad[i].rgbGreen, prgbquad[i].rgbBlue);
#else
      colorrefa[i] = ARGB(255, prgbquad[i].rgbBlue, prgbquad[i].rgbGreen, prgbquad[i].rgbRed);
#endif

      if (colorrefa[i] == ARGB(255, 255, 255, 255))
      {

         output_debug_string("completely white");

      }

   }

}

#endif



namespace imaging_freeimage
{


   bool freeimage_load_imagea_frame(::image * pimageCompose, image_frame_array * pimagea, index iFrame, FIBITMAP * pfi);

   
   ::estatus context_image::_load_image(::image * pimageCompose, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory)
   {

      fimemory mem(*pmemory);

      if (!mem)
      {

         return false;

      }

      FIMULTIBITMAP * multibitmap = nullptr;

      try
      {

         FREE_IMAGE_FORMAT format = mem.get_image_format();

         //if (true)
         {

            multibitmap = FreeImage_LoadMultiBitmapFromMemory(format, mem);

            try
            {

               ::count cFrame = FreeImage_GetPageCount(multibitmap);

               for (index iFrame = 0; iFrame < cFrame; iFrame++)
               {

                  auto pframe = __new(image_frame);

                  pframea->add(pframe);

                  __construct(pframe->m_pimage);

                  pframe->m_iFrame = iFrame;

                  FIBITMAP * pfi = FreeImage_LockPage(multibitmap, (int)iFrame);

                  if (pfi != nullptr)
                  {

                     int w = FreeImage_GetWidth(pfi);

                     int h = FreeImage_GetHeight(pfi);

                     FITAG * ptag;

                     if (iFrame <= 0)
                     {

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalWidth", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cx = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "LogicalHeight", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                           {

                              pframea->m_size.cy = *((short *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "GlobalPalette", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_PALETTE)
                           {

                              cra_from_quada(pframea->m_colorrefa, (RGBQUAD *)FreeImage_GetTagValue(ptag), FreeImage_GetTagCount(ptag));

                           }

                        }

                        if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "Loop", &ptag))
                        {

                           if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                           {

                              pframea->m_countLoop = (unsigned int)*((long *)FreeImage_GetTagValue(ptag));

                           }

                        }

                        pimageCompose->create(pframea->m_size);

                        pimageCompose->fill(0);

                     }

                     pframe->m_rect.left = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameLeft", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rect.left = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rect.right = pframe->m_rect.left + w;

                     pframe->m_rect.top = 0;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTop", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_SHORT)
                        {

                           pframe->m_rect.top = *((short *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     pframe->m_rect.bottom = pframe->m_rect.top + h;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "NoLocalPalette", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           pframe->m_bLocalPalette = *((u8 *)FreeImage_GetTagValue(ptag)) == 0;

                        }

                     }

                     pframe->m_edisposal = draw2d::disposal_undefined;

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "DisposalMethod", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_BYTE)
                        {

                           auto iDisposal = *((u8 *)FreeImage_GetTagValue(ptag));

                           pframe->gif_set_disposal(iDisposal);

                        }

                     }

                     if (FreeImage_GetMetadata(FIMD_ANIMATION, pfi, "FrameTime", &ptag))
                     {

                        if (FreeImage_GetTagType(ptag) == FIDT_LONG)
                        {

                           pframe->m_tick = (u32) * ((long *)FreeImage_GetTagValue(ptag));

                        }

                     }

                     if (!freeimage_load_imagea_frame(pimageCompose, pframea, iFrame, pfi))
                     {

                        output_debug_string("failed to load page image");

                     }

                  }

               }

            }
            catch (...)
            {

            }

            FreeImage_CloseMultiBitmap(multibitmap);

         }

      }
      catch (...)
      {
         return false;

      }

      return true;

   }


   bool freeimage_load_imagea_frame(image * pimageCompose, image_frame_array * pframea, index iFrame, FIBITMAP * pfi)
   {

      if (pfi == nullptr)
      {

         return false;

      }

      image_frame * pframe = pframea->element_at(iFrame);

      //BITMAPINFO * pbi = nullptr;

      //void * pdata = nullptr;

      //pbi = FreeImage_GetInfo(pfi);

      //pdata = FreeImage_GetBits(pfi);

      //int w = FreeImage_GetWidth(pfi);

      //int h = FreeImage_GetHeight(pfi);

      image_pointer pimageFrame;

      auto estatus = __construct(pimageFrame);

      if (!estatus || !pimageFrame)
      {

         return false;

      }

      image_from_freeimage(pimageFrame, pfi);

      ::draw2d::e_disposal edisposal = iFrame <= 0 ? ::draw2d::disposal_none : pframea->element_at(iFrame)->m_edisposal;

      pframe->m_edisposal = edisposal;

      pframe->_001Process(pimageCompose, pimageFrame, pframea);


//      int transparentIndex = FreeImage_GetTransparentIndex(pfi);
//
//      bool bIsTransparent = FreeImage_IsTransparent(pfi) != 0;
//
//      if (!bIsTransparent)
//      {
//
//         transparentIndex = -1;
//
//      }
//
//      RGBQUAD quad;
//
//      if (FreeImage_GetBackgroundColor(pfi, &quad))
//      {
//
//         output_debug_string("has background color");
//
//      }
//
//      int iScan = FreeImage_GetPitch(pfi);
//
//      if (FreeImage_GetBPP(pfi) == 8)
//      {
//
//         if (pframe->m_bLocalPalette && pbi->bmiHeader.biClrUsed > 0)
//         {
//
//            colorref_array cra;
//
//            cra_from_quada(cra, pbi->bmiColors, pbi->bmiHeader.biClrUsed);
//
//            /*if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (u8 *)pdata, iScan, cra, transparentIndex))
//            {
//
//               return false;
//
//            }*/
//
//         }
//         else
//         {
//
//#if defined(ANDROID) && defined(__arm__)
//
//            color32_t crQuad = ARGB(255, quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
//
//#else
//
//            //color32_t crQuad = ARGB(255, quad.rgbBlue, quad.rgbGreen, quad.rgbRed);
//
//#endif
//
//            //if (!draw2d_gif_load_frame(pimageCompose, pframea, pframe, iFrame, (u8 *)pdata, iScan, pframea->m_colorrefa, transparentIndex))
//            //{
//
//            //   return false;
//
//            //}
//
//         }
//
//      }
//      else if (FreeImage_GetBPP(pfi) == 32)
//      {
//
//         ::copy_colorref(pframe->m_pimage->colorref(), pframe->m_pimage->width(), pframe->m_pimage->height(), pframe->m_pimage->scan_size(), (color32_t *)pdata, iScan);
//
//         return true;
//
//      }
//      else
//      {
//
//         return false;
//
//      }

      return true;

   }


} // namespace imaging_freeimage



