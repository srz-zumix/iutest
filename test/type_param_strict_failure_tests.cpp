//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_strict_failure_tests.cpp
 * @brief       type parameter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#if defined(IUTEST_TYPED_TEST_P_STRICT)
#  undef IUTEST_TYPED_TEST_P_STRICT
#endif
#define IUTEST_TYPED_TEST_P_STRICT  1
#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST_P

#if IUTEST_HAS_STREAM_BUFFER
    ::iutest::detail::IUStreamBuffer<> stderr_capture(stderr);
#endif

#if IUTEST_TYPED_TEST_P_STRICT

template<typename T>
class VerifyFailTypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(VerifyFailTypeParamTest);

IUTEST_TYPED_TEST_P(VerifyFailTypeParamTest, A)
{
}
IUTEST_TYPED_TEST_P(VerifyFailTypeParamTest, B)
{
    IUTEST_FAIL();
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(VerifyFailTypeParamTest, A);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, VerifyFailTypeParamTest, ::iutest::Types<int>);

#endif

template<typename T>
class RegisterFailTypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(RegisterFailTypeParamTest);
IUTEST_TYPED_TEST_P(RegisterFailTypeParamTest, A)
{
}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(RegisterFailTypeParamTest, A);

IUTEST_TYPED_TEST_P(RegisterFailTypeParamTest, B)
{
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
#endif
#if IUTEST_HAS_TYPED_TEST_P && IUTEST_HAS_STREAM_BUFFER
#if IUTEST_TYPED_TEST_P_STRICT
    IUTEST_EXPECT_STRIN("Test \"B\" has not been registered.", stderr_capture.GetStreamString());
#endif
    IUTEST_EXPECT_STRIN(
        "Test \"B\" must be defined before IUTEST_REGISTER_TYPED_TEST_SUITE_P(RegisterFailTypeParamTest, ...)."
        , stderr_capture.GetStreamString() );
#endif
    if( IUTEST_RUN_ALL_TESTS() ) return 1;

    printf("*** Successful ***\n");
    return 0;
}

