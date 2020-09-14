#include "framework.h"
#include "acme/os/_c.h"
#include "acme/os/_.h"
#include "acme/const/id.h"


namespace multithreading
{


   //CLASS_DECL_ACME comparable_eq_array<ITHREAD> * s_piaThread2 = nullptr;
   //CLASS_DECL_ACME __pointer_array(thread) * s_pthreadptra2 = nullptr;
   //CLASS_DECL_ACME::critical_section * s_pcs2 = nullptr;


   //CLASS_DECL_ACME void init_multithreading()
   //{

   //   //s_pcs2 = new ::critical_section();

   //   //s_piaThread2 = new comparable_eq_array<ITHREAD>;

   //   //s_pthreadptra2 = new __pointer_array(thread);

   //   __node_init_multithreading();

   //}


   //CLASS_DECL_ACME void term_multithreading()
   //{

   //   __node_term_multithreading();

   //   //::acme::del(s_pthreadptra2);

   //   //::acme::del(s_piaThread2);

   //   //::acme::del(s_pcs2);

   //}

   //CLASS_DECL_ACME bool thread_id_registered(ITHREAD id)
   //{

   //   //cslock lock(s_pcs2);

   //   //return s_piaThread2->contains(id);

   //   return ::get_context_system()->get_thread(id) != nullptr;

   //}


   //bool thread_registered(::thread * pthread)
   //{

   //   return ::get_context_system()->get_thread_id(pthread) != 0;

   //}


   //void thread_register(ITHREAD ithread, ::thread * pthread)
   //{

   //   ::get_context_system()->set_thread(ithread, pthread);

   //}


   //void thread_unregister(ITHREAD ithread, ::thread * pthread)
   //{

   //   auto psystem = ::get_context_system();

   //   psystem->unset_thread(ithread, pthread);

   //}


   //bool is_child(::thread * pthreadChildCandidate)
   //{

   //   if (::is_null(pthreadChildCandidate))
   //   {

   //      return false;

   //   }

   //   if (pthreadChildCandidate->m_pthreadParent)
   //   {

   //      return true;

   //   }

   //   sync_lock sl(&::get_context_system()->m_mutexThread);

   //   for (auto & pair : ::get_context_system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         if (pair.element1()->m_threada.contains(pthreadChildCandidate))
   //         {

   //            return true;

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //   return false;

   //}


   //void post_quit_to_all_threads()
   //{

   //   sync_lock sl(&::get_context_system()->m_mutexThread);

   //   for (auto& pair : ::get_context_system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         pair.element1()->finalize();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}


   //CLASS_DECL_ACME void post_to_all_threads(UINT message, WPARAM wparam, LPARAM lparam)
   //{

   //   sync_lock sl(&::get_context_system()->m_mutexThread);

   //   for (auto& pair : ::get_context_system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         pair.element1()->post_message(message, wparam, lparam);

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}


   //CLASS_DECL_ACME __pointer(::thread) calc_parent(::thread * pthread)
   //{

   //   if (::is_null(pthread))
   //   {

   //      return nullptr;

   //   }

   //   if (pthread == ::get_context_system())
   //   {

   //      return nullptr;

   //   }

   //   auto pthreadContext = pthread->get_context_thread();

   //   if (::is_set(pthreadContext))
   //   {

   //      if (pthreadContext->is_set_finish() || !pthreadContext->m_bLastingThread)
   //      {

   //         pthreadContext = calc_parent(pthreadContext);

   //         if (::is_set(pthreadContext))
   //         {

   //            return pthreadContext;

   //         }

   //      }
   //      else
   //      {

   //         return pthreadContext;

   //      }

   //   }

   //   auto papplicationContext = pthread->get_context_application();

   //   if (::is_set(papplicationContext) && papplicationContext != pthread)
   //   {

   //      return papplicationContext;

   //   }

   //   auto psessionContext = pthread->get_context_session();

   //   if (psessionContext != pthread && ::is_set(psessionContext))
   //   {

   //      return psessionContext;

   //   }

   //   auto psystemContext = pthread->get_context_system();

   //   if (psystemContext != pthread && ::is_set(psystemContext))
   //   {

   //      return psystemContext;

   //   }

   //   return ::get_context_system();

   //}


} // namespace multithreading


CLASS_DECL_ACME ::thread * get_thread_raw()
{

   return ::get_thread();

}


typedef bool THREAD_GET_RUN();
using PFN_THREAD_GET_RUN = THREAD_GET_RUN*;


PFN_THREAD_GET_RUN g_pthreadgetrun = nullptr;


bool thread_get_run()
{

   if (!g_pthreadgetrun)
   {

      return true;

   }

   return g_pthreadgetrun();

}


CLASS_DECL_ACME void set_thread_get_run(PFN_THREAD_GET_RUN pthreadrun)
{

   g_pthreadgetrun = pthreadrun;

}


//bool thread_get_run()
//{
//
//   try
//   {
//
//      if(::is_null(::get_thread()) || !::get_thread()->is_thread()) // system threads don't have generally associated ca2 thread generic
//      {
//         ////////// and have short life, so it is safe to keep it running
//         //return true;
//         return ::get_context_system()->thread_get_run();
//
//      }
//
//      return ::get_thread()->thread_get_run();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return false;
//
//}


namespace multithreading
{


   //CLASS_DECL_ACME void set_finish()
   //{

   //   set_finish(::get_thread());

   //}


   //CLASS_DECL_ACME bool post_quit_and_wait(const duration & duration)
   //{

   //   return post_quit_and_wait(::get_thread(), duration);

   //}


   //void set_finish(::thread * pthread)
   //{

   //   if (pthread == nullptr)
   //   {

   //      return;

   //   }

   //   try
   //   {

   //      pthread->finalize();

   //   }
   //   catch (...)
   //   {


   //   }

   //}


   //bool post_quit_and_wait(::thread * pthreadParam, const duration & duration)
   //{

   //   __pointer(::thread) pthread;

   //   try
   //   {

   //      pthread = pthreadParam;

   //   }
   //   catch (...)
   //   {

   //      return true;

   //   }

   //   if (pthread.is_null())
   //   {

   //      return true;

   //   }

   //   try
   //   {

   //      pthread->finalize();

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      return pthread->wait(duration).succeeded();

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


} // namespace multithreading


::mutex * s_pmutexMessageDispatch = nullptr;


::mutex & message_dispatch_mutex()
{


   return *s_pmutexMessageDispatch;

}


//::context * get_context()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if (pthread->get_context())
//   {
//
//      if (::is_null_ref(pthread->get_context()->file()))
//      {
//
//         pthread->get_context()->initialize_context();
//
//      }
//
//      return pthread->get_context();
//
//   }
//
//   if (pthread->get_context_application())
//   {
//
//      return pthread->get_context_application();
//
//   }
//
//   return nullptr;
//
//}


//::acme::application * g_papp;


//void set_global_application(::acme::application* papp)
//{
//
//    g_papp = papp;
//
//}
//
//
//::acme::application * get_global_application()
//{
//
//   return g_papp;
//
//}


//::acme::application * get_context_application()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return get_global_application();
//
//   }
//
//   return pthread->get_context_application();
//
//}


//::acme::session * get_context_session()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return pthread->get_context_session();
//
//}

//::acme::system * g_pacmesystem = nullptr;
//
//CLASS_DECL_ACME ::acme::system * get_context_system()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return g_pacmesystem;
//
//   }
//
//   ::acme::system * psystem = pthread->get_context_system();
//
//   if (!psystem)
//   {
//
//      psystem = g_pacmesystem;
//
//   }
//
//   return psystem;
//
//}







//
//void thread_ptra::set_finish()
//{
//
//   try
//   {
//
//      //sync_lock sl(mutex());
//
//      for (index i = 0; i < get_count(); i++)
//      {
//
//         ::thread * pthread = element_at(i);
//
//         try
//         {
//
//            /// this is quite dangerous
//            //sync_lock slThread(pthread->mutex());
//
//            pthread->finalize();
//
//         }
//         catch (...)
//         {
//
//            remove(pthread);
//
//            break;
//
//         }
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//}
//

//
//::count thread_ptra::get_count_except_current_thread()
//{
//
//   thread * pthread = ::get_thread();
//
//   ::count c = 0;
//
//   for(index i = 0; i < __pointer_array(thread)::get_count(); i++)
//   {
//
//      ::thread * pthreadItem = element_at(i);
//
//      if(pthreadItem != pthread && pthreadItem != nullptr)
//      {
//
//         TRACE("\nthread_ptra::get_count_except_current_thread %s", typeid(*pthreadItem).name());
//
//         c++;
//
//      }
//
//   }
//
//   return c;
//
//}
//
//
//void thread_ptra::wait(const duration & duration, sync_lock & sl)
//{
//
//   ::datetime::time timeEnd = ::datetime::time::get_current_time() + MAX(seconds(2), duration);
//
//   try
//   {
//
////      sync_lock sl(psyncParent);
////
//      ::count cCount = get_count_except_current_thread();
//
//      ::datetime::time timeNow = ::datetime::time::get_current_time();
//
//      while (cCount > 0 &&  timeNow < timeEnd)
//      {
//
//         sl.unlock();
//
//         timeNow = ::datetime::time::get_current_time();
//
//         cCount = get_count_except_current_thread();
//
//         Sleep(500);
//
//         sl.lock();
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//}


CLASS_DECL_ACME ::estatus call(::generic * pobject)
{

   ::estatus estatus;

   try
   {

      estatus = pobject->call();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


bool isvowel_dup(int i)
{

   if (i == 'a')
   {
      return true;
   }
   else if (i == 'e')
   {
      return true;
   }
   else if (i == 'i')
   {
      return true;
   }
   else if (i == 'o')
   {
      return true;
   }
   else if (i == 'u')
   {
      return true;
   }
   if (i == 'A')
   {
      return true;
   }
   else if (i == 'E')
   {
      return true;
   }
   else if (i == 'I')
   {
      return true;
   }
   else if (i == 'O')
   {
      return true;
   }
   else if (i == 'U')
   {
      return true;
   }
   else
   {
      return false;
   }

}


string _001OnlyAlnumString(const char * psz)
{

   string strOnlyAlnum;

   while (*psz)
   {

      if (ansi_char_is_alphanumeric(*psz))
      {

         strOnlyAlnum += *psz;

      }

      psz++;

   }

   return strOnlyAlnum;

}


string _001OnlyAlnumNonVowelString(const char * psz)
{

   string strOnlyAlnum;

   while (*psz)
   {

      if (ansi_char_is_alphanumeric(*psz))
      {

         if (!isvowel_dup(*psz))
         {

            strOnlyAlnum += *psz;

         }

      }

      psz++;

   }

   return strOnlyAlnum;

}


string _001CompactString(const string & str, int iSkip, int iSkipBegin = 0)
{

   string strCompact;

   strsize i = 0;

   for (; i < iSkipBegin; i++)
   {

      strCompact += str[i];

   }

   for (; i < str.get_length(); i += (iSkip + 1))
   {

      strCompact += str[i];

   }

   return strCompact;

}


void thread_name_abbreviate(string & strName, int len)
{

   if (strName.get_length() <= len)
   {

      return;

   }

   string_array stra;

   strsize iFindLast = 0;

   strsize iFind = 0;

   string strOnlyAlnum;

   while (iFind >= 0)
   {

      iFind = strName.find("::", iFindLast);

      stra.add(strName.Mid(iFindLast, iFind - iFindLast + 1));

      iFindLast = iFind + 2;

   }

   strName = stra.implode(":");

   if (strName.get_length() <= len)
   {

      return;

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumString(stra[i]);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumNonVowelString(stra[i]);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001CompactString(stra[i], 1, 1);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   strName.truncate(len);

}







::estatus     run_runnable(::generic* pobjectTask)
{

   ::estatus     estatus = error_exception;

   try
   {

      __pointer(generic) pobject(e_move_transfer, pobjectTask);

      try
      {

         estatus = pobject->call();

      }
      catch (...)
      {

      }

   }
   catch (...)
   {

   }

   return estatus;

}


thread_local __pointer(layered) t_pthread;


CLASS_DECL_ACME ::layered * get_layered_thread()
{

   return t_pthread;

}


CLASS_DECL_ACME ::thread* get_thread()
{

   return ___thread(get_layered_thread());

}


CLASS_DECL_ACME void set_thread(layered * pthread)
{

    t_pthread = pthread;

}


CLASS_DECL_ACME void thread_release()
{

   t_pthread.release();

}


