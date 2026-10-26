//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        bool_matcher_tests.cpp
 * @brief       Boolean matcher tests
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

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01080100)

#if IUTEST_HAS_CXX11
#include <memory>
#endif

using namespace ::iutest::matchers;

IUTEST(BoolMatcher, Bool)
{
    IUTEST_ASSERT_THAT(true, IsTrue());
    IUTEST_ASSERT_THAT(false, IsFalse());
    IUTEST_EXPECT_THAT(false, Not(IsTrue()));
    IUTEST_EXPECT_THAT(true, Not(IsFalse()));
}

IUTEST(BoolMatcher, Integer)
{
    IUTEST_EXPECT_THAT(1, IsTrue());
    IUTEST_EXPECT_THAT(-1, IsTrue());
    IUTEST_EXPECT_THAT(0, IsFalse());
}

IUTEST(BoolMatcher, RawPointer)
{
    int value = 0;
    int* ptr = &value;
    IUTEST_EXPECT_THAT(ptr, IsTrue());
    IUTEST_EXPECT_THAT(static_cast<int*>(NULL), IsFalse());
}

#if IUTEST_HAS_CXX11
IUTEST(BoolMatcher, UniquePtr)
{
    ::std::unique_ptr<int> ptr(new int(0));
    IUTEST_EXPECT_THAT(ptr, IsTrue());
    ptr.reset();
    IUTEST_EXPECT_THAT(ptr, IsFalse());
}

IUTEST(BoolMatcher, SharedPtr)
{
    ::std::shared_ptr<int> ptr(new int(0));
    IUTEST_EXPECT_THAT(ptr, IsTrue());
    ptr.reset();
    IUTEST_EXPECT_THAT(ptr, IsFalse());
}
#endif

#if IUTEST_HAS_EXPLICIT_CONVERSION
namespace {

class ExplicitBool
{
public:
    explicit ExplicitBool(bool value) : m_value(value) {}
    explicit operator bool() const { return m_value; }
private:
    bool m_value;
};

} // namespace

IUTEST(BoolMatcher, ExplicitConversion)
{
    IUTEST_EXPECT_THAT(ExplicitBool(true), IsTrue());
    IUTEST_EXPECT_THAT(ExplicitBool(false), IsFalse());
}
#endif

IUTEST(BoolMatcher, AssertionNamespace)
{
    IUTEST_ASSERT_TRUE(true);
    IUTEST_ASSERT_FALSE(false);
    IUTEST_ASSERT_EQ(1, 1);
    IUTEST_ASSERT( true );
}

#if !defined(IUTEST_USE_GMOCK)
#  define CHECK_BOOL_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE(x, str)
#else
#  define CHECK_BOOL_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE(x, "")
#endif

IUTEST(BoolMatcher, FailureMessage)
{
    CHECK_BOOL_FAILURE(IUTEST_ASSERT_THAT(false, IsTrue()), "Is True");
    CHECK_BOOL_FAILURE(IUTEST_ASSERT_THAT(true, IsFalse()), "Is False");
    CHECK_BOOL_FAILURE(IUTEST_ASSERT_THAT(0, IsTrue()), "Is True");
    CHECK_BOOL_FAILURE(IUTEST_ASSERT_THAT(-1, IsFalse()), "Is False");
    CHECK_BOOL_FAILURE(IUTEST_ASSERT_THAT(static_cast<int*>(NULL), IsTrue()), "Is True");
}

#undef CHECK_BOOL_FAILURE

#if !defined(IUTEST_USE_GMOCK)
IUTEST(BoolMatcher, Descriptions)
{
    ::std::ostringstream description;
    ::std::ostringstream negation;
    IsTrue().DescribeTo(&description);
    IsTrue().DescribeNegationTo(&negation);
    IUTEST_EXPECT_EQ("is true", description.str());
    IUTEST_EXPECT_EQ("is false", negation.str());
    description.str("");
    negation.str("");
    IsFalse().DescribeTo(&description);
    IsFalse().DescribeNegationTo(&negation);
    IUTEST_EXPECT_EQ("is false", description.str());
    IUTEST_EXPECT_EQ("is true", negation.str());
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
