//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        param_test_tests1.cpp
 * @brief       parameter test
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
#include "param_test_tests.hpp"  // IWYU pragma: keep

#if IUTEST_HAS_PARAM_TEST

IUTEST_P(ParamTest, Test)
{
    IUTEST_SUCCEED() << GetParam();
}

int param_test_array[] = { 3, 2, 1, 0 };
::std::vector<int> va(param_test_array, param_test_array+(sizeof(param_test_array)/sizeof(param_test_array[0])));
IUTEST_INSTANTIATE_TEST_SUITE_P(Range, ParamTest, ::iutest::Range<int>(0, 10));
IUTEST_INSTANTIATE_TEST_SUITE_P(Values, ParamTest, ::iutest::Values(0, 1, 10));
IUTEST_INSTANTIATE_TEST_SUITE_P(ValuesInArray, ParamTest, ::iutest::ValuesIn(param_test_array));
IUTEST_INSTANTIATE_TEST_SUITE_P(ValuesInVector, ParamTest, ::iutest::ValuesIn(va));
#if IUTEST_HAS_INITIALIZER_LIST
IUTEST_INSTANTIATE_TEST_SUITE_P(ValuesInInitializerList, ParamTest, ::iutest::ValuesIn({ 3, 2, 1, 0 }));
#endif

#if !defined(IUTEST_USE_GTEST)

enum TestEnum
{
      TestEnum_0
    , TestEnum_1
    , TestEnum_2
    , TestEnum_3
    , TestEnum_4
    , TestEnum_5
};

class EnumParamTest : public ::iutest::TestWithParam<TestEnum> {};

IUTEST_P(EnumParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Range, EnumParamTest, ::iutest::Range<TestEnum>(TestEnum_0, TestEnum_5));

#endif

class BoolParamTest : public ::iutest::TestWithParam<bool> {};

IUTEST_P(BoolParamTest, X_Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, BoolParamTest, ::iutest::Bool());

#if !defined(IUTEST_USE_GTEST)

// name conflict test
class BoolParamTest_X : public ::iutest::TestWithParam<bool> {};
class B_BoolParamTest_X : public ::iutest::TestWithParam<bool> {};

IUTEST_P(BoolParamTest_X, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A_B, BoolParamTest_X, ::iutest::Bool());
IUTEST_INSTANTIATE_TEST_SUITE_P(A, B_BoolParamTest_X, ::iutest::Bool());

#endif


IUTEST_P(MultiInstantiateParamTest, Test)
{
    int param = GetParam();
    IUTEST_ASSERT_EQ(0, value);
    IUTEST_ASSERT_EQ(param, param);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, MultiInstantiateParamTest, ::iutest::Range<int>(0, 10));

class InheritanceTestFixture : public ::iutest::Test {};
class InheritanceParamTest : public InheritanceTestFixture, public ::iutest::WithParamInterface<int> {};

IUTEST_P(InheritanceParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, InheritanceParamTest, ::iutest::Values(0));

#endif

