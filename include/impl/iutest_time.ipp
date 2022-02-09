//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_time.ipp
 * @brief       iris unit test time utility
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TIME_IPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
#define INCG_IRIS_IUTEST_TIME_IPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_

//======================================================================
// include
#include "../internal/iutest_time.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// function
IUTEST_IPP_INLINE bool Localtime(time_t sec, struct tm* dst) IUTEST_CXX_NOEXCEPT_SPEC
{
#if IUTEST_HAS_CTIME

#if defined(_MSC_VER)
#  if defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__
    return localtime_s(dst, &sec) == 0;
#  else
    struct tm* t = localtime(&sec); // NOLINT
    if( t == IUTEST_NULLPTR )
    {
        return false;
    }
    if( dst != IUTEST_NULLPTR ) *dst = *t;
    return true;
#  endif
#elif defined(__MINGW32__) || defined(__MINGW64__)
    const struct tm* const t = localtime(&sec); // NOLINT
    if( t == IUTEST_NULLPTR || dst == IUTEST_NULLPTR )
    {
        return false;
    }
    *dst = *t;
    return true;
#else
    return localtime_r(&sec, dst) != IUTEST_NULLPTR;
#endif

#else
    IUTEST_UNUSED_VAR(sec);
    IUTEST_UNUSED_VAR(dst);
    return false;
#endif
}

IUTEST_IPP_INLINE ::std::string FormatTimeInMillisec(TimeInMillisec msec)
{
    iu_stringstream ss;
    ss << msec;
    return ss.str();
}

IUTEST_IPP_INLINE ::std::string FormatTimeInMillisecAsSecond(TimeInMillisec msec)
{
    iu_stringstream ss;
#if defined(_MSC_VER) && _MSC_VER < 1300
    ss << static_cast<unsigned int>(msec)/1000.0;
#else
    ss << static_cast<double>(msec)*1e-3;
#endif
    return ss.str();
}

IUTEST_IPP_INLINE ::std::string FormatTimeInMillisecAsIso8601(TimeInMillisec msec)
{
#if IUTEST_HAS_CTIME
    const time_t sec = static_cast<time_t>(msec / 1000);
    struct tm t;
    if( !Localtime(sec, &t) )
    {
        return FormatTimeInMillisecAsSecond(msec);
    }

    iu_stringstream ss;
    ss << (t.tm_year+1900);
    return ss.str() + "-"
        + FormatIntWidth2(t.tm_mon+1) + "-"
        + FormatIntWidth2(t.tm_mday) + "T"
        + FormatIntWidth2(t.tm_hour) + ":"
        + FormatIntWidth2(t.tm_min) + ":"
        + FormatIntWidth2(t.tm_sec) + "."
        + FormatIntWidthN(static_cast<int>(msec % 1000), 3);
#else
    return FormatTimeInMillisecAsSecond(msec);
#endif
}

IUTEST_IPP_INLINE time_t GetTime() IUTEST_CXX_NOEXCEPT_SPEC
{
#if IUTEST_HAS_CTIME
    return time(IUTEST_NULLPTR);
#else
    return 0;
#endif
}

IUTEST_IPP_INLINE TimeInMillisec GetTimeInMillis() IUTEST_CXX_NOEXCEPT_SPEC
{
#if   defined(IUTEST_GetMillisec)
    return IUTEST_GetMillisec();

#elif IUTEST_HAS_CXX_HDR_CHRONO
    return static_cast<TimeInMillisec>(::std::chrono::duration_cast< ::std::chrono::milliseconds >(
        ::std::chrono::high_resolution_clock::now().time_since_epoch() ).count());

#elif IUTEST_HAS_GETTIMEOFDAY
    timeval tv;
    gettimeofday(&tv, IUTEST_NULLPTR);
    return static_cast<TimeInMillisec>(tv.tv_sec) * 1000 + static_cast<TimeInMillisec>(tv.tv_usec) / 1000;

#elif defined(IUTEST_OS_WINDOWS)

#if defined(IUTEST_OS_WINDOWS_MOBILE)
    return static_cast<TimeInMillisec>(GetTickCount());
#else

    _timeb tb;

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    _ftime(&tb);
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

    return static_cast<TimeInMillisec>(tb.time * 1000 + tb.millitm);

#endif

#elif IUTEST_HAS_CLOCK
    return clock() * 1000 / CLOCKS_PER_SEC;

#else
    return GetTime()*1000;
#endif
}

IUTEST_IPP_INLINE unsigned int GetIndefiniteValue() IUTEST_CXX_NOEXCEPT_SPEC
{
    // なるべく同じにならないようにする
    static unsigned int s = static_cast<unsigned int>(GetTimeInMillis());
    s = s*1664525 + 1013904223;
    return s;
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_TIME_IPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
