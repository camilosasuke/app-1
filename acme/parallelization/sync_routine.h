#pragma once


namespace promise
{


   class sync_routine;


   inline __pointer(sync_routine) ___sync_routine(const ::promise::routine & routine);


   class CLASS_DECL_ACME sync_routine :
           public ::sync
   {
   protected:

      friend __pointer(sync_routine) ___sync_routine(const ::promise::routine &routine);


      sync_routine(const ::promise::routine & routine) :
         m_routine(routine)
      {

         __defer_construct(m_peventCompletion);

      }


   public:


      routine                          m_routine;
      __pointer(manual_reset_event)    m_peventCompletion;
      ::duration                       m_duration;
      ::estatus                        m_estatus;


      virtual ~sync_routine() {}


      inline virtual ::estatus operator()() override
      {

         m_estatus = m_routine();

         m_peventCompletion->SetEvent();

         return m_estatus;

      }


      virtual sync_result wait(const duration &durationTimeout)
      {

         return m_peventCompletion->wait(durationTimeout);

      }


   };


   inline __pointer(sync_routine) ___sync_routine(const ::promise::routine & routine)
   {

      return __new(sync_routine(routine));

   }


} // namespace promise



