//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_param_macro_tests.cpp
 * @brief       legacy parameter-test feature macro compatibility
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#if defined(IUTEST_USE_GTEST)
#include <gtest/internal/gtest-port.h>
#if defined(GTEST_HAS_PARAM_TEST)
static const int kUpstreamHasParamTest = GTEST_HAS_PARAM_TEST;
#else
static const int kUpstreamHasParamTest = 1;
#endif
#endif

#include "iutest.hpp"
#include "../include/gtest/iutest_switch.hpp"
#include "main.cpp"

#ifndef GTEST_HAS_PARAM_TEST
#  error GTEST_HAS_PARAM_TEST must remain defined for legacy source compatibility
#endif

#if GTEST_HAS_PARAM_TEST != IUTEST_HAS_PARAM_TEST
#  error The legacy macro must match IUTEST_HAS_PARAM_TEST
#endif

IUTEST(GTestParamMacro, LegacyPresence)
{
#ifdef GTEST_HAS_PARAM_TEST
    IUTEST_EXPECT_TRUE(true);
#else
    IUTEST_FAIL();
#endif
}

IUTEST(GTestParamMacro, FeatureValue)
{
    IUTEST_EXPECT_EQ(IUTEST_HAS_PARAM_TEST, GTEST_HAS_PARAM_TEST);
#if defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_EQ(kUpstreamHasParamTest, IUTEST_HAS_PARAM_TEST);
#endif
#if GTEST_HAS_PARAM_TEST
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_PARAM_TEST);
#else
    IUTEST_EXPECT_EQ(0, IUTEST_HAS_PARAM_TEST);
#endif
}

#if defined(IUTEST_USE_GTEST)
IUTEST(GTestParamMacro, GeneratorFeatures)
{
    IUTEST_EXPECT_EQ((IUTEST_HAS_PARAM_TEST && GTEST_VER >= 0x01140000), IUTEST_HAS_CONVERT_GENERATOR);
    IUTEST_EXPECT_EQ((IUTEST_HAS_PARAM_TEST && GTEST_VER >= 0x01170000), IUTEST_HAS_CONVERT_GENERATOR_FUNC);
}
#endif

#if IUTEST_HAS_PARAM_TEST
class GTestParamMacroTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(GTestParamMacroTest, ParameterizedTest)
{
    IUTEST_EXPECT_EQ(42, GetParam());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(LegacyMacro, GTestParamMacroTest, ::iutest::Values(42));
#endif
