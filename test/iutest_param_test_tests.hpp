//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_test_tests.hpp
 * @brief		iutest parameter test
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
#ifndef INCG_iutest_param_test_tests_HPP_
#define INCG_iutest_param_test_tests_HPP_

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_PARAM_TEST

//======================================================================
// class
class ParamTest : public iutest::TestWithParam<int> {};

class MultiInstantiateParamTest : public iutest::TestWithParam<int> 
{
public:
	const int value;
	MultiInstantiateParamTest(void) : value(0) {}
};

IUTEST_P(MultiInstantiateParamTest, Test)
{
	int param = GetParam();
	IUTEST_ASSERT_EQ(0, value);
	IUTEST_ASSERT_EQ(param, param);
}

#endif

#endif
