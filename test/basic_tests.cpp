//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        basic_tests.cpp
 * @brief       iutest basic test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)
IUTEST(VersionTest, Check)
{
    unsigned long v = (IUTEST_MAJORVER << 24) | (IUTEST_MINORVER << 16) | (IUTEST_MICROVER << 8) | IUTEST_REVISION;
    IUTEST_ASSERT_EQ( IUTEST_VER, v );
}
#endif

#define EVAL_IUTEST_FLAG(expression)  x = (expression) ? x : __LINE__

IUTEST(CommandLineFlagTest, CanBeAccessed)
{
    int x = 1;
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(break_on_failure) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(catch_exceptions) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(list_tests) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(print_time) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(random_seed) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(shuffle) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(throw_on_failure) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(color) != "unknown" );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(filter) != "unknown" );
#if !defined(IUTEST_USE_GTEST)
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(verbose) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(file_location_style_msvc) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(list_tests_with_where) );
    EVAL_IUTEST_FLAG( ::iutest::IUTEST_FLAG(default_package_name) != "unknown" );
#endif
        EVAL_IUTEST_FLAG( (::iutest::IUTEST_FLAG(repeat) > 0) );
    IUTEST_EXPECT_NE(0, x);
}

IUTEST(TestInformation, CurrentTestSuite)
{
    IUTEST_ASSERT_STREQ("TestInformation", ::iuutil::GetCurrentTestSuite()->name());
    IUTEST_ASSERT_TRUE(::iuutil::GetCurrentTestSuite()->should_run());
}

IUTEST(TestInformation, CurrentTestInfo)
{
    IUTEST_ASSERT_STREQ("TestInformation", ::iuutil::GetTestSuiteName(::iutest::UnitTest::GetInstance()->current_test_info()));
    IUTEST_ASSERT_STREQ("CurrentTestInfo", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
    IUTEST_ASSERT_TRUE(::iutest::UnitTest::GetInstance()->current_test_info()->should_run());
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
    IUTEST_ASSERT_EQ(NULL, ::iutest::UnitTest::GetInstance()->current_test_info()->type_param());
    IUTEST_ASSERT_EQ(NULL, ::iutest::UnitTest::GetInstance()->current_test_info()->value_param());
#endif
}

IUTEST(TestInformation, DISABLED_Test)
{
}

IUTEST(TestInformation, TestInfoCount)
{
    IUTEST_ASSERT_EQ(4, ::iuutil::GetCurrentTestSuite()->total_test_count());
    IUTEST_ASSERT_EQ(3, ::iuutil::GetCurrentTestSuite()->test_to_run_count());
    IUTEST_ASSERT_EQ(3, ::iuutil::GetCurrentTestSuite()->successful_test_count());
    IUTEST_ASSERT_EQ(0, ::iuutil::GetCurrentTestSuite()->failed_test_count());
    IUTEST_ASSERT_EQ(1, ::iuutil::GetCurrentTestSuite()->disabled_test_count());
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
    IUTEST_ASSERT_EQ(1, ::iuutil::GetCurrentTestSuite()->reportable_disabled_test_count());
    IUTEST_ASSERT_EQ(4, ::iuutil::GetCurrentTestSuite()->reportable_test_count());
#endif
#if !defined(IUTEST_USE_GTEST)
    IUTEST_ASSERT_EQ(0, ::iuutil::GetCurrentTestSuite()->test_run_skipped_count());
    IUTEST_ASSERT_EQ(0, ::iuutil::GetCurrentTestSuite()->reportable_test_run_skipped_count());
    IUTEST_ASSERT_EQ(1, ::iuutil::GetCurrentTestSuite()->skip_test_count());
    IUTEST_ASSERT_EQ(1, ::iuutil::GetCurrentTestSuite()->reportable_skip_test_count());
#endif
}

#if IUTEST_HAS_GENRAND

IUTEST(TestRandom, Genrand)
{
    IUTEST_ASSERT_LE(genrand(100), 100u);
}

#if IUTEST_HAS_CXX_HDR_RANDOM

IUTEST(TestRandom, Engine)
{
    IUTEST_ASSERT_LE( ::std::uniform_int_distribution<unsigned int>(0, 100)(random_engine()), 100u);
}
#endif

#endif

#if !defined(IUTEST_USE_GTEST)

// name conflict test
IUTEST(TestNameConflict_X, Y)
{
}
IUTEST(TestNameConflict, X_Y)
{
}

#endif

#define SHOW_MACRO(macro)   ::iutest::detail::iuConsole::output("#define %s  %s\n", #macro, IUTEST_PP_TOSTRING(macro))

IUTEST(Config, Check)
{
#ifdef _MSC_FULL_VER
    SHOW_MACRO(_MSC_FULL_VER);
#endif
#ifdef _LIBCPP_VERSION
    SHOW_MACRO(_LIBCPP_VERSION);
#endif
#ifdef __GLIBCXX__
    SHOW_MACRO(__GLIBCXX__);
#endif
}

