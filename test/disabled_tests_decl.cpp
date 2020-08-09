//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        disabled_tests_decl.cpp
 * @brief       disabled tests testsuite definitions
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(DISABLED_Foo, Bar)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, DISABLED_Bar)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, Bar_DISABLED_)
{
    IUTEST_ASSERT_EQ(3, 3);
}

#if IUTEST_HAS_PARAM_TEST

class FooP : public ::iutest::TestWithParam< int >
{
};

typedef FooP FooP_DISABLED_;
typedef FooP DISABLED_FooP;

IUTEST_P(FooP_DISABLED_, Bar)
{
}

IUTEST_P(FooP, DISABLED_Bar)
{
    int v = GetParam();
    IUTEST_FAIL() << v;
}

IUTEST_P(DISABLED_FooP, Bar)
{
    int v = GetParam();
    IUTEST_FAIL() << v;
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, FooP, ::iutest::Values(0, 2));
IUTEST_INSTANTIATE_TEST_SUITE_P(A, FooP_DISABLED_, ::iutest::Values(0, 2));
IUTEST_INSTANTIATE_TEST_SUITE_P(A, DISABLED_FooP , ::iutest::Values(0, 2));

#endif

#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
    IUTEST_ASSERT_EQ(x, y);
}

IUTEST_PMZ(ParamMethod_Foo_DISABLED_, EQ, TestFunction, 0, 0);
IUTEST_PMZ(ParamMethod_Foo, DISABLED_EQ, TestFunction, 0, 1);
IUTEST_PMZ(DISABLED_ParamMethod_Foo, EQ, TestFunction, 0, 1);

class ParamMethodF_Foo : public ::iutest::Test {};
typedef ParamMethodF_Foo ParamMethodF_Foo_DISABLED_;
typedef ParamMethodF_Foo DISABLED_ParamMethodF_Foo;

IUTEST_PMZ_F(ParamMethodF_Foo_DISABLED_, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(ParamMethodF_Foo, DISABLED_EQ, TestFunction, 0, 1);
IUTEST_PMZ_F(DISABLED_ParamMethodF_Foo, EQ, TestFunction, 0, 1);

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedFoo : public ::iutest::Test {};
template<typename T>
class TypedFoo_DISABLED_ : public ::iutest::Test {};
template<typename T>
class DISABLED_TypedFoo : public ::iutest::Test {};

typedef ::iutest::Types<int> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedFoo, TypedTestTypes);
IUTEST_TYPED_TEST_SUITE(TypedFoo_DISABLED_, TypedTestTypes);
IUTEST_TYPED_TEST_SUITE(DISABLED_TypedFoo , TypedTestTypes);

IUTEST_TYPED_TEST(TypedFoo_DISABLED_, Bar)
{
}

IUTEST_TYPED_TEST(TypedFoo, DISABLED_Bar)
{
    IUTEST_FAIL();
}

IUTEST_TYPED_TEST(DISABLED_TypedFoo, Bar)
{
    IUTEST_FAIL();
}

#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypePFoo : public ::iutest::Test {};
template<typename T>
class TypedPFoo_DISABLED_ : public ::iutest::Test {};
template<typename T>
class DISABLED_TypedPFoo : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(TypePFoo);
IUTEST_TYPED_TEST_SUITE_P(TypedPFoo_DISABLED_);
IUTEST_TYPED_TEST_SUITE_P(DISABLED_TypedPFoo);

IUTEST_TYPED_TEST_P(TypedPFoo_DISABLED_, Bar)
{
}

IUTEST_TYPED_TEST_P(TypePFoo, DISABLED_Bar)
{
    IUTEST_FAIL();
}

IUTEST_TYPED_TEST_P(DISABLED_TypedPFoo, Bar)
{
    IUTEST_FAIL();
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypedPFoo_DISABLED_, Bar);
IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypePFoo, DISABLED_Bar);
IUTEST_REGISTER_TYPED_TEST_SUITE_P(DISABLED_TypedPFoo, Bar);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, TypedPFoo_DISABLED_, int);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, TypePFoo, int);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, DISABLED_TypedPFoo, int);

#endif

int GetExpectedTestCount()
{
    int expected_test_count = 4;
#if IUTEST_HAS_PARAM_TEST
    expected_test_count += 6;
#endif
#if IUTEST_HAS_PARAM_METHOD_TEST
    expected_test_count += 6;
#endif
#if IUTEST_HAS_TYPED_TEST
    expected_test_count += 3;
#endif
#if IUTEST_HAS_TYPED_TEST_P
    expected_test_count += 3;
#endif
    return expected_test_count;
}

int GetExpectedDisableTestCount()
{
    int expected_disable_test_count = 2;
#if IUTEST_HAS_PARAM_TEST
    expected_disable_test_count += 4;
#endif
#if IUTEST_HAS_PARAM_METHOD_TEST
    expected_disable_test_count += 4;
#endif
#if IUTEST_HAS_TYPED_TEST
    expected_disable_test_count += 2;
#endif
#if IUTEST_HAS_TYPED_TEST_P
    expected_disable_test_count += 2;
#endif
    return expected_disable_test_count;
}

static const int expected_test_count = GetExpectedTestCount();
static const int expected_disable_test_count = GetExpectedDisableTestCount();
