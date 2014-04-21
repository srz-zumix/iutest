//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_test_tests2.cpp
 * @brief		parameter test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_param_test_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

IUTEST_INSTANTIATE_TEST_CASE_P(My2, MultiInstantiateParamTest, ::iutest::Values(0, 1, 10));

#endif

