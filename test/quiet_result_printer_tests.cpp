//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        quiet_result_printer_tests.cpp
 * @brief       QuietResultPrinter test
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
#include "logger_tests.hpp"

IUTEST(Test, Ok)
{
}

IUTEST(Test, NG)
{
    IUTEST_ASSERT_TRUE(false);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 実行対象テストがないので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

#if !defined(IUTEST_USE_GTEST)
    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
#endif

    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    ::iutest::TestEventListener* listener = ::iuutil::QuietResultPrinter::SetUp();
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_NOTNULL( listener ) << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_NULL( listeners.default_result_printer() ) << ::iutest::AssertionReturn<int>(1);
#else
    IUTEST_TERMINATE_ON_FAILURE(listener != NULL);
    IUTEST_TERMINATE_ON_FAILURE(listeners.default_result_printer() == NULL);
#endif

    if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_STRNOTIN("[       OK ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRIN   ("[  FAILED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif


    delete listeners.Release(listener);
    listener = ::iuutil::QuietResultPrinter::SetUp();
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_NULL( listener ) << ::iutest::AssertionReturn<int>(1);
#else
    if( listener != NULL ) return 1;
#endif

    printf("*** Successful ***\n");
    return 0;
}
