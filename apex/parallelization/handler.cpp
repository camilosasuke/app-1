#include "framework.h"


handler_manager::handler_manager(const string& strThreadName, bool bSingleThread, int iAliveCount) :
   m_strThreadName(strThreadName),
   m_bSingleThread(bSingleThread),
   m_iAliveCount(iAliveCount),
   m_pevTaskOnQueue(e_create_new),
   m_iAlive(0),
   m_bUseDedicatedThread(false)
{

   defer_create_mutex();

}


handler_manager::~handler_manager()
{


}


::estatus handler_manager::handle(const ::promise::routine & routine, bool bSync)
{

   if (bSync)
   {

      return sync(routine);

   }
   else
   {

      return async(routine);

   }

}


::estatus handler_manager::sync(const ::promise::routine & routine)
{

   if (m_bUseDedicatedThread)
   {

      auto proutine = ___sync_routine(routine);

      async(proutine);

      proutine->wait(one_minute());

      return ::success;

   }
   else
   {

      return routine();

   }

}


::estatus handler_manager::set_finish_composites(::context_object * pcontextobjectFinish)
{

   return ::object::set_finish_composites(pcontextobjectFinish);

}



::estatus handler_manager::async(const ::promise::routine & routine)
{

   {

      sync_lock sl(mutex());

      m_routinea.add(routine);

      m_pevTaskOnQueue->SetEvent();

   }

   if (!m_pthread)
   {

      m_pthread = fork([this]()
      {

         ::get_task()->set_thread_name(m_strThreadName);

         loop();

         ::output_debug_string("handler_manager::async fork finished!!");

      });
      
   }

   return ::success;

}


::promise::routine handler_manager::pick_new_task()
{

   sync_lock sl(mutex());

   if (m_routinea.is_empty())
   {

      sl.unlock();

      m_pevTaskOnQueue->wait(1_s);

      sl.lock();

   }

   if (m_routinea.is_empty())
   {

      return nullptr;

   }

   auto method = m_routinea.first();

   m_routinea.remove_at(0);

   return method;

}


void handler_manager::loop()
{

#ifdef WINDOWS

   if (m_bSingleThread)
   {

      defer_co_initialize_ex(false, true);

   }

#endif

   int iAlive = 0;

   while (::thread_get_run())
   {

      auto method = pick_new_task();

      if(!method)
      {

         continue;

      }

      method();

   }

   m_pthread.release();

};

