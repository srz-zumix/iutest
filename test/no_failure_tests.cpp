//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        no_failure_tests.cpp
 * @brief       iutest no failure test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

void NoFatalFailureTest_Subroutine(void)
{
    IUTEST_EXPECT_EQ(3, 3);
}

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()

IUTEST(NoFatalFailureTest, Assert)
{
    IUTEST_ASSERT_NO_FATAL_FAILURE(;);
    IUTEST_ASSERT_NO_FATAL_FAILURE(IUTEST_SUCCEED());
    IUTEST_ASSERT_NO_FATAL_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_ASSERT_NO_FATAL_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFatalFailureTest, Expect)
{
    IUTEST_EXPECT_NO_FATAL_FAILURE(;);
    IUTEST_EXPECT_NO_FATAL_FAILURE(IUTEST_SUCCEED());
    IUTEST_EXPECT_NO_FATAL_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_EXPECT_NO_FATAL_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFatalFailureTest, Inform)
{
    IUTEST_INFORM_NO_FATAL_FAILURE(;);
    IUTEST_INFORM_NO_FATAL_FAILURE(IUTEST_SUCCEED());
    IUTEST_INFORM_NO_FATAL_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_INFORM_NO_FATAL_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFatalFailureTest, Assume)
{
    IUTEST_ASSUME_NO_FATAL_FAILURE(;);
    IUTEST_ASSUME_NO_FATAL_FAILURE(IUTEST_SUCCEED());
    IUTEST_ASSUME_NO_FATAL_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_ASSUME_NO_FATAL_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFailureTest, Assert)
{
    IUTEST_ASSERT_NO_FAILURE(;);
    IUTEST_ASSERT_NO_FAILURE(IUTEST_SUCCEED());
    IUTEST_ASSERT_NO_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_ASSERT_NO_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFailureTest, Expect)
{
    IUTEST_EXPECT_NO_FAILURE(;);
    IUTEST_EXPECT_NO_FAILURE(IUTEST_SUCCEED());
    IUTEST_EXPECT_NO_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_EXPECT_NO_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFailureTest, Inform)
{
    IUTEST_INFORM_NO_FAILURE(;);
    IUTEST_INFORM_NO_FAILURE(IUTEST_SUCCEED());
    IUTEST_INFORM_NO_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_INFORM_NO_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST(NoFailureTest, Assume)
{
    IUTEST_ASSUME_NO_FAILURE(;);
    IUTEST_ASSUME_NO_FAILURE(IUTEST_SUCCEED());
    IUTEST_ASSUME_NO_FAILURE(NoFatalFailureTest_Subroutine());
    IUTEST_ASSUME_NO_FAILURE({ IUTEST_SUCCEED(); });
}

IUTEST_PRAGMA_WARN_POP()
