//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_explain_tests.cpp
 * @brief       Matcher explanation tests
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
#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && !defined(IUTEST_USE_GTEST)

using namespace ::iutest::matchers;

namespace {

class IsFive : public ::iutest::detail::IMatcher
{
public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "IsFive"; }
    ::iutest::AssertionResult operator ()(int value) const
    {
        return value == 5 ? ::iutest::AssertionSuccess() : ::iutest::AssertionFailure() << WhichIs();
    }
    bool MatchAndExplain(int value, ::std::ostream* listener) const
    {
        if( value == 5 ) return true;
        *listener << "which is " << 5 - value << " less than 5";
        return false;
    }
};

class NonCopyableIsFive : public IsFive
{
    NonCopyableIsFive(const NonCopyableIsFive&);
    NonCopyableIsFive& operator=(const NonCopyableIsFive&);
public:
    NonCopyableIsFive() {}
};

int three = 3;
int five = 5;
IsFive matcher;
NonCopyableIsFive noncopyable_matcher;
int* three_pointer = &three;
int* null_pointer = NULL;
::std::vector<int> values(2, 3);

struct Sample
{
    explicit Sample(int v) : field(v) {}
    int property() const { return field; }
    int field;
};
Sample sample(3);

}   // end of namespace

IUTEST(MatcherExplain, Direct)
{
    ::std::ostringstream listener;
    IUTEST_EXPECT_FALSE(ExplainMatchResult(IsFive(), three, &listener));
    IUTEST_EXPECT_EQ("which is 2 less than 5", listener.str());
    listener.str("");
    IUTEST_EXPECT_TRUE(ExplainMatchResult(IsFive(), five, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
    IUTEST_EXPECT_FALSE(ExplainMatchResult(SizeIs(3), values, &listener));
    IUTEST_EXPECT_EQ("whose size is 2", listener.str());
    IUTEST_EXPECT_THAT(values.begin(), Pointee(Eq(3)));
#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
    listener.str("");
    IUTEST_EXPECT_TRUE(ExplainMatchResult(AnyOf(IsFive(), Eq(3)), three, &listener));
    IUTEST_EXPECT_TRUE(listener.str().empty());
#endif
}

IUTEST(MatcherExplain, FailureMessage)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three, matcher),
        "Actual: 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three, noncopyable_matcher),
        "Actual: 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three, IsFive()),
        "Actual: 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(values, SizeIs(3)),
        "whose size is 2");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(values, Each(IsFive())),
        "whose element #0 doesn't match, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(values, ElementsAre(IsFive(), IsFive())),
        "whose element #0 doesn't match, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three_pointer, Pointee(IsFive())),
        "which points to 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(null_pointer, Pointee(IsFive())),
        "which is NULL");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(sample, Field(&Sample::field, IsFive())),
        "whose field is 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(sample, Property(&Sample::property, IsFive())),
        "whose property is 3, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(five, Not(IsFive())), "Actual: 5, which matches");
#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three, AllOf(IsFive(), Gt(0))),
        "matcher #0 doesn't match, which is 2 less than 5");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(three, AnyOf(IsFive(), Eq(0))),
        "matcher #0 doesn't match, which is 2 less than 5; matcher #1 doesn't match");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
