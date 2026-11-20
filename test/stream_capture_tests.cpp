//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        stream_capture_tests.cpp
 * @brief       Google Test compatible stream capture tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include <iostream>
#include "../include/gtest/iutest_switch.hpp"

#if (!defined(IUTEST_USE_GTEST) && IUTEST_HAS_STREAM_CAPTURE) \
    || (defined(IUTEST_USE_GTEST) && GTEST_HAS_STREAM_REDIRECTION)

IUTEST(StreamCaptureTest, Stdout)
{
    ::testing::internal::CaptureStdout();
    printf("printf output");
    ::std::cout << " and cout output";
    const ::std::string captured = ::testing::internal::GetCapturedStdout();
    IUTEST_EXPECT_EQ("printf output and cout output", captured);
}

IUTEST(StreamCaptureTest, Stderr)
{
    ::testing::internal::CaptureStderr();
    fprintf(stderr, "%s", "stderr output");
    const ::std::string captured = ::testing::internal::GetCapturedStderr();
    IUTEST_EXPECT_EQ("stderr output", captured);
}

IUTEST(StreamCaptureTest, EmptyAndRepeated)
{
    for( int i = 0; i < 3; ++i )
    {
        ::testing::internal::CaptureStdout();
        const ::std::string out = ::testing::internal::GetCapturedStdout();
        ::testing::internal::CaptureStderr();
        const ::std::string err = ::testing::internal::GetCapturedStderr();
        IUTEST_EXPECT_TRUE(out.empty());
        IUTEST_EXPECT_TRUE(err.empty());
    }
}

IUTEST(StreamCaptureTest, IndependentStreams)
{
    ::testing::internal::CaptureStdout();
    ::testing::internal::CaptureStderr();
    printf("stdout");
    fprintf(stderr, "%s", "stderr");
    const ::std::string out = ::testing::internal::GetCapturedStdout();
    fprintf(stderr, "%s", " still captured");
    const ::std::string err = ::testing::internal::GetCapturedStderr();
    IUTEST_EXPECT_EQ("stdout", out);
    IUTEST_EXPECT_EQ("stderr still captured", err);
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(StreamCaptureTest, FlushBeforeCaptureAndRestore)
{
    ::std::string out;
    ::std::string err;
    ::std::string outer_out;
    ::std::string outer_err;
    fflush(NULL);
    {
        ::iutest::detail::IUStreamCaptureStdout stdout_capture;
        ::iutest::detail::IUStreamCaptureStderr stderr_capture;
        printf("before");
        fprintf(stderr, "%s", "before");
        ::iutest::internal::CaptureStdout();
        ::iutest::internal::CaptureStderr();
        printf("inner");
        fprintf(stderr, "%s", "inner");
        out = ::iutest::internal::GetCapturedStdout();
        err = ::iutest::internal::GetCapturedStderr();
        printf("after");
        fprintf(stderr, "%s", "after");
        fflush(NULL);
        outer_out = stdout_capture.GetStreamString();
        outer_err = stderr_capture.GetStreamString();
    }
    IUTEST_EXPECT_EQ("inner", out);
    IUTEST_EXPECT_EQ("inner", err);
    IUTEST_EXPECT_EQ("beforeafter", outer_out);
    IUTEST_EXPECT_EQ("beforeafter", outer_err);
}
#endif

IUTEST(StreamCaptureTest, EmbeddedNull)
{
    const char text[] = { 'a', '\0', 'b' };
    ::testing::internal::CaptureStdout();
    fwrite(text, 1, sizeof(text), stdout);
    const ::std::string out = ::testing::internal::GetCapturedStdout();
    ::testing::internal::CaptureStderr();
    fwrite(text, 1, sizeof(text), stderr);
    const ::std::string err = ::testing::internal::GetCapturedStderr();
    IUTEST_EXPECT_EQ(::std::string(text, sizeof(text)), out);
    IUTEST_EXPECT_EQ(::std::string(text, sizeof(text)), err);
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
