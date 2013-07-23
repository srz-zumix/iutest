//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_failure_tests.cpp
 * @brief		iutest_no  failure test
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

void NoFatalFailureTest_Subroutine(void)
{
	IUTEST_EXPECT_EQ(3, 3);
}

IUTEST_PRAGMA_GCC_WARN_PUSH()
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

IUTEST_PRAGMA_GCC_WARN_POP()
