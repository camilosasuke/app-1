#pragma once


class CLASS_DECL_APEX plain_service :
   public service_base
{
public:


   plain_service();
   virtual ~plain_service();


   virtual void Start(u32);
   virtual void Stop(u32);


   void CallServiceThread();



};
