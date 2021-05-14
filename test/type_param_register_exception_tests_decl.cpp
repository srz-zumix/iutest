//======================================================================
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

#include <stdexcept>

#if IUTEST_HAS_STREAM_BUFFER
    ::iutest::detail::IUStreamBuffer<> stderr_capture(stderr);
#endif

#if REGISTER_EXCEPTION_TEST

struct exception_value
{
};

namespace iutest
{
namespace detail
{

bool is_throw = true;

template<>
::std::string MakeIndexTypedTestName<exception_value>(const char* basename, size_t index)
{
    if( is_throw )
    {
#if REGISTER_EXCEPTION_TEST_THROW_INT
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw 42);
#else
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::runtime_error("HOGE"));
#endif
    }
    return MakeIndexTestName(basename, index);
}

} // end of namespace detail
} // end of namespace iutest

template<typename T>
class RegisterExceptionTypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(RegisterExceptionTypeParamTest);

IUTEST_TYPED_TEST_P(RegisterExceptionTypeParamTest, Noop)
{
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(RegisterExceptionTypeParamTest, Noop);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, RegisterExceptionTypeParamTest, ::iutest::Types<exception_value>);

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
#if REGISTER_EXCEPTION_TEST_THROW_INT
    IUTEST_EXPECT_STRIN(
        "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed...\n"
        , stderr_capture.GetStreamString() );
#else
    IUTEST_EXPECT_STRIN(
        "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed... (what: HOGE)\n"
        , stderr_capture.GetStreamString() );
#endif
#endif
    if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;

    printf("*** Successful ***\n");
    return 0;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}

