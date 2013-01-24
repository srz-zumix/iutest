//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_time.hpp
 * @brief		iris unit test time utility ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_time_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_
#define INCG_IRIS_iutest_time_HPP_C6B9E65B_4059_4175_A6DB_397DBF338AA8_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include <time.h>

#if IUTEST_HAS_CXX11_HDR_CHRONO
#  include <chrono>
#endif

#if		IUTEST_HAS_HDR_SYSTIME
#  include <sys/time.h>
#elif	defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <sys/timeb.h>
#endif

namespace iutest {
namespace detail
{

//======================================================================
// declare
::std::string	FormatTimeInMillisecAsSecond(TimeInMillisec msec);
time_t			GetTime(void);
TimeInMillisec	GetTimeInMillis(void);
unsigned int	GetIndefiniteValue(void);

//======================================================================
// class
/**
 * @internal
 * @brief	ストップウォッチクラス
*/
class iuStopWatch
{
private:
	TimeInMillisec	m_begin;
public:
	iuStopWatch(void) : m_begin(0)	{}

public:
	// 現在の時間をミリ秒単位で取得
	static TimeInMillisec	get_millisec(void)
	{
#if		defined(IUTEST_NOT_SUPPORT_STOPWATCH)
		return 0;
#else
		return GetTimeInMillis();
#endif
	}
public:
	void			start(void)
	{
		m_begin = get_millisec();
	}
	TimeInMillisec	stop(void) const
	{
		return get_millisec() - m_begin;
	}
};

//======================================================================
// function
/**
  * @internal
  * @brief	TimeInMillisec to string
  * @param	[in]	msec	= ミリ秒
  * @return	秒数の文字列
*/
inline ::std::string	FormatTimeInMillisecAsSecond(TimeInMillisec msec)
{
	detail::iuStringStream::type ss;
	ss << msec/1000.0;
	return ss.str();
}

/**
 * @brief	現在時刻の取得
*/
inline time_t	GetTime(void)
{
#if IUTEST_HAS_CTIME
	return time(NULL);
#else
	return 0;
#endif
}

/**
 * @brief	現在時刻のミリ秒取得
*/
inline TimeInMillisec	GetTimeInMillis(void)
{
#if		defined(IUTEST_GetMillisec)
	return IUTEST_GetMillisec();

#elif	IUTEST_HAS_CXX11_HDR_CHRONO
	return ::std::chrono::duration_cast< ::std::chrono::milliseconds>(::std::chrono::high_resolution_clock::now().time_since_epoch()).count();

#elif	IUTEST_HAS_GETTIMEOFDAY
	timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<TimeInMillisec>(tv.tv_sec) * 1000 + static_cast<TimeInMillisec>(tv.tv_usec) / 1000;

#elif	IUTEST_HAS_CLOCK
	return clock() * 1000 / CLOCKS_PER_SEC;

#elif	defined(IUTEST_OS_WINDOWS)

#if		defined(IUTEST_OS_WINDOWS_MOBILE)
	return static_cast<TimeInMillisec>(GetTickCount());
#else

	__timeb64 tb;

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
	_ftime64(&tb);
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

	return static_cast<TimeInMillisec>(tb.time * 1000 + tb.millitm);

#endif

#else

#define IUTEST_NO_GETTIMEINMILLIS
	return GetTime()*1000;
#endif
}

/**
 * @brief	不定な値の取得
*/
inline unsigned int GetIndefiniteValue(void)
{
#if !defined(IUTEST_NO_GETTIMEINMILLIS)
	return static_cast<unsigned int>(GetTimeInMillis());
#else
	// なるべく同じにならないようにする
	static unsigned int s = 20120206;
	s = s*1664525 + 1013904223;
	return s;
#endif
}

}	// end of namespace detail
}	// end of namespace iutest

#endif
