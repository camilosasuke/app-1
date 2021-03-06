#pragma once


//#include "GLOBAL_ID.h"
//
//
//enum enum_property
//{
//
//   property_default = 0,
//   property_id,
//   property_count,
//
//};
//
//
//enum enum_factory
//{
//
//   factory_draw2d_bitmap,
//   factory_draw2d_brush,
//   factory_draw2d_font,
//   factory_draw2d_graphics,
//   factory_draw2d_image,
//   factory_draw2d_path,
//   factory_draw2d_pen,
//   factory_draw2d_region,
//   factory_count,
//
//};
//
//
//#define SUCCESS 1
//#define TIMEOUT (1 << 1)
//#define FAILURE (1 << 2)
//
//
//#define OK SUCCESS
//
//
//#define e_message_update WM_APP + 256
//#define e_message_system WM_APP + 257
//#define e_message_event WM_APP + 258
//
//
//
//#define NONE_ID 0
//#define INVALID_ID ((::u64) -1)
//
//
//
////#define e_object_success (1 << 0)
////#define e_object_timeout (1 << 1)
////#define e_object_failure (1 << 2)
////#define PERSIST_ID (1 << 3)
////#define e_object_factory (1 << 4)
////#define e_object_storing (1 << 5)
////#define e_object_acquire (1 << 6)
////#define DEFAULT_ID (1 << 7)
//
//
//#define FILEMANAGER_IMPACT 1'001'000
//#define COLORSEL_IMPACT 2'001'000
//#define FONTSEL_IMPACT 2'002'000
//
//#define TABBED_GROUP 100
//#define LIST_GROUP 200
//#define FOLDER_SELECTION_LIST_GROUP 300
//
//
//#define MAIN_IMPACT 1
//#define A2_IMPACT 2
//#define CONTEXT_MENU_IMPACT 3
//#define MENU_IMPACT 4
//#define MAIN_SWITCHER_IMPACT 5
//#define DEVEDGE_IMPACT 6
//#define GCOM_IMPACT 7
//#define OPTIONS_IMPACT 8
//#define EDIT_IMPACT 9
//#define WEATHER_IMPACT 10
//#define AUDIO_DEVICES_IMPACT 11
//#define TEST_IMPACT 12
//#define ACTION_AREA_IMPACT 13
//#define DESK_IMPACT 14
//#define CONFIGURATION_IMPACT 15
//#define PROPERTIES_IMPACT 16
//#define HELP_IMPACT 17
//
//
//
//
//
//
//enum e_lib_main
//{
//
//   lib_main_none = 0,
//   lib_main_any = 1 << 0,
//   lib_main_process_attach = 1 << 1,
//   lib_main_process_detach = 1 << 2,
//   lib_main_thread_attach = 1 << 3,
//   lib_main_thread_detach = 1 << 4,
//
//};
//
//
//
//
//enum e_default_init
//{
//
//   default_init
//
//};
//
//
//enum enum_type
//{
//   /// special meaning
//   type_parareturn = 0,
//   type_new,
//   e_type_null,
//   type_key_exists,
//   type_empty,
//   type_empty_argument,
//   type_not_found,
//
//   // integral
//   //type_block = 1000,
//   type_bool,
//   type_pbool,
//   type_char,
//   type_i8 = type_char,
//   type_pi8,
//   type_byte,
//   type_u8 = type_byte,
//   type_pu8,
//   type_i16,
//   type_pi16,
//   type_u16,
//   type_pu16,
//   type_i32,
//   type_pi32,
//   type_u32,
//   type_pu32,
//   type_i64,
//   type_pi64,
//   type_u64,
//   type_pu64,
//
//   // floating point
//   type_float = 2000,
//   type_pfloat,
//   type_double,
//   type_pdouble,
//
//   // simple classes
//   type_string = 4000,
//   type_pstring,
//   type_type,
//   type_duration,
//   type_pduration,
//   type_id,
//   type_pid,
//   type_time,
//   type_filetime,
//   type_prop,
//   type_pvar,
//   type_routine,
//   type_callback,
//
//   // context_object classes
//   type_element = 8000,
//   type_stra,
//   type_inta,
//   type_vara,
//   type_propset,
//   type_i64a,
//   type_memory,
//   type_path,
//   type_image,
//   __type_last_element,
//
//   // enum
//   type_enum_command = 20000,
//   type_enum_status,
//   type_enum_check,
//
//};
//
//enum e_trace_category
//{
//   trace_category_general,
//   trace_category_first = trace_category_general,
//   trace_category_com,
//   trace_category_qi,
//   trace_category_registrar,
//   trace_category_refcount,
//   trace_category_windowing,
//   trace_category_controls,
//   trace_category_hosting,
//   trace_category_dbclient,
//   trace_category_dbprovider,
//   trace_category_snapin,
//   trace_category_notimpl,
//   trace_category_allocation,
//   trace_category_exception,
//   trace_category_time,
//   trace_category_cache,
//   trace_category_stencil,
//   trace_category_string,
//   trace_category_map,
//   trace_category_util,
//   trace_category_security,
//   trace_category_sync,
//   trace_category_isapi,
//   trace_category_user,
//   trace_category_user2,
//   trace_category_user3,
//   trace_category_user4,
//   trace_category_appmsg,        // main message pump trace (includes dde)
//   trace_category_winmsg,        // windows message tracing
//   trace_category_cmdrouting,    // windows command routing trace
//   trace_category_ole,          // special ole callback trace
//   trace_category_database,     // special database trace
//   trace_category_internet,     // special internet client trace
//   trace_category_dumpcontext,   // traces from dump_context
//   trace_category_memory,      // matter non-kernel memory traces
//   trace_category_html,         // html traces
//   trace_category_socket,      // socket traces
//   trace_category_colorertake5,
//   trace_category_prodevian, // screen update and window layout
//   trace_category_count
//
//};
//
//enum e_trace_level
//{
//
//   trace_level_none,
//   trace_level_information, // info
//   trace_level_warning,     // warn
//   trace_level_error,       // error
//   trace_level_fatal,       // fatal
//   trace_level_count
//
//};
//
//enum e_cursor
//{
//
//   cursor_unmodified,
//   cursor_draw2d,
//   cursor_default,
//   cursor_none,
//   cursor_system,
//   cursor_arrow,
//   cursor_hand,
//   cursor_text_select,
//   cursor_size_top_left,
//   cursor_size_top,
//   cursor_size_top_right,
//   cursor_size_right,
//   cursor_size_bottom_right,
//   cursor_size_bottom,
//   cursor_size_bottom_left,
//   cursor_size_left,
//   cursor_size_vertical,
//   cursor_size_horizontal,
//   cursor_move
//
//};
//
//enum enum_object : i64
//{
//
//   e_object_none,
//   e_object_success = 1 << 0,
//   e_object_timeout = 1 << 1,
//   e_object_failure = 1 << 2,
//   e_object_persist = 1 << 3,
//   e_object_factory = 1 << 4,
//   e_object_storing = 1 << 5,
//   e_object_acquire = 1 << 6,
//   e_object_default = 1 << 7,
//   e_object_synchro = 1 << 8,
//   aaa_want_to_remove_object_locked = 1 << 9,
//   aaa_want_to_remove_object_shared = 1 << 10,
//   aaa_want_to_remove_object_read_only_link = 1 << 11,
//   e_object_log_disable = 1 << 12,
//   e_object_property_set_modified = 1 << 13,
//   //e_object_default_property_exchange = 1 << 14, //
//   e_object_default_io_exchange = 1 << 15,
//   e_object_alertable_wait = 1 << 16,
//#if OBJ_TYP_CTR
//   e_object_obj_typ_ctr = 1 << 17,
//#endif
//
//};
//
//
//#define ALOG_CATEGORY trace_category_general
//
//
//#include "status.h"
//
//
//
//enum e_priority
//{
//
//   priority_none = -1,
//   priority_idle = 1,
//   priority_lowest = 48,
//   priority_below_normal,
//   priority_normal,
//   priority_above_normal,
//   priority_highest,
//   priority_time_critical = 99
//
//};
//
////bool CLASS_DECL_AURA succeeded(const ::estatus & estatus);
////bool CLASS_DECL_AURA status_succeeded(i64 i);
////bool CLASS_DECL_AURA failed(const ::estatus & estatus);
////bool CLASS_DECL_AURA status_failed(i64 i);
//
//enum e_thread
//{
//
//   thread_none,
//   thread_thread,
//   thread_service,
//   thread_application,
//   thread_session,
//   thread_system,
//
//};
//
//
//enum enum_timer : i64;
//
//enum e_set
//{
//
//   // negative state... bad/failure states
//
//   set_no = -1, // 0xffffffff......
//   set_false = -1,
//
//   set_none = 0,
//   set_empty = 0, // 0x00000000......
//   set_undefined = 0,
//
//   set_yes = 1, // <3tbs
//   set_true = 1, // 0x00000001......
//
//   // positive state... good/success states
//
//};
//
//
//
//
//enum e_clock
//{
//
//   clock_none,
//   clock_slow, // indicative usage: few minutes
//   clock_fast, // indicative usage: few seconds or big second fraction
//
//};
//
//
//
//
//
//
//
//
//enum e_zorder
//{
//
//   zorder_none = 0,
//   zorder_bottom,
//   zorder_normal_anchor,
//   zorder_normal,
//   zorder_top,
//   zorder_no_top_most,
//   zorder_top_most_anchor,
//   zorder_top_most,
//
//   zorder_hwnd = -1,
//
//
//};
//
//
//enum e_callstack :
//   i64
//{
//
//   callstack_none,
//   callstack_exception = 1 << 0,
//   callstack_fork_global = 1 << 1,
//
//};
//
//
////#define __epromisse(e, mod) ((e_promisse)((i64)(promisse_##e) + (i64) mod))
//
//
//
//
//
//
//enum e_unit_size
//{
//
//   unit_size,
//
//};
//
//
//enum enum_display
//{
//
//   e_display_undefined = MINI32,
//   e_display_notify_icon,
//   e_display_default,
//   //display_close,
//   e_display_hide,
//
//   e_display_none = 0,
//   e_display_current,
//   e_display_normal,
//   e_display_restore,
//   e_display_compact,
//   e_display_broad,
//   e_display_iconic,
//   e_display_zoomed,
//   e_display_full_screen,
//   e_display_up,
//   e_display_down,
//   e_display_minimal,
//   e_display_fixed_size,
//   e_display_center,
//
//
//   e_display_left = 0x1000,
//   e_display_top = 0x2000,
//   e_display_right = 0x4000,
//   e_display_bottom = 0x8000,
//   e_display_top_left = e_display_top | e_display_left,
//   e_display_top_right = e_display_top | e_display_right,
//   e_display_bottom_left = e_display_bottom | e_display_left,
//   e_display_bottom_right = e_display_bottom | e_display_right,
//   e_display_full_left = e_display_left | e_display_top | e_display_bottom,
//   e_display_full_top = e_display_top | e_display_left | e_display_right,
//   e_display_full_right = e_display_right | e_display_top | e_display_bottom,
//   e_display_full_bottom = e_display_bottom | e_display_left | e_display_right,
//
//   e_display_docking_mask = 0xff00,
//
//   e_display_command_mask = 0xffff,
//
//};
//
//
//enum enum_activation
//{
//
//   e_activation_default = 0,
//   e_activation_no_activate = 1 << 0,
//   e_activation_set_active = 1 << 1,
//   e_activation_set_foreground = 1 << 2,
//   e_activation_under_mouse_cursor = 1 << 3,
//   e_activation_on_center_of_screen = 1 << 4,
//   e_activation_display_change = 1 << 5,
//
//};
//
//
//enum e_layout_experience
//{
//
//   layout_experience_none,
//   layout_experience_moving,
//   layout_experience_sizing,
//   layout_experience_docking,
//
//};
//
//
//enum enum_appearance
//{
//
//   e_appearance_none = 0,
//   e_appearance_transparent_frame = 1 << 0,
//
//};
//
//
//
//
//enum e_dock
//{
//   dock_none = 0,
//   dock_left = 1,
//   dock_top = 2,
//   dock_right = 4,
//   dock_bottom = 8,
//   dock_top_left = dock_top | dock_left,
//   dock_top_right = dock_top | dock_right,
//   dock_bottom_left = dock_bottom | dock_left,
//   dock_bottom_right = dock_bottom | dock_right,
//   dock_all = dock_left | dock_top | dock_right | dock_bottom,
//};
//
//enum e_grip
//{
//   grip_none = 0,
//   grip_left = 1 << 0,
//   grip_top = 1 << 1,
//   grip_right = 1 << 2,
//   grip_bottom = 1 << 3,
//   grip_top_left = 1 << 4,
//   grip_top_right = 1 << 5,
//   grip_bottom_left = 1 << 6,
//   grip_bottom_right = 1 << 7,
//   grip_all = grip_left | grip_top | grip_right | grip_bottom |
//   grip_top_left | grip_top_right |
//   grip_bottom_left | grip_bottom_right,
//};
//
//
//enum e_border
//{
//
//   border_none = 0,
//   border_left = 1,
//   border_top = 2,
//   border_right = 4,
//   border_bottom = 8,
//   border_top_left = border_top | border_left,
//   border_top_right = border_top | border_right,
//   border_top_right_bottom = border_top | border_right | border_bottom,
//   border_bottom_left = border_bottom | border_left,
//   border_bottom_right = border_bottom | border_right,
//   border_bottom_left_top = border_bottom | border_left | border_top,
//   border_left_top_right = border_left | border_top | border_right,
//   border_right_bottom_left = border_right | border_bottom | border_left,
//   border_all = border_left | border_top | border_right | border_bottom,
//
//};
//
//
//
//enum e_window_flag
//{
//
//   window_flag_none,
//   window_flag_is_window = 1 << 0,
//   window_flag_enable = 1 << 1,
//   window_flag_focus = 1 << 2,
//   window_flag_active = 1 << 3,
//   window_flag_redraw_in_queue = 1 << 4,
//   window_flag_visual_changed = 1 << 5,
//   window_flag_auto_prodevian_on_show = 1 << 6,
//   window_flag_on_show_window_visible = 1 << 7,
//   window_flag_on_show_window_screen_visible = 1 << 8,
//   window_flag_satellite_window = 1 << 9,
//   window_flag_graphical = 1 << 10,
//   window_flag_disable_window_placement_snapping = 1 << 11,
//   window_flag_embedded_prodevian = 1 << 12,
//   window_flag_arbitrary_positioning = 1 << 13,
//   window_flag_desktop_window = 1 << 14,
//   window_flag_dock_window = 1 << 15,
//   window_flag_load_window_rect_on_impl = 1 << 17,
//   window_flag_window_created = 1 << 18,
//   window_flag_updown = 1 << 19,
//   window_flag_postpone_visual_update = 1 << 20,
//   window_flag_miniaturizable = 1 << 21,
//   window_flag_auto_store_window_rect = 1 << 22,
//   window_flag_pending_save_window_rect = 1 << 23,
//   window_flag_loading_window_rect = 1 << 24,
//   window_flag_main_frame = 1 << 25,
//
//};
//
//
//#ifndef WM_USER
//#define WM_USER 0x0400
//#endif // WM_USER
//
//#ifndef CLASS_DECL_AURA
//#define CLASS_DECL_AURA
//#endif // CLASS_DECL_AURA
//#ifndef WM_APP
//#define WM_APP 0x8000
//#endif
//
//
//
//
//enum e_system_message
//{
//
//   system_message_none,
//   system_message_create,
//   system_message_meta,
//   system_message_pred,
//   system_message_runnable,
//
//};
//
//
///*
//
//
//enum enum_procedure
//{
//
//   e_routine_create,
//   e_routine_destroy,
//
//};
//
//
//enum enum_callback
//{
//
//   e_callback_finish,
//   e_callback_dialog_result,
//   e_callback_complete,
//
//};
//
//
//*/
//
//#ifndef WINDOWS_DESKTOP
//#include "aura/os/cross/windows/message_box.h"
//#endif
//
//
//enum enum_message_box
//{
//
//   e_message_box_ok = e_message_box_ok,
//   e_message_box_yes_no = MB_YESNO,
//   e_message_box_yes_no_cancel = MB_YESNOCANCEL,
//   e_message_box_icon_error = MB_ICONERROR,
//   e_message_box_icon_exclamation = e_message_box_icon_exclamation,
//   e_message_box_icon_question = MB_ICONQUESTION,
//   e_message_box_icon_asterisk = MB_ICONASTERISK,
//   e_message_box_icon_hand = e_message_box_icon_error,
//   e_message_box_icon_warning = e_message_box_icon_exclamation,
//   e_message_box_icon_information = e_message_box_icon_asterisk,
//   e_message_box_icon_stop = e_message_box_icon_asterisk,
//
//};



