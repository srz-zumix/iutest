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
// include
namespace iuutil
{

//======================================================================
// function

/**
 * @brief   テスト名を取得
*/
inline ::std::string TestFullName(const ::iutest::TestInfo* test_info)
{
    ::std::string fullname = test_info->test_suite_name();
    fullname += ".";
    fullname += test_info->name();
    return fullname;
}

/**
 * @brief   インデックスを除いたテスト名を取得
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
*/
inline ::std::string TestSuiteNameRemoveIndexName(const char* name)
{
    return TestNameRemoveIndexName(name);
}

/**
 * @brief   インスタンス名とインデックスを除いた TestSuite 名を取得
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
*/
inline const ::iutest::TestSuite* FindTestSuite(const char* testsuite_name)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iutest::UnitTest::GetInstance()->total_test_suite_count();
    for( int i=0; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
        if( strcmp(testsuite->name(), testsuite_name) == 0 )
        {
            return testsuite;
        }
    }
    return NULL;
}

/**
 * @brief   TestSuite の検索
*/
inline const ::iutest::TestSuite* FindParamTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iutest::UnitTest::GetInstance()->total_test_suite_count();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
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
*/
inline const ::iutest::TestSuite* FindTypedTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iutest::UnitTest::GetInstance()->total_test_suite_count();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
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
*/
inline const ::iutest::TestSuite* FindParamTypedTestSuite(const char* testsuite_name, const ::iutest::TestSuite* begin=NULL)
{
    if( testsuite_name == NULL )
    {
        return NULL;
    }
    const int testsuite_count = ::iutest::UnitTest::GetInstance()->total_test_suite_count();
    int i=0;
    if( begin != NULL )
    {
        for( ; i < testsuite_count; ++i )
        {
            const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
            if( testsuite == begin )
            {
                break;
            }
        }
        ++i;
    }
    for( ; i < testsuite_count; ++i )
    {
        const ::iutest::TestSuite* testsuite = ::iutest::UnitTest::GetInstance()->GetTestSuite(i);
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
    return GetTestSuiteAdHocResult(::iutest::UnitTest::GetInstance()->current_test_suite());
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

#if !defined(IUTEST_REMOVE_LEGACY_TEST_CASEAPI_)

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
