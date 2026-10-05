//======================================================================
// Copyright (C) 2026, Takazumi Shirayanagi
// This software is released under the new BSD License, see LICENSE.
//======================================================================
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHER_FIELDSARE
#include <memory>
#include <tuple>
#include <utility>

using namespace ::iutest::matchers;

namespace {
struct Point { int x; int y; };
struct Single { int value; };
struct ManyFields
{
    int f0, f1, f2, f3, f4, f5, f6, f7;
    int f8, f9, f10, f11, f12, f13, f14, f15;
};
struct NonCopyable { ::std::unique_ptr<int> value; int number; };

template<size_t ...I>
void CheckArity(::std::index_sequence<I...>)
{
    const auto value = ::std::make_tuple(static_cast<int>(I)...);
    IUTEST_EXPECT_THAT(value, FieldsAre(static_cast<int>(I)...));
}
}   // namespace

IUTEST(FieldsAre, Aggregate)
{
    const Point point = { 0, 1 };
    IUTEST_EXPECT_THAT(point, FieldsAre(Ge(0), 1));
    IUTEST_EXPECT_THAT(Single{42}, FieldsAre(42));
}

IUTEST(FieldsAre, Tuple)
{
    const auto value = ::std::make_tuple(1, ::std::string("hello"), 3.0);
    IUTEST_EXPECT_THAT(value, FieldsAre(Ge(0), StrEq("hello"), DoubleEq(3.0)));
}

IUTEST(FieldsAre, Pair)
{
    const ::std::pair<int, ::std::string> value(2, "hello");
    IUTEST_EXPECT_THAT(value, FieldsAre(2, HasSubstr("ell")));
}

IUTEST(FieldsAre, SixteenFields)
{
    static const ManyFields value = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    IUTEST_EXPECT_THAT(value, FieldsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(value, FieldsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 42)),
        "field #15");
}

IUTEST(FieldsAre, AllArities)
{
#define IIUT_CHECK_FIELDSARE_ARITY(i, unused1, unused2) CheckArity(::std::make_index_sequence<i + 1>());
    IUTEST_PP_REPEAT_BINARY(16, IIUT_CHECK_FIELDSARE_ARITY, unused, unused)
#undef IIUT_CHECK_FIELDSARE_ARITY
}

IUTEST(FieldsAre, Array)
{
    const int value[] = { 0, 1, 2 };
    IUTEST_EXPECT_THAT(value, FieldsAre(0, Ge(1), 2));
}

IUTEST(FieldsAre, ReusableMatcher)
{
    auto matcher = FieldsAre(0, 1);
    const Point first = { 0, 1 };
    const Point second = { 0, 2 };
    IUTEST_EXPECT_THAT(first, matcher);
    IUTEST_EXPECT_THAT(first, Not(Not(matcher)));
    IUTEST_EXPECT_THAT(second, Not(matcher));
    IUTEST_EXPECT_THAT(first, matcher);
}

IUTEST(FieldsAre, NonCopyableFields)
{
    const NonCopyable value = { ::std::unique_ptr<int>(new int(42)), 1 };
    IUTEST_EXPECT_THAT(value, FieldsAre(Pointee(42), 1));
    const auto tuple = ::std::make_tuple(::std::unique_ptr<int>(new int(42)), 1);
    IUTEST_EXPECT_THAT(tuple, FieldsAre(Pointee(42), 1));
}

IUTEST(FieldsAre, Nested)
{
    const auto value = ::std::make_tuple(Point{0, 1}, ::std::make_pair(2, 3));
    IUTEST_EXPECT_THAT(value, FieldsAre(FieldsAre(0, 1), FieldsAre(2, 3)));
}

IUTEST(FieldsAre, FailureMessages)
{
    static const Point point = { 0, 1 };
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(0, 2)), "field #1");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(Gt(0), 1)), "field #0");
    static const auto tuple = ::std::make_tuple(0, 1);
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(tuple, FieldsAre(0, 2)), "field #1");
    static const auto pair = ::std::make_pair(0, 1);
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(pair, FieldsAre(0, 2)), "field #1");
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(point, FieldsAre(0, Gt(1))), "Gt: 1");
    IUTEST_EXPECT_EQ("FieldsAre: {0, 1}", FieldsAre(0, 1).WhichIs());
#endif
}

#else

IUTEST(FieldsAre, Disabled)
{
    IUTEST_EXPECT_EQ(0, IUTEST_HAS_MATCHER_FIELDSARE);
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
