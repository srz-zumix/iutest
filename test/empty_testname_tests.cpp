﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        empty_testname_tests.cpp
 * @brief       iutest empty testname allow test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

// well-formed test definitions..

IUTEST(, )
{
}

class BaseFixture : public ::iutest::Test
{
public:
    static void SetUpTestSuite()
    {
        ::iutest::Test::SetUpTestSuite();
    }
    static void TearDownTestSuite()
    {
        ::iutest::Test::TearDownTestSuite();
    }
};

IUTEST_F(BaseFixture, )
{
}

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
namespace fixture_alias
{

IUTEST_F((, BaseFixture), )
{
}

}
#endif

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, )
{
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, ParamTest, ::iutest::Values(0, 1));

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
typedef ParamTest   ParamTest2;
#define ParamTestAlias  (, ParamTest2)
IUTEST_P(ParamTestAlias, )
{
}
IUTEST_INSTANTIATE_TEST_CASE_P(A, ParamTestAlias, ::iutest::Values(0, 1));
#endif

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

typedef ::iutest::Types<int, float> TypedTestTypes;
IUTEST_TYPED_TEST_CASE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, )
{
}

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
template<typename T>
class TypedTest2 : public ::iutest::Test {};
#define TypedTestAlias  (, TypedTest2)
IUTEST_TYPED_TEST_CASE(TypedTestAlias, TypedTestTypes);
IUTEST_TYPED_TEST(TypedTestAlias, )
{
}
#endif

#endif

#if IUTEST_HAS_ANY_PARAM_TEST

IUTEST_AP(AnyParamTest, )
{
}

IUTEST_INSTANTIATE_TEST_CASE_AP(My1, AnyParamTest, ::iutest::Values(0));

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
