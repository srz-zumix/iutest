//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        begin_end_distance_is_matcher_tests.cpp
 * @brief       BeginEndDistanceIs matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <list>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01080000)

#if IUTEST_HAS_CXX11
#include <forward_list>
#endif

using ::iutest::matchers::BeginEndDistanceIs;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Not;

#if !defined(IUTEST_USE_GMOCK) || !defined(GTEST_HAS_STD_BEGIN_AND_END_) || GTEST_HAS_STD_BEGIN_AND_END_
#  define TEST_HAS_BEGIN_END 1
#else
#  define TEST_HAS_BEGIN_END 0
#endif

namespace {

const int values[] = { 1, 2, 3 };
const ::std::list<int> empty_values;

#if TEST_HAS_BEGIN_END
struct AdlRange
{
    typedef const int* const_iterator;
    const int* first;
    const int* last;
};

const int* begin(const AdlRange& range) { return range.first; }
const int* end(const AdlRange& range) { return range.last; }
#endif

} // namespace

#if TEST_HAS_BEGIN_END && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
IUTEST(BeginEndDistanceIsMatcher, Array)
{
    int mutable_values[] = { 1, 2, 3 };
    IUTEST_EXPECT_THAT(values, BeginEndDistanceIs(3));
    IUTEST_EXPECT_THAT(mutable_values, BeginEndDistanceIs(Eq(3)));
    IUTEST_EXPECT_THAT(values, BeginEndDistanceIs(Ge(2)));
    IUTEST_EXPECT_THAT(values, Not(BeginEndDistanceIs(2)));
}
#endif

IUTEST(BeginEndDistanceIsMatcher, List)
{
    const ::std::list<int> container(values, values + 3);
    IUTEST_EXPECT_THAT(container, BeginEndDistanceIs(3));
    IUTEST_EXPECT_THAT(container, BeginEndDistanceIs(Ge(2)));
    IUTEST_EXPECT_THAT(empty_values, BeginEndDistanceIs(0));
    IUTEST_EXPECT_THAT(empty_values, Not(BeginEndDistanceIs(1)));
}

#if TEST_HAS_BEGIN_END
IUTEST(BeginEndDistanceIsMatcher, AdlRange)
{
    const AdlRange range = { values, values + 3 };
    IUTEST_EXPECT_THAT(range, BeginEndDistanceIs(3));
    const AdlRange reversed = { values + 3, values };
    IUTEST_EXPECT_THAT(reversed, BeginEndDistanceIs(-3));
}
#endif

#if IUTEST_HAS_CXX11
IUTEST(BeginEndDistanceIsMatcher, ForwardList)
{
    const ::std::forward_list<int> container(values, values + 3);
    IUTEST_EXPECT_THAT(container, BeginEndDistanceIs(3));
    IUTEST_EXPECT_THAT(container, BeginEndDistanceIs(Eq(3)));
    IUTEST_EXPECT_THAT(container, BeginEndDistanceIs(Ge(2)));
    IUTEST_EXPECT_THAT(::std::forward_list<int>(), BeginEndDistanceIs(0));
}
#endif

IUTEST(BeginEndDistanceIsMatcher, FailureMessage)
{
#if TEST_HAS_BEGIN_END && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(values, BeginEndDistanceIs(2)),
        "whose distance between begin() and end() 3 doesn't match");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(values, BeginEndDistanceIs(Ge(4))),
        "whose distance between begin() and end() 3 doesn't match");
#endif
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(empty_values, BeginEndDistanceIs(1)),
        "whose distance between begin() and end() 0 doesn't match");
}

#undef TEST_HAS_BEGIN_END

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
