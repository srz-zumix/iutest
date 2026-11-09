//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matcher_cast_tests.cpp
 * @brief       Typed matcher cast tests
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
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::Matcher;
using ::iutest::matchers::MatcherCast;
using ::iutest::matchers::SafeMatcherCast;

namespace {

const int matcher_expected = 42;

struct Base { virtual ~Base() {} };
struct Derived : Base {};

struct NonCopyable
{
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

int SelectOverload(const Matcher<int>&) { return 1; }
int SelectOverload(const Matcher< ::std::string>&) { return 2; }

Matcher<int> MakeValueMatcher()
{
    int value = matcher_expected;
    return MatcherCast<int>(value);
}

}   // end of namespace

IUTEST(MatcherCast, Value)
{
    const Matcher<int> matcher = MakeValueMatcher();
    IUTEST_EXPECT_TRUE(matcher.Matches(matcher_expected));
    IUTEST_EXPECT_FALSE(matcher.Matches(0));
    IUTEST_EXPECT_THAT(matcher_expected, matcher);
    IUTEST_EXPECT_THAT(0, ::iutest::matchers::Not(matcher));
    const Matcher< ::std::string> text = MatcherCast< ::std::string>("hello");
    IUTEST_EXPECT_TRUE(text.Matches("hello"));
    IUTEST_EXPECT_FALSE(text.Matches("world"));
    const Matcher<const ::std::string&> reference = MatcherCast<const ::std::string&>(::std::string("hello"));
    IUTEST_EXPECT_TRUE(reference.Matches("hello"));
}

IUTEST(MatcherCast, PolymorphicMatcher)
{
    const Matcher<int> matcher = MatcherCast<int>(::iutest::matchers::Eq(matcher_expected));
    IUTEST_EXPECT_TRUE(matcher.Matches(matcher_expected));
    IUTEST_EXPECT_FALSE(matcher.Matches(0));
    IUTEST_EXPECT_EQ(1, SelectOverload(MatcherCast<int>(::iutest::matchers::_)));
    IUTEST_EXPECT_EQ(2, SelectOverload(MatcherCast< ::std::string>(::iutest::matchers::_)));
}

IUTEST(MatcherCast, TypedMatcher)
{
    const Matcher<int> original = MatcherCast<int>(matcher_expected);
    const Matcher<short> safe = SafeMatcherCast<short>(original);
    IUTEST_EXPECT_TRUE(safe.Matches(42));
    IUTEST_EXPECT_FALSE(safe.Matches(0));
    const Matcher<double> unchecked = MatcherCast<double>(original);
    IUTEST_EXPECT_TRUE(unchecked.Matches(42.9));
    const Matcher<int> same = MatcherCast<int>(original);
    IUTEST_EXPECT_TRUE(same.Matches(matcher_expected));
}

IUTEST(MatcherCast, CopyAndAssignment)
{
    Matcher<int> assigned;
    {
        const Matcher<int> original = MakeValueMatcher();
        Matcher<int> copy(original);
        assigned = copy;
        copy = MatcherCast<int>(0);
        IUTEST_EXPECT_TRUE(copy.Matches(0));
    }
    IUTEST_EXPECT_TRUE(assigned.Matches(matcher_expected));
    Matcher<int>& alias = assigned;
    assigned = alias;
    IUTEST_EXPECT_TRUE(assigned.Matches(matcher_expected));
}

IUTEST(MatcherCast, SafeValuesAndPolymorphicMatchers)
{
    IUTEST_EXPECT_TRUE(SafeMatcherCast<int>(matcher_expected).Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<int>(::iutest::matchers::Eq(matcher_expected)).Matches(matcher_expected));
    const Matcher<double> wide = MatcherCast<double>(1.5);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<float>(wide).Matches(1.5f));
    const Matcher<int> integer = MatcherCast<int>(1);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<bool>(integer).Matches(true));
    IUTEST_EXPECT_FALSE(SafeMatcherCast<bool>(wide).Matches(false));
    const Matcher<unsigned int> unsigned_integer = MatcherCast<unsigned int>(1U);
    IUTEST_EXPECT_TRUE(SafeMatcherCast<unsigned char>(unsigned_integer).Matches(1));
}

IUTEST(MatcherCast, ReferencesAndNonCopyable)
{
    NonCopyable object;
    const Matcher<const NonCopyable&> original =
        MatcherCast<const NonCopyable&>(::iutest::matchers::Ref(object));
    const Matcher<NonCopyable&> converted = SafeMatcherCast<NonCopyable&>(original);
    IUTEST_EXPECT_TRUE(converted.Matches(object));
    NonCopyable other;
    IUTEST_EXPECT_FALSE(converted.Matches(other));
    const Matcher<const int&> reference = MatcherCast<const int&>(::iutest::matchers::Ref(matcher_expected));
    const Matcher<const int&> same = SafeMatcherCast<const int&>(reference);
    IUTEST_EXPECT_TRUE(same.Matches(matcher_expected));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<const int&>(MatcherCast<int>(matcher_expected)).Matches(matcher_expected));
}

IUTEST(MatcherCast, PointerAndReferenceUpcasts)
{
    Derived object;
    const Matcher<Base*> pointer = MatcherCast<Base*>(::iutest::matchers::NotNull());
    IUTEST_EXPECT_TRUE(SafeMatcherCast<Derived*>(pointer).Matches(&object));
    IUTEST_EXPECT_FALSE(SafeMatcherCast<Derived*>(pointer).Matches(NULL));
    const Matcher<const Base&> reference = MatcherCast<const Base&>(::iutest::matchers::Ref(object));
    IUTEST_EXPECT_TRUE(SafeMatcherCast<const Derived&>(reference).Matches(object));
}

IUTEST(MatcherCast, Descriptions)
{
    const Matcher<int> matcher = MatcherCast<int>(::iutest::matchers::Eq(matcher_expected));
    ::std::ostringstream original;
    ::std::ostringstream converted;
    matcher.DescribeTo(&original);
    SafeMatcherCast<short>(matcher).DescribeTo(&converted);
    IUTEST_EXPECT_EQ(original.str(), converted.str());
    original.str("");
    converted.str("");
    matcher.DescribeNegationTo(&original);
    SafeMatcherCast<short>(matcher).DescribeNegationTo(&converted);
    IUTEST_EXPECT_EQ(original.str(), converted.str());
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(0, MatcherCast<int>(matcher_expected)), "42");
}

#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)

namespace {

#if defined(IUTEST_USE_GTEST)
typedef ::testing::MatchResultListener Explanation;
#else
typedef ::std::ostream Explanation;
#endif

struct IsEven
{
    bool MatchAndExplain(int value, Explanation* os) const
    {
        *os << "remainder " << value % 2;
        return value % 2 == 0;
    }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

}   // end of namespace

IUTEST(MatcherCast, Explanation)
{
#if defined(IUTEST_USE_GTEST)
    const Matcher<int> matcher = MatcherCast<int>(::testing::MakePolymorphicMatcher(IsEven()));
    ::testing::StringMatchResultListener listener;
#else
    const Matcher<int> matcher = MatcherCast<int>(IsEven());
    ::std::ostringstream listener;
#endif
    IUTEST_EXPECT_FALSE(SafeMatcherCast<short>(matcher).MatchAndExplain(3, &listener));
    IUTEST_EXPECT_EQ("remainder 1", listener.str());
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, matcher), "remainder 1");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(4, ::iutest::matchers::Not(matcher)), "is odd");
}

#endif
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
