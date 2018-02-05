//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        flagfile_tests.cpp
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

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_FOPEN
#  define FLAG_FILE_TEST    1
#else
#  define FLAG_FILE_TEST    0
#endif

#if FLAG_FILE_TEST

IUTEST(Foo, Run)
{
    IUTEST_EXPECT_STREQ("testdata/flagfile.txt", ::iutest::IUTEST_FLAG(flagfile).c_str() );
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

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if FLAG_FILE_TEST
    ::std::vector< ::std::string > targv;
    for( int i=0; i < argc; ++i )
    {
        targv.push_back(argv[i]);
    }
    targv.push_back("--iutest_flagfile=testdata/flagfile.txt");
    ::iutest::InitIrisUnitTest(targv);
#else
    IUTEST_INIT(&argc, argv);
#endif
    return IUTEST_RUN_ALL_TESTS();
}

