﻿#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_thread:
      virtual public ::thread
   {
   public:


      ::filemanager::e_state            m_estate;
      operation_view *                 m_pview;
      __pointer_array(::filemanager::operation)              m_fileoperationa;
      i32                          m_iOperation;
      bool                             m_bStep;
      ::mutex                            m_mutexFileOperationA;
      bool                             m_bStop;


      operation_thread();

      void queue_copy(::file::listing & stra,const ::file::path & pszDest,const ::file::path & pszSrcBase,bool bExpand,bool bReplaceAll,bool bDeleteOriginOnSuccessfulCopy, __pointer(::user::interaction) puiCallback = nullptr,UINT uiMessage = WM_USER,WPARAM wparam = 0x1000);
      void kick();

      i32 get_item_count();
      string get_item_message(i32 iItem);
      double get_item_progress(i32 iItem);

      double get_progress_rate();

      void step();

      virtual ::estatus     run() override;


   };


} // namespace filemanager












