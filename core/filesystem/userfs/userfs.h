#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::apex::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual ::estatus init1() override;


   };



} // namespace userfs



