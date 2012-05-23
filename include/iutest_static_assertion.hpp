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
 * @ingroup	IUTEST_
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
 * @ingroup	IUTEST_
 * @brief	型アサーション
 * @note	マクロバージョン
 *			エラーが呼び出し位置に出る
*/
#define StaticAssertTypeEq	detail::StaticAssertTypeEqHelper

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

}

}	// end of namespace iutest

#endif
