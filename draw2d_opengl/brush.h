#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL brush : 
      virtual public ::draw2d::brush
   {
   public:


      brush();
      virtual ~brush();


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_opengl


