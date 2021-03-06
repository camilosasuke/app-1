#include "framework.h"
#include "aura/update.h"


namespace multimedia
{


   decoder::decoder()
   {

      m_bDecoderDecode = false;

   }


   decoder::~decoder()
   {

   }


   //void decoder::DecoderDiscard()
   //{

   //   release();

   //}


   //void decoder::delete_this()
   //{

   //   //if(m_pplugin != nullptr)
   //   //{

   //   //   m_pplugin->DeleteDecoder(this);

   //   //}
   //   //else
   //   //{

   //      ::object::delete_this();

   //   //}

   //}


   ::estatus decoder::multimedia_open(::file::file * pfile)
   {

      return ::success;

   }


   bool decoder::multimedia_close()
   {

      return false;

   }


   ::estatus decoder::impl_multimedia_open(::file::file * pfile)
   {

      return ::error_failed;

   }


   bool decoder::impl_multimedia_close()
   {


      m_pathOrigin.Empty();



      return true;

   }


   void decoder::FillTitleInfo(string_array & wstraFormat, string2a & wstr2aTitle)
   {

      payload strAttr;

      string str;
      string wstrAttr;


      bool bMediaCall = false;

      ::file::path strPathOrigin = (string)m_pathOrigin;

      {

         auto& multimedia = Multimedia;

         auto pmultimedia = get_context_multimedia(this);

         sync_lock sl(multimedia.mutex());

         wstrAttr = pmultimedia->get_media_call_title(strPathOrigin);

      }

      if (wstrAttr.has_char())
      {

         bMediaCall = true;

         wstraFormat.add("%0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);

      }
      else if (multimedia_get_attribute(id_title, strAttr))
      {
         //strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         wstraFormat.add("%0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }
      else
      {
         wstrAttr = m_pathOrigin.title();
         wstraFormat.add("%0");
         wstr2aTitle.add_new();
         wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
      }

      if (multimedia_get_attribute(id_artist, strAttr))
      {
         //strAttr.ReleaseBuffer();
         wstrAttr = strAttr.stra()._008Implode(", ", " and ");
         if (wstrAttr.has_char())
         {
            wstraFormat.add("Performer: %0");
            wstr2aTitle.add_new();
            wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
         }
      }

      if (multimedia_get_attribute(id_album, strAttr))
      {
         //            strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         if (wstrAttr.has_char())
         {
            wstraFormat.add("Album: %0");
            wstr2aTitle.add_new();
            wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
         }
      }

      if (multimedia_get_attribute(id_composer, strAttr))
      {
         //            strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         if (wstrAttr.has_char())
         {
            wstraFormat.add("Composer: %0");
            wstr2aTitle.add_new();
            wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
         }
      }

      if (multimedia_get_attribute(id_channel, strAttr))
      {
         //            strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         if (wstrAttr.has_char())
         {
            wstraFormat.add("%0");
            wstr2aTitle.add_new();
            wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
         }
      }

      if (multimedia_get_attribute(id_year, strAttr))
      {
         //strAttr.ReleaseBuffer();
         wstrAttr = strAttr;
         if (wstrAttr.has_char())
         {
            wstraFormat.add("Year: %0");
            wstr2aTitle.add_new();
            wstr2aTitle[wstr2aTitle.get_upper_bound()].add(wstrAttr);
         }
      }

      if (bMediaCall)
      {

         Multimedia.on_decoder_fill_title_info(this, wstraFormat, wstr2aTitle);


      }

   }


   string decoder::multimedia_get_origin_path()
   {

      return m_pathOrigin;

   }

   void decoder::multimedia_set_origin_path(const string & strOriginPath)
   {

      m_pathOrigin = strOriginPath;

   }


   bool decoder::multimedia_get_attribute(::e_id eattribute, payload & payload)
   {

      sync_lock lock(mutex());

      if (eattribute == id_title)
      {

         payload = value("name");

      }
      else if (eattribute == id_album)
      {

         payload = value("album");

      }
      else if (eattribute == id_artist)
      {

         payload = value("artist");

      }
      else if (eattribute == id_year)
      {

         payload = value("year");

      }
      else if (eattribute == id_composer)
      {

         payload = value("composer");

      }
      else
      {

         payload = ::type_empty;

      }

      return true;

   }


} // namespace multimedia



