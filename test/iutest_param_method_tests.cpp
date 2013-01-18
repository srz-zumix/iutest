//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_method_tests.cpp
 * @brief		iutest parameter method test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
	IUTEST_ASSERT_EQ(x, y);
}
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 0, 0);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 1, 1);
IUTEST_PMZ(ParamMethodTest, EQ, TestFunction, 2, 2);

class ParamMethodTestFixed : public ::iutest::Test {};

IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 1, 1);
IUTEST_PMZ_F(ParamMethodTestFixed, EQ, TestFunction, 2, 2);

#endif

