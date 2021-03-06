#pragma once


namespace graphics
{


   class CLASS_DECL_AURA bitmap_source_buffer :
      virtual public graphics
   {
   public:


      file::memory_map              m_memorymap;
      string                        m_strBitmapSource;


      bitmap_source_buffer();
      virtual ~bitmap_source_buffer();


      virtual ::estatus initialize_graphics_graphics(::user::interaction_impl* pimpl) override;

      virtual void defer_initialize_bitmap_source_buffer();

      virtual bool ipc_copy(const pixmap * ppixmap);

      virtual bool round_swap_key_buffers() override;


   };

} // namespace graphics



