//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        tr1_param_direct_tests.cpp
 * @brief       parameter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "param_test_tests.hpp"

#if !defined(IUTEST_USE_GTEST)

#include "../include/tr1/iutest_param_direct_tests.hpp"

#if IUTEST_HAS_PARAM_TEST && !defined(IUTEST_NO_VARIADIC_MACROS)

typedef ParamTest ParamDirectTest;
IUTEST_P(ParamDirectTest, Test)
{
    IUTEST_SUCCEED() << GetParam();
}

int param_test_array[] = { 3, 2, 1, 0 };
::std::vector<int> va(param_test_array, param_test_array+(sizeof(param_test_array)/sizeof(param_test_array[0])));
IUTEST_INSTANTIATE_TEST_SUITE_P(My1, ParamDirectTest, ::iutest::Range<int>(0, 10));
IUTEST_INSTANTIATE_TEST_SUITE_P(My3, ParamDirectTest, ::iutest::Values(0, 1, 10));
IUTEST_INSTANTIATE_TEST_SUITE_P(My4, ParamDirectTest, ::iutest::ValuesIn(param_test_array));
IUTEST_INSTANTIATE_TEST_SUITE_P(My5, ParamDirectTest, ::iutest::ValuesIn(va));
#if IUTEST_HAS_INITIALIZER_LIST
IUTEST_INSTANTIATE_TEST_SUITE_P(My6, ParamDirectTest, ::iutest::ValuesIn({ 3, 2, 1, 0 }));
IUTEST_INSTANTIATE_TEST_SUITE_P(My7, ParamDirectTest, { 3, 2, 1, 0 });
#endif

#endif

#endif
