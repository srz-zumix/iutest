//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        random_values_in_range_tests.cpp
 * @brief       iutest bounded random values test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#if IUTEST_HAS_RANDOMVALUES

namespace
{

template<typename T>
void CheckRange(T min, T max)
{
    typedef ::iutest::detail::iuIParamGenerator<T> Generator;
    ::iutest::detail::scoped_ptr<Generator> first(::iutest::RandomValuesInRange(100, min, max, 123));
    ::iutest::detail::scoped_ptr<Generator> second(::iutest::RandomValuesInRange(100, min, max, 123));
    size_t count = 0;
    bool varied = false;
    first->Begin();
    second->Begin();
    const T initial = first->GetCurrent();
    for( ; !first->IsEnd(); first->Next(), second->Next(), ++count )
    {
        IUTEST_ASSERT_FALSE(second->IsEnd());
        const T value = first->GetCurrent();
        IUTEST_EXPECT_GE(value, min);
        IUTEST_EXPECT_LE(value, max);
        IUTEST_EXPECT_EQ(value, second->GetCurrent());
        varied = varied || value != initial;
    }
    IUTEST_EXPECT_TRUE(second->IsEnd());
    IUTEST_EXPECT_EQ(100u, count);
    if( min != max )
    {
        IUTEST_EXPECT_TRUE(varied);
    }
}

}   // end of namespace

IUTEST(RandomValuesInRangeTest, Integers)
{
    CheckRange(-10, 10);
    CheckRange(-100, -90);
    CheckRange(0, 3);
    CheckRange(10u, 20u);
    CheckRange(static_cast<signed char>(-128), static_cast<signed char>(127));
    CheckRange(static_cast<unsigned char>(0), static_cast<unsigned char>(255));
    CheckRange(false, true);
}

IUTEST(RandomValuesInRangeTest, IntegerLimits)
{
    CheckRange((::std::numeric_limits<int>::min)(), (::std::numeric_limits<int>::max)());
    CheckRange(::iutest::UInt64(0), (::std::numeric_limits< ::iutest::UInt64 >::max)());
    CheckRange((::std::numeric_limits< ::iutest::Int64 >::min)(),
        (::std::numeric_limits< ::iutest::Int64 >::max)());
    CheckRange((::std::numeric_limits< ::iutest::Int64 >::min)(), ::iutest::Int64(-1));
    CheckRange((::std::numeric_limits< ::iutest::UInt64 >::max)() - 3,
        (::std::numeric_limits< ::iutest::UInt64 >::max)());
    CheckRange(::iutest::UInt64(0), (::iutest::UInt64(1) << 63));
#if IUTEST_HAS_INT128
    const unsigned __int128 high = static_cast<unsigned __int128>(1) << 64;
    CheckRange(high, high + 3);
    CheckRange(-static_cast<__int128>(high), static_cast<__int128>(high));
    CheckRange((::std::numeric_limits<__int128>::min)(), (::std::numeric_limits<__int128>::max)());
    CheckRange(static_cast<unsigned __int128>(0), (::std::numeric_limits<unsigned __int128>::max)());
#endif
}

IUTEST(RandomValuesInRangeTest, FloatingPoint)
{
    CheckRange(-2.5f, 4.5f);
    CheckRange(0.0, 10.0);
    CheckRange(-100.0, -90.0);
    CheckRange(-(::std::numeric_limits<double>::max)(), (::std::numeric_limits<double>::max)());
#if IUTEST_HAS_LONG_DOUBLE
    CheckRange(static_cast<long double>(-1), static_cast<long double>(1));
#endif
}

IUTEST(RandomValuesInRangeTest, EqualBounds)
{
    CheckRange(7, 7);
    CheckRange(-2.5, -2.5);
    CheckRange((::std::numeric_limits< ::iutest::Int64 >::min)(),
        (::std::numeric_limits< ::iutest::Int64 >::min)());
}

IUTEST(RandomValuesInRangeTest, Empty)
{
    typedef ::iutest::detail::iuIParamGenerator<int> Generator;
    ::iutest::detail::scoped_ptr<Generator> zero(::iutest::RandomValuesInRange(0, 0, 10, 123));
    ::iutest::detail::scoped_ptr<Generator> reversed(::iutest::RandomValuesInRange(10, 10, 0, 123));
    zero->Begin();
    reversed->Begin();
    IUTEST_EXPECT_TRUE(zero->IsEnd());
    IUTEST_EXPECT_TRUE(reversed->IsEnd());
}

class RandomValuesInRangeParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(RandomValuesInRangeParamTest, Bounds)
{
    IUTEST_EXPECT_GE(GetParam(), -5);
    IUTEST_EXPECT_LE(GetParam(), 5);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(Seeded, RandomValuesInRangeParamTest, ::iutest::RandomValuesInRange(5, -5, 5, 123));
IUTEST_INSTANTIATE_TEST_SUITE_P(Unseeded, RandomValuesInRangeParamTest, ::iutest::RandomValuesInRange(5, -5, 5));

#if IUTEST_HAS_CONCAT
IUTEST_INSTANTIATE_TEST_SUITE_P(Concat, RandomValuesInRangeParamTest,
    ::iutest::RandomValuesInRange(2, -5, 0, 123) + ::iutest::Values(5));
#endif

#endif
