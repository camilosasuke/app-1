#pragma once


typedef void FN_CAIRO_TEXT(cairo_t *, const char*);
typedef FN_CAIRO_TEXT * PFN_CAIRO_TEXT;

#if defined(USE_PANGO)

typedef void FN_PANGO_TEXT(cairo_t *cr, PangoLayout *layout);
typedef FN_PANGO_TEXT * PFN_PANGO_TEXT;

#endif

namespace draw2d_cairo
{


   class brush;
   class pen;
   class font;
   class object;


   class CLASS_DECL_DRAW2D_CAIRO graphics :
      virtual public ::draw2d::graphics
   {
   public:


      int                        m_iSaveDC;
      int                        m_iSaveDCPositiveClip;
      cairo_t *                  m_pdc;
      i32                        m_iType;
      bool                       m_bPrinting;
      int                        m_nStretchBltMode;
      bool                       m_bToyQuotedFontSelection;

#ifdef WINDOWS
      cairo_surface_t *          m_psurfaceAttach;
      HDC                        m_hdcAttach;
#endif

      graphics();
      virtual ~graphics();



      virtual void * detach() override;

      bool IsPrinting() override;            // TRUE if being used for printing

      ::draw2d::pen *     get_current_pen() override;
      ::draw2d::brush *   get_current_brush() override;
      ::draw2d::palette * get_current_palette() override;
      ::draw2d::font *    get_current_font() override;
      ::draw2d::bitmap *  get_current_bitmap() override;


      //pen *       lnx_pen();
      //brush *     lnx_brush();
      //font *      lnx_font();

      // for bidi and mirrored localization
      u32 GetLayout() override;
      u32 SetLayout(u32 dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC() override;

      // Device-Context Functions
      virtual i32 SaveDC() override;
      virtual bool RestoreDC(i32 nSavedDC) override;
      i32 GetDevicecaps(i32 nIndex);
      UINT SetBoundsRect(const ::rect & rectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT rectBounds, UINT flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(i32 x, i32 y) override;
      point SetBrushOrg(const ::point & point) override;
      i32 EnumObjects(i32 nObjectType,
                      i32(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* set_stock_object(i32 nIndex) override;
      virtual ::estatus set(::draw2d::pen* ppen) override;
      virtual ::estatus set(::draw2d::brush* pbrush) override;
      virtual ::estatus set(::draw2d::font* pfont) override;
      virtual ::estatus set(::draw2d::bitmap* pbitmap) override;
      virtual i32 set(::draw2d::region* pregion) override;       // special return for regions
      //::draw2d_cairo::object* SelectObject(::draw2d_cairo::object* pObject);
      // ::draw2d_cairo::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

// color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette() override;
      void UpdateColors() override;

      i32 GetPolyFillMode() override;
      i32 GetROP2() override;
      i32 GetStretchBltMode() override;

      i32 SetPolyFillMode(i32 nPolyFillMode) override;
      i32 SetROP2(i32 nDrawMode) override;
      i32 SetStretchBltMode(i32 nStretchMode) override;

      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

#if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() override;
      COLORREF SetDCBrushColor(COLORREF crColor) override;

      COLORREF GetDCPenColor() override;
      COLORREF SetDCPenColor(COLORREF crColor) override;

#endif

      // Graphics mode
      i32 SetGraphicsMode(i32 iMode) override;
      i32 GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform, u32 iMode);
      bool GetWorldTransform(XFORM* pXform);

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
      void DPtoLP(LPPOINT lpPoints, count nCount = 1) override;
      void DPtoLP(RECT * prect) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, count nCount = 1) override;
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
      bool PtVisible(const ::point & point) override;
      virtual bool RectVisible(const ::rect & rect) override;
      i32 SelectClipRgn(::draw2d::region* pRgn) override;
      i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      i32 ExcludeClipRect(const ::rect & rect) override;
      i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      virtual i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      i32 OffsetClipRgn(i32 x, i32 y) override;
      i32 OffsetClipRgn(const ::size & size) override;
      i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode) override;

      // Line-Output Functions
      pointd current_position() override;
      bool move_to(const ::point & point) override;
      bool move_to(const ::pointd & point) override;
      //    point MoveTo(const ::point & point) override;
      bool line_to(const ::pointd & point) override;
      //  bool LineTo(const ::point & point) override;
      virtual bool draw_line(const ::point & point1, const ::point & point2, ::draw2d::pen * ppen) override;
      virtual bool draw_line(const ::pointd & point1, const ::pointd & point2, ::draw2d::pen * ppen) override;
      bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Arc(double x, double y, double w, double h, double start, double extends) override;
      bool Arc(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      bool Polyline(const POINT* lpPoints, count nCount) override;

      bool AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle) override;
      bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      i32 GetArcDirection() override;
      i32 SetArcDirection(i32 nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount) override;
      bool PolylineTo(const POINT* lpPoints, count nCount) override;
      bool PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount) override;

      bool PolyBezier(const POINT* lpPoints, count nCount) override;
      bool PolyBezierTo(const POINT* lpPoints, count nCount) override;

      // Simple Drawing Functions
      bool fill_rect(const ::rect & rect, ::draw2d::brush* pBrush) override;
      bool draw_rect(const ::rect & rect, ::draw2d::pen * ppen) override;
      void frame_rect(const ::rect & rect, ::draw2d::brush* pBrush) override;
      void invert_rect(const ::rect & rect) override;

      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon) override;
      bool DrawIcon(const ::point & point, ::draw2d::icon * picon) override;
      bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, UINT nFlags,
                     HBRUSH hBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                     ::draw2d::brush* pBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;




      bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                 i32 x4, i32 y4) override;
      bool Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      void DrawFocusRect(const ::rect & rect) override;

//      bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool DrawEllipse(const ::rect & rect) override;
//
//      bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2) override;
//      bool FillEllipse(const ::rect & rect) override;

      bool draw_ellipse(double x1, double y1, double x2, double y2) override;
      bool draw_ellipse(const ::rectd & rect) override;

      bool fill_ellipse(double x1, double y1, double x2, double y2) override;
      bool fill_ellipse(const ::rectd & rect) override;

      bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;

      virtual bool fill_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool fill_polygon(const POINT* lpPoints, count nCount) override;

      virtual bool draw_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINT* lpPoints, count nCount) override;


      bool polygon(const POINT * lpPoints, count nCount) override;
      bool polygon(const POINTD * lpPoints, count nCount) override;
      bool rectangle(const ::rect & rect) override;
      //virtual bool draw_rect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual bool DrawRectangle(const ::rect & rect) override;
      //virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual bool FillRectangle(const ::rect & rect) override;
      //bool roundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3) override;
      bool round_rect(const ::rect & rect, const ::point & point) override;

      // Bitmap Functions
      bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, u32 dwRop) override;
      bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                     i32 xSrc, i32 ySrc, u32 dwRop) override;
      bool StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc,
                         i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop) override;
      COLORREF GetPixel(i32 x, i32 y) override;
      COLORREF GetPixel(const ::point & point) override;
      COLORREF SetPixel(i32 x, i32 y, COLORREF crColor) override;
      COLORREF SetPixel(const ::point & point, COLORREF crColor) override;
      bool FloodFill(i32 x, i32 y, COLORREF crColor) override;
      bool ExtFloodFill(i32 x, i32 y, COLORREF crColor, UINT nFillType) override;
      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
                   u32 dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask) override;
      bool SetPixelV(i32 x, i32 y, COLORREF crColor) override;
      bool SetPixelV(const ::point & point, COLORREF crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
                        void * pMesh, WINULONG nMeshElements, u32 dwMode) override;
      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                          UINT clrTransparent) override;

      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool text_out(i32 x, i32 y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(i32 x, i32 y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const string & str) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const ::rect & rect, const char * lpszString, strsize nCount, LPINT lpDxWidths) override;
      virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const ::rect & rect, const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;
      virtual size TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin) override;

#if defined(USE_PANGO)
      //virtual bool internal_draw_text_cairo(const char * lpszString, strsize nCount, const ::rect & rect, UINT nFormat, PFN_CAIRO_TEXT pfnText);
      virtual bool internal_draw_text_pango(const char * lpszString, strsize nCount, const ::rectd & rect, UINT nFormat, PFN_PANGO_TEXT pfnText);
      virtual bool internal_draw_text(const char * lpszString, strsize nCount, const ::rectd & rect, UINT nFormat);
#else
      virtual bool internal_draw_text(const char * lpszString, strsize nCount, const ::rectd & rect, UINT nFormat, PFN_CAIRO_TEXT ftext);
#endif
      virtual bool draw_text(const char * lpszString, strsize nCount, const ::rect & rect, UINT nFormat) override;
      virtual bool draw_text(const string & str, const ::rect & rect, UINT nFormat) override;

      virtual bool draw_text_ex(LPTSTR lpszString, strsize nCount, const ::rect & rect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str, const ::rect & rect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;

      sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool _GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex);
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight) override;
      UINT GetTextAlign() override;
      UINT SetTextAlign(UINT nFlags) override;
      i32 GetTextFace(count nCount, LPTSTR lpszFacename) override;
      i32 GetTextFace(string & rString) override;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
      i32 GetTextCharacterExtra() override;
      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      u32 GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      //xxx      u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE lpSize) override;

#endif

      // Advanced Drawing
      bool DrawEdge(const ::rect & rect, UINT nEdge, UINT nFlags) override;
      bool DrawFrameControl(const ::rect & rect, UINT nType, UINT nState) override;

      // Scrolling Functions
      bool ScrollDC(i32 dx, i32 dy, const ::rect & rectScroll, const ::rect & rectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      u32 SetMapperFlags(u32 dwFlag) override;
      size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      u32 GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
      //xxx    u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
      //xxx         LPABCFLOAT lpABCF) override;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;

      u32 GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) override;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData) override;
      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData) override;

      // Escape helpers
      i32 StartDoc(const char * lpszDocName) override;  // old Win3.0 version
//xxx      i32 StartDoc(LPDOCINFO lpDocInfo) override;
      i32 StartPage() override;
      i32 EndPage() override;
      i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect & rectBounds) override;
      //    bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

// Path Functions
      bool abort_path() override;
      bool begin_path() override;
      bool close_figure() override;
      bool end_path() override;
      bool fill_path() override;
      bool flatten_path() override;
      bool stroke_and_fill_path() override;
      bool stroke_path() override;
      bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;

      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes, count nCount) override;
      bool SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::object * pobject);
//      void DrawDragRect(const ::rect & rect, const ::size & size,
//                        const ::rect & rectLast, const ::size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rect(const RECT64 * rect, COLORREF clr) override;
      void fill_rect(const ::rect & rect, COLORREF clr) override;
      void fill_rect(const ::rectd & rect, COLORREF clr) override;
      //void fill_rect(i32 x, i32 y, i32 cx, i32 cy, COLORREF clr) override;
      void draw3d_rect(const ::rect & rect, COLORREF clrTopLeft, COLORREF clrBottomRight, eborder eborder = border_all) override;
      //void draw3d_rect(i32 x, i32 y, i32 cx, i32 cy,
      //              COLORREF clrTopLeft, COLORREF clrBottomRight) override;




      // Implementation
   public:
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      //      HGDIOBJ SelectObject(HGDIOBJ) override;      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::e_alpha_mode ealphamode) override;

      virtual bool set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrenderinghint) override;

//      virtual void * get_os_data() const override;
      //      virtual HDC get_handle() override;
      //    virtual HDC get_handle1() override;
      //  virtual HDC get_handle2() override;

      virtual bool attach(void * pdata) override;

      virtual ::estatus clear_current_point() override;
      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const ::rect & rect) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h) override;


      // platform-specific or platform-internals
      bool set_os_color(COLORREF cr);
      bool set(const ::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool set(const ::draw2d::pen * ppen);
#if !defined(USE_PANGO)
      bool set(const ::draw2d::font * pfont);
#endif
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool set(const ::draw2d::path::rect & rect);
      bool set(const ::draw2d::path::string_path & str);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush, double xOrg  = 0.0, double yOrg = 0.0);
      bool _fill1(::draw2d::brush* pbrush, double xOrg = 0.0, double yOrg = 0.0);
      bool _fill2(::draw2d::brush* pbrush, double xOrg = 0.0, double yOrg = 0.0);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill(double xOrg = 0.0, double yOrg = 0.0);
      bool _fill1(double xOrg = 0.0, double yOrg = 0.0);
      bool _fill2(double xOrg = 0.0, double yOrg = 0.0);
      bool draw();


      virtual bool _get(::draw2d::matrix & matrix) override;
      virtual bool _set(const ::draw2d::matrix & matrix) override;
//      virtual bool append(const ::draw2d::matrix & matrix);
      //    virtual bool prepend(const ::draw2d::matrix & matrix);


      virtual bool flush() override;

#ifdef WINDOWS

      virtual bool attach_hdc(HDC hdc) override;
      virtual HDC detach_hdc() override;

#endif

      virtual void enum_fonts(::draw2d::font_enum_item_array & itema) override;

      virtual string get_font_path(string str);


      FT_Face ftface(const char* pszFontName);

   };


   CLASS_DECL_AURA string q_valid_string(string str);


} // namespace win




