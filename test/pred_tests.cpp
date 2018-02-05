//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pred_tests.cpp
 * @brief       assertion predicate test
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
#include "pred_tests.hpp"

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

#if !defined(IUTEST_NO_VARIADIC_MACROS)

#if IUTEST_HAS_VARIADIC_TEMPLATES

IUTEST(AssertionTest, VariadicPred)
{
    IUTEST_ASSERT_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
    IUTEST_EXPECT_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
    IUTEST_INFORM_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
    IUTEST_ASSUME_PRED(PredTest6, 0, 1, 2, 3, 4, 5);
}

#endif

IUTEST(AssertionTest, VariadicPredFormat)
{
    IUTEST_ASSERT_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
    IUTEST_EXPECT_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
    IUTEST_INFORM_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
    IUTEST_ASSUME_PRED_FORMAT(Pred6Formater, 0, 1, 2, 3, 4, 5);
}

#endif

#endif
