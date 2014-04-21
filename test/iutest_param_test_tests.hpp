//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_test_tests.hpp
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
#ifndef INCG_iutest_param_test_tests_HPP_
#define INCG_iutest_param_test_tests_HPP_

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_PARAM_TEST

//======================================================================
// class
class ParamTest : public ::iutest::TestWithParam<int> {};

class MultiInstantiateParamTest : public ::iutest::TestWithParam<int> 
{
public:
	const int value;
	MultiInstantiateParamTest(void) : value(0) {}
};

#endif

#endif
