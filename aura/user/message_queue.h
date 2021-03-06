﻿#pragma once


namespace user
{


   class CLASS_DECL_AURA message_queue:
      virtual public message_queue_listener,
      virtual public ::user::interaction
   {
   public:


      __pointer(message_queue_listener)      m_plistener;


      message_queue();
      virtual ~message_queue();


      virtual bool create_message_queue(const char * pszName,::user::message_queue_listener * plistener = nullptr);

      virtual void message_handler(::message::base * pbase);

      virtual void message_queue_message_handler(::message::message * pmessage);

      virtual bool message_queue_is_initialized();

      virtual bool message_queue_set_timer(uptr uId,::u32 dwMillis);

      virtual bool message_queue_post_message(const ::id & id, WPARAM wparam = 0,lparam lparam = 0);

      virtual LRESULT message_queue_send_message(const ::id & id, WPARAM wparam = 0,lparam lparam = 0);

      virtual bool message_queue_del_timer(uptr uId);

      virtual bool message_queue_destroy();

      virtual void * message_queue_get_os_handle();

   };


   typedef __pointer(message_queue) message_queue_pointer;


} // namespace aura




















