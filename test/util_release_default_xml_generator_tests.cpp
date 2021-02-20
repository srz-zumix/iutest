//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        util_release_default_xml_generator_tests.cpp
 * @brief       iutest util ReleaseDefaultXmlGenerator
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#ifdef UNICODE
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],   cmd }
#endif

IUTEST(UtilReleaseXmlGeneratorTest, Fail)
{
    IUTEST_FAIL();
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    (void)argc;
    (void)argv;
    int targc = 2;
    DECAL_ARGV("--gtest_output=xml:util_release_default_xml_generator_tests.xml");
    IUTEST_INIT(&targc, targv);
    ::iuutil::ReleaseDefaultXmlGenerator();
    {
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        IUTEST_ASSERT_EXIT(listeners.default_xml_generator() == NULL);
    }
    if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
    printf("*** Successful ***\n");
    return 0;
}

