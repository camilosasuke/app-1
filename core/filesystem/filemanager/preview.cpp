#include "framework.h"
//#include "_filemanager.h"


namespace filemanager
{


   preview::preview()
   {

   }


   preview::~preview()
   {

   }


   void preview::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
   }



   void preview::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      ::rect rectClient;
      get_client_rect(rectClient);
      pgraphics->fill_rect(rectClient, RGB(200, 200, 190));

      if(filemanager_document() == nullptr)
         return;

      if (m_iCurFile < 0)
      {
      }
      else if (m_iCurFile == 0 && filemanager_document()->m_listingUser2.get_size() == 0)
      {
         pgraphics->text_out(10, 10, "No files in this directory");
      }
      else if(m_iCurFile < filemanager_document()->m_listingUser2.get_size())
      {

         pgraphics->text_out(10,10,filemanager_document()->m_listingUser2.title(m_iCurFile));

      }

   }


   void preview::update(::update * pupdate)
   {

      ::filemanager::impact::update(pupdate);

      if (pupdate->m_id == INITIALIZE_ID)
      {

         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                     AddClient(this);
                     SetDataInterface(&m_datainterface);
                     AddClient(&m_datainterface);
                     string str;
                     str.Format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                     if(filemanager_data()->m_bTransparentBackground)
                     {
                     ::user::list::m_etranslucency = ::user::list::translucency_present;
                     }
                     DISetSection(str);
                     _001UpdateColumns();*/
      }
      else if (pupdate->m_id == FILTER_ID)
      {
         /*if(pupdate->value(id_filter).is_empty())
         {
         FilterClose();
         }
         else
         {
         FilterBegin();
         Filter1(pupdate->value(id_filter));
         FilterApply();
         }*/
      }

   }


} // namespace filemanager


