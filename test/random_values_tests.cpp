//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        random_values_tests.cpp
 * @brief       iutest random values test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_GENRAND && IUTEST_HAS_CXX_HDR_RANDOM
IUTEST(RandomEngineTest, Test)
{
    IUTEST_ASSERT_LE(::std::uniform_int_distribution<unsigned int>(0, 1)(random_engine()), 1u);
}
#endif

#if IUTEST_HAS_RANDOMVALUES

class RandomValuesTest1 : public ::iutest::TestWithParam<int> {};
class RandomValuesTest2 : public ::iutest::TestWithParam<char> {};
class RandomValuesTest3 : public ::iutest::TestWithParam<float> {};

IUTEST_P(RandomValuesTest1, Test)
{
    const int v = GetParam();
    IUTEST_SUCCEED() << v;
}
IUTEST_P(RandomValuesTest2, Test)
{
    const char v = GetParam();
    IUTEST_SUCCEED() << ::iutest::PrintToString(v);
}
IUTEST_P(RandomValuesTest3, Test)
{
    const float v = GetParam();
    IUTEST_ASSERT_GE(1, v);
    IUTEST_ASSERT_LE(0, v);
    IUTEST_SUCCEED() << v;
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, RandomValuesTest1, ::iutest::RandomValues(5));
IUTEST_INSTANTIATE_TEST_SUITE_P(A, RandomValuesTest2, ::iutest::RandomValues(5));
IUTEST_INSTANTIATE_TEST_SUITE_P(A, RandomValuesTest3, ::iutest::RandomValues(5));

#endif
