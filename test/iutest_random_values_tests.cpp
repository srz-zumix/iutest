//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_random_values_tests.cpp
 * @brief		iutest random values test
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

#if !defined(IUTEST_USE_GTEST)

#if IUTEST_HAS_PARAM_TEST

class RandomValuesTest1 : public ::iutest::TestWithParam<int> {};
class RandomValuesTest2 : public ::iutest::TestWithParam<char> {};
class RandomValuesTest3 : public ::iutest::TestWithParam<float> {};

IUTEST_P(RandomValuesTest1, Test)
{
	int v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_P(RandomValuesTest2, Test)
{
	char v = GetParam();
	IUTEST_SUCCEED() << v;
}
IUTEST_P(RandomValuesTest3, Test)
{
	float v = GetParam();
	IUTEST_ASSERT_GE(1, v);
	IUTEST_ASSERT_LE(0, v);
	IUTEST_SUCCEED() << v;
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, RandomValuesTest1, ::iutest::RandomValues(5));
IUTEST_INSTANTIATE_TEST_CASE_P(A, RandomValuesTest2, ::iutest::RandomValues(5));
IUTEST_INSTANTIATE_TEST_CASE_P(A, RandomValuesTest3, ::iutest::RandomValues(5));

#endif

#endif
