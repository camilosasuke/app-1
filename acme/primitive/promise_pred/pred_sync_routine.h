#pragma once


namespace promise
{


   template<typename PRED>
   class pred_sync_routine :
           virtual public ::matter
   {
   public:


      PRED                 m_pred;
      manual_reset_event   m_ev;


      pred_sync_routine(PRED pred) : m_pred(pred) {}
      virtual ~pred_sync_routine() {}


      virtual ::estatus run() override
      {

         m_pred();

         m_ev.SetEvent();

         return ::success;

      }


      void sync_wait() override
      {

         m_ev.wait();

      }


      void sync_wait(const ::duration &duration) override
      {

         m_ev.wait();

      }


   };


} // namespace promise


template < typename PRED >
::promise::routine __sync_routine(PRED pred)
{

   return __new(::promise::pred_sync_routine<PRED>(pred));

}
