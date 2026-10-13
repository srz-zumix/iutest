//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_style_matcher_tests.cpp
 * @brief       gtest style matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <ostream>
#include <string>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE) \
    && (!defined(IUTEST_USE_GTEST) || GMOCK_VER >= 0x01110000)

#if defined(IUTEST_USE_GTEST)
#define TEST_STYLE_MATCHER(matcher) ::testing::MakePolymorphicMatcher(matcher)
typedef ::testing::MatchResultListener MatcherExplanation;
#else
#define TEST_STYLE_MATCHER(matcher) matcher
typedef ::std::ostream MatcherExplanation;
#endif

namespace {

class IsEven
{
public:
    bool MatchAndExplain(const int& value, MatcherExplanation* explanation) const
    {
        if( value % 2 == 0 ) return true;
        *explanation << "has an odd remainder";
        return false;
    }
    void DescribeTo(::std::ostream* os) const { *os << "is even"; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "is odd"; }
};

class HasLength
{
public:
    explicit HasLength(size_t length) : m_length(length) {}
    template<typename T>
    bool MatchAndExplain(const T& value, MatcherExplanation* explanation) const
    {
        if( value.size() == m_length ) return true;
        *explanation << "has length " << value.size();
        return false;
    }
    void DescribeTo(::std::ostream* os) const { *os << "has length " << m_length; }
    void DescribeNegationTo(::std::ostream* os) const { *os << "does not have length " << m_length; }
private:
    size_t m_length;
};

}   // end of namespace

IUTEST(GTestStyleMatcher, Match)
{
    IUTEST_EXPECT_THAT(4, TEST_STYLE_MATCHER(IsEven()));
    IUTEST_EXPECT_THAT(::std::string("four"), TEST_STYLE_MATCHER(HasLength(4)));
}

IUTEST(GTestStyleMatcher, FailureMessage)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, TEST_STYLE_MATCHER(IsEven())), "is even");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(3, TEST_STYLE_MATCHER(IsEven())), "has an odd remainder");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_THAT(::std::string("abc"), TEST_STYLE_MATCHER(HasLength(4))), "has length 3");
}

IUTEST(GTestStyleMatcher, NotDescription)
{
    IUTEST_EXPECT_THAT(3, ::iutest::matchers::Not(TEST_STYLE_MATCHER(IsEven())));
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(4, ::iutest::matchers::Not(TEST_STYLE_MATCHER(IsEven()))), "is odd");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_THAT(::std::string("four"), ::iutest::matchers::Not(TEST_STYLE_MATCHER(HasLength(4)))),
        "does not have length 4");
#if !defined(IUTEST_USE_GTEST)
    ::std::ostringstream os;
    ::iutest::matchers::Not(IsEven()).DescribeTo(&os);
    IUTEST_EXPECT_EQ("is odd", os.str());
    os.str("");
    ::iutest::matchers::Not(IsEven()).DescribeNegationTo(&os);
    IUTEST_EXPECT_EQ("is even", os.str());
#endif
}

IUTEST(GTestStyleMatcher, ExistingMatchers)
{
    IUTEST_EXPECT_THAT(3, ::iutest::matchers::Eq(3));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_TRUE(::iutest::matchers::Value(3, 3));
    IUTEST_EXPECT_FALSE(::iutest::matchers::Value(3, 4));
    IUTEST_EXPECT_TRUE(::iutest::matchers::Value(3, ::iutest::matchers::Eq(3)));
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
