//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_case.hpp
 * @brief		iris unit test testcase ファイル
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
#ifndef INCG_IRIS_iutest_case_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_
#define INCG_IRIS_iutest_case_HPP_F57C9B7E_7CAA_4429_BE75_FCAAEED1B220_

//======================================================================
// include
#include "iutest_info.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	テストケース
*/
class TestCase : public detail::iu_list_node<TestCase>
{
protected:
	typedef detail::iu_list<TestInfo>	iuTestInfos;	//!< TestInfo リスト
protected:
	/**
	 * @brief	コンストラクタ
	 * @param [in]	testcase_name	= テストケース名
	 * @param [in]	id				= テストケースID
	 * @param [in]	setup			= テスト事前実行関数
	 * @param [in]	teardown		= テスト事後実行関数
	*/
	TestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
	: m_testcase_name(testcase_name)
	, m_setup(setup), m_teardown(teardown)
	, m_id(id), m_disable_num(0)
	, m_should_run_num(0)
	, m_elapsedmsec(0)
	, m_disable(false)
	{
		if( strstr(testcase_name, "DISABLED_") == testcase_name )
		{
			m_disable = true;
		}
	}

public:
	/**
	 * @brief	デストラクタ
	*/
	virtual	~TestCase(void) {}

public:
	/**
	 * @brief	テストの実行
	 * @return	成否
	*/
	bool	Run(void)
	{
		if( !should_run() ) return true;

		if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
		{
			m_testinfos.shuffle(TestEnv::genrand());
		}

		// テスト開始
		TestEnv::event_listeners().OnTestCaseStart(*this);
		bool result = RunImpl();
		// テスト終了
		TestEnv::event_listeners().OnTestCaseEnd(*this);

		return result;
	}

public:
	/** test case 名の取得 */
	const	char*	name(void)					const	{ return m_testcase_name.c_str(); }
	
	/** テスト総数 */
	int				total_test_count(void)		const	{ return m_testinfos.count(); }
	/** 実行したテスト総数 */
	int				test_to_run_count(void)		const	{ return m_should_run_num; }
	/** 失敗テスト総数 */
	int				failed_test_count(void)		const	{ return get_failed_test_count(); }
	/** 無効テスト総数 */
	int				disabled_test_count(void)	const	{ return m_disable_num; }
	/** 成功テスト総数 */
	int				successful_test_count(void)	const	{ return test_to_run_count() - failed_test_count(); }
	/** スキップテスト総数 */
	int				skip_test_count(void)		const	{ return total_test_count() - test_to_run_count(); }
	/** テストの実行ミリ秒 */
	TimeInMillisec	elapsed_time(void)			const	{ return m_elapsedmsec; }

	/** TestInfo の取得 */
	const TestInfo*	GetTestInfo(int index)		const	{ return m_testinfos[index]; }
	/** should_run */
	bool			should_run(void)			const	{ return m_should_run_num != 0; }

	/** テストが成功したかどうか */
	bool			Passed(void)				const	{ return get_failed_test_count() == 0; }
	/** テストが失敗したかどうか */
	bool			Failed(void)				const	{ return !Passed(); }

	/** type param 文字列の取得 */
	virtual const char*	type_param(void)		const	{ return NULL; }

	/** TestCase 出力情報の取得 */
	std::string testcase_name_with_where(void) const
	{
		std::string str = m_testcase_name;
		if( type_param() != NULL )
		{
			str += ", where TypeParam = ";
			str += type_param();
		}
		return str;
	}

private:
	/**
	 * @brief	実行
	 * @return	成否
	*/
	bool RunImpl(void)
	{
		bool result=true;
		m_setup();
		m_elapsedmsec = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( it->should_run() )
			{
				// 実行
				if( !it->Run() )
				{
					result = false;
				}
				m_elapsedmsec += it->elapsed_time();
			}
		}
		m_teardown();
		return result;
	}

public:
	/**
	 * @private
	 * @brief	テストケース比較用オブジェクト
	*/
	struct FindOp
	{
		TestTypeId	m_id;
		const char*	m_name;

		bool operator () (const TestCase* p) const
		{
			if( p->get_typeid() == m_id && (strcmp(p->name(), m_name) == 0) )
			{
				return true;
			}
			return false;
		}
	};
private:
	/**
	 * @brief	テストのクリア
	*/
	void	clear(void)
	{
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			it->clear();
		}
	}

	/*
	 * @brief	テストのフィルタリング
	 * @return	実行する場合は真
	*/
	bool	filter(void)
	{
		m_should_run_num = 0;
		m_disable_num = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( m_disable )
			{
				// DISABLE の伝搬
				it->m_disable = true;
			}
			if( it->is_disabled_test() )
			{
				++m_disable_num;
			}
			if( it->filter() )
			{
				++m_should_run_num;
			}
		}
		return should_run();
	}

	/** 失敗テスト総数 */
	int get_failed_test_count(void) const
	{
		int count = 0;
		for( iuTestInfos::iterator it = m_testinfos.begin(), end=m_testinfos.end(); it != end; ++it )
		{
			if( it->should_run() && it->HasFailure() ) ++count;
		}
		return count;
	}

private:
	friend bool	operator == (const TestCase& lhs, const TestCase& rhs)
	{
		return (lhs.m_id == rhs.m_id) && (strcmp(lhs.name(), rhs.name()) == 0);
	}

	void	push_back(TestInfo* p)	{ m_testinfos.push_back(p); }

private:
	iuTestInfos::iterator	begin(void)	const		{ return m_testinfos.begin(); }
	iuTestInfos::iterator	end(void)	const		{ return m_testinfos.end(); }
	TestTypeId				get_typeid(void) const	{ return m_id; }

private:
	friend class UnitTestImpl;
	friend class UnitTest;

	std::string		m_testcase_name;	//!< テストケース名
	iuTestInfos		m_testinfos;		//!< テスト情報リスト
	SetUpMethod		m_setup;			//!< SetUp 関数
	TearDownMethod	m_teardown;			//!< TearDown 関数
	TestTypeId		m_id;				//!< TypeID
	int				m_disable_num;		//!< 無視したテストの総数
	int				m_should_run_num;	//!< 実行すべきテストの総数
	TimeInMillisec	m_elapsedmsec;		//!< テスト時間
	bool			m_disable;			//!< 無効真偽値

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestCase);
};

/**
 * @brief	型つきテストケース
*/
template<typename T>
class TypedTestCase : public TestCase
{
public:
	typedef T	TypeParam;	//!< 型

protected:
	/**
	 * @brief	コンストラクタ
	 * @param [in]	testcase_name	= テストケース名
	 * @param [in]	id				= テストケースID
	 * @param [in]	setup			= テスト事前実行関数
	 * @param [in]	teardown		= テスト事後実行関数
	*/
	TypedTestCase(const char* testcase_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: TestCase(testcase_name, id, setup, teardown)
#if IUTEST_HAS_RTTI
		, m_type_param(typeid(TypeParam).name())
#endif
	{}

public:
	/** type param 文字列の取得 */
	virtual const char*	type_param(void) const	{ return m_type_param.empty() ? NULL : m_type_param.c_str(); }

private:
	friend class UnitTestImpl;

	std::string	m_type_param;		//!< type param string
};

namespace detail
{

/**
 * @brief	テストケース仲介者
*/
class TestCaseMediator : public detail::iuITestCaseMediator
{
public:
	TestCaseMediator(TestCase* p) : iuITestCaseMediator(p) {}
public:
	virtual const char*	test_case_name(void) const { return m_test_case->name(); }
	virtual const char*	type_param(void) const	{ return m_test_case->type_param(); }
};

}	// end of namespace detail

}	// end of namespace iutest

#endif
