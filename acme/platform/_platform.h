#pragma once


//#include "match.h"

//#include "history.h"

//#include "theme.h"

//#include "os_history.h"

//#include "strn.h"

//#include "process_data.h"

#include "profiler.h"


//
//#pragma once
//
//
//#include "acme/_.h"

//
//#ifdef _CORE_LIBRARY
//#define CLASS_DECL_ACME  CLASS_DECL_EXPORT
//#else
//#define CLASS_DECL_ACME  CLASS_DECL_IMPORT
//#endif


#ifndef __PARTIAL_CPP

class image_list;


#ifdef WINDOWS

interface ID2D1DeviceContext;

#endif

namespace user
{

   class printer;
   //class tree;
   //class form;
   class single_document_template;
   class main_frame;



} // namespace user


namespace experience
{

   class frame_window;

} // namespace experience


class service_base;


namespace bergedge
{


   class document;
   class view;


} // namespace bergedge


namespace filehandler
{


   class handler;


} // namespace filehandler


namespace html
{


   class html_ex;


} // namespace html


namespace userfs
{

   
   class userfs;


} // namespace userfs


namespace userex
{


   class userex;
   //class pane_tab_view;


} // namespace userex


namespace filemanager
{


   class document;
   class data;
   //class filemanager;


} // namespace filemanager


namespace user
{


   //class impact_data;
   class form_callback;
//   class split_view;

   class combo_box;
   class combo_list;


} // namespace user





namespace dynamic_source
{


   class script;
   class script_manager;


} // namespace dynamic_source










namespace acme
{

   //class run_start_installer;

   CLASS_DECL_ACME bool init_core();

   CLASS_DECL_ACME bool term_core();


} // namespace acme








//class task;




#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;


#include "const.h"


//#include "core/user/userex/const.h"


//#include "strn.h"


#include "less.h"


//#include "smart_pointer_query.h"


#define ASSERT_KINDOF(class_name, matter) ASSERT(base_class < class_name > ::bases(matter))
#define DYNAMIC_CAST(class_name, matter) (dynamic_cast < class_name * > (matter))
#define ZERO_INIT_JUST_THIS(base_class) __memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));


#include "constraint.h"

//
//class resource_exception;
//class user_exception;
//namespace acme
//{
//   class menu;                 // a menu
//
//}
//
//namespace draw2d
//{
//   class graphics;                   // a Display Context / HDC wrapper
//   class matter;            // ::draw2d::graphics_pointer drawing tool
//   class bitmap;           // a bitmap
//   class palette;          // a palette
//   class region;
//   class font;
//   class pen;
//   class brush;
//   class memory_graphics;         // ::draw2d::graphics_pointer for client of window
//   class window_graphics;         // ::draw2d::graphics_pointer for entire window
//   class paint_graphics;          // embeddable BeginPaint struct helper
//}
//
//namespace acme
//{
//   class job;
//}
//
//class channel;            // a target for ::account::user commands
//
//namespace user
//{
//   class plain_edit;            // Edit control
//   class document_manager;      // impact_system manager matter
//   class frame_window;        // standard SDI frame
//   class interaction_child;
//   class combo_box;        // ComboBox control
//} // namespace user
//
//
//namespace math
//{
//
//
//   class math;
//
//
//} // namespace math
//
//namespace geometry
//{
//
//   class geometry;
//
//} // namespace geometry
//class dialog;          // a dialog
//
////// standard windows controls
////class CStatic;          // Static control
////class CListBox;         // ListBox control
////class CCheckListBox;// special listbox with checks
////class CScrollBar;       // ScrollBar control
////
////// frame windows
////class CMDIFrameWnd; // standard MDI frame
////class CMDIChildWnd; // standard MDI child
////class CMiniFrameWnd;// half-height caption frame wnd
////
////// views on a document
////class CScrollView;  // a scrolling ::user::impact
//
///*class single_document_template;
//class multiple_document_template;
//*/
//
////namespace user
////{
////
////   class user;
////
////
////} // namespace user
////


//#include "history.h"

//#include "os_history.h"


namespace acme
{


   CLASS_DECL_ACME void format_strings(string& rString, const char* pszFormat, const char* const* rgpsz, i32 nString);

   CLASS_DECL_ACME bool extract_sub_string(string& rString, const char* pszFullString, i32 iSubString, char chSep = '\n');


}


//#include "process_data.h"

//#include "types.h"

//#include "progress_interface.h"

#include "debug.h"

#include "acme/primitive/collection/std_iterator.h"
#include "acme/primitive/collection/insert_iterator.h"
#include "acme/primitive/collection/back_insert_iterator.h"
#include "acme/primitive/collection/std_pair.h"


#include "muldiv32.h"


#include "logic.h"

//#include "util1.h"

//#include "app/acme/math/math_math.h"

//#include "theme.h"

//#include "app/acme/user/_.h"

#include "debug.h"

//#include "acme/filesystem/filehandler/filehandler.h"

//#include "patch.h"

//#include "filesystem/filemanager/callback.h"
//
//#include "filesystem/filemanager/item_action.h"
//

//#include "acme/math/math_math.h"



#endif


//#include "str_context.h"



