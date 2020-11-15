//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util_vc_unittest.hpp
 * @brief       iris unit test, visual studio 11 C++ Unit Test Framework 対応 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_VC_UNITTEST_HPP_5CA7C30C_2D2A_40A1_A9DE_83EAB4527787_
#define INCG_IRIS_IUTEST_UTIL_VC_UNITTEST_HPP_5CA7C30C_2D2A_40A1_A9DE_83EAB4527787_

//======================================================================
// include
#include <CppUnitTest.h>
#include "../../include/iutest_prod.hpp"
#include "../../include/util/iutest_util_tests.hpp"

//======================================================================
// define

#ifdef IUTEST_USE_GTEST

#ifdef IIUT_TEST_P_
#  undef IIUT_TEST_P_
#endif
#define IIUT_TEST_P_    TEST_P

#ifdef IIUT_TYPED_TEST_
#  undef IIUT_TYPED_TEST_
#endif
#define IIUT_TYPED_TEST_    TYPED_TEST

#ifdef IIUT_TYPED_TEST_P_
#  undef IIUT_TYPED_TEST_P_
#endif
#define IIUT_TYPED_TEST_P_  TYPED_TEST_P

#endif

/**
 * @private
 * @{
*/

#ifdef IUTEST
#  undef IUTEST
#endif
#define IUTEST(testsuite_, testname_)    \
    IUTEST_VCUNIT_I(testsuite_, testname_, testsuite_##testname_##_class, testsuite_##_##testname_);        \
    IUTEST_TEST(testsuite_, testname_)

#ifdef IUTEST_F
#  undef IUTEST_F
#endif
#define IUTEST_F(testfixture_, testname_)   \
    IUTEST_VCUNIT_I(testfixture_, testname_, testfixture_##testname_##_class, testfixture_##_##testname_);  \
    IUTEST_TEST_F_(testfixture_, testname_)

#ifdef IUTEST_P
#  undef IUTEST_P
#endif
#define IUTEST_P(testfixture_, testname_)   \
    IUTEST_VCUNIT_I(testfixture_, testname_, testfixture_##testname_##_class, testfixture_##_##testname_);  \
    IUTEST_TEST_P_(testfixture_, testname_)

#ifdef IUTEST_TYPED_TEST
#  undef IUTEST_TYPED_TEST
#endif
#define IUTEST_TYPED_TEST(testfixture_, testname_)  \
    IUTEST_VCUNIT_I(testfixture_, testname_, testfixture_##testname_##_class, testfixture_##_##testname_);  \
    IUTEST_TYPED_TEST_(testfixture_, testname_)

#ifdef IUTEST_TYPED_TEST_P
#  undef IUTEST_TYPED_TEST_P
#endif
#define IUTEST_TYPED_TEST_P(testfixture_, testname_)    \
    IUTEST_VCUNIT_I(testfixture_, testname_, testfixture_##testname_##_class, testfixture_##_##testname_);  \
    IIUT_TYPED_TEST_P_(testfixture_, testname_)


#define IUTEST_VCUNIT_I(testsuite_, testname_, className, methodName)   \
    IUTEST_VCUNIT_TEST_CLASS(className) {                               \
    public: TEST_METHOD(methodName) {                                   \
        IUTEST_VCUNIT_EXEC_(testsuite_, testname_); }                   \
        IIUT_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)            \
    }

/*
#define IUTEST_VCUNIT_F(testsuite_, testname_, className, methodName)   \
    IUTEST_VCUNIT_TEST_CLASS(className) {                               \
    public: TEST_METHOD(methodName) {                                   \
        IUTEST_VCUNIT_EXEC_(testsuite_, testname_); }                   \
        IIUT_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)            \
        TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_GET_SETUP_TESTSUITE(testsuite_, __FILE__, __LINE__)(); }      \
        TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_GET_TEARDOWN_TESTSUITE(testsuite_, __FILE__, __LINE__)(); }   \
    }
*/

#define IIUT_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)    \
    BEGIN_TEST_METHOD_ATTRIBUTE(methodName)                     \
        TEST_METHOD_ATTRIBUTE(L"TestSuite", L#testsuite_)       \
    END_TEST_METHOD_ATTRIBUTE()

#define IUTEST_VCUNIT_EXEC_(testsuite_, testname_)   \
    Body( "*" #testsuite_ "." #testname_ "*" )

#define IUTEST_VCUNIT_TEST_CLASS(className) \
    ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::iuutil::VisualStudio::TestClass<className>

//======================================================================
// class
namespace iuutil {
namespace VisualStudio
{

template<typename T>
class TestClass : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<T>
{
    typedef ::Microsoft::VisualStudio::CppUnitTestFramework::Logger Logger;
public:
    void Body(const char* filter)
    {
        SetUpCppUnitTest();
        ::iutest::IUTEST_FLAG(catch_exceptions) = false;
        ::iutest::IUTEST_FLAG(filter) = filter;
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
        IUTEST_RUN_ALL_TESTS();
    }
};

/**
 * @brief   Logger
*/
class VCCppUnitTestLogger : public ::iutest::detail::iuLogger
{
    typedef ::Microsoft::VisualStudio::CppUnitTestFramework::Logger Logger;
public:
    virtual void voutput(const char* fmt, va_list va)
    {
        int length = _vscprintf(fmt, va);
        if( length <= 0 )
        {
            return;
        }
        length += 1;
        char* buf = new char [length];
        vsprintf_s(buf, length, fmt, va);
        m_log += buf;
        delete [] buf;

        int pos = m_log.find('\n');
        while(pos >= 0) {
            Logger::WriteMessage(m_log.substr(0, pos).c_str());
            m_log = m_log.substr(pos+1);
            pos = m_log.find('\n');
        }
    }
private:
    ::std::string m_log;
};

/**
 * @brief   Hook 用リポーター
*/
class VCCppUnitTestPartResultReporter : public ::iutest::EmptyTestEventListener
{
public:
    VCCppUnitTestPartResultReporter()
    {
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        listeners.Append(this);
    }
    virtual ~VCCppUnitTestPartResultReporter()
    {
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        listeners.Release(this);
    }
    virtual void OnTestPartResult(const ::iutest::TestPartResult& result)
    {
        // VC にも送る
        if( result.failed() )
        {
            size_t size=0;
            wchar_t buf1[4096]; // TODO: Fixed buffer...
            wchar_t buf2[MAX_PATH];
            ::mbstowcs_s(&size, buf1, sizeof(buf1)/sizeof(buf1[0]), result.message(), _TRUNCATE);
            ::mbstowcs_s(&size, buf2, sizeof(buf2)/sizeof(buf2[0]), result.file_name(), _TRUNCATE);
            ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(buf1
                , &Microsoft::VisualStudio::CppUnitTestFramework::__LineInfo(buf2, "", result.line_number()) );
        }
    }
};

class VCCppUnitResultPrinter : public ::iutest::TestEventListener
{
public:
    explicit VCCppUnitResultPrinter(::iutest::TestEventListener* default_printer)
        : m_default_printer(default_printer)
    {}
    virtual ~VCCppUnitResultPrinter()
    {
        delete m_default_printer;
    }

public:
    virtual void OnTestProgramStart(const ::iutest::UnitTest& ) {}

    virtual void OnTestIterationStart(const ::iutest::UnitTest& , int ) {}

    virtual void OnEnvironmentsSetUpStart(const ::iutest::UnitTest& ) {}

    virtual void OnEnvironmentsSetUpEnd(const ::iutest::UnitTest& ) {}

    virtual void OnTestSuiteStart(const ::iutest::TestSuite& ) {}

    virtual void OnTestStart(const ::iutest::TestInfo& test_info)
    {
        m_default_printer->OnTestStart(test_info);
    }
    virtual void OnTestPartResult(const ::iutest::TestPartResult& test_part_result)
    {
        m_default_printer->OnTestPartResult(test_part_result);
    }
    virtual void OnTestEnd(const ::iutest::TestInfo& test_info)
    {
        m_default_printer->OnTestEnd(test_info);
    }

    virtual void OnTestSuiteEnd(const ::iutest::TestSuite& ) {}

    virtual void OnEnvironmentsTearDownStart(const ::iutest::UnitTest& ) {}

    virtual void OnEnvironmentsTearDownEnd(const ::iutest::UnitTest& ) {}

    virtual void OnTestIterationEnd(const ::iutest::UnitTest& , int iteration) {}

    virtual void OnTestProgramEnd(const ::iutest::UnitTest& ) {}
private:
    ::iutest::TestEventListener* m_default_printer;

public:
    /**
    * @brief    VCCppUnitResultPrinter に切り替え
    */
    static ::iutest::TestEventListener* SetUp()
    {
        static ::iutest::TestEventListener* p = NULL;
        if( p == NULL )
        {
            ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
            ::iutest::TestEventListener* default_printer = listeners.Release(listeners.default_result_printer());
            if( default_printer == NULL )
            {
                return NULL;
            }
            p = new VCCppUnitResultPrinter(default_printer);
            listeners.Append(p);
        }
        return p;
    }
};

inline void SetUpCppUnitTest()
{
    {
        static VCCppUnitTestPartResultReporter fake;
#ifndef IUTEST_USE_GTEST
        static VCCppUnitTestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
        ::iutest::UnitTestSource::GetInstance().Initialize();
#endif
        VCCppUnitResultPrinter::SetUp();
    }
}

}   // end of namespace VisualStudio
}   // end of namespace iuutil

/**
 * @}
*/


#endif  // INCG_IRIS_IUTEST_UTIL_VC_UNITTEST_HPP_5CA7C30C_2D2A_40A1_A9DE_83EAB4527787_
