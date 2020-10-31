//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        param_test_tests2.cpp
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

IUTEST_INSTANTIATE_TEST_SUITE_P(My2, MultiInstantiateParamTest, ::iutest::Values(0, 1, 10));

#if IUTEST_HAS_TUPLE && !defined(IUTEST_USE_GTEST)

class TupleGetTest : public ::iutest::TestWithParam< ::iutest::tuples::tuple<bool, int> >
{
};

IUTEST_P(TupleGetTest, Test)
{
    IUTEST_ASSERT_TRUE(GetParam<0>());
    IUTEST_ASSERT_EQ(10, GetParam<1>());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, TupleGetTest
    , ::iutest::Values( ::iutest::tuples::tuple<bool, int>(true, 10) ) );

#if !defined(IUTEST_USE_GTEST)

class TypeConversionParamTest : public ::iutest::TestWithParam<double> {};

IUTEST_P(TypeConversionParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, TypeConversionParamTest, ::iutest::Values(4));

#endif

#endif

#endif

