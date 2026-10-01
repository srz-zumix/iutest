//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_default_printer.ipp
 * @brief       iris unit test デフォルト出力イベントリスナー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_DEFAULT_PRINTER_IPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
#define INCG_IRIS_IUTEST_DEFAULT_PRINTER_IPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_

//======================================================================
// include
#include "../listener/iutest_default_printer.hpp"

namespace iutest
{
namespace detail
{

/**
 * @brief   単数形・複数形を切り替える
 * @param [in]  count       = 数
 * @param [in]  singular    = 単数形の表記
 * @param [in]  plural      = 複数形の表記
 * @return  count に応じた表記
*/
IUTEST_IPP_INLINE const char* FormatCountableNoun(int count, const char* singular, const char* plural)
{
    return count == 1 ? singular : plural;
}

}   // end of namespace detail

IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestProgramStart(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);
    // フィルタリング
    if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
    {
        detail::iuConsole::color_output(detail::iuConsole::yellow, "Note: iutest filter = %s\n", TestEnv::test_filter());
    }
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestIterationStart(const UnitTest& test
                                , int iteration)
{
    if( test.repeat_count() != 1 )
    {
        detail::iuConsole::output("\nRepeating all tests (iteration %d) . . .\n\n", iteration+1);
    }
    // シャッフルテスト
    if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
    {
        detail::iuConsole::color_output(detail::iuConsole::yellow, "Note: Randomizing tests' orders with a seed of %u\n", test.random_seed());
    }
    detail::iuConsole::color_output(detail::iuConsole::green, "[==========] ");
    {
        const int test_count = test.test_to_run_count();
        const int suite_count = test.test_suite_to_run_count();
        detail::iuConsole::output("Running %d %s from %d %s.\n"
            , test_count, detail::FormatCountableNoun(test_count, "test", "tests")
            , suite_count, detail::FormatCountableNoun(suite_count, "test suite", "test suites") );
    }
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnEnvironmentsSetUpStart(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);

    detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
    detail::iuConsole::output("Global test environment set-up.\n" );
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnEnvironmentsSetUpEnd(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestSuiteStart(const TestSuite& test_suite)
{
    detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
    const int count = test_suite.test_to_run_count();
    detail::iuConsole::output("%d %s from %s\n", count, detail::FormatCountableNoun(count, "test", "tests")
        , test_suite.testsuite_name_with_where().c_str() );
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestStart(const TestInfo& test_info)
{
    detail::iuConsole::color_output(detail::iuConsole::green, "[ RUN      ] ");
    detail::iuConsole::output("%s.%s\n", test_info.test_suite_name(), test_info.name());
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestPartResult(const TestPartResult& test_part_result)
{
    //if( test_part_result.type() == TestPartResult::kSuccess ) return;
    const std::string msg = test_part_result.make_newline_message();
#if defined(_MSC_VER) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    OutputDebugStringA(msg.c_str());
#endif
    detail::iuConsole::output("%s", msg.c_str());
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestRecordProperty(const TestProperty& test_property)
{
    detail::iuConsole::output("iutest record property:\n  %s=%s\n", test_property.key(), test_property.value());
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::PrintTestResult(const TestInfo& test_info) const
{
    if( test_info.HasFailure() )
    {
        detail::iuConsole::color_output(detail::iuConsole::red   , "[  FAILED  ] ");
        detail::iuConsole::output("%s.%s", test_info.test_suite_name(), test_info.test_name_with_where().c_str());
        return;
    }
    if( test_info.is_skipped() )
    {
        detail::iuConsole::color_output(detail::iuConsole::yellow, "[  SKIPPED ] ");
        detail::iuConsole::output("%s.%s", test_info.test_suite_name(), test_info.name());
        return;
    }
    detail::iuConsole::color_output(detail::iuConsole::green , "[       OK ] ");
    detail::iuConsole::output("%s.%s", test_info.test_suite_name(), test_info.name());
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestEnd(const TestInfo& test_info)
{
    PrintTestResult(test_info);
    if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
    {
#if defined(IUTEST_NOT_SUPPORT_STOPWATCH)
        detail::iuConsole::output(" (--ms)" );
#else
        detail::iuConsole::output(" (%sms)", detail::FormatTimeInMillisec(test_info.elapsed_time()).c_str());
#endif
    }
    detail::iuConsole::output("\n");
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestSuiteEnd(const TestSuite& test_suite)
{
    detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
    const int count = test_suite.test_to_run_count();
    detail::iuConsole::output("%d %s from %s", count, detail::FormatCountableNoun(count, "test", "tests")
        , test_suite.name() );
    if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
    {
#if defined(IUTEST_NOT_SUPPORT_STOPWATCH)
        detail::iuConsole::output(" (--ms total)");
#else
        detail::iuConsole::output(" (%sms total)", detail::FormatTimeInMillisec(test_suite.elapsed_time()).c_str());
#endif
    }
    detail::iuConsole::output("\n\n");
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnEnvironmentsTearDownStart(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);

    detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
    detail::iuConsole::output("Global test environment tear-down.\n" );
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnEnvironmentsTearDownEnd(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestIterationEnd(const UnitTest& test
                                , int iteration)
{
    IUTEST_UNUSED_VAR(iteration);

    detail::iuConsole::color_output(detail::iuConsole::green, "[==========] ");
    {
        const int test_count = test.test_to_run_count();
        const int suite_count = test.test_suite_to_run_count();
        detail::iuConsole::output("%d %s from %d %s ran."
            , test_count, detail::FormatCountableNoun(test_count, "test", "tests")
            , suite_count, detail::FormatCountableNoun(suite_count, "test suite", "test suites") );
    }
    if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
    {
#if defined(IUTEST_NOT_SUPPORT_STOPWATCH)
        detail::iuConsole::output(" (--ms total)");
#else
        detail::iuConsole::output(" (%sms total)", detail::FormatTimeInMillisec(test.elapsed_time()).c_str());
#endif
    }
    detail::iuConsole::output("\n");

    {
        {
            const int count = test.successful_test_count();
            detail::iuConsole::color_output(detail::iuConsole::green, "[  PASSED  ] ");
            detail::iuConsole::output("%d %s.\n", count, detail::FormatCountableNoun(count, "test", "tests") );
        }
        {
            const int count = test.reportable_disabled_test_count();
            if( !TestFlag::IsEnableFlag(TestFlag::RUN_DISABLED_TESTS) && count > 0 )
            {
                detail::iuConsole::color_output(detail::iuConsole::yellow, "[ DISABLED ] ");
                detail::iuConsole::output("%d %s.\n", count, detail::FormatCountableNoun(count, "test", "tests") );
                if( TestFlag::IsEnableFlag(TestFlag::VERBOSE) )
                {
                    for( int i=0, case_count=test.total_test_suite_count(); i < case_count; ++i )
                    {
                        const TestSuite* testsuite = test.GetTestSuite(i);
                        for( int j=0, info_count=testsuite->total_test_count(); j < info_count; ++j )
                        {
                            const TestInfo* testinfo = testsuite->GetTestInfo(j);
                            if( testinfo->is_disabled_test() )
                            {
                                detail::iuConsole::color_output(detail::iuConsole::yellow, "[ DISABLED ] ");
                                detail::iuConsole::output("%s.%s\n", testinfo->test_suite_name(), testinfo->name());
                            }
                        }
                    }
                }
            }
        }
        {
            const int count = test.reportable_test_run_skipped_count();
            if( count > 0 )
            {
                detail::iuConsole::color_output(detail::iuConsole::yellow, "[  SKIPPED ] ");
                detail::iuConsole::output("%d %s.\n", count, detail::FormatCountableNoun(count, "test", "tests") );
                if( TestFlag::IsEnableFlag(TestFlag::VERBOSE) )
                {
                    for( int i=0, case_count=test.total_test_suite_count(); i < case_count; ++i )
                    {
                        const TestSuite* testsuite = test.GetTestSuite(i);
                        for( int j=0, info_count=testsuite->total_test_count(); j < info_count; ++j )
                        {
                            const TestInfo* testinfo = testsuite->GetTestInfo(j);
                            if( testinfo->is_skipped() )
                            {
                                detail::iuConsole::color_output(detail::iuConsole::yellow, "[  SKIPPED ] ");
                                detail::iuConsole::output("%s.%s\n", testinfo->test_suite_name(), testinfo->name());
                            }
                        }
                    }
                }
            }
        }

        if( !test.Passed() )
        {
            const int failed_num = test.failed_test_count();
            detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
            detail::iuConsole::output("%d %s, listed below:\n", failed_num, detail::FormatCountableNoun(failed_num, "test", "tests") );

            for( int i=0, count=test.total_test_suite_count(); i < count; ++i )
            {
                const TestSuite* testsuite = test.GetTestSuite(i);
                for( int j=0, info_count=testsuite->total_test_count(); j < info_count; ++j )
                {
                    const TestInfo* testinfo = testsuite->GetTestInfo(j);
                    if( testinfo->HasFailure() )
                    {
                        detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
                        detail::iuConsole::output("%s.%s\n", testinfo->test_suite_name(), testinfo->name());
                    }
                }
                if( testsuite->ad_hoc_test_result()->Failed() )
                {
                    detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
                    detail::iuConsole::output("%s at SetUpTestSuite/TearDownTestSuite\n", testsuite->name());
                }
            }

            if( test.ad_hoc_test_result()->Failed() )
            {
                detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
                detail::iuConsole::output("other than\n");
            }
            detail::iuConsole::output("\n%d FAILED %s.\n", failed_num, detail::FormatCountableNoun(failed_num, "TEST", "TESTS") );
        }
    }
}
IUTEST_IPP_INLINE void DefaultResultPrintListener::OnTestProgramEnd(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_DEFAULT_PRINTER_IPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
