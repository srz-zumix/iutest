//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		main.cpp
 * @brief		sample main ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

/*
 * is not available vprintf, can be replaced.
*/
//#define IUTEST_VPRINTF

/*
 * include testing framework
*/
#include "../include/iutest.hpp"

#if defined(USE_TAP)
#include "../include/listener/iutest_tap_printer.hpp"
#endif
#if defined(USE_PROGRESS)
#include "../include/listener/iutest_progress_printer.hpp"
#endif
#if defined(USE_SSTPNOTIFIER)
#include "../include/listener/iutest_sstp_notifier.hpp"
#endif

/** --------------------------------------------------
 * Environment サンプル
*//*--------------------------------------------------*/
class FooEnvironment : public ::iutest::Environment
{
	virtual void	SetUp(void)
	{
		iuutil::Console::output("FooEnvironment::SetUp\n");
	}
	virtual void	TearDown(void)
	{
		iuutil::Console::output("FooEnvironment::TearDown\n");
	}
};
#include <iostream>

#if defined(_MSC_VER) && IUTEST_HAS_LIB

#pragma comment(lib, IUTEST_LIB_NAME(libiutest_main) )

#else

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
	setlocale(LC_CTYPE, "");
#endif

#if 1
	iutest::AddGlobalTestEnvironment(new FooEnvironment());
#endif

	//iutest::IUTEST_FLAG(shuffle) = false;
	//iutest::IUTEST_FLAG(throw_on_failure) = true;
	IUTEST_INIT(&argc, argv);

#if defined(USE_TAP)
	::iutest::TAPPrintListener::SetUp();
#endif

#if defined(USE_PROGRESS)
	::iutest::ProgressPrintListener::SetUp();
#endif

#if defined(USE_SSTPNOTIFIER)
	::iutest::SSTPNotifier::SetUp("localhost");
#endif

	//::iuutil::QuietResultPrinter::SetUp();

	return IUTEST_RUN_ALL_TESTS();
}

#endif

/** --------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if defined(SHOW_FAILURE)	// Failure Test

IUTEST(TestFailure, EQ)
{
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(TestFailure, NE)
{
	int x=1, y=1;
	IUTEST_ASSERT_NE(x, y);
}

IUTEST(TestFailure, GE)
{
	float a = 0.1f, b = 1.0f;
	IUTEST_ASSERT_GE(a, b);
}

IUTEST(TestFailure, TRUE)
{
	IUTEST_ASSERT_TRUE(0);
	IUTEST_ASSERT_TRUE(false);
}

IUTEST(TestFailure, FALSE)
{
	IUTEST_ASSERT_FALSE(true);
	IUTEST_ASSERT_FALSE(2);
}

IUTEST(TestFailure, Fail)
{
	IUTEST_FAIL() << "add messages.\n";
}

#if defined(IUTEST_OS_WINDOWS)

IUTEST(TestFailure, HRESULT)
{
	IUTEST_ASSERT_HRESULT_SUCCEEDED(E_OUTOFMEMORY);
}

#endif

void AssertFunc(void)
{
	IUTEST_ASSERT_TRUE(FALSE);
}

IUTEST(TestFailure, NoFailure)
{
	IUTEST_INFORM_NO_FATAL_FAILURE( AssertFunc() );
	IUTEST_EXPECT_NO_FATAL_FAILURE( AssertFunc() );
	IUTEST_ASSERT_NO_FATAL_FAILURE( AssertFunc() );
}

#if IUTEST_HAS_GENRAND

IUTEST(TestExpectFailure, Random)
{
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
	IUTEST_EXPECT_EQ( genrand(), genrand() );
}

#endif

IUTEST(TestExpectFailure, Pred)
{
	int x=4, y=5;
	IUTEST_EXPECT_PRED1(IsOdd, x);
	IUTEST_EXPECT_PRED2(IsGreater, x, y);
}

IUTEST(TestExpectFailure, OREQ)
{
	IUTEST_EXPECT_PRED_FORMAT2(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT3(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 1);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 2, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT4(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 2, 0, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 2, 1, 0);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 0, 3, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 0, 2, 1);
	IUTEST_EXPECT_PRED_FORMAT5(iuutil::CmpHelperOR<iuutil::CmpHelper::EQ>::Comp, 100, 3, 2, 0, 1);
}

#if IUTEST_HAS_EXCEPTIONS
IUTEST(TestExpectFailure, Exception)
{
	IUTEST_EXPECT_THROW(ExceptionFunction(0), int);
	IUTEST_EXPECT_ANY_THROW(ExceptionFunction(0));
	IUTEST_EXPECT_NO_THROW(ExceptionFunction(2));
	IUTEST_EXPECT_NO_THROW(throw "error");

	IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 0);
	IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 2);

	IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "Error");
	IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "rror");
}
IUTEST(TestExpectFailure, UnexpectedException1)
{
	throw "fail";
}
IUTEST(TestExpectFailure, UnexpectedException2)
{
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
IUTEST_PRAGMA_GCC_WARN_PUSH()
IUTEST_PRAGMA_GCC_WARN_DISABLE("-Wnonnull")

	strcpy(NULL, NULL);

IUTEST_PRAGMA_GCC_WARN_POP()
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
}
#endif

IUTEST(TestExpectFailure, Mix)
{
	IUTEST_EXPECT_EQ(0.1, 1);
	IUTEST_EXPECT_NE(0, 0);
	IUTEST_EXPECT_LE(2, 0);
	IUTEST_EXPECT_LT(0, 0);
	IUTEST_EXPECT_GE(0, 2);
	IUTEST_EXPECT_GT(0, 0);
	IUTEST_EXPECT_TRUE(0);
	IUTEST_EXPECT_FALSE(1);
	IUTEST_EXPECT_FLOAT_EQ(0.0f, 0.1f);
	IUTEST_EXPECT_DOUBLE_EQ(0.0, 0.1);
	IUTEST_EXPECT_NEAR(0, 100, 2);
	IUTEST_EXPECT_FAIL();
	{
		::std::string str1 = "test";
		::std::string str2 = "text";

		IUTEST_EXPECT_STREQ("text", str1);
		IUTEST_EXPECT_STRNE("text", str2);
		IUTEST_EXPECT_STRCASEEQ("Text", str1);
		IUTEST_EXPECT_STRCASENE("Text", str2);
	}
	// EQ_COLLECTIONS
	{
		int  aa[] = { 0, 1, 2, 3, 4 };
		int  ab[] = { 0, 1, 2, 3, 4, 5 };
		char ac[] = { 0, 0, 2, 3, 5 };
		IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(ab, ab+(sizeof(ab)/sizeof(ab[0])), aa, aa+(sizeof(aa)/sizeof(aa[0])));
		IUTEST_EXPECT_EQ_COLLECTIONS(aa, aa+(sizeof(aa)/sizeof(aa[0])), ac, ac+(sizeof(ac)/sizeof(ac[0])));
	}
}

// サブルーチン
static void Sub1(int n)
{
	IUTEST_EXPECT_EQ(1, n);
}
static void Sub2(int n)
{
	IUTEST_ASSERT_EQ(1, n);
}

IUTEST(TestFailureSubroutine, Test1)
{
	{
		int x=100;
		IUTEST_SCOPED_TRACE(::iutest::Message() << "routine1. x=" << x);

		Sub1(x);
	}
	// ここの失敗には "routine1." のメッセージは表示されません。
	Sub1(3);
}

IUTEST(TestFailureSubroutine, Test2)
{
	{
		IUTEST_SCOPED_TRACE("routine2.");
		//IUTEST_SCOPED_TRACE("routine2.") << "iutest can do." ;

		Sub2(2);
	}
	// ここの失敗には "routine2." のメッセージは表示されません。
	Sub2(3);
}

/** --------------------------------------------------
 * パラメタライズ関数コール
*//*--------------------------------------------------*/
#if IUTEST_HAS_PARAM_METHOD_TEST

IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 0, 0);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 1, 2);
IUTEST_PMZ(TestFailureParamMethod, EQ, TestFunction, 2, 2);

typedef TestFixed TestFailureParamMethodFixed;

IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(TestFailureParamMethodFixed, EQ, TestFunction, 2, 3);

#endif

#endif
