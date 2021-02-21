//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        default_printer_listener_tests.cpp
 * @brief       default printer test
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

TestLogger logger;
static ::std::string s_log_testcases;

class LoggerClear IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE
    {
        logger.clear();
    }
    virtual void TearDown(void) IUTEST_CXX_OVERRIDE
    {
        s_log_testcases = logger.c_str();
        logger.clear();
    }
};

IUTEST(Test, Ok)
{
}

IUTEST(Test, NG)
{
    IUTEST_ASSERT_TRUE(false);
}

IUTEST(Test, Skip)
{
    IUTEST_SKIP();
}

IUTEST(DISABLED_Test, NotRun)
{
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

    ::iutest::AddGlobalTestEnvironment(new LoggerClear());
    ::iutest::detail::iuConsole::SetLogger(&logger);

    ::iutest::IUTEST_FLAG(color) = "no";

    {
        ::iutest::IUTEST_FLAG(verbose) = false;
        ::iutest::IUTEST_FLAG(print_time) = true;

        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN("[ DISABLED ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  SKIPPED ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  PASSED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  FAILED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRNOTIN("[ DISABLED ] DISABLED_Test.NotRun", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRNOTIN("[  SKIPPED ] Test.Skip", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRNOTIN("[       OK ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRIN("ms total)", s_log_testcases.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("ms)", s_log_testcases.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
    }
    {
        ::iutest::IUTEST_FLAG(verbose) = true;
        ::iutest::IUTEST_FLAG(print_time) = false;

        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN("[ DISABLED ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  SKIPPED ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  PASSED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  FAILED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRIN("[ DISABLED ] DISABLED_Test.NotRun", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRIN("[  SKIPPED ] Test.Skip", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRNOTIN("[       OK ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);

        IUTEST_ASSERT_STRNOTIN("ms total)", s_log_testcases.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_STRNOTIN("ms)", s_log_testcases.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
    }

    printf("*** Successful ***\n");

    return 0;
}
