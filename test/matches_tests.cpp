//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matches_tests.cpp
 * @brief       Matches predicate tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <algorithm>
#include <string>
#include <vector>
#include "../include/gtest/iutest_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::Contains;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Matches;
using ::iutest::matchers::StartsWith;

namespace {

struct StaticIntegralValue
{
    static const int value = 3;
};

template<typename Predicate>
void CheckPredicate(const Predicate& predicate)
{
    Predicate copy(predicate);
    IUTEST_EXPECT_TRUE(predicate(3));
    IUTEST_EXPECT_FALSE(predicate(4));
    IUTEST_EXPECT_TRUE(copy(3));
    IUTEST_EXPECT_FALSE(copy(4));
}

#if !defined(IUTEST_NO_SFINAE)
template<typename Predicate>
void CheckValueCopy(const Predicate& predicate, int* expected)
{
    *expected = 4;
    CheckPredicate(predicate);
}
#endif

#if !defined(IUTEST_USE_GTEST)
struct CopyCounts
{
    CopyCounts() : total(0), original_nonconst(0) {}
    int total;
    int original_nonconst;
};

class CopyCountingMatcher : public ::iutest::detail::IMatcher
{
public:
    CopyCountingMatcher(int expected, CopyCounts* copies)
        : m_expected(expected), m_copies(copies), m_is_original(true) {}
    CopyCountingMatcher(CopyCountingMatcher& other)
        : ::iutest::detail::IMatcher(other), m_expected(other.m_expected), m_copies(other.m_copies)
        , m_is_original(false)
    {
        ++m_copies->total;
        if( other.m_is_original ) ++m_copies->original_nonconst;
    }
    CopyCountingMatcher(const CopyCountingMatcher& other)
        : ::iutest::detail::IMatcher(other), m_expected(other.m_expected), m_copies(other.m_copies)
        , m_is_original(false)
    {
        ++m_copies->total;
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "CopyCountingMatcher"; }
    bool operator ()(int actual) const { return actual == m_expected; }
    void SetExpected(int expected) { m_expected = expected; }

private:
    int m_expected;
    CopyCounts* m_copies;
    bool m_is_original;
};

#if !defined(IUTEST_NO_SFINAE)
struct VolatileValue
{
    explicit VolatileValue(int n) : value(n) {}
    VolatileValue(VolatileValue& other) : value(other.value) {}
    VolatileValue(const VolatileValue& other) : value(other.value) {}
    VolatileValue(volatile VolatileValue& other) : value(other.value) {}
    VolatileValue(const volatile VolatileValue& other) : value(other.value) {}

    int value;
};

bool operator ==(int actual, const VolatileValue& expected)
{
    return actual == expected.value;
}

volatile int second_function_call_count = 0;

void FirstFunction() {}
void SecondFunction() { second_function_call_count = 1; }
#endif
#endif

}   // end of namespace

IUTEST(Matches, CountIf)
{
    const int values[] = { 1, 10, 11, 20 };
    const ::std::vector<int> v(values, values + 4);
    IUTEST_EXPECT_EQ(2, ::std::count_if(v.begin(), v.end(), Matches(Gt(10))));
}

IUTEST(Matches, DirectCall)
{
    const ::std::string s("abc");
    IUTEST_EXPECT_TRUE(Matches(StartsWith("a"))(s));
    IUTEST_EXPECT_FALSE(Matches(StartsWith("b"))(s));
    IUTEST_EXPECT_TRUE(Matches(Eq(3))(3));
    IUTEST_EXPECT_FALSE(Matches(Eq(3))(4));
}

IUTEST(Matches, FindIf)
{
    const ::std::string values[] = { "beta", "alpha", "gamma" };
    IUTEST_EXPECT_EQ(values + 1, ::std::find_if(values, values + 3, Matches(StartsWith("a"))));
    IUTEST_EXPECT_EQ(values + 3, ::std::find_if(values, values + 3, Matches(StartsWith("z"))));
}

IUTEST(Matches, ConstPredicateAndCopy)
{
    const int expected = 3;
    CheckPredicate(Matches(Eq(expected)));
}

IUTEST(Matches, ContainerMatcher)
{
    const int values[] = { 1, 3 };
    const ::std::vector<int> v(values, values + 2);
    IUTEST_EXPECT_TRUE(Matches(Contains(3))(v));
    IUTEST_EXPECT_FALSE(Matches(Contains(4))(v));
}

#if !defined(IUTEST_NO_SFINAE)
IUTEST(Matches, PlainValue)
{
    IUTEST_EXPECT_TRUE(Matches(3)(3));
    IUTEST_EXPECT_FALSE(Matches(3)(4));
    IUTEST_EXPECT_TRUE(Matches("abc")(::std::string("abc")));
    IUTEST_EXPECT_FALSE(Matches("abc")(::std::string("def")));
    const ::std::string expected("abc");
    IUTEST_EXPECT_TRUE(Matches(expected)(expected));
    const int values[] = { 3, 4, 3 };
    IUTEST_EXPECT_EQ(2, ::std::count_if(values, values + 3, Matches(3)));
}

IUTEST(Matches, StaticIntegralConstant)
{
    IUTEST_EXPECT_TRUE(Matches(StaticIntegralValue::value)(3));
}

IUTEST(Matches, StoresValueByCopy)
{
    int expected = 3;
    CheckValueCopy(Matches(expected), &expected);
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(Matches, ArrayAndFunctionDecay)
{
    int values[] = { 1, 2 };
    const int const_values[] = { 1, 2 };
    int* value = values;
    const int* const_value = const_values;
    typedef void (*FunctionPointer)();

    const ::iutest::detail::MatcherAsPredicate<int*> array_predicate = Matches(values);
    const ::iutest::detail::MatcherAsPredicate<const int*> const_array_predicate = Matches(const_values);
    const ::iutest::detail::MatcherAsPredicate<FunctionPointer> function_predicate = Matches(FirstFunction);
    IUTEST_EXPECT_TRUE(array_predicate(value));
    IUTEST_EXPECT_TRUE(const_array_predicate(const_value));
    IUTEST_EXPECT_TRUE(function_predicate(&FirstFunction));
    IUTEST_EXPECT_FALSE(function_predicate(&SecondFunction));
}

IUTEST(Matches, VolatileValues)
{
    volatile int number = 3;
    const ::iutest::detail::MatcherAsPredicate<int> number_predicate = Matches(number);
    number = 4;
    IUTEST_EXPECT_EQ(4, number);
    CheckPredicate(number_predicate);

    volatile VolatileValue value(3);
    const ::iutest::detail::MatcherAsPredicate<VolatileValue> predicate = Matches(value);
    value.value = 4;
    IUTEST_EXPECT_EQ(4, value.value);
    CheckPredicate(predicate);

#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
    volatile VolatileValue explicit_value(3);
    const ::iutest::detail::MatcherAsPredicate<VolatileValue> volatile_predicate =
        Matches<VolatileValue>(explicit_value);
    CheckPredicate(volatile_predicate);

    const volatile VolatileValue const_value(3);
    const ::iutest::detail::MatcherAsPredicate<VolatileValue> const_predicate = Matches(const_value);
    CheckPredicate(const_predicate);
    const ::iutest::detail::MatcherAsPredicate<VolatileValue> explicit_predicate =
        Matches<VolatileValue>(const_value);
    CheckPredicate(explicit_predicate);
#endif
}
#endif
#endif

#if !defined(IUTEST_USE_GTEST)
IUTEST(Matches, CopiesMatcherOnce)
{
    CopyCounts copies;
    CopyCountingMatcher matcher(3, &copies);
    const ::iutest::detail::MatcherAsPredicate<CopyCountingMatcher> predicate = Matches(matcher);
    CopyCounts const_copies;
    const CopyCountingMatcher const_matcher(3, &const_copies);
    const ::iutest::detail::MatcherAsPredicate<CopyCountingMatcher> const_predicate = Matches(const_matcher);
    CopyCounts temporary_copies;
    const ::iutest::detail::MatcherAsPredicate<CopyCountingMatcher> temporary_predicate =
        Matches(CopyCountingMatcher(3, &temporary_copies));
#if !defined(IUTEST_NO_SFINAE) \
    && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING) && !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    IUTEST_EXPECT_EQ(0, copies.original_nonconst);
#if IUTEST_HAS_CXX17
    IUTEST_EXPECT_EQ(1, copies.total);
    IUTEST_EXPECT_EQ(1, const_copies.total);
    IUTEST_EXPECT_EQ(1, temporary_copies.total);
#endif
#endif
    matcher.SetExpected(4);
    CheckPredicate(predicate);
    CheckPredicate(const_predicate);
    CheckPredicate(temporary_predicate);
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
