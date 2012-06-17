//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_test_tests.cpp
 * @brief		テストが無いときの結果 対応テスト
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

#if IUTEST_HAS_COMBINE

static const int tble[] = {0, 1};

class CombineTest : public ::iutest::TestWithParam< ::iutest::tuple::tuple<bool, int, int> >
{
public:
	typedef ::iutest::tuple::tuple<bool, int, int> Tuple;
	static const int TABLE_SIZE = sizeof(tble)/sizeof(tble[0]);

	static int index;
	static Tuple list[2*2*TABLE_SIZE];
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
	EXPECT_EQ( 2*2*TABLE_SIZE, ::iutest::UnitTest::GetInstance()->current_test_case()->total_test_count() );
	EXPECT_EQ( list[index++], GetParam() );
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, CombineTest
	, ::iutest::Combine(::iutest::Bool(), ::iutest::Values(1, 10), ::iutest::ValuesIn(tble)));


#if IUTEST_HAS_VARIADIC_COMBINE

namespace variadic_combine_test
{

typedef ::iutest::tuple::tuple<int, int, int, int, int, int, int, int, int, int> VariadicCombineTestTuple;

static const int TUPLE_SIZE = ::iutest::tuple::tuple_size< VariadicCombineTestTuple >::value;
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
		return ::iutest::tuple::make_tuple(
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
	EXPECT_EQ( num, ::iutest::UnitTest::GetInstance()->current_test_case()->total_test_count() );
	EXPECT_EQ( count_to_tuple(count++), GetParam() );
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, VariadicCombineTest
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

}


#endif

#endif

