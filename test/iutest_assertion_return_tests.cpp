//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assertion_return_tests.cpp
 * @brief		iutest assertion return test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

#if !defined(IUTEST_USE_GTEST)

static int value = 0;

int ReturnTest(void)
{
	IUTEST_ASSERT_TRUE(false) << "message" << ::iutest::AssertionReturn<int>(-1);
	return 0;
}

void ReturnTestCall(void)
{
	value = ReturnTest();
}

IUTEST(ReturnTest, Test)
{
	IUTEST_ASSERT_FATAL_FAILURE(ReturnTestCall(), "");
	IUTEST_ASSERT_EQ(-1, value);
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

