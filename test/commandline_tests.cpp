﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        commandline_tests.cpp
 * @brief       CommandLine tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2019, Takazumi Shirayanagi\n
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
#  define DECAL_ARGV(...) const wchar_t* targv[] = { argv[0], L ##__VA_ARGS__ }
#else
#  define DECAL_ARGV(...) const char*    targv[] = { argv[0],     __VA_ARGS__ }
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
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_NULLPTR
    {
        int targc = 0;
        IUTEST_INIT(&targc, nullptr);
    }
#endif

    {
        int targc = 2;
        DECAL_ARGV("--help");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
#if !defined(IUTEST_USE_GTEST)
    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));

        int targc = 2;
        DECAL_ARGV("--version");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        IUTEST_EXPECT_NE( "no", ::iutest::IUTEST_FLAG(color) );
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_VERSION));

        int targc = 2;
        DECAL_ARGV("--feature");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_FEATURE));

        int targc = 2;
        DECAL_ARGV("--spec");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_SPEC));
        int targc = 4;
        DECAL_ARGV("test1", "-v", "test2");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(3, targc);
        IUTEST_EXPECT_STREQ("test1", targv[1]);
        IUTEST_EXPECT_STREQ("test2", targv[2]);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("test1");
        vargv.push_back("-v");
        vargv.push_back("test2");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(2u, vargv.size());
        IUTEST_EXPECT_STREQ("test1", vargv[0]);
        IUTEST_EXPECT_STREQ("test2", vargv[1]);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }

    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_VERSION));

        int targc = 2;
        DECAL_ARGV("-h");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));

        int targc = 2;
        DECAL_ARGV("-?");
        IUTEST_INIT(&targc, targv);
        IUTEST_EXPECT_EQ(1, targc);
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }

    {
        const bool file_location_msvc = ::iutest::IUTEST_FLAG(file_location_style_msvc);
        ::iutest::IUTEST_FLAG(file_location_style_msvc) = !file_location_msvc;

        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_break_on_failure");
        vargv.push_back("--iutest_throw_on_failure");
        vargv.push_back("--iutest_filter");
        vargv.push_back("--iutest_file_location=auto");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());

        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(break_on_failure) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(throw_on_failure) );
        IUTEST_EXPECT_STREQ( "*", ::iutest::IUTEST_FLAG(filter).c_str() );
        IUTEST_EXPECT_EQ   ( file_location_msvc, ::iutest::IUTEST_FLAG(file_location_style_msvc) );

        if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;
    }

    {
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_HELP));
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_FEATURE));
        IUTEST_EXPECT_FALSE(::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::SHOW_VERSION));

        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_break_on_failure=1");
        vargv.push_back("--iutest_throw_on_failure=t");
        vargv.push_back("--iutest_also_run_disabled_tests");
        vargv.push_back("--iutest_catch_exceptions=yes");
        vargv.push_back("--iutest_print_time=n");
        vargv.push_back("--iutest_shuffle");
        vargv.push_back("--iutest_color=ansi");
        vargv.push_back("--iutest_file_location=vs");
        vargv.push_back("--iutest_random_seed=200");
        vargv.push_back("--iutest_repeat=2");
        vargv.push_back("--iutest_filter=Flag*");
        vargv.push_back("--iutest_default_package_name=root");
        vargv.push_back("--iutest_warning_into_error=t");
        vargv.push_back("--iutest_locale_ctype=C");
#if IUTEST_HAS_STREAM_RESULT
        vargv.push_back("--iutest_stream_result_to=test");
#endif
        vargv.push_back("--verbose");

        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());

        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(break_on_failure) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(throw_on_failure) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(catch_exceptions) );
        IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(print_time) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(shuffle) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(file_location_style_msvc) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(warning_into_error) );

        IUTEST_EXPECT_EQ( 200u, ::iutest::IUTEST_FLAG(random_seed) );
        IUTEST_EXPECT_EQ(   2 , ::iutest::IUTEST_FLAG(repeat) );

        IUTEST_EXPECT_STREQ( "ansi", ::iutest::IUTEST_FLAG(color).c_str() );
        IUTEST_EXPECT_STREQ( "Flag*", ::iutest::IUTEST_FLAG(filter).c_str() );
        IUTEST_EXPECT_STREQ( "root", ::iutest::IUTEST_FLAG(default_package_name).c_str() );
        IUTEST_EXPECT_STREQ( "C", ::iutest::IUTEST_FLAG(locale_ctype).c_str() );
#if IUTEST_HAS_STREAM_RESULT
        IUTEST_EXPECT_STREQ( "test", ::iutest::IUTEST_FLAG(stream_result_to).c_str() );
#endif
        IUTEST_EXPECT_TRUE (::iutest::TestFlag::IsEnableFlag(::iutest::TestFlag::VERBOSE));

        if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;
    }

    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("--gtest_break_on_failure=1");
        vargv.push_back("--gtest_throw_on_failure=t");
        vargv.push_back("--gtest_also_run_disabled_tests");
        vargv.push_back("--gtest_catch_exceptions=yes");
        vargv.push_back("--gtest_print_time=n");
        vargv.push_back("--gtest_shuffle");
        vargv.push_back("--gtest_color=ansi");
        vargv.push_back("--gtest_file_location=gcc");
        vargv.push_back("--gtest_random_seed=200");
        vargv.push_back("--gtest_repeat=2");
        vargv.push_back("--gtest_filter=Flag*");
        vargv.push_back("--iutest_default_package_name=");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());

        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(break_on_failure) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(throw_on_failure) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(catch_exceptions) );
        IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(print_time) );
        IUTEST_EXPECT_TRUE ( ::iutest::IUTEST_FLAG(shuffle) );
        IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(file_location_style_msvc) );

        IUTEST_EXPECT_EQ( 200u, ::iutest::IUTEST_FLAG(random_seed) );
        IUTEST_EXPECT_EQ(   2 , ::iutest::IUTEST_FLAG(repeat) );

        IUTEST_EXPECT_STREQ( "ansi", ::iutest::IUTEST_FLAG(color).c_str() );
        IUTEST_EXPECT_STREQ( "Flag*", ::iutest::IUTEST_FLAG(filter).c_str() );
        IUTEST_EXPECT_STREQ( "", ::iutest::IUTEST_FLAG(default_package_name).c_str() );

        if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;

        ::iutest::IUTEST_FLAG(repeat) = 1;
    }

    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_color=off");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());
        IUTEST_EXPECT_STREQ( "no", ::iutest::IUTEST_FLAG(color).c_str() );

        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_color=1");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());
        IUTEST_EXPECT_STREQ( "yes", ::iutest::IUTEST_FLAG(color).c_str() );

        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    {
        ::std::vector< ::std::string > vargv;
        vargv.push_back("--iutest_color=auto");
        ::iutest::InitIrisUnitTest(vargv);
        IUTEST_EXPECT_EQ(0u, vargv.size());
        IUTEST_EXPECT_STREQ( "auto", ::iutest::IUTEST_FLAG(color).c_str() );

        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
#endif
    printf("*** Successful ***\n");
    return 0;
}

