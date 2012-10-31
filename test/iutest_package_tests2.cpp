//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_package_tests2.cpp
 * @brief		iutest_package test
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

//======================================================================
// include
#include "../include/iutest.hpp"
#include "iutest_package_tests.hpp"

namespace pkg1
{
	IUTEST(Test, B)
	{
		IUTEST_EXPECT_PACKAGENAME(pkg1, Test);
	}
	
	IUTEST_F(TestFixed, B)
	{
		IUTEST_EXPECT_PACKAGENAME(pkg1, TestFixed);
	}
	
#if IUTEST_HAS_PARAM_METHOD_TEST
	IUTEST_PMZ(ParamMethodTest, B, TestFunction, 0, 0);
#endif
	
#if IUTEST_HAS_PARAM_TEST
	IUTEST_P(ParamTest, B)
	{
		const char* name = ::iutest::UnitTest::GetInstance()->current_test_case()->name();
		IUTEST_EXPECT_PACKAGENAME_(pkg1, ParamTest, ::iuutil::TestCaseNameRemoveInstantiateAndIndexName(name));
	}
	IUTEST_INSTANTIATE_TEST_CASE_P(B, ParamTest, ::iutest::Range<int>(0, 2));
#endif

#if IUTEST_HAS_TYPED_TEST
	IUTEST_TYPED_TEST(TypedTest, B)
	{
		const char* name = ::iutest::UnitTest::GetInstance()->current_test_case()->name();
		IUTEST_EXPECT_PACKAGENAME_(pkg1, TypedTest, ::iuutil::TestNameRemoveIndexName(name));
	}
#endif

#if IUTEST_HAS_TYPED_TEST_P
	typedef ::iutest::Types<int, float> MyTypesB;
	IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(B, TypeParamTest, MyTypesB);
#endif

}
