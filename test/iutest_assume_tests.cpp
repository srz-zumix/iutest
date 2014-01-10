//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assume_tests.cpp
 * @brief		iutest assume test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

static int assume_test_var_a=0;
static int assume_test_var_b=1;

#define DECL_ASSUMETEST(prod, expr)		\
		IUTEST(AssumeTest, prod) {		\
			IUTEST_ASSUME_##prod expr;	\
			IUTEST_ASSERT_##prod expr;	\
		}
		
IUTEST(AssumeTest, A)
{
	IUTEST_ASSUME_TRUE(false);
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(AssumeTest, B)
{
	IUTEST_ASSUME_FALSE(true);
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(AssumeTest, C)
{
	IUTEST_EXPECT_EQ(0, 1);
	IUTEST_ASSUME_EQ(0, 1);
}

DECL_ASSUMETEST(EQ, (0,1))
DECL_ASSUMETEST(NE, (1,1))
DECL_ASSUMETEST(LT, (2,1))
DECL_ASSUMETEST(LE, (2,1))
DECL_ASSUMETEST(GT, (1,2))
DECL_ASSUMETEST(GE, (1,2))
DECL_ASSUMETEST(NULL, (&assume_test_var_a))
DECL_ASSUMETEST(NOTNULL, (NULL))
DECL_ASSUMETEST(SAME, (assume_test_var_a, assume_test_var_b))
DECL_ASSUMETEST(FLOAT_EQ, (0.0f,1.0f))
DECL_ASSUMETEST(DOUBLE_EQ, (0.0,1.0))
DECL_ASSUMETEST(NEAR, (0.0,10.0, 1.0))
DECL_ASSUMETEST(STREQ, ("A","a"))
DECL_ASSUMETEST(STRNE, ("A","A"))
DECL_ASSUMETEST(STRCASEEQ, ("A","B"))
DECL_ASSUMETEST(STRCASENE, ("A","a"))
#if defined(IUTEST_OS_WINDOWS) && IUTEST_OS_WINDOWS
DECL_ASSUMETEST(HRESULT_SUCCEEDED, (-1))
DECL_ASSUMETEST(HRESULT_FAILED, (0))
#endif

IUTEST(AssumeTest, THROW)
{
	IUTEST_ASSUME_THROW((void)0, ::std::bad_exception);
	IUTEST_ASSERT_THROW((void)0, ::std::bad_exception);
}

IUTEST(AssumeTest, ANY_THROW)
{
	IUTEST_ASSUME_ANY_THROW((void)0);
	IUTEST_ASSERT_ANY_THROW((void)0);
}

void AssumeTest_NO_THROW_Test() { throw 1; }

IUTEST(AssumeTest, NO_THROW)
{
	IUTEST_ASSUME_NO_THROW(AssumeTest_NO_THROW_Test());
	IUTEST_ASSERT_NO_THROW(AssumeTest_NO_THROW_Test());
}

IUTEST(AssumeTest, THROW_VALUE_EQ)
{
	IUTEST_ASSUME_THROW_VALUE_EQ((void)0, int, 0);
	IUTEST_ASSERT_THROW_VALUE_EQ((void)0, int, 0);
}

IUTEST(AssumeTest, THROW_VALUE_NE)
{
	IUTEST_ASSUME_THROW_VALUE_NE((void)0, int, 0);
	IUTEST_ASSERT_THROW_VALUE_NE((void)0, int, 0);
}

IUTEST(AssumeTest, THROW_VALUE_STREQ)
{
	IUTEST_ASSUME_THROW_VALUE_STREQ((void)0, const char*, "");
	IUTEST_ASSERT_THROW_VALUE_STREQ((void)0, const char*, "");
}

IUTEST(AssumeTest, THROW_VALUE_STRCASEEQ)
{
	IUTEST_ASSUME_THROW_VALUE_STRCASEEQ((void)0, const char*, "");
	IUTEST_ASSERT_THROW_VALUE_STRCASEEQ((void)0, const char*, "");
}

#if defined(IUTEST_OS_WINDOWS) && IUTEST_OS_WINDOWS
static const int assume_test_count = 25 + 2;
#else
static const int assume_test_count = 25;
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
	IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
	// 失敗テストを含むので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	const int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->test_run_skipped_count() == assume_test_count );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == assume_test_count );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == assume_test_count );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == assume_test_count );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->successful_test_case_count() == 0 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
#endif
	printf("*** Successful ***\n");
	return 0;
}

