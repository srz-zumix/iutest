//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_misc_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(UnitEnvTest, GetEnvironmentVariable)
{
    char buf[2];
    IUTEST_EXPECT_FALSE(::iutest::detail::GetEnvironmentVariable("PATH", buf, sizeof(buf)));
    IUTEST_EXPECT_FALSE(::iutest::detail::GetEnvironmentVariable("PATH", NULL, 0));
}

IUTEST(UnitAnyTest, Empty)
{
    ::iutest::any a;
    ::iutest::any* p = NULL;
    IUTEST_EXPECT_NULL(::iutest::unsafe_any_cast<int>(p));
    IUTEST_EXPECT_NULL(::iutest::unsafe_any_cast<int>(&a));
}

IUTEST(UnitAnyTest, String)
{
    ::iutest::any a = "test";
    IUTEST_EXPECT_EQ("test", ::iutest::any_cast< ::std::string >(a));
}

IUTEST(UnitRandomTest, Size64)
{
    ::iutest::detail::iuRandom r;
    iutest::UInt64 x[10];
    for( int i=0; i < 10; ++i)
    {
        x[i] = r.genrand<iutest::UInt64>() >> 32;
    }
    iutest::UInt64 y[10];
    for( int i=0; i < 10; ++i)
    {
        y[i] = r.genrand<iutest::UInt64>() >> 32;
    }
    IUTEST_EXPECT_NE_RANGE(x, y);
}
