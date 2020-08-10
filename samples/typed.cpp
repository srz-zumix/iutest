//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        typed.cpp
 * @brief       typed and type parameterized test sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * 型付けテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};
typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Equal)
{
    TypeParam a = 0;
    IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST(TypedTest, Litle)
{
    TypeParam a = 1;
    IUTEST_ASSERT_LT(0, a);
}

#endif

/* ---------------------------------------------------
 * 型をパラメータ化したテスト
*//*--------------------------------------------------*/
#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypedTestP : public ::iutest::Test {};
typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE_P(TypedTestP);

IUTEST_TYPED_TEST_P(TypedTestP, Equal)
{
    TypeParam a = 0;
    IUTEST_ASSERT_EQ(0, a);
}

IUTEST_TYPED_TEST_P(TypedTestP, Litle)
{
    TypeParam a = 1;
    IUTEST_ASSERT_LT(0, a);
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypedTestP, Equal, Litle);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(TypedTestPInstance, TypedTestP, TypedTestTypes);

#endif


