//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_dont_define_tests.cpp
 * @brief       Google Test short macro opt-out tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#define GTEST_DONT_DEFINE_FAIL 1
#define GTEST_DONT_DEFINE_SUCCEED 1
#define GTEST_DONT_DEFINE_ASSERT_EQ 1
#define GTEST_DONT_DEFINE_ASSERT_NE 1
#define GTEST_DONT_DEFINE_ASSERT_LT 1
#define GTEST_DONT_DEFINE_ASSERT_LE 1
#define GTEST_DONT_DEFINE_ASSERT_GT 1
#define GTEST_DONT_DEFINE_ASSERT_GE 1
#define GTEST_DONT_DEFINE_ASSERT_TRUE 1
#define GTEST_DONT_DEFINE_ASSERT_FALSE 1
#define GTEST_DONT_DEFINE_EXPECT_TRUE 1
#define GTEST_DONT_DEFINE_EXPECT_FALSE 1
#define GTEST_DONT_DEFINE_TEST 1

#include "../include/gtest/iutest_switch.hpp"

#if defined(FAIL) || defined(FAIL_AT) || defined(SUCCEED) || defined(TEST)
#  error Google Test short test macros must not be defined
#endif
#if defined(ASSERT_EQ) || defined(ASSERT_NE) || defined(ASSERT_LT) || defined(ASSERT_LE) \
    || defined(ASSERT_GT) || defined(ASSERT_GE)
#  error Google Test short comparison macros must not be defined
#endif
#if !defined(IUTEST_USE_GTEST) || defined(GTEST_ASSERT_TRUE)
#  if defined(ASSERT_TRUE) || defined(ASSERT_FALSE) || defined(EXPECT_TRUE) || defined(EXPECT_FALSE)
#    error Google Test short boolean macros must not be defined
#  endif
#endif

#include "gtest_alias_tests.cpp"
