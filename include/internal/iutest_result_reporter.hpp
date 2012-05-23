//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_result_reporter.hpp
 * @brief		iris unit test TestPartResult リポーター ファイル
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
#ifndef INCG_IRIS_iutest_result_reporter_HPP_803FD1F7_1FD2_4d1e_9AFC_A5851284316F_
#define INCG_IRIS_iutest_result_reporter_HPP_803FD1F7_1FD2_4d1e_9AFC_A5851284316F_

//======================================================================
// include
#include "iutest_core_impl.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	デフォルト TestPartResult リポーター
*/
class DefaultGlobalTestPartResultReporter : public TestPartResultReporterInterface
{
public:
	virtual ~DefaultGlobalTestPartResultReporter(void) {}
	virtual void ReportTestPartResult(const TestPartResult& test_part_result)
	{
		UnitTestImpl::current_test_result()->AddTestPartResult(test_part_result);
		TestEnv::event_listeners().OnTestPartResult(test_part_result);
	}
};

/**
 * @brief	TestPartResult の情報収集ヘルパー
*/
class NewTestPartResultCheckHelper
{
public:
	template<TestPartResult::Type Type>
	struct CondEq
	{
		bool operator ()(const TestPartResult& result)
		{
			return result.type() == Type;
		}
	};

	template<TestPartResult::Type Type>
	struct CondNe
	{
		bool operator ()(const TestPartResult& result)
		{
			return result.type() != Type;
		}
	};
public:
	template<typename COND, typename REPORTER=DefaultGlobalTestPartResultReporter>
	class Reporter : public REPORTER
	{
		typedef REPORTER	_Mybase;
	public:
		Reporter(void)
			: m_origin(TestEnv::GetGlobalTestPartResultReporter())
			, m_count(0)
		{
			TestEnv::SetGlobalTestPartResultReporter(this);
		}
		virtual ~Reporter(void) 
		{
			TestEnv::SetGlobalTestPartResultReporter(m_origin);
		}
		virtual void ReportTestPartResult(const TestPartResult& result)
		{
			if( m_cond(result) )
			{
				++m_count;
			}
			_Mybase::ReportTestPartResult(result);
		}
	public:
		int	count(void)	{ return m_count; }
	private:
		TestPartResultReporterInterface*	m_origin;
		COND m_cond;
		int m_count;

		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(Reporter);
	};
};

}	// end of namespace detail
}	// end of namespace iutest

#endif
