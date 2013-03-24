//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_values_gen_tests.cpp
 * @brief		iutest ValuesGen test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_VALUESGEN

class ValuesGenTest : public ::iutest::TestWithParam<int>
{
public:
	struct Gen
	{
		int i;
		Gen(int n) : i(n) {}
		int operator ()(void) { return i++; }
	};
};

IUTEST_P(ValuesGenTest, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, ValuesGenTest, ::iutest::ValuesGen(5, ValuesGenTest::Gen(0)));

#if IUTEST_HAS_LAMBDA && IUTEST_HAS_CXX_HDR_RANDOM

IUTEST_INSTANTIATE_TEST_CASE_P(Random, ValuesGenTest, ::iutest::ValuesGen(5,
	[]() {
		struct gen {
			::std::mt19937 engine;
			int operator ()(void)
			{
				for(;;)
				{
					int n = ::std::uniform_int_distribution<int>(0, 1000)(engine);
					if( n != 10 && n != 50 && n != 100 && n != 500 ) return n;
				}
			}
		} g;
		return g;
	}()
	));

#endif

struct RandomVMExceptMoneyGenerator
{
	::iutest::detail::iuRandom engine;
	int operator ()(void)
	{
		for(;;)
		{
			int n =  engine() % 1000;
			if( n != 10 && n != 50 && n != 100 && n != 500 ) return n;
		}
	}
};

IUTEST_INSTANTIATE_TEST_CASE_P(Random03, ValuesGenTest, ::iutest::ValuesGen(5, RandomVMExceptMoneyGenerator()));

#endif
