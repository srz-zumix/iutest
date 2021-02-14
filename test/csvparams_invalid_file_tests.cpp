//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        csvparams_invalid_file_tests.cpp
 * @brief       CSV param invalid files test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_CSVPARAMS
#  define CAN_CSVPARAMS_INVALID_FILE_TEST   1
#else
#  define CAN_CSVPARAMS_INVALID_FILE_TEST   0
#endif

#if CAN_CSVPARAMS_INVALID_FILE_TEST

class CsvParamsIntTest : public ::iutest::TestWithParam< int >
{
};

IUTEST_P(CsvParamsIntTest, DoNothing)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(NotExist, CsvParamsIntTest, ::iutest::CSV<int>("testdata/not-exist?.csv") );
IUTEST_INSTANTIATE_TEST_SUITE_P(EmptyCsv, CsvParamsIntTest, ::iutest::CSV<int>("testdata/empty.csv") );

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if CAN_CSVPARAMS_INVALID_FILE_TEST

#if IUTEST_HAS_STREAM_BUFFER
    ::iutest::detail::IUStreamBuffer<> stderr_capture(stderr);
#endif

    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return 1;
#if IUTEST_HAS_STREAM_BUFFER && IUTEST_HAS_ASSERTION_RETURN
    ::std::string stderr_message = stderr_capture.GetStreamString();
    IUTEST_ASSERT_STRIN("Unable to open file \"testdata/not-exist?.csv\".", stderr_message)
        << ::iutest::AssertionReturn<int>(1);
#if IUTEST_HAS_FOPEN
    IUTEST_ASSERT_STRIN("Empty params file "    "\"testdata/empty.csv\".", stderr_message)
#else
    IUTEST_ASSERT_STRIN("Unable to open file "  "\"testdata/empty.csv\".", stderr_message)
#endif
        << ::iutest::AssertionReturn<int>(1);
#endif
    printf("*** Successful ***\n");
#else
    (void)argc;
    (void)argv;
    printf("*** CAN_CSVPARAMS_INVALID_FILE_TEST=0 ***\n");
#endif
    return 0;
}



