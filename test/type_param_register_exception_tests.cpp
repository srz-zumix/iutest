﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_register_exception_tests.cpp
 * @brief       type parameter exception in register test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#define IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME   1
#define IUTEST_ABORT()  (void)0

#include "iutest.hpp"
#include <stdexcept>

#if IUTEST_HAS_TYPED_TEST_P && IUTEST_HAS_EXCEPTIONS && !defined(IUTEST_USE_GTEST)
#  define REGISTER_EXCEPTION_TEST   1
#endif

#if !defined(REGISTER_EXCEPTION_TEST)
#  define REGISTER_EXCEPTION_TEST   0
#endif


#if IUTEST_HAS_STREAM_BUFFER
    ::iutest::detail::IUStreamBuffer<> stderr_capture(stderr);
#endif

#if REGISTER_EXCEPTION_TEST

struct exception_value
{
};

struct exception_int_value
{
};

namespace iutest
{
namespace detail
{
template<>
::std::string MakeIndexTypedTestName<exception_value>(const char* basename, size_t index)
{
    IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::runtime_error("HOGE"));
    return MakeIndexTestName(basename, index);
}
template<>
::std::string MakeIndexTypedTestName<exception_int_value>(const char* basename, size_t index)
{
    IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw 42);
    return MakeIndexTestName(basename, index);
}
}
}

template<typename T>
class RegisterExceptionTypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(RegisterExceptionTypeParamTest);

IUTEST_TYPED_TEST_P(RegisterExceptionTypeParamTest, Noop)
{
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(RegisterExceptionTypeParamTest, Noop);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, RegisterExceptionTypeParamTest, ::iutest::Types<exception_value>);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(B, RegisterExceptionTypeParamTest, ::iutest::Types<exception_int_value>);

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if REGISTER_EXCEPTION_TEST
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
#if IUTEST_HAS_STREAM_BUFFER
    // IUTEST_EXPECT_STRIN(
    //     "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed... (what: HOGE)\n"
    //     , stderr_capture.GetStreamString() );
    // IUTEST_EXPECT_STRIN(
    //     "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed...\n"
    //     , stderr_capture.GetStreamString() );

    // It will be fflushed and will be overwritten
    IUTEST_EXPECT_STRIN(
        "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed...\n\nwhat: HOGE)\n"
        , stderr_capture.GetStreamString() );
#endif
#endif
    return IUTEST_RUN_ALL_TESTS();
}

