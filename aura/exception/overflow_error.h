#pragma once


class CLASS_DECL_AURA overflow_error :
   public ::exception::error
{
   // aura class for resource-critical aura API exceptions
   // handles composite and initialization of an error message
public:


   overflow_error(const char * pszMessage = nullptr);
   virtual ~overflow_error();


};


