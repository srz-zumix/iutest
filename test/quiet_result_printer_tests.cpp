//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        quiet_result_printer_tests.cpp
 * @brief       QuietResultPrinter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2022, Takazumi Shirayanagi\n
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
    IUTEST_ASSERT_TRUE(false) << "quiet printer failure marker";
}

#if !defined(IUTEST_USE_GTEST)
class TestEndCounter : public ::iutest::EmptyTestEventListener
{
public:
    TestEndCounter() : count(0) {}
    virtual void OnTestEnd(const ::iutest::TestInfo&) IUTEST_CXX_OVERRIDE { ++count; }
    int count;
};

static bool CheckOutput(TestLogger& logger, bool show_ok, bool show_progress)
{
    logger.clear();
    if( IUTEST_RUN_ALL_TESTS() == 0 ) return false;
    const char* output = logger.c_str();
    return (strstr(output, "[       OK ] Test.Ok") != NULL) == show_ok
        && (strstr(output, "[ RUN      ] Test.Ok") != NULL) == show_progress
        && (strstr(output, "[----------]") != NULL) == show_progress
        && strstr(output, "quiet printer failure marker") != NULL
        && strstr(output, "[  FAILED  ] Test.NG") != NULL
        && strstr(output, "[  PASSED  ] 1 test") != NULL;
}

static bool CheckQuietFlag(TestLogger& logger)
{
    const char* normal_argv[] = { "quiet_result_printer_tests", "--iutest_color=no" };
    int argc = 2;
    IUTEST_INIT(&argc, normal_argv);
    if( IUTEST_FLAG_GET(quiet_printer) || !CheckOutput(logger, true, true) ) return false;

    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    ::iutest::TestEventListener* const original = listeners.default_result_printer();
    ::iutest::TestEventListener* const xml = listeners.default_xml_generator();
    TestEndCounter* const counter = new TestEndCounter;
    listeners.Append(counter);
    const char* quiet_argv[] = { "quiet_result_printer_tests", "--iutest_quiet_printer", "remaining" };
    argc = 3;
    IUTEST_INIT(&argc, quiet_argv);
    bool ok = argc == 2 && strcmp(quiet_argv[1], "remaining") == 0 && IUTEST_FLAG_GET(quiet_printer)
        && CheckOutput(logger, false, true) && counter->count == 2
        && listeners.default_result_printer() == original && listeners.default_xml_generator() == xml;
    delete listeners.Release(counter);

    const char* off_argv[] = { "quiet_result_printer_tests", "--iutest_quiet_printer=no" };
    argc = 2;
    IUTEST_INIT(&argc, off_argv);
    ok = ok && argc == 1 && !IUTEST_FLAG_GET(quiet_printer) && CheckOutput(logger, true, true);

    IUTEST_FLAG_SET(quiet_printer, true);
    ok = ok && CheckOutput(logger, false, true);
    IUTEST_FLAG_SET(quiet_printer, false);
    return ok;
}
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(DISABLE_FALSE_POSITIVE_XML)
    // 実行対象テストがないので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

#if !defined(IUTEST_USE_GTEST)
    static TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
    if( !CheckQuietFlag(logger) ) return 1;
    logger.clear();
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

    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        return 1;
    }
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_STRNOTIN("[       OK ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
    IUTEST_ASSERT_STRIN   ("[  FAILED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif


    delete listeners.Release(listener);
    listener = ::iuutil::QuietResultPrinter::SetUp();
#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_NULL( listener ) << ::iutest::AssertionReturn<int>(1);
#else
    if( listener != NULL )
    {
        return 1;
    }
#endif

#if !defined(IUTEST_USE_GTEST)
    IUTEST_FLAG_SET(quiet_printer, true);
    logger.clear();
    if( IUTEST_RUN_ALL_TESTS() == 0 || *logger.c_str() != '\0' ) return 1;
    ::iutest::detail::iuConsole::SetLogger(NULL);
#endif

    printf("*** Successful ***\n");
    return 0;
}
