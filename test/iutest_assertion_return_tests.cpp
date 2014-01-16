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
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_ASSERTION_RETURN

static int value = 0;

int ReturnTest(void)
{
	IUTEST_ASSERT_TRUE(false) << "message" << ::iutest::AssertionReturnType<int>(-1);
	IUTEST_ASSERT_TRUE(false) << "message" << ::iutest::AssertionReturn(-1);
	return 0;
}

void ReturnTestCall(void)
{
	value = ReturnTest();
	IUTEST_ASSERT_TRUE(true) << ::iutest::AssertionReturn();
}

IUTEST(ReturnTest, Test)
{
	IUTEST_ASSERT_FATAL_FAILURE(ReturnTestCall(), "");
#if IUTEST_USE_THROW_ON_ASSERTION_FAILURE
	IUTEST_ASSERT_EQ( 0, value);
#else
	IUTEST_ASSERT_EQ(-1, value);
#endif
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

