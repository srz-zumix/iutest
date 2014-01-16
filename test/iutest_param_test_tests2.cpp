//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_test_tests2.cpp
 * @brief		iutest parameter test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
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

