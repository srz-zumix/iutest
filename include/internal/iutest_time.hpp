//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_time.hpp
 * @brief       time utility
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TIME_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
#define INCG_IRIS_IUTEST_TIME_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include <time.h>

#if IUTEST_HAS_CXX_HDR_CHRONO
#  include <chrono>
#endif

#if   IUTEST_HAS_HDR_SYSTIME
#  include <sys/time.h>
#elif defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <sys/timeb.h>
#endif

//======================================================================
// define
//! @deprecated
#if !defined(IUTEST_GetMillisec) && !IUTEST_HAS_CXX_HDR_CHRONO && !IUTEST_HAS_GETTIMEOFDAY && !defined(IUTEST_OS_WINDOWS) && !IUTEST_HAS_CLOCK
#  define IUTEST_NO_GETTIMEINMILLIS
#endif

namespace iutest {
namespace detail
{

//======================================================================
// declare
/**
 * @internal
 * @brief   localtime
 * @param   [in]    sec = 秒
 * @param   [out]   dst = 時刻
 * @return  成否
*/
bool Localtime(time_t sec, struct tm* dst);

/**
 * @internal
 * @brief   TimeInMillisec to string
 * @param   [in]    msec    = ミリ秒
 * @return  ミリ秒数の文字列
*/
::std::string FormatTimeInMillisec(TimeInMillisec msec);

/**
 * @internal
 * @brief   TimeInMillisec to string
 * @param   [in]    msec    = ミリ秒
 * @return  秒数の文字列
*/
::std::string FormatTimeInMillisecAsSecond(TimeInMillisec msec);

/**
 * @internal
 * @brief   TimeInMillisec to string
 * @param   [in]    msec    = ミリ秒
 * @return  時刻の文字列
*/
::std::string FormatTimeInMillisecAsIso8601(TimeInMillisec msec);

/**
 * @brief   現在時刻の取得
*/
time_t GetTime();

/**
 * @brief   現在時刻のミリ秒取得
*/
TimeInMillisec GetTimeInMillis();

/**
 * @brief   不定な値の取得
*/
unsigned int GetIndefiniteValue();

//======================================================================
// class
/**
 * @internal
 * @brief   ストップウォッチクラス
*/
class iuStopWatch
{
private:
    TimeInMillisec m_begin;
public:
    iuStopWatch() : m_begin(0) {}

public:
    // 現在の時間をミリ秒単位で取得
    static TimeInMillisec get_millisec()
    {
#if defined(IUTEST_NOT_SUPPORT_STOPWATCH)
        return 0;
#else
        return GetTimeInMillis();
#endif
    }
public:
    void start()
    {
        m_begin = get_millisec();
    }
    TimeInMillisec stop() const
    {
        return get_millisec() - m_begin;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_time.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_TIME_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
