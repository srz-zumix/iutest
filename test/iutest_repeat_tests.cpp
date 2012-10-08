//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_repeat_tests.cpp
 * @brief		ŒJ‚è•Ô‚µ‘Î‰žƒeƒXƒg
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

//======================================================================
// include
#include "../include/iutest.hpp"

#include <assert.h>

int g_foo_bar = 0;
int g_hoge_fuga = 0;

IUTEST(Foo, Bar)
{
	++g_foo_bar;
}

IUTEST(Hoge, Fuga)
{
	++g_hoge_fuga;
}

#if IUTEST_HAS_PARAM_TEST
int g_param_test = 0;

const int kNumberOfParamTests = 10;

class TestP : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_CASE_P(Foo, TestP, ::iutest::Range<int>(0, kNumberOfParamTests));

IUTEST_P(TestP, Bar)
{
	++g_param_test;
}

#endif

int g_environment_setup = 0;
int g_environment_teardown = 0;

class MyEnvironment : public ::iutest::Environment
{
private:
	virtual void SetUp(void)	{ ++g_environment_setup; }
	virtual void TearDown(void)	{ ++g_environment_teardown; }
};

IUTEST(Repeat, Counter)
{
	IUTEST_ASSERT_EQ(g_environment_setup, ::iutest::UnitTest::GetInstance()->repeat_counter()+1);
}


void ClearCounter(void)
{
	g_foo_bar = 0;
	g_hoge_fuga = 0;
	g_environment_setup = 0;
	g_environment_teardown = 0;
#if IUTEST_HAS_PARAM_TEST
	g_param_test = 0;
#endif
}

void CheckCount(int expected)
{
	IUTEST_EXPECT_EQ(expected, g_environment_setup);
	IUTEST_EXPECT_EQ(expected, g_environment_teardown);
	IUTEST_EXPECT_EQ(expected, g_foo_bar);
	IUTEST_EXPECT_EQ(expected, g_hoge_fuga);
#if IUTEST_HAS_PARAM_TEST
	IUTEST_EXPECT_EQ(expected*kNumberOfParamTests, g_param_test);
#endif
}

bool RunTest(void)
{
	ClearCounter();
	IUTEST_RUN_ALL_TESTS();
	return ::iutest::UnitTest::GetInstance()->Passed();
}

bool RepeatTest(int repeat)
{
	::iutest::IUTEST_FLAG(repeat) = repeat;
	return RunTest();
}

bool RepeatTestUnspecified(void)
{
	RunTest();
	CheckCount(1);
	return ::iutest::UnitTest::GetInstance()->Passed();
}

bool RepeatTestNonFilter(int repeat)
{
	if( !RepeatTest(repeat) ) return false;
	CheckCount(repeat);
	return ::iutest::UnitTest::GetInstance()->Passed();
}

bool RepeatTestWithEmpyFilter(int repeat)
{
	::iutest::IUTEST_FLAG(filter) = "None";
	if( !RepeatTest(repeat) ) return false;
	CheckCount(0);
	return ::iutest::UnitTest::GetInstance()->Passed();
}

bool RepeatTestWithFilter(int repeat)
{
	::iutest::IUTEST_FLAG(filter) = "*Bar*";
	if( !RepeatTest(repeat) ) return false;
	IUTEST_EXPECT_EQ(repeat, g_environment_setup);
	IUTEST_EXPECT_EQ(repeat, g_environment_teardown);
	IUTEST_EXPECT_EQ(repeat, g_foo_bar);
	IUTEST_EXPECT_EQ(0, g_hoge_fuga);
#if IUTEST_HAS_PARAM_TEST
	IUTEST_EXPECT_EQ(repeat*kNumberOfParamTests, g_param_test);
#endif
	return ::iutest::UnitTest::GetInstance()->Passed();
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	MyEnvironment* const env = new MyEnvironment();
	assert( ::iutest::AddGlobalTestEnvironment(env) == env );
	IUTEST_INIT(&argc, argv);
	
	assert( RepeatTestUnspecified() );
	assert( RepeatTestNonFilter(0) );
	assert( RepeatTestNonFilter(2) );
	assert( RepeatTestNonFilter(10) );

	assert( RepeatTestWithEmpyFilter(2) );
	assert( RepeatTestWithEmpyFilter(3) );
	
	assert( RepeatTestWithFilter(3) );

	printf("*** Successful ***\n");
	return 0;
}

