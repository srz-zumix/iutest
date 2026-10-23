//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        print_to_string_param_name_invalid_tests.cpp
 * @brief       Invalid printed parameter names
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#if !defined(IUTEST_USE_GTEST)
#  define IUTEST_ABORT()  (void)0
#endif
#include "../include/gtest/iutest_switch.hpp"

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR

class InvalidPrintParamNameTest : public ::iutest::TestWithParam< ::std::string > {};

IUTEST_P(InvalidPrintParamNameTest, Name) {}

IUTEST_INSTANTIATE_TEST_SUITE_P(Print, InvalidPrintParamNameTest
    , ::iutest::Values("", "a b", "a-b", "a/b", "\"a\"", "-1", "a.b")
    , ::iutest::PrintToStringParamName());

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_PARAM_TEST && IUTEST_HAS_PARAM_TEST_PARAM_NAME_GENERATOR
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    if( ::iutest::detail::IUTestLog::GetCount(::iutest::detail::IUTestLog::LOG_FATAL) != 7 )
    {
        return 1;
    }
    return IUTEST_RUN_ALL_TESTS() == 0 ? 1 : 0;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}
