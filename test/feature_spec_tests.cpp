//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        feature_spec_tests.cpp
 * @brief       --feature --spce test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

TestLogger logger;

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],   cmd }
#endif

#ifdef UNICODE
#  define DECAL_ARGV2(cmd1, cmd2) const wchar_t* targv[] = { argv[0], L cmd1, L cmd2 }
#else
#  define DECAL_ARGV2(cmd1, cmd2) const char*    targv[] = { argv[0],   cmd1,   cmd2 }
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
    ::iutest::detail::iuConsole::SetLogger(&logger);

    {
        int targc = 2;
        DECAL_ARGV("--feature");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_FEATURE));
        logger.clear();
        const int ret = IUTEST_RUN_ALL_TESTS();
#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN   ("IUTEST_HAS_TYPED_TEST_P", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRNOTIN("IUTEST_HAS_TUPLE", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
        if( ret != 0 ) return 1;
    }

    {
        int targc = 2;
        DECAL_ARGV("--spec");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_SPEC));
        logger.clear();
        const int ret = IUTEST_RUN_ALL_TESTS();
#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRNOTIN("IUTEST_HAS_TYPED_TEST_P", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN   ("IUTEST_HAS_TUPLE", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
        if( ret != 0 ) return 1;
    }

    {
        int targc = 3;
        DECAL_ARGV2("--feature", "--spec");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_FEATURE));
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_SPEC));
        logger.clear();
        const int ret = IUTEST_RUN_ALL_TESTS();
#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN("IUTEST_HAS_TYPED_TEST_P", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("IUTEST_HAS_TUPLE", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
        if( ret != 0 ) return 1;
    }
#endif
    printf("*** Successful ***\n");
    return 0;
}

