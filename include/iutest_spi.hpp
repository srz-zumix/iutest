//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_spi.hpp
 * @brief		iris unit test spi 対応用 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_spi_HPP_
#define INCG_IRIS_iutest_spi_HPP_

//======================================================================
// include
#include "iutest.hpp"

#ifdef _MSC_VER
// /ZI オプションだと __LINE__ が __LINE__Var+N(Nは番号) になりコンパイルエラーになるための対応
#  ifndef __LINE__Var
#    define __LINE__Var	0
#  endif
#endif

//======================================================================
// define
/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	Fatal Failure 発生確認テスト
*/
#define IUTEST_ASSERT_FATAL_FAILURE(statement, substr)		IUTEST_TEST_FATAL_FAILURE_(statement, #statement, substr, IUTEST_ASSERT_FAILURE)

/**
 * @ingroup	IUTEST_ASSERT_
 * @brief	Non Fatal Failure 発生確認テスト
*/
#define IUTEST_ASSERT_NONFATAL_FAILURE(statement, substr)	IUTEST_TEST_NONFATAL_FAILURE_(statement, #statement, substr, IUTEST_ASSERT_FAILURE)

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	Fatal Failure 発生確認テスト
*/
#define IUTEST_EXPECT_FATAL_FAILURE(statement, substr)		IUTEST_TEST_FATAL_FAILURE_(statement, #statement, substr, IUTEST_EXPECT_FAILURE)

/**
 * @ingroup	IUTEST_EXPECT_
 * @brief	Non Fatal Failure 発生確認テスト
*/
#define IUTEST_EXPECT_NONFATAL_FAILURE(statement, substr)	IUTEST_TEST_NONFATAL_FAILURE_(statement, #statement, substr, IUTEST_EXPECT_FAILURE)


/**
 * @private
 * @{
*/

#if IUTEST_SPI_LAMBDA_ENABLE

#if IUTEST_HAS_EXCEPTIONS && IUTEST_THROW_ON_ASSERT_FAILURE
#  define IIUT_STATEMENT_EXECUTER(statement)	[&](){ try {	\
	::iutest::detail::ScopedSPITestFlag guard;					\
	statement;													\
	} catch(...) {}												\
	}()
#else
#  define IIUT_STATEMENT_EXECUTER(statement)	[&](){ ::iutest::detail::ScopedSPITestFlag guard; statement; }()
#endif

#define IUTEST_TEST_FATAL_FAILURE_(statement, text, substr, on_failure)		\
	if( ![&]() -> bool {													\
		::iutest::detail::NewTestPartResultCheckHelper::Reporter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondEq<			\
				::iutest::TestPartResult::kFatalFailure>					\
				, ::iutest::detail::FakeTestPartResultReporter > iutest_failure_checker;		\
		IIUT_STATEMENT_EXECUTER(statement);									\
		return iutest_failure_checker.count() != 0;							\
	}() )																	\
		on_failure("\nExpected: " text " generate new fatal failure.\n  Actual: it does.") << substr

#define IUTEST_TEST_NONFATAL_FAILURE_(statement, text, substr, on_failure)	\
	if( ![&]() -> bool {													\
		::iutest::detail::NewTestPartResultCheckHelper::Reporter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondEq<			\
				::iutest::TestPartResult::kNotFatalFailure>					\
				, ::iutest::detail::FakeTestPartResultReporter > iutest_failure_checker;	\
		IIUT_STATEMENT_EXECUTER(statement);									\
		return iutest_failure_checker.count() != 0;							\
	}() )																	\
		on_failure("\nExpected: " text " generate new non fatal failure.\n  Actual: it does.") << substr

#else

#if IUTEST_HAS_EXCEPTIONS && IUTEST_THROW_ON_ASSERT_FAILURE
#  define IIUT_STATEMENT_EXECUTER(statement)	struct IUTestFatalFailureStatement {	\
	static void Execute() { ::iutest::detail::ScopedSPITestFlag guard;					\
	try { statement; } catch(...) {} }													\
	};																					\
	IUTestFatalFailureStatement::Execute()
#else
#  define IIUT_STATEMENT_EXECUTER(statement)	struct IUTestFatalFailureStatement {	\
	static void Execute() { ::iutest::detail::ScopedSPITestFlag guard; statement; }		\
	};																					\
	IUTestFatalFailureStatement::Execute()
#endif

#define IUTEST_TEST_FATAL_FAILURE_(statement, text, substr, on_failure)		\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::detail::AlwaysTrue() ) {									\
		::iutest::detail::NewTestPartResultCheckHelper::Reporter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondEq<			\
				::iutest::TestPartResult::kFatalFailure>					\
				, ::iutest::detail::FakeTestPartResultReporter > iutest_failure_checker;	\
		IIUT_STATEMENT_EXECUTER(statement);									\
		if( iutest_failure_checker.count() == 0 ) {							\
			goto IUTEST_PP_CAT(iutest_label_test_fatalfailure_, __LINE__);	\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_test_fatalfailure_, __LINE__):			\
		on_failure("\nExpected: " text " generate new fatal failure.\n  Actual: it does.") << substr

#define IUTEST_TEST_NONFATAL_FAILURE_(statement, text, substr, on_failure)	\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_											\
	if( ::iutest::detail::AlwaysTrue() ) {									\
		::iutest::detail::NewTestPartResultCheckHelper::Reporter<			\
			::iutest::detail::NewTestPartResultCheckHelper::CondEq<			\
				::iutest::TestPartResult::kNotFatalFailure>					\
				, ::iutest::detail::FakeTestPartResultReporter > iutest_failure_checker;	\
		IIUT_STATEMENT_EXECUTER(statement);									\
		if( iutest_failure_checker.count() == 0 ) {							\
			goto IUTEST_PP_CAT(iutest_label_test_fatalfailure_, __LINE__);	\
		}																	\
	} else																	\
		IUTEST_PP_CAT(iutest_label_test_fatalfailure_, __LINE__):			\
		on_failure("\nExpected: " text " generate new non fatal failure.\n  Actual: it does.") << substr

//		IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(statement);

#endif

/**
 * @}
*/

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	SPI 用リポーター
*/
class FakeTestPartResultReporter : public TestPartResultReporterInterface
{
public:
	virtual ~FakeTestPartResultReporter(void) {}
	virtual void ReportTestPartResult(const TestPartResult& result) IUTEST_CXX_OVERRIDE
	{
		IUTEST_UNUSED_VAR(result);
	}
};

/**
 * @biref	フラグ変更スコープ
*/
class ScopedSPITestFlag : public TestFlag::ScopedGuard
{
public:
	ScopedSPITestFlag(void)
	{
		IUTEST_FLAG(throw_on_failure) = false;
		IUTEST_FLAG(break_on_failure) = false;
	}
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
