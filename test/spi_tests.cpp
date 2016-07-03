//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        spi_tests.cpp
 * @brief       iutest spi test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "pred_tests.hpp"

namespace spitest
{

class SPITest : public ::iutest::Test
{
public:
#if IUTEST_HAS_SPI_LAMBDA_SUPPORT
    const char* null_str;
    int a, b;
    int  aa[5];
    int  ab[6];
    char ac[5];
    ::std::string sa;
    ::std::string sb;
    ::std::string sa2;

    SPITest()
        : null_str(NULL)
        , a(0), b(0)
        , sa("a")
        , sb("b")
    {
        int  aa_[5] = { 0, 1, 2, 3, 4 };
        int  ab_[6] = { 0, 1, 2, 3, 4, 5 };
        char ac_[5] = { 0, 0, 2, 3, 5 };
        for( int i=0; i < 5; ++i )
        {
            aa[i] = aa_[i];
            ab[i] = ab_[i];
            ac[i] = ac_[i];
        }
        ab[5] = 5;
    }
#endif

public:
    void FatalFailure_Sub(int& count);
    void FatalFailure2_Sub(int& count);
};

#if !IUTEST_HAS_SPI_LAMBDA_SUPPORT
const char* null_str = NULL;
int a=0, b=0;
int  aa[] = { 0, 1, 2, 3, 4 };
int  ab[] = { 0, 1, 2, 3, 4, 5 };
char ac[] = { 0, 0, 2, 3, 5 };
::std::string sa="a";
::std::string sb="b";
#endif

void SPITest::FatalFailure_Sub(int& count)
{
    #define FLAVOR(n) IUTEST_ASSERT##n
    #define FAILURE_MACRO IUTEST_ASSERT_FATAL_FAILURE

#include "spi_tests_decl.cpp"

    #undef FLAVOR
    #undef FAILURE_MACRO

    count++;
}

IUTEST_F(SPITest, FatalFailure)
{
    int count=0;
#if IUTEST_HAS_EXCEPTIONS
    try {
        FatalFailure_Sub(count);
    } catch(...) {
    }
#else
    FatalFailure_Sub(count);
#endif
    IUTEST_ASSERT_EQ(1, count);
}

void SPITest::FatalFailure2_Sub(int& count)
{
    #define FLAVOR(n) IUTEST_ASSERT##n
    #define FAILURE_MACRO IUTEST_EXPECT_FATAL_FAILURE

#include "spi_tests_decl.cpp"

    #undef FLAVOR
    #undef FAILURE_MACRO

    count++;
}

IUTEST_F(SPITest, FatalFailure2)
{
    int count=0;
#if IUTEST_HAS_EXCEPTIONS
    try {
        FatalFailure2_Sub(count);
    } catch(...) {
    }
#else
    FatalFailure2_Sub(count);
#endif
    IUTEST_ASSERT_EQ(1, count);
}

IUTEST_F(SPITest, NonFatalFailure)
{
    #define FLAVOR(n) IUTEST_EXPECT##n
    #define FAILURE_MACRO IUTEST_ASSERT_NONFATAL_FAILURE

#include "spi_tests_decl.cpp"

    #undef FLAVOR
    #undef FAILURE_MACRO
}

IUTEST_F(SPITest, NonFatalFailure2)
{
    #define FLAVOR(n) IUTEST_EXPECT##n
    #define FAILURE_MACRO IUTEST_EXPECT_NONFATAL_FAILURE

#include "spi_tests_decl.cpp"

    #undef FLAVOR
    #undef FAILURE_MACRO
}

}   // end of namespace spitest
