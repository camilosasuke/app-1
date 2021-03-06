#pragma once



//inline ::image_result object::create_image()
//{
//
//   return __create < ::image >();
//
//}
//
//
//inline ::image_result object::create_image(const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//{
//
//   ::image_pointer pimage;
//
//   auto estatus = __construct(pimage);
//
//   if (!estatus)
//   {
//
//      return nullptr;
//
//   }
//
//   estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);
//
//   if (!estatus)
//   {
//
//      return nullptr;
//
//   }
//
//   return pimage;
//
//}
//
//
//inline ::estatus object::__compose(__composite(::image) & pimage)
//{
//
//   return __compose < ::image >(pimage);
//
//}
//
//
//inline ::estatus object::__compose(__composite(::image) & pimage, ::image * pimageSource)
//{
//
//   if (pimageSource)
//   {
//
//      __compose < ::image >(pimage, pimageSource);
//
//   }
//
//   return m_estatus;
//
//}


//inline ::estatus object::__compose(__composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//{
//
//   __compose(pimage);
//
//   if (pimage)
//   {
//
//      pimage->create(size, uidCreate, iGoodStride, bPreserve);
//
//   }
//
//   return m_estatus;
//
//}


//inline ::estatus object::__internal_preserve_ownership(__composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride)
//{
//
//   return __compose(pimage, size, uidCreate, iGoodStride, true);
//
//}


//inline ::estatus object::__construct(::image_pointer & pimage)
//{
//
//   m_estatus = ::success;
//
//   if (!pimage)
//   {
//
//      pimage = __create < ::image >();
//
//      if (!pimage)
//      {
//
//         m_estatus = ::error_no_memory;
//
//      }
//      else
//      {
//
//         m_estatus = pimage->initialize(get_object());
//
//      }
//
//   }
//
//   return m_estatus;
//
//}
//

//template < typename IMAGE_SOURCE >
//inline estatus object::__construct(::image_pointer & pimage, IMAGE_SOURCE pimageSource)
//{
//
//   m_estatus = __construct(pimage);
//
//   if (m_estatus)
//   {
//
//      if (!pimage->copy_from(pimageSource))
//      {
//
//         m_estatus = error_failed;
//
//      }
//
//   }
//
//   return m_estatus;
//
//}


//inline ::estatus object::__construct(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
//{
//
//   // DIFFERENT __construct behaviour (for image)
//   // DEFERRED.....
//   if (!pimage)
//   {
//
//      __construct(pimage);
//
//   }
//
//   if (pimage && pimage->size() != size)
//   {
//
//      m_estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);
//
//   }
//
//
//   return m_estatus;
//
//}


//inline ::estatus object::__preserve(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride)
//{
//
//   return __construct(pimage, size, eobjectCreate, iGoodStride, true);
//
//}


inline ::image_pointer create_image()
{

   auto ptype = __create < ::image >();

   if (!ptype)
   {

      return nullptr;

   }

   return ptype;

}


inline ::image_pointer create_image(const ::size & size, ::eobject eobjectFlag = IMAGE_OBJECT_OK)
{

   auto ptype = __create < ::image >();

   if (!ptype)
   {

      return nullptr;

   }

   auto estatus = ptype->create(size, eobjectFlag);

   if (!estatus)
   {

      return nullptr;

   }

   return ptype;

}


// inline ::image_result __create_image(::layered * pobjectContext)
// {

//    auto ptype = __create_new_image();

//    if (!ptype)
//    {

//       return ptype;

//    }

//    auto estatus = ptype->initialize(pobject);

//    if (!estatus)
//    {

//       return estatus;

//    }

//    return ptype;

// }



// template < typename COMPOSER >
// inline ::estatus __compose(COMPOSER && pcomposer, __composite(::image) & pimage)
// {

//    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
//    //{

//    //   return error_composite_not_composer_member;

//    //}

//    return pcomposer->__compose(pimage);

// }


// template < typename COMPOSER >
// inline ::estatus __compose(COMPOSER && pcomposer, __composite(::image) & pimage, ::image * pimageSource)
// {

//    return pcomposer->__compose(pimage, pimageSource);

// }



// template < typename COMPOSER >
// inline ::estatus __compose(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
// {

//    auto estatus = __compose(pcomposer, pimage);

//    if (!estatus)
//    {

//       return estatus;

//    }

//    if (pimage && pimage->size() != size)
//    {

//       estatus = pimage->create(size, uidCreate, iGoodStride, bPreserve);

//    }

//    return estatus;

// }


// template < typename COMPOSER >
// inline ::estatus __preserve(COMPOSER && pcomposer, __composite(::image) & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride)
// {

//    //if (((uptr)&pimage) < (uptr)pcomposer || ((uptr)&pimage) >= ((uptr)pcomposer) + sizeof(COMPOSER))
//    //{

//    //   return error_composite_not_composer_member;

//    //}

//    return pcomposer->__compose(pimage, size, uidCreate, iGoodStride, true);

// }


inline ::estatus __construct(::image_pointer & pimage)
{

   if (!pimage)
   {

      return __construct < ::image >(pimage);

   }

   return ::success;

}


inline ::estatus __construct(::image_pointer & pimage, ::image * pimageSource)
{

   auto estatus = __construct(pimage);

   if (estatus)
   {

      if (!pimage->copy_from(pimageSource))
      {

         return ::error_failed;

      }

   }

   return estatus;

}


inline ::image_pointer & __construct(::image_pointer & pimage, ::object * pobjectSource)
{

   __construct(pimage);

   pimage->initialize(pobjectSource);

   return pimage;

}


inline ::estatus __construct(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride, bool bPreserve)
{

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   if (pimage && pimage->size() != size)
   {

      estatus = pimage->create(size, eobjectCreate, iGoodStride, bPreserve);

   }

   return estatus;

}


inline ::estatus __preserve_construct(::image_pointer & pimage, const ::size & size, ::eobject eobjectCreate, int iGoodStride)
{

   return __construct(pimage, size, eobjectCreate, iGoodStride, true);

}





inline void copy_colorref(color32_t * pcolorrefDst, const ::size & size, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc)
{
   return copy_colorref(pcolorrefDst, size.cx, size.cy, iStrideDst, pcolorrefSrc, iStrideSrc);
}


inline CLASS_DECL_AURA void copy_colorref(color32_t * pcolorrefDst, const ::point & point, const ::size & size, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc)
{

   byte * pDst = (byte *) pcolorrefDst;

   return copy_colorref((color32_t *) pDst + point.x * sizeof(color32_t) + point.y * iStrideDst, size.cx, size.cy, iStrideDst, pcolorrefSrc, iStrideSrc);

}


inline CLASS_DECL_AURA void copy_colorref(color32_t * pcolorrefDst, const ::rect & rect, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc)
{

   return copy_colorref(pcolorrefDst, rect.top_left(), rect.size(), iStrideDst, pcolorrefSrc, iStrideSrc);

}


inline color32_t * image::get_data() { return m_pcolorref1; }


const color32_t * image::get_data() const
{

   map();

   return colorref();

}



