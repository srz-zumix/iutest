//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        floatingpoint_printers_tests.cpp
 * @brief       float/double printer precision test
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

#if (!defined(IUTEST_USE_GTEST) && IUTEST_HAS_FULL_PRECISION_FLOAT_PRINT && IUTEST_HAS_IOMANIP) \
    || (defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01130000)

IUTEST(FloatingPointPrintersTest, Float)
{
    IUTEST_EXPECT_STREQ("0.1", ::iutest::PrintToString(0.1f));
    IUTEST_EXPECT_STREQ("0.333333343", ::iutest::PrintToString(1.0f / 3));
    IUTEST_EXPECT_STREQ("-0.333333343", ::iutest::PrintToString(-1.0f / 3));
    IUTEST_EXPECT_STREQ("1.0999999", ::iutest::PrintToString(1.0999999f));
    IUTEST_EXPECT_STREQ("9e+09", ::iutest::PrintToString(9e9f));
    IUTEST_EXPECT_STREQ("1e+10", ::iutest::PrintToString(1e10f));
}

IUTEST(FloatingPointPrintersTest, Double)
{
    IUTEST_EXPECT_STREQ("0.1", ::iutest::PrintToString(0.1));
#if defined(IUTEST_USE_GTEST) || IUTEST_HAS_CXX11
    IUTEST_EXPECT_STREQ("0.33333333333333331", ::iutest::PrintToString(1.0 / 3));
    IUTEST_EXPECT_STREQ("-0.33333333333333331", ::iutest::PrintToString(-1.0 / 3));
#else
    IUTEST_EXPECT_STREQ("0.333333333333333315", ::iutest::PrintToString(1.0 / 3));
    IUTEST_EXPECT_STREQ("-0.333333333333333315", ::iutest::PrintToString(-1.0 / 3));
#endif
    IUTEST_EXPECT_STREQ("10000000000", ::iutest::PrintToString(1e10));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(FloatingPointPrintersTest, Wrapper)
{
    const ::iutest::floating_point<float> value(1.0f / 3);
    IUTEST_EXPECT_STRIN("0.333333343(0x", ::iutest::PrintToString(value));
}

IUTEST(FloatingPointPrintersTest, RestoresPrecision)
{
    ::iutest::iu_stringstream stream;
    stream.precision(3);
    ::iutest::detail::PrintTo(1.0 / 3, &stream);
    IUTEST_EXPECT_EQ(3, stream.precision());
}
#endif
#endif

#if !defined(IUTEST_USE_GTEST) && !IUTEST_HAS_FULL_PRECISION_FLOAT_PRINT
IUTEST(FloatingPointPrintersTest, LegacyPrecision)
{
    IUTEST_EXPECT_STREQ("0.333333", ::iutest::PrintToString(1.0f / 3));
    IUTEST_EXPECT_STREQ("0.333333", ::iutest::PrintToString(1.0 / 3));
}
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
