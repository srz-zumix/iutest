//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        internal_log_tests.cpp
 * @brief       IUTEST_LOG_ test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(locale_ctype) = "";

    IUTEST_LOG_(INFO) << "a";

    ::iutest::IUTEST_FLAG(warning_into_error) = false;
    if( IUTEST_RUN_ALL_TESTS() != 0 )
    {
        return 1;
    }

    ::iutest::IUTEST_FLAG(warning_into_error) = true;
    if( IUTEST_RUN_ALL_TESTS() != 0 )
    {
        return 1;
    }

    IUTEST_LOG_(WARNING) << "a";

    ::iutest::IUTEST_FLAG(warning_into_error) = false;
    if( IUTEST_RUN_ALL_TESTS() != 0 )
    {
        return 1;
    }

    ::iutest::IUTEST_FLAG(warning_into_error) = true;
    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        return 1;
    }

    IUTEST_LOG_(ERROR) << "a";

    ::iutest::IUTEST_FLAG(warning_into_error) = false;
    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        return 1;
    }

    ::iutest::IUTEST_FLAG(warning_into_error) = true;
    if( IUTEST_RUN_ALL_TESTS() == 0 )
    {
        return 1;
    }

#endif
    printf("*** Successful ***\n");
    return 0;
}

