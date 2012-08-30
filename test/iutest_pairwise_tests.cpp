//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_pairwise_tests.cpp
 * @brief		Pairwise ‘Î‰ƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_PAIRWISE

typedef ::iutest::tuples::tuple<int, int, int, int, int, int, int, int, int> PairwiseTestTuple;

class PairwiseTest : public ::iutest::TestWithParam< PairwiseTestTuple >
{
};

IUTEST_P(PairwiseTest, Num)
{
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
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, PairwiseTest
	, ::iutest::Pairwise(::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
	));

#if IUTEST_HAS_VARIADIC_PAIRWISE

typedef ::iutest::tuples::tuple<int, int, int, int, int, int, int, int, int, int> VariadicPairwiseTestTuple;

class VariadicPairwiseTest : public ::iutest::TestWithParam< VariadicPairwiseTestTuple >
{
};

IUTEST_P(VariadicPairwiseTest, Num)
{
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
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, VariadicPairwiseTest
	, ::iutest::Pairwise(::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
		, ::iutest::Range(0,2)
	));


#endif

#endif


