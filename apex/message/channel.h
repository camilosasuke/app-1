#pragma once


//#include "apex/primitive/collection/runnable_array.h"
namespace user
{


   class command;


} // namespace user


namespace message
{

   class message;
   class id_route;
   template < typename MESSAGE > class typed_route;
   class id;
   class route;

} // namespace status


class CLASS_DECL_APEX channel :
   virtual public ::object
{
public:


   static __pointer(::mutex)                       s_pmutexChannel;
   __pointer(::channel)                            m_pchannel;
   id_array                                        m_idaHandledCommands;
   ::message::id_route                             m_idroute;
   ::message::id_route                             m_idrouteNew;
   bool                                            m_bNewChannel;
   id_map < __pointer_array(::generic) >           m_mapUpdate;
   id_map < runnable_array >                       m_mapRunnable;


   channel();
   virtual ~channel();



   virtual ::mutex * defer_mutex_channel();

   virtual void remove_receiver(::object * preceiver);

   virtual void transfer_receiver(::message::id_route & router, ::object * preceiver);

   virtual void remove_all_routes();

   template < typename RECEIVER, typename MESSAGE >
   ::message::typed_route < MESSAGE > & get_typed_route(::message::id id, RECEIVER * preceiverDerived);

   template < typename RECEIVER, typename MESSAGE >
   void add_receiver_route(::message::id id, RECEIVER * preceiver, void (RECEIVER:: * phandler)(MESSAGE * pmessage));

   template < typename RECEIVER >
   ::message::route & add_route(::message::id id, RECEIVER * preceiver);

   template < typename RECEIVER, typename MESSAGE_PRED >
   void add_route(::message::id id, RECEIVER * preceiverDerived, MESSAGE_PRED pred);

   template < typename RECEIVER >
   void add_route(RECEIVER * preceiverDerived, void (RECEIVER:: * phandler)(::message::message * pmessage), ::message::id id = ::message::id());

   virtual void route_message(::message::message * pmessage);


   virtual __pointer(::message::base) get_message_base(LPMESSAGE pmsg);

   virtual __pointer(::message::base) get_message_base(UINT message, WPARAM wparam, lparam lparam);


#ifdef LINUX

   virtual __pointer(::message::base) get_message_base(void * pevent, ::user::interaction * pwnd = nullptr);

#endif



   template < class T >
   void connect_command_probe(const ::id & id, void (T:: * pfn)(::message::message *))
   {

      connect_command_probe(id, dynamic_cast <T *> (this), pfn);

   }


   template < class T >
   void connect_command(const ::id & id, void (T:: * pfn)(::message::message *))
   {

      connect_command(id, dynamic_cast <T *> (this), pfn);

   }

   template < class T >
   void connect_command_probe(const ::id & id, T * p, void (T:: * pfn)(::message::message *))
   {

      ::message::id messageid;

      messageid = ::message::type_command_probe;

      messageid.::id::operator=(id);

      add_route(p, pfn, messageid);

   }


   template < class T >
   void connect_command(const ::id & id, T * p, void (T:: * pfn)(::message::message *))
   {

      ::message::id messageid;

      messageid = ::message::type_command;

      messageid.::id::operator=(id);

      add_route(p, pfn, messageid);

   }


   template < typename MESSAGE_PRED >
   void connect_command_pred(const ::id & id, MESSAGE_PRED pred)
   {

      ::message::id messageid;

      messageid = ::message::type_command;

      messageid.::id::operator=(id);

      add_route(messageid, this) = pred;

   }


   template < typename RECEIVER, typename MESSAGE_PRED >
   void add_update_route_pred(RECEIVER * preceiver, const ::id & id, MESSAGE_PRED pred)
   {

      ::message::id messageid;

      messageid = ::message::type_update;

      messageid.::id::operator=(id);

      add_route(messageid, preceiver) = pred;

   }


   void default_toggle_check_handling(const ::id& id);


   template < typename RECEIVER >
   void add_update_route(RECEIVER * preceiver, const ::id & id)
   {

      add_update_route_pred(preceiver, id, [preceiver, id](::message::message * pmessage)
      {

         preceiver->call_update(id);

      });

   }


   virtual void _001SendCommand(::user::command * pcommand);
   virtual void _001SendCommandProbe(::user::command * pcommand);


   using ::object::call_update;
   virtual void call_update(const ::id & id, const ::action_context & action_context);


   virtual void on_command(::user::command * pcommand);
   virtual bool has_command_handler(::user::command * pcommand);
   virtual void on_command_probe(::user::command * pcommand);


   virtual void route_command_message(::user::command * pcommand);

   
   virtual void on_command_message(::user::command* pcommand);


   virtual void install_message_routing(::channel * pchannel);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(::user::command * pcommand);


};


