//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pp_tests.cpp
 * @brief       pp test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#define PPTEST_DEC(n)   IUTEST_STATIC_ASSERT(n-1 == IUTEST_PP_DEC(n))

IUTEST(PPTest, Dec)
{
    PPTEST_DEC(1);
    PPTEST_DEC(2);
    PPTEST_DEC(3);
    PPTEST_DEC(4);
    PPTEST_DEC(5);
    PPTEST_DEC(6);
    PPTEST_DEC(7);
    PPTEST_DEC(8);
    PPTEST_DEC(9);
    PPTEST_DEC(10);
    PPTEST_DEC(11);
    PPTEST_DEC(12);
    PPTEST_DEC(13);
    PPTEST_DEC(14);
    PPTEST_DEC(15);
    PPTEST_DEC(16);
    PPTEST_DEC(17);
    PPTEST_DEC(18);
    PPTEST_DEC(19);
    PPTEST_DEC(20);
    PPTEST_DEC(21);
    PPTEST_DEC(22);
    PPTEST_DEC(23);
    PPTEST_DEC(24);
    PPTEST_DEC(25);
    PPTEST_DEC(26);
    PPTEST_DEC(27);
    PPTEST_DEC(28);
    PPTEST_DEC(29);
    PPTEST_DEC(30);
    PPTEST_DEC(31);
    PPTEST_DEC(32);
    PPTEST_DEC(33);
    PPTEST_DEC(34);
    PPTEST_DEC(35);
    PPTEST_DEC(36);
    PPTEST_DEC(37);
    PPTEST_DEC(38);
    PPTEST_DEC(39);
    PPTEST_DEC(40);
    PPTEST_DEC(41);
    PPTEST_DEC(42);
    PPTEST_DEC(43);
    PPTEST_DEC(44);
    PPTEST_DEC(45);
    PPTEST_DEC(46);
    PPTEST_DEC(47);
    PPTEST_DEC(48);
    PPTEST_DEC(49);
    PPTEST_DEC(50);
    PPTEST_DEC(51);
    PPTEST_DEC(52);
    PPTEST_DEC(53);
    PPTEST_DEC(54);
    PPTEST_DEC(55);
    PPTEST_DEC(56);
    PPTEST_DEC(57);
    PPTEST_DEC(58);
    PPTEST_DEC(59);
    PPTEST_DEC(60);
    PPTEST_DEC(61);
    PPTEST_DEC(62);
    PPTEST_DEC(63);
    PPTEST_DEC(64);
    PPTEST_DEC(65);
    PPTEST_DEC(66);
    PPTEST_DEC(67);
    PPTEST_DEC(68);
    PPTEST_DEC(69);
    PPTEST_DEC(70);
    PPTEST_DEC(71);
    PPTEST_DEC(72);
    PPTEST_DEC(73);
    PPTEST_DEC(74);
    PPTEST_DEC(75);
    PPTEST_DEC(76);
    PPTEST_DEC(77);
    PPTEST_DEC(78);
    PPTEST_DEC(79);
    PPTEST_DEC(80);
    PPTEST_DEC(81);
    PPTEST_DEC(82);
    PPTEST_DEC(83);
    PPTEST_DEC(84);
    PPTEST_DEC(85);
    PPTEST_DEC(86);
    PPTEST_DEC(87);
    PPTEST_DEC(88);
    PPTEST_DEC(89);
    PPTEST_DEC(90);
    PPTEST_DEC(91);
    PPTEST_DEC(92);
    PPTEST_DEC(93);
    PPTEST_DEC(94);
    PPTEST_DEC(95);
    PPTEST_DEC(96);
    PPTEST_DEC(97);
    PPTEST_DEC(98);
    PPTEST_DEC(99);
    PPTEST_DEC(100);
}

#define PPTEST_INC(n)   IUTEST_STATIC_ASSERT(n+1 == IUTEST_PP_INC(n))

IUTEST(PPTest, Inc)
{
    PPTEST_INC(0);
    PPTEST_INC(1);
    PPTEST_INC(2);
    PPTEST_INC(3);
    PPTEST_INC(4);
    PPTEST_INC(5);
    PPTEST_INC(6);
    PPTEST_INC(7);
    PPTEST_INC(8);
    PPTEST_INC(9);
    PPTEST_INC(10);
    PPTEST_INC(11);
    PPTEST_INC(12);
    PPTEST_INC(13);
    PPTEST_INC(14);
    PPTEST_INC(15);
    PPTEST_INC(16);
    PPTEST_INC(17);
    PPTEST_INC(18);
    PPTEST_INC(19);
    PPTEST_INC(20);
    PPTEST_INC(21);
    PPTEST_INC(22);
    PPTEST_INC(23);
    PPTEST_INC(24);
    PPTEST_INC(25);
    PPTEST_INC(26);
    PPTEST_INC(27);
    PPTEST_INC(28);
    PPTEST_INC(29);
    PPTEST_INC(30);
    PPTEST_INC(31);
    PPTEST_INC(32);
    PPTEST_INC(33);
    PPTEST_INC(34);
    PPTEST_INC(35);
    PPTEST_INC(36);
    PPTEST_INC(37);
    PPTEST_INC(38);
    PPTEST_INC(39);
    PPTEST_INC(40);
    PPTEST_INC(41);
    PPTEST_INC(42);
    PPTEST_INC(43);
    PPTEST_INC(44);
    PPTEST_INC(45);
    PPTEST_INC(46);
    PPTEST_INC(47);
    PPTEST_INC(48);
    PPTEST_INC(49);
    PPTEST_INC(50);
    PPTEST_INC(51);
    PPTEST_INC(52);
    PPTEST_INC(53);
    PPTEST_INC(54);
    PPTEST_INC(55);
    PPTEST_INC(56);
    PPTEST_INC(57);
    PPTEST_INC(58);
    PPTEST_INC(59);
    PPTEST_INC(60);
    PPTEST_INC(61);
    PPTEST_INC(62);
    PPTEST_INC(63);
    PPTEST_INC(64);
    PPTEST_INC(65);
    PPTEST_INC(66);
    PPTEST_INC(67);
    PPTEST_INC(68);
    PPTEST_INC(69);
    PPTEST_INC(70);
    PPTEST_INC(71);
    PPTEST_INC(72);
    PPTEST_INC(73);
    PPTEST_INC(74);
    PPTEST_INC(75);
    PPTEST_INC(76);
    PPTEST_INC(77);
    PPTEST_INC(78);
    PPTEST_INC(79);
    PPTEST_INC(80);
    PPTEST_INC(81);
    PPTEST_INC(82);
    PPTEST_INC(83);
    PPTEST_INC(84);
    PPTEST_INC(85);
    PPTEST_INC(86);
    PPTEST_INC(87);
    PPTEST_INC(88);
    PPTEST_INC(89);
    PPTEST_INC(90);
    PPTEST_INC(91);
    PPTEST_INC(92);
    PPTEST_INC(93);
    PPTEST_INC(94);
    PPTEST_INC(95);
    PPTEST_INC(96);
    PPTEST_INC(97);
    PPTEST_INC(98);
    PPTEST_INC(99);
}

#define EMPTY
#define NOT_EMPTY   hoge

IUTEST(PPTest, Empty)
{
    IUTEST_STATIC_ASSERT( IUTEST_PP_IS_EMPTY(IUTEST_PP_EMPTY()) == 1 );
    IUTEST_STATIC_ASSERT( IUTEST_PP_IS_EMPTY(EMPTY) == 1 );
    IUTEST_STATIC_ASSERT( IUTEST_PP_IS_EMPTY(NOT_EMPTY) == 0 );
}

#define VALUE_A 1024
#define VALUE_B 8

IUTEST(PPTest, If)
{
    IUTEST_STATIC_ASSERT( IUTEST_PP_IF(1, VALUE_A, VALUE_B) == VALUE_A );
    IUTEST_STATIC_ASSERT( IUTEST_PP_IF(0, VALUE_A, VALUE_B) == VALUE_B );
    IUTEST_STATIC_ASSERT( IUTEST_PP_IF(128, VALUE_A, VALUE_B) == VALUE_A );
}

IUTEST(PPTest, Counter)
{
#if IUTEST_HAS_COUNTER_MACRO
    IUTEST_STATIC_ASSERT( IUTEST_PP_COUNTER != __LINE__ );
#else
    IUTEST_STATIC_ASSERT( IUTEST_PP_COUNTER == __LINE__ );
#endif
}

#if defined(IUTEST_PP_IS_BEGIN_PARENS)
#define PAREN_TRUE  (x, y)
#define PAREN_FALSE x, y

IUTEST(PPTest, IsBeginParens)
{
    IUTEST_STATIC_ASSERT( IUTEST_PP_IS_BEGIN_PARENS(PAREN_TRUE) );
    IUTEST_STATIC_ASSERT( IUTEST_PP_IS_BEGIN_PARENS(PAREN_FALSE) == 0 );
}
#endif
