#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_CORE session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::layered * pobjectContext);
      virtual ~session();


      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool query(const char * pszQuery, payload & payload);


   };


} // namespace simpledb


