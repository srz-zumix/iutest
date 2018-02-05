//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pred_tests.hpp
 * @brief       assertion predicate test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IUTEST_PRED_TESTS_HPP_
#define INCG_IUTEST_PRED_TESTS_HPP_

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
template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
bool Pred6Formater(const char* , T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
    return PredTest6(t0, t1, t2, t3, t4, t5);
}
#endif

#endif
