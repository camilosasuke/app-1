#include "framework.h"
#include "_pcre.h"


pcre_code_impl::pcre_code_impl(pcre_context_impl* pcreContext)
{

   m_pcreContext = pcreContext;

   m_pc = nullptr;

}

 pcre_code_impl::~pcre_code_impl()
{

   if (m_pc != nullptr)
   {

      pcre2_code_free(m_pc);

      m_pc = nullptr;

   }

}


bool pcre_code_impl::compile(const string& str)
{

   int e;

   PCRE2_SIZE eo;

   m_pc = pcre2_compile((PCRE2_SPTR)(const char*)str, str.get_length(), 0, &e, &eo, m_pcreContext->m_pcc);

   if (m_pc == nullptr)
      return false;

   return true;

}
   
bool pcre_code_impl::matches(const string& str)
{

   int c = pcre2_match(m_pc, (PCRE2_SPTR)(const char*)str, str.get_length(), 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

   return c > 0;
}

bool pcre_code_impl::matches(const char* psz, strsize len)
{

   int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

   return c > 0;
}


   ::count pcre_code_impl::match_count(const string& str)
{

   return match_count(str.c_str(), str.length());

}

   
   ::count pcre_code_impl::match_count(const char* psz, strsize len)
{

   int c = pcre2_match(m_pc, (PCRE2_SPTR)psz, len, 0, 0, m_pcreContext->m_pimpl->m_pmd, nullptr);

   return c;
}


__pointer(::str::range_array) pcre_code_impl::matches_ranges(const string& str)
{

   return matches_ranges(str.c_str(), str.get_length());

}


__pointer(::str::range_array) pcre_code_impl::matches_ranges(const char* psz, strsize len)
{

   auto c = match_count(psz, len);

   if (c <= 0)
   {

      return nullptr;

   }

   PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(m_pcreContext->m_pimpl->m_pmd);

   auto prangeaMatches = __new(::str::range_array);

   for (strsize i = 0; i < c; i++)
   {

      prangeaMatches->add(::str::range(ovector[2 * i], ovector[2 * i + 1]));

   }

   return prangeaMatches;


}


bool pcre_code_impl::replace(string& str, const string& strPrefix, string& strRet)
{

   size_t s = max(256, str.get_length() + strPrefix.get_length() * 3);

   int err;

   while (true)
   {

      err = pcre2_substitute(
         m_pc,
         (PCRE2_SPTR8)str.c_str(),
         str.get_length(),
         0,
         PCRE2_SUBSTITUTE_GLOBAL, m_pcreContext->m_pimpl->m_pmd, nullptr, (PCRE2_SPTR8)strPrefix.c_str(), strPrefix.get_length(), (PCRE2_UCHAR8*)strRet.get_string_buffer(s), &s);

      strRet.release_string_buffer(s);

      if (err >= 0)
      {
         return true;

      }
      else if (err != PCRE2_ERROR_NOMEMORY)
      {

         return false;

      }


      s *= 2;

   }

   return true;

}

