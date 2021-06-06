//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        spi_tests.cpp
 * @brief       iutest spi test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "pred_tests.hpp"

namespace spi_test
{

struct TestObjectX
{
    int ma, mb, mc;
    TestObjectX(int a, int b, int c) : ma(a), mb(b), mc(c) {}
};

template<typename T>
T Div(T a, T b) { return a/b; }

class SPITest : public ::iutest::Test
{
public:
#if IUTEST_HAS_SPI_LAMBDA_SUPPORT
    const char* null_str;
    const int a, b;
    const float fa;
    const double da;
    int  aa[5];
    int  aa2[5];
    int  ab[6];
    char ac[5];
    const ::std::string sa;
    const ::std::string sb;
    const ::std::string sa2;
    TestObjectX ox;
    TestObjectX oy;
#if IUTEST_HAS_CXX_HDR_VARIANT
    const ::std::variant<int, float, ::std::string> v;
#endif
#if IUTEST_HAS_LONG_DOUBLE
    long double lda;
#endif

    SPITest()
        : null_str(NULL)
        , a(0), b(0)
        , fa(0.0f)
        , da(0.0)
        , sa("a")
        , sb("b")
        , ox(0, 1, 2)
        , oy(0, 0, 0)
#if IUTEST_HAS_CXX_HDR_VARIANT
        , v(1)
#endif
#if IUTEST_HAS_LONG_DOUBLE
        , lda(0.0l)
#endif
    {
        const char ac_[5] = { 0, 0, 2, 3, 5 };
        for( int i=0; i < 5; ++i )
        {
            aa[i] = aa2[i] = ab[i] = i;
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
const int a=0, b=0;
const int  aa[] = { 0, 1, 2, 3, 4 };
const int  aa2[] = { 0, 1, 2, 3, 4 };
const int  ab[] = { 0, 1, 2, 3, 4, 5 };
const char ac[] = { 0, 0, 2, 3, 5 };
const ::std::string sa="a";
const ::std::string sb="b";
const float fa = static_cast<float>(a);
const double da = static_cast<double>(a);
const TestObjectX ox(0, 1, 2);
const TestObjectX oy(0, 0, 0);
#if IUTEST_HAS_CXX_HDR_VARIANT
const ::std::variant<int, float, ::std::string> v = 1;
#endif
#if IUTEST_HAS_LONG_DOUBLE
long double lda = static_cast<long double>(a);
#endif
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

}   // end of namespace spi_test
