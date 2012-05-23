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
	IUTEST_VC_TEST_CLASS(className), public IUTEST_TEST_CLASS_NAME_(testcase_, testname_) { \
	public: TEST_METHOD(methodName) { SetUp(); Body(); TearDown(); }										\
	TEST_CLASS_INITIALIZE(iuSetUp) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::SetUpTestCase(); }		\
	TEST_CLASS_CLEANUP(iuTearDown) { IUTEST_TEST_CLASS_NAME_(testcase_, testname_)::TearDownTestCase(); }	\
	virtual void	Body(void);				\
	};										\
	void className::Body() 


#define IUTEST_VC_TEST_CLASS(className)	\
	ONLY_USED_AT_NAMESPACE_SCOPE class className : public ::iuutil::VisualStudio::TestClass<className>

//======================================================================
// class
namespace iuutil {
namespace VisualStudio
{

template<typename T>
class TestClass : public ::Microsoft::VisualStudio::CppUnitTestFramework::TestClass<T>
{
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

inline void SetUpCppUnitTest(void)
{
	static VCCppUnitTestPartResultReporter fake;
}

}
}


#endif
