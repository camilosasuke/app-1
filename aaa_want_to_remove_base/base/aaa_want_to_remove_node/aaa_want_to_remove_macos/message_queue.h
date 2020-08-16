#pragma once


namespace macos
{


   class CLASS_DECL_BASE message_queue:
      virtual public ::user::message_queue,
      virtual public ::user::interaction
   {
   public:


      __pointer(::user::interaction)          m_spuiMessage;
      message_queue_listener *         m_plistener;


      message_queue(::object * pobject);
      virtual ~message_queue();


      virtual bool create_message_queue(const char * pszName,::user::message_queue_listener * plistener = nullptr);

      virtual void message_handler(::message::base * pbase);

      virtual void message_queue_message_handler(::message::message * pmessage);

      virtual bool message_queue_is_initialized();

      virtual bool message_queue_set_timer(uptr uiId,DWORD dwMillis);

      virtual bool message_queue_post_message(u32 uiMessage,WPARAM wparam = 0,lparam lparam = 0);

      virtual LRESULT message_queue_send_message(u32 uiMessage,WPARAM wparam = 0,lparam lparam = 0);

      virtual bool message_queue_del_timer(uptr uiId);

      virtual bool message_queue_destroy();

      virtual void * message_queue_get_os_handle();


   };


} // namespace windows

