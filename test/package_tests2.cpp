//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        package_tests2.cpp
 * @brief       package test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "package_tests.hpp"

IUTEST_PACKAGE(pkg1)
{
    IUTEST(Test, B)
    {
        IUTEST_EXPECT_PACKAGENAME(pkg1, Test);
    }

    IUTEST_F(PackageTestFixed, B)
    {
        IUTEST_EXPECT_PACKAGENAME(pkg1, PackageTestFixed);
    }

#if IUTEST_HAS_PARAM_METHOD_TEST
    IUTEST_PMZ(ParamMethodTest, B, TestFunction, 0, 0);
#endif

#if IUTEST_HAS_PARAM_TEST
    IUTEST_P(PackageParamTest, B)
    {
        const char* name = ::iuutil::GetCurrentTestSuite()->name();
        IUTEST_EXPECT_PACKAGENAME_(pkg1, PackageParamTest, ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName(name));
    }
    IUTEST_INSTANTIATE_TEST_SUITE_P(B, PackageParamTest, ::iutest::Range<int>(0, 2));
#endif

#if IUTEST_HAS_TYPED_TEST
    IUTEST_TYPED_TEST(PackageTypedTest, B)
    {
        const char* name = ::iuutil::GetCurrentTestSuite()->name();
        IUTEST_EXPECT_PACKAGENAME_(pkg1, PackageTypedTest, ::iuutil::TestNameRemoveIndexName(name));
    }
#endif

#if IUTEST_HAS_TYPED_TEST_P
    typedef ::iutest::Types<int, float> MyTypesB;
    IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(B, PackageTypeParamTest, MyTypesB);
#endif
}
