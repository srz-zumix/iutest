//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        explain_match_result_tests.cpp
 * @brief       ExplainMatchResult tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <sstream>
#include "../include/gtest/iutest_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::Eq;
using ::iutest::matchers::ExplainMatchResult;

#if defined(IUTEST_USE_GTEST)
typedef ::testing::StringMatchResultListener TestListener;
typedef ::testing::MatchResultListener MatcherExplanation;
#else
typedef ::std::ostringstream TestListener;
typedef ::std::ostream MatcherExplanation;
#endif

IUTEST(ExplainMatchResult, MatcherWithoutExplanation)
{
    TestListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(Eq(3), 3, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
    IUTEST_EXPECT_FALSE(ExplainMatchResult(Eq(3), 4, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
}

#if !defined(IUTEST_NO_SFINAE)
IUTEST(ExplainMatchResult, PlainValue)
{
    TestListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(3, 3, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
    IUTEST_EXPECT_FALSE(ExplainMatchResult(3, 4, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
}
#endif

#if defined(IUTEST_USE_GTEST) || (!defined(IUTEST_NO_SFINAE) \
    && !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4))

#if defined(IUTEST_USE_GTEST)
#define TEST_EXPLAIN_MATCHER(matcher) ::testing::MakePolymorphicMatcher(matcher)
#else
#define TEST_EXPLAIN_MATCHER(matcher) matcher
#endif

namespace {

class IsEven
{
public:
    bool MatchAndExplain(int value, MatcherExplanation* listener) const
    {
        *listener << "whose remainder is " << value % 2;
        return value % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

class ForwardIsEven : public IsEven
{
public:
    bool MatchAndExplain(int value, MatcherExplanation* listener) const
    {
        return ExplainMatchResult(TEST_EXPLAIN_MATCHER(IsEven()), value, listener);
    }
};

}   // end of namespace

IUTEST(ExplainMatchResult, SuccessExplanation)
{
    TestListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(TEST_EXPLAIN_MATCHER(IsEven()), 4, &listener));
    IUTEST_EXPECT_EQ("whose remainder is 0", listener.str());
}

IUTEST(ExplainMatchResult, FailureExplanation)
{
    TestListener listener;
    IUTEST_EXPECT_FALSE(ExplainMatchResult(TEST_EXPLAIN_MATCHER(IsEven()), 3, &listener));
    IUTEST_EXPECT_EQ("whose remainder is 1", listener.str());
}

IUTEST(ExplainMatchResult, ForwardSuccessExplanation)
{
    TestListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(TEST_EXPLAIN_MATCHER(ForwardIsEven()), 4, &listener));
    IUTEST_EXPECT_EQ("whose remainder is 0", listener.str());
}

IUTEST(ExplainMatchResult, ForwardFailureExplanation)
{
    TestListener listener;
    IUTEST_EXPECT_FALSE(ExplainMatchResult(TEST_EXPLAIN_MATCHER(ForwardIsEven()), 3, &listener));
    IUTEST_EXPECT_EQ("whose remainder is 1", listener.str());
}

#undef TEST_EXPLAIN_MATCHER
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
