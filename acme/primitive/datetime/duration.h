#pragma once


class CLASS_DECL_ACME duration
{
public:


   enum enum_unit
   {

      unit_nanos,
      unit_micros,
      unit_millis,
      unit_seconds,
      unit_minutes,
      unit_hours,
      unit_days

   };


   //e_duration     m_eduration;
   ::i64          m_iNanoseconds;
   ::i64          m_iSeconds;


   explicit duration(long double dSeconds);
   duration(i64 iSeconds = 0, i64 iNanoseconds = 0) : m_iSeconds(iSeconds), m_iNanoseconds(iNanoseconds) {}
   duration(enum_normalize, i64 iSeconds, i64 iNanoseconds);
   duration(u64 uSeconds, i64 iNanoseconds = 0) : duration((::i64) uSeconds, iNanoseconds) {}
   duration(i32 iSeconds, i64 iNanoseconds = 0) : duration((::i64) iSeconds, iNanoseconds) {}
   duration(u32 uSeconds, i64 iNanoseconds = 0) : duration((::i64) uSeconds, iNanoseconds) {}
   duration(const class ::nanos & nanos);
   duration(const class ::micros & micros);
   duration(const class ::millis & millis);
   duration(const class ::secs & secs);
   duration(const class ::duration & duration);


   inline void raw_set(i64 iSeconds, i64 iNanoseconds = 0);
   inline void set(i64 iSeconds, i64 iNanoseconds);
   inline void set_null();
   static inline duration raw_create(i64 iSeconds, i64 iNanoseconds);
   static inline duration create(i64 iSeconds, i64 iNanoseconds);
   static inline duration create_null();


   void fset(long double dSeconds);
   void fset(long double dSeconds, double dNanoseconds);
   static inline duration fcreate(long double dSeconds, double dNanoseconds);


   void set(i64 i, enum_unit eunit);
   void set(long double d, enum_unit eunit);


   inline ::nanos nanos() const;
   inline ::micros micros() const;
   inline ::millis millis() const;
   inline ::secs secs() const;
   inline ::u32 u32_millis() const;
   inline bool is_pos_infinity() const;
   inline bool is_infinite() const;
   inline bool is_null() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   //inline bool operator == (const duration & duration) const;


   duration & operator = (const ::secs & secs);
   duration & operator = (const ::millis & millis);
   duration & operator = (const ::micros & micros);
   duration & operator = (const ::nanos & nanos);
   duration & operator = (const ::duration & duration);


   void normalize();


   inline operator bool() const;


   inline duration operator - (const ::duration & duration) const { return { e_normalize, m_iSeconds - duration.m_iSeconds, m_iNanoseconds - duration.m_iNanoseconds }; }
   inline duration operator + (const ::duration & duration) const { return { e_normalize, m_iSeconds + duration.m_iSeconds, m_iNanoseconds + duration.m_iNanoseconds }; }
   inline duration & operator -= (const ::duration & duration) { m_iSeconds -= duration.m_iSeconds; m_iNanoseconds -= duration.m_iNanoseconds; normalize();  return *this; }
   inline duration & operator += (const ::duration & duration) { m_iSeconds += duration.m_iSeconds; m_iNanoseconds += duration.m_iNanoseconds; normalize();  return *this; }


   inline duration & operator = (const ::datetime::time_span & span);
   inline duration & operator += (const ::datetime::time_span & duration);
   inline duration & operator -= (const ::datetime::time_span & duration);


   inline time_t GetTimeSpan() const;


   //duration operator - (const duration & duration) const;
   //duration operator + (const duration & duration) const;


   void sleep() const;


};


inline duration::duration(enum_normalize, ::i64 iSeconds, ::i64 iNanoseconds)
{

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

   normalize();

}


inline duration::duration(long double dSeconds)
{

   fset(dSeconds);

}


inline duration::duration(const ::duration& duration) :
   m_iNanoseconds(duration.m_iNanoseconds),
   m_iSeconds(duration.m_iSeconds)
{

}


inline void duration::raw_set(i64 iSeconds, i64 iNanoseconds)
{

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

}


inline void duration::set(i64 iSeconds, i64 iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


inline void duration::set_null()
{

   raw_set(0, 0);

}


inline duration duration::raw_create(i64 iSeconds, i64 iNanoseconds)
{

   duration duration;

   duration.raw_set(iSeconds, iNanoseconds);

   return duration;

}


inline duration duration::fcreate(long double d, double dNano)
{

   duration duration;

   duration.fset(d, dNano);

   return duration;

}


inline duration duration::create(i64 iSeconds, i64 iNanoseconds)
{

   duration duration;

   duration.set(iSeconds, iNanoseconds);

   return duration;

}


inline duration duration::create_null()
{

   duration duration;

   duration.set_null();

   return duration;

}


inline ::millis duration::millis() const
{

   return m_iSeconds * 1000 + m_iNanoseconds / 1000000;

}


inline ::u32 duration::u32_millis() const
{

   return is_infinite() ? UINT_MAX : (::u32) MIN((::i64) UINT_MAX, millis().m_iMilliseconds);

}


inline ::micros duration::micros() const
{

   return m_iSeconds * 1000000 + m_iNanoseconds / 1000;

}


inline nanos duration::nanos() const
{

   return m_iNanoseconds + m_iSeconds * 1'000'000'000;

}


inline bool duration::is_pos_infinity() const
{

   return m_iSeconds < 0;

}


inline bool duration::is_infinite() const
{

   return m_iSeconds < 0;

}


bool duration::is_null() const
{

   return m_iSeconds == 0 && m_iNanoseconds == 0;

}


inline duration duration::infinite()
{

   return {-1,0};

}


inline duration duration::pos_infinity()
{

   return {-1, 0};

}


inline duration duration::zero()
{

   return {0, 0};

}


//inline bool duration::operator == (const duration & duration) const
//{
//
//   return m_iSeconds == duration.m_iSeconds && m_iNanoseconds == duration.m_iNanoseconds;
//
//}


class CLASS_DECL_ACME nanosecond :
   public duration
{
public:


   inline nanosecond(i64 iNanoseconds = 0);
   inline nanosecond(u64 uNanoseconds) : nanosecond((::i64)uNanoseconds){}
   inline nanosecond(i32 iNanoseconds);
   inline nanosecond(u32 dwNanoseconds);
   nanosecond(long double dNanoseconds);

};


//inline nanosecond operator "" _ns(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME microsecond :
   public duration
{
public:


   inline microsecond(i64 iMicroseconds = 0);
   inline microsecond(u64 uMicroseconds) : microsecond((::i64)uMicroseconds) {}
   inline microsecond(i32 iMicroseconds);
   inline microsecond(u32 uMicroseconds);
   microsecond(long double dMicroseconds);

};


//inline micros operator "" _us(unsigned long long int u) { return (::u64) u; }


class CLASS_DECL_ACME millisecond :
   public duration
{
public:


   inline millisecond(i64 iMillisecond = 0);
   inline millisecond(u64 uMillisecond);
   inline millisecond(i32 iMillisecond);
   inline millisecond(u32 uMillisecond);
   inline millisecond(double dMillisecond);
   millisecond(long double dMillisecond);

};
//
//const char *
//unsigned long long int
//long double
//char
//wchar_t
//char16_t
//char32_t
//const char *, std::size_t
//const wchar_t *, std::size_t
//const char16_t *, std::size_t
//const char32_t *, std::size_t





inline duration::duration(const ::millis & millis)
{

    m_iSeconds = millis.m_iMilliseconds / 1'000;

    m_iNanoseconds = (millis.m_iMilliseconds % 1'000) * 1'000'000;

}


inline duration::duration(const ::secs & secs)
{

   m_iSeconds = secs.m_iSeconds;

   m_iNanoseconds = 0;

}


inline  duration::duration(const ::micros & micros)
{

    m_iSeconds = micros.m_iMicroseconds / 1'000'000;

    m_iNanoseconds = (micros.m_iMicroseconds % 1'000'000) * 1'000;

}


inline  duration::duration(const ::nanos & nanos)
{

    m_iSeconds = nanos.m_iNanoseconds / 1'000'000'000;

    m_iNanoseconds = nanos.m_iNanoseconds % 1'000'000'000;

}


class CLASS_DECL_ACME seconds :
   public duration
{
public:


   inline seconds(i64 iSeconds = 0);
   inline seconds(u64 u) :seconds((::i64)u) {}
   inline seconds(i32 iSeconds);
   inline seconds(u32 dwSeconds);
   seconds(long double dSeconds);


};


//inline seconds operator "" _s(unsigned long long int u) { return (::u64) u; }
inline seconds operator "" _s(long double d) { return d; }


class CLASS_DECL_ACME one_second :
   public duration
{
public:


   one_second() : duration(1) {}


};


class CLASS_DECL_ACME minutes :
   public duration
{
public:


   inline minutes(i64 iMinutes = 0);
   inline minutes(u64 u) :minutes((::i64)u) {}
   inline minutes(i32 iMinutes);
   inline minutes(u32 dwMinutes);
   inline minutes(long double dMinutes);


};


inline minutes operator "" _min(unsigned long long int u) { return (::u64) u; }

class CLASS_DECL_ACME one_minute :
   public duration
{
public:


   one_minute() : duration(60) {}


};


class CLASS_DECL_ACME hours :
   public duration
{
public:


   inline hours(i64 iHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(u64 u, int iMinutes = 0, int iSeconds = 0) :hours((::i64)u, iMinutes, iSeconds) {}
   inline hours(i32 iHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(u32 dwHours, int iMinutes = 0, int iSeconds = 0);
   inline hours(long double dHours);


};


inline hours operator "" _hours(unsigned long long int u) { return (::u64) u; }
inline hours operator "" _hour(unsigned long long int u) { return (::u64) u; }

class CLASS_DECL_ACME one_hour :
   public hours
{
public:


   one_hour(int iMinutes = 0, int iSeconds = 0) : hours(1, iMinutes, iSeconds) {}


};


class CLASS_DECL_ACME days :
   public duration
{
public:


   inline days(i64 iDays = 0);
   inline days(u64 u) :days((::i64)u) {}
   inline days(i32 iDays);
   inline days(u32 dwDays);
   inline days(long double dDays);


};


inline days operator "" _days(unsigned long long int u) { return (::u64) u; }
inline days operator "" _day(unsigned long long int u) { return (::u64) u; }


inline nanosecond::nanosecond(i64 i) :
   duration(i / (1'000'000'000), (i % (1'000'000'000)))
{

}


inline nanosecond::nanosecond(i32 i) :
   duration(i / (1'000'000'000), (i % (1'000'000'000)))
{

}


inline nanosecond::nanosecond(u32 dw) :
   duration(dw / (1'000'000'000), (dw % (1'000'000'000)))
{

}


inline microsecond::microsecond(i64 i) :
   duration(i / (1'000'000), (i % (1'000'000)) * 1'000)
{

}


inline microsecond::microsecond(i32 i) :
   duration(i / (1'000'000), (i % (1'000'000)) * 1'000)
{

}


inline microsecond::microsecond(u32 dw) :
   duration(dw / (1'000'000), (dw % (1'000'000)) * 1'000)
{

}


inline millisecond::millisecond(i64 i) :
   duration(i / 1'000, (i % 1'000) * 1'000'000)
{

}


inline millisecond::millisecond(u64 u) :
duration(u / 1'000, (u % 1'000) * 1'000'000)
{

}


inline millisecond::millisecond(i32 i) :
   duration(i / 1'000, (i % 1'000) * 1'000'000)
{

}


inline millisecond::millisecond(u32 dw) :
   duration(dw / 1'000, (dw % 1'000) * 1'000'000)
{

}

inline millisecond::millisecond(double d) :
   duration((::i64) (d / 1'000.0), (::i64) (fmod(d, 1'000.0) * 1'000'000.0))
{

}


inline seconds::seconds(i64 i) :
   duration(i)
{

}


inline seconds::seconds(i32 i) :
   duration(i)
{

}


inline seconds::seconds(u32 dw) :
   duration(dw)
{

}


inline seconds::seconds(long double d) :
   duration(d)
{

}


inline minutes::minutes(i64 i) :
   duration(i * 60)
{

}


inline minutes::minutes(i32 i) :
   duration(i * 60)
{

}


inline minutes::minutes(u32 dw) :
   duration(dw * 60)
{

}


inline minutes::minutes(long double d) :
   duration(d * 60.0)
{

}


inline hours::hours(i64 iHours, i32 iMinutes, i32 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}


inline hours::hours(i32 iHours, i32 iMinutes, i32 iSeconds) :
   duration(iHours * 3600 + iMinutes * 60 + iSeconds)
{

}


inline hours::hours(u32 dwHours, i32 iMinutes, i32 iSeconds) :
   duration(dwHours * 3600 + iMinutes * 60 + iSeconds)
{

}


inline hours::hours(long double d) :
   duration(d * 3600.0)
{

}


inline days::days(i64 i) :
   duration(i * 86400)
{

}


inline days::days(i32 i) :
   duration(i * 86400)
{

}


inline days::days(u32 dw) :
   duration(dw * 86400)
{

}


inline days::days(long double d) :
   duration(d * 86400.0)
{

}


inline time_t duration::GetTimeSpan() const
{

   return m_iSeconds;

}


inline ::secs duration::secs() const
{

   return m_iSeconds;

}


inline duration::operator bool() const
{

   return m_iSeconds != 0 || m_iNanoseconds != 0;

}


//CLASS_DECL_ACME void millis_sleep(const duration & duration);


inline bool operator == (const duration & duration1, const ::duration & duration2) { return duration1.m_iSeconds == duration2.m_iSeconds && duration1.m_iNanoseconds == duration2.m_iSeconds; }
inline bool operator != (const duration & duration1, const ::duration & duration2) { return !(duration1 == duration2); }
inline bool operator < (const duration & duration1, const ::duration & duration2) { return duration1.m_iSeconds < duration2.m_iSeconds || (duration1.m_iSeconds == duration2.m_iSeconds && duration1.m_iNanoseconds < duration2.m_iNanoseconds); }
inline bool operator <= (const duration & duration1, const ::duration & duration2) { return duration1.m_iSeconds < duration2.m_iSeconds || (duration1.m_iSeconds == duration2.m_iSeconds && duration1.m_iNanoseconds <= duration2.m_iNanoseconds); }
inline bool operator > (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }
inline bool operator >= (const duration & duration1, const ::duration & duration2) { return !(duration1 <= duration2); }


//inline bool CLASS_DECL_ACME operator >(const duration & duration1, const duration & duration2)
//{
//
//   auto iCompare = duration1.m_iSeconds - duration2.m_iSeconds;
//
//   if(iCompare > 0)
//   {
//
//      return true;
//
//   }
//   else if(iCompare == 0)
//   {
//
//      return duration1.m_iSeconds > duration2.m_iSeconds;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}
//
//
//inline bool CLASS_DECL_ACME operator < (const duration & duration1, const duration & duration2)
//{
//
//   auto iCompare = duration1.m_iSeconds - duration2.m_iSeconds;
//
//   if(iCompare < 0)
//   {
//
//      return true;
//
//   }
//   else if(iCompare == 0)
//   {
//
//      return duration1.m_iSeconds < duration2.m_iSeconds;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}


//inline bool millis::operator == (const ::duration& duration) const { return m_iMilliseconds == duration.millis().m_iMilliseconds; }
//inline bool millis::operator != (const ::duration& duration) const { return m_iMilliseconds != duration.millis().m_iMilliseconds; }
//inline bool millis::operator < (const ::duration& duration) const { return m_iMilliseconds < duration.millis().m_iMilliseconds; }
//inline bool millis::operator <= (const ::duration& duration) const { return m_iMilliseconds <= duration.millis().m_iMilliseconds; }
//inline bool millis::operator > (const ::duration& duration) const { return m_iMilliseconds > duration.millis().m_iMilliseconds; }
//inline bool millis::operator >= (const ::duration& duration) const { return m_iMilliseconds >= duration.millis().m_iMilliseconds; }
//inline millis millis::operator - (const ::duration& duration) const { return m_iMilliseconds - duration.millis().m_iMilliseconds; }
//inline millis millis::operator + (const ::duration& duration) const { return m_iMilliseconds + duration.millis().m_iMilliseconds; }
//inline millis& millis::operator -= (const ::duration& duration) { m_iMilliseconds -= duration.millis().m_iMilliseconds; return *this; }
//inline millis& millis::operator += (const ::duration& duration) { m_iMilliseconds += duration.millis().m_iMilliseconds; return *this; }


inline duration __random(const duration & d1, const duration & d2)
{

   auto iSeconds = __random(d1.m_iSeconds, d2.m_iSeconds);

   return duration(iSeconds, __random(
         (iSeconds > d1.m_iSeconds) ? 0 : d1.m_iNanoseconds,
         (iSeconds < d2.m_iSeconds) ? 999'999'999 : d2.m_iNanoseconds));

}


inline secs::secs(const duration & duration) { m_iSeconds = duration.m_iSeconds; }
inline millis::millis(const duration & duration) { m_iMilliseconds = duration.millis().m_iMilliseconds; }
inline micros::micros(const duration & duration) { m_iMicroseconds = duration.micros().m_iMicroseconds; }
inline nanos::nanos(const duration & duration) { m_iNanoseconds = duration.nanos().m_iNanoseconds;  }


#ifdef WINDOWS

inline u32 __os(const ::duration & duration) { return duration.u32_millis(); }

#endif



