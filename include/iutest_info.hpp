//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_info.hpp
 * @brief       iris unit test info
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_INFO_HPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_
#define INCG_IRIS_IUTEST_INFO_HPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_body.hpp"
#include "internal/iutest_factory.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/**
 * @brief   テスト情報クラス
*/
class TestInfo
#if IUTEST_USE_OWN_LIST
    : public detail::iu_list_node<TestInfo>
#endif
{
public:
    /**
     * @brief   コンストラクタ
     * @param [in]  testsuite   = TestSuite 仲介者
     * @param [in]  name        = テスト名
     * @param [in]  factory     = テスト生成器
    */
    TestInfo(detail::iuITestSuiteMediator* testsuite, const ::std::string& name, detail::iuFactoryBase* factory)
        : m_testname(name)
        , m_factory(factory)
        , m_testsuite(testsuite)
        , m_should_run(true)
        , m_ran(false)
        , m_disable(detail::IsDisableTestName(name))
        , m_skip(false)
        , m_matches_filter(true)
    {
        m_mediator.SetPointer(this);
    }

public:
    /** test suite 名の取得 */
    const   char*   test_suite_name()    const { return m_testsuite->test_suite_name(); }
#if IUTEST_HAS_TESTCASE
    const   char*   test_case_name()    const { return m_testsuite->test_suite_name(); }
#endif
    /** test 名の取得 */
    const   char*   name()              const { return m_testname.c_str(); }
    /** should_run */
    bool            should_run()        const IUTEST_CXX_NOEXCEPT_SPEC { return m_should_run; }
    /** is ran */
    bool            is_ran()            const IUTEST_CXX_NOEXCEPT_SPEC { return m_ran; }
    /** disable */
    bool            is_disabled_test()  const IUTEST_CXX_NOEXCEPT_SPEC { return m_disable; }
    /** is skipped */
    bool            is_skipped()        const IUTEST_CXX_NOEXCEPT_SPEC { return m_skip || m_test_result.Skipped(); }
    /** is reportable */
    bool            is_reportable()     const IUTEST_CXX_NOEXCEPT_SPEC { return m_matches_filter; }
    /** テストの実行ミリ秒 */
    TimeInMillisec  elapsed_time()      const { return m_test_result.elapsed_time(); }
    /** テスト結果の取得 */
    const TestResult*   result()        const IUTEST_CXX_NOEXCEPT_SPEC { return &m_test_result; }

    /** value param 文字列の取得 */
    const   char*   value_param()       const { return m_value_param.empty() ? NULL : m_value_param.c_str(); }
    /** type param 文字列の取得 */
    const   char*   type_param()        const { return m_testsuite->type_param(); }

    /** default package 名を含む TestSuite 名の取得 */
    ::std::string testsuite_name_with_default_package_name() const
    {
        return TestEnv::AddDefaultPackageName(test_suite_name());
    }
public:
    /**
     * @brief   致命的なエラーが出たかどうか
     * @return  真偽値
    */
    bool    HasFatalFailure() const
    {
        return m_test_result.HasFatalFailure();
    }

    /**
     * @brief   致命的ではないエラーが出たかどうか
     * @return  真偽値
    */
    bool    HasNonfatalFailure() const
    {
        return m_test_result.HasNonfatalFailure();
    }

    /**
     * @brief   エラーが出たかどうか
     * @return  真偽値
    */
    bool    HasFailure() const
    {
        return m_test_result.Failed();
    }

    /**
     * @brief   警告があるかどうか
     * @return  真偽値
    */
    bool    HasWarning() const
    {
        return m_test_result.HasWarning();
    }

    /**
     * @brief   成功したかどうか
     * @return  真偽値
    */
    bool    Passed() const
    {
        if( is_skipped() )
        {
            return false;
        }
        return m_test_result.Passed();
    }

public:
    /** テストのフル名を取得 */
    ::std::string test_full_name() const
    {
        ::std::string fullname = test_suite_name();
        fullname += ".";
        fullname += name();
        return fullname;
    }

    /** テスト名 + where の取得 */
    ::std::string test_name_with_where() const
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
    /**
     * @brief   有効なプロパティ名かどうかチェック
     * @param [in] name = プロパティ名
     * @retval  true=有効
     * @retval  false=無効
    */
    static bool ValidateTestPropertyName(const ::std::string& name)
    {
        const char* ban[] = { "name", "status", "time", "classname", "type_param", "value_param" };
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
        return TestProperty::ValidateName(name, ban);
#else
        return TestProperty::ValidateName(name, ban, ban+IUTEST_PP_COUNTOF(ban));
#endif
    }
public:
    /** @private */
    void set_value_param(const char* str) { m_value_param = str; }

private:
    /**
     * @brief   実行
    */
    bool Run();

private:
    void RunImpl();

#if IUTEST_HAS_SEH && IUTEST_HAS_EXCEPTIONS
#if IUTEST_HAS_MINIDUMP
    void MiniDump(_EXCEPTION_POINTERS* ep);
#endif
    void RunOnMSC(Test* test);
#endif

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

    /**
    * @brief    テストのスキップ
    */
    void skip() { m_skip = true; }

private:
    class Mediator IUTEST_CXX_FINAL : public detail::iuITestInfoMediator
    {
    public:
        explicit Mediator(TestInfo* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : iuITestInfoMediator(p) {}
    public:
        virtual bool HasFatalFailure() const IUTEST_CXX_OVERRIDE
        {
            return ptr()->HasFatalFailure();
        }
        virtual bool HasNonfatalFailure() const IUTEST_CXX_OVERRIDE
        {
            return ptr()->HasNonfatalFailure();
        }
        virtual bool HasFailure() const IUTEST_CXX_OVERRIDE
        {
            return ptr()->HasFailure();
        }
        virtual bool IsSkipped() const IUTEST_CXX_OVERRIDE
        {
            return ptr()->is_skipped();
        }
    public:
        void SetPointer(TestInfo* p) { m_test_info = p; }
    };
private:
    friend class UnitTestImpl;
    friend class UnitTest;
    friend class TestSuite;
    friend class detail::UncaughtScopedTrace;

    ::std::string           m_testname;         //!< テスト名
    ::std::string           m_value_param;      //!< value param string
    TestResult              m_test_result;      //!< テスト結果
    Mediator                m_mediator;         //!< 自身の仲介インスタンス
    detail::iuFactoryBase*          m_factory;  //!< テスト生成器
    detail::iuITestSuiteMediator*   m_testsuite;//!< TestSuite 仲介者
    bool                    m_should_run;       //!< 実行すべきかの真偽値
    bool                    m_ran;              //!< 実行したかどうか
    bool                    m_disable;          //!< 無効真偽値
    bool                    m_skip;             //!< スキップしたかどうか
    bool                    m_matches_filter;   //!< フィルターにマッチしたかどうか

    typedef ::std::vector<detail::iuCodeMessage> UncaughtMessagesType;
    UncaughtMessagesType    m_uncaught_messages;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestInfo);
};

}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_info.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_INFO_HPP_764A79A8_E822_4C0F_8CB7_82C635BA28BA_
