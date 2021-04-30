//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pairwise_seed_tests.cpp
 * @brief       Pairwise same seed test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#define IUTEST_USE_OWN_SHUFFLE  1
#include "iutest.hpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PAIRWISE

typedef ::iutest::tuples::tuple<int, int, int> PairwiseTestTuple;

static const int N1 = 2;
static const int N2 = 2;
static const int N3 = 3;

bool golden[2][N1][N2][N3] = {
    {
        {
            { false,  true,  true },
            {  true, false,  true },
        },
        {
            {  true, false,  true },
            { false,  true, false },
        }
    },
    {
        {
            { false,  true,  true },
            {  true, false, false },
        },
        {
            {  true, false,  true },
            { false,  true,  true },
        }
    }
};

class PairwiseTest : public ::iutest::TestWithParam< PairwiseTestTuple >
{
public:
    static void SetUpTestCase(void)
    {
        for( int n1=0; n1 < N1; ++n1 )
        {
            for( int n2=0; n2 < N2; ++n2 )
            {
                for( int n3=0; n3 < N3; ++n3 )
                {
                    mtx[n][n1][n2][n3] = false;
                }
            }
        }
    }
    static void TearDownTestCase(void)
    {
#if 0
        for( int n1=0; n1 < N1; ++n1 )
        {
            for( int n2=0; n2 < N2; ++n2 )
            {
                for( int n3=0; n3 < N3; ++n3 )
                {
                    if( mtx[n][n1][n2][n3] )
                    {
                        IUTEST_LOG_(INFO) << n1 << ", " << n2 << ", " << n3;
                    }
                }
            }
        }
#endif
        ++n;
    }
public:
    static int n;
    static bool mtx[2][N1][N2][N3];
};

int PairwiseTest::n = 0;
bool PairwiseTest::mtx[2][N1][N2][N3];

IUTEST_P(PairwiseTest, Num)
{
    const PairwiseTestTuple param = GetParam();
    mtx[n][::iutest::tuples::get<0>(param)][::iutest::tuples::get<1>(param)][::iutest::tuples::get<2>(param)] = true;
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, PairwiseTest
    , ::iutest::Pairwise(::iutest::Range(0, 2), ::iutest::Range(0, 2), ::iutest::Range(0, 3)) );
IUTEST_INSTANTIATE_TEST_SUITE_P(B, PairwiseTest
    , ::iutest::Pairwise(::iutest::Range(0, 2), ::iutest::Range(0, 2), ::iutest::Range(0, 3)) );

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    ::iutest::detail::iuRandom rnd;
    ::iutest::IUTEST_FLAG(random_seed) = 9;
    IUTEST_INIT(&argc, argv);
    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 )
    {
        return 1;
    }

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PAIRWISE
    IUTEST_ASSERT_EXIT((memcmp(PairwiseTest::mtx[0], PairwiseTest::mtx[1], sizeof(PairwiseTest::mtx[0])) != 0));
    IUTEST_ASSERT_EXIT((memcmp(golden, PairwiseTest::mtx, sizeof(PairwiseTest::mtx)) == 0));
#endif
    return 0;
}
