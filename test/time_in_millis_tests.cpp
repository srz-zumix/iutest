//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        time_in_millis_tests.cpp
 * @brief       GoogleTest time type compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <climits>
#include <limits>
#include "../include/gtest/iutest_switch.hpp"

namespace
{

#if defined(IUTEST_USE_GTEST)
typedef ::testing::TimeInMillis GetterTime;
#else
typedef ::iutest::TimeInMillisec GetterTime;
#endif

template<typename T>
void CheckTimeGetter(const T& object, GetterTime (T::*getter)() const)
{
    const GetterTime value = (object.*getter)();
    const ::testing::TimeInMillis compatible_value = value;
    IUTEST_EXPECT_GE(compatible_value, 0);
    IUTEST_EXPECT_EQ(value, static_cast<GetterTime>(compatible_value));
}

}   // namespace

IUTEST(TimeInMillisTest, Signed64Bit)
{
    IUTEST_EXPECT_TRUE(::std::numeric_limits< ::testing::TimeInMillis>::is_signed);
    IUTEST_EXPECT_EQ(63, ::std::numeric_limits< ::testing::TimeInMillis>::digits);
    IUTEST_EXPECT_EQ(64u, sizeof(::testing::TimeInMillis) * CHAR_BIT);
    const ::testing::TimeInMillis negative = -1;
    IUTEST_EXPECT_LT(negative, 0);
    IUTEST_EXPECT_EQ(-1, negative);
    const ::testing::TimeInMillis large_negative = -(static_cast< ::testing::TimeInMillis>(1) << 32);
    IUTEST_EXPECT_LT(large_negative, (::std::numeric_limits<int>::min)());
    IUTEST_EXPECT_EQ(-1, large_negative / (static_cast< ::testing::TimeInMillis>(1) << 32));

#if !defined(IUTEST_USE_GTEST)
    const ::iutest::TimeInMillis native_negative = negative;
    IUTEST_EXPECT_EQ(negative, native_negative);
    IUTEST_EXPECT_EQ(sizeof(::iutest::Int64), sizeof(native_negative));
#endif
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(TimeInMillisTest, LegacyUnsignedType)
{
    IUTEST_EXPECT_FALSE(::std::numeric_limits< ::iutest::TimeInMillisec>::is_signed);
    IUTEST_EXPECT_GE(::std::numeric_limits< ::iutest::TimeInMillisec>::digits, 64);
    const ::iutest::TimeInMillisec value = 123;
    const ::iutest::TimeInMillis converted = value;
    IUTEST_EXPECT_EQ(123, converted);
    const ::iutest::TimeInMillisec maximum =
        (::std::numeric_limits< ::iutest::TimeInMillisec>::max)();
    IUTEST_EXPECT_GT(maximum, static_cast< ::iutest::TimeInMillisec>(
        (::std::numeric_limits< ::iutest::TimeInMillis>::max)()));
}
#endif

IUTEST(TimeInMillisTest, GetterSignatures)
{
    const ::testing::UnitTest& unit = *::testing::UnitTest::GetInstance();
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01070000
    CheckTimeGetter(unit, &::testing::UnitTest::start_timestamp);
#endif
    CheckTimeGetter(unit, &::testing::UnitTest::elapsed_time);
    const ::testing::TestResult result;
    CheckTimeGetter(result, &::testing::TestResult::elapsed_time);

#if IUTEST_HAS_TESTSUITE
    const ::testing::TestSuite* suite = unit.current_test_suite();
    IUTEST_ASSERT_NOTNULL(suite);
    CheckTimeGetter(*suite, &::testing::TestSuite::elapsed_time);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01100000
    CheckTimeGetter(*suite, &::testing::TestSuite::start_timestamp);
#endif
#else
    const ::testing::TestCase* suite = unit.current_test_case();
    IUTEST_ASSERT_NOTNULL(suite);
    CheckTimeGetter(*suite, &::testing::TestCase::elapsed_time);
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
