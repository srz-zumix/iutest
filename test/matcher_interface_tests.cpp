//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_interface_tests.cpp
 * @brief       User-defined matcher interface tests
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
#include <string>
#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::MatcherInterface;
using ::iutest::matchers::Matcher;
using ::iutest::matchers::MakeMatcher;
using ::iutest::matchers::MakePolymorphicMatcher;
using ::iutest::matchers::PolymorphicMatcher;
using ::iutest::MatchResultListener;

namespace {

class Listener : public MatchResultListener
{
public:
    explicit Listener(::std::ostream* os) : MatchResultListener(os) {}
};

class IsEven : public MatcherInterface<int>
{
public:
    bool MatchAndExplain(int value, MatchResultListener* listener) const IUTEST_CXX_OVERRIDE
    {
        *listener << "has remainder " << value % 2;
        return value % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is odd"; }
};

class HasLength
{
public:
    explicit HasLength(size_t length) : m_length(length) {}
    template<typename T>
    bool MatchAndExplain(const T& value, MatchResultListener* listener) const
    {
        *listener << "has length " << value.size();
        return value.size() == m_length;
    }
    void DescribeTo(::std::ostream* os) const { *os << "has requested length " << m_length; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "does not have requested length " << m_length; }
private:
    size_t m_length;
};

class IsPositive : public MatcherInterface<int>
{
public:
    bool MatchAndExplain(int value, MatchResultListener*) const IUTEST_CXX_OVERRIDE { return value > 0; }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is positive"; }
};

class ListenerInterested : public MatcherInterface<int>
{
public:
    bool MatchAndExplain(int, MatchResultListener* listener) const IUTEST_CXX_OVERRIDE
    {
        return listener->IsInterested();
    }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "has an interested listener"; }
};

class RefMatcher : public MatcherInterface<int&>
{
public:
    explicit RefMatcher(int* value) : m_value(value) {}
    bool MatchAndExplain(int& value, MatchResultListener*) const IUTEST_CXX_OVERRIDE { return &value == m_value; }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "refers to the expected object"; }
private:
    int* m_value;
};

class TrackedMatcher : public MatcherInterface<int>
{
public:
    explicit TrackedMatcher(int* live) : m_live(live) { ++*m_live; }
    ~TrackedMatcher() IUTEST_CXX_OVERRIDE { --*m_live; }
    bool MatchAndExplain(int, MatchResultListener*) const IUTEST_CXX_OVERRIDE { return true; }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "matches"; }
private:
    int* m_live;
    TrackedMatcher(const TrackedMatcher&);
    TrackedMatcher& operator =(const TrackedMatcher&);
};

class Increment
{
public:
    bool MatchAndExplain(int& value, MatchResultListener*) const { return ++value == 2; }
    void DescribeTo(::std::ostream* os) const { *os << "increments to two"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "does not increment to two"; }
};

}   // end of namespace

IUTEST(MatcherInterfaceTest, MakeMatcher)
{
    const Matcher<int> matcher = MakeMatcher(new IsEven);
    IUTEST_EXPECT_THAT(4, matcher);
    IUTEST_EXPECT_FALSE(matcher.Matches(3));
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, MakeMatcher(new IsEven)), "is even");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, MakeMatcher(new IsEven)), "has remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(4, ::iutest::matchers::Not(MakeMatcher(new IsEven))), "is odd");
}

IUTEST(MatcherInterfaceTest, DirectConstruction)
{
    const Matcher<int> matcher(new IsEven);
    IUTEST_EXPECT_TRUE(matcher.Matches(2));
    IUTEST_EXPECT_FALSE(matcher.Matches(1));
}

IUTEST(MatcherInterfaceTest, DefaultNegation)
{
    const Matcher<int> matcher = MakeMatcher(new IsPositive);
    ::std::ostringstream os;
    matcher.DescribeNegationTo(&os);
    IUTEST_EXPECT_EQ("not (is positive)", os.str());
}

IUTEST(MatcherInterfaceTest, Reference)
{
    int value = 42;
    int other = value;
    const Matcher<int&> matcher = MakeMatcher(new RefMatcher(&value));
    IUTEST_EXPECT_TRUE(matcher.Matches(value));
    IUTEST_EXPECT_FALSE(matcher.Matches(other));
}

IUTEST(MatcherInterfaceTest, SharedOwnership)
{
    int live = 0;
    {
        Matcher<int> copy;
        {
            Matcher<int> original = MakeMatcher(new TrackedMatcher(&live));
            const Matcher<int> constructed(original);
            copy = original;
            original = original;
            IUTEST_EXPECT_EQ(1, live);
            IUTEST_EXPECT_TRUE(constructed.Matches(0));
        }
        IUTEST_EXPECT_EQ(1, live);
        IUTEST_EXPECT_TRUE(copy.Matches(0));
        copy = MakeMatcher(new IsEven);
        IUTEST_EXPECT_EQ(0, live);
    }
    IUTEST_EXPECT_EQ(0, live);
}

IUTEST(MatcherInterfaceTest, Listener)
{
    const Matcher<int> matcher = MakeMatcher(new IsEven);
    ::std::ostringstream os;
    Listener listener(&os);
    IUTEST_EXPECT_FALSE(matcher.MatchAndExplain(3, &listener));
    IUTEST_EXPECT_EQ("has remainder 1", os.str());
    Listener ignored(NULL);
    IUTEST_EXPECT_FALSE(ignored.IsInterested());
    IUTEST_EXPECT_TRUE(matcher.MatchAndExplain(2, &ignored));
    const Matcher<int> interested = MakeMatcher(new ListenerInterested);
    IUTEST_EXPECT_FALSE(interested.Matches(0));
    IUTEST_EXPECT_TRUE(interested.MatchAndExplain(0, &listener));
    IUTEST_EXPECT_FALSE(interested.MatchAndExplain(0, &ignored));
}

IUTEST(PolymorphicMatcherTest, MultipleTypes)
{
    const PolymorphicMatcher<HasLength> matcher = MakePolymorphicMatcher(HasLength(3));
    IUTEST_EXPECT_THAT(::std::string("abc"), matcher);
    IUTEST_EXPECT_THAT(::std::vector<int>(3), matcher);
    const Matcher<const ::std::string&> string_matcher = matcher;
    const Matcher<const ::std::vector<int>&> vector_matcher(matcher);
    IUTEST_EXPECT_TRUE(string_matcher.Matches("abc"));
    IUTEST_EXPECT_TRUE(vector_matcher.Matches(::std::vector<int>(3)));
    IUTEST_EXPECT_FALSE(vector_matcher.Matches(::std::vector<int>(2)));
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(::std::string("ab"), MakePolymorphicMatcher(HasLength(3))), "has length 2");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(::std::string("abc"), ::iutest::matchers::Not(MakePolymorphicMatcher(HasLength(3)))),
        "does not have requested length 3");
}

IUTEST(PolymorphicMatcherTest, MutableImplementation)
{
    PolymorphicMatcher<HasLength> matcher(HasLength(2));
    const Matcher<const ::std::string&> before = matcher;
    matcher.mutable_impl() = HasLength(3);
    const Matcher<const ::std::string&> after = matcher;
    IUTEST_EXPECT_TRUE(before.Matches("ab"));
    IUTEST_EXPECT_TRUE(after.Matches("abc"));
    ::std::ostringstream os;
    matcher.impl().DescribeTo(&os);
    IUTEST_EXPECT_EQ("has requested length 3", os.str());
}

IUTEST(PolymorphicMatcherTest, MutableReference)
{
    int value = 1;
    const Matcher<int&> matcher = MakePolymorphicMatcher(Increment());
    IUTEST_EXPECT_TRUE(matcher.Matches(value));
    IUTEST_EXPECT_EQ(2, value);
}

IUTEST(MatcherInterfaceTest, MatcherCast)
{
    const Matcher<int> matcher = MakeMatcher(new IsEven);
    IUTEST_EXPECT_THAT(4L, ::iutest::matchers::MatcherCast<long>(matcher));
    IUTEST_EXPECT_THAT(static_cast<short>(4), ::iutest::matchers::SafeMatcherCast<short>(matcher));
    const Matcher<const ::std::string&> length =
        ::iutest::matchers::MatcherCast<const ::std::string&>(MakePolymorphicMatcher(HasLength(3)));
    IUTEST_EXPECT_TRUE(length.Matches("abc"));
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
