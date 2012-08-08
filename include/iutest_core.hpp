//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_core.hpp
 * @brief		iris unit test core ファイル
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
#ifndef INCG_IRIS_iutest_core_HPP_33560431_783B_4ae7_8FC8_6E78355CAF87_
#define INCG_IRIS_iutest_core_HPP_33560431_783B_4ae7_8FC8_6E78355CAF87_

//======================================================================
// include
#include "internal/iutest_result_reporter.hpp"
#include "internal/iutest_params_util.hpp"
#include "internal/iutest_file.h"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	テスト全体の管理者
*/
class UnitTest : public UnitTestImpl
{
public:
	/** @private */
	static	UnitTest&	instance(void)		{ static UnitTest inst; return inst; }
	/** 
	 * @brief	UnitTest インスタンスの取得
	*/
	static	UnitTest*	GetInstance(void)	{ return &instance(); }

public:
	/**
	 * @brief	テスト中の TestCase の取得
	*/
	const TestCase*		current_test_case(void)		const	{ return m_current_testcase; }

	/**
	 * @brief	テスト中の TestInfo の取得
	 * @note	互換性のため メンバ関数 にしています。
	*/
	const TestInfo*		current_test_info(void)		const	{ return Test::GetCurrentTestInfo(); }

	/** 乱数シードの取得 */
	unsigned int		random_seed(void)			const	{ return TestEnv::current_random_seed(); }

	/** 現在何回目のくり返しか取得 */
	int					repeat_counter(void)		const	{ return m_repeat_counter; }

public:
	/** テスト総数 */
	int				total_test_count(void)		const	{ return m_total_test_num; }
	/** 実行した/するテスト総数 */
	int				test_to_run_count(void)		const	{ return m_should_run_num; }
	/** 失敗テスト総数 */
	int				failed_test_count(void)		const	{ return get_failed_test_count(); }
	/** 無効テスト総数 */
	int				disabled_test_count(void)	const	{ return m_disable_num; }
	/** 成功テスト総数 */
	int				successful_test_count(void)	const	{ return test_to_run_count() - failed_test_count(); }
	/** スキップテスト総数 */
	int				skip_test_count(void)		const	{ return total_test_count() - test_to_run_count(); }

	/** テストケース数の総数 */
	int				total_test_case_count(void)	const	{ return m_testcases.count(); }
	/** 実行したテストケース総数 */
	int				test_case_to_run_count(void)	const
	{
		int count=0;
		for( iuTestCases::iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !it->should_run() ) continue;
			++count;
		}
		return count;
	}
	/** 成功したテストケース総数 */
	int				successful_test_case_count(void)	const
	{
		int count=0;
		for( iuTestCases::iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !it->should_run() ) continue;
			if( it->failed_test_count() == 0 ) ++count;
		}
		return count;
	}
	/** 失敗したテストケース総数 */
	int				failed_test_case_count(void)	const
	{
		int count=0;
		for( iuTestCases::iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !it->should_run() ) continue;
			if( it->failed_test_count() > 0 ) ++count;
		}
		return count;
	}

	/** テストの実行ミリ秒 */
	TimeInMillisec	elapsed_time(void)		const	{ return m_elapsedmsec; }

	/** テストケースの取得 */
	const TestCase*	GetTestCase(int index)	const	{ return m_testcases[index]; }

	/** テストが成功したかどうか */
	bool			Passed(void)			const	{ return get_failed_test_count() == 0 && m_ad_hoc_testresult.Passed(); }
	/** テストが失敗したかどうか */
	bool			Failed(void)			const	{ return !Passed(); }

	/** イベントリスナーの取得 */
	TestEventListeners&	listeners(void)		const	{ return TestEnv::event_listeners(); }

protected:
	/**
	 * @brief	テストの実行
	*/
	int Run(void)
	{
		if( m_init_iutest_count == 0 )
		{
//#if IUTEST_HAS_PARAM_TEST
//			if( m_param_testcase_holder.count() )
//#endif
			{
				detail::iuConsole::output("This test program did NOT call ::iutest::InitIrisUnitTest before calling IUTEST_RUN_ALL_TESTS().  Please fix it.\n");
				return 1;
			}
		}

		if( !PreRunner() ) return 0;

		int ret = 1;
#if IUTEST_HAS_EXCEPTIONS
		if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_GLOBAL) )
		{
			try
			{
#if IUTEST_HAS_SEH
				ret = RunOnMSC();
#else
				ret = RunImpl();
#endif
			}
			catch( ... )
			{
			}
		}
		else
#endif
		{
			ret = RunImpl();
		}
		return ret;
	}
protected:
#if IUTEST_HAS_EXCEPTIONS && IUTEST_HAS_SEH
	int	RunOnMSC(void)
	{
		_EXCEPTION_POINTERS* info = NULL;
		int ret = 1;
		__try
		{
			ret = RunImpl();
		}
		__except (info = GetExceptionInformation()
			, detail::seh_exception::should_process_through_break_and_cppexceptions(GetExceptionCode()))
		{
			detail::seh_exception::translator(GetExceptionCode(), info);
		}
		return ret;
	}
#endif

private:
	int RunImpl(void)
	{
		m_repeat_counter = 0;
		int repeat = TestEnv::get_repeat_count();
		if( repeat == 0 ) return 0;

		TestProgramStart();

		bool result = true;
		while(repeat)
		{
			SetUpTestIteration();

			listeners().OnTestIterationStart(*this, m_repeat_counter);
			if( !RunOnce() )
			{
				result = false;
			}
			listeners().OnTestIterationEnd(*this, m_repeat_counter);

			++m_repeat_counter;
			if( repeat > 0 ) --repeat;
		}

		TestProgramEnd();

		return result ? 0 : 1;
	}

	/**
	 * @brief	プログラムの開始
	*/
	void	TestProgramStart(void)
	{
#if 0
#if IUTEST_HAS_EXCEPTIONS && defined(_MSC_VER) && IUTEST_HAS_SEH
		// /EHa オプションが必要
		if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION) )
		{
			// SEH 例外に対応する
			_set_se_translator(detail::seh_exception::translator);
		}
#endif
#endif

		// フィルタリング
		m_should_run_num = 0;
		m_disable_num = 0;
		for( iuTestCases::iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			it->filter();
			m_should_run_num += it->test_to_run_count();
			m_disable_num += it->disabled_test_count();
		}

		atexit(OnExit);

		listeners().OnTestProgramStart(*this);
	}

	/**
	 * @brief	イテレーション毎のセットアップ
	*/
	void	SetUpTestIteration(void)
	{
		TestEnv::SetUp();
	}

	/**
	 * @brief	環境セットアップ
	*/
	void	EnvironmentSetUp(void)
	{
		listeners().OnEnvironmentsSetUpStart(*this);
		for( iuEnvironmentList::iterator it = TestEnv::environments().begin(), end=TestEnv::environments().end(); it != end; ++it )
		{
			(*it)->SetUp();
		}
		listeners().OnEnvironmentsSetUpEnd(*this);
	}

	/**
	 * @brief	テストの実行（１ループ）
	*/
	bool	RunOnce(void)
	{
		m_elapsedmsec = 0;

		// 実行対象のテストがない場合は何もしない
		if( test_to_run_count() == 0 ) return Passed();

		// テスト結果のクリア
		for( iuTestCases::iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			it->clear();
		}

		// シャッフル
		if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
		{
			m_testcases.shuffle(TestEnv::genrand());
		}

		// グローバル環境セット
		EnvironmentSetUp();

		if( m_ad_hoc_testresult.HasFatalFailure() )
		{
			return false;
		}

		{
			detail::iuStopWatch sw;
			sw.start();
			for( iuTestCases::iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
			{
				if( !it->should_run() ) continue;

				m_current_testcase = *it;
				it->Run();
				m_current_testcase = NULL;
			}
			m_elapsedmsec = sw.stop();
		}

		// グローバル環境セット
		EnvironmentTearDown();

		return Passed();
	}

	/**
	 * @brief	環境解除
	*/
	void	EnvironmentTearDown(void)
	{
		listeners().OnEnvironmentsTearDownStart(*this);
		for( iuEnvironmentList::reverse_iterator it = TestEnv::environments().rbegin(), end=TestEnv::environments().rend(); it != end; ++it )
		{
			(*it)->TearDown();
		}
		listeners().OnEnvironmentsTearDownEnd(*this);
	}

	/**
	 * @brief	プログラムの終了
	*/
	void	TestProgramEnd(void)
	{
		static bool pass = false;
		if( pass ) return;
		listeners().OnTestProgramEnd(*this);
		pass = true;
	}

private:
	// C言語の終了コールバック関数
	static void	OnExit(void)
	{
		instance().TestProgramEnd();
	}

private:
	UnitTest(void)
		: m_repeat_counter(0)
		, m_init_iutest_count(0)
		, m_current_testcase(NULL)
	{
		// デフォルトリポーターをセット
		TestEnv::SetGlobalTestPartResultReporter(&m_default_test_part_result_reporter);
		// 環境変数によるテストフラグ指定をロード
		TestEnv::LoadEnviromentVariable();
	}
	~UnitTest(void)
	{
		TestEnv::ReleaseGlobalTestEnvironment();
		TestEnv::SetGlobalTestPartResultReporter(NULL);
	}

private:
	// 初期化処理
	void	Initialize(void)
	{
		m_init_iutest_count++;

		// ファイルシステムの初期化
		if( detail::IFileSystem::GetInstance() == NULL )
		{
#if defined(IUTEST_FILE)
			static FileSystem<IUTEST_FILE> filesystem;
			filesystem.Initialize();
#elif IUTEST_HAS_FOPEN
			static FileSystem<StdioFile> filesystem;
			filesystem.Initialize();
#endif
		}

		// 以降初回のみ
		if( m_init_iutest_count != 1 ) return;

#if IUTEST_HAS_PARAM_TEST
		m_param_testcase_holder.RegisterTests();
#endif
	}

	int get_failed_test_count(void) const
	{
		int count = 0;
		for( iuTestCases::iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
		{
			if( !it->should_run() ) continue;
			count += it->failed_test_count();
		}
		return count;
	}

#if IUTEST_HAS_PARAM_TEST
public:
	/** @private */
	ParamTestCaseHolder&	parameterized_test_registry(void)	{ return m_param_testcase_holder; }
private:
	ParamTestCaseHolder	m_param_testcase_holder;
#endif

private:
	friend class UnitTestSource;

	int m_repeat_counter;
	int m_init_iutest_count;
	const TestCase*	m_current_testcase;
	detail::DefaultGlobalTestPartResultReporter	m_default_test_part_result_reporter;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(UnitTest);
};

namespace detail
{

/**
 * @private
 * @internal
 * @brief	単体テストインスタンス
*/
template<class Tester>
class TestInstance
{
public:
	// コンストラクタ
	TestInstance(const char* testcase, const char* name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: m_mediator(UnitTest::instance().AddTestCase<TestCase>(testcase, id, setup, teardown))
		, m_info(&m_mediator, name, &m_factory)
	{
		UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
	}
	// コンストラクタ
	TestInstance(const char* testcase, const char* name, const char*  value_params, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
		: m_mediator(UnitTest::instance().AddTestCase<TestCase>(testcase, id, setup, teardown))
		, m_info(&m_mediator, name, &m_factory)
	{
		m_info.set_value_param(value_params);
		UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
	}

private:
	TestCaseMediator	m_mediator;
	TestInfo			m_info;
	iuFactory<Tester>	m_factory;
};

}	// end of namespace detail

}	// end of namespace iutest

#endif
