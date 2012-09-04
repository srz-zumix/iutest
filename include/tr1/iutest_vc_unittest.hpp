//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_vc_unittest.hpp
 * @brief		iris unit test, visual studio 11 C++ Unit Test Framework 対応 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_vc_unittest_HPP_5CA7C30C_2D2A_40a1_A9DE_83EAB4527787_
#define INCG_IRIS_iutest_vc_unittest_HPP_5CA7C30C_2D2A_40a1_A9DE_83EAB4527787_

//======================================================================
// include
#include "CppUnitTest.h"
#include "../../../include/util/iutest_util_tests.hpp"

//======================================================================
// define

#ifdef IUTEST
#  undef IUTEST
#endif
#define IUTEST(testcase_, testname_)	IUTEST_VCUNIT(testcase_, testname_, iutest::Test	\
											, iutest::internal::GetTestTypeId()				\
											, testcase_##testname_##_class, testcase_##_##testname_)

#ifdef IUTEST_F
#  undef IUTEST_F
#endif
#define IUTEST_F(testcase_, testname_)	IUTEST_VCUNIT(testcase_, testname_, testcase_	\
											, iutest::internal::GetTypeId<testcase_>()	\
											, testcase_##testname_##_class, testcase_##_##testname_)


#define IUTEST_VCUNIT(testcase_, testname_, parent_, type_id_, className, methodName)		\
	IUTEST_TEST_(testcase_, testname_, parent_, type_id_) {}								\
	IUTEST_VCUNIT_I(testcase_, testname_, className, methodName)

#define IUTEST_VCUNIT_I(testcase_, testname_, className, methodName)						\
	IUTEST_VC_TEST_CLASS(className), public IUTEST_TEST_CLASS_NAME_(testcase_, testname_) { \
	public: TEST_METHOD(methodName) { OnTestStart(#testcase_, #testname_); SetUp();			\
										Body(); TearDown(); OnTestEnd(#testcase_, #testname_); }			\
	TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::SetUpTestCase(); }		\
	TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::TearDownTestCase(); }	\
	virtual void	Body(void);				\
	};										\
	void className::Body() 

#ifdef IUTEST_P
#  undef IUTEST_P
#endif

IUTEST_MAKE_SCOPED_PEEP(::iutest::detail::iuFactoryBase* ::iutest::TestInfo::*, iutest, TestInfo, m_factory);

#define IUTEST_P(testcase_, testname_)														\
	class IUTEST_TEST_CLASS_NAME_(testcase_, testname_) : public testcase_ {				\
	public: IUTEST_TEST_CLASS_NAME_(testcase_, testname_)(void) {}							\
	protected: virtual void Body(void) {}													\
		IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testcase_, testname_));	\
	};																						\
	IUTEST_P_VCUNIT_I(testcase_, testname_, testcase_##testname_##_class, testcase_##_##testname_)

#define IUTEST_P_VCUNIT_I(testcase_, testname_, className, methodName)						\
	IUTEST_VC_TEST_CLASS(className), public IUTEST_TEST_CLASS_NAME_(testcase_, testname_) { \
	public: TEST_METHOD(methodName) {														\
		int testcase_count = ::iutest::UnitTest::GetInstance()->total_test_case_count();	\
		for( int i=0; i < testcase_count; ++i ) {											\
			const ::iutest::TestCase* testcase = ::iutest::UnitTest::GetInstance()->GetTestCase(i);	\
			::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testcase);	\
			const char* testcase_name = testcase->name();									\
			testcase_name = strchr(testcase_name, '/');										\
			if( testcase_name != NULL && strcmp(testcase_name, testcase_name) == 0 ) {		\
				::std::string name(#testname_);	name += "/";								\
				int testinfo_count = testcase->total_test_count();							\
				for( int i=0; i < testinfo_count; ++i ) {									\
					const ::iutest::TestInfo* testinfo = testcase->GetTestInfo(i);			\
					::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(testinfo);	\
					const char* testinfo_name = testinfo->name();							\
					if( strstr(testinfo_name, name.c_str()) == testinfo_name ) {			\
						::iutest::detail::iuParamTestFactory<className>* factory =			\
							(::iutest::detail::iuParamTestFactory<className>*)(				\
								IUTEST_PEEP_GET(*testinfo, TestInfo, m_factory));			\
						::Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(factory);	\
						SetParam(&factory->GetParam());										\
						OnTestStart(#testcase_, #testname_);								\
						SetUp(); Body(); TearDown();										\
						OnTestEnd(#testcase_, #testname_);									\
					}																		\
				}																			\
			}																				\
		}																					\
	}																						\
	TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::SetUpTestCase(); }		\
	TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::TearDownTestCase(); }	\
	virtual void	Body(void);																\
	private: static int	AddRegister(void) {													\
			static ::iutest::detail::ParamTestInstance< className > testinfo(#testname_);	\
			::iutest::UnitTest::GetInstance()->parameterized_test_registry().				\
			GetTestCasePatternHolder< testcase_ >(#testcase_)->AddTestPattern(&testinfo);	\
			return 0;																		\
		}																					\
		static int dummy_;																	\
	};																						\
	int className::dummy_ IUTEST_ATTRIBUTE_UNUSED_ = className::AddRegister();				\
	void className::Body() 


#define IUTEST_VC_TEST_CLASS(className)	\
	ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::iuutil::VisualStudio::TestClass<className>

//======================================================================
// class
namespace iuutil {
namespace VisualStudio
{

typedef void (::iutest::TestEventListeners::* OnTestStartEnd)(const ::iutest::TestInfo& test_info);

IUTEST_MAKE_SCOPED_PEEP(OnTestStartEnd, iutest, TestEventListeners, OnTestStart);
IUTEST_MAKE_SCOPED_PEEP(OnTestStartEnd, iutest, TestEventListeners, OnTestEnd);

template<typename T>
class TestClass : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<T>
{
	typedef ::Microsoft::VisualStudio::CppUnitTestFramework::Logger Logger;
public:
	void OnTestStart(const char* testcase_name, const char* testinfo_name)
	{
		const ::iutest::TestInfo* testinfo = iuutil::FindTestInfo(testcase_name, testinfo_name);
		if( testinfo == NULL ) return;
		IUTEST_PEEP_GET(::iutest::TestEnv::event_listeners(), TestEventListeners, OnTestStart)(*testinfo);
	}
	void OnTestEnd(const char* testcase_name, const char* testinfo_name)
	{
		const ::iutest::TestInfo* testinfo = iuutil::FindTestInfo(testcase_name, testinfo_name);
		if( testinfo == NULL ) return;
		IUTEST_PEEP_GET(::iutest::TestEnv::event_listeners(), TestEventListeners, OnTestEnd)(*testinfo);
	}
};

/**
 * @brief	Hook 用リポーター
*/
class VCCppUnitTestPartResultReporter : public iutest::EmptyTestEventListener
{
public:
	VCCppUnitTestPartResultReporter(void)
	{
		iutest::TestEventListeners& listeners = iutest::UnitTest::GetInstance()->listeners();
		listeners.Append(this);
	}
	virtual ~VCCppUnitTestPartResultReporter(void) 
	{
		iutest::TestEventListeners& listeners = iutest::UnitTest::GetInstance()->listeners();
		listeners.Release(this);
	}
	virtual void OnTestPartResult(const iutest::TestPartResult& result)
	{
		// VC にも送る
		if( result.failed() )
		{
			size_t size=0;
			wchar_t buf1[4096];	// TODO: Fixed buffer...
			wchar_t buf2[MAX_PATH];
			::mbstowcs_s(&size, buf1, sizeof(buf1)/sizeof(buf1[0]), result.message(), _TRUNCATE);
			::mbstowcs_s(&size, buf2, sizeof(buf2)/sizeof(buf2[0]), result.file_name(), _TRUNCATE);
			::Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail(buf1
				, &Microsoft::VisualStudio::CppUnitTestFramework::__LineInfo(buf2, "", result.line_number()) );
		}
	}
};

/**
 * @brief	Logger
*/
class VCCppUnitTestLogger : public ::iutest::detail::iuLogger
{
	typedef ::Microsoft::VisualStudio::CppUnitTestFramework::Logger	Logger;
public:
	virtual void voutput(const char* fmt, va_list va)
	{
		int length = _vscprintf(fmt, va);
		if( length <= 0 ) return;
		length += 1;
		char* buf = new char [length];
		vsprintf_s(buf, length, fmt, va);
		Logger::WriteMessage(buf);
		delete [] buf;
	}
};

inline void SetUpCppUnitTest(void)
{
	static VCCppUnitTestPartResultReporter fake;
	static VCCppUnitTestLogger logger;
	::iutest::detail::iuConsole::SetLogger(&logger);
	::iutest::UnitTestSource::GetInstance().Initialize();
}

}	// end of namespace VisualStudio
}	// end of namespace iuutil


#endif
