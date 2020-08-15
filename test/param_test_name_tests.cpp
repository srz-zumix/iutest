//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        param_test_name_tests.cpp
 * @brief       parameter test name
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
#include "main.cpp"

#if IUTEST_HAS_PARAM_TEST

#if !defined(IUTEST_USE_GTEST)

class iuRenameParamTest : public ::iutest::TestWithParam<bool>
{
public:
    static const ::std::string MakeTestParamName(const iutest::TestParamInfo<bool>& info)
    {
        return ::iutest::StreamableToString(info.param);
    }
};

IUTEST_P(iuRenameParamTest, Test)
{
    if( GetParam() )
    {
        IUTEST_ASSERT_STREQ("Test/true", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
    }
    else
    {
        IUTEST_ASSERT_STREQ("Test/false", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
    }
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, iuRenameParamTest, ::iutest::Bool());

#endif

#if IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR

class RenameParamTest : public ::iutest::TestWithParam< ::std::string > {};

struct CustomParamNameFunctor
{
    ::std::string operator()(const ::iutest::TestParamInfo< ::std::string >& info)
    {
        return info.param;
    }
};

static ::std::string CustomParamNameFunction(const ::iutest::TestParamInfo< ::std::string >& info)
{
    return info.param;
}

IUTEST_P(RenameParamTest, Test)
{
    ::std::string name = "Test/";
    name += GetParam();
    IUTEST_ASSERT_STREQ(name, ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(CustomParamNameFunctor, RenameParamTest
                                , ::iutest::Values("abcdefghijklmnopqrstuvwxyz", "1234567890")
                                , CustomParamNameFunctor() );

IUTEST_INSTANTIATE_TEST_SUITE_P(CustomParamNameFunction, RenameParamTest
                                , ::iutest::Values("abcdefghijklmnopqrstuvwxyz", "1234567890")
                                , CustomParamNameFunction );

#if IUTEST_HAS_LAMBDA
IUTEST_INSTANTIATE_TEST_SUITE_P(CustomParamNameLambda, RenameParamTest
                                , ::iutest::Values("abcdefghijklmnopqrstuvwxyz", "1234567890")
                                , [](const ::iutest::TestParamInfo< ::std::string >& info) {
                                    return info.param;
                                });
#endif

#endif

#endif

