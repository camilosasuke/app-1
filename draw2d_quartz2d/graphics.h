#pragma once



namespace draw2d_quartz2d
{

   class graphics;


   class brush;
   class pen;
   class font;
   class path;


   class CLASS_DECL_DRAW2D_QUARTZ2D graphics :
      virtual public ::draw2d::graphics
   {
   public:

      int                           m_iSaveDC;
      bool                          m_bOwnDC;
      CGContextRef                  m_pdc;
      CGLayerRef                    m_layer;
//      CGAffineTransform             m_affine;

      i32                       m_iType;
#ifdef __MM
      NSColor *                     m_nscolorFore;
      NSColor *                     m_nscolorBack;
#else
      void *                        m_pnscolorFore;
      void *                        m_pnscolorBack;
#endif

      bool                          m_bForeColor;
      bool                          m_bBackColor;
      u64                      m_uiForeColor;
      u64                      m_uiBackColor;
      bool                          m_bPrinting;


      graphics();
      virtual ~graphics();


      bool IsPrinting() override;            // TRUE if being used for printing

      ::draw2d::pen * get_current_pen() override;
      ::draw2d::brush * get_current_brush() override;
      ::draw2d::palette * get_current_palette() override;
      ::draw2d::font * get_current_font() override;
      ::draw2d::bitmap * get_current_bitmap() override;


      // for bidi and mirrored localization
      DWORD GetLayout() override;
      DWORD SetLayout(DWORD dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual bool RestoreDC(i32 nSavedDC) override;
      i32 GetDeviceCaps(i32 nIndex) override;
      UINT SetBoundsRect(const ::rect & rectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectBounds, UINT flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode);

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(i32 x, i32 y) override;
      point SetBrushOrg(const ::point & point) override;
      i32 EnumObjects(i32 nObjectType,
                          i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

//      // Type-safe selection helpers
//   public:
//      virtual ::draw2d::object* SelectStockObject(i32 nIndex) override;
//      ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
//      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
//      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont) override;
      virtual ::estatus set(::draw2d::bitmap* pBitmap) override;
//      i32 SelectObject(::draw2d::region* pRgn) override;       // special return for regions
//      ::draw2d::object* SelectObject(::draw2d::object* pObject);


      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

      //virtual bool SelectFont(::draw2d::font * pfont) override;


      // color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette() override;
      void UpdateColors() override;

      // Drawing-Attribute Functions
      COLORREF GetBkColor() const;
      i32 GetBkMode() const;
      i32 GetPolyFillMode() override;
      i32 GetROP2() override;
      i32 GetStretchBltMode() override;

      virtual COLORREF SetBkColor(COLORREF crColor);
      i32 SetBkMode(i32 nBkMode);
      i32 SetPolyFillMode(i32 nPolyFillMode) override;
      i32 SetROP2(i32 nDrawMode) override;
      i32 SetStretchBltMode(i32 nStretchMode) override;

      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);

#if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() const;
      COLORREF SetDCBrushColor(COLORREF crColor);

      COLORREF GetDCPenColor() const;
      COLORREF SetDCPenColor(COLORREF crColor);

#endif

      // Graphics mode
      i32 SetGraphicsMode(i32 iMode) override;
      i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,DWORD iMode);
      bool GetWorldTransform(XFORM* pXform) const;

      // Mapping Functions
      virtual i32 GetMapMode() override;
      virtual point GetViewportOrg() override;
      virtual i32 SetMapMode(i32 nMapMode) override;
      // Viewport Origin
      virtual point SetViewportOrg(i32 x, i32 y) override;
      virtual point SetViewportOrg(const ::point & point) override;
      virtual point OffsetViewportOrg(i32 nWidth, i32 nHeight) override;

      // Viewport Extent
      virtual size GetViewportExt() override;
      virtual size SetViewportExt(i32 cx, i32 cy) override;
      virtual size SetViewportExt(const ::size & size) override;
      virtual size ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom) override;

      // Window Origin
      point GetWindowOrg() override;
      point SetWindowOrg(i32 x, i32 y) override;
      point SetWindowOrg(const ::point & point) override;
      point OffsetWindowOrg(i32 nWidth, i32 nHeight) override;

      // Window extent
      size GetWindowExt() override;
      virtual size SetWindowExt(i32 cx, i32 cy) override;
      size SetWindowExt(const ::size & size) override;
      virtual size ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom) override;

      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints, i32 nCount = 1) const;
      void DPtoLP(RECT * prect) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, i32 nCount = 1) const;
      void LPtoDP(RECT * prect) override;
      void LPtoDP(LPSIZE lpSize) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) override;
      void LPtoHIMETRIC(LPSIZE lpSize) override;
      void HIMETRICtoDP(LPSIZE lpSize) override;
      void HIMETRICtoLP(LPSIZE lpSize) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual i32 GetClipBox(RECT * prect) override;
      virtual bool PtVisible(i32 x, i32 y) override;
      virtual bool PtVisible(const ::point & point) override;
      virtual bool RectVisible(const ::rect & rect) override;
      virtual i32 SelectClipRgn(::draw2d::region* pRgn) override;
      virtual i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      virtual i32 ExcludeClipRect(const ::rect & rect) override;
      //i32 ExcludeUpdateRgn(::user::interaction * pWnd);
      virtual i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      virtual i32 IntersectClipRect(const ::rect & rect) override;
      virtual i32 OffsetClipRgn(i32 x, i32 y) override;
      virtual i32 OffsetClipRgn(const ::size & size) override;
      virtual i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode) override;

      // Line-Output Functions
      virtual pointd current_position() override;
      //      point MoveTo(i32 x, i32 y);
      //    point MoveTo(const ::point & point);
      virtual bool line_to(const ::pointd & point) override;
      //  bool LineTo(const ::point & point);
//      virtual bool Arc(i32 x1, i32 y1, i32 w, i32 h, double start, double extends) override;
  //    virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
//      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      virtual bool Arc(double x, double y, double w, double h, double start, double end) override;
//      virtual bool Arc(const ::rectd & rect, const ::pointd & pointStart, const ::pointd & pointEnd) override;
      virtual bool Polyline(const POINT* lpPoints, count nCount) override;

      virtual bool AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle) override;
//      virtual bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      virtual bool ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual i32 GetArcDirection() override;
      virtual i32 SetArcDirection(i32 nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, i32 nCount);
      bool PolylineTo(const POINT* lpPoints, i32 nCount);
      bool PolyPolyline(const POINT* lpPoints,
                        const DWORD* lpPolyPoints, i32 nCount);

      bool PolyBezier(const POINT* lpPoints, i32 nCount);
      bool PolyBezierTo(const POINT* lpPoints, i32 nCount);

      // Simple Drawing Functions
      virtual bool fill_rect(const ::rectd & rect, ::draw2d::brush* pbrush) override;
      virtual bool draw_rect(const ::rectd & rect, ::draw2d::pen* ppen) override;

      virtual bool rectangle(const ::rectd & rect) override;
      virtual bool draw_rect(const ::rectd & rect) override;
      virtual bool fill_rect(const ::rectd & rect) override;

      virtual void frame_rect(const ::rect & rect, ::draw2d::brush* pbrush) override;
      virtual void invert_rect(const ::rect & rect) override;
      
      
      virtual bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon) override;
      virtual bool DrawIcon(const ::point & point, ::draw2d::icon * picon) override;
      virtual bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, UINT nFlags,
//                             HBRUSH hBrush = nullptr) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
//                             ::draw2d::brush* pBrush = nullptr) override;
      /*      bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                           HBRUSH hBrush = nullptr);
            bool DrawState(const ::point & point, const ::size & size, HICON hIcon, UINT nFlags,
                           ::draw2d::brush* pBrush = nullptr);*/
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      virtual bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
//                             bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;
      //xxx      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, UINT nFlags, HBRUSH hBrush = nullptr);
      //xxx      bool DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = nullptr);

      // Ellipse and Polygon Functions
      virtual bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                         i32 x4, i32 y4) override;
      virtual bool Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual void DrawFocusRect(const ::rect& rect) override;

//      bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool DrawEllipse(const ::rectd & rect) override;
//
//      bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool FillEllipse(const ::rectd & rect) override;

      //bool draw(double x1, double y1, double x2, double y2) override;
      bool draw_ellipse(const ::rectd & rect) override;

      //bool FillEllipse(double x1, double y1, double x2, double y2) override;
      bool fill_ellipse(const ::rectd & rect) override;

      bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      virtual bool set_polygon(const POINTD * lpPoints, count nCount);
      virtual bool set_polygon(const POINT * lpPoints, count nCount);
      virtual bool fill_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool fill_polygon(const POINT* lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINT * lpPoints, count nCount) override;
      virtual bool polygon(const POINTD * ppoint,count nCount) override;
      virtual bool round_rect(const ::rectd & rect, const ::pointd & point) override;

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, DWORD dwRop) override;
      using ::draw2d::graphics::BitBlt;
      bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                     i32 xSrc, i32 ySrc, DWORD dwRop) override;
      virtual bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                                 i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, DWORD dwRop) override;
      COLORREF GetPixel(i32 x, i32 y) override;
      COLORREF GetPixel(const ::point & point) override;
      COLORREF SetPixel(i32 x, i32 y, COLORREF crColor) override;
      COLORREF SetPixel(const ::point & point, COLORREF crColor) override;
      bool FloodFill(i32 x, i32 y, COLORREF crColor) override;
      bool ExtFloodFill(i32 x, i32 y, COLORREF crColor, UINT nFillType) override;
      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
                   DWORD dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask) override;
      bool SetPixelV(i32 x, i32 y, COLORREF crColor) override;
      bool SetPixelV(const ::point & point, COLORREF crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
                        void * pMesh, WINULONG nMeshElements, DWORD dwMode) override;
      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                          UINT clrTransparent) override;

      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
       ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
       BLENDFUNCTION blend);*/


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;

      // Text Functions
      virtual bool internal_show_text(double x, double y, double w, UINT nFormat, const string & str, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr, ::draw2d::pen * ppen=nullptr, ::draw2d::brush * pbrush = nullptr, ::draw2d::font * pfont = nullptr);

      virtual bool internal_show_text(::draw2d::font_pointer spfont,::draw2d::brush_pointer spbrush,::draw2d::pen_pointer sppen, double x, double y, double w, UINT nFormat, const string & str, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = nullptr, CGFloat * pdescent = nullptr, CGFloat * pleading = nullptr, CGFloat * pwidth = nullptr);

      void internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush);

      virtual bool BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop) override;

      virtual bool draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen) override;
      virtual bool text_out(i32 x, i32 y, const char * lpszString, strsize nCount) override;

      virtual bool text_out(i32 x, i32 y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const string & str) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const ::rectd & rect,
                              const char * lpszString, UINT nCount, LPINT lpDxWidths);
      bool ExtTextOut(i32 x, i32 y, UINT nOptions, const ::rect & rect,
                      const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, i32 nCount,
                                 i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      size TabbedTextOut(i32 x, i32 y, const string & str,
                         i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);

      virtual i32 draw_text(const char * lpszString, i32 nCount, const ::rectd & rect, UINT nFormat);
      virtual bool draw_text(const string & str, const ::rectd & rect, UINT nFormat) override;
      virtual bool draw_text(const string & strParam,const ::rect & rect,UINT nFormat) override;

      virtual i32 draw_text_ex(LPTSTR lpszString, i32 nCount, const ::rectd & rect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str, const ::rectd & rect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;

      sized GetTextExtent(const char * lpszString, strsize nCount, i32 iIndex);
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, i32 iIndex) ;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) ;
      virtual bool GrayString(::draw2d::brush* pBrush,
                              bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData,
                              i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight) override;
      UINT GetTextAlign() override;
      UINT SetTextAlign(UINT nFlags) override;
      i32 GetTextFace(i32 nCount, LPTSTR lpszFacename);
      i32 GetTextFace(string & rString) override;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
      i32 GetTextCharacterExtra() override;
      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      DWORD GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
      //xxx      DWORD GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE lpSize) const;

#endif



      // Advanced Drawing
      bool DrawEdge(RECT * prect, UINT nEdge, UINT nFlags);
      bool DrawFrameControl(RECT * prect, UINT nType, UINT nState);

      // Scrolling Functions
      bool ScrollDC(i32 dx, i32 dy, const ::rect & rectScroll, const ::rect & rectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      DWORD SetMapperFlags(DWORD dwFlag) override;
      size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
      DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) override;
      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      //xxx      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
      //xxx      DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
      //xxx    DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
      //xxx         LPABCFLOAT lpABCF) const;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;

      DWORD GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData) override;
      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData) override;

      // Escape helpers
      i32 StartDoc(const char * lpszDocName) override;  // old Win3.0 version
      //xxx      i32 StartDoc(LPDOCINFO lpDocInfo);
      i32 StartPage() override;
      i32 EndPage() override;
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect & rectBounds);
      bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

      // Path Functions
      virtual bool abort_path() override;
      virtual bool begin_path() override;
      virtual bool close_figure() override;
      virtual bool end_path() override;
      virtual bool fill_path() override;
      virtual bool flatten_path() override;
      virtual bool stroke_and_fill_path() override;
      virtual bool stroke_path() override;
      virtual bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;

      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      bool draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);


      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes, i32 nCount) ;
      bool SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::base::application * papp);
//      void DrawDragRect(const ::rectd & rect, const ::size & size,
//                        const ::rectd & rectLast, const ::size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      virtual void fill_rect(const ::rectd & rect, COLORREF clr) override;
      virtual void draw3d_rect(const ::rectd & rect, COLORREF clrTopLeft, COLORREF clrBottomRight, eborder eborder = border_all) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool set_alpha_mode(::draw2d::e_alpha_mode ealphamode) override;

      virtual bool set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrenderinghint) override;

      //virtual void * get_os_data() const override;
      //      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;

      virtual bool attach(void * pdata) override;
      virtual void * detach() override;


      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rect & rect) override;



      // platform-specific or platform-internals
      bool clip(const ::draw2d::region * pregion);
      bool add_path(const ::draw2d::region * pregion);
      bool set(const ::draw2d::brush * pbrush);
      bool set_pen(const ::draw2d::brush * pbrush, double dWidth);
      bool set(const ::draw2d::pen * ppen);
      //bool set(const ::draw2d::font * pfont);
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool fill_inline(const ::draw2d::path * ppath, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_inline(const ::draw2d::path::element & e, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path::element & e, ::draw2d::pen * ppen);
      bool set(const ::draw2d::path::string_path & stringpath);
      bool fill_inline(const ::draw2d::path::string_path & stringpath, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path::string_path & stringpath, ::draw2d::pen * ppen);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush);
      bool _fill(::draw2d::brush * pbrush, bool bClip);
      bool draw(::draw2d::brush * pbrush);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill();
      bool draw();


      void internal_set_fill_color(COLORREF cr);


      virtual void enum_fonts(::draw2d::font_enum_item_array & itema) override;
      
      
      virtual ::estatus clear_current_point() override;
      

   };


} // namespace draw2d_quartz2d




