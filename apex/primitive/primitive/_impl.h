#pragma once


#include "acme/primitive/comparison/equals.h"


//inline bool __enum_is_failed(const ::estatus & e)
//{
//  return ::failed(e);
//}


//inline duration & duration::operator = (const ::datetime::time_span & span)
//{
//
//  raw_set(span.GetTotalSeconds());
//
//  return *this;
//
//}
//
//
//inline duration & duration::operator += (const ::datetime::time_span & span)
//{
//
//  set(m_iSeconds + span.GetTotalSeconds(), m_iNanoseconds);
//
//  return *this;
//
//}
//
//
//inline duration & duration::operator -= (const ::datetime::time_span & span)
//{
//
//  set(m_iSeconds - span.GetTotalSeconds(), m_iNanoseconds);
//
//  return *this;
//
//}
//
//
//template < class T >
//inline string pointer < T >::type_str()
//{
//
//  return __type_str(T);
//
//}



//inline payload & payload::operator = (::image * pimage)
//{
//
//  set_type(type_image, false);
//
//  ::add_ref(m_pimage, pimage);
//
//  return *this;
//
//}
//
//
//inline payload::payload(::image * pimage)
//{
//
//  m_etype = type_new;
//
//  operator =(pimage);
//
//}

//
//inline type::type(const ::matter * pobject)
//{
//
//  m_strName = typeid(*(matter *)pobject).name();
//
//  demangle(m_strName);
//
//}


//template < typename BASE >
//inline type::type(const __pointer(BASE) & point)
//{
//
//  m_strName = typeid(*((BASE *)point.m_p)).name();
//
//  demangle(m_strName);
//
//}

//
//template < >
//inline uptr uptr_hash < const type & >(const ::type & type)
//{
//
//  return uptr_hash < const string & > (type.m_strName);
//
//}


//inline stream & operator << (stream & stream, const ::type & type)
//{
//
//  stream << type.m_strName;
//
//  return stream;
//
//}
//
//
//inline stream & operator >> (stream & stream, type & type)
//{
//
//  stream >> type.m_strName;
//
//  return stream;
//
//}


//inline bool get_memory::get_base64(const string & str)
//{
//
//  if (::is_set(m_pmemory))
//  {
//
//     m_pmemory->from_base64(str);
//
//     return true;
//
//  }
//  else
//  {
//
//     return System.m_pbase64->decode(m_block, str);
//
//  }
//
//}
//
//
//template < typename PRED >
//inline ::image_result object::get_image(const payload & varFile, ::u64 uTrait, PRED pred)
//{
//
//  return System.get_image(this, varFile, uTrait, pred);
//
//}
//

#include "acme/primitive/primitive/trait_pred.h"



//inline ::index property_set::find_index(const ::id & id, ::index i) const
//{
//
//  for(; i < m_nSize; i++)
//  {
//
//     if (m_pData[i]->m_id == id)
//     {
//
//        return i;
//
//     }
//
//  }
//
//  return -1;
//
//}
//
//
//inline property & property_set::get(const ::id & id)
//{
//
//  auto pproperty = find(id);
//
//  if (!pproperty)
//  {
//
//     pproperty = new property(id);
//
//     add_item(pproperty);
//
//  }
//
//  return *pproperty;
//
//}
//
//
//inline ::property * property_set::find(const ::id & id) const
//{
//
//  auto iFind = find_index(id);
//
//  if(__not_found(iFind))
//  {
//
//     return nullptr;
//
//  }
//
//  return (const_cast < property_set * > (this))->m_pData[iFind];
//
//}
//
//
//inline payload property_set::operator()(const ::id & id, const payload & varDefault) const
//{
//
//  auto pproperty = find(id);
//
//  if (!pproperty)
//  {
//
//     return varDefault;
//
//  }
//
//  return pproperty;
//
//}
//
//
//inline payload property_set::topic(const id & id)
//{
//
//  return &set(id);
//
//}
//
//
//inline payload & property_set::set(const ::id & id)
//{
//
//  auto pproperty = find(id);
//
//  if (!pproperty)
//  {
//
//     pproperty = new property(id);
//
//     add_item(pproperty);
//
//  }
//
//  return *pproperty;
//
//}
//
//
//inline property * payload::find_property(const ::id & id) const
//{
//
//   if (!casts_to(type_propset))
//   {
//
//      return nullptr;
//
//   }
//
//   return propset().find(id);
//
//}


//inline property & payload::get_property(const ::id & id)
//{
//
//   return propset().get(id);
//
//}


//inline string  id::operator +(const char * psz) const
//{
//
//  return to_string() + psz;
//
//}
//
//
//inline string  id::operator +(const string & str) const
//{
//
//  return to_string() +str;
//
//}
//
//
//inline CLASS_DECL_APEX id id::operator + (const id & id) const
//{
//
//  if (is_integer())
//  {
//
//     if (id.is_integer())
//     {
//
//        return (iptr)(m_i + id.m_i);
//
//     }
//     else if (id.is_text())
//     {
//
//        return __str(m_i) + "." + string(id.m_psz);
//
//     }
//     else
//     {
//
//        return *this;
//
//     }
//
//  }
//  else if (id.is_integer())
//  {
//
//     if (is_text())
//     {
//
//        return string(m_psz) + "." + __str(id.m_i);
//
//     }
//     else
//     {
//
//        return id;
//
//     }
//
//  }
//  else if (is_text())
//  {
//
//     if (id.is_text())
//     {
//
//        return string(m_psz) + string(id.m_psz);
//
//     }
//     else
//     {
//
//        return *this;
//
//     }
//
//  }
//  else if (id.is_text())
//  {
//
//     return id;
//
//  }
//  else
//  {
//
//     return ::id();
//
//  }
//
//}
//
//
//inline bool property_set::has_property(id idName) const
//{
//
//  if (::is_null(this))
//  {
//
//     return false;
//
//  }
//
//  const property * pproperty = find(idName);
//
//  return pproperty != nullptr && pproperty->m_etype != ::type_new;
//
//}
//
//
//inline bool property_set::is_true(id idName, bool bDefault) const
//{
//
//  const property * pproperty = find(idName);
//
//  if (pproperty == nullptr)
//  {
//
//     return bDefault;
//
//  }
//
//  return pproperty->is_true(bDefault);
//
//}
//
//
//inline payload property_set::value(id idName) const
//{
//
//  property * pproperty = find(idName);
//
//  if (pproperty == nullptr)
//  {
//
//     return ::error_not_found;
//
//  }
//
//  return *pproperty;
//
//}
//
//
//inline payload property_set::value(id idName, payload varDefault) const
//{
//
//  property * pproperty = find(idName);
//
//  if (pproperty == nullptr)
//  {
//
//     return varDefault;
//
//  }
//
//  return *pproperty;
//
//}
//
//
//inline payload payload::first() const
//{
//
//  return at(0);
//
//}
//
//
//inline payload payload::last() const
//{
//
//  if (array_get_count() == 0)
//  {
//
//     return first();
//
//  }
//  else
//  {
//
//     return at(array_get_upper_bound());
//
//  }
//
//}
//
//
//inline payload payload::first()
//{
//
//  return at(0);
//
//}
//
//
//inline payload payload::last()
//{
//
//  if (array_get_count() == 0)
//  {
//
//     return first();
//
//  }
//  else
//  {
//
//     return at(array_get_upper_bound());
//
//  }
//
//}
//
//
//inline property_set ca_property_set()
//{
//
//  return property_set();
//
//}
//
//
//inline string CLASS_DECL_APEX operator + (const char * psz, const ::id & id)
//{
//
//  return __str(psz) + id.to_string();
//
//}
//
//
///// END property_set

//
//inline __pointer(::handle::ini) operator ""_pini(const char * psz, size_t s)
//{
//
//  return __new(::handle::ini(string(psz, s)));
//
//}
//
//
//inline string CLASS_DECL_APEX operator + (const char * psz, const payload & payload)
//{
//
//  return __str(psz) + payload.get_string();
//
//}
//
//
////inline class payload & payload::operator -= (const class property & property) { operator -=(property);  return *this; }
////inline class payload & payload::operator += (const class property & property) { operator +=(property);  return *this; }
////inline class payload & payload::operator /= (const class property & property) { operator /=(property);  return *this; }
////inline class payload & payload::operator *= (const class property & property) { operator *=(property);  return *this; }
//
//
//inline ::property * payload::find_property(const ::id & id) const
//{
//
//  if (m_etype == type_pvar)
//  {
//
//     return m_pvar->find_property(id);
//
//  }
//  else if (m_etype == type_prop)
//  {
//
//     return m_pprop->find_property(id);
//
//  }
//  else if (m_etype == type_propset)
//  {
//
//     return m_pset->find_property(id);
//
//  }
//
//  return nullptr;
//
//}
//
//
//inline ::index payload::property_index(const ::id & id) const
//{
//
//  if (m_etype == type_pvar)
//  {
//
//     return m_pvar->property_index(id);
//
//  }
//  else if (m_etype == type_prop)
//  {
//
//     return m_pprop->property_index(id);
//
//  }
//  else if (m_etype == type_propset)
//  {
//
//     return m_pset->find_index(id);
//
//  }
//
//  return -1;
//
//}
//
//
//inline property & payload::get_property(const ::id & id)
//{
//
//  if (m_etype == type_pvar)
//  {
//
//     return m_pvar->get_property(id);
//
//  }
//  else if (m_etype == type_prop)
//  {
//
//     return m_pprop->get_property(id);
//
//  }
//  else if (m_etype == type_propset)
//  {
//
//     return m_pset->get(id);
//
//  }
//
//  return propset().get(id);
//
//}
//
//
//inline bool id::begins(const string & strPrefix) const
//{
//
//  if (strPrefix.is_empty())
//  {
//
//     return true;
//
//  }
//
//  if (is_empty())
//  {
//
//     return false;
//
//  }
//  else if (is_integer())
//  {
//
//     char sz[64];
//
//     ansi_from_i64(sz, m_i);
//
//     return ::str::begins(sz, strPrefix);
//
//  }
//  else if (is_text())
//  {
//
//     return ::str::begins(m_psz, strPrefix);
//
//  }
//  else
//  {
//
//     __throw(::exception::exception("Unexpected ::id m_etype"));
//
//  }
//
//}
//
//
//inline bool id::begins_ci(const string & strPrefix) const
//{
//
//  if (strPrefix.is_empty())
//  {
//
//     return true;
//
//  }
//
//  if (is_empty())
//  {
//
//     return false;
//
//  }
//  else if (is_integer())
//  {
//
//     char sz[64];
//
//     ansi_from_i64(sz, m_i);
//
//     return ::str::begins(sz, strPrefix);
//
//  }
//  else if (is_text())
//  {
//
//     return ::str::begins_ci(m_psz, strPrefix);
//
//  }
//  else
//  {
//
//     __throw(::exception::exception("Unexpected ::id m_etype"));
//
//  }
//
//}
//
//
//template < class T >
//template < typename VAR >
//inline pointer < T >  & pointer < T >::operator = (const var_type < VAR > & payload)
//{
//
//  if (payload.this_var()->m_etype == type_element)
//  {
//
//     return operator = (payload.this_var()->m_p);
//
//  }
//  else if (payload.this_var()->m_etype == type_memory)
//  {
//
//     auto pfile = create_memory_file();
//
//     ::binary_stream stream(pfile);
//
//     stream << payload.this_var()->memory();
//
//     string strText;
//
//     stream >> strText;
//
//     if (!stream.fail())
//     {
//
//        if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
//        {
//
//           if(is_set() && m_p->type_name() == strText)
//           {
//
//              ::output_debug_string("POINTER: loading into existing object of same class type (1)");
//
//           }
//           else
//           {
//
//              this->defer_create_new();
//
//              if(is_null())
//              {
//
//                 ::output_debug_string("POINTER: defer_new failed (1.1)");
//
//                 stream.set_fail_bit();
//
//              }
//              else if(m_p->type_name() != strText)
//              {
//
//                 ::output_debug_string("POINTER: allocated object type is different from streamed object type (1.2)");
//
//                 stream.set_fail_bit();
//
//              }
//
//           }
//
//        }
//        else
//        {
//
//           ::id id = stream.text_to_factory_id(strText);
//
//           if(is_set() && m_p->type_name() == id)
//           {
//
//              ::output_debug_string("POINTER: loading into existing object of same class type (2)");
//
//           }
//           else
//           {
//
//              auto p = stream.create_object_from_text(strText);
//
//              if(!p)
//              {
//
//                 ::output_debug_string("POINTER: stream::alloc_object_from_text failed (2.1)");
//
//              }
//              else if(::str::demangle(p->type_name()) != id.to_string())
//              {
//
//                 ::output_debug_string("POINTER: allocated object type is different from streamed object type (2.2)");
//
//                 stream.set_fail_bit();
//
//              }
//              else
//              {
//
//                 operator =(p);
//
//              }
//
//           }
//
//        }
//
//        if (!stream.fail())
//        {
//
//           m_p->read(stream);
//
//        }
//
//     }
//
//     return *this;
//
//  }
//  else
//  {
//
//     return operator =(nullptr);
//
//  }
//
//}
//
//
//inline bool succeeded(const ::payload & payload)
//{
//
//  if (payload.m_etype == type_enum_status)
//  {
//
//     return ::succeeded(payload.m_estatus);
//
//  }
//  else if (payload.is_integer())
//  {
//
//     return ::succeeded(payload.i64());
//
//  }
//  else
//  {
//
//     __throw(::unexpected_situation());
//
//  }
//
//}
//
//
//inline bool succeeded(const ::property & property)
//{
//
//  return ::succeeded((const ::payload &) property);
//
//}
//
//
//inline string property_set::_001Replace(const string & str) const
//{
//
//  return ::papaya::property_set::evaluate(*this, str);
//
//}
//
//
template < typename BASE_TYPE >
inline __result(BASE_TYPE) object::__create()
{

 auto p = ::__create<BASE_TYPE>();

 if (p)
 {

    auto estatus = p->initialize(this);

    if (!estatus)
    {

       return estatus;

    }

 }

 return p;

}


template < typename BASE_TYPE >
inline __result(BASE_TYPE) object::__id_create(const ::id & id)
{

  auto p = ::__id_create<BASE_TYPE>(id);

  if (p)
  {

     auto estatus = p->initialize(this);

     if (!estatus)
     {

        return estatus;

     }

  }

  return p;

}


template < typename TYPE >
inline __result(TYPE) object::__create_new()
{

  ASSERT(::is_set(this));

  auto p = ::__create_new<TYPE>();

  if (p)
  {

     p->initialize(this);

  }

  return p;

}


//template < class T >
//template < typename TEMPLATER >
//inline __pointer(T) & pointer < T >::create(TEMPLATER)
//{
//
//  __construct(*this);
//
//  return *this;
//
//}
//
//
//template < class T >
//template < typename TYPE, typename OBJECT >
//inline __pointer(T) & pointer < T >::create(OBJECT * pobjectContext)
//{
//
//  auto p = __create < TYPE >();
//
//  if (p)
//  {
//
//     p->initialize(pobjectContext);
//
//  }
//
//  return operator =(p);
//
//}
//
//
//template < class T >
//template < typename TYPE, typename OBJECT >
//inline __pointer(T) & pointer < T >::create(OBJECT * pobjectContext, bool bCreate)
//{
//
//  if (bCreate)
//  {
//
//     defer_create(pobjectContext);
//
//  }
//  else
//  {
//
//     release();
//
//  }
//
//  return *this;
//
//}


template < typename BASE_TYPE >
inline ::estatus object::__compose(__composite(BASE_TYPE) & pbase)
{

  if (!pbase)
  {

     auto & pfactory = ::factory::get_factory < BASE_TYPE >();

     if (!pfactory)
     {

        return ::error_no_factory;

     }

     auto ptypeNew = pfactory->call_new();

     if (!ptypeNew)
     {

        return ::error_no_memory;

     }

     pbase = ptypeNew;

     if (!pbase)
     {

        return error_wrong_type;

     }

     auto estatus = pbase->initialize(this);

     if (!estatus)
     {

        return estatus;

     }

     estatus = add_composite(pbase);

     if (!estatus)
     {

        return estatus;

     }

  }

  return ::success;

}


template < typename BASE_TYPE >
inline ::estatus object::__raw_compose(__composite(BASE_TYPE) & pbase)
{

  if (!pbase)
  {

     auto & pfactory = ::factory::get_factory < BASE_TYPE >();

     if (!pfactory)
     {

        return ::error_no_factory;

     }

     auto ptypeNew = pfactory->call_new();

     if (!ptypeNew)
     {

        return ::error_no_memory;

     }

     pbase = ptypeNew;

     if (!pbase)
     {

        return error_wrong_type;

     }

     auto estatus = add_composite(pbase);

     if (!estatus)
     {

        return estatus;

     }

  }

  return ::success;

}


template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__compose(__composite(BASE_TYPE) & pbase, const SOURCE * psource OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  pbase = psource;

  if (!pbase)
  {

     return error_wrong_type;

  }

  auto estatus = pbase->initialize(this);

  if (!estatus)
  {

     return estatus;

  }

  m_estatus = add_composite(pbase OBJ_REF_DBG_COMMA_ARGS);

  return m_estatus;

}

template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__raw_compose(__composite(BASE_TYPE) & pbase, const SOURCE * psource)
{

  pbase = psource;

  if (!pbase)
  {

     return error_wrong_type;

  }

  m_estatus = add_composite(pbase);

  return m_estatus;

}

template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__compose(__composite(BASE_TYPE) & pbase, const __pointer(SOURCE) & psource OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return __compose(pbase, psource.get() OBJ_REF_DBG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__raw_compose(__composite(BASE_TYPE) & pbase, const __pointer(SOURCE) & psource)
{

  return __raw_compose(pbase, psource.get());

}



template < typename BASE_TYPE >
inline ::estatus object::__id_compose(__composite(BASE_TYPE) & pbase, const ::id & id)
{

  auto & pfactory = ::factory::get_factory(id);

  if (!pfactory)
  {

     return ::error_no_factory;

  }

  auto ptypeNew = pfactory->call_new();

  if (!ptypeNew)
  {

     return ::error_no_memory;

  }

  pbase = ptypeNew;

  if (!pbase)
  {

     return ::error_wrong_type;

  }

  auto estatus = pbase->initialize(this);

  if (!estatus)
  {

     return estatus;

  }

  estatus = add_composite(pbase);

  if (!estatus)
  {

     return estatus;

  }

  return estatus;

}


template < typename TYPE >
inline ::estatus object::__raw_compose_new(__composite(TYPE) & p)
{

  auto ptypeNew = __new(TYPE);

  if (!ptypeNew)
  {

     return ::error_no_memory;

  }

  p = ptypeNew;

  auto estatus = add_composite(p);

  if (!estatus)
  {

     p.clear_member();

     return estatus;

  }

  return estatus;

}


template < typename TYPE >
inline ::estatus object::__compose_new(__composite(TYPE) & p)
{

  auto ptypeNew = __new(TYPE);

  if (!ptypeNew)
  {

     return ::error_no_memory;

  }

  auto estatus = ptypeNew->initialize(this);

  if (!estatus)
  {

     return estatus;

  }

  p = ptypeNew;

  estatus = add_composite(p);

  if (!estatus)
  {

     p.clear_member();

     return estatus;

  }

  return estatus;

}


template < typename TYPE >
inline ::estatus object::__construct(__pointer(TYPE) & p)
{

  auto estatus = ::__construct(p);

  if (estatus && p)
  {

     estatus = p->initialize(this);

  }

  return estatus;

}


template < typename TYPE >
inline ::estatus object::__id_construct(__pointer(TYPE) & p, const ::id & id)
{

  auto estatus = ::__id_construct(p, id);

  if (estatus && p)
  {

     estatus = p->initialize(this);

  }

  return estatus;

}


template < typename TYPE >
inline ::estatus object::__construct_new(__pointer(TYPE) & p)
{

  auto estatus = ::__construct_new(p);

  if (estatus)
  {

     estatus = p->initialize(this);

  }

  return estatus;

}


template < typename BASE_TYPE >
inline ::estatus object::__release(__composite(BASE_TYPE) & pcomposite OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  if (pcomposite)
  {

     sync_lock sl(mutex());

     if (m_pcompositea)
     {

        if (m_pcompositea->remove(pcomposite.get()) >= 0)
        {

           pcomposite.clear_member();

        }

     }

  }

  return ::success;

}


template < typename BASE_TYPE >
inline ::estatus object::__release(__reference(BASE_TYPE) & preference OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  if (preference)
  {

     sync_lock sl(mutex());

     if (m_preferencea)
     {

        if (m_preferencea->remove(preference.get()) >= 0)
        {

           //preference->release(OBJ_REF_DBG_ARGS);

           preference.clear_member();

        }
        else
        {

           return ::error_failed;

        }

     }

  }

  return ::success;

}


template < typename SOURCE >
inline ::estatus object::release_reference(__pointer(SOURCE) & psource OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return release_reference(psource.m_p);

}


CLASS_DECL_APEX void object_on_add_composite(const matter * pbase);


template < typename BASE_TYPE >
inline ::estatus object::add_composite(__composite(BASE_TYPE) & pcomposite OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return add_composite(pcomposite.get() OBJ_REF_DBG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__refer(__reference(BASE_TYPE) & preference, const __pointer(SOURCE) & psource  OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return __refer(preference, psource.get()  OBJ_REF_DBG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__refer(__reference(BASE_TYPE) & preference, const ::primitive::member < SOURCE > & pmember OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return __refer(preference, pmember.get()  OBJ_REF_DBG_COMMA_ARGS);

}


template < typename BASE_TYPE, typename SOURCE >
inline ::estatus object::__refer(__reference(BASE_TYPE) & preference, const SOURCE * psource OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  preference = psource;

  if (!preference)
  {

     return error_wrong_type;

  }

  return add_reference(preference OBJ_REF_DBG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::estatus object::add_reference(__pointer(SOURCE) & psource  OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return add_reference(psource.get() OBJ_REF_DBG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::estatus object::add_reference(__reference(SOURCE) & preference OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  return add_reference(preference.get() OBJ_REF_DBG_COMMA_ARGS);

}


template < typename SOURCE >
inline ::estatus object::add_reference(SOURCE * psource OBJ_REF_DBG_COMMA_PARAMS_DEF)
{

  ::matter * pmatter = psource;

  if (::is_null(pmatter))
  {

     return error_wrong_type;

  }

  return add_reference(pmatter OBJ_REF_DBG_COMMA_ARGS);

}


//template < typename T >
//inline __pointer(T) move_transfer(T * p) { return ::pointer < T >(e_move_transfer, p); }


inline const char * object::topic_text() { return ::is_null(m_pmeta) ? nullptr : m_pmeta->m_strTopicText; }


inline payload object::context_value(const payload& payload)
{

  ::payload varContextValue;

  varContextValue["context"] = get_context();

  varContextValue["value"] = payload;

  return varContextValue;

}


inline void object::defer_set_context_object(::layered * pobjectContext)
{

  if (::is_null(get_context_object()) && ::is_set(pobjectContext))
  {

     set_context_object(pobjectContext);

  }

}


//#include "_property_set_composite_impl.h"


//template < typename TYPE >
//TYPE & operator |=(TYPE & o, enum_object eobject)
//{
//
//  o.set(eobject);
//
//  return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator +=(TYPE & o, enum_object eobject)
//{
//
//  o.set(eobject);
//
//  return o;
//
//}
//
//
//template < typename TYPE >
//TYPE & operator -=(TYPE & o, enum_object eobject)
//{
//
//  o.clear(eobject);
//
//  return o;
//
//}


//template < typename T >
//template < typename TEMPLATER >
//inline __pointer(T) & pointer<T> ::defer_create(TEMPLATER)
//{
//
//  if (is_null())
//  {
//
//     operator=(__create < TYPE >());
//
//  }
//
//  return *this;
//
//}
//
//
//template < typename T >
//template < typename TYPE, typename OBJECT  >
//inline __pointer(T) & pointer<T> ::defer_create(OBJECT * pobjectContext)
//{
//
//  if (is_null())
//  {
//
//     operator=(__create < TYPE >(pobjectContext));
//
//  }
//
//  return *this;
//
//}
//
//
//template < class T >
//inline stream & operator << (stream & os, const pointer < T > & sp)
//{
//
//  os << *sp.m_p;
//
//  return os;
//
//}
//
//
//template < class T >
//inline stream & operator >> (stream & is, pointer < T > & sp)
//{
//
//  is >> *sp.m_p;
//
//  return is;
//
//}
//

inline ::estatus context::load_from_file(::matter* pobject, const ::payload& varFile, const payload* pvarOptions)
{

  if (pvarOptions)
  {

     return _load_from_file(pobject, varFile, *pvarOptions);

  }
  else
  {

     return _load_from_file(pobject, varFile, type_empty_argument);

  }

}


inline ::estatus context::load_from_file(::matter* pobject, const ::payload& varFile)
{

  return _load_from_file(pobject, varFile, type_empty_argument);

}


inline ::estatus context::save_to_file(const ::payload& varFile, const payload* pvarOptions, const ::matter * pobject)
{

  if (pvarOptions)
  {

     return _save_to_file(varFile, *pvarOptions, pobject);

  }
  else
  {

     return _save_to_file(varFile, type_empty_argument, pobject);

  }

}


inline ::estatus context::save_to_file(const ::payload& varFile, const ::matter* pobject)
{

  return _save_to_file(varFile, type_empty_argument, pobject);

}




inline ::file_result object::get_reader(const payload & varFile, efileopen eopen)
{

  return get_file(varFile, eopen | ::file::mode_read) ;

}


inline ::file_result object::get_writer(const payload & varFile, efileopen eopen)
{

  return get_file(varFile, eopen | ::file::mode_write);

}


//#ifndef DEBUG
//
//
//inline i64 matter::add_ref(OBJ_REF_DBG_PARAMS_DEF)
//{
//
//  return atomic_increment(&m_countReference);
//
//}
//
//
//inline i64 matter::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
//{
//
//  return atomic_decrement(&m_countReference);
//
//}
//
//
//inline i64 matter::release(OBJ_REF_DBG_PARAMS_DEF)
//{
//
//  i64 i = dec_ref(OBJ_REF_DBG_ARGS);
//
//  if (i == 0)
//  {
//
//     delete_this();
//
//  }
//
//  return i;
//
//}
//
//#endif





template < typename TYPE >
inline void context_object::set(const ::id & id, const TYPE & t)
{

  ::assign(value(id), t);

  set(e_object_property_set_modified);

}


template < typename TYPE >
inline void context_object::get(const ::id & id, TYPE & t)
{

  ::assign(t, value(id));

}


//inline payload::operator string & ()
//{
//
//  if (m_etype == ::type_pvar)
//  {
//
//     return m_pvar->operator string & ();
//
//  }
//  else if (m_etype == ::type_prop)
//  {
//
//     return m_pprop->operator string & ();
//
//  }
//  else if (m_etype == ::type_pstring)
//  {
//
//     return *m_pstr;
//
//  }
//  else if (m_etype != ::type_string)
//  {
//
//     m_str = get_string();
//
//     set_type(type_string, false);
//
//  }
//
//  return m_str;
//
//}
//

//inline payload::operator string() const
//{
//
//    return get_string();
//
//}

#define IMPL_VAR_REF(TYPE, VAR, ENUM)        \
  inline payload::operator TYPE &()                  \
  {                                         \
                                            \
     if(m_etype == ::type_pvar)        \
     {                                      \
                                            \
        return m_pvar->operator TYPE &();   \
                                            \
     }                                      \
     else if(m_etype == ::type_prop)        \
     {                                      \
                                            \
        return m_pprop->operator TYPE &();   \
                                            \
     }                                      \
     else if(m_etype == ::type_p ## ENUM)        \
     {                                      \
                                            \
        return *m_p ## VAR;                 \
                                            \
     }                                      \
     else if(m_etype == ::type_ ## ENUM)    \
     {                                      \
                                            \
        return m_ ## VAR;                   \
                                            \
     }                                      \
     else                                   \
     {                                      \
                                            \
        set_type(::type_ ## ENUM, true);   \
                                            \
        return m_ ## VAR;                   \
                                            \
     }                                      \
                                            \
  }


//#define IMPL_VAR_REF1(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF1(bool, b);
//#undef IMPL_VAR_REF1
//
//
//#define IMPL_VAR_REF2(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, VAR)
//IMPL_VAR_REF2(::i8, i8);
//IMPL_VAR_REF2(::u8, u8);
//IMPL_VAR_REF2(::i16, i16);
//IMPL_VAR_REF2(::u16, u16);
//IMPL_VAR_REF2(::i32, i32);
//IMPL_VAR_REF2(::u32, u32);
//IMPL_VAR_REF2(::i64, i64);
//IMPL_VAR_REF2(::u64, u64);
//#undef IMPL_VAR_REF2
//
//
//#define IMPL_VAR_REF3(TYPE, VAR) IMPL_VAR_REF(TYPE, VAR, TYPE)
//IMPL_VAR_REF3(float, f);
//IMPL_VAR_REF3(double, d);
//#undef IMPL_VAR_REF3
//
//
//#undef IMPL_VAR_REF


template < typename TYPE >
inline ::estatus object::__construct(::thread_pointer & p, void (TYPE:: * pfn)(), e_priority epriority)
{

  p = fork(pfn, epriority);

  if (!p)
  {

     return error_failed;

  }

  return p->m_estatus;

}


template < typename TYPE >
inline ::estatus object::__construct_below_normal(::thread_pointer & p, void (TYPE:: * pfn)())
{

  return __construct(p, pfn, priority_below_normal);

}


template < typename TYPE >
inline ::thread_pointer object::__start_thread(const ::id & id, void(TYPE:: * pfn)(), e_priority epriority)
{

  auto pfork = fork(pfn, epriority);

  get_property_set()[__id(thread)][id] = pfork;

  return pfork;

}

//
//inline payload & payload::operator = (::memory * pmemory)
//{
//
//   set_element(pmemory);
//
//   return *this;
//
//}




//template < typename HANDLER, typename TYPE >
//void object::start_traits(__pointer(HANDLER) phandler, __pointer(TYPE) ptype)
//{
//
//  fork([phandler, ptype]()
//     {
//
//        for(index i = 0; i < ptype->m_ptraits->m_piaTraits->get_count(); i++)
//        {
//
//           auto iTrait = ptype->m_ptraits->m_piaTraits->element_at(i);
//
//           auto estatus = phandler->trait(ptype, iTrait);
//
//           ptype->m_ptraits->m_pestatusa->set_at_grow(i, estatus);
//
//           if (::failed(estatus))
//           {
//
//              return;
//
//           }
//
//        }
//
//     });
//
//
//
//
//}
//
//


template < typename PRED >
inline void add_routine(::promise::routine_array & procedurea, PRED pred)
{
   
   procedurea.add(__routine(pred));

}


template < typename PRED >
inline void add_process(::promise::process_array & futurevara, PRED pred)
{

   futurevara.add(__process(pred));
   
}


//inline payload::operator ::memory & ()
//{
//
//  return this->memory();
//
//}
//
//
//inline payload::operator ::memory() const
//{
//
//  return this->memory();
//
//}
//
//
//
//
//
//inline payload::operator ::estatus &()
//{
//
//  if(m_etype == ::type_pvar)
//  {
//
//     return m_pvar->operator ::estatus &();
//
//  }
//  else if(m_etype == ::type_prop)
//  {
//
//     return m_pprop->operator ::estatus &();
//
//  }
//  else if(m_etype == ::type_enum_status)
//  {
//
//     return m_estatus;
//
//  }
//  else
//  {
//
//     set_type(::type_enum_status, true);
//
//     return m_estatus;
//
//  }
//
//}
//
//
//
//inline bool type::operator == (const ::id& id) const
//{
//
//  return m_strName == id.to_string();
//
//}
//
//
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const payload& payload) :
//  string_base(payload.to_string())
//{
//
//
//}
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const property& property) :
//  string_base(property.to_string())
//{
//
//
//}
//
//
//
//template < typename TYPE_CHAR >
//inline string_base < TYPE_CHAR >::string_base(const id& id) :
//  string_base(id.to_string())
//{
//
//
//}
//
//
//
//
//
//  template < class T >
//  inline __pointer(T) payload::cast(T * pDefault)
//  {
//
//     if (m_etype == type_pvar && m_pvar != nullptr)
//     {
//
//        return m_pvar->cast < T >(pDefault);
//
//     }
//     else if (m_etype == type_prop && m_pprop != nullptr)
//     {
//
//        return m_pprop->cast < T >(pDefault);
//
//     }
//
//     auto p = cast < T >();
//
//     if (!p)
//     {
//
//        return pDefault;
//
//     }
//
//     return p;
//
//  }
//
//
//
//
//
//     template < class T >
//  inline T & payload::get_cast(T * pDefault)
//  {
//
//     if (m_etype == type_pvar && m_pvar != nullptr)
//     {
//
//        return m_pvar->get_cast < T >(pDefault);
//
//     }
//
//     if (m_etype == type_prop && m_pprop != nullptr)
//     {
//
//        return m_pprop->get_cast <T>(pDefault);
//
//     }
//
//     if (m_etype != type_element)
//     {
//
//        return defer_create_type < T >(pDefault);
//
//     }
//
//     auto p = cast < T >();
//
//     if (!p)
//     {
//
//        return defer_create_type < T >(pDefault);
//
//     }
//
//     return *p;
//
//  }
//
//
//
//     template < class T >
//  inline __pointer(T) payload::cast()
//  {
//
//     if(m_etype == type_pvar && m_pvar != nullptr)
//        return m_pvar->cast < T >();
//     if (m_etype == type_prop && m_pprop != nullptr)
//        return m_pprop->cast < T >();
//
//#define CAST_ELEMENT(P, ENUM_TYPE) \
//if(m_etype == ENUM_TYPE) { return dynamic_cast < T * >(P); }
//     CAST_ELEMENT(m_p, type_element);
//     CAST_ELEMENT(m_pstra, type_stra);
//     CAST_ELEMENT(m_pia, type_inta);
//     CAST_ELEMENT(m_pvara, type_vara);
//     CAST_ELEMENT(m_pset, type_propset);
//     CAST_ELEMENT(m_pi64a, type_i64a);
//     CAST_ELEMENT(m_pmemory, type_memory);
//     CAST_ELEMENT(m_ppath, type_path);
//     CAST_ELEMENT(m_pimage, type_image);
//     return nullptr;
//#undef CAST_ELEMENT
//
//  }
//


//template < typename PRED >
//void routine::pred(PRED pred)
//{
//
//  m_pobjectTask = __task_procedure(pred);
//
//}
//
//template < typename PRED >
//inline void callback::pred(PRED pred)
//{
//
//  m_pobjectTask = __task_callback(pred);
//
//}
//



template < typename TYPE >
inline __pointer(TYPE) context_object::cast(const ::id & id)
{

  return value(id).cast < TYPE>();

}







//
//template < typename T >
//inline __pointer(T) payload::pointer() const
//{
//
//  auto pproperty = find_pointer < T >();
//
//  if(!pproperty)
//  {
//
//     return nullptr;
//
//  }
//
//  return pproperty->template cast < T > ();
//
//}

//
//inline payload __visible(payload varOptions, bool bVisible)
//{
//
//  varOptions["visible"] = bVisible;
//
//  return varOptions;
//
//}



template < typename PRED >
inline ::count fork_count_end(::object* pobject, ::count iCount, PRED pred, index iStart, ::e_priority epriority)
{

  if (iCount <= 0)
  {

     return -1;

  }

  auto pgroup = System.thread_group(epriority);

  sync_lock slGroup(pgroup->mutex());

  ///   auto ptool = System.thread_tool(op_fork_count);

  if (pgroup == nullptr || pgroup->get_count() <= 1)
  {

     for (index i = iStart; i < iCount; i++)
     {

        pred(i);

     }

     return 1;

  }

  if (!pgroup->prepare(::e_thread_op_fork_count, iCount - iStart))
  {

     return -1;

  }

  sync_array ptra;

  ::count iScan = max(1, min(iCount - iStart, pgroup->thread_count()));

  for (index iOrder = 0; iOrder < iScan; iOrder++)
  {

     __pointer(pred_holder_base) pbase = __new(forking_count_pred < PRED > (pobject, iOrder, iOrder + iStart, iScan, iCount, pred));

     if (!pgroup->add_pred(pbase))
     {

        return -1;

     }

  }

  if (!(*pgroup)())
  {

     return -1;

  }

  return iScan;

}


//inline void callback::receive_response(const payload & payload) const
//{
//
//  if (!m_pobjectTask)
//  {
//
//     return;
//
//  }
//
//  return m_pobjectTask->receive_response(payload);
//
//}


template < typename TYPE >
inline ::estatus context_object::__construct_new(__pointer(TYPE)& pbase)
{

  ::estatus estatus = ::__construct_new(pbase);

  if (!estatus)
  {

     return estatus;

  }

  estatus = pbase->initialize(get_context_object());

  if (!estatus)
  {

     return estatus;

  }

  return estatus;

}


//template < typename PRED >
//routine::routine(const ::id& id, PRED pred, ::matter* pobjectHold) : function_base(id, __new(__λprocedure < PRED >(pred, pobjectHold))) { }
//template < typename PRED >
//routine::routine(PRED pred, ::matter* pobjectHold) : routine(::id(), pred, pobjectHold) { }



////namespace user
////{
//
//
//  inline message_box::message_box(const payload& payload)
//  {
//
//     if (payload.get_type() == type_string)
//     {
//
//        m_strMessage = payload;
//
//     }
//     else if (payload.has_property("message") && payload["message"].has_char())
//     {
//
//        m_strMessage = payload["message"];
//
//     }
//     else if (payload.has_property("format") && payload["format"].has_char())
//     {
//
//        m_strMessage = payload.propset().format(payload["format"]);
//
//     }
//
//     m_puserprimitive = __user_primitive(payload["parent"].cast < ::layered >());
//     m_strTitle = payload["title"];
//     m_emessagebox = (::emessagebox) payload["flags"].i64();
//
//     //if (m_puserprimitive)
//     //{
//
//     //   //m_oswindow = m_puserinteractionParent->get_safe_handle();
//
//     //}
//
//  }
//
//
////} // namespace user
////
////
////

//#include "property_set_papaya.h"



inline ::estatus object::defer_start(::thread_pointer& pthread, const ::promise::routine & routine)
{

   auto estatus = __defer_construct(pthread);

   if (!estatus)
   {

      return estatus;

   }

   pthread->m_pmatter = routine;

   return pthread->begin_task();

}



