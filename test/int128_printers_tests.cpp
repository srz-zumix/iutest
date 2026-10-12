//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        int128_printers_tests.cpp
 * @brief       128-bit integer printer test
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

#if defined(IUTEST_USE_GTEST)
#  if defined(__SIZEOF_INT128__) && GTEST_VER >= 0x01120000
#    define IUTEST_TEST_INT128_PRINT 1
#  endif
#elif IUTEST_HAS_INT128
#  define IUTEST_TEST_INT128_PRINT 1
#endif

#if defined(IUTEST_TEST_INT128_PRINT)
IUTEST(Int128PrintersTest, Signed)
{
    typedef __int128_t Int128;
    typedef __uint128_t UInt128;
    const Int128 max = static_cast<Int128>(~static_cast<UInt128>(0) >> 1);
    const Int128 min = -max - 1;

    IUTEST_EXPECT_STREQ("0", ::iutest::PrintToString(static_cast<Int128>(0)));
    IUTEST_EXPECT_STREQ("1", ::iutest::PrintToString(static_cast<Int128>(1)));
    IUTEST_EXPECT_STREQ("-1", ::iutest::PrintToString(static_cast<Int128>(-1)));
    IUTEST_EXPECT_STREQ("18446744073709551616", ::iutest::PrintToString(static_cast<Int128>(1) << 64));
    IUTEST_EXPECT_STREQ("-18446744073709551616", ::iutest::PrintToString(-(static_cast<Int128>(1) << 64)));
    IUTEST_EXPECT_STREQ("170141183460469231731687303715884105727", ::iutest::PrintToString(max));
    IUTEST_EXPECT_STREQ("-170141183460469231731687303715884105728", ::iutest::PrintToString(min));
}

IUTEST(Int128PrintersTest, Unsigned)
{
    typedef __uint128_t UInt128;
    const UInt128 max = ~static_cast<UInt128>(0);

    IUTEST_EXPECT_STREQ("0", ::iutest::PrintToString(static_cast<UInt128>(0)));
    IUTEST_EXPECT_STREQ("1", ::iutest::PrintToString(static_cast<UInt128>(1)));
    IUTEST_EXPECT_STREQ("18446744073709551616", ::iutest::PrintToString(static_cast<UInt128>(1) << 64));
    IUTEST_EXPECT_STREQ("340282366920938463463374607431768211455", ::iutest::PrintToString(max));
}
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
