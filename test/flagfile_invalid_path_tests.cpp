//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        flagfile_invalid_path_tests.cpp
 * @brief       flag file invalid path test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_FOPEN
#  define FLAGFILE_TEST 1
#else
#  define FLAGFILE_TEST 0
#endif

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(3, 3);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if FLAGFILE_TEST
    ::std::vector< ::iutest::detail::iu_tstring > targv;
    for( int i=0; i < argc; ++i )
    {
        targv.push_back(argv[i]);
    }
    targv.push_back(IU_TSTR("--iutest_flagfile=invalid_FLAGFILE_TEST.txt"));

    {
#if IUTEST_HAS_STREAM_CAPTURE
        ::iutest::detail::IUStreamCaptureStderr stderr_capture;
#endif
        ::iutest::InitIrisUnitTest(targv);
#if IUTEST_HAS_STREAM_CAPTURE && IUTEST_HAS_ASSERTION_RETURN
        IUTEST_ASSERT_STRIN("Unable to open flag file \"invalid_FLAGFILE_TEST.txt\".", stderr_capture.GetStreamString())
            << ::iutest::AssertionReturn<int>(1);
#endif
    }

    return IUTEST_RUN_ALL_TESTS();
#else
    (void)argc;
    (void)argv;
    printf("*** FLAGFILE_TEST=0 ***\n");
    return 0;
#endif
}
