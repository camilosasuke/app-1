#pragma once


class CLASS_DECL_APEX file_system :
   virtual public object
{
public:


   ::file::path         m_pathCa2Module;
   ::file::path         m_pathModule;


   file_system();
   virtual ~file_system();


   virtual ::estatus initialize(::layered * pobjectContext) override;

   virtual ::estatus init_system();

   virtual ::estatus update_module_path();




};



