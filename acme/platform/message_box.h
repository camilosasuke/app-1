#pragma once


class CLASS_DECL_ACME message_box
{
public:


   __pointer(::layered)        m_puserprimitive;
   string                           m_strMessage;
   string                           m_strTitle;
   ::emessagebox                    m_emessagebox;
   ::duration                       m_durationTimeout;
   ::promise::process               m_future;


   message_box();
   message_box(const payload & payload);
   virtual ~message_box();


   //::estatus show(::matter* pobject);


};




inline payload operator + (payload payload, const ::enum_message_box& emessagebox)
{

   if (payload.get_type() != type_propset)
   {

      payload["message"] = payload.get_string();

   }

   payload["flags"] = (::i64) emessagebox;

   return payload;

}


template < typename TYPE_CHAR >
inline payload operator +(const string_base < TYPE_CHAR >& str, const enum_message_box& e)
{

   return payload(str) + e;

}




inline payload operator + (const char* psz, const ::enum_message_box& emessagebox)
{

   return payload(psz) + emessagebox;

}


CLASS_DECL_ACME ::estatus os_message_box(const char* pszText, const char* pszTitle = nullptr, ::emessagebox emessagebox = e_message_box_ok, const ::promise::process & process = ::promise::process());



