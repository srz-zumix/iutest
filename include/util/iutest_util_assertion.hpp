//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_assertion.hpp
 * @brief		iris unit test assertion 拡張 ファイル
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_
#define INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_

//======================================================================
// include
#include "../internal/iutest_type_traits.hpp"

//======================================================================
// define
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	== テスト(collection)
 * @param	b1	= 期待値の先頭
 * @param	e1	= 期待値の終端
 * @param	b2	= 検査対象の先頭
 * @param	e2	= 検査対象の終端
*/
#ifndef IUTEST_ASSERT_EQ_COLLECTIONS
#  define	IUTEST_ASSERT_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	== テスト(collection)
 * @param	b1	= 期待値の先頭
 * @param	e1	= 期待値の終端
 * @param	b2	= 検査対象の先頭
 * @param	e2	= 検査対象の終端
*/
#ifndef IUTEST_EXPECT_EQ_COLLECTIONS
#  define	IUTEST_EXPECT_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	== テスト(collection)
 * @param	b1	= 期待値の先頭
 * @param	e1	= 期待値の終端
 * @param	b2	= 検査対象の先頭
 * @param	e2	= 検査対象の終端
*/
#ifndef IUTEST_INFORM_EQ_COLLECTIONS
#  define	IUTEST_INFORM_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME_
 * @brief	== テスト(collection)
 * @param	b1	= 期待値の先頭
 * @param	e1	= 期待値の終端
 * @param	b2	= 検査対象の先頭
 * @param	e2	= 検査対象の終端
*/
#ifndef IUTEST_ASSUME_EQ_COLLECTIONS
#  define	IUTEST_ASSUME_EQ_COLLECTIONS(b1, e1, b2, e2)	IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	== テスト(range)
 * @param	expected	= 期待値
 * @param	actual		= 検査対象
*/
#ifndef IUTEST_ASSERT_EQ_RANGE
#  define	IUTEST_ASSERT_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	== テスト(range)
 * @param	expected	= 期待値
 * @param	actual		= 検査対象
*/
#ifndef IUTEST_EXPECT_EQ_RANGE
#  define	IUTEST_EXPECT_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM_
 * @brief	== テスト(range)
 * @param	expected	= 期待値
 * @param	actual		= 検査対象
*/
#ifndef IUTEST_INFORM_EQ_RANGE
#  define	IUTEST_INFORM_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME_
 * @brief	== テスト(range)
 * @param	expected	= 期待値
 * @param	actual		= 検査対象
*/
#ifndef IUTEST_ASSUME_EQ_RANGE
#  define	IUTEST_ASSUME_EQ_RANGE(expected, actual)	IUTEST_TEST_EQ_RANGE(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列長の一致 テスト
 * @param	len		= 期待文字列長
 * @param	v2		= 検査対象
*/
#ifndef IUTEST_ASSERT_STRLNEQ
#  define	IUTEST_ASSERT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列長の一致 テスト
 * @param	len		= 期待文字列長
 * @param	v2		= 検査対象
*/
#ifndef IUTEST_EXPECT_STRLNEQ
#  define	IUTEST_EXPECT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列長の一致 テスト
 * @param	len		= 期待文字列長
 * @param	v2		= 検査対象
*/
#ifndef IUTEST_INFORM_STRLNEQ
#  define	IUTEST_INFORM_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列長の一致 テスト
 * @param	len		= 期待文字列長
 * @param	v2		= 検査対象
*/
#ifndef IUTEST_ASSUME_STRLNEQ
#  define	IUTEST_ASSUME_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_STRIN
#  define	IUTEST_ASSERT_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_EXPECT_STRIN
#  define	IUTEST_EXPECT_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_INFORM_STRIN
#  define	IUTEST_INFORM_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_ASSUME_STRIN
#  define	IUTEST_ASSUME_STRIN(substr, actual)		IUTEST_TEST_STRIN(substr, actual, IUTEST_ASSUME_FAILURE)
#endif


/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_STRNOTIN
#  define	IUTEST_ASSERT_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_EXPECT_STRNOTIN
#  define	IUTEST_EXPECT_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_INFORM_STRNOTIN
#  define	IUTEST_INFORM_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列部分一致 テスト
 * @param	substr	= 部分文字列
 * @param	actual	= 検査対象文字列
*/
#ifndef IUTEST_ASSUME_STRNOTIN
#  define	IUTEST_ASSUME_STRNOTIN(substr, actual)		IUTEST_TEST_STRNOTIN(substr, actual, IUTEST_ASSUME_FAILURE)
#endif

#if IUTEST_HAS_REGEX

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列正規表現一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_MATCHES_REGEXEQ
#  define	IUTEST_ASSERT_MATCHES_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXEQ(regex_str, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列正規表現一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_EXPECT_MATCHES_REGEXEQ
#  define	IUTEST_EXPECT_MATCHES_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXEQ(regex_str, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列正規表現一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_INFORM_MATCHES_REGEXEQ
#  define	IUTEST_INFORM_MATCHES_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXEQ(regex_str, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列正規表現一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_ASSUME_MATCHES_REGEXEQ
#  define	IUTEST_ASSUME_MATCHES_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXEQ(regex_str, actual, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列正規表現不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_MATCHES_REGEXNE
#  define	IUTEST_ASSERT_MATCHES_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXNE(regex_str, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列正規表現不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_EXPECT_MATCHES_REGEXNE
#  define	IUTEST_EXPECT_MATCHES_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXNE(regex_str, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列正規表現不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_INFORM_MATCHES_REGEXNE
#  define	IUTEST_INFORM_MATCHES_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXNE(regex_str, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列正規表現不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_ASSUME_MATCHES_REGEXNE
#  define	IUTEST_ASSUME_MATCHES_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_MATCHES_REGEXNE(regex_str, actual, IUTEST_ASSUME_FAILURE)
#endif



/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列正規表現部分一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_CONTAINS_REGEXEQ
#  define	IUTEST_ASSERT_CONTAINS_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXEQ(regex_str, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列正規表現部分一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_EXPECT_CONTAINS_REGEXEQ
#  define	IUTEST_EXPECT_CONTAINS_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXEQ(regex_str, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列正規表現部分一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_INFORM_CONTAINS_REGEXEQ
#  define	IUTEST_INFORM_CONTAINS_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXEQ(regex_str, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列正規表現部分一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_ASSUME_CONTAINS_REGEXEQ
#  define	IUTEST_ASSUME_CONTAINS_REGEXEQ(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXEQ(regex_str, actual, IUTEST_ASSUME_FAILURE)
#endif

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列正規表現部分不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
*/
#ifndef IUTEST_ASSERT_CONTAINS_REGEXNE
#  define	IUTEST_ASSERT_CONTAINS_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXNE(regex_str, actual, IUTEST_ASSERT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列正規表現部分不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_EXPECT_CONTAINS_REGEXNE
#  define	IUTEST_EXPECT_CONTAINS_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXNE(regex_str, actual, IUTEST_EXPECT_FAILURE)
#endif
/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列正規表現部分不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_INFORM_CONTAINS_REGEXNE
#  define	IUTEST_INFORM_CONTAINS_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXNE(regex_str, actual, IUTEST_INFORM_FAILURE)
#endif
/**
 * @ingroup	IUTEST_ASSUME
 * @brief	文字列正規表現部分不一致 テスト
 * @param	regex_str	= 正規表現文字列
 * @param	actual		= 検査対象文字列
 */
#ifndef IUTEST_ASSUME_CONTAINS_REGEXNE
#  define	IUTEST_ASSUME_CONTAINS_REGEXNE(regex_str, actual)		\
	IUTEST_TEST_CONTAINS_REGEXNE(regex_str, actual, IUTEST_ASSUME_FAILURE)
#endif

#endif

/**
 * @private
 * @brief	for gtest
 * @{
*/

#define ASSERT_EQ_COLLECTIONS	IUTEST_ASSERT_EQ_COLLECTIONS
#define ASSERT_EQ_RANGE			IUTEST_ASSERT_EQ_RANGE
#define ASSERT_STRLNEQ			IUTEST_ASSERT_STRLNEQ
#define ASSERT_STRIN			IUTEST_ASSERT_STRIN
#define ASSERT_STRNOTIN			IUTEST_ASSERT_STRNOTIN

#define EXPECT_EQ_COLLECTIONS	IUTEST_EXPECT_EQ_COLLECTIONS
#define EXPECT_EQ_RANGE			IUTEST_EXPECT_EQ_RANGE
#define EXPECT_STRLNEQ			IUTEST_EXPECT_STRLNEQ
#define EXPECT_STRIN			IUTEST_EXPECT_STRIN
#define EXPECT_STRNOTIN			IUTEST_EXPECT_STRNOTIN

#define INFORM_EQ_COLLECTIONS	IUTEST_INFORM_EQ_COLLECTIONS
#define INFORM_EQ_RANGE			IUTEST_INFORM_EQ_RANGE
#define INFORM_STRLNEQ			IUTEST_INFORM_STRLNEQ
#define INFORM_STRIN			IUTEST_INFORM_STRIN
#define INFORM_STRNOTIN			IUTEST_INFORM_STRNOTIN

#define ASSUME_EQ_COLLECTIONS	IUTEST_ASSUME_EQ_COLLECTIONS
#define ASSUME_EQ_RANGE			IUTEST_ASSUME_EQ_RANGE
#define ASSUME_STRLNEQ			IUTEST_ASSUME_STRLNEQ
#define ASSUME_STRIN			IUTEST_ASSUME_STRIN
#define ASSUME_STRNOTIN			IUTEST_ASSUME_STRNOTIN

#if IUTEST_HAS_REGEX

#define ASSERT_MATCHES_REGEXEQ	IUTEST_ASSERT_MATCHES_REGEXEQ
#define EXPECT_MATCHES_REGEXEQ	IUTEST_EXPECT_MATCHES_REGEXEQ
#define INFORM_MATCHES_REGEXEQ	IUTEST_INFORM_MATCHES_REGEXEQ
#define ASSUME_MATCHES_REGEXEQ	IUTEST_ASSUME_MATCHES_REGEXEQ

#define ASSERT_MATCHES_REGEXNE	IUTEST_ASSERT_MATCHES_REGEXNE
#define EXPECT_MATCHES_REGEXNE	IUTEST_EXPECT_MATCHES_REGEXNE
#define INFORM_MATCHES_REGEXNE	IUTEST_INFORM_MATCHES_REGEXNE
#define ASSUME_MATCHES_REGEXNE	IUTEST_ASSUME_MATCHES_REGEXNE

#define ASSERT_CONTAINS_REGEXEQ	IUTEST_ASSERT_CONTAINS_REGEXEQ
#define EXPECT_CONTAINS_REGEXEQ	IUTEST_EXPECT_CONTAINS_REGEXEQ
#define INFORM_CONTAINS_REGEXEQ	IUTEST_INFORM_CONTAINS_REGEXEQ
#define ASSUME_CONTAINS_REGEXEQ	IUTEST_ASSUME_CONTAINS_REGEXEQ

#define ASSERT_CONTAINS_REGEXNE	IUTEST_ASSERT_CONTAINS_REGEXNE
#define EXPECT_CONTAINS_REGEXNE	IUTEST_EXPECT_CONTAINS_REGEXNE
#define INFORM_CONTAINS_REGEXNE	IUTEST_INFORM_CONTAINS_REGEXNE
#define ASSUME_CONTAINS_REGEXNE	IUTEST_ASSUME_CONTAINS_REGEXNE

#endif

/**
 * @}
*/

/**
 * @private
 * @{
*/
#define IUTEST_TEST_EQ_COLLECTIONS(b1, e1, b2, e2, on_failure)	IUTEST_PRED_FORMAT4_( ::iuutil::CmpHelperEqCollections, b1, e1, b2, e2, on_failure)
#define IUTEST_TEST_EQ_RANGE(expected, actual, on_failure)		IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperEqRange, expected, actual, on_failure)

#define	IUTEST_TEST_STRLNEQ(len, v2, on_failure)				IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRLNEQ, len, v2, on_failure )
#define IUTEST_TEST_STRIN(substr, actual, on_failure)			IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRIN, substr, actual, on_failure )
#define IUTEST_TEST_STRNOTIN(substr, actual, on_failure)		IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRNOTIN, substr, actual, on_failure )

#if IUTEST_HAS_REGEX

#define IUTEST_TEST_MATCHES_REGEXEQ(regex, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperMatchesRegexEq, regex, actual, on_failure )
#define IUTEST_TEST_MATCHES_REGEXNE(regex, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperMatchesRegexNe, regex, actual, on_failure )

#define IUTEST_TEST_CONTAINS_REGEXEQ(regex, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperContainsRegexEq, regex, actual, on_failure )
#define IUTEST_TEST_CONTAINS_REGEXNE(regex, actual, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperContainsRegexNe, regex, actual, on_failure )

#endif

/**
 * @}
*/

namespace iuutil
{

//======================================================================
// function
/**
 * @brief	Equal Collection Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqIterator(T1 b1, T1 e1, T2 b2, T2 e2)
{
	int elem=0;
	bool result = true;
	::iutest::Message ar;
	for(elem=0; b1 != e1 && b2 != e2; ++b1, ++b2, ++elem)
	{
		if(!::iutest::internal::EqHelper<false>::Compare("", "", *b1, *b2))
		{
			result = false;
			ar << "\nMismatch in a position " << elem << ": "
				<< ::iutest::internal::FormatForComparisonFailureMessage(*b1, *b2)
				<< " vs " << ::iutest::internal::FormatForComparisonFailureMessage(*b2, *b1);
		}
	}
	if(b1 != e1)
	{
		int elem1 = elem;
		for(; b1 != e1; ++b1, ++elem1) {}
		result = false;
		ar << "\nMismatch element : " << elem1 << " vs " << elem;
	}
	if(b2 != e2)
	{
		int elem2 = elem;
		for(; b2 != e2; ++b2, ++elem2) {}
		result = false;
		ar << "\nMismatch element : " << elem << " vs " << elem2;
	}
	if( !result )
	{
		return ::iutest::AssertionFailure() << ar;
	}
	return ::iutest::AssertionSuccess();
}

/**
 * @brief	Equal Collection Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqCollections(const char* expr1b, const char* expr1e
	, const char* expr2b, const char* expr2e
	, T1 b1, T1 e1, T2 b2, T2 e2)
{
	if( ::iutest::AssertionResult ar = CmpHelperEqIterator(b1, e1, b2, e2) )
		return ::iutest::AssertionSuccess();

	return ::iutest::AssertionFailure() << "error: Expected: { " << expr1b << ", " << expr1e << " } == { "
				<< expr2b << ", " << expr2e << " }\n  Actual:" << ar.message();
}

namespace detail
{

template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 b1, T1 e1, T2 b2, T2 e2)
{
	if( ::iutest::AssertionResult ar = CmpHelperEqIterator(b1, e1, b2, e2) )
		return ::iutest::AssertionSuccess();

	return ::iutest::AssertionFailure() << "error: Expected: " << expected_expr << " == " << actual_expr
				<< " \n  Actual:" << ar.message();
}

}	// end of namespace detail

/**
 * @brief	Equal Range Helper
*/
template<typename T1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 expected, T2 actual)
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected.begin(), expected.end()
		, actual.begin(), actual.end());
}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

/** @overload */
template<typename T1, size_t SIZE1, typename T2, size_t SIZE2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 (&expected)[SIZE1], T2 (&actual)[SIZE2])
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected, expected+SIZE1
		, actual, actual+SIZE2);
}
/** @overload */
template<typename T1, typename T2, size_t SIZE2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1 expected, T2(&actual)[SIZE2])
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected.begin(), expected.end()
		, actual, actual+SIZE2);
}
/** @overload */
template<typename T1, size_t SIZE1, typename T2>
::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperEqRange(const char* expected_expr, const char* actual_expr
	, T1(&expected)[SIZE1], T2 actual)
{
	return detail::CmpHelperEqRange(expected_expr, actual_expr, expected, expected+SIZE1
		, actual.begin(), actual.end());
}

#endif

/**
 * @brief	文字列長アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										, size_t len1, const char* val2)
{
	const size_t len2 = strlen(val2);
	if( len2 == len1 )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == strlen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1;
}
/**
 * @brief	文字列長アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										, size_t len1, const wchar_t* val2)
{
	const size_t len2 = wcslen(val2);
	if( len2 == len1 )
	{
		return ::iutest::AssertionSuccess();
	}
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == wcslen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1;
}

namespace StrInHelper
{

inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const char* substr, const char* actual)
{
	if( substr == NULL || actual == NULL )
	{
		return substr == actual;
	}
	return strstr(actual, substr) != NULL;
}

inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const wchar_t* substr, const wchar_t* actual)
{
	if( substr == NULL || actual == NULL )
	{
		return substr == actual;
	}
	return wcsstr(actual, substr) != NULL;
}

template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const ::std::basic_string<Elem, Traits, Ax>& substr
	, const ::std::basic_string<Elem, Traits, Ax>& actual)
{
	return Compare(substr.c_str(), actual.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const Elem* substr
	, const ::std::basic_string<Elem, Traits, Ax>& actual)
{
	return Compare(substr, actual.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const ::std::basic_string<Elem, Traits, Ax>& substr
	, const Elem* actual)
{
	return Compare(substr.c_str(), actual);
}

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* substr_str, const char* actual_str
	, const T1& substr, const T2& actual)
{
	if( Compare(substr, actual) )
	{
		return ::iutest::AssertionSuccess();
	}

	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") != NULL"
		<< "\n  Actual: " << "strstr(\"" << actual << "\", " << substr << ") == NULL";
}

}	// end of namespace StrInHelper

/**
 * @brief	文字列部分一致アサーションフォーマッター
*/
template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRIN(const char* substr_str, const char* actual_str
	, const T1& substr, const T2& actual)
{
	return StrInHelper::Assertion(substr_str, actual_str, substr, actual);
}

namespace StrNotInHelper
{

template<typename T1, typename T2>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T1& substr, const T2& actual)
{
	return !StrInHelper::Compare(substr, actual);
}

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* substr_str, const char* actual_str
	, const T1& substr, const T2& actual)
{
	if( Compare(substr, actual) )
	{
		return ::iutest::AssertionSuccess();
	}

	return ::iutest::AssertionFailure() << "error: Expected: " << "strstr(" << actual_str << ", " << substr_str << ") == NULL"
		<< "\n  Actual: " << "strstr(\"" << actual << "\", " << substr << ") != NULL";
}

}	// end of namespace StrNotInHelper

/**
 * @brief	文字列部分一致アサーションフォーマッター
*/
template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNOTIN(const char* substr_str, const char* actual_str
	, const T1& substr, const T2& actual)
{
	return StrNotInHelper::Assertion(substr_str, actual_str, substr, actual);
}

#if IUTEST_HAS_REGEX

namespace RegexHelper
{

inline bool FullMatch(const ::std::string& str, ::iutest::internal::RE& re)
{
	return ::iutest::internal::RE::FullMatch(str, re);
}
inline bool FullMatch(const char* str, ::iutest::internal::RE& re)
{
	if( str == NULL ) return false;
	return ::iutest::internal::RE::FullMatch(str, re);
}

inline bool PartialMatch(const ::std::string& str, ::iutest::internal::RE& re)
{
	return ::iutest::internal::RE::PartialMatch(str, re);
}
inline bool PartialMatch(const char* str, ::iutest::internal::RE& re)
{
	if( str == NULL ) return false;
	return ::iutest::internal::RE::PartialMatch(str, re);
}

}	// end of namespace RegexHelper

namespace MatchesRegexEqHelper
{

template<typename T1, typename T2>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T1& regex, const T2& actual)
{
	::iutest::internal::RE m(regex);
	return RegexHelper::FullMatch(actual, m);
}

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* regex_str, const char* actual_str
	, const T1& regex, const T2& actual)
{
	if( Compare(regex, actual) )
	{
		return ::iutest::AssertionSuccess();
	}
	::std::string expected_str = "Matches Regex (";
	expected_str += regex_str;
	expected_str += ")";

	return ::iutest::internal::EqFailure(expected_str.c_str(), actual_str
		, ::iutest::PrintToString(regex)
		, ::iutest::PrintToString(actual)
		, false);
}

}	// end of namespace MatchesRegexEqHelper

/**
 * @brief	文字列正規表現一致アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperMatchesRegexEq(const char* regex_str, const char* actual_str
	, const char* regex, const char* actual)
{
	return MatchesRegexEqHelper::Assertion(regex_str, actual_str, regex, actual);
}

namespace MatchesRegexNeHelper
{

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* regex_str, const char* actual_str
	, const T1& regex, const T2& actual)
{
	if( !MatchesRegexEqHelper::Compare(regex, actual) )
	{
		return ::iutest::AssertionSuccess();
	}
	::std::string expected_str = "Not Matches Regex (";
	expected_str += regex_str;
	expected_str += ")";

	return ::iutest::internal::EqFailure(expected_str.c_str(), actual_str
		, ::iutest::PrintToString(regex)
		, ::iutest::PrintToString(actual)
		, false);
}

}	// end of namespace MatchesRegexNeHelper

/**
 * @brief	文字列正規表現不一致アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperMatchesRegexNe(const char* regex, const char* actual_str
	, const char* regex_str, const char* actual)
{
	return MatchesRegexNeHelper::Assertion(regex, actual_str, regex_str, actual);
}

namespace ContainsRegexEqHelper
{

template<typename T1, typename T2>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T1& regex, const T2& actual)
{
	::iutest::internal::RE m(regex);
	return RegexHelper::PartialMatch(actual, m);
}

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* regex_str, const char* actual_str
	, const T1& regex, const T2& actual)
{
	if( Compare(regex, actual) )
	{
		return ::iutest::AssertionSuccess();
	}
	::std::string expected_str = "Contains Regex (";
	expected_str += regex_str;
	expected_str += ")";

	return ::iutest::internal::EqFailure(expected_str.c_str(), actual_str
		, ::iutest::PrintToString(regex)
		, ::iutest::PrintToString(actual)
		, false);
}

}	// end of namespace ContainsRegexEqHelper

/**
 * @brief	文字列正規表現部分一致アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperContainsRegexEq(const char* regex_str, const char* actual_str
	, const char* regex, const char* actual)
{
	return ContainsRegexEqHelper::Assertion(regex_str, actual_str, regex, actual);
}

namespace ContainsRegexNeHelper
{

template<typename T1, typename T2>
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(const char* regex_str, const char* actual_str
	, const T1& regex, const T2& actual)
{
	if( !ContainsRegexEqHelper::Compare(regex, actual) )
	{
		return ::iutest::AssertionSuccess();
	}
	::std::string expected_str = "Not Contains Regex (";
	expected_str += regex_str;
	expected_str += ")";

	return ::iutest::internal::EqFailure(expected_str.c_str(), actual_str
		, ::iutest::PrintToString(regex)
		, ::iutest::PrintToString(actual)
		, false);
}

}	// end of namespace ContainsRegexNeHelper

/**
 * @brief	文字列正規表現部分不一致アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperContainsRegexNe(const char* regex_str, const char* actual
	, const char* regex, const char* actual)
{
	return ContainsRegexNeHelper::Assertion(regex_str, actual_str, regex, actual);
}

#endif

/**
 * @private
 * @{
*/
#define IIUT_COMPARE_HELPER_DEC_(name)	struct name {										\
	template<typename T1, typename T2>														\
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const T1& val1, const T2& val2) {	\
		return ::iutest::internal::CmpHelper##name(expr1, expr2, val1, val2);				\
	}																						\
	}
/**
 * @}
*/

}	// end of namespace iuutil

#endif // INCG_IRIS_IUTEST_UTIL_ASSERTION_HPP_A45F8265_40E0_44F2_91C6_090B1778657C_
