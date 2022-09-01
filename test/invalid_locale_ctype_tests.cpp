//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        invalid_locale_ctype_tests.cpp
 * @brief       invalid locale ctype option test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STREAM_CAPTURE
::iutest::detail::IUStreamCaptureStderr stderr_capture;

IUTEST(Locale, Invalid)
{
    IUTEST_ASSUME_NULL(setlocale(LC_CTYPE, "xxx"));
    IUTEST_ASSERT_STRIN("failed: setlocale LC_CTYPE to hoge", stderr_capture.GetStreamString());
}
#endif

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L##cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],    cmd }
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    (void)argc;
    int targc = 2;
    DECAL_ARGV("--iutest_locale_ctype=hoge");
    IUTEST_INIT(&targc, targv);
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
    IUTEST_EXPECT_EQ("hoge", ::iutest::IUTEST_FLAG(locale_ctype));
    return IUTEST_RUN_ALL_TESTS();
}

