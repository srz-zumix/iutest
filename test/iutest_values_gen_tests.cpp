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

#if !defined(_MSC_VER)

IUTEST_INSTANTIATE_TEST_CASE_P(Random, ValuesGenTest, ::iutest::ValuesGen(5,
	[]() {
		struct {
			::std::mt19937 engine;
			int operator ()(void)
			{
				::std::uniform_int_distribution<int> dist(0, 1000);
				for(;;)
				{
					int n = dist(engine);
					if( n != 10 && n != 50 && n != 100 && n != 500 ) return n;
				}
			}
		} g;
		return g;
	}()
	));
	
#endif

/*
IUTEST_INSTANTIATE_TEST_CASE_P(Random, ValuesGenTest, ::iutest::ValuesIn(
	[](int n) {
		struct {
			::std::mt19937 engine;
			int operator ()(void)
			{
				::std::uniform_int_distribution<int> dist(0, 1000);
				for(;;)
				{
					int n = dist(engine);
					if( n != 10 && n != 50 && n != 100 && n != 500 ) return n;
				}
			}
		} g;
		::std::vector<int> v(n);
		::std::generate(v.begin(), v.end(), g);
		return v;
	}(5)
	));
*/

#endif

bool VMExceptMoney(int n) { return n != 10 && n != 50 && n != 100 && n != 500; }

struct RandomVMExceptMoneyGenerator
{
	::iutest::detail::iuRandom engine;
	int operator ()(void)
	{
		for(;;)
		{
			int n =  engine() % 1000;
			if( VMExceptMoney(n) ) return n;
		}
	}
};

#if IUTEST_HAS_LAMBDA
IUTEST_INSTANTIATE_TEST_CASE_P(RandomGen_lambda, ValuesGenTest, ::iutest::ValuesGen(5, ::iutest::RandomGenerator<int>([](int n){ return n != 10 && n != 50 && n != 100 && n != 500; })));
#endif

IUTEST_INSTANTIATE_TEST_CASE_P(Random03_00, ValuesGenTest, ::iutest::ValuesGen(5, RandomVMExceptMoneyGenerator()));
IUTEST_INSTANTIATE_TEST_CASE_P(Random03_01, ValuesGenTest, ::iutest::ValuesGen(5, ::iutest::RandomGenerator<int>(&VMExceptMoney)));

::std::vector<int> RandomVMExceptMoneyParams(int n)
{
    ::std::vector<int> v(n);
    ::std::generate(v.begin(), v.end(), RandomVMExceptMoneyGenerator());
    return v;
}

IUTEST_INSTANTIATE_TEST_CASE_P(Random03_2, ValuesGenTest, ::iutest::ValuesIn(RandomVMExceptMoneyParams(5)));

#endif
