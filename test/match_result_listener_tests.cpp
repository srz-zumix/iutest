//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        match_result_listener_tests.cpp
 * @brief       Matcher result listener compatibility tests
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

#if IUTEST_HAS_MATCHERS

using ::iutest::MatchResultListener;
using ::iutest::StringMatchResultListener;
using ::iutest::matchers::ExplainMatchResult;
using ::iutest::matchers::MakePolymorphicMatcher;

namespace {

class Listener : public MatchResultListener
{
public:
    explicit Listener(::std::ostream* os) : MatchResultListener(os) {}
};

class IsEven
{
public:
    bool MatchAndExplain(int value, MatchResultListener* listener) const
    {
        *listener << "remainder " << value % 2;
        return value % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

class Interested
{
public:
    bool MatchAndExplain(int, MatchResultListener* listener) const
    {
        *listener << "interested";
        return listener->IsInterested();
    }
    void DescribeTo(::std::ostream* os) const { *os << "has interested listener"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "has no interested listener"; }
};

#if IUTEST_HAS_MATCHER_MACROS
IUTEST_MATCHER(ForwardEven, "is even")
{
    MatchResultListener* listener = result_listener;
    return ExplainMatchResult(MakePolymorphicMatcher(IsEven()), arg, listener);
}

IUTEST_MATCHER_P(ForwardMatcher, inner, "forwards to inner")
{
    return ExplainMatchResult(inner, arg, result_listener);
}
#endif

}   // end of namespace

IUTEST(MatchResultListener, Stream)
{
    ::std::ostringstream os;
    Listener listener(&os);
    IUTEST_EXPECT_TRUE(listener.IsInterested());
    IUTEST_EXPECT_EQ(&os, listener.stream());
    listener << "value " << 42;
    *listener.stream() << '!';
    IUTEST_EXPECT_EQ("value 42!", os.str());
}

IUTEST(MatchResultListener, NullStream)
{
    Listener listener(NULL);
    IUTEST_EXPECT_FALSE(listener.IsInterested());
    IUTEST_EXPECT_TRUE(listener.stream() == NULL);
    listener << "ignored " << 42;
}

IUTEST(MatchResultListener, StringAndClear)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(listener.IsInterested());
    IUTEST_EXPECT_TRUE(listener.stream() != NULL);
    IUTEST_EXPECT_TRUE(listener.str().empty());
    listener << "first " << 1;
    IUTEST_EXPECT_EQ("first 1", listener.str());
    listener.Clear();
    IUTEST_EXPECT_TRUE(listener.str().empty());
    listener << "second";
    IUTEST_EXPECT_EQ("second", listener.str());
}

#if !defined(IUTEST_NO_SFINAE) \
    && !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4)
IUTEST(MatchResultListener, PolymorphicMatcher)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(MakePolymorphicMatcher(IsEven()), 4, &listener));
    IUTEST_EXPECT_EQ("remainder 0", listener.str());
    listener.Clear();
    IUTEST_EXPECT_FALSE(ExplainMatchResult(MakePolymorphicMatcher(IsEven()), 3, &listener));
    IUTEST_EXPECT_EQ("remainder 1", listener.str());
}

IUTEST(MatchResultListener, UninterestedMatcher)
{
    Listener listener(NULL);
    IUTEST_EXPECT_FALSE(ExplainMatchResult(MakePolymorphicMatcher(Interested()), 0, &listener));
    IUTEST_EXPECT_TRUE(ExplainMatchResult(MakePolymorphicMatcher(IsEven()), 4, &listener));
    IUTEST_EXPECT_FALSE(ExplainMatchResult(MakePolymorphicMatcher(IsEven()), 3, &listener));
}
#endif

#if IUTEST_HAS_MATCHER_MACROS && !defined(IUTEST_NO_SFINAE) \
    && !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4)
IUTEST(MatchResultListener, NestedMacroExplanations)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(ForwardMatcher(ForwardEven()), 4, &listener));
    IUTEST_EXPECT_EQ("remainder 0", listener.str());
    listener.Clear();
    IUTEST_EXPECT_FALSE(ExplainMatchResult(ForwardMatcher(ForwardEven()), 3, &listener));
    IUTEST_EXPECT_EQ("remainder 1", listener.str());
}

IUTEST(MatchResultListener, NestedUninterested)
{
    Listener listener(NULL);
    IUTEST_EXPECT_FALSE(ExplainMatchResult(ForwardMatcher(MakePolymorphicMatcher(Interested())), 0, &listener));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(MatchResultListener, DirectMacroMatchAndExplain)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(ForwardEven().MatchAndExplain(4, &listener));
    IUTEST_EXPECT_EQ("remainder 0", listener.str());
    ::std::ostringstream os;
    IUTEST_EXPECT_FALSE(ForwardEven().MatchAndExplain(3, &os));
    IUTEST_EXPECT_EQ("remainder 1", os.str());
    IUTEST_EXPECT_TRUE(static_cast<bool>(ForwardEven()(4)));
}
#endif
#endif

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_SFINAE) \
    && !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4)
IUTEST(MatchResultListener, RawMatcherAndLegacyStream)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(IsEven(), 4, &listener));
    IUTEST_EXPECT_EQ("remainder 0", listener.str());
    ::std::ostringstream os;
    IUTEST_EXPECT_FALSE(ExplainMatchResult(IsEven(), 3, &os));
    IUTEST_EXPECT_EQ("remainder 1", os.str());
    Listener uninterested(NULL);
    IUTEST_EXPECT_FALSE(ExplainMatchResult(Interested(), 0, &uninterested));
    listener.Clear();
    IUTEST_EXPECT_FALSE(ExplainMatchResult(IsEven(), 3, &listener));
    IUTEST_EXPECT_EQ("remainder 1", listener.str());
    os.str("");
    IUTEST_EXPECT_TRUE(MakePolymorphicMatcher(IsEven()).MatchAndExplain(4, &os));
    IUTEST_EXPECT_EQ("remainder 0", os.str());
    IUTEST_EXPECT_TRUE(static_cast<bool>(MakePolymorphicMatcher(IsEven())(4)));
}

class LegacyStreamMatcher
{
public:
    bool MatchAndExplain(int value, ::std::ostream* os) const
    {
        *os << "legacy " << value;
        return value == 4;
    }
};

IUTEST(MatchResultListener, LegacyStreamMatcher)
{
    StringMatchResultListener listener;
    IUTEST_EXPECT_TRUE(ExplainMatchResult(LegacyStreamMatcher(), 4, &listener));
    IUTEST_EXPECT_EQ("legacy 4", listener.str());
    listener.Clear();
    IUTEST_EXPECT_FALSE(ExplainMatchResult(LegacyStreamMatcher(), 3, &listener));
    IUTEST_EXPECT_EQ("legacy 3", listener.str());
    Listener uninterested(NULL);
    IUTEST_EXPECT_FALSE(ExplainMatchResult(LegacyStreamMatcher(), 3, &uninterested));
}

#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE
IUTEST(MatchResultListener, RawMatcherAssertion)
{
    IUTEST_EXPECT_THAT(4, IsEven());
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, IsEven()), "is even");
    IUTEST_EXPECT_THAT(3, ::iutest::matchers::Not(IsEven()));
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, ::iutest::matchers::Not(IsEven())), "is odd");
}
#endif
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
