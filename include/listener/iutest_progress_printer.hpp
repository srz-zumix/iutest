//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_progress_printer.hpp
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
#ifndef INCG_IRIS_iutest_progress_printer_HPP_D31CE626_EA82_4265_B2B6_50EC5C63CFB6_
#define INCG_IRIS_iutest_progress_printer_HPP_D31CE626_EA82_4265_B2B6_50EC5C63CFB6_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	プログレス出力イベントリスナー
*/
class ProgressPrintListener : public EmptyTestEventListener
{
public:
	ProgressPrintListener(void) : m_should_run_num(0), m_ran_num(0) {}
public:
	virtual void OnTestProgramStart(const UnitTest& test);
	virtual void OnTestIterationStart(const UnitTest& test
									, int iteration);
	virtual void OnTestEnd(const TestInfo& test_info);

private:
	int m_should_run_num;
	int m_ran_num;
};

inline void ProgressPrintListener::OnTestProgramStart(const UnitTest& test)
{
	IUTEST_UNUSED_VAR(test);

	detail::iuConsole::output("0%%   10   20   30   40   50   60   70   80   90   100%%\n");
	detail::iuConsole::output("|----|----|----|----|----|----|----|----|----|----|   \n");
}
inline void ProgressPrintListener::OnTestIterationStart(const UnitTest& test
								  , int iteration)
{
	IUTEST_UNUSED_VAR(iteration);

	m_should_run_num = test.test_to_run_count();
	m_ran_num = 0;
	detail::iuConsole::output("\r");
}
inline void ProgressPrintListener::OnTestEnd(const TestInfo& test_info)
{
	IUTEST_UNUSED_VAR(test_info);

	++m_ran_num;
	const int star_count = 51;
	const int n = (m_ran_num * star_count) / m_should_run_num;
	char progress[52] = "\r";
	for( int i=1; i < n+1; ++i ) progress[i] = '*';
	progress[n+1] = '\0';
	detail::iuConsole::output(progress);
}

//======================================================================
// function
//! ProgressPrintListener に切り替え
inline void SetUpProgressPrintListener(void)
{
	::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
	delete listeners.Release(listeners.default_result_printer());
	listeners.Append(new ProgressPrintListener);
}

}	// end of namespace iutest

#endif
