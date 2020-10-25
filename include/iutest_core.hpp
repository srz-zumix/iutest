//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_core.hpp
 * @brief       iris unit test core
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CORE_HPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
#define INCG_IRIS_IUTEST_CORE_HPP_33560431_783B_4AE7_8FC8_6E78355CAF87_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "internal/iutest_result_reporter.hpp"
#include "internal/iutest_file.hpp"
#include "internal/iutest_params_util.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/**
 * @brief   テスト全体の管理者
*/
class UnitTest : public UnitTestImpl
{
public:
    /** @private */
    static UnitTest& instance() { static UnitTest inst; return inst; }
    /**
     * @brief   UnitTest インスタンスの取得
    */
    static UnitTest* GetInstance() { return &instance(); }

public:
    /**
     * @brief   テスト中の TestSuite の取得
    */
    const TestSuite*     current_test_suite() const { return m_current_testsuite; }

    /**
     * @brief   テスト中の TestInfo の取得
     * @note    互換性のため メンバ関数 にしています。
    */
    const TestInfo*     current_test_info() const { return Test::GetCurrentTestInfo(); }

    /** 乱数シードの取得 */
    unsigned int        random_seed()       const { return TestEnv::current_random_seed(); }

    /** 現在何回目のくり返しか取得 */
    int                 repeat_counter()    const IUTEST_CXX_NOEXCEPT_SPEC { return m_repeat_counter; }

    /** リピート回数を取得 */
    int                 repeat_count()      const IUTEST_CXX_NOEXCEPT_SPEC { return TestEnv::get_repeat_count(); }

public:
    /** テスト総数 */
    int             total_test_count()      const IUTEST_CXX_NOEXCEPT_SPEC { return m_total_test_num; }
    /** レポート対象のテスト総数 */
    int             reportable_test_count() const;
    /** 実行した/するテスト総数 */
    int             test_to_run_count()     const IUTEST_CXX_NOEXCEPT_SPEC { return m_should_run_num; }
    /** 失敗テスト総数 */
    int             failed_test_count()     const;
    /** 無効テスト総数 */
    int             disabled_test_count()   const IUTEST_CXX_NOEXCEPT_SPEC { return m_disable_num; }
    /** レポート対象の無効テスト総数 */
    int             reportable_disabled_test_count() const;
    /** 成功テスト総数 */
    int             successful_test_count() const;
    /** スキップテスト総数 */
    int             skip_test_count()       const;
    /** レポート対象のスキップテスト総数 */
    int             reportable_skip_test_count() const;
    /** 明示的にスキップされたテスト総数 (SKIP, ASSUME) */
    int             test_run_skipped_count() const;
    /** レポート対象の明示的にスキップされたテスト総数 (SKIP, ASSUME) */
    int             reportable_test_run_skipped_count() const;

    /** TestSuite 数の総数 */
    int             total_test_suite_count() const { return static_cast<int>(m_testsuites.size()); }
    /** 実行した TestSuite 総数 */
    int             test_suite_to_run_count() const;
    /** 成功した TestSuite 総数 */
    int             successful_test_suite_count() const;
    /** 失敗した TestSuite 総数 */
    int             failed_test_suite_count() const;

    /**
     * @brief テスト実行中じゃないときのリザルトの取得
     * @deprecated
     */
    const TestResult* ad_hoc_testresult() const IUTEST_CXX_NOEXCEPT_SPEC { return ad_hoc_test_result(); }

    /** テスト実行中じゃないときのリザルトの取得 */
    const TestResult* ad_hoc_test_result() const IUTEST_CXX_NOEXCEPT_SPEC { return &m_ad_hoc_testresult; }

    /** テストの実行ミリ秒 */
    TimeInMillisec  elapsed_time()      const IUTEST_CXX_NOEXCEPT_SPEC { return m_elapsedmsec; }

    /** テスト開始時のタイムスタンプを取得 */
    TimeInMillisec  start_timestamp()   const IUTEST_CXX_NOEXCEPT_SPEC { return m_start_timestamp; }

    /** TestSuite の取得 */
    const TestSuite* GetTestSuite(int index)  const { return m_testsuites[index]; }

    /** テストが成功したかどうか */
    bool            Passed()            const;
    /** テストが失敗したかどうか */
    bool            Failed()            const { return !Passed(); }

    /** イベントリスナーの取得 */
    TestEventListeners& listeners()     const { return TestEnv::event_listeners(); }

#if IUTEST_HAS_TESTCASE
    const TestCase*     GetTestCase(int index)  const { return m_testsuites[index]; }
    const TestCase*     current_test_case() const { return m_current_testsuite; }
    int                 total_test_case_count() const { return static_cast<int>(m_testsuites.size()); }
    int                 test_case_to_run_count() const { return test_suite_to_run_count(); }
    int                 successful_test_case_count() const { return successful_test_suite_count(); }
    int                 failed_test_case_count() const { return failed_test_suite_count(); }
#endif

protected:
    /**
     * @brief   テストの実行
    */
    int Run();

private:
#if IUTEST_HAS_SEH && IUTEST_HAS_EXCEPTIONS
    int RunOnMSC();
#endif
    int RunImpl();

    /**
     * @brief   テストの実行（１ループ）
    */
    bool RunOnce();

private:
    /**
     * @brief   プログラムの開始
    */
    void TestProgramStart();

    /**
     * @brief   イテレーション毎のセットアップ
    */
    void SetUpTestIteration();

    /**
     * @brief   環境セットアップ
    */
    void EnvironmentSetUp();

    /**
     * @brief   環境解除
    */
    void EnvironmentTearDown();

    /**
     * @brief   プログラムの終了
    */
    void TestProgramEnd();

private:
    // C言語の終了コールバック関数
    static void OnExit()
    {
        instance().TestProgramEnd();
    }

private:
    UnitTest()
        : m_repeat_counter(0)
        , m_init_iutest_count(0)
        , m_test_started(false)
        , m_start_timestamp(0)
    {
        // デフォルトリポーターをセット
        TestEnv::SetGlobalTestPartResultReporter(&m_default_test_part_result_reporter);
        // 環境変数によるテストフラグ指定をロード
        TestEnv::LoadEnvironmentVariable();
    }
#if defined(_MSC_VER) && _MSC_VER < 1300
public: // VC++6.0 bug
#endif
    ~UnitTest()
    {
        TestEnv::ReleaseGlobalTestEnvironment();
        TestEnv::SetGlobalTestPartResultReporter(NULL);
    }

private:
    // 初期化処理
    void Initialize();

#if IUTEST_HAS_PARAM_TEST
public:
    /** @private */
    detail::ParamTestSuiteHolder& parameterized_test_registry() IUTEST_CXX_NOEXCEPT_SPEC
    {
        return m_param_testsuite_holder;
    }

private:
    detail::ParamTestSuiteHolder m_param_testsuite_holder;
#endif

private:
    friend class UnitTestSource;

    int m_repeat_counter;
    int m_init_iutest_count;
    bool m_test_started;
    TimeInMillisec m_start_timestamp;
    detail::DefaultGlobalTestPartResultReporter m_default_test_part_result_reporter;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(UnitTest);
};

namespace detail
{

/**
 * @private
 * @internal
 * @brief   単体テストインスタンス
*/
template<class Tester>
class TestInstance
{
public:
    /** コンストラクタ */
    TestInstance(const char* testsuite, const char* name, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown)
        : m_mediator(AddTestSuite(testsuite, id, setup, teardown))
        , m_info(&m_mediator, name, &m_factory)
    {
        UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
    }
    /** コンストラクタ */
    TestInstance(const ::std::string& testsuite, const char* name, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown)
        : m_mediator(AddTestSuite(testsuite, id, setup, teardown))
        , m_info(&m_mediator, name, &m_factory)
    {
        UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
    }
    /** コンストラクタ */
    TestInstance(const char* testsuite, const char* name, const char*  value_params, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown)
        : m_mediator(AddTestSuite(testsuite, id, setup, teardown))
        , m_info(&m_mediator, name, &m_factory)
    {
        m_info.set_value_param(value_params);
        UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
    }
    /** コンストラクタ */
    TestInstance(const ::std::string& testsuite, const char* name, const char*  value_params, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown)
        : m_mediator(AddTestSuite(testsuite, id, setup, teardown))
        , m_info(&m_mediator, name, &m_factory)
    {
        m_info.set_value_param(value_params);
        UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
    }

private:
    TestSuite* AddTestSuite(const char* testsuite, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
    {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
        return UnitTest::instance().AddTestSuite<TestSuite>(testsuite, id, setup, teardown);
#else
        return UnitTest::instance().AddTestSuite(testsuite, id, setup, teardown, detail::explicit_type<TestSuite>());
#endif
    }
    TestSuite* AddTestSuite(const ::std::string& testsuite, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
    {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
        return UnitTest::instance().AddTestSuite<TestSuite>(testsuite, id, setup, teardown);
#else
        return UnitTest::instance().AddTestSuite(testsuite, id, setup, teardown, detail::explicit_type<TestSuite>());
#endif
    }

private:
    TestSuiteMediator    m_mediator;
    TestInfo            m_info;
    iuFactory<Tester>   m_factory;
};

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_core.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_CORE_HPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
