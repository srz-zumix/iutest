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
#include <cstdio>

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
class ListListener : public ::iutest::EmptyTestEventListener
{
public:
    ListListener() : calls(0), count(-1) {}
    virtual void OnListup(int total_test_num, const ::std::vector< ::iutest::TestSuite*>& tests) IUTEST_CXX_OVERRIDE
    {
        ++calls;
        count = total_test_num;
        suites = tests;
    }
    bool HasAllSuites() const
    {
        const ::iutest::UnitTest* unit_test = ::iutest::UnitTest::GetInstance();
        const int suite_count = unit_test->total_test_suite_count();
        if( suites.size() != static_cast<size_t>(suite_count) ) return false;
        for( int i = 0; i < suite_count; ++i )
        {
            if( suites[static_cast<size_t>(i)] != unit_test->GetTestSuite(i) ) return false;
        }
        return true;
    }
    int calls;
    int count;
    ::std::vector< ::iutest::TestSuite*> suites;
};

#if IUTEST_HAS_REGISTER_TEST && IUTEST_HAS_FOPEN && !defined(__WANDBOX__)
class ListRegisteredTest : public ::iutest::Test
{
    virtual void Body() IUTEST_CXX_OVERRIDE {}
};

::iutest::Test* MakeListRegisteredTest() { return new ListRegisteredTest; }
#endif

const char list_test_str[] =
#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TYPED_TEST
"4 tests from 3 testsuite\n"
#elif IUTEST_HAS_TYPED_TEST || IUTEST_HAS_PARAM_TEST
"3 tests from 2 testsuite\n"
#else
"2 tests from 1 testsuite\n"
#endif
"Test.\n"
"  A\n"
"  B\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0.\n"
"  A\n"
#endif
#if IUTEST_HAS_PARAM_TEST
"Test/ParamTest.\n"
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
"Test.\n"
"  A\n"
"  B\n"
#if IUTEST_HAS_TYPED_TEST
"TypedTest/0, where TypeParam = int.\n"
"  A\n"
#endif
#if IUTEST_HAS_PARAM_TEST
"Test/ParamTest.\n"
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
#if !defined(IUTEST_USE_GTEST)
    ListListener* listener = new ListListener;
    ::iutest::UnitTest::GetInstance()->listeners().Append(listener);
#endif
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
        IUTEST_ASSERT_EQ(1, listener->calls) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_TRUE(listener->HasAllSuites()) << ::iutest::AssertionReturn<int>(1);
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
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest.\n  A\n", logger.c_str())
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(1, listener->count) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_TRUE(listener->HasAllSuites()) << ::iutest::AssertionReturn<int>(1);
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
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest/ParamTest.\n  A/0, where GetParam() = 42\n", logger.c_str())
#elif IUTEST_HAS_TYPED_TEST
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTypedTest/0, where TypeParam = int.\n  A\n", logger.c_str())
#else
        IUTEST_ASSERT_STREQ("1 tests from 1 testsuite\nTest.\n  B\n", logger.c_str())
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
        IUTEST_ASSERT_EQ(0, listener->count) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_TRUE(listener->HasAllSuites()) << ::iutest::AssertionReturn<int>(1);
        if( ret != 0 ) return 1;
    }
#if IUTEST_HAS_FOPEN && !defined(__WANDBOX__)
    {
#if IUTEST_HAS_REGISTER_TEST
        ::iutest::RegisterTest("Escaped&Suite", "Test<Name", "type<&>", "value<&>"
            , "a&b<.cpp", 123, &MakeListRegisteredTest);
        ::iutest::RegisterTest("Escaped&Suite", "NoFile", NULL, NULL
            , NULL, 0, &MakeListRegisteredTest);
#endif
        int targc = 3;
        DECAL_ARGV_FILTER("--iutest_list_tests", "--iutest_output=xml:list_test_output.xml");
        IUTEST_INIT(&targc, targv);
#if IUTEST_HAS_REGISTER_TEST
        IUTEST_FLAG_SET(filter, "Escaped&Suite.Test<Name");
#else
        IUTEST_FLAG_SET(filter, "Test.A");
#endif
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;

        ::std::string xml;
        IUTEST_ASSERT_TRUE(::iutest::detail::IFileSystem::ReadAll("list_test_output.xml", xml))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("<testsuites tests=\"1\""))
            << ::iutest::AssertionReturn<int>(1);
#if IUTEST_HAS_REGISTER_TEST
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("name=\"Escaped&amp;Suite\" tests=\"1\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("name=\"Test&lt;Name\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("file=\"a&amp;b&lt;.cpp\" line=\"123\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("value_param=\"value&lt;&amp;&gt;\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("type_param=\"type&lt;&amp;&gt;\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, xml.find("NoFile"))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_FLAG_SET(filter, "Escaped&Suite.NoFile");
        IUTEST_FLAG_SET(list_tests, true);
        IUTEST_ASSERT_EQ(0, IUTEST_RUN_ALL_TESTS()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_TRUE(::iutest::detail::IFileSystem::ReadAll("list_test_output.xml", xml))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("name=\"NoFile\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("file=\"\" line=\"0\""))
            << ::iutest::AssertionReturn<int>(1);
#else
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("name=\"A\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, xml.find("name=\"B\""))
            << ::iutest::AssertionReturn<int>(1);
#endif
        IUTEST_FLAG_SET(filter, "NoSuchTest.*");
        IUTEST_FLAG_SET(list_tests, true);
        IUTEST_ASSERT_EQ(0, IUTEST_RUN_ALL_TESTS()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_TRUE(::iutest::detail::IFileSystem::ReadAll("list_test_output.xml", xml))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, xml.find("<testsuites tests=\"0\""))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, xml.find("<testsuite "))
            << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(0, ::std::remove("list_test_output.xml"))
            << ::iutest::AssertionReturn<int>(1);
    }
#endif
#endif
    return 0;
}
