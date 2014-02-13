//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_pred_tests.hpp
 * @brief		iutest assertion pred test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_iutest_pred_tests_HPP_
#define INCG_iutest_pred_tests_HPP_

//======================================================================
// function
inline bool IsOdd(int val)
{
	return (val & 1) != 0;
}
inline bool IsGreater(int a, int b)
{
	return a > b;
}
inline bool PredTest3(int v0, int v1, int v2)
{
	return v0 == 0 && v1 == 1 && v2 == 2;
}
inline bool PredTest4(int v0, int v1, int v2, int v3)
{
	return PredTest3(v0, v1, v2) && v3 == 3;
}
inline bool PredTest5(int v0, int v1, int v2, int v3, int v4)
{
	return PredTest4(v0, v1, v2, v3) && v4 == 4;
}
#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_VARIADIC_MACROS)
inline bool PredTest6(int v0, int v1, int v2, int v3, int v4, int v5)
{
	return PredTest5(v0, v1, v2, v3, v4) && v5 == 5;
}
#endif

#endif
