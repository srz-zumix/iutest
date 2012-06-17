//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_assertion.hpp
 * @brief		iris unit test assertion 拡張 ファイル
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
#ifndef INCG_IRIS_iutest_util_assertion_HPP_A45F8265_40E0_44f2_91C6_090B1778657C_
#define INCG_IRIS_iutest_util_assertion_HPP_A45F8265_40E0_44f2_91C6_090B1778657C_

//======================================================================
// include
#include "../internal/iutest_type_traits.hpp"

namespace iuutil
{

//======================================================================
// define
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	文字列長の一致 テスト
*/
#ifndef IUTEST_ASSERT_STRLNEQ
#  define	IUTEST_ASSERT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_ASSERT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	文字列長の一致 テスト
*/
#ifndef IUTEST_EXPECT_STRLNEQ
#  define	IUTEST_EXPECT_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_EXPECT_FAILURE)
#endif

/**
 * @ingroup	IUTEST_INFORM
 * @brief	文字列長の一致 テスト
*/
#ifndef IUTEST_INFORM_STRLNEQ
#  define	IUTEST_INFORM_STRLNEQ(len, v2)			IUTEST_TEST_STRLNEQ(len, v2, IUTEST_INFORM_FAILURE)
#endif

/**
 * @private
 * @{
*/
#define	IUTEST_TEST_STRLNEQ(len, v2, on_failure)	IUTEST_PRED_FORMAT2_( ::iuutil::CmpHelperSTRLNEQ, len, v2, on_failure )

/**
 * @}
*/

//======================================================================
// function
/**
 * @brief	文字列長アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										 , size_t len1, const char* val2)
{
	size_t	len2 = strlen(val2);
	if( len2 == len1 ) return ::iutest::AssertionSuccess();
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == strlen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1 ;
}
/**
 * @brief	文字列長アサーションフォーマッター
*/
inline ::iutest::AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRLNEQ(const char* expr1, const char* expr2
										 , size_t len1, const wchar_t* val2)
{
	size_t	len2 = wcslen(val2);
	if( len2 == len1 ) return ::iutest::AssertionSuccess();
	return ::iutest::AssertionFailure() << "error: Value of: " << expr1 << " == wcslen(" << expr2 << ")"
		<< "\n  Actual: " << val2 << " : " << len2 << "\nExpected: " << len1 ;
}

/**
 * @private
 * @{
*/
#define COMPARE_HELPER_DEC(name)	struct name {											\
	template<typename T1, typename T2>														\
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const T1& val1, const T2& val2)	{	\
		return ::iutest::internal::CmpHelper##name(expr1, expr2, val1, val2);				\
	}																						\
	}
/**
 * @}
*/

/**
 * @brief	OR テスト用オブジェクト郡
*/
struct CmpHelper
{
	COMPARE_HELPER_DEC(EQ);	//!< OR テスト用 EQ
	COMPARE_HELPER_DEC(NE);	//!< OR テスト用 NE
	COMPARE_HELPER_DEC(LE);	//!< OR テスト用 LE
	COMPARE_HELPER_DEC(LT);	//!< OR テスト用 LT
	COMPARE_HELPER_DEC(GE);	//!< OR テスト用 GE
	COMPARE_HELPER_DEC(GT);	//!< OR テスト用 GT
#undef COMPARE_HELPER_DEC
};

/**
 * @brief	OR テスト用比較ヘルパー
*/
template<typename COMP>
struct CmpHelperOR
{
private:
	template<typename T, typename DMY=void>
	struct CompImpl
	{
		template<typename T1, typename T2>
		static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
			, T1 val1, T2 val2)
		{
			return T::Comp(expr1, expr2, val1, val2);
		}
	};
	template<typename DMY>
	struct CompImpl<CmpHelper::EQ, DMY>
	{
		template<typename T1, typename T2>
		static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
			, T1 val1, T2 val2)
		{
			// val1 == actual
			return CmpHelper::EQ::Comp(expr2, expr1, val2, val1);
		}
	};
public:

	/**
	 * @brief	フォーマッター
	*/
	template<typename T1, typename T2>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2
		, T1 val1, T2 val2)
	{
		return CompImpl<COMP>::Comp(expr1, expr2, val1, val2);
	}
	/** @overload */
	template<typename T1, typename T2, typename T3>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3
		, T1 val1, T2 val2, T3 val3)
	{
		typename ::iutest_type_traits::add_revalue_reference< ::iutest::AssertionResult >::type ar = Comp(expr1, expr2, val1, val2);
		if( ar ) return ar;
		return Comp(expr1, expr3, val1, val3) << "\n" << ar.message();
	}
	/** @overload */
	template<typename T1, typename T2, typename T3, typename T4>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3, const char* expr4
		, T1 val1, T2 val2, T3 val3, T4 val4)
	{
		typename ::iutest_type_traits::add_revalue_reference< ::iutest::AssertionResult >::type ar =  Comp(expr1, expr2, expr3, val1, val2, val3);
		if( ar ) return ar;
		return Comp(expr1, expr4, val1, val4) << "\n" << ar.message();
	}
	/** @overload */
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static ::iutest::AssertionResult Comp(const char* expr1, const char* expr2, const char* expr3, const char* expr4, const char* expr5
		, T1 val1, T2 val2, T3 val3, T4 val4, T5 val5)
	{
		typename ::iutest_type_traits::add_revalue_reference< ::iutest::AssertionResult >::type ar =  Comp(expr1, expr2, expr3, expr4, val1, val2, val3, val4);
		if( ar ) return ar;
		return Comp(expr1, expr5, val1, val5) << "\n" << ar.message();
	}
};

}	// end of namespace iuutil

#endif
