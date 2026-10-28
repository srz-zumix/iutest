//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_macro_tests.cpp
 * @brief       Matcher definition macro tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHER_MACROS

namespace {

IUTEST_MATCHER(IsEven, "")
{
    const arg_type remainder = arg % 2;
    if( result_listener->IsInterested() )
    {
        *result_listener << "remainder ";
        *result_listener->stream() << remainder;
    }
    return remainder == 0;
}

IUTEST_MATCHER(IsPositive, negation ? "is not positive" : "is positive")
{
    return arg > 0;
}

IUTEST_MATCHER_P(IsDivisibleBy, n, "")
{
    const n_type divisor = n;
    return arg % divisor == 0;
}

IUTEST_MATCHER_P(HasValue, value, ::std::string(negation ? "does not equal " : "equals ") + ::iutest::PrintToString(value))
{
    return arg == value;
}

IUTEST_MATCHER_P2(IsBetween, low, high, "")
{
    const low_type lower = low;
    const high_type upper = high;
    return lower <= arg && arg <= upper;
}

IUTEST_MATCHER_P3(HasSum, a, b, c, "") { return arg == a + b + c; }
IUTEST_MATCHER_P4(HasSum, a, b, c, d, "") { return arg == a + b + c + d; }
IUTEST_MATCHER_P5(HasSum, a, b, c, d, e, "") { return arg == a + b + c + d + e; }
IUTEST_MATCHER_P6(HasSum, a, b, c, d, e, f, "") { return arg == a + b + c + d + e + f; }
IUTEST_MATCHER_P7(HasSum, a, b, c, d, e, f, g, "") { return arg == a + b + c + d + e + f + g; }
IUTEST_MATCHER_P8(HasSum, a, b, c, d, e, f, g, h, "") { return arg == a + b + c + d + e + f + g + h; }
IUTEST_MATCHER_P9(HasSum, a, b, c, d, e, f, g, h, i, "") { return arg == a + b + c + d + e + f + g + h + i; }
IUTEST_MATCHER_P10(HasSum, a, b, c, d, e, f, g, h, i, j, "") { return arg == a + b + c + d + e + f + g + h + i + j; }

MATCHER(IsZero, "") { return arg == 0; }
MATCHER_P(IsEqualTo, value, "") { return arg == value; }
MATCHER_P2(IsSumOf, a, b, "") { return arg == a + b; }

IUTEST_MATCHER(Is_HTTP2_ready, "") { return arg; }

IUTEST_MATCHER_P(IsExplainedBy, inner, "")
{
#if defined(IUTEST_USE_GTEST)
    return ::testing::ExplainMatchResult(inner, arg, result_listener);
#else
    return ::iutest::matchers::ExplainMatchResult(inner, arg, result_listener);
#endif
}

IUTEST_MATCHER_P(EqualsStreamParameter, os, "") { return arg == os; }

} // namespace

IUTEST(MatcherMacro, Match)
{
    IUTEST_EXPECT_THAT(4, IsEven());
    IUTEST_EXPECT_THAT(2L, IsEven());
    IUTEST_EXPECT_THAT(10, IsDivisibleBy(5));
    IUTEST_EXPECT_THAT(2, IsBetween(1, 3L));
    IUTEST_EXPECT_THAT(6, HasSum(1, 2, 3));
    IUTEST_EXPECT_THAT(10, HasSum(1, 2, 3, 4));
    IUTEST_EXPECT_THAT(15, HasSum(1, 2, 3, 4, 5));
    IUTEST_EXPECT_THAT(21, HasSum(1, 2, 3, 4, 5, 6));
    IUTEST_EXPECT_THAT(28, HasSum(1, 2, 3, 4, 5, 6, 7));
    IUTEST_EXPECT_THAT(36, HasSum(1, 2, 3, 4, 5, 6, 7, 8));
    IUTEST_EXPECT_THAT(45, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9));
    IUTEST_EXPECT_THAT(55, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
    IUTEST_EXPECT_THAT(0, IsZero());
    IUTEST_EXPECT_THAT(1, IsEqualTo(1));
    IUTEST_EXPECT_THAT(3, IsSumOf(1, 2));
    IUTEST_EXPECT_THAT(::std::string("abc"), HasValue(::std::string("abc")));
    IUTEST_EXPECT_THAT(2, IsExplainedBy(IsEven()));
    IUTEST_EXPECT_THAT(3, EqualsStreamParameter(3));
}

IUTEST(MatcherMacro, FailureDescriptions)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "is even");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(-1, IsPositive()), "is positive");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, IsDivisibleBy(3)), "is divisible by (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, IsDivisibleBy(3)), "3)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, IsBetween(1, 3)), "is between (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(1, HasValue(2)), "equals 2");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(0, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
        "10)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(false, Is_HTTP2_ready()), "is h t t p 2 ready");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsExplainedBy(IsEven())), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(2, EqualsStreamParameter(3)), "3)");
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(4, IsBetween(1, 3)), "is between (low: 1, high: 3)");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(0, HasSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
        "has sum (a: 1, b: 2, c: 3, d: 4, e: 5, f: 6, g: 7, h: 8, i: 9, j: 10)");
#endif
}

IUTEST(MatcherMacro, CompositionAndNegation)
{
    using ::iutest::matchers::Not;
    IUTEST_EXPECT_THAT(3, Not(IsEven()));
#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
    IUTEST_EXPECT_THAT(2, ::iutest::matchers::AllOf(IsEven(), IsPositive()));
    IUTEST_EXPECT_THAT(5, ::iutest::matchers::AnyOf(IsEven(), IsPositive()));
#endif
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, Not(IsEven())), "not (is even)");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(1, Not(IsPositive())), "is not positive");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, Not(IsDivisibleBy(5))), "not (is divisible by (");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(10, Not(IsDivisibleBy(5))), "5))");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(2, Not(HasValue(2))), "does not equal 2");
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(MatcherMacro, UninterestedListener)
{
    IUTEST_EXPECT_TRUE(IsEven().MatchAndExplain(4, NULL));
    IUTEST_EXPECT_FALSE(IsEven().MatchAndExplain(3, NULL));
    IUTEST_EXPECT_FALSE(IsExplainedBy(IsEven()).MatchAndExplain(3, NULL));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
