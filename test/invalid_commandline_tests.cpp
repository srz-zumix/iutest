//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        invalid_commandline_tests.cpp
 * @brief       不正なコマンドライン引数対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(Foo, NotRun)
{
    IUTEST_ASSERT_EQ(0, 1);
}

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
#if defined(OUTPUTXML)
    // 実行対象テストがないので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    {
        int targc = 2;
        DECAL_ARGV("--gtest_foo");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(2, targc);
#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
#endif
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
#if !defined(IUTEST_USE_GTEST)
    {
        int targc = 2;
        DECAL_ARGV("--iutest_foo");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(2, targc);
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_random_seed");
        vargv.push_back("--iutest_repeat");
        vargv.push_back("--iutest_stream_result_to");
        vargv.push_back("--iutest_file_location");
        vargv.push_back("--iutest_file_location=xxx");
        vargv.push_back("--iutest_print_time");
        vargv.push_back("--iutest_print_time=");
        vargv.push_back("--iutest_catch_exceptions");
        vargv.push_back("--iutest_color");
        vargv.push_back("--iutest_color=hoge");
        vargv.push_back("--iutest_shuffle=1");
        vargv.push_back("--iutest_output");
        vargv.push_back("--iutest_also_run_disabled_tests=1");
        vargv.push_back("--iutest_list_tests=1");
        vargv.push_back("--iutest_list_tests_with_where=1");
        vargv.push_back("--x");
        vargv.push_back("-x");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(17u, vargv.size()) << ::iutest::PrintToString(vargv);
        IUTEST_EXPECT_TRUE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
#endif
    printf("*** Successful ***\n");
    return 0;
}

