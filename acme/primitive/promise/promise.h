#pragma once


// <3tbs, Mummi and bilbo!!


namespace promise
{


   class CLASS_DECL_ACME promise :
           virtual public ::matter
   {
   public:


      ::promise::process            m_process;
      ::matter_pointer              m_pmatter;


      promise(::matter *pmatter, const ::promise::process & process);

      virtual ~promise();


      virtual ::estatus on_task() override;


   };




} // namespace promise



