//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_junit_xml_empty_tests.cpp
 * @brief       output junit xml empty test
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

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM && IUTEST_HAS_ASSERTION_RETURN
#  define OUTPUT_JUNIT_XML_TEST 1
#else
#  define OUTPUT_JUNIT_XML_TEST 0
#endif

#if OUTPUT_JUNIT_XML_TEST

class FileIO IUTEST_CXX_FINAL : public ::iutest::StringStreamFile
{
public:
    static ::std::string s_io;

    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        s_io = ss.str();
    }
};

::std::string FileIO::s_io;

IUTEST_FILESYSTEM_INSTANTIATE(FileIO);

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if OUTPUT_JUNIT_XML_TEST
    IUTEST_INIT(&argc, argv);

    ::iutest::IUTEST_FLAG(output) = "junit:test.xml";

    {
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;

        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("<?xml version"))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        FileIO::s_io.clear();
    }
    printf("*** Successful ***\n");
#else
    (void)argc;
    (void)argv;
    printf("*** OUTPUT_JUNIT_XML_TEST=0 ***\n");
#endif
    return 0;
}
