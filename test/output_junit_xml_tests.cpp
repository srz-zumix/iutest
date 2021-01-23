//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_junit_xml_tests.cpp
 * @brief       output junit xml test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
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

IUTEST(Test, Fail)
{
    IUTEST_SUCCEED();
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Fail, Test)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, Skip)
{
    IUTEST_SKIP();
}

IUTEST(Foo, DISABLED_Test)
{
}

class Fixture : public ::iuutil::backward::Test<Fixture>
{
public:
    static void SetUpTestSuite()
    {
        RecordProperty("fixture", 1);
    }
};

IUTEST_F(Fixture, Test)
{
}

#if IUTEST_HAS_PARAM_TEST

class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(ParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, ParamTest, ::iutest::Values(0, 10));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

typedef ::iutest::Types<int> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedTest, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTest, Test)
{
}

#endif

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
#if OUTPUT_JUNIT_XML_TEST
    IUTEST_INIT(&argc, argv);

    ::iutest::IUTEST_FLAG(output) = "junit:test.xml";

    {
        ::iutest::IUTEST_FLAG(filter) = "-*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;

        IUTEST_ASSERT_EQ( "test.xml"
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
                )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Fail"))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Foo" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("<skipped type=\"iutest.skip\"" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("disabled test" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("<property name=\"fixture\" value=\"1\"" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#if IUTEST_HAS_TYPED_TEST
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("<property name=\"type_param\" value=" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#endif
#if IUTEST_HAS_PARAM_TEST
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("<property name=\"Test/0\" value=\"0\""  ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("<property name=\"Test/1\" value=\"10\"" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#endif
#endif

        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "junit";
    {
        ::iutest::IUTEST_FLAG(filter) = "*Fail*";
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret == 0 ) return 1;
        IUTEST_ASSERT_EQ( ::iutest::detail::kStrings::DefaultXmlReportFileName
            , (reinterpret_cast< ::iutest::DefaultXmlGeneratorListener*>(
                ::iutest::TestEnv::event_listeners().default_xml_generator()
                )->GetFilePath()) ) << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("Fail"))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("Foo" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);

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
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Test" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Fail"))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("root.Foo" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("root.Bar" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#if IUTEST_HAS_PACKAGE
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find("test.Foo" ))
            << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
#endif

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
