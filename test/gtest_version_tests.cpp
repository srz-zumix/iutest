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

#if defined(GTEST_EXPECT_VER)

IUTEST(GTest, Version)
{
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

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
