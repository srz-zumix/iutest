﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        empty_testname_failure_tests.cpp
 * @brief       iutest empty testname static_assert test
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

// ill-formed test definitions..

IUTEST_TEST_STATICASSERT("static_assert: testsuite_ must not be empty")
IUTEST(, Test)
{
}

IUTEST_TEST_STATICASSERT("static_assert: testname_ must not be empty")
IUTEST(Test, )
{
}

class BaseFixture : public ::iutest::Test
{
};

IUTEST_TEST_STATICASSERT("static_assert: testname_ must not be empty")
IUTEST_F(BaseFixture, )
{
}

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
namespace fixture_alias
{

IUTEST_TEST_STATICASSERT("static_assert: testsuite_ must not be empty")
IUTEST_F((, BaseFixture), Test)
{
}

}
#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(TypeParamTest);
IUTEST_TEST_STATICASSERT("static_assert: testname_ must not be empty")
IUTEST_TYPED_TEST_P(TypeParamTest, )
{
}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, );

typedef ::iutest::Types<int, float> TypeParamTestTypes;
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My1, TypeParamTest, TypeParamTestTypes);

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