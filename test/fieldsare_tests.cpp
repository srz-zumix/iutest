//======================================================================
/**
 * @file        fieldsare_tests.cpp
 * @brief       FieldsAre matcher tests
 *
 * Copyright (C) 2026, Takazumi Shirayanagi
 * This software is released under the new BSD License,
 * see LICENSE
*/
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHER_FIELDSARE

#include <memory>
#include <tuple>
#include <utility>

using namespace ::iutest::matchers;

namespace {

struct Point { int x; int y; };
struct Empty {};
struct Single { int value; };
struct MoveOnly { ::std::unique_ptr<int> value; int tag; };
struct Sixteen
{
    int a0, a1, a2, a3, a4, a5, a6, a7;
    int a8, a9, a10, a11, a12, a13, a14, a15;
};

const Point point = { 1, 2 };
const Sixteen sixteen = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

template<size_t ...I>
void CheckArity(::std::index_sequence<I...>)
{
    const int values[] = { static_cast<int>(I)... };
    const auto tuple = ::std::make_tuple(static_cast<int>(I)...);
    IUTEST_EXPECT_THAT(values, FieldsAre(static_cast<int>(I)...));
    IUTEST_EXPECT_THAT(tuple, FieldsAre(static_cast<int>(I)...));
}

template<size_t ...I>
void CheckAllArities(::std::index_sequence<I...>)
{
    (CheckArity(::std::make_index_sequence<I + 1>()), ...);
}

} // namespace

IUTEST(FieldsAreTest, Aggregate)
{
    IUTEST_EXPECT_THAT(point, FieldsAre(Ge(0), 2));
    IUTEST_EXPECT_THAT(point, FieldsAre(1, Lt(3)));
    IUTEST_EXPECT_THAT((Single{ 3 }), FieldsAre(3));
}

IUTEST(FieldsAreTest, Tuple)
{
    const auto tuple = ::std::make_tuple(1, ::std::string("hello"), 3.0);
    IUTEST_EXPECT_THAT(tuple, FieldsAre(1, StartsWith("he"), DoubleEq(3.0)));
    IUTEST_EXPECT_THAT(tuple, FieldsAre(_, "hello", Ge(0.0)));
}

IUTEST(FieldsAreTest, Pair)
{
    const auto pair = ::std::make_pair(1, ::std::string("hello"));
    IUTEST_EXPECT_THAT(pair, FieldsAre(Ge(0), "hello"));
}

#if !defined(IUTEST_USE_GTEST)
// gMock 1.11 cannot instantiate FieldsAre() with an empty matcher pack.
IUTEST(FieldsAreTest, Empty)
{
    IUTEST_EXPECT_THAT(Empty(), FieldsAre());
    IUTEST_EXPECT_THAT(::std::tuple<>(), FieldsAre());
}
#endif

IUTEST(FieldsAreTest, DoesNotCopyFields)
{
    const MoveOnly value = { ::std::unique_ptr<int>(new int(7)), 1 };
    IUTEST_EXPECT_THAT(value, FieldsAre(Pointee(7), 1));
    IUTEST_EXPECT_THAT(::std::tie(value.value, value.tag), FieldsAre(Pointee(7), 1));
}

IUTEST(FieldsAreTest, Nested)
{
    const auto value = ::std::make_pair(point, ::std::make_tuple(3, 4));
    IUTEST_EXPECT_THAT(value, FieldsAre(FieldsAre(1, 2), FieldsAre(3, 4)));
    IUTEST_EXPECT_THAT(point, Not(FieldsAre(1, 3)));
#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
    IUTEST_EXPECT_THAT(point, AllOf(FieldsAre(1, _), FieldsAre(_, 2)));
#endif
}

IUTEST(FieldsAreTest, SixteenFields)
{
    IUTEST_EXPECT_THAT(sixteen, FieldsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
}

IUTEST(FieldsAreTest, AllSupportedArities)
{
    CheckAllArities(::std::make_index_sequence<16>());
}

IUTEST(FieldsAreTest, StoresExpectedValues)
{
    auto matcher = FieldsAre(1, ::std::string("hello"));
    const auto value = ::std::make_pair(1, ::std::string("hello"));
    IUTEST_EXPECT_THAT(value, matcher);
}

IUTEST(FieldsAreTest, FailureIdentifiesFirstField)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(0, 2)), "field #0");
}

IUTEST(FieldsAreTest, FailureIdentifiesSecondField)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(1, 3)), "field #1");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(::std::make_tuple(1, 2), FieldsAre(1, 3)), "field #1");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(::std::make_pair(1, 2), FieldsAre(1, 3)), "field #1");
}

IUTEST(FieldsAreTest, FailureAtUpperBound)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(sixteen,
        FieldsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16)), "field #15");
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(FieldsAreTest, FailureIncludesMatcherAndActual)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(1, Ge(3))),
        "field #1 does not match (2): Ge: 3");
}

IUTEST(FieldsAreTest, Description)
{
    IUTEST_EXPECT_EQ("FieldsAre: {1, Ge: 2}", FieldsAre(1, Ge(2)).WhichIs());
    IUTEST_EXPECT_EQ("FieldsAre: {}", FieldsAre().WhichIs());
}
#endif

#else

IUTEST(FieldsAreTest, Disabled)
{
    IUTEST_EXPECT_EQ(0, IUTEST_HAS_MATCHER_FIELDSARE);
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
