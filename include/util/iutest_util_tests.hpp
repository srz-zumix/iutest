//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util_tests.hpp
 * @brief       iris unit test テスト情報 utility ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_TESTS_HPP_4095FF9B_D6B8_4CD3_BF86_43DFED1760EA_
#define INCG_IRIS_IUTEST_UTIL_TESTS_HPP_4095FF9B_D6B8_4CD3_BF86_43DFED1760EA_

//======================================================================
// define
#if IUTEST_HAS_TESTSUITE
#  define IUTEST_CLASS_INITIALIZE(methodName)   static void SetUpTestSuite() { methodName(); } static void methodName()
#  define IUTEST_CLASS_CLEANUP(methodName)      static void TearDownTestSuite() { methodName(); } static void methodName()
#else
#  define IUTEST_CLASS_INITIALIZE(methodName)   static void SetUpTestCase() { methodName(); } static void methodName()
#  define IUTEST_CLASS_CLEANUP(methodName)      static void TearDownTestCase() { methodName(); } static void methodName()
#endif

#define IUTEST_METHOD_INITIALIZE(methodName)    virtual void SetUp() IUTEST_CXX_OVERRIDE { methodName(); } void methodName()
#define IUTEST_METHOD_CLEANUP(methodName)       virtual void TearDown() IUTEST_CXX_OVERRIDE { methodName(); } void methodName()

namespace iuutil
{

//======================================================================
// class

/// backward compatible for googletest old version
namespace backward
{

template<typename T>
class Test : public ::iutest::Test
{
public:
#if IUTEST_HAS_TESTSUITE
#if defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
    static void SetUpTestSuite()    { T::SetUpTestCase(); }
    static void TearDownTestSuite() { T::TearDownTestCase(); }
    static void SetUpTestCase()     {}
    static void TearDownTestCase()  {}
#endif
#else
    static void SetUpTestCase()     { T::SetUpTestSuite(); }
    static void TearDownTestCase()  { T::TearDownTestSuite(); }
    static void SetUpTestSuite()    {}
    static void TearDownTestSuite() {}
#endif
};

class TestEventListener : public ::iutest::TestEventListener
{
#if IUTEST_HAS_TESTSUITE
#if defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)
    virtual void OnTestSuiteStart(const ::iutest::TestSuite& test_suite) IUTEST_CXX_OVERRIDE { OnTestCaseStart(test_suite); }
    virtual void OnTestCaseStart(const ::iutest::TestSuite& /*test_suite*/) {}
    virtual void OnTestSuiteEnd(const ::iutest::TestSuite& test_suite) IUTEST_CXX_OVERRIDE   { OnTestCaseEnd(test_suite); }
    virtual void OnTestCaseEnd(const ::iutest::TestSuite& /*test_suite*/)   {}
#endif
#else
    virtual void OnTestSuiteStart(const ::iutest::TestCase& /*test_case*/) {}
    virtual void OnTestCaseStart(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE    { OnTestSuiteStart(test_case); }
    virtual void OnTestSuiteEnd(const ::iutest::TestCase& /*test_case*/)   {}
    virtual void OnTestCaseEnd(const ::iutest::TestCase& test_case) IUTEST_CXX_OVERRIDE      { OnTestSuiteEnd(test_case); }
#endif
};

}   // end of namespace backward

//======================================================================
// function

/**
 * @brief   Get TestSuite by index
 * @param   index = test suite index
*/
inline const ::iutest::TestSuite* GetTestSuite(int index)
{
#if IUTEST_HAS_TESTSUITE
    return ::iutest::UnitTest::GetInstance()->GetTestSuite(index);
#else
    return ::iutest::UnitTest::GetInstance()->GetTestCase(index);
#endif
}

/**
 * @brief   現在の TestSuite を取得
*/
inline const ::iutest::TestSuite* GetCurrentTestSuite()
{
#if IUTEST_HAS_TESTSUITE
    return ::iutest::UnitTest::GetInstance()->current_test_suite();
#else
    return ::iutest::UnitTest::GetInstance()->current_test_case();
#endif
}

/**
 * @brief   現在の TestSuite を取得
*/
inline const ::iutest::TestSuite* GetCurrentTestSuite(const ::iutest::UnitTest* unit_test)
{
#if IUTEST_HAS_TESTSUITE
    return unit_test->current_test_suite();
#else
    return unit_test->current_test_case();
#endif
}

/**
 * @brief   Get TestSuite Name
 * @param   test_info = test info
*/
inline const ::std::string GetTestSuiteName(const ::iutest::TestInfo* test_info)
{
#if IUTEST_HAS_TESTSUITE
    return test_info->test_suite_name();
#else
    return test_info->test_case_name();
#endif
}

/**
 * @brief   Get total TestSuite count
*/
inline int GetTotalTestSuiteCount()
{
#if IUTEST_HAS_TESTSUITE
    return ::iutest::UnitTest::GetInstance()->total_test_suite_count();
#else
    return ::iutest::UnitTest::GetInstance()->total_test_case_count();
#endif
}

/**
 * @brief   Get successful TestSuite count
*/
inline int GetSuccessfulTestSuiteCount()
{
#if IUTEST_HAS_TESTSUITE
    return ::iutest::UnitTest::GetInstance()->successful_test_suite_count();
#else
    return ::iutest::UnitTest::GetInstance()->successful_test_case_count();
#endif
}

/**
 * @brief   Get TestName
 * @param   test_info = test info
*/
inline ::std::string TestFullName(const ::iutest::TestInfo* test_info)
{
    ::std::string fullname = GetTestSuiteName(test_info);
    fullname += ".";
    fullname += test_info->name();
    return fullname;
}

/**
 * @brief   インデックスを除いたテスト名を取得
 * @param   name = test name
*/
inline ::std::string TestNameRemoveIndexName(const char* name)
{
    const char* const p = strrchr(name, '/');
    if( p == NULL )
    {
        return name;
    }
    return ::std::string(name, p);
}

/**
 * @brief   インデックスを除いた TestSuite 名を取得
 * @param   name = test name
*/
inline ::std::string TestSuiteNameRemoveIndexName(const char* name)
{
    return TestNameRemoveIndexName(name);
}

/**
 * @brief   インスタンス名とインデックスを除いた TestSuite 名を取得
 * @param   name = test name
*/
inline ::std::string TestSuiteNameRemoveInstantiateAndIndexName(const char* name)
{
    // パッケージ名があれば取得
    const char* const pkg = strrchr(name, '.');
    // 先頭にインスタンス名がある
    const char* const p1 = strchr(name, '/');
    if( p1 == NULL )
    {
        return name;
    }
    if( pkg == NULL )
    {
        return TestSuiteNameRemoveIndexName(p1 + 1);
    }
    else
    {
        return ::std::string(name, pkg + 1) + TestSuiteNameRemoveIndexName(p1 + 1);
    }
}

/**
 * @brief   TestSuite の検索
 * @param   testsuite_name = test suite name
*/
inline const ::iutest::TestSuite* FindTestSuite(const char* testsuite_name)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iuutil::GetTotalTestSuiteCount();
    for( int i=0; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
        if( strcmp(testsuite->name(), testsuite_name) == 0 )
        {
            return testsuite;
        }
    }
    return NULL;
}

/**
 * @brief   TestSuite の検索
 * @param   testsuite_name  = test suite name
 * @param   begin           = search begin
*/
inline const ::iutest::TestSuite* FindParamTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iuutil::GetTotalTestSuiteCount();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
        const char* testsuite_origin_name = strchr(testsuite->name(), '/');
        if( testsuite_origin_name != NULL )
        {
            if( strcmp(testsuite_origin_name+1, testsuite_name) == 0 )
            {
                return testsuite;
            }
        }
    }
    return NULL;
}

/**
 * @brief   Typed Test の TestSuite の検索
 * @param   testsuite_name  = test suite name
 * @param   begin           = search begin
*/
inline const ::iutest::TestSuite* FindTypedTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iuutil::GetTotalTestSuiteCount();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
        if( testsuite != NULL )
        {
            const char* name = testsuite->name();
            if( name != NULL
                && strstr(name, testsuite_name) == name
                && name[strlen(testsuite_name)] == '/' )
            {
                return testsuite;
            }
        }
    }
    return NULL;
}

/**
 * @brief   Type Parameter Test の TestSuite の検索
 * @param   testsuite_name  = test suite name
 * @param   begin           = search begin
*/
inline const ::iutest::TestSuite* FindParamTypedTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iuutil::GetTotalTestSuiteCount();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iuutil::GetTestSuite(i);
        const char* name = strchr(testsuite->name(), '/');
        if( name != NULL )
        {
            ++name;
            if( strstr(name, testsuite_name) == name
                && name[strlen(testsuite_name)] == '/' )
            {
                return testsuite;
            }
        }
    }
    return NULL;
}

/**
 * @brief   TestInfo の検索
*/
inline const ::iutest::TestInfo* FindTestInfo(const ::iutest::TestSuite* testsuite, const char* testinfo_name)
{
    if( testsuite == NULL || testinfo_name == NULL )
    {
        return NULL;
    }

    const int testinfo_count = testsuite->total_test_count();
    for( int i=0; i < testinfo_count; ++i )
    {
        const ::iutest::TestInfo* testinfo = testsuite->GetTestInfo(i);
        if( strcmp(testinfo->name(), testinfo_name) == 0 )
        {
            return testinfo;
        }
    }
    return NULL;
}

/**
 * @brief   TestInfo の検索
*/
inline const ::iutest::TestInfo* FindTestInfo(const char* testsuite_name, const char* testinfo_name)
{
    if( testsuite_name == NULL || testinfo_name == NULL )
    {
        return NULL;
    }
    const ::iutest::TestSuite* testsuite = FindTestSuite(testsuite_name);
    return FindTestInfo(testsuite, testinfo_name);
}

/**
 * @brief   TestInfo の検索
*/
inline const ::iutest::TestInfo* FindParamTestInfo(const ::iutest::TestSuite* testsuite, const char* testinfo_name
                                                    , const ::iutest::TestInfo* begin=NULL)
{
    if( testsuite == NULL || testinfo_name == NULL )
    {
        return NULL;
    }

    const int testinfo_count = testsuite->total_test_count();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testinfo_count; ++i )
        {
            const ::iutest::TestInfo* testinfo = testsuite->GetTestInfo(i);
            if( testinfo == begin )
            {
                break;
            }
        }
        ++i;
    }

    for( ; i < testinfo_count; ++i )
    {
        const ::iutest::TestInfo* testinfo = testsuite->GetTestInfo(i);
        if( testinfo != NULL )
        {
            const char* name = testinfo->name();
            if( name != NULL
                && strstr(name, testinfo_name) == name
                && name[strlen(testinfo_name)] == '/' )
            {
                return testinfo;
            }
        }
    }
    return NULL;
}

/**
 * @private
*/
inline const ::iutest::TestResult* TestResultPointer(const ::iutest::TestResult* result)
{
    return result;
}
/**
 * @private
*/
inline const ::iutest::TestResult* TestResultPointer(const ::iutest::TestResult& result)
{
    return &result;
}

/**
 * @brief   ad_hoc_test_result の取得
*/
inline const ::iutest::TestResult* GetAdHocTestResult()
{
#if !defined(IUTEST_NO_UNITEST_AD_HOC_TEST_RESULT_ACCESSOR)
    return TestResultPointer(::iutest::UnitTest::GetInstance()->ad_hoc_test_result());
#else
    return NULL;
#endif
}

/**
 * @brief   TestSuite の ad_hoc_test_result の取得
*/
inline const ::iutest::TestResult* GetTestSuiteAdHocResult(const ::iutest::TestSuite* test_suite)
{
#if !defined(IUTEST_NO_TESTCASE_AD_HOC_TEST_RESULT_ACCESSOR)
    return TestResultPointer(test_suite->ad_hoc_test_result());
#else
    IUTEST_UNUSED_VAR(test_suite);
    return GetAdHocTestResult();
#endif
}

/**
 * @brief   TestSuite の ad_hoc_test_result の取得
*/
inline const ::iutest::TestResult* GetCurrentTestSuiteAdHocResult()
{
    return GetTestSuiteAdHocResult(GetCurrentTestSuite());
}

/**
 * @brief   get test result
*/
inline const ::iutest::TestResult* GetTestResult(const ::iutest::TestInfo* test_info)
{
    return TestResultPointer(test_info->result());
}

/**
 * @brief   get test result
*/
inline const ::iutest::TestResult* GetCurrentTestResult()
{
    return GetTestResult(::iutest::UnitTest::GetInstance()->current_test_info());
}

#if IUTEST_HAS_TESTCASE

inline const ::iutest::TestCase* GetTestCase(int index) { return GetTestSuite(index); }
inline const ::iutest::TestCase* GetCurrentTestCase() { return GetCurrentTestSuite(); }
inline const ::iutest::TestCase* GetCurrentTestCase(const ::iutest::UnitTest* unit_test) { return GetCurrentTestSuite(unit_test); }
inline const ::std::string GetTestCaseName(const ::iutest::TestInfo* test_info) { return GetTestSuiteName(test_info); }
inline int GetSuccessfulTestCaseCount() { return GetSuccessfulTestSuiteCount(); }
inline int GetTotalTestCaseCount() { return GetTotalTestSuiteCount(); }

inline ::std::string TestCaseNameRemoveIndexName(const char* name) { return TestSuiteNameRemoveIndexName(name); }
inline ::std::string TestCaseNameRemoveInstantiateAndIndexName(const char* name) { return TestSuiteNameRemoveInstantiateAndIndexName(name); }
inline const ::iutest::TestCase* FindTestCase(const char* name) { return FindTestSuite(name); }

inline const ::iutest::TestCase* FindParamTestCase(const char* name, const ::iutest::TestCase* begin=NULL)
{
    return FindParamTestSuite(name, begin);
}
inline const ::iutest::TestCase* FindTypedTestCase(const char* name, const ::iutest::TestCase* begin=NULL)
{
    return FindTypedTestSuite(name, begin);
}
inline const ::iutest::TestCase* FindParamTypedTestCase(const char* name, const ::iutest::TestCase* begin=NULL)
{
    return FindParamTypedTestSuite(name, begin);
}
inline const ::iutest::TestResult* GetTestCaseAdHocResult(const ::iutest::TestCase* testcase)
{
    return GetTestSuiteAdHocResult(testcase);
}
inline const ::iutest::TestResult* GetCurrentTestCaseAdHocResult()
{
    return GetCurrentTestSuiteAdHocResult();
}

#endif

}   // end of namespace iuutil

#endif // INCG_IRIS_IUTEST_UTIL_TESTS_HPP_4095FF9B_D6B8_4CD3_BF86_43DFED1760EA_
