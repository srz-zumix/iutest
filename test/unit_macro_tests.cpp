//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_macro_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2021, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_CXX2B
IUTEST(UnitMacroTest, CXX2B)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX20);
}
#endif
#if IUTEST_HAS_CXX20
IUTEST(UnitMacroTest, CXX20)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX2A);
}
#endif
#if IUTEST_HAS_CXX2A
IUTEST(UnitMacroTest, CXX2A)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX17);
}
#endif
#if IUTEST_HAS_CXX17
IUTEST(UnitMacroTest, CXX17)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX1Z);
}
#endif
#if IUTEST_HAS_CXX1Z
IUTEST(UnitMacroTest, CXX1Z)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX14);
}
#endif
#if IUTEST_HAS_CXX14
IUTEST(UnitMacroTest, CXX14)
{
    IUTEST_EXPECT_EQ(1, IUTEST_HAS_CXX11);
}
#endif
