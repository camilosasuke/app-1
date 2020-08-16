#include "framework.h"
#include <wincodec.h>


namespace imaging_wic
{


   bool windows_image_from_bitmap_source(::image * pimageFrame, IWICBitmapSource * pbitmapsource, IWICImagingFactory * pimagingfactory);


   imaging::imaging() :
      m_managerImageLoad("imaging_load_image", true)
   {

#ifdef WINDOWS

      m_managerImageLoad.m_bUseDedicatedThread = true;

#endif

   }


   imaging::~imaging()
   {

   }


   comptr < IWICImagingFactory > get_imaging_factory()
   {

      comptr < IWICImagingFactory > pimagingfactory;

      pimagingfactory.CoCreateInstance(CLSID_WICImagingFactory1);

      return pimagingfactory;

   }


#ifdef _UWP

   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool imaging::_desk_to_image(::image* pimage)
   {


      bool bOk = true;

      defer_main_thread([&]()
         {

            auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

            if (dataPackage == nullptr)
            {

               bOk = false;

               return;

            }

            if (!dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap))
            {

               bOk = false;

               return;

            }

            ::Windows::Storage::Streams::IRandomAccessStream^ stream = (::Windows::Storage::Streams::IRandomAccessStream^) ::wait(dataPackage->GetDataAsync(L"DeviceIndependentBitmap"));

            //auto ref = ::wait(dataPackage->GetDataAsync(L"DeviceIndependentBitmap"));

            if (stream == nullptr)
            {

               bOk = false;

               return;

            }

            //::Windows::Storage::Streams::IRandomAccessStreamWithContentType ^ stream = ::wait(ref->OpenReadAsync());

            //if (stream == nullptr)
            //{


            //   bOk = false;

            //   return;

            //}

            memsize s = (memsize)stream->Size;

            Windows::Storage::Streams::Buffer^ buffer = ref new Windows::Storage::Streams::Buffer(s);

            if (buffer == nullptr)
               return;

            ::wait(stream->ReadAsync(buffer, s, ::Windows::Storage::Streams::InputStreamOptions::ReadAhead));

            memory m;

            m.set_os_buffer(buffer);

            BITMAPINFO* _ = (BITMAPINFO*)m.get_data();

            pimage->create({ _->bmiHeader.biWidth,  _->bmiHeader.biHeight });

            pimage->map();

            vertical_swap_copy_colorref(
               pimage->get_data(),
               pimage->width(),
               pimage->height(),
               pimage->scan_size(),
               (COLORREF*)&m.get_data()[_->bmiHeader.biSize],
               _->bmiHeader.biSizeImage / _->bmiHeader.biHeight);


            //memory m;

            //m.

            //if (!windows_load_image_from_file(pimage, stream, get_context_application()))
            //{


            //   bOk = false;

            //   return;

            //}

         });

      return bOk;

   }
   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool imaging::_desk_has_image()
   {

      bool bOk = false;

      defer_main_thread([&bOk]()
         {

            auto dataPackage = ::Windows::ApplicationModel::DataTransfer::Clipboard::GetContent();

            if (dataPackage == nullptr)
            {

               return;

            }

            if (dataPackage->Contains(::Windows::ApplicationModel::DataTransfer::StandardDataFormats::Bitmap))
            {

               bOk = true;

               return;

            }

         });

      return bOk;

   }

   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool imaging::_image_to_desk(const ::image* pimage)
   {

      bool bOk = true;

      auto package = ref new ::Windows::ApplicationModel::DataTransfer::DataPackage;

      if (package == nullptr)
      {

         return false;

      }

      Windows::Storage::Streams::InMemoryRandomAccessStream^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

      ::save_image saveimage;

      saveimage.m_eformat = ::draw2d::format_png;

      saveimage.m_iQuality = 100;

      if (!node_save_image(randomAccessStream, pimage, &saveimage))
      {

         return false;

      }

      package->RequestedOperation = ::Windows::ApplicationModel::DataTransfer::DataPackageOperation::Copy;

      auto context_object = ::Windows::Storage::Streams::RandomAccessStreamReference::CreateFromStream(randomAccessStream);

      package->SetBitmap(context_object);

      defer_main_thread([&package, this]()
         {

            ::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(package);

         });

      return true;


   }

#endif


} // namespace imaging_wic



