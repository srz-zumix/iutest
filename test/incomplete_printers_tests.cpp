//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        incomplete_printers_tests.cpp
 * @brief       incomplete type printer test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

struct Incomplete;

IUTEST(IncompletePrintersTest, Reference)
{
    char object = 0;
    IUTEST_EXPECT_STREQ("(incomplete type)", ::iutest::PrintToString(reinterpret_cast<Incomplete&>(object)));
}

struct Complete
{
    unsigned char bytes[2];
};

IUTEST(IncompletePrintersTest, CompleteRawBytes)
{
    Complete object = { { 0, 1 } };
#if defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("2-byte object <00-01>", ::iutest::PrintToString(object));
#else
    IUTEST_EXPECT_STREQ("2-Byte object < 00 01 >", ::iutest::PrintToString(object));
#endif
}

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
