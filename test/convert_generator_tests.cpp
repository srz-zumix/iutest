//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        convert_generator_tests.cpp
 * @brief       test ::iutest::ConvertGenerator
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"
#include "main.cpp"

#if IUTEST_HAS_CONVERT_GENERATOR && IUTEST_HAS_COMBINE

namespace convert_generator_test
{

typedef ::iutest::tuples::tuple<int, int> Pair;

struct ExplicitParam
{
    ExplicitParam() : first(0), second(0) {}
    explicit ExplicitParam(const Pair& pair)
        : first(::iutest::tuples::get<0>(pair)), second(::iutest::tuples::get<1>(pair)) {}

    int first;
    int second;
};

class ConvertGeneratorTest : public ::iutest::TestWithParam<ExplicitParam> {};

IUTEST_P(ConvertGeneratorTest, ConvertsCombinedValues)
{
    IUTEST_EXPECT_EQ(1, GetParam().first);
    IUTEST_EXPECT_TRUE(GetParam().second == 2 || GetParam().second == 3);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Explicit, ConvertGeneratorTest,
    ::iutest::ConvertGenerator<Pair>(
        ::iutest::Combine(::iutest::Values(1), ::iutest::Values(2, 3))));

struct ExplicitInt
{
    ExplicitInt() : value(0) {}
    explicit ExplicitInt(int n) : value(n) {}

    int value;
};

class ConvertIntTest : public ::iutest::TestWithParam<ExplicitInt> {};

IUTEST_P(ConvertIntTest, ConvertsValues)
{
    IUTEST_EXPECT_TRUE(GetParam().value == 2 || GetParam().value == 3);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Range, ConvertIntTest,
    ::iutest::ConvertGenerator<int>(::iutest::Range(2, 4)));
IUTEST_INSTANTIATE_TEST_SUITE_P(Values, ConvertIntTest,
    ::iutest::ConvertGenerator<int>(::iutest::Values(2, 3)));

#if IUTEST_HAS_CONVERT_GENERATOR_FUNC

struct MakeParam
{
    ExplicitParam operator()(const Pair& pair) const
    {
        return ExplicitParam(pair);
    }
};

IUTEST_INSTANTIATE_TEST_SUITE_P(Callable, ConvertGeneratorTest,
    ::iutest::ConvertGenerator(
        ::iutest::Combine(::iutest::Values(1), ::iutest::Values(2, 3)), MakeParam()));

static ExplicitInt Increment(int value)
{
    return ExplicitInt(value + 1);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Function, ConvertIntTest,
    ::iutest::ConvertGenerator(::iutest::Values(1, 2), Increment));

#endif

}   // end of namespace convert_generator_test

#endif
