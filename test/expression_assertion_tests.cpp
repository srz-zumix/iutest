//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        expression_assertion_tests.cpp
 * @brief       iutest expression assertion test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

int f(void)
{
    return 42;
}
bool g(void)
{
    return false;
}
template<typename T, typename U>
int x(T a, U b)
{
    return a * b;
}
int z(void)
{
    return 0;
}

IUTEST(Expression, Monadic)
{
    IUTEST_EXPECT(true);
    IUTEST_EXPECT(f());
}

IUTEST(Expression, Comparison)
{
    IUTEST_EXPECT(true);
    IUTEST_EXPECT(f());
    IUTEST_EXPECT(f() == 42);
    IUTEST_EXPECT(f() != 41);
    IUTEST_EXPECT(f() <= 42);
    IUTEST_EXPECT(f() >= 42);
    IUTEST_EXPECT(f() <  50);
    IUTEST_EXPECT(f() >  40);
    IUTEST_EXPECT(f() &&  1);
    IUTEST_EXPECT(f() ||  0);
}

IUTEST(Expression, Arithmetic)
{
    IUTEST_EXPECT(f() + 2 == 44);
    IUTEST_EXPECT(f() - 2 == 40);
    IUTEST_EXPECT(f() * 2 == 84);
    IUTEST_EXPECT(f() / 2 == 21);
    IUTEST_EXPECT(f() % 4 == 2);
    IUTEST_EXPECT(f() + f() + f() == 126);
}

#if IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE
IUTEST(Expression, Bitwise)
{
    IUTEST_EXPECT(f() & 2);
    IUTEST_EXPECT(z() | 1);
}
#endif

IUTEST(Expression, Logical)
{
    IUTEST_EXPECT(f() == 42 && g() == false );
    IUTEST_EXPECT(f() != 42 || g() == false );
}

#ifndef IUTEST_NO_VARIADIC_MACROS
IUTEST(Expression, VariadicMacro)
{
    IUTEST_ASSERT(x<int, int>(1, 42) == 42);
    IUTEST_EXPECT(x<int, int>(1, 42) == 42);
    IUTEST_INFORM(x<int, int>(1, 42) == 42);
    IUTEST_ASSUME(x<int, int>(1, 42) == 42);
    IUTEST_ASSERT_NOT(x<int, int>(1, 42) != 42);
    IUTEST_EXPECT_NOT(x<int, int>(1, 42) != 42);
    IUTEST_INFORM_NOT(x<int, int>(1, 42) != 42);
    IUTEST_ASSUME_NOT(x<int, int>(1, 42) != 42);
}
#endif

IUTEST(ExpressionNot, Monadic)
{
    IUTEST_EXPECT_NOT(false);
    IUTEST_EXPECT_NOT(!f());
}

IUTEST(ExpressionNot, Comparison)
{
    IUTEST_EXPECT_NOT(f() == 41);
    IUTEST_EXPECT_NOT(f() != 42);
    IUTEST_EXPECT_NOT(f() <= 41);
    IUTEST_EXPECT_NOT(f() >= 43);
    IUTEST_EXPECT_NOT(f() <  40);
    IUTEST_EXPECT_NOT(f() >  50);
    IUTEST_EXPECT_NOT(g() &&  true);
    IUTEST_EXPECT_NOT(g() ||  false);
}

IUTEST(ExpressionNot, Arithmetic)
{
    IUTEST_EXPECT_NOT(f() + 2 == 1);
    IUTEST_EXPECT_NOT(f() - 2 == 1);
    IUTEST_EXPECT_NOT(f() * 2 == 1);
    IUTEST_EXPECT_NOT(f() / 2 == 1);
    IUTEST_EXPECT_NOT(f() % 4 == 1);
    IUTEST_EXPECT_NOT(f() + f() + f() == 1);
}

#if IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE
IUTEST(ExpressionNot, Bitwise)
{
    IUTEST_EXPECT_NOT(f() & 1);
    IUTEST_EXPECT_NOT(z() | 0);
}
#endif

IUTEST(ExpressionNot, Logical)
{
    IUTEST_EXPECT_NOT(f() == 42 && g() );
    IUTEST_EXPECT_NOT(f() != 42 || g() );
}

#if !defined(IUTEST_USE_GTEST)
#  define CHECK_FATAL_FAILURE(expr, str)    IUTEST_EXPECT_FATAL_FAILURE(expr, str)
#else
#  define CHECK_FATAL_FAILURE(expr, str)    IUTEST_EXPECT_FATAL_FAILURE(expr, "")
#endif

IUTEST(ExpressionFail, Monadic)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(false), "expansion: false");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(!f()) , "expansion: false");
}

IUTEST(ExpressionFail, Comparison)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() == 41), "expansion: 42 == 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42), "expansion: 42 != 42");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() <  41), "expansion: 42 < 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() <= 41), "expansion: 42 <= 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() >  43), "expansion: 42 > 43");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() >= 43), "expansion: 42 >= 43");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(g() &&  0), "expansion: false && 0");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(g() ||  0), "expansion: false || 0");
}

#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE
IUTEST(ExpressionFail, Arithmetic)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() + 2 == 1), "expansion: 42 + 2 == 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() - 2 == 1), "expansion: 42 - 2 == 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() * 2 == 1), "expansion: 42 * 2 == 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() / 2 == 1), "expansion: 42 / 2 == 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() % 4 == 1), "expansion: 42 % 4 == 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() + f() + f() == 1), "expansion: 42 + 42 + 42 == 1");
}
#endif

IUTEST(ExpressionFail, Logical)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42 || f() == 32 ), "expansion: 42 != 42 || false");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42 IUTEST_OPERAND(||) f() == 32 ), "expansion: 42 != 42 || 42 == 32");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() != 42 IUTEST_OPERAND(&&) f() == 32 ), "expansion: 42 != 42 && 42 == 32");
}

#if IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE
IUTEST(ExpressionFail, Bitwise)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(f() & 1), "expansion: 42 & 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT(z() | 0), "expansion: 0 | 0");
}
#endif


IUTEST(ExpressionNotFail, Monadic)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(true), "expansion: true");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f()) , "expansion: 42");
}

IUTEST(ExpressionNotFail, Comparison)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() == 42), "expansion: 42 == 42");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() != 41), "expansion: 42 != 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() <  43), "expansion: 42 < 43");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() <= 43), "expansion: 42 <= 43");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() >  41), "expansion: 42 > 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() >= 41), "expansion: 42 >= 41");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() &&  1), "expansion: 42 && 1");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(g() ||  1), "expansion: false || 1");
}

#if IUTEST_HAS_ARITHMETIC_EXPRESSION_DECOMPOSE
IUTEST(ExpressionNotFail, Arithmetic)
{
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() + 2 == 44), "expansion: 42 + 2 == 44");
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() - 2 == 40), "expansion: 42 - 2 == 40");
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() * 2 == 84), "expansion: 42 * 2 == 84");
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() / 2 == 21), "expansion: 42 / 2 == 21");
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() % 4 == 2), "expansion: 42 % 4 == 2");
    CHECK_FATAL_FAILURE(IUTEST_ASSERT_NOT(f() + f() + f() == 126), "expansion: 42 + 42 + 42 == 126");
}
#endif

IUTEST(ExpressionNotFail, Logical)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() != 42 || f() == 42 ), "expansion: 42 != 42 || true");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() != 42 IUTEST_OPERAND(||) f() == 42 ), "expansion: 42 != 42 || 42 == 42");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() != 42 || IUTEST_EXPRESSION(f() == 42) ), "expansion: 42 != 42 || 42 == 42");
}

#if IUTEST_HAS_BITWISE_EXPRESSION_DECOMPOSE
IUTEST(ExpressionNotFail, Bitwise)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(f() & 2), "expansion: 42 & 2");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_NOT(z() | 1), "expansion: 0 | 1");
}
#endif

IUTEST(ExpressionMacro, True)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_TRUE(IUTEST_EXPRESSION(f() != 42)), "42 != 42");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_TRUE(IUTEST_EXPRESSION(f() != 42) && IUTEST_EXPRESSION(f() != 10)), "42 != 42 && 42 != 10");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_TRUE(IUTEST_EXPRESSION(f() != 42) || IUTEST_EXPRESSION(f() == 10)), "42 != 42 || 42 == 10");
}
IUTEST(ExpressionMacro, False)
{
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_FALSE(IUTEST_EXPRESSION(f() == 42)), "42 == 42");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_FALSE(IUTEST_EXPRESSION(f() != 41) && IUTEST_EXPRESSION(f() != 10)), "42 != 41 && 42 != 10");
    CHECK_FATAL_FAILURE( IUTEST_ASSERT_FALSE(IUTEST_EXPRESSION(f() != 42) || IUTEST_EXPRESSION(f() == 42)), "42 != 42 || 42 == 42");
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

