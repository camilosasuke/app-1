#pragma once



class mq;


typedef isomap < ITHREAD, __pointer(thread) > thread_map;


///
/// a thread must be always allocated in the heap
///
class CLASS_DECL_AURA thread :
   virtual public channel
#ifdef WINDOWS
   ,virtual public ::exception::translator
#endif
{
public:


   class CLASS_DECL_AURA file_info :
      virtual public object
   {
   public:


      file_info();
      ~file_info();

      ::duration                             m_durationFileSharingViolationTimeout;

   };


   __composite(mq)                                    m_pmq;
   bool                                               m_bClosedMq;


   __pointer(::thread)                                m_pthreadParent;
   __pointer_array(::thread)                          m_threada;
   MESSAGE                                            m_message;
   bool                                               m_bLastingThread;
   bool                                               m_bMessageThread;
   string                                             m_strThreadName;
   string                                             m_strThreadTag;
   bool                                               m_bFork;
   bool                                               m_bDedicated;
   bool                                               m_bAvoidProcFork;
   bool                                               m_bThreadToolsForIncreasedFps;
   ::estatus                                          m_estatus;
   user_interaction_ptr_array *                       m_puiptraThread;
   ::mutex *                                          m_pmutexThreadUiPtra;
   single_lock *                                      m_pslUser;
   static bool                                        s_bAllocReady;

#ifdef __DEBUG
   char *                                             m_pszDebug;
#endif

   __pointer(manual_reset_event)                      m_pevent;
   __pointer(manual_reset_event)                      m_pevStarted;
   __pointer(manual_reset_event)                      m_pevSync;
   __pointer(manual_reset_event)                      m_pevReady;

   bool                                               m_bAuraMessageQueue;
   ::tick                                             m_tickHeartBeat;
   bool                                               m_bReady;
   ::status::result                                   m_result;
   __pointer(::user::primitive)                       m_puiMain1;           // Main interaction_impl (usually same System.m_puiMain)
   __pointer(::user::primitive)                       m_puiActive;         // Active Main interaction_impl (may not be m_puiMain)
   string                                             m_strWorkUrl;
   bool                                               m_bSimpleMessageLoop;
   bool                                               m_bZipIsDir2;

   __pointer(file_info)                               m_pfileinfo;
   __pointer(counter)                                 m_pcounter;

   bool                                               m_bDupHandle;
   HTHREAD                                            m_hthread;
   ITHREAD                                            m_uThread;

   string                                             m_strDebugType;

   address_array < ::user::frame * >                  m_frameptra;


   UINT                                               m_nDisablePumpCount;

   UINT                                               m_dwFinishTimeout;
   bool                                               m_bThreadClosed;

   object_array                                       m_objectaTask;


   __pointer(manual_reset_event)                      m_pevent1;
   e_priority                                         m_epriority;


   string                                             m_strDebug;
   string                                             m_strFile;
   int                                                m_iLine;

   DWORD_PTR                                          m_dwThreadAffinityMask;
   bool                                               m_bTemporary;
   __pointer(manual_reset_event)                      m_pevSleep;
   __pointer(::object)                                m_pobjectScript;


#ifdef MACOS

   array < CFRunLoopSourceRef >                       m_runloopsourcea;
   CFRunLoopRef                                       m_runloop;

#endif

#ifdef WINDOWS

   bool                                               m_bCoInitialize;
   HRESULT                                            m_hresultCoInitialize;

#endif

   __pointer_array(event)                             m_eventaWait;

protected:

   bool                                               m_bRunThisThread;

public:


   thread();
   virtual ~thread();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   inline mq* get_mq() { return m_pmq ? m_pmq : _get_mq(); }
   mq* _get_mq();

   int_bool peek_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
   int_bool get_message(LPMESSAGE pMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);
   int_bool post_message(oswindow oswindow, UINT uMessage, WPARAM wParam, LPARAM lParam);

   user_interaction_ptr_array & uiptra();

//#ifdef WINDOWS_DESKTOP
//
//   virtual void associate_imc(::user::interaction* pinteraction);
//
//#endif

   void add_waiting_event(event * pevent);
   void remove_waiting_event(event * pevent);

   // file related stuff
   file_info * get_file_info();
   DWORD get_file_sharing_violation_timeout_total_milliseconds();
   ::duration set_file_sharing_violation_timeout(::duration duration);


   //virtual void dependant_add(::object * pobject) override;

   ///  \brief    starts thread on first call
   virtual void start();

   virtual void * get_os_data() const;
   virtual ITHREAD get_os_int() const;

   virtual void SetCurrentHandles();

   virtual HTHREAD get_os_handle() const;

   virtual bool thread_active() const;
   virtual bool is_dedicated_thread() const;
   virtual bool is_thread() const override;
   virtual bool is_running() const override;

   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(ITHREAD iData);


   friend bool __internal_pre_translate_message(MESSAGE * pMsg);


   void thread_common_construct();

   virtual void on_keep_alive() override;
   virtual bool is_alive() override;


   virtual int get_x_window_count() const;

   virtual sync_result wait(const duration & duration);

   bool set_thread_priority(::e_priority epriority);

   ::e_priority thread_priority();

   virtual bool set_thread_name(const char * pszName);

   //inline ::command::command * command() { return m_pcommand; }
   //inline ::command::command * command() const { return ((thread *)this)->m_pcommand; }
   //virtual ::command::command * get_command();

   //inline bool has_property(const ::id& id) const;
   //inline var command_value(const ::id& id) const;
   //inline bool command_value_is_true(const ::id& id) const;


   virtual u32 ResumeThread();
   virtual bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);

   virtual bool send_message(UINT message,WPARAM wParam = 0,lparam lParam = 0, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_object(UINT message, WPARAM wParam, lparam lParam);

   virtual bool send_object(UINT message, WPARAM wParam, lparam lParam, ::duration durationTimeout = ::duration::infinite());

   virtual bool post_task(::generic_object * pobjectTask);
   virtual bool send_task(::generic_object * pobjectTask, ::duration durationTimeout = ::duration::infinite());

   template < typename PRED >
   bool pred(PRED pred)
   {
      return post_runnable(__runnable(pred));
   }

   template < typename PRED >
   bool post_pred(PRED pred)
   {
      return post_object(SYSTEM_MESSAGE, system_message_pred, __new(pred_holder < PRED >(get_context_application(), pred)));
   }

   template < typename PRED >
   bool send_pred(PRED pred, ::duration durationTimeout = ::duration::infinite())
   {
      return send_object(SYSTEM_MESSAGE, system_message_pred, __new(pred_holder < PRED >(get_context_application(), pred)), durationTimeout);
   }

   template < typename PRED >
   bool schedule_pred(__pointer(::context_object) phold, PRED pred)
   {
      return post_pred(phold, pred);
   }

   template < typename PRED >
   bool schedule_pred(PRED pred)
   {
      return post_pred(pred);
   }

   template < typename PRED >
   bool synch_pred(__pointer(object) phold, PRED pred, ::duration durationTimeout = ::duration::infinite())
   {
      if (this == ::get_thread())
      {
         pred();
         return true;
      }
      return send_pred(phold, pred, durationTimeout);
   }

   template < typename PRED >
   bool synch_pred(PRED pred, ::duration durationTimeout = ::duration::infinite())
   {
      if (this == ::get_thread())
      {
         pred();
         return true;
      }
      return send_pred(pred, durationTimeout);
   }


   //virtual bool final_handle_exception(::exception_pointer e);
   __pointer(::object) running(const char * pszTag) const override;

   ///virtual void relay_exception(::exception_pointer e, e_thread ethreadSource = thread_none);
   virtual int _GetMessage(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

   virtual bool has_step() const;
   virtual bool has_raw_message() const;
   virtual bool has_message() const;

   // running and idle processing
   virtual void pre_translate_message(::message::message * pmessage);
   virtual void app_pre_translate_message(::message::message * pmessage);
   virtual void session_pre_translate_message(::message::message * pmessage);
   virtual void system_pre_translate_message(::message::message * pmessage);
   virtual ::estatus thread_loop(); // low level thread loop
   virtual bool thread_step();     // low level step
   virtual bool pump_message();     // low level message pump
   virtual bool pump_runnable();
   virtual bool get_message();     // low level message pump
   virtual bool raw_pump_message();     // low level message pump
   virtual bool defer_pump_message();     // deferred message pump
   virtual void process_message(::message::base * pbase);
   virtual void process_thread_message(::message::base * pbase);
   virtual void process_window_message(::message::base * pbase);
   virtual bool process_message();     // route message
   virtual bool raw_process_message();     // route message
   // virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   virtual bool on_thread_on_idle(::thread * pthread, LONG lCount);
   virtual bool is_idle_message(::message::message * pmessage);  // checks for special messages
   virtual bool is_idle_message();  // checks for special messages

   virtual ::estatus init_thread();
   virtual ::estatus on_pre_run_thread();

   virtual ::estatus run() override;

   virtual void on_pos_run_thread();
   virtual void term_thread();

   virtual void process_window_procedure_exception(::exception_pointer pe, ::message::message * pmessage);

   virtual void process_message_filter(i32 code, ::message::message * pmessage);

   // virtual void add(::user::primitive * pinteraction);
   //virtual void remove(::user::primitive * pinteraction);
   //virtual ::count get_ui_count();
   //virtual ::user::primitive * get_ui(index iIndex);
   //virtual void set_timer(::user::primitive * pinteraction, uptr nIDEvent, UINT nEllapse);
   //virtual void unset_timer(::user::primitive * pinteraction, uptr nIDEvent);
   //virtual void set_auto_delete(bool bAutoDelete = true);
   virtual ::user::primitive * get_active_ui();
   virtual ::user::primitive * set_active_ui(::user::primitive * pinteraction);
   //virtual void step_timer();
   //virtual bool on_run_step();


   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   virtual void dispatch_thread_message(::message::message * pmessage);  // helper


   virtual ::estatus     main();


   virtual void wait();


   virtual iptr item() const;



   virtual ::estatus verb();


   virtual void post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam);



   //virtual bool register_dependent_thread(::thread * pthread);
   //virtual void unregister_dependent_thread(::thread * pthread);
   //virtual bool on_register_dependent_thread(::thread * pthread);
   //virtual void on_unregister_dependent_thread(::thread * pthread);
   //virtual void signal_close_dependent_threads();
   //virtual void wait_close_dependent_threads(const duration & duration);
   //virtual bool register_at_required_threads();
   //virtual void unregister_from_required_threads();
   //virtual void close_dependent_threads(const ::duration & dur);


   virtual bool do_events();
   //virtual bool do_events(const duration & duration);

   virtual string get_tag() const override;
   virtual bool thread_get_run() const override;
   virtual bool set_run();
   virtual void finalize() override;
   virtual bool is_set_finish() const;
   virtual void set_finish() override;
   virtual void kick_idle();
   virtual void post_quit();

   virtual bool thread_add(::thread * pthread);
   virtual void thread_remove(::thread * pthread);
   //virtual void wait_quit(::duration durationTimeout) override;

   virtual bool kick_thread();

   //virtual void defer_add_thread_run_wait(sync_array & soa);

   virtual void message_queue_message_handler(::message::base * pmessage);

   //DECL_GEN_SIGNAL(_001OnSendThreadMessage);
   //DECL_GEN_SIGNAL(_001OnThreadMessage);


   virtual void shutdown(bool bPrompt = true);

   virtual bool on_before_shutdown();

   virtual bool is_application() const;
   virtual bool is_session() const;
   virtual bool is_system() const;

   //virtual void delete_this();

   virtual bool on_get_thread_name(string& strThreadName);

   /// thread implementation
   virtual ::estatus on_thread_init();
   virtual ::estatus on_thread_term();
   //virtual ::estatus     on_thread_end();
   //virtual void thread_delete();
   operator HTHREAD() const;


   virtual ::estatus initialize(::object * pobjectContext) override;


   //virtual ::estatus __thread_proc() override;


   virtual ::estatus osthread_init() override;
   virtual ::estatus __thread_init() override;
   virtual ::estatus __thread_main() override;
   virtual ::estatus __thread_term() override;
   virtual ::estatus osthread_term() override;


   virtual bool begin_thread(
   bool bSynchInitialization = false,
   ::e_priority epriority = ::priority_normal,
   UINT nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);



   virtual bool begin(
   ::e_priority epriority = ::priority_normal,
   UINT nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);


   virtual bool begin_synch(
   ::e_priority epriority = ::priority_normal,
   UINT nStackSize = 0,
   u32 uiCreateFlags = 0,
   LPSECURITY_ATTRIBUTES psa = nullptr);


   virtual ::estatus inline_init();
   virtual ::estatus inline_term();



   virtual bool initialize_message_queue();

   virtual void message_handler(::message::base * pbase);

   virtual ::estatus     do_request(::create * pcreate) override;

   virtual ::estatus     get_result_status();

   virtual void delete_this() override;


protected:


   virtual void __priority_and_affinity();
   virtual void __os_initialize();
//   virtual ::estatus __os_thread_start();
   virtual void __set_thread_on();
   virtual void __os_finalize();
  // virtual ::estatus __os_thread_end();

   // last called function for the thread lifetime.
   // after its call, the thread object must considered invalid/destroyed
   virtual void __set_thread_off();


};


namespace multithreading
{


   CLASS_DECL_AURA void set_finish();
   CLASS_DECL_AURA bool post_quit_and_wait(const duration & duration);


   CLASS_DECL_AURA void set_finish(::thread * pthread);
   CLASS_DECL_AURA bool post_quit_and_wait(::thread * pthread, const duration & duration);


   template < typename THREAD >
   void set_finish(__pointer(THREAD) & spthread)
   {

      if (spthread.is_set())
      {

         ::multithreading::set_finish(spthread.m_p);

         spthread.release();

      }

   }


   template < typename THREAD >
   bool post_quit_and_wait(__pointer(THREAD) & spthread, const duration & duration)
   {

      if (spthread.is_set())
      {

         if (!::multithreading::post_quit_and_wait(spthread.m_p, duration))
         {

            return false;

         }

         spthread.release();

      }

      return true;

   }




} // namespace multithreading


using id_thread_map = id_map < __pointer(thread) >;


CLASS_DECL_AURA void sleep(const duration& duration);


CLASS_DECL_AURA bool is_active(::thread * pthread);



CLASS_DECL_AURA bool is_thread_on(ITHREAD id);
CLASS_DECL_AURA void set_thread_on(ITHREAD id);
CLASS_DECL_AURA void set_thread_off(ITHREAD id);



CLASS_DECL_AURA bool thread_sleep(tick tick, sync * psync = nullptr);
CLASS_DECL_AURA bool thread_pump_sleep(tick tick, sync * psync = nullptr);
CLASS_DECL_AURA bool app_sleep(tick tick);




template < typename PRED >
inline ::sync_result while_pred_Sleep(int iTime, PRED pred)
{

   iTime += 99;

   iTime /= 100;

   for (index i = 0; i < iTime; i++)
   {

      Sleep(100);

      if (!pred())
      {

         return  ::sync_result::result_event0;

      }

      if (!::thread_get_run())
      {

         return ::sync_result::result_abandon0;

      }

   }

   return ::sync_result::result_timeout;

}


CLASS_DECL_AURA void defer_create_thread(::object * pobjectContext);


CLASS_DECL_AURA void thread_name_abbreviate(string & strName, int len);


