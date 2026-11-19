//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        main.cpp
 * @brief       iutest vcpkg port test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(VcpkgTest, Simple)
{
    IUTEST_ASSERT_EQ(2, 1 + 1);
}

class VcpkgParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(VcpkgParamTest, Param)
{
    IUTEST_ASSERT_LT(0, GetParam());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, VcpkgParamTest, ::iutest::Values(1, 2, 3));
