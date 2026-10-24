//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        print_to_string_param_name_tests.cpp
 * @brief       PrintToStringParamName compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"
#include "main.cpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR

IUTEST(PrintToStringParamNameTest, Integer)
{
    const ::iutest::PrintToStringParamName name;
    IUTEST_EXPECT_EQ("42", name(::iutest::TestParamInfo<int>(42, 7)));
    IUTEST_EXPECT_EQ("-1", name(::iutest::TestParamInfo<int>(-1, 0)));
}

IUTEST(PrintToStringParamNameTest, String)
{
    const ::std::string value = "alpha_123";
    const ::testing::PrintToStringParamName name;
    IUTEST_EXPECT_EQ(::iutest::PrintToString(value)
        , name(::iutest::TestParamInfo< ::std::string >(value, 1)));
    IUTEST_EXPECT_EQ(::iutest::PrintToString("beta")
        , name(::iutest::TestParamInfo<const char*>("beta", 0)));
}

class PrintIntegerParamNameTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(PrintIntegerParamNameTest, Name)
{
    IUTEST_EXPECT_EQ("Name/" + ::iutest::PrintToString(GetParam())
        , ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Print, PrintIntegerParamNameTest
    , ::iutest::Values(0, 42, 123), ::iutest::PrintToStringParamName());

#if !defined(IUTEST_USE_GTEST)
// Google Test quotes strings in PrintToString, making them invalid parameter names.
class PrintStringParamNameTest : public ::iutest::TestWithParam< ::std::string > {};

IUTEST_P(PrintStringParamNameTest, Name)
{
    IUTEST_EXPECT_EQ("Name/" + GetParam()
        , ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Print, PrintStringParamNameTest
    , ::iutest::Values("alpha", "beta_123"), ::testing::PrintToStringParamName());
#endif

#endif
