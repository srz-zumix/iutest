//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        compatibility_tests.cpp
 * @brief       compatibility test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(Compatibility, UnitTest)
{
    (void)::iutest::UnitTest::GetInstance()->disabled_test_count();
    (void)::iutest::UnitTest::GetInstance()->failed_test_count();
    (void)::iutest::UnitTest::GetInstance()->successful_test_count();
    (void)::iutest::UnitTest::GetInstance()->total_test_count();
    (void)::iutest::UnitTest::GetInstance()->test_to_run_count();

#if !defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
    (void)::iutest::UnitTest::GetInstance()->successful_test_case_count();
    (void)::iutest::UnitTest::GetInstance()->failed_test_case_count();
    (void)::iutest::UnitTest::GetInstance()->test_case_to_run_count();
    (void)::iutest::UnitTest::GetInstance()->current_test_case();
    (void)::iutest::UnitTest::GetInstance()->GetTestCase(0);
#endif

#if IUTEST_HAS_TESTSUITE
    (void)::iutest::UnitTest::GetInstance()->successful_test_suite_count();
    (void)::iutest::UnitTest::GetInstance()->failed_test_suite_count();
    (void)::iutest::UnitTest::GetInstance()->test_suite_to_run_count();
    (void)::iutest::UnitTest::GetInstance()->current_test_suite();
    (void)::iutest::UnitTest::GetInstance()->GetTestSuite(0);
#endif

    (void)::iutest::UnitTest::GetInstance()->Passed();
    (void)::iutest::UnitTest::GetInstance()->Failed();

    (void)::iutest::UnitTest::GetInstance()->current_test_info();

    (void)::iutest::UnitTest::GetInstance()->random_seed();
    (void)::iutest::UnitTest::GetInstance()->elapsed_time();

    (void)::iutest::UnitTest::GetInstance()->listeners();
}

#if !defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
IUTEST(Compatibility, TestCase)
{
    const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->current_test_case();
    IUTEST_ASSERT_NOTNULL(testcase);
    (void)testcase->disabled_test_count();
    (void)testcase->failed_test_count();
    (void)testcase->successful_test_count();
    (void)testcase->total_test_count();
    (void)testcase->test_to_run_count();

    (void)testcase->Passed();
    (void)testcase->Failed();

    (void)testcase->name();
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
    (void)testcase->type_param();
#endif
    (void)testcase->should_run();
    (void)testcase->elapsed_time();

    (void)testcase->GetTestInfo(0);
}
#endif

#if IUTEST_HAS_TESTSUITE

IUTEST(Compatibility, TestSuite)
{
    const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->current_test_suite();
    IUTEST_ASSERT_NOTNULL(testsuite);
    (void)testsuite->disabled_test_count();
    (void)testsuite->failed_test_count();
    (void)testsuite->successful_test_count();
    (void)testsuite->total_test_count();
    (void)testsuite->test_to_run_count();

    (void)testsuite->Passed();
    (void)testsuite->Failed();

    (void)testsuite->name();
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
    (void)testsuite->type_param();
#endif
    (void)testsuite->should_run();
    (void)testsuite->elapsed_time();

    (void)testsuite->GetTestInfo(0);
}

#endif

IUTEST(Compatibility, TestInfo)
{
    const ::iutest::TestInfo* testinfo = ::iutest::UnitTest::GetInstance()->current_test_info();
    IUTEST_ASSERT_NOTNULL(testinfo);

#if !defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
    (void)testinfo->test_case_name();
#endif
#if IUTEST_HAS_TESTSUITE
    (void)testinfo->test_suite_name();
#endif
    (void)testinfo->name();
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
    (void)testinfo->type_param();
    (void)testinfo->value_param();
#endif
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
    (void)testinfo->is_reportable();
#endif
    (void)testinfo->should_run();
    (void)testinfo->result();
}

IUTEST(Compatibility, TestResult)
{
    const ::iutest::TestInfo* testinfo = ::iutest::UnitTest::GetInstance()->current_test_info();
    IUTEST_ASSERT_NOTNULL(testinfo);
    const ::iutest::TestResult* result = testinfo->result();
    IUTEST_ASSERT_NOTNULL(result);

    (void)result->total_part_count();
    (void)result->test_property_count();
    (void)result->Passed();
    (void)result->Failed();
    (void)result->HasFatalFailure();
    (void)result->HasNonfatalFailure();
    (void)result->elapsed_time();

    (void)&::iutest::TestResult::GetTestPartResult;
    (void)&::iutest::TestResult::GetTestProperty;
}

IUTEST(Compatibility, TestPartResult)
{
    (void)&::iutest::TestPartResult::type;
    (void)&::iutest::TestPartResult::file_name;
    (void)&::iutest::TestPartResult::line_number;
    (void)&::iutest::TestPartResult::summary;
    (void)&::iutest::TestPartResult::message;
    (void)&::iutest::TestPartResult::passed;
    (void)&::iutest::TestPartResult::failed;
    (void)&::iutest::TestPartResult::nonfatally_failed;
    (void)&::iutest::TestPartResult::fatally_failed;
}

IUTEST(Compatibility, TestBody)
{
    HasFatalFailure();
    HasNonfatalFailure();
}
