//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_core_impl.hpp
 * @brief       iris unit test UnitTest core
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CORE_IMPL_HPP_D5ABC7DE_C751_4AC0_922F_547880163891_
#define INCG_IRIS_IUTEST_CORE_IMPL_HPP_D5ABC7DE_C751_4AC0_922F_547880163891_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_internal.hpp"
#include "iutest_option_message.hpp"
#include "../iutest_suite.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/** @private */
class UnitTestImpl
{
protected:
#if IUTEST_USE_OWN_LIST
    typedef detail::iu_list<TestSuite>  iuTestSuites;
#else
    typedef ::std::vector<TestSuite*>   iuTestSuites;
#endif
    typedef ::std::vector<Environment*> iuEnvironmentList;
protected:
    UnitTestImpl() : m_total_test_num(0), m_disable_num(0), m_should_run_num(0)
        , m_current_testsuite(NULL), m_elapsedmsec(0)
    {
        ptr() = this;
    }
    ~UnitTestImpl() { TerminateImpl(); }

public:
    /**
     * @brief   テスト中のテストの TestResult の取得
    */
    static TestResult* current_test_result();

public:
    /**
     * @brief   有効なプロパティ名かどうかチェック
     * @param [in] name = プロパティ名
     * @retval  true=有効
     * @retval  false=無効
    */
    static bool ValidateTestPropertyName(const ::std::string& name)
    {
        const char* ban[] = {
            "name", "tests", "failures", "disabled", "skip", "errors", "time", "timestamp", "random_seed"
        };
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
        return TestProperty::ValidateName(name, ban);
#else
        return TestProperty::ValidateName(name, ban, ban+IUTEST_PP_COUNTOF(ban));
#endif
    }

public:
    /** @private */
    template<typename T>
    TestSuite* AddTestSuite(const ::std::string& testsuite_name, TestTypeId id
        , SetUpMethod setup, TearDownMethod teardown IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T) )
    {
        TestSuite* p = FindTestSuite(testsuite_name, id);
        if( p == NULL )
        {
            p = new T (testsuite_name, id, setup, teardown);
            m_testsuites.push_back(p);
        }
        return p;
    }
    /** @private */
    void AddTestInfo(TestSuite* pCase, TestInfo* pInfo);
    /** @private */
    static bool SkipTest();

protected:
    /**
     * @brief   テストのリストアップ
    */
    int Listup() const;

    /**
     * @brief   テストのリストアップ(with where)
    */
    int ListupWithWhere() const;

    /**
     * @brief   事前処理
    */
    bool PreRunner();

    /**
     * @brief   テスト結果のクリア
    */
    void ClearNonAdHocTestResult();

    /**
     * @brief   ad_hoc_testresult のクリア
    */
    void ClearAdHocTestResult()
    {
        m_ad_hoc_testresult.Clear();
    }

private:
    /**
     * @brief   RecordProperty
    */
    static void RecordProperty(const TestProperty& prop);

    /**
     * @brief   FindTestSuite
    */
    TestSuite* FindTestSuite(const ::std::string& testsuite_name, TestTypeId id);

    /**
     * @brief   Do information options
    */
    bool DoInfoOptions();

private:
    /**
     * @brief   セットアップ
    */
    void InitializeImpl();
    /**
     * @brief   後片付け
    */
    void TerminateImpl();

private:
#if IUTEST_HAS_INVALID_PARAMETER_HANDLER

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

    // _invalid_parameter_handler
    IUTEST_ATTRIBUTE_NORETURN_ static void OnInvalidParameter(const wchar_t * expression, const wchar_t * function
        , const wchar_t * file, unsigned int line, uintptr_t pReserved);

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#endif

private:
    static UnitTestImpl*& ptr() IUTEST_CXX_NOEXCEPT_SPEC
    {
        static UnitTestImpl* ptr = NULL;
        return ptr;
    }
protected:
    friend class UnitTestSource;
    friend class Test::TestRecordPropertyHelper;

    int             m_total_test_num;   //!< 登録されたテスト総数
    int             m_disable_num;      //!< 無視したテスト総数
    int             m_should_run_num;   //!< 実行すべきテスト総数
    TestSuite*      m_current_testsuite;//!< 現在実行中の TestSuite
    TimeInMillisec  m_elapsedmsec;      //!< テストの実行時間
    iuTestSuites    m_testsuites;       //!< TestSuite リスト
    TestResult      m_ad_hoc_testresult;//!< テストが実行中でないときのリザルト
};

namespace detail
{

/**
 * @brief   テスト名の作成
 * @param [in]  index       = インデックス
*/
::std::string MakeIndexName(size_t index);

/**
 * @brief   テスト名の作成
 * @param [in]  basename    = ベース名
 * @param [in]  index       = インデックス
*/
::std::string MakeIndexTestName(const char* basename, size_t index);

/**
 * @brief   テスト名の作成
 * @param [in]  basename    = ベース名
 * @param [in]  parame_name = パラメータ名
*/
::std::string MakeParamTestName(const ::std::string& basename, const ::std::string& parame_name);

/**
 * @brief   テスト名の作成
 * @param [in]  basename    = ベース名
 * @param [in]  index       = インデックス
*/
template<typename T>
::std::string MakeIndexTypedTestName(const char* basename, size_t index)
{
#if IUTEST_HAS_RTTI
    ::std::string name = MakeIndexTestName(basename, index);
    name += "/";
    name += GetTypeNameProxy<T>::GetTypeNameProxy();
    return name;
#else
    return MakeIndexTestName(basename, index);
#endif
}

/**
 * @brief   テスト名の作成
 * @param [in]  prefix      = prefix
 * @param [in]  basename    = ベース名
 * @param [in]  index       = インデックス
*/
::std::string MakePrefixedIndexTestName(const char* prefix, const char* basename, size_t index);

/**
 * @brief   テスト名の作成
 * @param [in]  prefix      = prefix
 * @param [in]  basename    = ベース名
 * @param [in]  index       = インデックス
*/
template<typename T>
::std::string MakePrefixedIndexTypedTestName(const char* prefix, const char* basename, size_t index)
{
#if IUTEST_HAS_RTTI
    ::std::string name = prefix;
    if( !name.empty() )
    {
        name += "/";
    }
    name += MakeIndexTypedTestName<T>(basename, index);
    return name;
#else
    return MakePrefixedIndexTestName(prefix, basename, index);
#endif
}

}   // end of namespace detail

}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_core_impl.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_CORE_IMPL_HPP_D5ABC7DE_C751_4AC0_922F_547880163891_
