//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_case.ipp
 * @brief		iris unit test testcase ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_case_IPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_iutest_case_IPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "../iutest_case.hpp"

namespace iutest
{

IUTEST_IPP_INLINE bool	TestCase::Run(void)
{
	if( !should_run() ) return true;

	if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
	{
		RandomShuffle(m_testinfos, TestEnv::genrand());
	}

	// テスト開始
	TestEnv::event_listeners().OnTestCaseStart(*this);
	bool result = RunImpl();
	// テスト終了
	TestEnv::event_listeners().OnTestCaseEnd(*this);

	return result;
}

IUTEST_IPP_INLINE bool TestCase::RunImpl(void)
{
	bool result=true;
	m_elapsedmsec = 0;

	m_setup();
	{
		detail::iuStopWatch sw;
		sw.start();
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( (*it)->should_run() )
			{
				// 実行
				if( !(*it)->Run() )
				{
					result = false;
				}
			}
		}
		m_elapsedmsec = sw.stop();
	}
	m_teardown();
	return result;
}

IUTEST_IPP_INLINE void	TestCase::clear(void)
{
	for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		(*it)->clear();
	}
}

IUTEST_IPP_INLINE bool	TestCase::filter(void)
{
	m_should_run_num = 0;
	m_disable_num = 0;
	for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		if( m_disable )
		{
			// DISABLE の伝搬
			(*it)->m_disable = true;
		}
		if( (*it)->is_disabled_test() )
		{
			++m_disable_num;
		}
		if( (*it)->filter() )
		{
			++m_should_run_num;
		}
	}
	return should_run();
}

IUTEST_IPP_INLINE int TestCase::get_failed_test_count(void) const
{
	int count = 0;
	for( iuTestInfos::const_iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		if( (*it)->should_run() && (*it)->HasFailure() ) ++count;
	}
	return count;
}

IUTEST_IPP_INLINE int TestCase::get_skipped_test_count(void) const
{
	int count = 0;
	for( iuTestInfos::const_iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
	{
		if( (*it)->should_run() && (*it)->is_skipped() ) ++count;
	}
	return count;
}

}	// end of namespace iutest

#endif
