//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_fatalfailure_tests.cpp
 * @brief		iutest_no fatal failure test
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

IUTEST_PRAGMA_GCC_WARN_POP()
