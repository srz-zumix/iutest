//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        progress_tests.cpp
 * @brief       プログレス表示 テスト
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
#include "../include/listener/iutest_progress_printer.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_NOTNULL( ::iutest::ProgressPrintListener::SetUp() );
#endif
    return IUTEST_RUN_ALL_TESTS();
}

#if !defined(IUTEST_USE_GTEST)

#define DECL_TEST(n)    IUTEST(Foo, Bar##n) {   \
                            ::iutest::internal::SleepMilliseconds(100); }


DECL_TEST(0)
DECL_TEST(1)
DECL_TEST(2)
DECL_TEST(3)
DECL_TEST(4)
DECL_TEST(5)
DECL_TEST(6)
DECL_TEST(7)
DECL_TEST(8)
DECL_TEST(9)
DECL_TEST(10)
DECL_TEST(11)
DECL_TEST(12)
DECL_TEST(13)
DECL_TEST(14)
DECL_TEST(15)
DECL_TEST(16)
DECL_TEST(17)
DECL_TEST(18)
DECL_TEST(19)

#endif
