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
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
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
static bool IsGreater(int a, int b)
{
	return a > b;
}
static bool PredTest3(int v0, int v1, int v2)
{
	return v0 == 0 && v1 == 1 && v2 == 2;
}
static bool PredTest4(int v0, int v1, int v2, int v3)
{
	return PredTest3(v0, v1, v2) && v3 == 3;
}
static bool PredTest5(int v0, int v1, int v2, int v3, int v4)
{
	return PredTest4(v0, v1, v2, v3) && v4 == 4;
}

IUTEST(AssertionTest, Pred1)
{
	IUTEST_ASSERT_PRED1(IsOdd, 3);
	IUTEST_EXPECT_PRED1(IsOdd, 3);
	IUTEST_INFORM_PRED1(IsOdd, 3);
	IUTEST_ASSUME_PRED1(IsOdd, 3);
}

IUTEST(AssertionTest, Pred2)
{
	IUTEST_ASSERT_PRED2(IsGreater, 3, 1);
	IUTEST_EXPECT_PRED2(IsGreater, 3, 1);
	IUTEST_INFORM_PRED2(IsGreater, 3, 1);
	IUTEST_ASSUME_PRED2(IsGreater, 3, 1);
}

IUTEST(AssertionTest, Pred3)
{
	IUTEST_ASSERT_PRED3(PredTest3, 0, 1, 2);
	IUTEST_EXPECT_PRED3(PredTest3, 0, 1, 2);
	IUTEST_INFORM_PRED3(PredTest3, 0, 1, 2);
	IUTEST_ASSUME_PRED3(PredTest3, 0, 1, 2);
}

IUTEST(AssertionTest, Pred4)
{
	IUTEST_ASSERT_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_EXPECT_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_INFORM_PRED4(PredTest4, 0, 1, 2, 3);
	IUTEST_ASSUME_PRED4(PredTest4, 0, 1, 2, 3);
}

IUTEST(AssertionTest, Pred5)
{
	IUTEST_ASSERT_PRED5(PredTest5, 0, 1, 2, 3, 4);
	IUTEST_EXPECT_PRED5(PredTest5, 0, 1, 2, 3, 4);
	IUTEST_INFORM_PRED5(PredTest5, 0, 1, 2, 3, 4);
	IUTEST_ASSUME_PRED5(PredTest5, 0, 1, 2, 3, 4);
}

#if !defined(IUTEST_USE_GTEST)

#ifndef IUTEST_NO_VARIADIC_MACROS

static bool PredTest6(int v0, int v1, int v2, int v3, int v4, int v5)
{
	return PredTest5(v0, v1, v2, v3, v4) && v5 == 5;
}

#if IUTEST_HAS_VARIADIC_TEMPLATES

IUTEST(AssertionTest, VariadicPred)
{
	IUTEST_ASSERT_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
	IUTEST_EXPECT_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
	IUTEST_INFORM_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
	IUTEST_ASSUME_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
}

#endif

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
bool Pred6Formater(const char* , T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
	return PredTest6(t0, t1, t2, t3, t4, t5);
}

IUTEST(AssertionTest, VariadicPredFormat)
{
	IUTEST_ASSERT_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
	IUTEST_EXPECT_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
	IUTEST_INFORM_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
	IUTEST_ASSUME_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
}

#endif

#endif
