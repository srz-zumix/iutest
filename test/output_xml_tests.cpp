//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_xml_tests.cpp
 * @brief       xml output tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM && IUTEST_HAS_ASSERTION_RETURN
#  define OUTPUT_XML_TEST   1
#else
#  define OUTPUT_XML_TEST   0
#endif

#if OUTPUT_XML_TEST

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

IUTEST(Test, Fail)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Fail, Test)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Fail, TestEscape)
{
    IUTEST_ASSERT_EQ(2, 3) << "<>&";
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(3, 3);
}

#if IUTEST_HAS_PACKAGE

IUTEST_PACKAGE(test)
{
    IUTEST(Foo, Bar)
    {
        IUTEST_ASSERT_EQ(3, 3);
    }
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if OUTPUT_XML_TEST
    ::iutest::IUTEST_FLAG(output) = "xml:test.xml";

    IUTEST_INIT(&argc, argv);

    {
        ::iutest::IUTEST_FLAG(output) = "";
        ::iutest::IUTEST_FLAG(filter) = "-*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;
        IUTEST_ASSERT_STRLNEQ(0, FileIO::s_io) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "xml:test.xml";

    {
        ::iutest::IUTEST_FLAG(filter) = "-*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret != 0 ) return 1;
        IUTEST_ASSERT_EQ( "test.xml"
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
            )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "xml";
    {
        ::iutest::IUTEST_FLAG(filter) = "*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret == 0 ) return 1;
        IUTEST_ASSERT_EQ( ::iutest::detail::kStrings::DefaultXmlReportFileName
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
            )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "xml:.";
    {
        ::iutest::IUTEST_FLAG(filter) = "*TestEscape*";
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret == 0 ) return 1;
        ::std::string strXml = ".";
        strXml += ::iutest::detail::GetPathSeparator();
        strXml += ::iutest::detail::kStrings::DefaultXmlReportFileName;
        IUTEST_ASSERT_EQ( strXml
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
            )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("&lt;")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("&gt;")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("&amp;")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "xml:";
    {
        ::iutest::IUTEST_FLAG(filter) = "*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret == 0 ) return 1;
        IUTEST_ASSERT_EQ( ::iutest::detail::kStrings::DefaultXmlReportFileName
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
            )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

        FileIO::s_io.clear();
    }

    {
        ::iutest::IUTEST_FLAG(default_package_name) = "root";
        ::iutest::IUTEST_FLAG(filter) = NULL;
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret == 0 ) return 1;
        IUTEST_ASSERT_EQ( ::iutest::detail::kStrings::DefaultXmlReportFileName
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
            )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Test" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Fail")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("root.Bar" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#if IUTEST_HAS_PACKAGE
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("test.Foo" )) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#endif

        FileIO::s_io.clear();
    }
    printf("*** Successful ***\n");
#else
    (void)argc;
    (void)argv;
    printf("*** OUTPUT_XML_TEST=0 ***\n");
#endif
    return 0;
}
