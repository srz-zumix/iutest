//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        ignore_tests.cpp
 * @brief       IUTEST_*_IGNORE 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_IGNORE_TEST

IUTEST_IGNORE(IgnoreTest, A)
{
    VedningMachine vm;
    vm.Insert(100);
    IUTEST_ASSERT_EQ(100, vm.GetTotalAmount());
}

class IgnoreTestF : public ::iutest::Test {};
IUTEST_F_IGNORE(IgnoreTestF, A)
{
    VedningMachine vm;
    vm.Insert(100);
    IUTEST_ASSERT_EQ(100, vm.GetTotalAmount());
}

#if IUTEST_HAS_PARAM_TEST

class IgnoreParamTest : public ::iutest::TestWithParam<int> {};
IUTEST_P_IGNORE(IgnoreParamTest, A)
{
    int n = GetParam();
    VedningMachine vm;
    vm.Insert(n);
    IUTEST_ASSERT_EQ(n, vm.GetTotalAmount());
}

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class IgnoreTypedTest : public ::iutest::Test {};

typedef ::iutest::Types<int, long, short> IgnoreTypedTestTypes;
IUTEST_TYPED_TEST_SUITE(IgnoreTypedTest, IgnoreTypedTestTypes);

IUTEST_TYPED_TEST_IGNORE(IgnoreTypedTest, A)
{
    VedningMachine vm;
    vm.Insert(100);
    IUTEST_ASSERT_EQ(100, vm.GetTotalAmount());
}

#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class IgnoreTypedTestP : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(IgnoreTypedTestP);

IUTEST_TYPED_TEST_P_IGNORE(IgnoreTypedTestP, A)
{
    VedningMachine vm;
    vm.Insert(100);
    IUTEST_ASSERT_EQ(100, vm.GetTotalAmount());
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(IgnoreTypedTestP, A);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(I, IgnoreTypedTestP, int);


#endif

#endif

