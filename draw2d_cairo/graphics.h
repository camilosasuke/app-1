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

      //::draw2d::pen *     get_current_pen() override;
      //::draw2d::brush *   get_current_brush() override;
      //::draw2d::palette * get_current_palette() override;
      //::draw2d::font *    get_current_font() override;
      //::draw2d::bitmap *  get_current_bitmap() override;


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
      ::u32 SetBoundsRect(const ::rect & rectBounds, ::u32 flags) override;
      ::u32 GetBoundsRect(LPRECT32 rectBounds, ::u32 flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(i32 x, i32 y) override;
      point SetBrushOrg(const ::point & point) override;
      //i32 EnumObjects(i32 nObjectType,
                      //i32(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* set_stock_object(i32 nIndex) override;
      //virtual ::estatus set(::draw2d::pen* ppen) override;
      //virtual ::estatus set(::draw2d::brush* pbrush) override;
      //virtual ::estatus set(::draw2d::font* pfont) override;
      virtual ::estatus set(::draw2d::bitmap* pbitmap) override;
      virtual ::estatus set(::draw2d::region* pregion) override;       // special return for regions
      //::draw2d_cairo::object* SelectObject(::draw2d_cairo::object* pObject);
      // ::draw2d_cairo::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

// color and color Palette Functions
      //color32_t GetNearestColor(const ::color & color) override;
      //::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      //::u32 RealizePalette() override;
      //void UpdateColors() override;

      i32 GetPolyFillMode() override;
      i32 GetROP2() override;
      i32 GetStretchBltMode() override;

      i32 SetPolyFillMode(i32 nPolyFillMode) override;
      i32 SetROP2(i32 nDrawMode) override;


      bool set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode) override;


      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

//#if (_WIN32_WINNT >= 0x0500)
//
//      color32_t GetDCBrushColor() override;
//      color32_t SetDCBrushColor(const ::color & color) override;
//
//      color32_t GetDCPenColor() override;
//      color32_t SetDCPenColor(const ::color & color) override;
//
//#endif

      // Graphics mode
      i32 SetGraphicsMode(i32 iMode) override;
      i32 GetGraphicsMode() override;

//      // World transform
//      bool SetWorldTransform(const XFORM* pXform);
//      bool ModifyWorldTransform(const XFORM* pXform, u32 iMode);
//      bool GetWorldTransform(XFORM* pXform);

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
      void DPtoLP(POINT32 * lpPoints, count nCount = 1) override;
      void DPtoLP(RECT32 * prect) override;
      void DPtoLP(LPSIZE32 LPSIZE32) override;
      void LPtoDP(POINT32 * lpPoints, count nCount = 1) override;
      void LPtoDP(RECT32 * prect) override;
      void LPtoDP(LPSIZE32 LPSIZE32) override;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE32 LPSIZE32) override;
      void LPtoHIMETRIC(LPSIZE32 LPSIZE32) override;
      void HIMETRICtoDP(LPSIZE32 LPSIZE32) override;
      void HIMETRICtoLP(LPSIZE32 LPSIZE32) override;

      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;

      // Clipping Functions
      virtual i32 GetClipBox(RECT32 * prect) override;
      //virtual bool PtVisible(i32 x, i32 y) override;
      //bool PtVisible(const ::point & point) override;
      //virtual bool RectVisible(const ::rect & rect) override;
      //i32 SelectClipRgn(::draw2d::region* pRgn) override;
      //i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //i32 ExcludeClipRect(const ::rect & rect) override;
      //i32 ExcludeUpdateRgn(::user::primitive * pwindow);
      //virtual i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual i32 IntersectClipRect(const ::rect & rect) override;
      //i32 OffsetClipRgn(i32 x, i32 y) override;
      //i32 OffsetClipRgn(const ::size & size) override;
      //i32 SelectClipRgn(::draw2d::region* pRgn, ::draw2d::enum_combine ecombine) override;


      virtual ::estatus reset_clip() override;

      // Maybe used by some 2d Graphics backends as group of helper
      // methods working together for some purpose
      // (initially created for clipping).
      // It should be an aid when the 2d graphics backend supports
      // "inline" paths.
      virtual ::estatus _intersect_clip() override;
      virtual ::estatus _add_shape(const ::rect & rect) override;
      virtual ::estatus _add_shape(const ::rectd & rect) override;
      virtual ::estatus _add_shape(const ::oval & oval) override;
      virtual ::estatus _add_shape(const ::ovald & oval) override;
      virtual ::estatus _add_shape(const ::polygon & polygon) override;
      virtual ::estatus _add_shape(const ::polygond & polygon) override;

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
      bool Arc(double x, double y, double w, double h, angle start, angle extends) override;
      bool Arc(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      bool Polyline(const POINT32* lpPoints, count nCount) override;

      bool AngleArc(i32 x, i32 y, i32 nRadius, angle fStartAngle, angle fSweepAngle) override;
      bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4) override;
      bool ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd) override;
      i32 GetArcDirection() override;
      i32 SetArcDirection(i32 nArcDirection) override;

      bool PolyDraw(const POINT32* lpPoints, const byte* lpTypes, count nCount) override;
      bool PolylineTo(const POINT32* lpPoints, count nCount) override;
      bool PolyPolyline(const POINT32* lpPoints, const ::i32 * lpPolyPoints, count nCount) override;

      bool PolyBezier(const POINT32* lpPoints, count nCount) override;
      bool PolyBezierTo(const POINT32* lpPoints, count nCount) override;

      // Simple Drawing Functions
      bool fill_rect(const ::rect & rect, ::draw2d::brush* pBrush) override;
      bool draw_rect(const ::rect & rect, ::draw2d::pen * ppen) override;
      void frame_rect(const ::rect & rect, ::draw2d::brush* pBrush) override;
      void invert_rect(const ::rect & rect) override;

      //bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon) override;
      //virtual bool draw(const ::point & point, ::draw2d::icon * picon, const ::size & size) override;
      //bool DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags) override;
      //bool DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags,
        //             HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags,
//                     ::draw2d::brush* pBrush = nullptr) override;
//      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = nullptr) override;
//      bool DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags,
//                     bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = nullptr) override;




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
      virtual bool fill_polygon(const POINT32* lpPoints, count nCount) override;

      virtual bool draw_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINT32* lpPoints, count nCount) override;


      bool polygon(const POINT32 * lpPoints, count nCount) override;
      bool polygon(const POINTD * lpPoints, count nCount) override;
      bool rectangle(const ::rect & rect) override;
      //virtual bool draw_rect(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual bool DrawRectangle(const ::rect & rect) override;
      //virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2) override;
      //virtual bool FillRectangle(const ::rect & rect) override;
      //bool roundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3) override;
      bool round_rect(const ::rect & rect, const ::point & point) override;

      // Bitmap Functions
      //bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight) override;


      bool draw_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc) override;
      bool stretch_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc) override;


      ::color GetPixel(i32 x, i32 y) override;
      ::color GetPixel(const ::point & point) override;
      ::color SetPixel(i32 x, i32 y, const ::color & color) override;
      ::color SetPixel(const ::point & point, const ::color & color) override;
//      bool FloodFill(i32 x, i32 y, const ::color & color) override;
//      bool ExtFloodFill(i32 x, i32 y, const ::color & color, ::u32 nFillType) override;
//      bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                   i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
//                   u32 dwRop) override;
//      bool PlgBlt(POINT32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//                  i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask) override;
      bool SetPixelV(i32 x, i32 y, const ::color & color) override;
      bool SetPixelV(const ::point & point, const ::color & color) override;
//      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
//                        void * pMesh, WINULONG nMeshElements, u32 dwMode) override;
//      bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
//                          ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
//                          ::u32 clrTransparent) override;

      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool text_out(i32 x, i32 y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(i32 x, i32 y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const string & str) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const char * lpszString, strsize nCount, int * lpDxWidths) override;
      virtual bool ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const string & str, int * lpDxWidths) override;
      virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;
      virtual size TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, int * lpnTabStopPositions, i32 nTabOrigin) override;

#if defined(USE_PANGO)
      //virtual bool internal_draw_text_cairo(const block & block, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT pfnText = nullptr);
      virtual bool internal_draw_text_pango(const block & block, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_PANGO_TEXT pfnText = nullptr);
      virtual bool internal_draw_text(const block & block, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
#else
      virtual bool internal_draw_text(const char * lpszString, strsize nCount, const ::rectd & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, PFN_CAIRO_TEXT ftext);
#endif
      //virtual bool draw_text(const char * lpszString, strsize nCount, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;
      virtual bool draw_text(const string & str, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      //virtual bool draw_text_ex(char * lpszString, strsize nCount, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams);
      //virtual bool draw_text_ex(const string & str, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPDRAWTEXTPARAMS lpDTParams = nullptr) override;
      virtual bool draw_text_ex(const string & str, const ::rect & rect, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none) override;

      sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool _GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex);
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      size GetTabbedTextExtent(const string & str, count nTabPositions, int * lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, int * lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const string & str, count nTabPositions, int * lpnTabStopPositions) override;
      //virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight) override;
      ::u32 GetTextAlign() override;
      ::u32 SetTextAlign(::u32 nFlags) override;
      i32 GetTextFace(count nCount, char * lpszFacename) override;
      i32 GetTextFace(string & rString) override;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
//      i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount) override;
//      i32 GetTextCharacterExtra() override;
//      i32 SetTextCharacterExtra(i32 nCharExtra) override;

      //xxx      u32 GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;
      //xxx      u32 GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE32 LPSIZE32) override;
      bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE32 LPSIZE32) override;

#endif

//      // Advanced Drawing
//      bool DrawEdge(const ::rect & rect, ::u32 nEdge, ::u32 nFlags) override;
//      bool DrawFrameControl(const ::rect & rect, ::u32 nType, ::u32 nState) override;

//      // Scrolling Functions
//      bool ScrollDC(i32 dx, i32 dy, const ::rect & rectScroll, const ::rect & rectClip,
//                    ::draw2d::region* pRgnUpdate, LPRECT32 lpRectUpdate) override;

//      // font Functions
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      bool GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) override;
//      u32 SetMapperFlags(u32 dwFlag) override;
//      size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) override;
//      u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) override;
      //xxx      i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      ::u32 GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      u32 GetGlyphOutline(::u32 nChar, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none, LPGLYPHMETRICS lpgm,
      //xxx    u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar,
//      //xxx         LPABCFLOAT lpABCF) override;
//      bool GetCharWidth(::u32 nFirstChar, ::u32 nLastChar,
//                        float* lpFloatBuffer) override;
//
//      u32 GetFontLanguageInfo() override;
//
//#if (_WIN32_WINNT >= 0x0500)
//
//      bool GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) override;
//      bool GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) override;
//
//#endif
//
//      // Printer/Device Escape Functions
//      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData) override;
//      i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData) override;
//      i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData) override;
//
      // Escape helpers
      i32 StartDoc(const char * lpszDocName) override;  // old Win3.0 version
//xxx      i32 StartDoc(LPDOCINFO lpDocInfo) override;
      i32 StartPage() override;
      i32 EndPage() override;
      //i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32)) override;
      i32 AbortDoc() override;
      i32 EndDoc() override;

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const ::rect & rectBounds) override;
      //    bool AddMetaFileComment(::u32 nDataSize, const byte* pCommentData) override;
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
      //i32 GetPath(POINT32 * lpPoints, LPBYTE lpTypes, count nCount) override;
      bool SelectClipPath(i32 nMode) override;

      // Misc Helper Functions
      //static ::draw2d::brush* PASCAL GetHalftoneBrush(::layered * pobjectContext);
//      void DrawDragRect(const ::rect & rect, const ::size & size,
//                        const ::rect & rectLast, const ::size & sizeLast,
//                        ::draw2d::brush* pBrush = nullptr, ::draw2d::brush* pBrushLast = nullptr) override;
      //void fill_rect(const RECT64 * rect, color32_t clr) override;
      void fill_rect(const ::rect & rect, const ::color & color) override;
      void fill_rect(const ::rectd & rect, const ::color & color) override;
      //void fill_rect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr) override;
      void draw_3drect(const ::rect & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder = border_all) override;
      //void draw3d_rect(i32 x, i32 y, i32 cx, i32 cy,
      //              color32_t clrTopLeft, color32_t clrBottomRight) override;




      // Implementation
   public:
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      //      HGDIOBJ SelectObject(HGDIOBJ) override;      // do not use for regions

      virtual bool set_alpha_mode(::draw2d::enum_alpha_mode ealphamode) override;

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
      bool _set_os_color(color32_t cr);
      bool _set(::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool _set(::draw2d::pen * ppen);
#if !defined(USE_PANGO)
      bool _set(::draw2d::font * pfont);
#endif
      bool _set(::draw2d::path * ppath);

      bool _set(const ::point_array & pointa);
      bool _set(const ::pointd_array & pointa);

      bool _set(___shape * pshape);
      bool _set(const enum_shape & eshape);
      bool _set(const ::arc & arc);
      bool _set(const ::line & line);
      bool _set(const ::lined & line);
      bool _set(const ::lines & lines);
      bool _set(const ::linesd & lines);
      bool _set(const ::rect & rect);
      bool _set(const ::rectd & rect);
      bool _set(const ::polygon & polygon);
      bool _set(const ::polygond & polygond);
      bool _set(const ::text_out & textout);
      bool _set(const ::draw_text & textout);
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


      virtual bool flush() override;

#ifdef WINDOWS

      virtual bool attach_hdc(HDC hdc) override;
      virtual HDC detach_hdc() override;

#endif

      virtual void enum_fonts(::draw2d::font_enum_item_array & itema) override;

      virtual string get_font_path(string str);


      FT_Face ftface(const char* pszFontName);

      //virtual void on_apply_clip_region() override;


   };


   CLASS_DECL_AURA string q_valid_string(string str);


} // namespace win





