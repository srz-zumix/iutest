//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        values_tests.cpp
 * @brief       Values test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

#if IUTEST_HAS_PARAM_TEST

class ValuesTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ValuesTest, Test)
{
}

#if IUTEST_HAS_VARIADIC_VALUES

IUTEST_INSTANTIATE_TEST_SUITE_P( X1, ValuesTest, ::iutest::Values(1) );
//IUTEST_INSTANTIATE_TEST_SUITE_P( X2, ValuesTest, ::iutest::Values(1,2) );
IUTEST_INSTANTIATE_TEST_SUITE_P( X51, ValuesTest
    , ::iutest::Values( IUTEST_PP_ENUM_PARAMS(51, IUTEST_PP_EMPTY()) ) );

#else

#define DECL_VALUES_PARAMS(i, param)    \
    IUTEST_INSTANTIATE_TEST_SUITE_P( IUTEST_PP_CAT(param, IUTEST_PP_INC(i)), ValuesTest   \
            , ::iutest::Values( IUTEST_PP_ENUM_PARAMS(IUTEST_PP_INC(i), IUTEST_PP_EMPTY()) ) );

#define DECL_VALUES_INSTANCE(n)         \
    IUTEST_PP_REPEAT(n, DECL_VALUES_PARAMS, X)

DECL_VALUES_INSTANCE(50)

#endif

#endif

#endif
