//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_version_tests.cpp
 * @brief       gtest version detect test
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
#include "iutest.hpp"

#if defined(IUTEST_USE_GTEST)

IUTEST(GTest, Print)
{
    IUTEST_SUCCEED() << GTEST_VER;
}

#if defined(GTEST_EXPECT_VER)

IUTEST(GTest, Version)
{
    IUTEST_ASSUME_GT(GTEST_EXPECT_VER, 0);
    IUTEST_EXPECT_EQ(GTEST_EXPECT_VER, GTEST_VER);
}

#endif

#if defined(GTEST_EXPECT_LATEST)

IUTEST(GTest, Latest)
{
    IUTEST_EXPECT_EQ(GTEST_EXPECT_LATEST, GTEST_LATEST);
}

#endif

#endif

#if defined(IUTEST_USE_GMOCK)

IUTEST(GMock, Print)
{
    IUTEST_SUCCEED() << GMOCK_VER;
}

#if !defined(GMOCK_EXPECT_VER) && defined(GTEST_EXPECT_VER)
#  define GMOCK_EXPECT_VER  GTEST_EXPECT_VER
#endif

#if defined(GMOCK_EXPECT_VER)

IUTEST(GMock, Version)
{
    IUTEST_ASSUME_GT(GMOCK_EXPECT_VER, 0);
    IUTEST_EXPECT_EQ(GMOCK_EXPECT_VER, GMOCK_VER);
}

#endif

#if !defined(GMOCK_EXPECT_LATEST) && defined(GTEST_EXPECT_LATEST)
#  define GMOCK_EXPECT_LATEST  GTEST_EXPECT_LATEST
#endif

#if defined(GMOCK_EXPECT_LATEST)

IUTEST(GMock, Latest)
{
    IUTEST_EXPECT_EQ(GMOCK_EXPECT_LATEST, GMOCK_LATEST);
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
