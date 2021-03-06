#include "framework.h"


namespace draw2d
{

   
   CLASS_DECL_AURA string default_font_name();


   font_enumeration::font_enumeration()
   {

      m_iUpdateId = -1;
      m_bUpdating = true;

   }


   font_enumeration::~font_enumeration()
   {

   }


   ::estatus font_enumeration::initialize(::layered* pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      System.add_process(id_os_font_change, this);

      return estatus;

   }


   void font_enumeration::on_subject(::promise::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         if (psubject->id() == id_font_enumeration)
         {

            check_need_update(psubject);

         }

      }


   }


   void font_enumeration::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      if (psubject->id() == id_os_font_change)
      {

         auto psubject = System.subject(id_os_font_change);

         update(psubject);

      }

   }


   bool font_enumeration::has_font_name(const string& str)
   {

      sync_lock sl(mutex());

      for (auto& pitem : *m_pitema)
      {

         if (pitem->m_strName.compare_ci(str) == 0)
         {

            return true;

         }

      }

      return false;

   }


   __pointer(::draw2d::font_enum_item) font_enumeration::similar_font(const char* psz)
   {

      sync_lock sl(mutex());

      __pointer(::draw2d::font_enum_item) pitemFound;

      double dMaxSimilarity = 0.2;

      auto & draw2d = System.draw2d();

      for(auto & pitem : *m_pitema)
      {

         int iFound = -1;

         double dSimilarity = draw2d.font_similarity(pitem->m_strName, psz);

         if (dSimilarity > dMaxSimilarity)
         {

            pitemFound = pitem;

            dMaxSimilarity = dSimilarity;

         }

         if (dMaxSimilarity >= 1.0)
         {

            break;

         }

      }

      return pitemFound;

   }


   void font_enumeration::adapt_font_name(string& str)
   {

      auto pitem = similar_font(str);

      if (pitem)
      {

         str = pitem->m_strName;

      }
      else
      {

         str = ::draw2d::default_font_name();

      }

   }


   void font_enumeration::check_need_update(::promise::subject * psubject)
   {

      m_bUpdating = true;

      auto g = create_memory_graphics();

      __pointer(::draw2d::font_enum_item_array) pitema;

      pitema = __new(::draw2d::font_enum_item_array);

      g->sorted_fonts(*pitema);

      if (m_pitema.is_set() && ::papaya::array::are_all_elements_equal(*pitema, *m_pitema))
      {

         m_bUpdating = false;

         psubject->m_esubject = e_subject_not_modified;

         return;

      }

      m_pitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      psubject->set_modified();

      psubject->m_esubject = e_subject_deliver;

   }


   bool font_enumeration::update(::promise::subject * psubject)
   {

      m_bUpdating = true;

      auto g = create_memory_graphics();

      __pointer(::draw2d::font_enum_item_array) pitema;

      pitema = __new(::draw2d::font_enum_item_array);

      g->sorted_fonts(*pitema);

      m_pitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      psubject->set_modified();

      return true;

   }


} // namespace draw2d


