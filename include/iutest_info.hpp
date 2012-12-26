//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_info.hpp
 * @brief		iris unit test 情報 ファイル
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
#ifndef INCG_IRIS_iutest_info_HPP_764A79A8_E822_4c0f_8CB7_82C635BA28BA_
#define INCG_IRIS_iutest_info_HPP_764A79A8_E822_4c0f_8CB7_82C635BA28BA_

//======================================================================
// include
#include "iutest_body.hpp"
#include "internal/iutest_factory.hpp"
#include "internal/iutest_exception.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	テスト情報クラス
*/
class TestInfo 
	: public detail::iu_list_node<TestInfo>
{
private:
	class Mediator : public detail::iuITestInfoMediator
	{
	public:
		Mediator(TestInfo* p=NULL) : iuITestInfoMediator(p) {}
	public:
		virtual	bool	HasFatalFailure(void) const IUTEST_CXX_OVERRIDE
		{
			return ptr()->HasFatalFailure();
		}
		virtual	bool	HasNonfatalFailure(void) const IUTEST_CXX_OVERRIDE
		{
			return ptr()->HasNonfatalFailure();
		}
		virtual bool	HasFailure(void) const IUTEST_CXX_OVERRIDE
		{
			return ptr()->HasFailure();
		}
		virtual void	RecordProperty(const TestProperty& prop) IUTEST_CXX_OVERRIDE
		{
			return ptr()->RecordProperty(prop);
		}
	public:
		void SetPointer(TestInfo* p) { m_test_info = p; }
	};
public:
	/**
	 * @brief	コンストラクタ
	 * @param [in]	testcase	= テストケース仲介者
	 * @param [in]	name		= テスト名
	 * @param [in]	factory		= テスト生成器
	*/
	TestInfo(detail::iuITestCaseMediator* testcase, const char* name, detail::iuFactoryBase* factory)
		: m_testcase(testcase)
		, m_testname(name)
		, m_factory(factory)
		, m_should_run(true)
		, m_ran(false)
		, m_disable(false)
		, m_skip(false)
	{
		m_mediator.SetPointer(this);
		if( strstr(name, "DISABLED_") == name )
		{
			m_disable = true;
		}
	}

public:
	/** test case 名の取得 */
	const	char*	test_case_name(void)	const	{ return m_testcase->test_case_name(); }
	/** test 名の取得 */
	const	char*	name(void)				const	{ return m_testname.c_str(); }
	/** should_run */
	bool			should_run(void)		const	{ return m_should_run; }
	/** is ran */
	bool			is_ran(void)			const	{ return m_ran; }
	/** disable */
	bool			is_disabled_test(void)	const	{ return m_disable; }
	/** is skipped */
	bool			is_skipped(void)		const	{ return !m_should_run || m_skip; }
	/** テストの実行ミリ秒 */
	TimeInMillisec	elapsed_time(void)		const	{ return m_test_result.elapsed_time(); }
	/** テスト結果の取得 */
	const TestResult*	result(void)		const	{ return &m_test_result; }

	/** value param 文字列の取得 */
	const	char*	value_param(void)		const	{ return m_value_param.empty() ? NULL : m_value_param.c_str(); }
	/** type param 文字列の取得 */
	const	char*	type_param(void)		const	{ return m_testcase->type_param(); }

public:
	/**
	 * @brief	致命的なエラーが出たかどうか
	 * @return	真偽値
	*/
	bool	HasFatalFailure(void) const
	{
		return m_test_result.HasFatalFailure();
	}

	/**
	 * @brief	致命的ではないエラーが出たかどうか
	 * @return	真偽値
	*/
	bool	HasNonfatalFailure(void) const
	{
		return m_test_result.HasNonfatalFailure();
	}

	/**
	 * @brief	エラーが出たかどうか
	 * @return	真偽値
	*/
	bool	HasFailure(void) const
	{
		return m_test_result.Failed();
	}

public:
	/** テストのフル名を取得 */
	::std::string	test_full_name(void)		const
	{
		::std::string fullname = test_case_name();
		fullname += ".";
		fullname += name();
		return fullname;
	}

	/** テスト名 + where の取得 */
	::std::string test_name_with_where(void)	const
	{
		::std::string str = m_testname;
		if( value_param() != NULL )
		{
			str += ", where GetParam() = ";
			str += m_value_param;
		}
		return str;
	}

public:
	/** @private */
	void	set_value_param(const char* str)	{ m_value_param = str; }

private:
	/**
	 * @brief	実行
	*/
	bool	Run(void);

private:

	void	RunImpl(void);

#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
	void	RunOnMSC(detail::auto_ptr<Test>& test);
#endif

	void	RecordProperty(const TestProperty& prop)
	{
		m_test_result.RecordProperty(prop);
	}
private:
	/**
	 * @brief	テストのクリア
	*/
	void	clear(void);

	/*
	 * @brief	テストのフィルタリング
	 * @return	実行する場合は真
	*/
	bool	filter(void);

private:
	friend class UnitTestImpl;
	friend class UnitTest;
	friend class TestCase;

	detail::iuITestCaseMediator*	m_testcase;	//!< テストケース仲介者
	::std::string					m_testname;	//!< テスト名
	::std::string			m_value_param;		//!< value param string
	TestResult				m_test_result;		//!< テスト結果
	detail::iuFactoryBase*	m_factory;			//!< テスト生成器
	Mediator				m_mediator;			//!< 自身の仲介インスタンス
	bool					m_should_run;		//!< 実行すべきかの真偽値
	bool					m_ran;				//!< 実行したかどうか
	bool					m_disable;			//!< 無効真偽値
	bool					m_skip;				//!< スキップしたかどうか

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestInfo);
};

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_info.ipp"
#endif

#endif
