//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_default_printer.hpp
 * @brief		iris unit test デフォルト出力イベントリスナー ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_default_printer_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
#define INCG_IRIS_iutest_default_printer_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	デフォルト出力イベントリスナー
*/
class DefalutResultPrintListener : public TestEventListener
{
public:
	DefalutResultPrintListener(void) {}

	virtual ~DefalutResultPrintListener(void)
	{
		TestEnv::event_listeners().set_default_result_printer(NULL);
	}
public:
	virtual void OnTestProgramStart(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);
		// フィルタリング
		if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
		{
			detail::iuConsole::color_output(detail::iuConsole::yellow, "Note: iutest filter = %s\n", TestEnv::test_filter());
		}
	}
	virtual void OnTestIterationStart(const UnitTest& test
									, int iteration)
	{
		if( iteration > 0 )
		{
			detail::iuConsole::output("\nRepeating all tests (iteration %d) . . .\n\n", iteration);
		}
		// シャッフルテスト
		if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
		{
			detail::iuConsole::color_output(detail::iuConsole::yellow, "Note: Randomizing tests' orders with a seed of %d\n", test.random_seed());
		}
		detail::iuConsole::color_output(detail::iuConsole::green, "[==========] ");
		detail::iuConsole::output("Running %d tests from %d test cases.\n", test.test_to_run_count(), test.test_case_to_run_count() );
	}
	virtual void OnEnvironmentsSetUpStart(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);

		detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
		detail::iuConsole::output("Global test environment set-up.\n" );
	}
	virtual void OnEnvironmentsSetUpEnd(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);
	}
	virtual void OnTestCaseStart(const TestCase& test_case)
	{
		detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
		detail::iuConsole::output("%d tests from %s\n", test_case.test_to_run_count(), test_case.testcase_name_with_where().c_str() );
	}
	virtual void OnTestStart(const TestInfo& test_info)
	{
		detail::iuConsole::color_output(detail::iuConsole::green, "[ RUN      ] ");
		detail::iuConsole::output("%s.%s\n", test_info.test_case_name(), test_info.name());
	}
	virtual void OnTestPartResult(const TestPartResult& test_part_result)
	{
		//if( test_part_result.type() == TestPartResult::kSuccess ) return;
		detail::iuConsole::output(test_part_result.make_newline_message().c_str());
#ifdef _MSC_VER
#ifdef IUTEST_OS_WINDOWS_MOBILE
#else
		OutputDebugStringA(test_part_result.make_newline_message().c_str());
#endif
#endif
	}
	virtual void OnTestRecordProperty(const TestProperty& test_property)
	{
		detail::iuConsole::output("iutest record property:\n  %s=%s\n", test_property.key(), test_property.value());
	}
	virtual void OnTestEnd(const TestInfo& test_info)
	{
		if( test_info.HasFailure() )
		{
			detail::iuConsole::color_output(detail::iuConsole::red  , "[  FAILED  ] ");
			detail::iuConsole::output("%s.%s", test_info.test_case_name(), test_info.test_name_with_where().c_str());
		}
		else
		{
			detail::iuConsole::color_output(detail::iuConsole::green, "[       OK ] ");
			detail::iuConsole::output("%s.%s", test_info.test_case_name(), test_info.name());
		}
		if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
		{
#if defined(IUTEST_NOT_SUPPORT_STOPWATCH)
			detail::iuConsole::output(" (--ms)\n" );
#else
			detail::iuConsole::output(" (%dms)\n", test_info.elapsed_time());
#endif
		}
		else
		{
			detail::iuConsole::output("\n");
		}
	}
	virtual void OnTestCaseEnd(const TestCase& test_case)
	{
		detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
#if !defined(IUTEST_NOT_SUPPORT_STOPWATCH)
		if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
		{
			detail::iuConsole::output("%d tests from %s (%dms total)\n\n", test_case.test_to_run_count(), test_case.name(), test_case.elapsed_time() );
		}
		else
#endif
		{
			detail::iuConsole::output("%d tests from %s\n\n", test_case.test_to_run_count(), test_case.name() );
		}
	}
	virtual void OnEnvironmentsTearDownStart(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);

		detail::iuConsole::color_output(detail::iuConsole::green, "[----------] ");
		detail::iuConsole::output("Global test environment tear-down.\n" );
	}
	virtual void OnEnvironmentsTearDownEnd(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);
	}
	virtual void OnTestIterationEnd(const UnitTest& test
									, int iteration)
	{
		IUTEST_UNUSED_VAR(iteration);

		detail::iuConsole::color_output(detail::iuConsole::green, "[==========] ");
#if !defined(IUTEST_NOT_SUPPORT_STOPWATCH)
		if( TestFlag::IsEnableFlag(TestFlag::PRINT_TIME) )
		{
			detail::iuConsole::output("%d tests from %d testcase ran. (%dms total)\n", test.test_to_run_count(), test.test_case_to_run_count(), test.elapsed_time() );
		}
		else
#endif
		{
			detail::iuConsole::output("%d tests from %d testcase ran.\n", test.test_to_run_count(), test.test_case_to_run_count() );
		}

		{
			{
				detail::iuConsole::color_output(detail::iuConsole::green, "[  PASSED  ] ");
				detail::iuConsole::output("%d tests.\n", test.successful_test_count() );
			}
			if( !TestFlag::IsEnableFlag(TestFlag::RUN_DISABLED_TESTS) && test.disabled_test_count() > 0 )
			{
				detail::iuConsole::color_output(detail::iuConsole::yellow, "[ DISABLED ] ");
				detail::iuConsole::output("%d tests.\n", test.disabled_test_count() );
			}
			if( !test.Passed() )
			{
				int failed_num = test.failed_test_count();
				detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
				detail::iuConsole::output("%d %s, listed below:\n", failed_num, failed_num == 1 ? "test" : "tests" );

				for( int i=0, count=test.total_test_case_count(); i < count; ++i )
				{
					const TestCase* testcase = test.GetTestCase(i);
					for( int j=0, info_count=testcase->total_test_count(); j < info_count; ++j )
					{
						const TestInfo* testinfo = testcase->GetTestInfo(j);
						if( testinfo->HasFailure() )
						{
							detail::iuConsole::color_output(detail::iuConsole::red, "[  FAILED  ] ");
							detail::iuConsole::output("%s.%s\n", testinfo->test_case_name(), testinfo->name());
						}
					}
				}
				detail::iuConsole::output("\n%d FAILED %s.\n", failed_num, failed_num == 1 ? "TEST" : "TESTS" );
			}
		}
	}
	virtual void OnTestProgramEnd(const UnitTest& test)
	{
		IUTEST_UNUSED_VAR(test);
	}
};

}	// end of namespace iutest

#endif
