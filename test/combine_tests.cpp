//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        combine_tests.cpp
 * @brief       test ;;iutest::Combine
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

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_COMBINE

static const int tble[] = {0, 1};

class CombineTest : public ::iutest::TestWithParam< ::iutest::tuples::tuple<bool, int, int> >
{
public:
    typedef ::iutest::tuples::tuple<bool, int, int> Tuple;
    static const int TABLE_SIZE = sizeof(tble)/sizeof(tble[0]);

    static int index;
    static Tuple list[2*2*TABLE_SIZE];

public:
    static void SetUpTestSuite(void) { index = 0; }
};

int CombineTest::index = 0;
CombineTest::Tuple CombineTest::list[2*2*CombineTest::TABLE_SIZE] = {
    CombineTest::Tuple(false, 1, 0)
    , CombineTest::Tuple(false, 1, 1)
    , CombineTest::Tuple(false, 10, 0)
    , CombineTest::Tuple(false, 10, 1)
    , CombineTest::Tuple(true, 1, 0)
    , CombineTest::Tuple(true, 1, 1)
    , CombineTest::Tuple(true, 10, 0)
    , CombineTest::Tuple(true, 10, 1)
};

IUTEST_P(CombineTest, Num)
{
    IUTEST_EXPECT_EQ( (2*2*TABLE_SIZE) * 2, ::iuutil::GetCurrentTestSuite()->total_test_count() );
}

IUTEST_P(CombineTest, Param)
{
    IUTEST_EXPECT_EQ( list[index++], GetParam() );
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, CombineTest
    , ::iutest::Combine(::iutest::Bool(), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble)));
#if IUTEST_HAS_CONCAT
IUTEST_INSTANTIATE_TEST_SUITE_P(B, CombineTest
    , ::iutest::Concat(
        ::iutest::Combine(::iutest::Values(false), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble))
        , ::iutest::Combine(::iutest::Values(true), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble))
    )
    );
IUTEST_INSTANTIATE_TEST_SUITE_P(C, CombineTest
    , ::iutest::Combine(::iutest::Values(false), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble))
        + ::iutest::Combine(::iutest::Values(true), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble))
    );
#endif


class CombineInTest : public ::iutest::TestWithParam< ::iutest::tuples::tuple< ::iutest::tuples::tuple<bool, int>, int > >
{
};

IUTEST_P(CombineInTest, A)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, CombineInTest
    , ::iutest::Combine( ::iutest::Combine(::iutest::Bool(), ::iutest::Values(1, 10)), ::iutest::ValuesIn(tble)) );
IUTEST_INSTANTIATE_TEST_SUITE_P(B, CombineInTest
    , ::iutest::Combine( ::iutest::Values( ::iutest::tuples::tuple<bool, int>(false, 1), ::iutest::tuples::tuple<bool, int>(true, 10) )
        , ::iutest::ValuesIn(tble)) );


#if IUTEST_HAS_VARIADIC_COMBINE

namespace variadic_combine_test
{

typedef ::iutest::tuples::tuple<int, int, int, int, int, int, int, int, int, int> VariadicCombineTestTuple;

static const int TUPLE_SIZE = ::iutest::tuples::tuple_size< VariadicCombineTestTuple >::value;
static const int test_table[] = { 0, 1 };
static const int TABLE_SIZE = sizeof(test_table)/sizeof(test_table[0]);

class VariadicCombineTest : public ::iutest::TestWithParam< VariadicCombineTestTuple >
{
    static int power(int n, int c) { return c == 0 ? 1 : power(n, c-1) * n; }
public:
    static int num;
    static int count;

    static VariadicCombineTestTuple count_to_tuple(int c)
    {
        return ::iutest::tuples::make_tuple(
            (c>>(TUPLE_SIZE-1))&1
            , (c>>(TUPLE_SIZE-2))&1
            , (c>>(TUPLE_SIZE-3))&1
            , (c>>(TUPLE_SIZE-4))&1
            , (c>>(TUPLE_SIZE-5))&1
            , (c>>(TUPLE_SIZE-6))&1
            , (c>>(TUPLE_SIZE-7))&1
            , (c>>(TUPLE_SIZE-8))&1
            , (c>>(TUPLE_SIZE-9))&1
            , (c>>(TUPLE_SIZE-10))&1
        );
    }
};
int VariadicCombineTest::num = power(TABLE_SIZE, TUPLE_SIZE);
int VariadicCombineTest::count = 0;

IUTEST_P(VariadicCombineTest, Num)
{
    IUTEST_EXPECT_EQ( num, ::iuutil::GetCurrentTestSuite()->total_test_count() );
    IUTEST_EXPECT_EQ( count_to_tuple(count++), GetParam() );
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, VariadicCombineTest
    , ::iutest::Combine(::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
        , ::iutest::ValuesIn(test_table)
    ));

}   // end of namespace variadic_combine_test

#endif

#endif

