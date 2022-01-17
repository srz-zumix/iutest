//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        repeat_tests.cpp
 * @brief       繰り返し対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

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

IUTEST_INSTANTIATE_TEST_SUITE_P(Foo, TestP, ::iutest::Range<int>(0, kNumberOfParamTests));

IUTEST_P(TestP, Bar)
{
    ++g_param_test;
}

#endif

int g_environment_setup = 0;
int g_environment_teardown = 0;

class MyEnvironment IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void SetUp(void)    IUTEST_CXX_OVERRIDE { ++g_environment_setup; }
    virtual void TearDown(void) IUTEST_CXX_OVERRIDE { ++g_environment_teardown; }
};

IUTEST(Repeat, Counter)
{
#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_EQ(g_environment_setup, ::iutest::UnitTest::GetInstance()->repeat_counter()+1);
#endif
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
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return false;
    return ::iutest::UnitTest::GetInstance()->Passed();
}

bool RepeatTest(int repeat)
{
    ::iutest::IUTEST_FLAG(repeat) = repeat;
    return RunTest();
}

bool RepeatTestUnspecified(void)
{
    (void)RunTest();
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
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::AddGlobalTestEnvironment(env) == env );
    IUTEST_INIT(&argc, argv);

    IUTEST_TERMINATE_ON_FAILURE( RepeatTestUnspecified() );
    IUTEST_TERMINATE_ON_FAILURE( RepeatTestNonFilter(0) );
    IUTEST_TERMINATE_ON_FAILURE( RepeatTestNonFilter(2) );
    IUTEST_TERMINATE_ON_FAILURE( RepeatTestNonFilter(10) );

    IUTEST_TERMINATE_ON_FAILURE( RepeatTestWithEmpyFilter(2) );
    IUTEST_TERMINATE_ON_FAILURE( RepeatTestWithEmpyFilter(3) );

    IUTEST_TERMINATE_ON_FAILURE( RepeatTestWithFilter(3) );

    printf("*** Successful ***\n");
    return 0;
}

