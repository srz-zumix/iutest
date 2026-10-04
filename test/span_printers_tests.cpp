//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        span_printers_tests.cpp
 * @brief       std::span printer test
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

#if IUTEST_HAS_CXX_HDR_SPAN && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01150000)

IUTEST(SpanPrintersTest, DynamicExtent)
{
    int values[] = { 1, 2, 3 };
    const ::std::span<int> span(values);
    IUTEST_EXPECT_STREQ("{ 1, 2, 3 }", ::iutest::PrintToString(span));
    IUTEST_EXPECT_STREQ("{}", ::iutest::PrintToString(span.subspan(0, 0)));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(SpanPrintersTest, FixedExtentConstElements)
{
    const int values[] = { 1, 2, 3 };
    const ::std::span<const int, 3> span(values);
    IUTEST_EXPECT_STREQ("{ 1, 2, 3 }", ::iutest::PrintToString(span));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
