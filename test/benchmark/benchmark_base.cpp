//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		benchmark_base.cpp
 * @brief		benchmark base file
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

IUTEST_PACKAGE(PACKAGENAME)
{
    template<typename T>
    ::std::vector<T> make_param(int n, T param)
    {
        ::std::vector<T> v;
        for( int i=0; i < n; ++i )
        {
            v.push_back(param);
        }
        return v;
    }

    class ParamTest : public ::iutest::TestWithParam<int> {};

    IUTEST_P(ParamTest, Eq)
    {
        IUTEST_ASSERT_EQ(0, GetParam());
        IUTEST_EXPECT_EQ(0, GetParam());
        IUTEST_INFORM_EQ(0, GetParam());
        IUTEST_ASSUME_EQ(0, GetParam());
    }
    IUTEST_P(ParamTest, Ne)
    {
        IUTEST_ASSERT_NE(0, GetParam());
        IUTEST_EXPECT_NE(0, GetParam());
        IUTEST_INFORM_NE(0, GetParam());
        IUTEST_ASSUME_NE(0, GetParam());
    }

    IUTEST_INSTANTIATE_TEST_SUITE_P(A, ParamTest, ::iutest::Range<int>(0, 100000));
    IUTEST_INSTANTIATE_TEST_SUITE_P(B, ParamTest, ::iutest::Values(IUTEST_PP_ENUM_PARAMS(IUTEST_PP_LIMIT_ENUM, IUTEST_PP_EMPTY())));
    IUTEST_INSTANTIATE_TEST_SUITE_P(C, ParamTest, ::iutest::ValuesIn(make_param(1000, 0)));

#if IUTEST_HAS_COMBINE

    class CombineTest : public ::iutest::TestWithParam< ::iutest::tuples::tuple<bool, int, int> > {};
    static const int kCombineTestTable[] = {0, 1};

    IUTEST_P(CombineTest, Param)
    {
        (void)GetParam();
    }
    IUTEST_INSTANTIATE_TEST_SUITE_P(A, CombineTest
        , ::iutest::Combine(::iutest::Bool(), ::iutest::Values(1, 10), ::iutest::ValuesIn(kCombineTestTable)));
    IUTEST_INSTANTIATE_TEST_SUITE_P(B, CombineTest
        , ::iutest::Concat(
            ::iutest::Combine(::iutest::Values(false), ::iutest::Values(1, 10), ::iutest::ValuesIn(kCombineTestTable))
            , ::iutest::Combine(::iutest::Values(true), ::iutest::Values(1, 10), ::iutest::ValuesIn(kCombineTestTable))
        )
    );
    IUTEST_INSTANTIATE_TEST_SUITE_P(C, CombineTest
        , ::iutest::Combine(::iutest::Values(false), ::iutest::Values(1, 10), ::iutest::ValuesIn(kCombineTestTable))
            + ::iutest::Combine(::iutest::Values(true), ::iutest::Values(1, 10), ::iutest::ValuesIn(kCombineTestTable))
    );

#endif

    template<typename T>
    class TypedTest : public ::iutest::Test {};

    typedef ::iutest::Types<char, signed char, unsigned char
        , short, signed short, unsigned short
        , int, signed int, unsigned int
        , long, signed long, unsigned long
        , float, double> TypedTestTypes;
    IUTEST_TYPED_TEST_SUITE(TypedTest, TypedTestTypes);

    IUTEST_TYPED_TEST(TypedTest, Mul2)
    {
        TypeParam x = 1;
        IUTEST_ASSERT_EQ(x+x, 2*x);
    }

    template<typename T>
    class TypeParamTest : public ::iutest::Test {};
    IUTEST_TYPED_TEST_SUITE_P(TypeParamTest);

    IUTEST_TYPED_TEST_P(TypeParamTest, Mul2)
    {
        TypeParam x = 1;
        IUTEST_ASSERT_EQ(x+x, 2*x);
    }

    IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, Mul2);
    IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, TypeParamTest, TypedTestTypes);
}
