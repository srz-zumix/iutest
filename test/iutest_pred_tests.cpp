//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_pred_tests.cpp
 * @brief		iutest assertion pred test
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
#include "../include/iutest.hpp"

static bool IsOdd(int val)
{
	return (val & 1) != 0;
}
static bool	IsGreater(int a, int b)
{
	return a > b;
}
static bool	PredTest3(int , int , int )
{
	return true;
}
static bool	PredTest4(int , int , int , int )
{
	return true;
}
static bool	PredTest5(int , int , int , int , int )
{
	return true;
}

IUTEST(AssertionTest, Pred)
{
	IUTEST_ASSERT_PRED1(IsOdd, 3);
	IUTEST_EXPECT_PRED1(IsOdd, 3);
	IUTEST_INFORM_PRED1(IsOdd, 3);
	IUTEST_ASSERT_PRED2(IsGreater, 3, 1);
	IUTEST_EXPECT_PRED2(IsGreater, 3, 1);
	IUTEST_INFORM_PRED2(IsGreater, 3, 1);
	IUTEST_ASSERT_PRED3(PredTest3, 0, 1, 2);
	IUTEST_EXPECT_PRED3(PredTest3, 0, 1, 2);
	IUTEST_INFORM_PRED3(PredTest3, 0, 1, 2);
	IUTEST_ASSERT_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_INFORM_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_ASSERT_PRED5(PredTest5, 0, 1, 2, 3, 4);
	IUTEST_EXPECT_PRED5(PredTest5, 0, 1, 2, 3, 4);
	IUTEST_INFORM_PRED5(PredTest5, 0, 1, 2, 3, 4);
}

