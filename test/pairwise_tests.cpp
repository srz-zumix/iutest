//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pairwise_tests.cpp
 * @brief       Pairwise test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PAIRWISE

typedef ::iutest::tuples::tuple<int, int> PairwiseTest2Tuple;

class PairwiseTest2 : public ::iutest::TestWithParam< PairwiseTest2Tuple >
{
public:
    static void SetUpTestCase(void)
    {
        mtx[0][0] = mtx[0][1] = mtx[1][0] = mtx[1][1] = false;
    }
    static void TearDownTestCase(void)
    {
        IUTEST_EXPECT_TRUE(mtx[0][0]);
        IUTEST_EXPECT_TRUE(mtx[0][1]);
        IUTEST_EXPECT_TRUE(mtx[1][0]);
        IUTEST_EXPECT_TRUE(mtx[1][1]);
    }
protected:
    static bool mtx[2][2];
};

bool PairwiseTest2::mtx[2][2];

IUTEST_P(PairwiseTest2, Num)
{
    const PairwiseTest2Tuple param = GetParam();
    mtx[::iutest::tuples::get<0>(param)][::iutest::tuples::get<1>(param)] = true;
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, PairwiseTest2
    , ::iutest::Pairwise(::iutest::Range(0, 2), ::iutest::Range(0, 2)) );


typedef ::iutest::tuples::tuple<int, int, int, int, int, int, int, int, int> PairwiseTestTuple;

class PairwiseTest : public ::iutest::TestWithParam< PairwiseTestTuple >
{
};

IUTEST_P(PairwiseTest, Num)
{
#ifndef USE_PROGRESS
    PairwiseTestTuple param = GetParam();
    printf("%d %d %d %d %d %d %d %d %d\n"
        , ::iutest::tuples::get<0>(param)
        , ::iutest::tuples::get<1>(param)
        , ::iutest::tuples::get<2>(param)
        , ::iutest::tuples::get<3>(param)
        , ::iutest::tuples::get<4>(param)
        , ::iutest::tuples::get<5>(param)
        , ::iutest::tuples::get<6>(param)
        , ::iutest::tuples::get<7>(param)
        , ::iutest::tuples::get<8>(param)
    );
#endif
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, PairwiseTest
    , ::iutest::Pairwise(
          ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
    ));
#if IUTEST_HAS_CONCAT
IUTEST_INSTANTIATE_TEST_SUITE_P(B, PairwiseTest
    , ::iutest::Concat(
        ::iutest::Pairwise(
              ::iutest::Range(0, 1)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
        ),
        ::iutest::Pairwise(
              ::iutest::Range(1, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
            , ::iutest::Range(0, 2)
        )
    )
    );
IUTEST_INSTANTIATE_TEST_SUITE_P(C, PairwiseTest
    , ::iutest::Pairwise(
          ::iutest::Range(0, 1)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
    ) + ::iutest::Pairwise(
          ::iutest::Range(1, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
    )
    );
#endif

#if IUTEST_HAS_VARIADIC_PAIRWISE

typedef ::iutest::tuples::tuple<int, int, int, int, int, int, int, int, int, int> VariadicPairwiseTestTuple;

class VariadicPairwiseTest : public ::iutest::TestWithParam< VariadicPairwiseTestTuple >
{
};

IUTEST_P(VariadicPairwiseTest, Num)
{
#ifndef USE_PROGRESS
    VariadicPairwiseTestTuple param = GetParam();
    printf("%d %d %d %d %d %d %d %d %d %d\n"
        , ::iutest::tuples::get<0>(param)
        , ::iutest::tuples::get<1>(param)
        , ::iutest::tuples::get<2>(param)
        , ::iutest::tuples::get<3>(param)
        , ::iutest::tuples::get<4>(param)
        , ::iutest::tuples::get<5>(param)
        , ::iutest::tuples::get<6>(param)
        , ::iutest::tuples::get<7>(param)
        , ::iutest::tuples::get<8>(param)
        , ::iutest::tuples::get<9>(param)
    );
#endif
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, VariadicPairwiseTest
    , ::iutest::Pairwise(
          ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
        , ::iutest::Range(0, 2)
    ));


#endif

#endif


