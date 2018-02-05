//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_tap_tests.cpp
 * @brief       https://github.com/kinow/gtest-tap-listener 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#define GTEST_TAP_PRINT_TO_STDOUT

//======================================================================
// include
#include "iutest.hpp"
#include "tap.h"

IUTEST(Foo, Bar)
{
    IUTEST_EXPECT_EQ(0, 1);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new tap::TapListener());
    return IUTEST_RUN_ALL_TESTS();
}
