#pragma once

// Cynokron "influenced" by handjob collaboration to use just C - the best choice, Artful Ubuntu 17.10
// using C++ to proof that C is better
// better
// best
// Everyone wants to rule the world....

namespace linux
{


   class desktop_file :
      virtual public ::matter
   {
   public:


      string_array      m_straLine;
      string            m_strAppId;


      desktop_file(const string & strAppId);
      virtual ~desktop_file();


      void create_default();
      void create();

      string_array registered_categories();
      string proper_category(string strCategory);
      string_array proper_category(string_array straCategory);


      ::file::path get_file_path();
      ::file::path get_board_path();

      void write();

      bool bamf_set_icon(oswindow oswindow);

   };


} // namespace linux



