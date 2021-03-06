#pragma once


namespace acme
{


   class CLASS_DECL_ACME system :
      virtual public ::promise::handler,
      virtual public ::task
   {
   public:


      ::mutex                                            m_mutexTask;
      task_map                                           m_taskmap;
      task_id_map                                        m_taskidmap;
      ::mutex                                            m_mutexTaskOn;
      isomap < ithread_t, ithread_t >                    m_mapTaskOn;


      ::apex::system *                                   m_papexsystem;
      ::aqua::system *                                   m_paquasystem;
      ::aura::system *                                   m_paurasystem;
      ::axis::system *                                   m_paxissystem;
      ::base::system *                                   m_pbasesystem;
      ::bred::system *                                   m_pbredsystem;
      ::core::system *                                   m_pcoresystem;

      string                                             m_strOsUserTheme;

      system();
      virtual ~system();



      virtual string os_get_user_theme();


      virtual void defer_calc_os_dark_mode();


      //virtual void defer_calc_os_user_theme();


      using ::promise::handler::on_subject;
      virtual void on_subject(::promise::subject * psubject) override;


      virtual ::estatus main_user_async(const ::promise::routine & routine, ::e_priority epriority = priority_normal);

      virtual ::estatus main_user_sync(const ::promise::routine & routine, const ::duration & duration = one_minute(), e_priority epriority = priority_normal);


      ::task * get_task(ithread_t ithread);
      ithread_t get_task_id(::task * ptask);
      void set_task(ithread_t ithread, ::task * ptask);
      void unset_task(ithread_t ithread, ::task * ptask);


   };


} // namespace acme
