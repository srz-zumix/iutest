//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        tap_printer_listener_tests.cpp
 * @brief       TAPPrintListener test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/listener/iutest_tap_printer.hpp"
#include "logger_tests.hpp"

const char tap_test_str[] =
"# Foo started.\n"
"ok 1 - Ok\n"
"# Foo ended.\n"
"# Bar started.\n"
"ok 2 # SKIP - DISABLED_Ng\n"
"# Bar ended.\n"
"1..2\n";

IUTEST(Foo, Ok)
{
    IUTEST_SUCCEED() << "not show.";
}

IUTEST(Bar, DISABLED_Ng)
{
    IUTEST_FAIL() << "show failed.\n test.";
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

#if !defined(IUTEST_USE_GTEST)
    ::iutest::TAPPrintListener::SetUp();

    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
#endif

    {
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;

#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_STREQ(tap_test_str, logger.c_str());
        logger.clear();
#endif
        if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;
    }

    {
        ::iutest::IUTEST_FLAG(filter) = "*Hoge*";
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = false;
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
        IUTEST_EXPECT_STRIN("*Hoge*", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        logger.clear();
#endif
    }

    {
        ::iutest::IUTEST_FLAG(filter) = NULL;
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
        IUTEST_EXPECT_STRIN("not ok", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_EXPECT_STRIN("show failed., test.", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        logger.clear();
#endif
    }

    printf("*** Successful ***\n");
    return 0;
}
