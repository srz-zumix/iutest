//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        near_message_tests.cpp
 * @brief       NEAR failure message tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/iutest_spi.hpp"

#if !defined(IUTEST_USE_GTEST)
IUTEST(NearMessageTest, OrdinaryFailure)
{
    const ::iutest::AssertionResult result =
        ::iutest::internal::DoubleNearPredFormat("1.0", "2.0", "0.1", 1.0, 2.0, 0.1);
    IUTEST_ASSERT_TRUE(result.failed());
    IUTEST_EXPECT_NE(::std::string::npos, ::std::string(result.message()).find("Value of: abs("));
    IUTEST_EXPECT_EQ(::std::string::npos, ::std::string(result.message()).find("adjacent doubles"));
}

IUTEST(NearMessageTest, ZeroTolerance)
{
    const ::iutest::AssertionResult result =
        ::iutest::internal::DoubleNearPredFormat("1.0", "2.0", "0.0", 1.0, 2.0, 0.0);
    IUTEST_ASSERT_TRUE(result.failed());
    IUTEST_EXPECT_NE(::std::string::npos, ::std::string(result.message()).find("Value of: abs("));
    IUTEST_EXPECT_EQ(::std::string::npos, ::std::string(result.message()).find("adjacent doubles"));
}

#if IUTEST_HAS_CXX11 && (!defined(_MSC_VER) || _MSC_VER >= 1800)
IUTEST(NearMessageTest, TinyTolerance)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_NEAR(1.0, 1.0 + 1e-15, 1e-30),
        "smaller than the distance between adjacent doubles");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_NEAR(1.0, 1.0 + 1e-15, 1e-30),
        "Consider using EXPECT_DOUBLE_EQ instead");
}
#endif
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
