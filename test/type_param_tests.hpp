//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_tests.hpp
 * @brief       type parameter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IUTEST_TYPE_PARAM_TESTS_HPP_
#define INCG_IUTEST_TYPE_PARAM_TESTS_HPP_

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST_P

//======================================================================
// class
template<typename T>
class TypeParamTest : public ::iutest::Test
{
public:
    static T value;
};

template<typename T>
T TypeParamTest<T>::value = 0;

IUTEST_TYPED_TEST_SUITE_P(TypeParamTest);

IUTEST_TYPED_TEST_P(TypeParamTest, Mul2)
{
    TypeParam x = 1;
    IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST_P(TypeParamTest, StaticMul2)
{
    TestFixture::value = 1;
    IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, StaticMul2, Mul2);


#endif

#endif
