//
//  file_context.hpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#pragma once


namespace macos
{


   class CLASS_DECL_APEX file_context :
      virtual public ::file_context
   {
   public:

      
      __reference(dir_system)      m_pdirsystem;
      __reference(file_system)      m_pfilesystem;


      file_context();
      virtual ~file_context();
      
      
      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual payload length(const ::file::path & path) override;

      virtual ::estatus update_module_path() override;

      virtual file_result get_file(const payload & varFile, const efileopen & eopen) override;


   };


} // namespace macos



