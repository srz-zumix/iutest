//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_vc_unittest.hpp
 * @brief       iris unit test, visual studio 11 C++ Unit Test Framework 対応 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_VC_UNITTEST_HPP_5CA7C30C_2D2A_40A1_A9DE_83EAB4527787_
#define INCG_IRIS_IUTEST_VC_UNITTEST_HPP_5CA7C30C_2D2A_40A1_A9DE_83EAB4527787_


//======================================================================
// include
#include "CppUnitTest.h"
#include "../../include/iutest_prod.hpp"
#include "../../include/util/iutest_util_tests.hpp"

//======================================================================
// define

#ifdef IUTEST
#  undef IUTEST
#endif
#define IUTEST(testsuite_, testname_)    IUTEST_TR1_VCUNIT(testsuite_, testname_, iutest::Test    \
                                            , iutest::internal::GetTestTypeId()                 \
                                            , testsuite_##testname_##_class, testsuite_##_##testname_)

#ifdef IUTEST_F
#  undef IUTEST_F
#endif
#define IUTEST_F(testsuite_, testname_)  IUTEST_TR1_VCUNIT(testsuite_, testname_, testsuite_    \
                                            , iutest::internal::GetTypeId<testsuite_>()         \
                                            , testsuite_##testname_##_class, testsuite_##_##testname_)

#define IUTEST_TR1_VCUNIT_CHECK_DISABLED(testsuite_, testname_) \
    if( const char* p = #testsuite_)        \
        if(strstr(p, "DISABLED_") == p)     \
            return;                         \
    if( const char* p = #testname_ )        \
        if(strstr(p, "DISABLED_") == p)     \
            return

#define IUTEST_TR1_VCUNIT(testsuite_, testname_, parent_, type_id_, className, methodName)   \
    IUTEST_TEST_(testsuite_, testname_, parent_, type_id_) {}                                \
    IUTEST_TR1_VCUNIT_I(testsuite_, testname_, className, methodName)

#define IUTEST_TR1_VCUNIT_I(testsuite_, testname_, className, methodName)   \
    IUTEST_TR1_VCUNIT_TEST_CLASS(className), public IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) { \
    public: TEST_METHOD(methodName) {                                       \
        IUTEST_TR1_VCUNIT_CHECK_DISABLED(testsuite_, testname_);            \
        OnTestStart(#testsuite_, #testname_); SetUp();                      \
        Body(); TearDown(); OnTestEnd(#testsuite_, #testname_); }           \
    TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_GET_SETUP_TESTSUITE(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_), __FILE__, __LINE__)(); }    \
    TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_GET_TEARDOWN_TESTSUITE(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_), __FILE__, __LINE__)(); }  \
    IIUT_TR1_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName) \
    virtual void Body();                                    \
    };                                                      \
    void className::Body()

//#define IIUT_TR1_VCUNIT_PACKAGENAME_GETTER()      \
//  static constexpr wchar_t* GetPackageNameW() {   \
//      static const ::std::wstring ws = ::iutest::detail::MultiByteStringToWideString(IUTEST_GET_PACKAGENAME_().c_str()).c_str();  \
//      static wchar_t package_name[256];       \
//      wcscpy(package_name, ws.c_str());       \
//      return package_name;                    \
//  }
//
//  TEST_METHOD_ATTRIBUTE(L"Package", GetPackageNameW() )   \

#define IIUT_TR1_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)    \
    BEGIN_TEST_METHOD_ATTRIBUTE(methodName)                         \
        TEST_METHOD_ATTRIBUTE(L"TestSuite", L#testsuite_)           \
    END_TEST_METHOD_ATTRIBUTE()

#ifndef IUTEST_USE_GTEST

#ifdef IUTEST_P
#  undef IUTEST_P
#endif

IUTEST_MAKE_PEEP(::iutest::detail::iuFactoryBase* ::iutest::TestInfo::*, ::iutest::TestInfo, m_factory);

#define IUTEST_P(testsuite_, testname_)                                                     \
    class IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) : public testsuite_ {              \
    public: IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)() {}                             \
    protected: virtual void Body() {}                                                       \
        IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)); \
    };                                                                                      \
    IUTEST_P_VCUNIT_I(testsuite_, testname_, testsuite_##testname_##_class, testsuite_##_##testname_)

#define IUTEST_P_VCUNIT_I(testsuite_, testname_, className, methodName)                     \
    IUTEST_TR1_VCUNIT_TEST_CLASS(className), public IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) { \
    public: TEST_METHOD(methodName) {                                                       \
        IUTEST_TR1_VCUNIT_CHECK_DISABLED(testsuite_, testname_);                            \
        const ::iutest::TestSuite* testsuite = ::iuutil::FindParamTestSuite(#testsuite_);   \
        ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testsuite);      \
        while( testsuite != NULL ) {                                                        \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(testsuite);  \
            const char* testsuite_name = testsuite->name();                                 \
            ::std::string name(#testname_); name += "/";                                    \
            int testinfo_count = testsuite->total_test_count();                             \
            for( int i=0; i < testinfo_count; ++i ) {                                       \
                const ::iutest::TestInfo* testinfo = testsuite->GetTestInfo(i);             \
                ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testinfo);   \
                const char* testinfo_name = testinfo->name();                               \
                if( strstr(testinfo_name, name.c_str()) == testinfo_name ) {                \
                    ::iutest::detail::iuParamTestFactory<className>* factory =              \
                        static_cast< ::iutest::detail::iuParamTestFactory<className>*>(     \
                            IUTEST_PEEP_GET(*testinfo, ::iutest::TestInfo, m_factory));     \
                    ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(factory);    \
                    SetParam(&factory->GetParam());                                         \
                    OnTestStart(testsuite_name, testinfo_name);                             \
                    SetUp(); Body(); TearDown();                                            \
                    OnTestEnd(testsuite_name, testinfo_name);                               \
                }                                                                           \
            }                                                                               \
            testsuite = ::iuutil::FindParamTestSuite(#testsuite_, testsuite);               \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(NULL);   \
        }                                                                                   \
    }                                                                                       \
    TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_GET_SETUP_TESTSUITE(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_), __FILE__, __LINE__)(); }      \
    TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_GET_TEARDOWN_TESTSUITE(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_), __FILE__, __LINE__)(); }   \
    IIUT_TR1_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)                                \
    virtual void Body();                                                                    \
    private: static int AddRegister() {                                                     \
            static ::iutest::detail::ParamTestInstance< className > testinfo(#testname_);   \
            ::iutest::UnitTest::GetInstance()->parameterized_test_registry().               \
            GetTestSuitePatternHolder< testsuite_ >(#testsuite_, IUTEST_GET_PACKAGENAME_()) \
                ->AddTestPattern(&testinfo); return 0;                                      \
        }                                                                                   \
        static int dummy_;                                                                  \
    };                                                                                      \
    int className::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = className::AddRegister();              \
    void className::Body()


#if 1
#ifdef IUTEST_TYPED_TEST
#  undef IUTEST_TYPED_TEST
#endif

#define IUTEST_TYPED_TEST(testsuite_, testname_)                                         \
    IUTEST_TYPED_TEST_VCUNIT_I(testsuite_, testname_, testsuite_##testname_##_class, testsuite_##_##testname_);    \
    IIUT_TYPED_TEST_(testsuite_, testname_)

#define IUTEST_TYPED_TEST_VCUNIT_I(testsuite_, testname_, className, methodName)            \
    IUTEST_TR1_VCUNIT_TEST_CLASS(className) {                                               \
    public: TEST_METHOD(methodName) {                                                       \
        IUTEST_TR1_VCUNIT_CHECK_DISABLED(testsuite_, testname_);                            \
        const ::iutest::TestSuite* testsuite = ::iuutil::FindTypedTestSuite(#testsuite_);   \
        ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testsuite);      \
        while( testsuite != NULL ) {                                                        \
            const char* testsuite_name = testsuite->name();                                 \
            const ::iutest::TestInfo* testinfo = ::iuutil::FindTestInfo(testsuite, #testname_);  \
            ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testinfo);   \
            ::iutest::detail::iuFactoryBase* factory =                                      \
                IUTEST_PEEP_GET(*testinfo, ::iutest::TestInfo, m_factory);                  \
            ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(factory);    \
            ::iutest::detail::auto_ptr< ::iutest::Test > p = factory->Create();             \
            ::iuutil::tr1::VisualStudio::Test* tester = static_cast< ::iuutil::tr1::VisualStudio::Test*>(p.get());  \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(testsuite);    \
            OnTestStart(testsuite_name, #testname_);                                        \
            tester->SetUp(); tester->Body(); tester->TearDown();                            \
            OnTestEnd(testsuite_name, #testname_);                                          \
            testsuite = ::iuutil::FindTypedTestSuite(#testsuite_, testsuite);               \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(NULL);   \
        }                                                                                   \
    }                                                                                       \
    IIUT_TR1_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)                                \
    }

#endif

#if 1
#ifdef IUTEST_TYPED_TEST_P
#  undef IUTEST_TYPED_TEST_P
#endif

#define IUTEST_TYPED_TEST_P(testsuite_, testname_)       \
    IUTEST_TYPED_TEST_P_VCUNIT_I(testsuite_, testname_, testsuite_##testname_##_class, testsuite_##_##testname_);  \
    IIUT_TYPED_TEST_P_(testsuite_, testname_)

#define IUTEST_TYPED_TEST_P_VCUNIT_I(testsuite_, testname_, className, methodName)           \
    IUTEST_TR1_VCUNIT_TEST_CLASS(className) {                                               \
    public: TEST_METHOD(methodName) {                                                       \
        const ::iutest::TestSuite* testsuite = ::iuutil::FindParamTypedTestSuite(#testsuite_);  \
        ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testsuite);       \
        while( testsuite != NULL ) {                                                         \
        ::Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(#testsuite_);  \
            const char* testsuite_name = testsuite->name();                                   \
            const ::iutest::TestInfo* testinfo = ::iuutil::FindTestInfo(testsuite, #testname_);  \
            ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testinfo);   \
            ::iutest::detail::iuFactoryBase* factory =                                      \
                IUTEST_PEEP_GET(*testinfo, ::iutest::TestInfo, m_factory);                  \
            ::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(factory);    \
            ::iutest::detail::auto_ptr< ::iutest::Test > p = factory->Create();             \
            ::iuutil::tr1::VisualStudio::Test* tester = static_cast< ::iuutil::tr1::VisualStudio::Test*>(p.get());  \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(testsuite);    \
            OnTestStart(testsuite_name, #testname_);                                     \
            tester->SetUp(); tester->Body(); tester->TearDown();                        \
            OnTestEnd(testsuite_name, #testname_);                                       \
            testsuite = ::iuutil::FindParamTypedTestSuite(#testsuite_, testsuite);          \
            ::iuutil::tr1::VisualStudio::VCCppUnitTestAdapter::SetCurrentTestSuite(NULL);        \
        }                                                                               \
    }                                                                                   \
    IIUT_TR1_VCUNIT_METHOD_ATTRIBUTE(testsuite_, methodName)                             \
    }

#endif


#endif

#define IUTEST_TR1_VCUNIT_TEST_CLASS(className) \
    ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::iuutil::tr1::VisualStudio::TestClass<className>

//======================================================================
// class
namespace iuutil {
namespace tr1 {
namespace VisualStudio
{

#if IUTEST_HAS_PEEP_FUNC

typedef ::testing::TestEventListener* (::testing::TestEventListeners::* pfnRepeater)();

#define testing iutest
IUTEST_MAKE_PEEP(pfnRepeater, ::testing::TestEventListeners, repeater);
#undef testing

::testing::TestEventListener* GetTestEventListenerRepeater(::testing::TestEventListeners& listeners)
{
#define testing iutest
    return IUTEST_PEEP_GET(listeners, ::testing::TestEventListeners, repeater)();
#undef testing
}

#else

#if defined(IUTEST_USE_GTEST)
    IUTEST_MAKE_PEEP(::testing::internal::TestEventRepeater* testing::TestEventListeners::*, ::testing::TestEventListeners, repeater_);
#else
    IUTEST_MAKE_PEEP(::iutest::TestEventRepeater iutest::TestEventListeners::*, ::iutest::TestEventListeners, m_repeater);
#endif

::testing::TestEventListener* GetTestEventListenerRepeater(::testing::TestEventListeners& listeners)
{
#if defined(IUTEST_USE_GTEST)
    return reinterpret_cast< ::testing::TestEventListener* >( IUTEST_PEEP_GET(listeners, ::testing::TestEventListeners, repeater_) );
#else
    return &(IUTEST_PEEP_GET(listeners, ::iutest::TestEventListeners, m_repeater));
#endif
}

#endif

#ifndef IUTEST_USE_GTEST

class Test : public ::iutest::Test
{
public:
    using ::iutest::Test::SetUp;
    using ::iutest::Test::Body;
    using ::iutest::Test::TearDown;
};

#endif

template<typename T>
class TestClass : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<T>
{
    typedef ::Microsoft::VisualStudio::CppUnitTestFramework::Logger Logger;
public:
    void OnTestStart(const char* testsuite_name, const char* testinfo_name)
    {
        const ::iutest::TestInfo* testinfo = iuutil::FindTestInfo(testsuite_name, testinfo_name);
        if( testinfo == NULL )
        {
            return;
        }
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        ::iutest::TestEventListener* repeator = GetTestEventListenerRepeater(listeners);
        repeator->OnTestStart(*testinfo);
    }
    void OnTestEnd(const char* testsuite_name, const char* testinfo_name)
    {
        const ::iutest::TestInfo* testinfo = iuutil::FindTestInfo(testsuite_name, testinfo_name);
        if( testinfo == NULL )
        {
            return;
        }
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        ::iutest::TestEventListener* repeator = GetTestEventListenerRepeater(listeners);
        repeator->OnTestEnd(*testinfo);
    }
};

#ifndef IUTEST_USE_GTEST

IUTEST_MAKE_PEEP(::iutest::TestSuite* ::iutest::UnitTestImpl::*, ::iutest::UnitTest, m_current_testsuite);

#endif

class VCCppUnitTestAdapter
{
public:
    static void SetCurrentTestSuite(const ::iutest::TestSuite* testsuite)
    {
#ifndef IUTEST_USE_GTEST
        (IUTEST_PEEP_GET(*(::iutest::UnitTest::GetInstance())
            , ::iutest::UnitTest, m_current_testsuite)) = const_cast< ::iutest::TestSuite* >(testsuite);
#endif
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


inline void SetUpCppUnitTest()
{
    {
        static VCCppUnitTestPartResultReporter fake;
#ifndef IUTEST_USE_GTEST
        static VCCppUnitTestLogger logger;
        ::iutest::detail::iuConsole::SetLogger(&logger);
        ::iutest::UnitTestSource::GetInstance().Initialize();
#endif
    }
}

}   // end of namespace VisualStudio
}   // end of namespace tr1
}   // end of namespace iuutil


#endif
