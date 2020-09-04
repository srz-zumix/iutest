//======================================================================
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

#if defined(IUTEST_PP_MSVC_TRADITIONAL)
#  define ENABLE_EMPTY_NAMETEST 0
#endif

#if !defined(ENABLE_EMPTY_NAMETEST)
#  define ENABLE_EMPTY_NAMETEST 1
#endif

#if ENABLE_EMPTY_NAMETEST

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, )
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, ParamTest, ::iutest::Values(0, 1));

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
typedef ParamTest   ParamTest2;
#define ParamTestAlias  (, ParamTest2)
IUTEST_P(ParamTestAlias, )
{
}
IUTEST_INSTANTIATE_TEST_SUITE_P(A, ParamTestAlias, ::iutest::Values(0, 1));
#endif

#endif

#if IUTEST_HAS_ANY_PARAM_TEST

IUTEST_AP(AnyParamTest, )
{
}

IUTEST_INSTANTIATE_TEST_SUITE_AP(My1, AnyParamTest, ::iutest::Values(0));

#endif

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
