//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        flagfile_gtest_tests.cpp
 * @brief       flag by file test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)
#  define FLAG_FILE_TEST    IUTEST_HAS_FOPEN
#else
#  if GTEST_VER >= 0x01080000
#    define FLAG_FILE_TEST  GTEST_USE_OWN_FLAGFILE_FLAG_
#  else
#    define FLAG_FILE_TEST  0
#  endif
#endif

#if FLAG_FILE_TEST

IUTEST(Foo, Run)
{
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("testdata/gtest_flagfile.txt", ::iutest::IUTEST_FLAG(flagfile).c_str() );
#endif
    IUTEST_EXPECT_STREQ("*Run*:*OK*", ::iutest::IUTEST_FLAG(filter).c_str() );
    IUTEST_EXPECT_STREQ( "no", ::iutest::IUTEST_FLAG(color).c_str() );
}

IUTEST(Foo, NG)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, OK)
{
    IUTEST_ASSERT_EQ(3, 3);
}

#ifdef UNICODE
#  define DECAL_ARGV(...) const wchar_t* targv[] = { argv[0], L ##__VA_ARGS__ }
#else
#  define DECAL_ARGV(...) const char*    targv[] = { argv[0],     __VA_ARGS__ }
#endif

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if FLAG_FILE_TEST
    (void)argc;
    int targc = 2;
    DECAL_ARGV("--gtest_flagfile=testdata/gtest_flagfile.txt");
    IUTEST_INIT(&targc, targv);
#else
    IUTEST_INIT(&argc, argv);
#endif
    return IUTEST_RUN_ALL_TESTS();
}

