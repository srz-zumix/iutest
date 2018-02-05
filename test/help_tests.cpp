//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        help_tests.cpp
 * @brief       help test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],   cmd }
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
        DECAL_ARGV("--help");
        IUTEST_INIT(&targc, targv);
#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
#endif
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;
    }
#if !defined(IUTEST_USE_GTEST)
    {
        int targc = 2;
        DECAL_ARGV("--help");
        IUTEST_INIT(&targc, targv);
        IUTEST_ADD_FAILURE();
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret == 0 ) return 1;
    }
#endif
    printf("*** Successful ***\n");
    return 0;
}

