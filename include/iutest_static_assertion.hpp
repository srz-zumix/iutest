//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_static_assertion.hpp
 * @brief		iris unit test static assertion 定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_static_assertion_HPP_53842FD6_9E5D_40a6_905D_EC6DEBE5ED6A_
#define INCG_IRIS_iutest_static_assertion_HPP_53842FD6_9E5D_40a6_905D_EC6DEBE5ED6A_

//======================================================================
// include

//======================================================================
// 
#if 0
/**
 * @ingroup	IUTEST_UTIL
 * @brief	型アサーション
*/
template<typename T1, typename T2>
static bool	StaticAssertTypeEq(void)
{
	(void)detail::StaticAssertTypeEqHelper<T1, T2>();
	return true;
}
#else

/**
 * @ingroup	IUTEST_UTIL
 * @brief	型アサーション
 * @note	マクロバージョン
 *			エラーが呼び出し位置に出る
*/
#define StaticAssertTypeEq	detail::StaticAssertTypeEqHelper

/**
 * @brief	static_assert
*/
#if IUTEST_HAS_STATIC_ASSERT
#  define IUTEST_STATIC_ASSERT_MSG(B, Msg)	static_assert(B, Msg)
#else
#  define IUTEST_STATIC_ASSERT_MSG(B, Msg)	\
	typedef ::iutest::detail::StaticAssertionTest< sizeof(::iutest::detail::StaticAssertionFailure< (bool)B >) > IUTEST_PP_CAT(iutest_static_assert_typedef_, __LINE__)
#endif

/**
 * @brief	static_assert
*/
#ifdef IUTEST_STATIC_ASSERT_MSG
#  ifdef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_STATIC_ASSERT(B)		IUTEST_STATIC_ASSERT_MSG(B, "")
#  else
#    define IUTEST_STATIC_ASSERT(...)	IUTEST_STATIC_ASSERT_MSG((__VA_ARGS__), "")
#  endif
#endif

#endif

//======================================================================
// function
namespace iutest
{

namespace detail
{

/** @private */
template<typename T1, typename T2>
struct StaticAssertTypeEqHelper;

/** @private */
template<typename T>
struct StaticAssertTypeEqHelper<T, T>
{
	operator bool (void) const { return true; }
};


/** @private */
template<bool b>struct StaticAssertionFailure;
/** @overload */
template<> struct StaticAssertionFailure<true> { enum { value = 1 }; };

/** @private */
template<int x>struct StaticAssertionTest {};

}

}	// end of namespace iutest

#endif
