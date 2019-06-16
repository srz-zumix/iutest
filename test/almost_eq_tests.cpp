﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        almost_eq_tests.cpp
 * @brief       almost eq assertion test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class AlmostTest : public ::iutest::Test
{
};

typedef ::iutest::Types<int, float, double> AlmostTestTypes;
IUTEST_TYPED_TEST_CASE(AlmostTest, AlmostTestTypes);

IUTEST_TYPED_TEST(AlmostTest, Eq)
{
    TypeParam x = 1;
    IUTEST_ASSERT_ALMOST_EQ(x+x, 2*x);
}

template<typename T>
class AlmostUlpTest : public ::iutest::Test
{
};

typedef ::iutest::Types<float, double> AlmostUlpTestTypes;
IUTEST_TYPED_TEST_CASE(AlmostUlpTest, AlmostUlpTestTypes);

IUTEST_TYPED_TEST(AlmostUlpTest, Eq)
{
    TypeParam x = static_cast<TypeParam>(1);
    ::iutest_compatible::FloatingPointUnion<TypeParam> ulp;
    ulp.fv = x;
    ulp.uv += 1;
    IUTEST_EXPECT_ALMOST_EQ(ulp.fv, x);
    IUTEST_EXPECT_ALMOST_EQ(ulp.fv, 1);
}

#endif
