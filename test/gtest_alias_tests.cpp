//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_alias_tests.cpp
 * @brief       Google Test prefixed macro compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include <cmath>
#include "../include/gtest/iutest_spi_switch.hpp"

GTEST_TEST(GTestAliasTest, Assertions)
{
    GTEST_ASSERT_EQ(1, 1) << "equal";
    GTEST_ASSERT_NE(1, 2) << "not equal";
    GTEST_ASSERT_LT(1, 2) << "less";
    GTEST_ASSERT_LE(1, 1) << "less or equal";
    GTEST_ASSERT_GT(2, 1) << "greater";
    GTEST_ASSERT_GE(1, 1) << "greater or equal";
#if !defined(IUTEST_USE_GTEST) || defined(GTEST_ASSERT_TRUE)
    GTEST_ASSERT_TRUE(true) << "true";
    GTEST_ASSERT_FALSE(false) << "false";
    GTEST_EXPECT_TRUE(true) << "true";
    GTEST_EXPECT_FALSE(false) << "false";
#endif
#if !defined(IUTEST_USE_GTEST) || defined(GTEST_SUCCEED)
    GTEST_SUCCEED() << "success";
#endif
}

GTEST_TEST(GTestAliasTest, Failures)
{
    EXPECT_FATAL_FAILURE(GTEST_FAIL() << "fatal alias", "fatal alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_EQ(1, 2) << "eq alias", "eq alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_NE(1, 1) << "ne alias", "ne alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_LT(2, 1) << "lt alias", "lt alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_LE(2, 1) << "le alias", "le alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_GT(1, 2) << "gt alias", "gt alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_GE(1, 2) << "ge alias", "ge alias");
#if !defined(IUTEST_USE_GTEST) || defined(GTEST_ASSERT_TRUE)
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_TRUE(false) << "true alias", "true alias");
    EXPECT_FATAL_FAILURE(GTEST_ASSERT_FALSE(true) << "false alias", "false alias");
    EXPECT_NONFATAL_FAILURE(GTEST_EXPECT_TRUE(false) << "true alias", "true alias");
    EXPECT_NONFATAL_FAILURE(GTEST_EXPECT_FALSE(true) << "false alias", "false alias");
#endif
#if !defined(IUTEST_USE_GTEST) || defined(GTEST_FAIL_AT)
    EXPECT_FATAL_FAILURE(GTEST_FAIL_AT("alias.cpp", 123) << "location alias", "location alias");
#endif
}

GTEST_TEST(GTestAliasTest, Skip)
{
    GTEST_SKIP() << "skip alias";
    GTEST_FAIL() << "must not reach";
}

GTEST_TEST(GTestAliasTest, IutestAssertions)
{
    IUTEST_ASSERT_TRUE(true);
    IUTEST_ASSERT_FALSE(false);
    IUTEST_ASSERT_EQ(1, 1);
    IUTEST_ASSERT_NE(1, 2);
    IUTEST_ASSERT_LT(1, 2);
    IUTEST_ASSERT_LE(1, 1);
    IUTEST_ASSERT_GT(2, 1);
    IUTEST_ASSERT_GE(1, 1);
    IUTEST_EXPECT_TRUE(true);
    IUTEST_EXPECT_FALSE(false);
    IUTEST_ASSERT(true);
    IUTEST_ASSERT_NOT(false);
    IUTEST_EXPECT(true);
    IUTEST_EXPECT_NOT(false);
    int value = 0;
    int* ptr = &value;
    IUTEST_ASSERT_NULL(static_cast<int*>(IUTEST_NULLPTR));
    IUTEST_ASSERT_NOTNULL(ptr);
    IUTEST_EXPECT_NOTNULL(ptr);
}

#if !(defined(GTEST_DONT_DEFINE_TEST) && GTEST_DONT_DEFINE_TEST)
TEST(GTestAliasTest, ShortNames)
{
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    ASSERT_EQ(1, 1);
    ASSERT_NE(1, 2);
    ASSERT_LT(1, 2);
    ASSERT_LE(1, 1);
    ASSERT_GT(2, 1);
    ASSERT_GE(1, 1);
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
    SUCCEED();
    EXPECT_FATAL_FAILURE(FAIL() << "short failure", "short failure");
}
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
