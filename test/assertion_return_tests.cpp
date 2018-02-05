//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        assertion_return_tests.cpp
 * @brief       iutest assertion return test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_ASSERTION_RETURN

static int value1 = 1;
static int value2 = 1;

int ReturnTest1(bool condition)
{
    IUTEST_ASSERT_TRUE(condition) << "message" << ::iutest::AssertionReturnType<int>(-1);
    return 0;
}

int ReturnTest2(bool condition)
{
    IUTEST_ASSERT_TRUE(condition) << "message" << ::iutest::AssertionReturn(-1);
    return 0;
}

void ReturnTestCall(void)
{
    IUTEST_ASSERT_EQ(0, ReturnTest1(true));
    IUTEST_ASSERT_EQ(0, ReturnTest2(true));
    IUTEST_ASSERT_FATAL_FAILURE(value1 = ReturnTest1(false), "message");
    IUTEST_ASSERT_FATAL_FAILURE(value2 = ReturnTest2(false), "message");
    IUTEST_ASSERT_TRUE(false) << ::iutest::AssertionReturn();
}

IUTEST(ReturnTest, Test)
{
    IUTEST_ASSERT_FATAL_FAILURE(ReturnTestCall(), "");
#if IUTEST_USE_THROW_ON_ASSERTION_FAILURE
    IUTEST_EXPECT_EQ( 1, value1);
    IUTEST_EXPECT_EQ( 1, value2);
#else
    IUTEST_EXPECT_EQ(-1, value1);
    IUTEST_EXPECT_EQ(-1, value2);
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

