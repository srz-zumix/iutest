//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        comparison_matcher_tests.cpp
 * @brief       comparison matcher value and reference lifetime tests
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

#if IUTEST_HAS_CXX11
#include <functional>
#endif

#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

namespace {

#if defined(IUTEST_USE_GTEST)
namespace comparison_detail = ::testing::internal;
#else
namespace comparison_detail = ::iutest::detail;
#endif

#define COMPARISON_VALUE_TESTS(name, actual, changed) \
    typedef comparison_detail::name##Matcher< ::std::string > name##StringMatcher; \
    name##StringMatcher Return##name() { \
        const ::std::string expected = "middle"; \
        return name(expected); \
    } \
    IUTEST(ComparisonMatcher, name##SourceMutation) { \
        ::std::string expected = "middle"; \
        const name##StringMatcher matcher = name(expected); \
        expected = changed; \
        IUTEST_EXPECT_THAT(::std::string(actual), matcher); \
    } \
    IUTEST(ComparisonMatcher, name##SourceLifetime) { \
        const name##StringMatcher matcher = Return##name(); \
        IUTEST_EXPECT_THAT(::std::string(actual), matcher); \
    } \
    IUTEST(ComparisonMatcher, name##Temporary) { \
        const name##StringMatcher matcher = name(::std::string("middle")); \
        IUTEST_EXPECT_THAT(::std::string(actual), matcher); \
    } \
    IUTEST(ComparisonMatcher, name##CopyOutlivesSource) { \
        name##StringMatcher* source = new name##StringMatcher(name(::std::string("middle"))); \
        const name##StringMatcher copy(*source); \
        delete source; \
        IUTEST_EXPECT_THAT(::std::string(actual), copy); \
    }

COMPARISON_VALUE_TESTS(Eq, "middle", "changed")
COMPARISON_VALUE_TESTS(Ne, "changed", "changed")
COMPARISON_VALUE_TESTS(Lt, "alpha", "aaaa")
COMPARISON_VALUE_TESTS(Le, "middle", "aaaa")
COMPARISON_VALUE_TESTS(Gt, "zulu", "zzzz")
COMPARISON_VALUE_TESTS(Ge, "middle", "zzzz")

#undef COMPARISON_VALUE_TESTS

EqStringMatcher ReturnEquals()
{
    const ::std::string expected = "middle";
    return Equals(expected);
}

#if defined(IUTEST_USE_GTEST)
typedef ::testing::Matcher< ::std::string > TypedStringMatcher;
#else
typedef ::iutest::detail::TypedEqMatcher< ::std::string > TypedStringMatcher;
#endif

TypedStringMatcher ReturnTypedEq()
{
    const ::std::string expected = "middle";
    return TypedEq< ::std::string >(expected);
}

IUTEST(ComparisonMatcher, EqualsValueAndCopy)
{
    ::std::string expected = "middle";
    const EqStringMatcher matcher = Equals(expected);
    expected = "changed";
    IUTEST_EXPECT_THAT(::std::string("middle"), matcher);
    EqStringMatcher* source = new EqStringMatcher(ReturnEquals());
    const EqStringMatcher copy(*source);
    delete source;
    IUTEST_EXPECT_THAT(::std::string("middle"), copy);
    const EqStringMatcher temporary = Equals(::std::string("middle"));
    IUTEST_EXPECT_THAT(::std::string("middle"), temporary);
}

IUTEST(ComparisonMatcher, TypedEqCopyOutlivesSource)
{
    TypedStringMatcher* source = new TypedStringMatcher(ReturnTypedEq());
    TypedStringMatcher copy(*source);
    delete source;
    IUTEST_EXPECT_THAT(::std::string("middle"), copy);
}

IUTEST(ComparisonMatcher, StringsAndArrays)
{
    IUTEST_EXPECT_THAT(::std::string("middle"), Eq("middle"));
    IUTEST_EXPECT_THAT("middle", Eq(::std::string("middle")));
    const char text[] = "middle";
    IUTEST_EXPECT_THAT(::std::string("middle"), Eq(text));
    int values[] = { 1, 2 };
    const int* pointer = values;
    IUTEST_EXPECT_THAT(pointer, Eq(values));
    IUTEST_EXPECT_THAT(pointer, Ne(values + 1));
    IUTEST_EXPECT_THAT(pointer, Lt(values + 1));
    IUTEST_EXPECT_THAT(pointer, Le(values));
    IUTEST_EXPECT_THAT(pointer + 1, Gt(values));
    IUTEST_EXPECT_THAT(pointer, Ge(values));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_THAT(text, Eq("middle"));
    IUTEST_EXPECT_THAT(text, Equals("middle"));
#endif
}

IUTEST(ComparisonMatcher, PointerValueIsCopied)
{
    int values[] = { 1, 2 };
    int* expected = values;
    const comparison_detail::EqMatcher<int*> matcher = Eq(expected);
    expected = values + 1;
    IUTEST_EXPECT_THAT(values, matcher);
}

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
IUTEST(ComparisonMatcher, ComposedValues)
{
    IUTEST_EXPECT_THAT(5, AllOf(Ge(5), Le(5), Not(Ne(5))));
    IUTEST_EXPECT_THAT(5, AnyOf(Eq(0), Eq(5)));
}
#endif

#if !defined(IUTEST_USE_GTEST)
IUTEST(ComparisonMatcher, NoArgumentComparisons)
{
    IUTEST_EXPECT_TRUE(Eq()(5, 5));
    IUTEST_EXPECT_TRUE(Ne()(5, 6));
    IUTEST_EXPECT_TRUE(Lt()(5, 6));
    IUTEST_EXPECT_TRUE(Le()(5, 5));
    IUTEST_EXPECT_TRUE(Gt()(6, 5));
    IUTEST_EXPECT_TRUE(Ge()(5, 5));
}
#endif

#if IUTEST_HAS_CXX11

class NonCopyableValue
{
public:
    explicit NonCopyableValue(int value) : m_value(value) {}
    operator int() const { return m_value; }
    void Set(int value) { m_value = value; }
private:
    NonCopyableValue(const NonCopyableValue&);
    NonCopyableValue& operator =(const NonCopyableValue&);
    int m_value;
};

template<typename M>
void CheckReference(M matcher, NonCopyableValue& expected, int actual, int changed)
{
    M copy(matcher);
    IUTEST_EXPECT_THAT(actual, copy);
    expected.Set(changed);
    IUTEST_EXPECT_THAT(actual, Not(copy));
}

#define COMPARISON_REFERENCE_TESTS(name, actual, changed) \
    IUTEST(ComparisonMatcher, name##ExplicitReference) { \
        NonCopyableValue expected(5); \
        CheckReference(name(::std::ref(expected)), expected, actual, changed); \
        expected.Set(5); \
        CheckReference(name(::std::cref(expected)), expected, actual, changed); \
    }

COMPARISON_REFERENCE_TESTS(Eq, 5, 6)
COMPARISON_REFERENCE_TESTS(Ne, 6, 6)
COMPARISON_REFERENCE_TESTS(Lt, 4, 4)
COMPARISON_REFERENCE_TESTS(Le, 5, 4)
COMPARISON_REFERENCE_TESTS(Gt, 6, 6)
COMPARISON_REFERENCE_TESTS(Ge, 5, 6)
COMPARISON_REFERENCE_TESTS(Equals, 5, 6)

#undef COMPARISON_REFERENCE_TESTS

IUTEST(ComparisonMatcher, StringReferences)
{
    ::std::string expected = "before";
    const comparison_detail::EqMatcher< ::std::reference_wrapper< ::std::string > >
        matcher = Eq(::std::ref(expected));
    const comparison_detail::EqMatcher< ::std::reference_wrapper<const ::std::string > >
        const_matcher = Eq(::std::cref(expected));
    expected = "after";
    IUTEST_EXPECT_THAT(::std::string("after"), matcher);
    IUTEST_EXPECT_THAT(::std::string("after"), const_matcher);
}

#if IUTEST_HAS_STD_TUPLE
IUTEST(ComparisonMatcher, NoArgumentTupleComparisons)
{
    IUTEST_EXPECT_THAT(::std::make_tuple(5, 5), Eq());
    IUTEST_EXPECT_THAT(::std::make_tuple(5, 6), Ne());
    IUTEST_EXPECT_THAT(::std::make_tuple(5, 6), Lt());
    IUTEST_EXPECT_THAT(::std::make_tuple(5, 5), Le());
    IUTEST_EXPECT_THAT(::std::make_tuple(6, 5), Gt());
    IUTEST_EXPECT_THAT(::std::make_tuple(5, 5), Ge());
}
#endif

#endif

}   // namespace

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
