#pragma once


class CLASS_DECL_ACME exit_exception :
   public ::exception::exception
{
public:


   int                           m_iCheck;
   __pointer(::layered)          m_pthreadExit;


   exit_exception(__pointer(::layered) playeredThreadExit = nullptr, const char * pszMessage = nullptr);
   virtual ~exit_exception();


   virtual ::estatus finish(::context_object * pcontextobjectFinish = nullptr) override;


};



