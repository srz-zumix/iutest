//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_package_tests1.cpp
 * @brief		iutest package test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_package_tests.hpp"

namespace pkg1
{
	IUTEST(Test, A)
	{
		IUTEST_EXPECT_PACKAGENAME(pkg1, Test);
	}
	
	IUTEST_F(PackageTestFixed, A)
	{
		IUTEST_EXPECT_PACKAGENAME(pkg1, PackageTestFixed);
	}
	
#if IUTEST_HAS_PARAM_METHOD_TEST
	IUTEST_PMZ(ParamMethodTest, A, TestFunction, 0, 0);
#endif
	
#if IUTEST_HAS_PARAM_TEST
	IUTEST_P(PackageParamTest, A)
	{
		const char* name = ::iutest::UnitTest::GetInstance()->current_test_case()->name();
		IUTEST_EXPECT_PACKAGENAME_(pkg1, PackageParamTest, ::iuutil::TestCaseNameRemoveInstantiateAndIndexName(name));
	}
	IUTEST_INSTANTIATE_TEST_CASE_P(A, PackageParamTest, ::iutest::Range<int>(0, 2));
#endif

#if IUTEST_HAS_TYPED_TEST
	IUTEST_TYPED_TEST(PackageTypedTest, A)
	{
		const char* name = ::iutest::UnitTest::GetInstance()->current_test_case()->name();
		IUTEST_EXPECT_PACKAGENAME_(pkg1, PackageTypedTest, ::iuutil::TestCaseNameRemoveIndexName(name));
	}
#endif

#if IUTEST_HAS_TYPED_TEST_P
	typedef ::iutest::Types<int, float> MyTypesA;
	IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(A, PackageTypeParamTest, MyTypesA);

#endif

}

IUTEST_PACKAGE(pkg2)
{
	IUTEST_PACKAGE(pkg3)
	{
		IUTEST_PACKAGE(pkg4)
		{
			IUTEST(Test, A)
			{
				IUTEST_EXPECT_PACKAGENAME(pkg2.pkg3.pkg4, Test);
			}
		}
	}
	IUTEST_PACKAGE(pkg2)
	{
		IUTEST(Test, A)
		{
			IUTEST_EXPECT_PACKAGENAME(pkg2.pkg2, Test);
		}
	}
}

