#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public ::user::document_manager_container
   {
   public:


      session();
      virtual ~session();


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace base



