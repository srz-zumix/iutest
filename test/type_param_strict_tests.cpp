//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_strict_tests.cpp
 * @brief       type parameter strict check test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#if defined(IUTEST_TYPED_TEST_P_STRICT)
#  undef IUTEST_TYPED_TEST_P_STRICT
#endif
#define IUTEST_TYPED_TEST_P_STRICT  1
#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST_P && 0 // FIXME

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

// Mul2 + suffix test
IUTEST_TYPED_TEST_P(TypeParamTest, Mul2Static)
{
    TestFixture::value = 1;
    IUTEST_ASSERT_EQ(TestFixture::value+TestFixture::value, 2*TestFixture::value);
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, Mul2Static, Mul2);

namespace type_param_test
{

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My, TypeParamTest, int);

}

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

