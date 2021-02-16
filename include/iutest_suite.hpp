//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_suite.hpp
 * @brief       iris unit test testsuite
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SUITE_HPP_0534E0BE_6BC4_4E99_80C0_56F441AD34ED_
#define INCG_IRIS_IUTEST_SUITE_HPP_0534E0BE_6BC4_4E99_80C0_56F441AD34ED_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_info.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/**
 * @brief   TestSuite
*/
class TestSuite
#if IUTEST_USE_OWN_LIST
    : public detail::iu_list_node<TestSuite>
#endif
{
protected:
    //! TestInfo リスト
#if IUTEST_USE_OWN_LIST
    typedef detail::iu_list<TestInfo>   iuTestInfos;
#else
    typedef ::std::vector<TestInfo*>    iuTestInfos;
#endif

protected:
    /**
     * @brief   コンストラクタ
     * @param [in]  testsuite_name  = TestSuite 名
     * @param [in]  id              = TestSuite ID
     * @param [in]  setup           = テスト事前実行関数
     * @param [in]  teardown        = テスト事後実行関数
    */
    TestSuite(const ::std::string& testsuite_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
    : m_testsuite_name(testsuite_name)
    , m_setup(setup)
    , m_teardown(teardown)
    , m_id(id)
    , m_disable_num(0)
    , m_should_run_num(0)
    , m_elapsedmsec(0)
    , m_start_timestamp(0)
    , m_disable(detail::IsDisableTestName(testsuite_name))
    {
    }

public:
    /**
     * @brief   デストラクタ
    */
    virtual ~TestSuite() {}

public:
    /** test suite 名の取得 */
    const char*     name()                  const { return m_testsuite_name.c_str(); }

    /** テスト総数 */
    int             total_test_count()      const IUTEST_CXX_NOEXCEPT_SPEC { return static_cast<int>(m_testinfos.size()); }
    /** レポート対象のテスト総数 */
    int             reportable_test_count() const;
    /** 実行したテスト総数 */
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
    /** 明示的にスキップされたテスト総数 */
    int             test_run_skipped_count() const;
    /** レポート対象の明示的にスキップされたテスト総数 */
    int             reportable_test_run_skipped_count() const;
    /** テストの実行ミリ秒 */
    TimeInMillisec  elapsed_time()          const IUTEST_CXX_NOEXCEPT_SPEC { return m_elapsedmsec; }
    /** テスト開始時刻 */
    TimeInMillisec  start_timestamp()       const IUTEST_CXX_NOEXCEPT_SPEC{ return m_start_timestamp; }

    /** TestInfo の取得 */
    const TestInfo* GetTestInfo(int index)  const { return m_testinfos[index]; }
    /** should_run */
    bool            should_run()            const IUTEST_CXX_NOEXCEPT_SPEC { return m_should_run_num != 0; }

    /** テストが成功したかどうか */
    bool            Passed()                const { return failed_test_count() == 0 && m_ad_hoc_testresult.Passed(); }
    /** テストが失敗したかどうか */
    bool            Failed()                const { return !Passed(); }

    /** type param 文字列の取得 */
    virtual const char* type_param()        const { return NULL; }

    /** TestSuite 名の取得 */
    ::std::string testsuite_name_with_where() const
    {
        ::std::string str = m_testsuite_name;
        if( type_param() != NULL )
        {
            str += ", where TypeParam = ";
            str += type_param();
        }
        return str;
    }

    /** default package 名を含む TestSuite 名の取得 */
    ::std::string testsuite_name_with_default_package_name() const
    {
        return TestEnv::AddDefaultPackageName(name());
    }

    /**
     * @brief   テスト実行中じゃないときのリザルトの取得
     * @deprecated
    */
    const TestResult* ad_hoc_testresult() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return ad_hoc_test_result();
    }

    /**
     * @brief   テスト実行中じゃないときのリザルトの取得
    */
    const TestResult* ad_hoc_test_result() const IUTEST_CXX_NOEXCEPT_SPEC
    {
        return &m_ad_hoc_testresult;
    }

public:
    /**
     * @brief   有効なプロパティ名かどうかチェック
     * @param [in] name = プロパティ名
     * @retval  true=有効
     * @retval  false=無効
    */
    static bool ValidateTestPropertyName(const ::std::string& name)
    {
        const char* ban[] = { "name", "tests", "failures", "disabled", "skip", "errors", "time" };
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
        return TestProperty::ValidateName(name, ban);
#else
        return TestProperty::ValidateName(name, ban, ban+IUTEST_PP_COUNTOF(ban));
#endif
    }

private:
    /**
     * @brief   テストの実行
     * @return  成否
    */
    bool Run();

    /**
     * @brief   実行
     * @return  成否
    */
    bool RunImpl();

private:
    /**
     * @brief   セットアップのスキップチェック
    */
    bool CheckSetUpSkipped();

public:
    /**
     * @private
     * @brief   TestSuite 比較用オブジェクト
    */
    struct FindOp
    {
        TestTypeId  m_id;
        const char* m_name;

        bool operator () (const TestSuite* p) const
        {
            if( p->get_typeid() == m_id && detail::IsStringEqual(p->m_testsuite_name, m_name) )
            {
                return true;
            }
            return false;
        }
    };
private:
    /**
     * @brief   テストのクリア
    */
    void clear();
    /*
     * @brief   テストのフィルタリング
     * @return  実行する場合は真
    */
    bool filter();

private:
    friend bool operator == (const TestSuite& lhs, const TestSuite& rhs)
    {
        return (lhs.m_id == rhs.m_id) && (strcmp(lhs.name(), rhs.name()) == 0);
    }

    void push_back(TestInfo* p) { m_testinfos.push_back(p); }

private:
    iuTestInfos::const_iterator begin() const       { return m_testinfos.begin(); }
    iuTestInfos::const_iterator end()   const       { return m_testinfos.end(); }
    TestTypeId                  get_typeid() const IUTEST_CXX_NOEXCEPT_SPEC { return m_id; }

private:
    bool HasWarning() const { return m_ad_hoc_testresult.HasWarning() || detail::AnyOverList(m_testinfos, &TestInfo::HasWarning); }

private:
    static bool IsSuccessfulTest(const TestInfo* p) { return p->is_ran() && p->Passed(); }
    static bool IsFailedTest(const TestInfo* p) { return p->should_run() && p->HasFailure(); }
    static bool IsSkipTest(const TestInfo* p) { return !p->is_ran() || p->is_skipped(); }
    static bool IsReportableSkipTest(const TestInfo* p) { return p->is_reportable() && IsSkipTest(p); }
    static bool IsRunSkippedTest(const TestInfo* p) { return p->should_run() && p->is_skipped(); }
    static bool IsReportableRunSkippedTest(const TestInfo* p) { return p->is_reportable() && IsRunSkippedTest(p); }
    static bool IsReportableDisabledTest(const TestInfo* p) { return p->is_reportable() && p->is_disabled_test(); }

private:
    friend class UnitTestImpl;
    friend class UnitTest;

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
    friend struct FindOp;
#endif

    ::std::string   m_testsuite_name;   //!< TestSuite 名
    iuTestInfos     m_testinfos;        //!< テスト情報リスト
    SetUpMethod     m_setup;            //!< SetUp 関数
    TearDownMethod  m_teardown;         //!< TearDown 関数
    TestTypeId      m_id;               //!< TypeID
    int             m_disable_num;      //!< 無視したテストの総数
    int             m_should_run_num;   //!< 実行すべきテストの総数
    TimeInMillisec  m_elapsedmsec;      //!< テスト時間
    TimeInMillisec  m_start_timestamp;  //!< テスト開始時刻
    bool            m_disable;          //!< 無効真偽値
    TestResult      m_ad_hoc_testresult;//!< テストが実行中でないときのリザルト

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestSuite);
};

/**
 * @brief   型つきTestSuite
*/
template<typename T>
class TypedTestSuite IUTEST_CXX_FINAL : public TestSuite
{
public:
    typedef T   TypeParam;  //!< 型

protected:
    /**
     * @brief   コンストラクタ
     * @param [in]  testsuite_name  = TestSuite 名
     * @param [in]  id              = TestSuite ID
     * @param [in]  setup           = テスト事前実行関数
     * @param [in]  teardown        = テスト事後実行関数
    */
    TypedTestSuite(const ::std::string& testsuite_name, TestTypeId id, SetUpMethod setup, TearDownMethod teardown)
        : TestSuite(testsuite_name, id, setup, teardown)
        , m_type_param(detail::GetTypeNameProxy<TypeParam>::GetTypeName())
    {
    }

public:
    /** type param 文字列の取得 */
    virtual const char* type_param() const IUTEST_CXX_OVERRIDE
    {
        return m_type_param.empty() ? NULL : m_type_param.c_str();
    }

private:
    friend class UnitTestImpl;

    ::std::string m_type_param;     //!< type param string
};

namespace detail
{

/**
 * @brief   TestSuite 仲介者
*/
class TestSuiteMediator IUTEST_CXX_FINAL : public detail::iuITestSuiteMediator
{
public:
    explicit TestSuiteMediator(TestSuite* p) IUTEST_CXX_NOEXCEPT_SPEC : iuITestSuiteMediator(p) {}
public:
    virtual const char* test_suite_name() const IUTEST_CXX_OVERRIDE { return m_test_suite->name(); }
    virtual const char* type_param()      const IUTEST_CXX_OVERRIDE { return m_test_suite->type_param(); }
};

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_suite.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_SUITE_HPP_0534E0BE_6BC4_4E99_80C0_56F441AD34ED_
