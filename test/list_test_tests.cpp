//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        list_test_tests.cpp
 * @brief       iutest_list_tests command line test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

IUTEST(Test, A)
{
}

IUTEST(Test, B)
{
}

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, A)
{
}
IUTEST_INSTANTIATE_TEST_SUITE_P(Test, ParamTest, ::iutest::Values(42));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(TypedTest, int);

IUTEST_TYPED_TEST(TypedTest, A)
{
}

#endif

#if !defined(IUTEST_USE_GTEST)
const char list_test_str[] =
#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TYPED_TEST
"4 tests from 3 testsuite\n"
#elif IUTEST_HAS_TYPED_TEST || IUTEST_HAS_PARAM_TEST
"3 tests from 2 testsuite\n"
#else
"2 tests from 1 testsuite\n"
#endif
"Test\n"
"  A\n"
"  B\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0\n"
"  A\n"
#endif
#if IUTEST_HAS_PARAM_TEST
"Test/ParamTest\n"
"  A/0\n"
#endif
"";

const char list_test_with_where_str[] =
#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TYPED_TEST
"4 tests from 3 testsuite\n"
#elif IUTEST_HAS_TYPED_TEST || IUTEST_HAS_PARAM_TEST
"3 tests from 2 testsuite\n"
#else
"2 tests from 1 testsuite\n"
#endif
"Test\n"
"  A\n"
"  B\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0, where TypeParam = int\n"
"  A\n"
#endif
#if IUTEST_HAS_PARAM_TEST
"Test/ParamTest\n"
"  A/0, where GetParam() = 42\n"
#endif
"";

#endif

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L##cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],    cmd }
#endif

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
#ifdef UNICODE
#  define DECAL_ARGV_FILTER(cmd, filter) const wchar_t* targv[] = { argv[0], L##cmd, L##filter }
#else
#  define DECAL_ARGV_FILTER(cmd, filter) const char* targv[] = { argv[0], cmd, filter }
#endif
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    (void)argc;
    (void)argv;
    {
        int targc = 2;
        DECAL_ARGV("--gtest_list_tests");
        IUTEST_INIT(&targc, targv);

#if !defined(IUTEST_USE_GTEST)
        TestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
#endif
        IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(list_tests) );
        const int ret = IUTEST_RUN_ALL_TESTS();

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_ASSERT_STREQ(list_test_str, logger.c_str())
            << ::iutest::AssertionReturn<int>(1);
#endif
        if( ret != 0 ) return 1;
    }
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
    {
        int targc = 2;
        DECAL_ARGV("--iutest_list_tests_with_where");
        IUTEST_INIT(&targc, targv);

        TestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);

        IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(list_tests) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(list_tests_with_where) );
        const int ret = IUTEST_RUN_ALL_TESTS();

        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_ASSERT_STREQ(list_test_with_where_str, logger.c_str())
            << ::iutest::AssertionReturn<int>(1);
        if( ret != 0 ) return 1;
    }
    {
        int targc = 3;
        DECAL_ARGV_FILTER("--iutest_list_tests", "--iutest_filter=Test.*-Test.B");
        IUTEST_INIT(&targc, targv);

        TestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
        const int ret = IUTEST_RUN_ALL_TESTS();
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest\n  A\n", logger.c_str())
            << ::iutest::AssertionReturn<int>(1);
        if( ret != 0 ) return 1;
    }
    {
        int targc = 2;
        DECAL_ARGV("--iutest_list_tests_with_where");
        IUTEST_INIT(&targc, targv);
#if IUTEST_HAS_PARAM_TEST
        IUTEST_FLAG_SET(filter, "Test/ParamTest.A/0");
#elif IUTEST_HAS_TYPED_TEST
        IUTEST_FLAG_SET(filter, "TypedTest/0.A");
#else
        IUTEST_FLAG_SET(filter, "Test.B");
#endif

        TestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
        const int ret = IUTEST_RUN_ALL_TESTS();
        ::iutest::detail::iuConsole::SetLogger(NULL);
#if IUTEST_HAS_PARAM_TEST
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest/ParamTest\n  A/0, where GetParam() = 42\n", logger.c_str())
#elif IUTEST_HAS_TYPED_TEST
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTypedTest/0, where TypeParam = int\n  A\n", logger.c_str())
#else
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest\n  B\n", logger.c_str())
#endif
            << ::iutest::AssertionReturn<int>(1);
        if( ret != 0 ) return 1;
    }
    {
        int targc = 2;
        DECAL_ARGV("--iutest_list_tests");
        IUTEST_INIT(&targc, targv);
        IUTEST_FLAG_SET(filter, "NoSuchTest.*");

        TestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
        const int ret = IUTEST_RUN_ALL_TESTS();
        ::iutest::detail::iuConsole::SetLogger(NULL);
        IUTEST_ASSERT_STREQ("0 tests from 0 testsuite\n", logger.c_str())
            << ::iutest::AssertionReturn<int>(1);
        if( ret != 0 ) return 1;
    }
#endif
    return 0;
}
