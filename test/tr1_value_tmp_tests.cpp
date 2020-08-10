//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        tr1_value_tmp_tests.cpp
 * @brief       実験場
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
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

#include "../include/tr1/iutest_value_tmp_tests.hpp"

#if IUTEST_HAS_TYPED_TEST

/**
 * @note    このようなテストがしたい場合、型付け もしくは 型をパラメータ化したテストで、
 *          要素の型に、必要な型・値の定義をすれば十分である
*/

template<int N>
class factorial
{
    template<int M, typename DMY>
    struct impl
    {
        static const int value = M * factorial<M-1>::value;
    };
    template<typename DMY>
    struct impl<1, DMY>
    {
        static const int value = 1;
    };
    template<typename DMY>
    struct impl<0, DMY>
    {
        static const int value = 0;
    };
    // 負数は省略
public:
    static const int value = impl<N, void>::value;
};

template<int N>
class TestValueType : public ::iutest::Test
{
protected:
    static const int V = factorial<N>::value;
};

typedef ::iutest::Types< ::iutest::TemplateValue<10>, ::iutest::TemplateValue<0> > Types;

IUTEST_VALUETMP_TEST_SUITE(TestValueType, Types);

IUTEST_VALUETMP_TEST(TestValueType, Equal)
{
    IUTEST_SUCCEED() << this->V;
}

template<typename T>
class TestValueType2 : public ::iutest::Test
{
};

IUTEST_TYPED_TEST_SUITE(TestValueType2, Types);

IUTEST_TYPED_TEST(TestValueType2, Equal)
{
    IUTEST_SUCCEED() << factorial<TypeParam::kValue>::value;
}

#endif

#endif

