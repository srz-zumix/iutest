//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        gtest_stringify_tests.cpp
 * @brief       internal stringification macro compatibility
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#define STRINGIFY_TEST_NAME ExpandedName
#define STRINGIFY_TEST_INDIRECT STRINGIFY_TEST_NAME

#if defined(IUTEST_USE_GTEST)
#include <gtest/gtest.h>
#if defined(GTEST_STRINGIFY_)
#  define STRINGIFY_TEST_HAS_UPSTREAM 1
static const char kUpstreamStringify[] = GTEST_STRINGIFY_(STRINGIFY_TEST_INDIRECT);
#else
#  define STRINGIFY_TEST_HAS_UPSTREAM 0
#endif
#endif

#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST) && defined(GTEST_STRINGIFY_)
#  error GTEST_STRINGIFY_ must not be supplied by the native public headers
#endif

#include "../include/gtest/iutest_switch.hpp"
#include "main.cpp"

#if defined(IUTEST_USE_GTEST)
#  if !STRINGIFY_TEST_HAS_UPSTREAM && defined(GTEST_STRINGIFY_)
#    error The switch must not supply GTEST_STRINGIFY_ in GoogleTest mode
#  endif
#elif !defined(IUTEST_NO_VARIADIC_MACROS)
#  if !defined(GTEST_STRINGIFY_)
#    error The native switch must supply GTEST_STRINGIFY_ with variadic macros
#  endif
#elif defined(GTEST_STRINGIFY_)
#  error GTEST_STRINGIFY_ must not be supplied without variadic macros
#endif

#if defined(GTEST_STRINGIFY_)
IUTEST(GTestStringify, Tokens)
{
    IUTEST_EXPECT_STREQ("TestName", GTEST_STRINGIFY_(TestName));
    IUTEST_EXPECT_STREQ("123", GTEST_STRINGIFY_(123));
    IUTEST_EXPECT_STREQ("two tokens", GTEST_STRINGIFY_(two   tokens));
    IUTEST_EXPECT_STREQ("\"a\\\\b\"", GTEST_STRINGIFY_("a\\b"));
}

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
#define STRINGIFY_TEST_EMPTY
#define STRINGIFY_TEST_COMMA first, second
#define STRINGIFY_TEST_FORWARD(a, b, c) GTEST_STRINGIFY_(a)

IUTEST(GTestStringify, Expansion)
{
    IUTEST_EXPECT_STREQ("ExpandedName", GTEST_STRINGIFY_(STRINGIFY_TEST_NAME));
    IUTEST_EXPECT_STREQ("ExpandedName", GTEST_STRINGIFY_(STRINGIFY_TEST_INDIRECT));
}

IUTEST(GTestStringify, Empty)
{
    IUTEST_EXPECT_STREQ("", GTEST_STRINGIFY_());
    IUTEST_EXPECT_STREQ("", GTEST_STRINGIFY_(STRINGIFY_TEST_EMPTY));
    IUTEST_EXPECT_STREQ("", GTEST_STRINGIFY_(, ignored));
    IUTEST_EXPECT_STREQ("", STRINGIFY_TEST_FORWARD(, x, y));
}

IUTEST(GTestStringify, Commas)
{
    IUTEST_EXPECT_STREQ("first", GTEST_STRINGIFY_(first, second));
    IUTEST_EXPECT_STREQ("first", GTEST_STRINGIFY_(STRINGIFY_TEST_COMMA));
    IUTEST_EXPECT_STREQ("(first, second)", GTEST_STRINGIFY_((STRINGIFY_TEST_COMMA)));
}
#endif

#if defined(IUTEST_USE_GTEST)
IUTEST(GTestStringify, UpstreamPreserved)
{
    IUTEST_EXPECT_STREQ(kUpstreamStringify, GTEST_STRINGIFY_(STRINGIFY_TEST_INDIRECT));
}
#endif
#endif

IUTEST(GTestStringify, NativeStringificationUnchanged)
{
    IUTEST_EXPECT_STREQ("ExpandedName", IUTEST_PP_TOSTRING(STRINGIFY_TEST_INDIRECT));
}
