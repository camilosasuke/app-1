#include "framework.h"


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#include <sys/ipc.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <sys/time.h>

#if defined(LINUX) || defined(__APPLE__)
#include <sys/sem.h>
#endif
#include "acme/os/ansios/_ansios.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void clock_getrealtime(struct timespec * pts)
{

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time

   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   pts->tv_sec = mts.tv_sec;
   pts->tv_nsec = mts.tv_nsec;

#else

   clock_gettime(CLOCK_REALTIME, pts);

#endif

}

#endif


//CLASS_DECL_ACME::layered* get_layered_thread();


event::event(char * sz, bool bInitiallyOwn, bool bManualReset, const char * pstrName,LPSECURITY_ATTRIBUTES psaAttribute)

{

#ifdef WINDOWS_DESKTOP

   m_hsync = ::CreateEventW(psaAttribute, bManualReset, bInitiallyOwn, wstring(pstrName));


   if (m_hsync == NULL)
   {

      __throw(resource_exception());

   }

#elif defined(_UWP)

   u32 dwFlags = 0;

   if(bInitiallyOwn)
   {

      dwFlags |= CREATE_EVENT_INITIAL_SET;

   }

   if(bManualReset)
   {

      dwFlags |= CREATE_EVENT_MANUAL_RESET;

   }

   m_hsync = (HSYNC) ::CreateEventEx(psaAttribute, ::str::international::utf8_to_unicode(pstrName), dwFlags, DELETE | EVENT_MODIFY_STATE | SYNCHRONIZE);

   if (m_hsync == nullptr)
   {

      __throw(resource_exception());

   }

#elif defined(ANDROID)

   m_pcond = new pthread_cond_t;

   pthread_cond_init((pthread_cond_t *) m_pcond, nullptr);

   m_bManualEvent = bManualReset;

   if(m_bManualEvent)
   {

      m_bSignaled = bInitiallyOwn;
      pthread_mutexattr_t  attr;
      pthread_mutexattr_init(&attr);
      pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
      i32 rc;
      m_pmutex = new pthread_mutex_t;
      if((rc = pthread_mutex_init((pthread_mutex_t *) m_pmutex,&attr)))
      {
         __throw(::exception::exception("RC_OBJECT_NOT_CREATED"));
      }


   }
   else
   {
      m_pmutex = nullptr;
   }

#else

   m_bManualEvent    = bManualReset;

   if(bManualReset)
   {

      m_pmutex = new pthread_mutex_t;

      m_pcond = new pthread_cond_t;

      pthread_mutex_init((pthread_mutex_t *) m_pmutex, 0);

      pthread_cond_init((pthread_cond_t *) m_pcond, 0);

      m_bSignaled = bInitiallyOwn;

   }
   else
   {

      m_pmutex = nullptr;

      m_pcond = nullptr;

      if(pstrName != nullptr && *pstrName != '\0')
      {

         string strPath = "/payload/tmp/ca2/ftok/event/" + string(pstrName);

         m_sem = semget(ftok(strPath, 0), 1, 0666 | IPC_CREAT);

      }
      else
      {

         m_sem = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

      }

      semun semctl_arg;

      if(bInitiallyOwn)
      {

         semctl_arg.val = 1;

      }
      else
      {

         semctl_arg.val = 0;

      }

      semctl((i32) m_sem, 0, SETVAL, semctl_arg);

   }


#endif


}


event::~event()
{

#if defined(LINUX)

   semun ignored_argument;

   semctl(m_sem, 0, IPC_RMID, ignored_argument);

   ::acme::del((pthread_mutex_t * &)m_pmutex);

   ::acme::del((pthread_cond_t * &)m_pcond);

#elif defined(ANDROID)

   if(m_pcond != nullptr)
   {
      delete (pthread_cond_t *)m_pcond;
   }
   if(m_pmutex != nullptr)
   {
      delete (pthread_mutex_t *)m_pmutex;
   }

#endif

}



bool event::SetEvent()
{

#ifdef WINDOWS

   if (m_hsync == nullptr)
   {

      ASSERT(false);

      return false;

   }

   try
   {

      return ::SetEvent((HANDLE)m_hsync) != FALSE;

   }
   catch(...)
   {
   }

   return false;

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

   }
   else
   {

      pthread_cond_signal((pthread_cond_t *) m_pcond);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   return true;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = true;

      m_iSignalId++;

      pthread_cond_broadcast((pthread_cond_t *) m_pcond);

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {

      sembuf sb;

      sb.sem_op   = 1;
      sb.sem_num  = 0;
      sb.sem_flg  = m_bManualEvent ? 0 : SEM_UNDO;

      return semop((i32) m_sem, &sb, 1) == 0;

   }

   return true;

#endif

}


//bool event::PulseEvent()
//{
//
//#ifdef WINDOWS_DESKTOP
//
//
//   ASSERT(m_hsync != nullptr);
//
//   return ::PulseEvent(m_hsync) != FALSE;
//
//#else
//
//   sembuf sb;
//
//   sb.sem_op   = 1;
//   sb.sem_num  = 0;
//   sb.sem_flg  = SEM_UNDO;
//
//   return semop((i32) m_hsync, &sb, 1) == 0;
//
//#endif
//
//}



bool event::ResetEvent()
{

#ifdef WINDOWS

   try
   {

      if(m_hsync == NULL)
      {

         ::output_debug_string(L"error reset event (1)");

         return false;

      }

      return ::ResetEvent((HANDLE)m_hsync) != FALSE;

   }
   catch(...)
   {

      ::output_debug_string(L"error reset event (2)");

   }

   return false;

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      m_bSignaled = false;

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {

      __throw(::exception::exception("It does not make sense to Reset a Event that is Automatic. It can be only Pulsed/Broadcasted."));

   }

   return true;

#endif

}


sync_result event::wait ()
{

   //__throw(todo("thread"));
   //if(m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}

#ifdef WINDOWS

   while (true)
   {

      int iResult = ::WaitForSingleObjectEx(hsync(), 300, FALSE);

      if(iResult == WAIT_OBJECT_0)
      {

         return sync_result(sync_result::result_event0);

      }
      else if (iResult == WAIT_TIMEOUT)
      {

         if (!thread_get_run())
         {

            return sync_result(sync_result::result_abandon0);

         }

      }
      else
      {

         return sync_result(sync_result::result_error);

      }

   }

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   if(m_bManualEvent)
   {

      i32 iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

   }
   else
   {

      pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

#else

   if(m_bManualEvent)
   {

      pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

      int iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

      }

      pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = 0;

      semop((i32) m_sem, &sb, 1);

   }

#endif

   //__throw(todo("thread"));
   //if(m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}

   return sync_result(sync_result::result_event0);

}

///  \brief		waits for an event for a specified time
///  \lparam		duration time period to wait for an event
///  \return	waiting action result as WaitResult
sync_result event::wait (const duration & durationTimeout)
{

   sync_result result;

   //__throw(todo("thread"));
   //if(durationTimeout > 1_s && m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->add_waiting_event(this);

   //   }

   //}


#ifdef WINDOWS

   auto osduration = durationTimeout.u32_millis();

   result = sync_result((u32) ::WaitForSingleObjectEx(hsync(), osduration,FALSE));

#elif defined(ANDROID)

   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

   timespec end;
   clock_gettime(CLOCK_REALTIME, &end);

   ((duration & ) durationTimeout).normalize();

   end.tv_sec +=durationTimeout.m_iSeconds;
   end.tv_nsec +=durationTimeout.m_iNanoseconds;

   end.tv_sec += end.tv_nsec / (1000 * 1000 * 1000);
   end.tv_nsec %= 1000 * 1000 * 1000;

   if(m_bManualEvent)
   {

      i32 iSignal = m_iSignalId;

      while(!m_bSignaled && iSignal == m_iSignalId)
      {

         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &end))
            break;

      }

   }
   else
   {

      timespec delay;
      delay.tv_sec = durationTimeout.m_iSeconds;
      delay.tv_nsec = durationTimeout.m_iNanoseconds;
      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);

   }

   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

   result =  m_bSignaled ? sync_result(sync_result::result_event0) : sync_result(sync_result::result_timeout);


#else

   if(m_bManualEvent)
   {

      if(durationTimeout.is_pos_infinity())
      {

         pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

         int iSignal = m_iSignalId;

         //clock_gettime(CLOCK_REALTIME, &abstime);

         while(!m_bSignaled && iSignal == m_iSignalId)
         {

            i32 error = pthread_cond_wait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex);

            if(error != 0)
            {

               break;

            }

         }

         pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

         if(m_bSignaled)
            result = sync_result(sync_result::result_event0);
         else
            result = sync_result(sync_result::result_error);

      }
      else
      {
         timespec abstime;

         ((duration & ) durationTimeout).normalize();

         pthread_mutex_lock((pthread_mutex_t *) m_pmutex);

         int iSignal = m_iSignalId;

         //clock_gettime(CLOCK_REALTIME, &abstime);

         clock_getrealtime(&abstime);

         abstime.tv_sec += durationTimeout.m_iSeconds;

         abstime.tv_nsec += durationTimeout.m_iNanoseconds;

         while(abstime.tv_nsec > 1000 * 1000 * 1000)
         {

            abstime.tv_nsec -= 1000 * 1000 * 1000;

            abstime.tv_sec++;

         }

         while(!m_bSignaled && iSignal == m_iSignalId)
         {

            i32 error = pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &abstime);

            if(error == EBUSY || error == ETIMEDOUT)
            {

               pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

               return sync_result(sync_result::result_timeout);

            }

         }

         pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);

         if(m_bSignaled)
            result = sync_result(sync_result::result_event0);
         else
            result = sync_result(sync_result::result_error);

      }

   }
   else
   {

      timespec delay;

      delay.tv_sec = 0;

      delay.tv_nsec = 1000 * 1000;

      u32 timeout = durationTimeout.u32_millis();

      auto start = ::millis::now();

      while(durationTimeout.is_pos_infinity() || start.elapsed() < timeout)
      {


         sembuf sb;

         sb.sem_op   = -1;
         sb.sem_num  = 0;
         sb.sem_flg  = IPC_NOWAIT;

         i32 ret = semop((i32) m_sem, &sb, 1);

         if(ret < 0)
         {
            if(ret == EPERM || ret == EBUSY)
            {
               nanosleep(&delay, nullptr);
            }
            else
            {
               return sync_result(sync_result::result_error);
            }
         }
         else
         {
            return sync_result(sync_result::result_event0);
         }

      }

      result= sync_result(sync_result::result_timeout);

   }


#endif

   ////__throw(todo("thread"));
   //if(durationTimeout > 1_s && m_eobject & e_object_alertable_wait)
   //{

   //   auto pthread = ::get_task();

   //   if(pthread)
   //   {

   //      pthread->remove_waiting_event(this);

   //   }

   //}

   return result;

}


//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************
//*****************************************************************************
//
//      Name:           Signaled
//      Description:    Determines whether the event is currently signaled.
//
//*****************************************************************************
bool event::is_signaled() const
{

#ifdef WINDOWS

   return WAIT_OBJECT_0 == ::WaitForSingleObjectEx((HANDLE)m_hsync,0,FALSE);

#elif defined(ANDROID)

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      return ((event *) this)->wait(millis(0)).signaled();

   }


#else

   if(m_bManualEvent)
   {

      return m_bSignaled;

   }
   else
   {

      sembuf sb;

      sb.sem_op   = -1;
      sb.sem_num  = 0;
      sb.sem_flg  = IPC_NOWAIT;

      i32 ret = semop((i32) m_sem, &sb, 1);

      if(ret < 0)
      {
         if(ret == EPERM)
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }

   }

#endif

}
//end**************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//end**************************************************************************

bool event::lock(const duration & durationTimeout)
{

   return wait(durationTimeout).succeeded();

//#ifdef WINDOWS
//
//   u32 dwRet = ::WaitForSingleObjectEx((HANDLE)m_hsync,durationTimeout.u32_millis(),FALSE);
//
//   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
//      return true;
//   else
//      return false;
//
//#elif defined(ANDROID)
//
//   pthread_mutex_lock((pthread_mutex_t *) m_pmutex);
//
//   ((duration & ) durationTimeout).normalize();
//
//
//   if(m_bManualEvent)
//   {
//
//      i32 iSignal = m_iSignalId;
//
//      while(!m_bSignaled && iSignal == m_iSignalId)
//      {
//
//         timespec delay;
//         delay.tv_sec = durationTimeout.m_iSeconds;
//         delay.tv_nsec = durationTimeout.m_iNanoseconds;
//         if(pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay))
//            break;
//
//      }
//
//      return m_bSignaled;
//
//   }
//   else
//   {
//
//      timespec delay;
//      delay.tv_sec = durationTimeout.m_iSeconds;
//      delay.tv_nsec = durationTimeout.m_iNanoseconds;
//      pthread_cond_timedwait((pthread_cond_t *) m_pcond, (pthread_mutex_t *) m_pmutex, &delay);
//
//      return is_locked();
//
//   }
//
//   pthread_mutex_unlock((pthread_mutex_t *) m_pmutex);
//
//#else
//
//
//   timespec delay;
//
//
//   if(m_bManualEvent)
//   {
//
//      wait(durationTimeout);
//
//      return m_bSignaled;
//
//   }
//   else
//   {
//
//      u32 timeout = durationTimeout.u32_millis();
//
//      u32 start= ::millis::now();
//
//      while(start.elapsed() < timeout)
//      {
//
//         sembuf sb;
//
//         sb.sem_op   = -1;
//         sb.sem_num  = 0;
//         sb.sem_flg  = IPC_NOWAIT;
//
//         i32 ret = semop((i32) m_hsync, &sb, 1);
//
//         if(ret < 0)
//         {
//            if(ret == EPERM)
//            {
//               nanosleep(&delay, nullptr);
//            }
//            else
//            {
//               return false;
//            }
//         }
//         else
//         {
//            return true;
//         }
//
//      }
//
//   }
//
//   return false;
//
//#endif

}


bool event::unlock()
{

   return true;

}


//HSYNC event::hsync() const
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   return m_hsync;
//
//#else
//
//   return (event *) this;
//
//#endif
//
//}



