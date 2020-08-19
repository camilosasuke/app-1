﻿#pragma once


namespace user
{


   class CLASS_DECL_AURA shell :
      virtual public ::object
   {
   public:


      enum e_file_attribute
      {

         file_attribute_none,
         file_attribute_normal,
         file_attribute_directory,

      };

      enum e_folder
      {

         folder_none,
         folder_file_system,
         folder_zip,

      };


      enum e_icon
      {

         icon_normal,
         icon_open,

      };


      class image_key
      {
      public:


         string                        m_strPath;
         string                        m_strShellThemePrefix;
         cflag < e_file_attribute >    m_eattribute;
         cflag < e_icon >              m_eicon;
         i32                           m_iIcon;
         string                        m_strExtension;

         //oswindow                      m_oswindow;
         COLORREF                      m_cr;


         image_key();
         image_key(const image_key& imagekey);
         image_key(const string& strPath, const string& strShellThemePrefix, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);
         virtual ~image_key();


         bool operator == (const image_key& key) const;
         void set_path(const string& strPath, bool bSetExtension = true);
         void set_extension(const string& strPath);


      };



      template < typename VALUE, typename ARG_VALUE >
      using image_key_map = map< image_key, const image_key&, VALUE, ARG_VALUE >;
   protected:

      ::int_map < __pointer(image_list) >                                   m_pil; // int is the size
      ::int_map < __pointer(image_list) >                                   m_pilHover; // int is the size;

   public:


      class CLASS_DECL_AURA thread :
         virtual public ::thread
      {
      public:


         __reference(shell)         m_pshell;

         image_key                  m_imagekey;


         thread(shell * pshell);
         virtual ~thread();

         virtual ::estatus init_thread() override;

         virtual ::estatus run() override;

         virtual void set_finish() override;


      };


      bool                                               m_bPendingUpdate;


   protected:


      int_array                                          m_iaSize;


   public:


      image_key_map < i32, i32 >                         m_imagemap;
      image_key_map < image_key, const image_key & >     m_imagekeymap;

      string                                             m_strShellThemePrefix;
      string_array                                       m_straThemeableIconName;
      __pointer(manual_reset_event)                      m_pevNewImageKey;

      index                                              m_iMaxThreadCount;
      index                                              m_iActiveThreadCount;
      index                                              m_iThread;
      ::mutex                                            m_mutexImage;
      __pointer_array(thread)                            m_threadptra;
      tick                                               m_tickLastMax;
      DWORD                                              m_bMax;
      bool                                               m_bInitialized;

      ::array < image_key >                              m_imagekeySchedule;


      shell();
      virtual ~shell();



      virtual ::estatus initialize(::object * pobjectContext) override;
      virtual void do_initialize();


      virtual void add_thread();


      virtual void on_update_sizes_interest();

      void add_size_interest(int_array iaSize);
      void set_size_interest(int_array iaSize);

      i32 _reserve_image(const image_key & key);

      bool contains_image(const image_key & imagekey, i32 & iImage);
      bool reserve_image(const image_key & imagekey, i32 & iImage);


      virtual void get_scheduled_image_key(image_key& imagekey);


      virtual void on_add_default_file_image();


      virtual i32 get_file_extension_image(const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);
      virtual i32 get_file_image(const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0);
      virtual i32 create_file_icon_image(const string & strPath, e_file_attribute eattribute, e_icon eicon, string strIcoLocation);



      virtual i32 get_file_image(const image_key & imagekey);
      virtual i32 _get_file_image(const image_key & imagekey);


      virtual i32 impl_get_file_image(const image_key & imagekey) = 0;


      image_list * GetImageList(int iSize);
      image_list * GetImageListHover(int iSize);


      virtual e_folder get_folder_type(::object * pobject, const widechar * pcszPath);
      virtual e_folder get_folder_type(::object * pobject, const char * pcszPath);

      int add_hover_image(int iSize, int iIndex, COLORREF crBk);


      virtual i32 add_icon_path(::file::path path, COLORREF crBk, int iImage);


      virtual void set_finish() override;


   };


   inline bool shell::image_key::operator == (const image_key& key) const
   {
      return m_eattribute == key.m_eattribute
         && m_eicon == key.m_eicon
         && m_strExtension == key.m_strExtension
         && m_strShellThemePrefix == key.m_strShellThemePrefix
         && m_strPath == key.m_strPath
         && m_iIcon == key.m_iIcon;
   }


} // namespace user


template < >
inline u32 u32_hash<const ::user::shell::image_key &>(const ::user::shell::image_key & key)
{
   // default identity hash - works for most primitive values
   return hash_cat(u32_hash(key.m_strPath),
      hash_cat(u32_hash(key.m_strShellThemePrefix),
         hash_cat(u32_hash(key.m_strExtension),
            (((int)key.m_eicon) << 8) ^ (((int)key.m_eattribute) << 16)) ^ (((int)key.m_iIcon))));
}



template <  >
inline bool EqualElements(const ::user::shell::image_key & element1, const ::user::shell::image_key & element2)
{

   return element1 == element2;

}