﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        cxx_feature_tests.cpp
 * @brief       iutest c++ feature test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "logger_tests.hpp"

#if IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE

namespace
{

int f1()
{
    return 1;
}
int n1() noexcept
{
    return 1;
}
int f2()
{
    return 2;
}
int n2() noexcept
{
    return 2;
}

}   // namespace

IUTEST(NoexceptFounctionType, Assert)
{
    IUTEST_EXPECT_EQ(f1(), n1());
    IUTEST_EXPECT_LE(f1(), n1());
    IUTEST_EXPECT_GE(f1(), n1());
    IUTEST_EXPECT_LT(f1(), n2());
    IUTEST_EXPECT_GT(f2(), n1());
    IUTEST_EXPECT_NE(f1(), n2());
}

IUTEST(NoexceptFounctionType, ExpressionAssert)
{
    IUTEST_EXPECT(f1() == n1());
}

#endif

#if IUTEST_HAS_STD_STRING_VIEW

IUTEST(StringView, Compare)
{
    std::string_view view = "Hello";
    IUTEST_ASSERT_EQ("Hello", view);
}

IUTEST(StringView, PrintTo)
{
    LogChecker ck("Hello");
    std::string_view view = "Hello";
    IUTEST_SUCCEED() << ::iutest::PrintToString(view);
}

#endif

#if IUTEST_HAS_STD_OPTIONAL

IUTEST(Optional, Compare)
{
    {
        std::optional<int> opt = 0;
        IUTEST_EXPECT_TRUE(opt);
        IUTEST_EXPECT_EQ(0, opt);
    }
    {
        std::optional<int> opt = std::nullopt;
        IUTEST_EXPECT_FALSE(opt);
        IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(1234, opt), "1234");
    }
}

IUTEST(Optional, PrintTo)
{
    {
        LogChecker ck("1234");
        std::optional<int> opt = 1234;
        IUTEST_SUCCEED() << ::iutest::PrintToString(opt);
    }
    {
        LogChecker ck("nullopt");
        std::optional<int> opt = std::nullopt;
        IUTEST_SUCCEED() << ::iutest::PrintToString(opt);
    }
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
