#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE main_frame :
      virtual public simple_main_frame
   {
   public:


      

      main_frame(::object * pobject);
      virtual ~main_frame();


      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pinteraction) override;

      //virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pinteraction) override;

      virtual bool has_pending_graphical_update() override;

   };


} // namespace sphere


















