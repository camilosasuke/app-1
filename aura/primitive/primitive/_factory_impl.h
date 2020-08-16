#pragma once


namespace factory
{


   inline __pointer(factory_interface) & get_factory(const ::id & id)
   {

      cslock cs(g_pcsFactory);

      return (*g_pfactorymap)[id];

   }


   inline void set_factory(const ::id & id, const __pointer(factory_interface) & pfactory)
   {

      cslock cs(g_pcsFactory);

      g_pfactorymap->set_at(id, pfactory);

   }


   template < typename TYPE, typename BASE >
   inline void create_factory(const ::id & id)
   {

      set_factory(id, __new(factory < TYPE, BASE >()));

   }


   template < typename TYPE >
   inline stream & load_object(stream & stream, __pointer(TYPE) & p)
   {

      string strText;

      stream >> strText;

      if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
      {

         if (p && ::str::demangle(p->type_name()) == strText)
         {

            ::output_debug_string("loading into existing object of same class type (1)");

         }
         else
         {

            p.defer_create_new();

            if (!p)
            {

               ::output_debug_string("defer_new failed (1.1)");

               stream.set_fail_bit();

            }
            else if (::str::demangle(p->type_name()) != strText)
            {

               ::output_debug_string("allocated object type is different from streamed object type (1.2)");

               stream.set_fail_bit();

            }

         }

      }
      else
      {

         auto id = stream.text_to_factory_id(strText);

         if (p && id == ::str::demangle(p->type_name()))
         {

            ::output_debug_string("loading into existing object of same class type (2)");

         }
         else
         {

            p = stream.create_object_from_text(strText);

            if (!p)
            {

               ::output_debug_string("stream::alloc_object_from_text failed (2.1)");

            }
            else if (::str::demangle(p->type_name()) != id.to_string())
            {

               ::output_debug_string("allocated object type is different from streamed object type (2.2)");

               stream.set_fail_bit();

            }

         }

      }

      if (!stream.fail())
      {

         if (p->has(e_object_factory))
         {

            p->read(stream);

         }
         else
         {

            stream >> *p;

         }

      }

      return stream;

   }


} // namespace factory




template < typename BASE_TYPE >
inline __pointer(BASE_TYPE) __create()
{

   auto pfactory = ::factory::get_factory < BASE_TYPE >();

   if (!pfactory)
   {

      return nullptr;

   }

   auto ptypeNew = pfactory->call_new();

   if (!ptypeNew)
   {

      return nullptr;

   }

   __pointer(BASE_TYPE) pbase = ptypeNew;

   if (!pbase)
   {

      return nullptr;

   }

   return pbase;

}


template < typename BASE_TYPE >
inline __pointer(BASE_TYPE) __create(::object * pobject)
{

   auto p = __create < BASE_TYPE >();

   if (!p)
   {

      return nullptr;

   }

   auto estatus = p->initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return p;

}


template < typename BASE_TYPE >
inline __pointer(BASE_TYPE) __id_create(const ::id & id)
{

   auto pfactory = ::factory::get_factory(id);

   if (!pfactory)
   {

      return nullptr;

   }

   auto ptypeNew = pfactory->call_new();

   if (!ptypeNew)
   {

      return nullptr;

   }

   __pointer(BASE_TYPE) pbase = ptypeNew;

   if (!pbase)
   {

      return nullptr;

   }

   pbase->m_eobject |= e_object_factory;

   return pbase;

}


template < typename TYPE >
inline __pointer(TYPE) __create_new()
{

   auto ptype = __new(TYPE);

   if (!ptype)
   {

      return nullptr;

   }

   return ptype;

}


template < typename TYPE >
inline __pointer(TYPE) __create_new(const TYPE & t)
{

   auto ptype = __new(TYPE(t));

   if (!ptype)
   {

      return nullptr;

   }

   return ptype;

}


template < typename TYPE >
inline __pointer(TYPE) __create_new(::object * pobjectContext)
{

   auto ptype = __create_new< TYPE > ();

   if (!ptype)
   {

      return ptype;

   }

   auto estatus = ptype->initialize(pobjectContext);

   if (!estatus)
   {

      return nullptr;

   }

   return ptype;

}


// __compose __composite


// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   __throw(::exception::exception(error_composite_not_composer_member));

//    //}

//    return pobject->__compose(pcomposite);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource)
// {

//    return __compose(pobject, pcomposite, psource.m_p);

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource)
// {

//    return __compose(pobject, pcomposite, psource.operator SOURCE * ());

// }


// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const SOURCE * psource)
// {
// //
// //#ifdef DEBUG
// //
// //   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
// //
// //   const char * psz = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
// //
// //#endif
// //
// //   if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
// //   {
// //
// //      __throw(::exception::exception(error_composite_not_composer_member));
// //
// //   }

//    return pobject->__compose(pcomposite, psource);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::id & id)
// {

//    //if (((uptr)&pcomposite) < (uptr)pobject || ((uptr)&pcomposite) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//    //{

//    //   __throw(::exception::exception(error_composite_not_composer_member));

//    //}

//    return pobject->__id_compose(pcomposite, id);

// }


// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::type & type)
// {

//    return pobject->__id_compose(pcomposite, (id) type);

// }


// template < typename OBJECT, typename TYPE >
// inline ::estatus __raw_compose_new(OBJECT && pobject, __composite(TYPE) & pcomposite)
// {

//    return pobject->__raw_compose_new(pcomposite);

// }


// template < typename OBJECT, typename TYPE >
// inline ::estatus __compose_new(OBJECT && pobject, __composite(TYPE) & pcomposite)
// {

//    return pobject->__compose_new(pcomposite);

// }














// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite) { return !pcomposite ? __compose(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const SOURCE * psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
// inline ::estatus __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource) { return !pcomposite ? __compose(pobject, pcomposite, psource) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::id & id) { return !pcomposite ? __id_compose(pobject, pcomposite) : ::success; }

// //template < typename OBJECT, typename BASE_TYPE >
// //inline ::estatus __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite, const ::type & type)  { return !pcomposite ? __compose(pobject, pcomposite) : ::success; }

// template < typename OBJECT, typename BASE_TYPE >
// inline ::estatus __defer_compose_new(OBJECT && pobject, __composite(BASE_TYPE) & pcomposite) { return !pcomposite ? __compose_new(pobject, pcomposite) : ::success; }

















// __compose __reference

//
//template < typename OBJECT, typename BASE_TYPE >
//inline ::estatus __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::exception::exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__internal_onwership(preference);
//
//}

template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
inline ::estatus __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource)
{
   return __refer(pobject, preference, psource.m_p);
}

template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
inline ::estatus __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & psource)
{
   return __refer(pobject, preference, psource.operator SOURCE * ());
}

template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
inline ::estatus __refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const SOURCE * psource)
{

//#ifdef DEBUG
//
//   auto size = sizeof(typename ::raw_type < OBJECT>::RAW_TYPE);
//
//   const char * psz = typeid(typename ::raw_type < OBJECT>::RAW_TYPE).name();
//
//#endif
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::exception::exception(error_composite_not_composer_member));
//
//   }

   return pobject->add_reference(preference, psource);

}


//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline ::estatus __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const SOURCE * psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline ::estatus __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource) {}
//
//template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//inline ::estatus __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::member < SOURCE > & psource) {}



//
//template < typename OBJECT, typename BASE_TYPE >
//inline ::estatus __id_refer(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::id & id)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::exception::exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_compose(preference, id);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline ::estatus __id_compose(OBJECT && pobject, __reference(BASE_TYPE) & preference, const ::type & type)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::exception::exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__id_compose(preference, (id)type);
//
//}


//template < typename OBJECT, typename BASE_TYPE >
//inline ::estatus __compose_new(OBJECT && pobject, __reference(BASE_TYPE) & preference)
//{
//
//   if (((uptr)&preference) < (uptr)pobject || ((uptr)&preference) >= ((uptr)pobject) + sizeof(typename ::raw_type < OBJECT>::RAW_TYPE))
//   {
//
//      __throw(::exception::exception(error_composite_not_composer_member));
//
//   }
//
//   return pobject->__compose_new(preference);
//
//}




// __construct

template < typename BASE_TYPE >
inline ::estatus __construct(__pointer(BASE_TYPE) & pbase)
{

   auto & pfactory = ::factory::get_factory < BASE_TYPE >();

   if (pfactory)
   {

      auto ptypeNew = pfactory->call_new();

      if (!ptypeNew)
      {

         ::release(pbase);

         return ::error_no_memory;

      }

      __dynamic_cast(pbase, ptypeNew);

   }
   else
   {

       return ::error_not_implemented;

   }


   if (!pbase)
   {

      return ::error_wrong_type;

   }

   return ::success;

}

template < typename BASE_TYPE >
inline ::estatus __defer_construct(__pointer(BASE_TYPE) & pbase)
{

   ::estatus estatus = ::success_none;

   if(!pbase)
   {

      estatus = __construct(pbase);

   }

   return estatus;

}


template < typename BASE_TYPE >
inline ::estatus __id_construct(__pointer(BASE_TYPE) & pbase, const ::id & id)
{

   auto pfactory = ::factory::get_factory(id);

   if (!pfactory)
   {

      ::release(pbase);

      return ::error_no_factory;

   }

   auto ptypeNew = pfactory->call_new();

   if (!ptypeNew)
   {

      ::release(pbase);

      return ::error_no_memory;

   }

   pbase = ptypeNew;

   if (!pbase)
   {

      return ::error_wrong_type;

   }

   return ::success;

}


template < typename BASE_TYPE >
inline ::estatus __defer_id_construct(__pointer(BASE_TYPE) & pbase, const ::id & id) { return !pbase ? __construct(pbase, id) : ::success; }


template < typename TYPE >
inline ::estatus __construct_new(__pointer(TYPE) & ptype)
{

   ptype = __new(TYPE());

   if (!ptype)
   {

      return ::error_no_memory;

   }

   return ::success;

}


template < typename TYPE >
inline ::estatus __defer_construct_new(__pointer(TYPE) & ptype)
{

   return !ptype ? __construct_new(ptype) : ::estatus(::success);

}
