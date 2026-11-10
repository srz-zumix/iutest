//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        args_matcher_tests.cpp
 * @brief       Args and AllArgs matcher tests
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

#if IUTEST_HAS_MATCHERS && IUTEST_HAS_STD_TUPLE \
    && (IUTEST_HAS_VARIADIC_TEMPLATES || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX11))
#include <memory>
#include <tuple>

using ::iutest::matchers::AllArgs;
using ::iutest::matchers::Args;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Le;
using ::iutest::matchers::Lt;
using ::iutest::matchers::Ne;
using ::iutest::matchers::Not;

namespace {

const ::std::tuple<int, int, int> failure_tuple(3, 2, 1);

}   // end of namespace

IUTEST(ArgsMatcher, SelectArguments)
{
    const ::std::tuple<int, int, int> actual(1, 2, 3);
    IUTEST_EXPECT_THAT(actual, (Args<0, 2>(Lt())));
    IUTEST_EXPECT_THAT(actual, (Args<2, 0>(Gt())));
    IUTEST_EXPECT_THAT(actual, (Args<1, 1>(Eq())));
    IUTEST_EXPECT_THAT(actual, (Args<0, 2>(Ne())));
    IUTEST_EXPECT_THAT(actual, (Args<1, 1>(Le())));
    IUTEST_EXPECT_THAT(actual, (Args<1, 1>(Ge())));
    IUTEST_EXPECT_THAT(actual, (Args<2, 0, 1>(Eq(::std::make_tuple(3, 1, 2)))));
    IUTEST_EXPECT_THAT(actual, (Args<1>(Eq(::std::make_tuple(2)))));
    IUTEST_EXPECT_THAT(actual, (Args<>(Eq(::std::tuple<>()))));
    IUTEST_EXPECT_THAT(::std::tuple<>(), (Args<>(Eq(::std::tuple<>()))));
}

IUTEST(ArgsMatcher, NestedMatchers)
{
    const ::std::tuple<int, int, int> actual(1, 2, 3);
    IUTEST_EXPECT_THAT(actual, (Not(Args<2, 0>(Lt()))));
    IUTEST_EXPECT_THAT(actual, (Args<2, 0, 1>(Args<1, 0>(Lt()))));
    IUTEST_EXPECT_THAT(actual, (Args<0, 2>(AllArgs(Lt()))));
}

IUTEST(ArgsMatcher, NonCopyableElements)
{
    ::std::unique_ptr<int> ptr(new int(1));
    const ::std::tuple< ::std::unique_ptr<int>&> refs(ptr);
    IUTEST_EXPECT_THAT(refs, (Args<0, 0>(Eq())));
#if !defined(IUTEST_USE_GMOCK)
    ::std::tuple< ::std::unique_ptr<int>, int> actual(::std::unique_ptr<int>(new int(1)), 2);
    IUTEST_EXPECT_THAT(actual, (Args<0, 0>(Eq())));
#endif
}

IUTEST(ArgsMatcher, ReferenceElements)
{
    int value = 2;
    const ::std::tuple<int&, const int&> actual(value, value);
    IUTEST_EXPECT_THAT(actual, (Args<0, 1>(Eq())));
    IUTEST_EXPECT_THAT(actual, (Args<1, 0>(Eq(::std::make_tuple(2, 2)))));
    value = 3;
    IUTEST_EXPECT_THAT(actual, (Args<0, 1>(Eq(::std::make_tuple(3, 3)))));
    IUTEST_EXPECT_THAT(::std::make_tuple(1, 2.5), (Args<0, 1>(Lt())));
}

IUTEST(AllArgsMatcher, MatchesOriginalTuple)
{
    IUTEST_EXPECT_THAT(::std::make_tuple(1, 2), AllArgs(Lt()));
    IUTEST_EXPECT_THAT(::std::make_tuple(2, 2), AllArgs(Eq()));
    IUTEST_EXPECT_THAT(::std::make_tuple(1, 2, 3), AllArgs(Eq(::std::make_tuple(1, 2, 3))));
    IUTEST_EXPECT_THAT(::std::tuple<>(), AllArgs(Eq(::std::tuple<>())));
    IUTEST_EXPECT_THAT(3, AllArgs(Eq(3)));
}

IUTEST(ArgsMatcher, FailureMessage)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(failure_tuple, (Args<0, 2>(Lt()))), "Args<0, 2>: Lt");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(failure_tuple, (Args<0, 2>(Lt()))),
        "whose selected arguments are (3, 1)");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(failure_tuple, (Args<0, 2>(Lt()))), "#0");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(failure_tuple, (Args<0, 2>(Lt()))), "(3, 1)");
#endif
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(failure_tuple, AllArgs(Eq(::std::make_tuple(1, 2, 3)))), "Expected:");
}

#if defined(IUTEST_USE_GMOCK) || (IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE))
#if defined(IUTEST_USE_GMOCK)
typedef ::testing::MatchResultListener ArgsExplanation;
#define TEST_ARGS_MATCHER(matcher) ::testing::MakePolymorphicMatcher(matcher)
#else
typedef ::std::ostream ArgsExplanation;
#define TEST_ARGS_MATCHER(matcher) matcher
#endif

namespace {

class FirstIsEven
{
public:
    template<typename T>
    bool MatchAndExplain(const T& value, ArgsExplanation* listener) const
    {
        *listener << "whose first remainder is " << ::std::get<0>(value) % 2;
        return ::std::get<0>(value) % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const { *os << "has an even first argument"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "has an odd first argument"; }
};

}   // end of namespace

IUTEST(ArgsMatcher, InnerExplanationAndDescription)
{
    IUTEST_EXPECT_THAT(failure_tuple, (Args<1>(TEST_ARGS_MATCHER(FirstIsEven()))));
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(failure_tuple, (Args<0>(TEST_ARGS_MATCHER(FirstIsEven())))), "has an even first argument");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(failure_tuple, (Args<0>(TEST_ARGS_MATCHER(FirstIsEven())))), "whose first remainder is 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(failure_tuple, (Not(Args<1>(TEST_ARGS_MATCHER(FirstIsEven()))))), "has an odd first argument");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(failure_tuple, AllArgs(TEST_ARGS_MATCHER(FirstIsEven()))), "whose first remainder is 1");
}

#undef TEST_ARGS_MATCHER
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
