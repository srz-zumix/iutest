//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        logical_array_matcher_tests.cpp
 * @brief       AllOfArray / AnyOfArray matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01100000)

using ::iutest::matchers::AllOfArray;
using ::iutest::matchers::AnyOfArray;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Not;

namespace {

const int equal_values[] = { 2, 2, 2 };
const int different_values[] = { 1, 2, 3 };

} // namespace

IUTEST(LogicalArrayMatcher, Values)
{
    IUTEST_EXPECT_THAT(2, AllOfArray(equal_values));
    IUTEST_EXPECT_THAT(1, Not(AllOfArray(equal_values)));
    IUTEST_EXPECT_THAT(2, Not(AllOfArray(different_values)));
    IUTEST_EXPECT_THAT(1, AnyOfArray(different_values));
    IUTEST_EXPECT_THAT(2, AnyOfArray(different_values));
    IUTEST_EXPECT_THAT(3, AnyOfArray(different_values));
    IUTEST_EXPECT_THAT(4, Not(AnyOfArray(different_values)));
}

IUTEST(LogicalArrayMatcher, Containers)
{
    const ::std::list<int> values(different_values, different_values + 3);
    IUTEST_EXPECT_THAT(2, Not(AllOfArray(values)));
    IUTEST_EXPECT_THAT(2, AnyOfArray(values));
    IUTEST_EXPECT_THAT(2, AllOfArray(::std::vector<int>(3, 2)));
    IUTEST_EXPECT_THAT(3, Not(AnyOfArray(::std::vector<int>(3, 2))));
    IUTEST_EXPECT_THAT(true, AllOfArray(::std::vector<bool>(3, true)));
    IUTEST_EXPECT_THAT(false, Not(AnyOfArray(::std::vector<bool>(3, true))));
}

IUTEST(LogicalArrayMatcher, StringValues)
{
    const ::std::string values[] = { "first", "second" };
    const ::std::string equal[] = { "second", "second" };
    IUTEST_EXPECT_THAT(::std::string("second"), AllOfArray(equal));
    IUTEST_EXPECT_THAT(::std::string("first"), Not(AllOfArray(equal)));
    IUTEST_EXPECT_THAT(::std::string("second"), AnyOfArray(values));
    IUTEST_EXPECT_THAT(::std::string("third"), Not(AnyOfArray(values)));
}

IUTEST(LogicalArrayMatcher, Empty)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(0, AllOfArray(empty));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(empty)));
    IUTEST_EXPECT_THAT(0, AllOfArray(equal_values, 0));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(equal_values, 0)));
}

IUTEST(LogicalArrayMatcher, PointerAndCount)
{
    const int* values = different_values;
    IUTEST_EXPECT_THAT(1, AllOfArray(values, 1));
    IUTEST_EXPECT_THAT(1, Not(AllOfArray(values, 2)));
    IUTEST_EXPECT_THAT(2, AnyOfArray(values, 2));
    IUTEST_EXPECT_THAT(3, Not(AnyOfArray(values, 2)));
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
IUTEST(LogicalArrayMatcher, IteratorRange)
{
    const ::std::list<int> values(different_values, different_values + 3);
    IUTEST_EXPECT_THAT(2, Not(AllOfArray(values.begin(), values.end())));
    IUTEST_EXPECT_THAT(2, AnyOfArray(values.begin(), values.end()));
    IUTEST_EXPECT_THAT(2, AllOfArray(equal_values, equal_values + 3));
    IUTEST_EXPECT_THAT(2, AnyOfArray(different_values, different_values + 3));
    IUTEST_EXPECT_THAT(0, AllOfArray(values.begin(), values.begin()));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(values.begin(), values.begin())));
    ::std::istringstream all_input("2 2 2");
    ::std::istringstream any_input("1 2 3");
    IUTEST_EXPECT_THAT(2, AllOfArray(::std::istream_iterator<int>(all_input), ::std::istream_iterator<int>()));
    IUTEST_EXPECT_THAT(3, AnyOfArray(::std::istream_iterator<int>(any_input), ::std::istream_iterator<int>()));
}
#endif

IUTEST(LogicalArrayMatcher, Matchers)
{
    const int low = 1;
    const int high = 3;
#if !defined(IUTEST_USE_GMOCK)
    typedef ::iutest::detail::GeMatcher<int> Matcher;
#else
    typedef ::testing::Matcher<int> Matcher;
#endif
    const Matcher matchers[] = { Ge(low), Ge(high) };
    const ::std::vector<Matcher> empty;
    const ::std::list<Matcher> container(matchers, matchers + 2);
    IUTEST_EXPECT_THAT(3, AllOfArray(matchers));
    IUTEST_EXPECT_THAT(2, Not(AllOfArray(matchers)));
    IUTEST_EXPECT_THAT(1, AnyOfArray(matchers));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(matchers)));
    IUTEST_EXPECT_THAT(0, AllOfArray(empty));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(empty)));
    IUTEST_EXPECT_THAT(3, AllOfArray(matchers, 2));
    IUTEST_EXPECT_THAT(1, AnyOfArray(matchers, 2));
    IUTEST_EXPECT_THAT(3, AllOfArray(container));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(container)));
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    IUTEST_EXPECT_THAT(2, Not(AllOfArray(container.begin(), container.end())));
    IUTEST_EXPECT_THAT(1, AnyOfArray(container.begin(), container.end()));
#endif
    IUTEST_EXPECT_THAT(3, Not(Not(AllOfArray(matchers))));
}

#if IUTEST_HAS_INITIALIZER_LIST || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX11)
IUTEST(LogicalArrayMatcher, InitializerList)
{
    IUTEST_EXPECT_THAT(2, AllOfArray({ 2, 2, 2 }));
    IUTEST_EXPECT_THAT(2, Not(AllOfArray({ 1, 2, 3 })));
    IUTEST_EXPECT_THAT(2, AnyOfArray({ 1, 2, 3 }));
    IUTEST_EXPECT_THAT(4, Not(AnyOfArray({ 1, 2, 3 })));
    IUTEST_EXPECT_THAT(3, AllOfArray({ Ge(1), Ge(3) }));
    IUTEST_EXPECT_THAT(2, Not(AllOfArray({ Ge(1), Ge(3) })));
    IUTEST_EXPECT_THAT(1, AnyOfArray({ Ge(1), Ge(3) }));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray({ Ge(1), Ge(3) })));
    IUTEST_EXPECT_THAT(0, AllOfArray(::std::initializer_list<int>()));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(::std::initializer_list<int>())));
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(LogicalArrayMatcher, CopiesExpectations)
{
    int values[] = { 2, 2 };
    const ::iutest::detail::LogicalArrayMatcher<int, true> all = AllOfArray(values);
    const ::iutest::detail::LogicalArrayMatcher<int, false> any = AnyOfArray(values);
    values[0] = values[1] = 9;
    IUTEST_EXPECT_THAT(2, all);
    IUTEST_EXPECT_THAT(2, any);
    IUTEST_EXPECT_THAT(9, Not(any));
#if IUTEST_HAS_INITIALIZER_LIST
    const ::iutest::detail::LogicalArrayMatcher<int, true> all_list = AllOfArray({ 2, 2 });
    const ::iutest::detail::LogicalArrayMatcher<int, false> any_list = AnyOfArray({ 1, 2 });
    IUTEST_EXPECT_THAT(2, all_list);
    IUTEST_EXPECT_THAT(2, any_list);
#endif
}

IUTEST(LogicalArrayMatcher, NullEmptyRange)
{
    const int* values = NULL;
    IUTEST_EXPECT_THAT(0, AllOfArray(values, 0));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(values, 0)));
    IUTEST_EXPECT_THAT(0, AllOfArray(values, values));
    IUTEST_EXPECT_THAT(0, Not(AnyOfArray(values, values)));
}

IUTEST(LogicalArrayMatcher, FailureMessages)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(2, AllOfArray(different_values)), "AllOfArray:");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(2, AllOfArray(different_values)), "matcher #0 doesn't match");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(4, AnyOfArray(different_values)), "AnyOfArray:");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(4, AnyOfArray(different_values)), "matches none of the 3 matchers");
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
