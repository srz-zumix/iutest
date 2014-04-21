//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_compatibility_tests.cpp
 * @brief		互換性 test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_switch.hpp"

IUTEST(Compatibility, UnitTest)
{
	(void)::iutest::UnitTest::GetInstance()->disabled_test_count();
	(void)::iutest::UnitTest::GetInstance()->failed_test_count();
	(void)::iutest::UnitTest::GetInstance()->successful_test_count();
	(void)::iutest::UnitTest::GetInstance()->total_test_count();
	(void)::iutest::UnitTest::GetInstance()->test_to_run_count();

	(void)::iutest::UnitTest::GetInstance()->successful_test_case_count();
	(void)::iutest::UnitTest::GetInstance()->failed_test_case_count();
	(void)::iutest::UnitTest::GetInstance()->test_case_to_run_count();

	(void)::iutest::UnitTest::GetInstance()->Passed();
	(void)::iutest::UnitTest::GetInstance()->Failed();

	(void)::iutest::UnitTest::GetInstance()->current_test_case();
	(void)::iutest::UnitTest::GetInstance()->current_test_info();

	(void)::iutest::UnitTest::GetInstance()->random_seed();
	(void)::iutest::UnitTest::GetInstance()->elapsed_time();

	(void)::iutest::UnitTest::GetInstance()->listeners();

	(void)::iutest::UnitTest::GetInstance()->GetTestCase(0);
}

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

IUTEST(Compatibility, TestInfo)
{
	const ::iutest::TestInfo* testinfo = ::iutest::UnitTest::GetInstance()->current_test_info();
	IUTEST_ASSERT_NOTNULL(testinfo);

	(void)testinfo->test_case_name();
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
