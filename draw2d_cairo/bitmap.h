#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      cairo_surface_t *       m_psurface;
      memory                  m_mem;
      ::size                  m_size;


      bitmap();
      virtual ~bitmap();


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(::u32 nIDResource);
      bool LoadOEMBitmap(::u32 nIDBitmap); // for OBM_/OCR_/OIC_
   #ifndef ___NO_AFXCMN_SUPPORT
// xxx      bool LoadMappedBitmap(::u32 nIDBitmap, ::u32 nFlags = 0, LPCOLORMAP lpColorMap = nullptr, i32 nMapSize = 0);
   #endif
      bool CreateBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight, ::u32 nPlanes, ::u32 nBitcount, const void * lpBits, i32 iStride);
//      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      bool create_bitmap(::draw2d::graphics * pgraphics, const ::size & size, void **ppvBits, int * stride);
      bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, ::u32 flInit, const void *pjBits, ::u32 iUsage);


      //i32 GetBitmap(BITMAP* pBitMap);


      ::u32 SetBitmapBits(::u32 dwCount, const void * lpBits);
      ::u32 GetBitmapBits(::u32 dwCount, void * lpBits) const;
      ::size SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;


      virtual bool attach(void * posdata);


      virtual void destroy();



   };


} // namespace draw2d_cairo


