//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        csvparams_tests.cpp
 * @brief       CSV 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

#endif

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_CSVPARAMS && IUTEST_HAS_FOPEN

static const int CsvParamsIntTest_Params[] = {
    #include "testdata/intcsvparams.csv"
};
class CsvParamsIntTest : public ::iuutil::backward::Test<CsvParamsIntTest>, public ::iutest::WithParamInterface<int>
{
protected:
    static int check_params[IUTEST_PP_COUNTOF(CsvParamsIntTest_Params)];

public:
    static void SetUpTestCase(void)
    {
        memcpy(check_params, CsvParamsIntTest_Params, sizeof(CsvParamsIntTest_Params));
    }
    static void TearDownTestCase(void)
    {
        for( size_t i=0; i < IUTEST_PP_COUNTOF(check_params); ++i )
        {
            IUTEST_EXPECT_EQ( 0, check_params[i] ) << i;
        }
    }
};

int CsvParamsIntTest::check_params[IUTEST_PP_COUNTOF(CsvParamsIntTest_Params)];

IUTEST_P(CsvParamsIntTest, Num)
{
    IUTEST_EXPECT_EQ( IUTEST_PP_COUNTOF(check_params)*2, ::iuutil::GetCurrentTestSuite()->total_test_count() );
}

IUTEST_P(CsvParamsIntTest, Param)
{
    IUTEST_EXPECT_NE( 0, GetParam() );
#if IUTEST_HAS_MATCHERS
    IUTEST_ASSERT_THAT( check_params, Contains( GetParam() ) );
#endif
    for( size_t i=0; i < IUTEST_PP_COUNTOF(check_params); ++i )
    {
        if( check_params[i] == GetParam() )
        {
            check_params[i] = 0;
            break;
        }
    }
}

IUTEST_INSTANTIATE_TEST_SUITE_P(CSV, CsvParamsIntTest, ::iutest::CSV<int>("testdata/intcsvparams.csv") );
IUTEST_INSTANTIATE_TEST_SUITE_P(TSV, CsvParamsIntTest, ::iutest::CSV<int>("testdata/intcsvparams.tsv", '\t') );

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_NARROWING()
IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_FLOAT_CONVERSION()

static const float CsvParamsFloatTest_Params[] = {
    #include "testdata/floatcsvparams.csv"
};

IUTEST_PRAGMA_WARN_POP()

class CsvParamsFloatTest : public ::iutest::TestWithParam< float >
{
protected:
    static float check_params[IUTEST_PP_COUNTOF(CsvParamsFloatTest_Params)];

public:
    IUTEST_CLASS_INITIALIZE(setup)
    {
        memcpy(check_params, CsvParamsFloatTest_Params, sizeof(CsvParamsFloatTest_Params));
    }
    IUTEST_CLASS_CLEANUP(teardown)
    {
        for( size_t i=0; i < IUTEST_PP_COUNTOF(check_params); ++i )
        {
            IUTEST_EXPECT_EQ( 0, check_params[i] ) << i;
        }
    }
};

float CsvParamsFloatTest::check_params[IUTEST_PP_COUNTOF(CsvParamsFloatTest_Params)];

IUTEST_P(CsvParamsFloatTest, Num)
{
    IUTEST_EXPECT_EQ( IUTEST_PP_COUNTOF(check_params)*2, ::iuutil::GetCurrentTestSuite()->total_test_count() );
}

IUTEST_P(CsvParamsFloatTest, Param)
{
    IUTEST_EXPECT_NE( 0.0f, GetParam() );
#if IUTEST_HAS_MATCHERS
    IUTEST_ASSERT_THAT( check_params, Contains( GetParam() ) );
#endif
    for( size_t i=0; i < IUTEST_PP_COUNTOF(check_params); ++i )
    {
        if( check_params[i] == GetParam() )
        {
            check_params[i] = 0.0f;
            break;
        }
    }
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A, CsvParamsFloatTest, ::iutest::CSV<float>("testdata/floatcsvparams.csv") );

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


