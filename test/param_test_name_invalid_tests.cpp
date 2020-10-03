//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        param_test_name_invalid_tests.cpp
 * @brief       parameter test name invalid
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST)

#if IUTEST_HAS_PARAM_TEST

class RenameParamTest : public ::iutest::TestWithParam<bool>
{
public:
    template<typename T>
    static const ::std::string MakeTestParamName(const iutest::TestParamInfo<T>& )
    {
        return "";
    }
};

IUTEST_P(RenameParamTest, Test)
{
    IUTEST_ASSERT_STREQ("Test", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, RenameParamTest, ::iutest::Bool());

#endif

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IUTEST_HAS_STREAM_BUFFER
    ::iutest::detail::IUStreamBuffer<> stderr_capture(stderr);
#endif
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_STREAM_BUFFER && IUTEST_CHECK_STRICT
    IUTEST_EXPECT_STRIN("My1/RenameParamTest.Test is already exist.", stderr_capture.GetStreamString());
#endif
#endif
    if( IUTEST_RUN_ALL_TESTS() ) return 1;

    printf("*** Successful ***\n");
    return 0;
}

