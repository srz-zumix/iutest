//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_tests3.cpp
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

//======================================================================
// include
#include "type_param_tests.hpp"

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest3 : public ::iutest::Test
{
public:
    static T value;
};

template<typename T>
T TypeParamTest3<T>::value = 0;


IUTEST_TYPED_TEST_SUITE_P(TypeParamTest3);

IUTEST_TYPED_TEST_P(TypeParamTest3, Mul2)
{
    TypeParam x = 1;
    IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST_P(TypeParamTest3, StaticMul2)
{
    TestFixture::value = 1;
    IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest3, StaticMul2, Mul2);

namespace type_param_test
{

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My3, TypeParamTest, float);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My3, TypeParamTest3, short);

}


#endif

