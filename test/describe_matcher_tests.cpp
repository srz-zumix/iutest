//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        describe_matcher_tests.cpp
 * @brief       DescribeMatcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::DescribeMatcher;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Not;

IUTEST(DescribeMatcher, DefaultDescription)
{
    IUTEST_EXPECT_EQ("is equal to 3", DescribeMatcher<int>(Eq(3)));
}

IUTEST(DescribeMatcher, ExplicitDescription)
{
    IUTEST_EXPECT_EQ("is equal to 3", DescribeMatcher<int>(Eq(3), false));
}

IUTEST(DescribeMatcher, NegationDescription)
{
    IUTEST_EXPECT_EQ("isn't equal to 3", DescribeMatcher<int>(Eq(3), true));
}

IUTEST(DescribeMatcher, NegatedMatcher)
{
    IUTEST_EXPECT_EQ("isn't equal to 3", DescribeMatcher<int>(Not(Eq(3)), false));
    IUTEST_EXPECT_EQ("is equal to 3", DescribeMatcher<int>(Not(Eq(3)), true));
}

#if !defined(IUTEST_NO_SFINAE)
IUTEST(DescribeMatcher, PlainValue)
{
    IUTEST_EXPECT_EQ("is equal to 3", DescribeMatcher<int>(3, false));
    IUTEST_EXPECT_EQ("isn't equal to 3", DescribeMatcher<int>(3, true));
}
#endif

#if !defined(IUTEST_USE_GTEST)
namespace {

class LegacyMatcher : public ::iutest::detail::IMatcher
{
public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "legacy description"; }
};

}   // end of namespace

IUTEST(DescribeMatcher, NegationFallback)
{
    IUTEST_EXPECT_EQ("legacy description", DescribeMatcher<int>(LegacyMatcher(), false));
    IUTEST_EXPECT_EQ("not (legacy description)", DescribeMatcher<int>(LegacyMatcher(), true));
}

namespace {

class DescribedMatcher : public LegacyMatcher
{
public:
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "custom description"; }
};

}   // end of namespace

IUTEST(DescribeMatcher, NativeDescriptionNegationFallback)
{
    IUTEST_EXPECT_EQ("custom description", DescribeMatcher<int>(DescribedMatcher(), false));
    IUTEST_EXPECT_EQ("not (custom description)", DescribeMatcher<int>(DescribedMatcher(), true));
}
#endif

#if defined(IUTEST_USE_GTEST) || (IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE))
namespace {

class IsEven
{
public:
#if defined(IUTEST_USE_GTEST)
    bool MatchAndExplain(int value, ::testing::MatchResultListener*) const { return value % 2 == 0; }
#else
    bool MatchAndExplain(int value, ::std::ostream*) const { return value % 2 == 0; }
#endif
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

}   // end of namespace

IUTEST(DescribeMatcher, CustomDescription)
{
#if defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_EQ("is even", DescribeMatcher<int>(::testing::MakePolymorphicMatcher(IsEven()), false));
    IUTEST_EXPECT_EQ("is odd", DescribeMatcher<int>(::testing::MakePolymorphicMatcher(IsEven()), true));
#else
    IUTEST_EXPECT_EQ("is even", DescribeMatcher<int>(IsEven(), false));
    IUTEST_EXPECT_EQ("is odd", DescribeMatcher<int>(IsEven(), true));
#endif
}

#if !defined(IUTEST_USE_GTEST)
namespace {

class DescriptionOnlyMatcher
{
public:
    bool MatchAndExplain(int value, ::std::ostream*) const { return value % 2 == 0; }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
};

}   // end of namespace

IUTEST(DescribeMatcher, CustomDescriptionNegationFallback)
{
    IUTEST_EXPECT_EQ("is even", DescribeMatcher<int>(DescriptionOnlyMatcher(), false));
    IUTEST_EXPECT_EQ("not (is even)", DescribeMatcher<int>(DescriptionOnlyMatcher(), true));
}
#endif
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
