//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        japanese.cpp
 * @brief       japanese test name
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"

/* ---------------------------------------------------
 * 日本語テスト名
*//*--------------------------------------------------*/
#if IUTEST_HAS_TESTNAME_ALIAS_JP

IUTEST_PRAGMA_MSC_WARN_PUSH()
IUTEST_PRAGMA_MSC_WARN_DISABLE(4566)

IUTEST(IUTEST_JAPANESE_NAME(テスト), IUTEST_JAPANESE_NAME(テスト))
{
}
class JapaneseFixedTest : public ::iutest::Test {};

IUTEST_F(IUTEST_JAPANESE_NAME_F(あいうえお, JapaneseFixedTest), IUTEST_JAPANESE_NAME(かきくけこ))
{
}

IUTEST_PRAGMA_MSC_WARN_POP()

#endif
