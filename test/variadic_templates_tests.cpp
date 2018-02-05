//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        variadic_templates_tests.cpp
 * @brief       Variadic Templates test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_VARIADIC_PRED

bool pred_test(int a0, int a1, int a2, int a3, int a4, int a5)
{
    return a0+a2+a4 == a1+a3+a5;
}

IUTEST(PredTest, Variadic)
{
    IUTEST_ASSERT_PRED(pred_test, 0, 0, 0, 0, 0, 0);
    IUTEST_EXPECT_PRED(pred_test, 0, 0, 0, 0, 0, 0);
    IUTEST_INFORM_PRED(pred_test, 0, 0, 0, 0, 0, 0);
}

#endif

