//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        charcode_tests.cpp
 * @brief       iutest charcode test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018-2025, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

IUTEST(CharCodeTest, IsUtf16SurrogatePair)
{
    IUTEST_EXPECT_TRUE(iutest::detail::IsUtf16SurrogatePair(0xD800, 0xDC00));
    IUTEST_EXPECT_TRUE(iutest::detail::IsUtf16SurrogatePair(0xDBFF, 0xDFFF));
    IUTEST_EXPECT_FALSE(iutest::detail::IsUtf16SurrogatePair(0xD7FF, 0xDC00));
    IUTEST_EXPECT_FALSE(iutest::detail::IsUtf16SurrogatePair(0xD800, 0xDBFF));
}

IUTEST(CharCodeTest, AnyStringToMultiByteStringWchar)
{
    IUTEST_EXPECT_STREQ("TEST", ::iutest::detail::AnyStringToMultiByteString(L"TEST", -1));
#if defined(IUTEST_OS_WINDOWS)
    IUTEST_EXPECT_STREQ("TEST", ::iutest::detail::win::WideStringToMultiByteString(L"TEST", -1));
    IUTEST_EXPECT_STREQ(::iutest::detail::AnyStringToMultiByteString(L"テスト", -1)
        , ::iutest::detail::win::WideStringToMultiByteString(L"テスト", -1));
    IUTEST_EXPECT_STREQ(::iutest::detail::AnyStringToMultiByteString(L"\U00020BB7", -1)
        , ::iutest::detail::win::WideStringToMultiByteString(L"\U00020BB7", -1));
#endif
}

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
