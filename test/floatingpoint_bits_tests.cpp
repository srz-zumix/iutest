//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        floatingpoint_bits_tests.cpp
 * @brief       floating-point representation and ULP tests
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

#include <cfloat>
#include <climits>
#include <limits>

#if !defined(IUTEST_USE_GTEST)
namespace
{

#if defined(__LONG_DOUBLE_IBM128__)
IUTEST(FloatingPointBitsTest, IBMDoubleDouble)
{
    IUTEST_EXPECT_EQ(0, IUTEST_HAS_LONG_DOUBLE);
    long double value = 0.0L;
    IUTEST_EXPECT_TRUE(::iutest::detail::StringToValue("1.25", value));
    IUTEST_EXPECT_TRUE(value == 1.25L);
    ::iutest::iu_stringstream stream;
    stream << value;
    IUTEST_EXPECT_STRIN("1.25", stream.str());
}
#endif

template<typename T>
void CheckBinaryFloat(int mantissa_width, unsigned int exponent_bias)
{
    typedef ::std::numeric_limits<T> Limits;
    typedef ::iutest::floating_point<T> Float;
    typedef typename Float::UInt UInt;
    IUTEST_ASSUME_TRUE(Limits::is_iec559);

    const UInt sign = UInt(1) << (sizeof(T) * CHAR_BIT - 1);
    const UInt exponent = UInt(exponent_bias) << mantissa_width;
    const UInt infinity = UInt(2 * exponent_bias + 1) << mantissa_width;
    const UInt fraction = UInt(1) << (mantissa_width - 1);
    const T value = static_cast<T>(1.5);
    const Float normal(-value);
    IUTEST_EXPECT_EQ(sign | exponent | fraction, normal.bits());
    IUTEST_EXPECT_EQ(normal.bits(), normal.enable_bits());
    IUTEST_EXPECT_EQ(sign, normal.sign_bit());
    IUTEST_EXPECT_EQ(exponent, normal.exponent_bits());
    IUTEST_EXPECT_EQ(fraction, normal.fraction_bits());
    IUTEST_EXPECT_EQ(fraction, normal.mantissa_bits());
    IUTEST_EXPECT_EQ(fraction, normal.economized_mantissa_bits());
    IUTEST_EXPECT_FALSE(normal.is_inf());
    IUTEST_EXPECT_FALSE(normal.is_nan());
    IUTEST_EXPECT_EQ(normal.bits(), Float(normal.raw()).bits());
    IUTEST_EXPECT_EQ(normal.bits(), Float(static_cast<T>(normal)).bits());

    const T zero = static_cast<T>(0);
    const Float positive_zero;
    const Float negative_zero(-zero);
    IUTEST_EXPECT_EQ(UInt(0), positive_zero.bits());
    IUTEST_EXPECT_EQ(sign, negative_zero.bits());
    IUTEST_EXPECT_EQ(sign, Float(negative_zero.raw()).bits());
    IUTEST_EXPECT_TRUE(positive_zero.AlmostEquals(negative_zero));

    const T subnormal = (Limits::denorm_min)();
    const Float tiny(subnormal);
    const Float negative_tiny(-subnormal);
    IUTEST_EXPECT_EQ(UInt(1), tiny.bits());
    IUTEST_EXPECT_EQ(UInt(0), tiny.exponent_bits());
    IUTEST_EXPECT_EQ(UInt(1), tiny.mantissa_bits());
    IUTEST_EXPECT_EQ(sign | UInt(1), negative_tiny.bits());
    IUTEST_EXPECT_TRUE(tiny.AlmostEquals(negative_tiny));
    IUTEST_EXPECT_TRUE(negative_zero.AlmostEquals(Float(subnormal * static_cast<T>(4))));
    IUTEST_EXPECT_FALSE(negative_zero.AlmostEquals(Float(subnormal * static_cast<T>(5))));

    const T ulp = Limits::epsilon();
    IUTEST_EXPECT_TRUE(normal.AlmostEquals(Float(-value - ulp * static_cast<T>(4))));
    IUTEST_EXPECT_FALSE(normal.AlmostEquals(Float(-value - ulp * static_cast<T>(5))));

    const Float positive_inf = Float::PINF();
    const Float negative_inf = Float::NINF();
    IUTEST_EXPECT_EQ(infinity, positive_inf.bits());
    IUTEST_EXPECT_EQ(sign | infinity, negative_inf.bits());
    IUTEST_EXPECT_EQ(Float(Limits::infinity()).bits(), Float(positive_inf.raw()).bits());
    IUTEST_EXPECT_EQ(Float(-Limits::infinity()).bits(), Float(negative_inf.raw()).bits());
    IUTEST_EXPECT_TRUE(positive_inf.is_inf());
    IUTEST_EXPECT_TRUE(negative_inf.is_inf());
    IUTEST_EXPECT_FALSE(positive_inf.is_nan());
    IUTEST_EXPECT_TRUE(positive_inf.AlmostEquals(Float((Limits::max)())));
    IUTEST_EXPECT_FALSE(positive_inf.AlmostEquals(negative_inf));

    const Float positive_nan = Float::PNAN();
    const Float negative_nan = Float::NNAN();
    IUTEST_EXPECT_EQ(infinity | UInt(1), positive_nan.bits());
    IUTEST_EXPECT_EQ(sign | positive_nan.bits(), negative_nan.bits());
    IUTEST_EXPECT_TRUE(positive_nan.is_nan());
    IUTEST_EXPECT_TRUE(negative_nan.is_nan());
    IUTEST_EXPECT_FALSE(positive_nan.is_inf());
    IUTEST_EXPECT_FALSE(positive_nan.AlmostEquals(positive_nan));
    IUTEST_EXPECT_FALSE(positive_nan.AlmostEquals(positive_inf));
    IUTEST_EXPECT_TRUE(positive_nan.NanSensitiveAlmostEquals(positive_nan));
    IUTEST_EXPECT_EQ(infinity | fraction, Float::PQNAN().bits());
    IUTEST_EXPECT_EQ(sign | infinity | fraction, Float::NQNAN().bits());

    Float assigned(negative_zero);
    IUTEST_EXPECT_EQ(sign, assigned.bits());
    assigned = value;
    IUTEST_EXPECT_EQ(exponent | fraction, assigned.bits());
    assigned = negative_nan;
    IUTEST_EXPECT_EQ(negative_nan.bits(), assigned.bits());
    assigned = Float::PQNAN().raw();
    IUTEST_EXPECT_EQ(infinity | fraction, assigned.bits());
}

IUTEST(FloatingPointBitsTest, Float)
{
    CheckBinaryFloat<float>(23, 127);
}

IUTEST(FloatingPointBitsTest, Double)
{
    CheckBinaryFloat<double>(52, 1023);
}

#if IUTEST_HAS_LONG_DOUBLE && LDBL_MANT_DIG == 64
IUTEST(FloatingPointBitsTest, X87Padding)
{
    typedef ::iutest::floating_point<long double> Float;
    typedef Float::UInt UInt;
    const UInt bits = (UInt(0x3fff) << 64) | (UInt(1) << 63);
    const Float one(1.0L);
    IUTEST_EXPECT_EQ(bits, one.bits());
    IUTEST_EXPECT_EQ(bits, Float(one.raw()).bits());
    IUTEST_EXPECT_TRUE(Float(Float::PINF().raw()).is_inf());
}
#endif

#if IUTEST_HAS_FLOAT128 && IUTEST_FLT128_MANT_DIG == 113
IUTEST(FloatingPointBitsTest, Float128)
{
    typedef ::iutest::floating_point<__float128> Float;
    typedef Float::UInt UInt;
    const Float negative_inf = Float::NINF();
    const UInt expected = UInt(0xffff) << 112;
    IUTEST_EXPECT_EQ(expected, negative_inf.bits());
    IUTEST_EXPECT_EQ(expected, Float(negative_inf.raw()).bits());
    IUTEST_EXPECT_TRUE(negative_inf.is_inf());
    IUTEST_EXPECT_TRUE(Float::PNAN().is_nan());
}
#endif

}   // end of namespace
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
