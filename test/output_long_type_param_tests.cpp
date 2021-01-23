//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_xml_long_type_param_tests.cpp
 * @brief       too long type param name tesst
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#define IUTEST_HAS_VARIADIC_TEMPLATES   0

#include "iutest.hpp"

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM && IUTEST_HAS_ASSERTION_RETURN && IUTEST_HAS_TYPED_TEST
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

template<IUTEST_PP_ENUM_SHIFTED_PARAMS(50, typename A)>
struct TestType {};

class TestNone {};

typedef TestType<IUTEST_PP_ENUM(50, IIUT_PP_REPEAT_PARAMS_MACRO_, TestNone)> AliasTestType;

IUTEST_FILESYSTEM_INSTANTIATE(FileIO);

template<typename T>
class MultiTypedTest : public ::iutest::Test
{
};
typedef ::iutest::Types< ::iutest::Types<int, float>, AliasTestType > MultiTypedTestTypes;

IUTEST_TYPED_TEST_SUITE(MultiTypedTest, MultiTypedTestTypes);

IUTEST_TYPED_TEST(MultiTypedTest, Get)
{
}

class HackXmlGeneratorListener : public ::iutest::DefaultXmlGeneratorListener
{
    HackXmlGeneratorListener() : ::iutest::DefaultXmlGeneratorListener("") {}
public:
    using DefaultXmlGeneratorListener::EscapeXmlAttribute;
    using DefaultXmlGeneratorListener::EscapeXmlText;
};

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if OUTPUT_XML_TEST
    IUTEST_INIT(&argc, argv);

    const ::std::string type_param1 = iutest::detail::GetTypeNameProxy< ::iutest::Types<int, float> >::GetTypeName();
    const ::std::string type_param2 = iutest::detail::GetTypeNameProxy< AliasTestType >::GetTypeName();
    const ::std::string xml_type_param1 = HackXmlGeneratorListener::EscapeXmlAttribute(type_param1);
    const ::std::string xml_type_param2 = HackXmlGeneratorListener::EscapeXmlAttribute(type_param2);

    ::iutest::IUTEST_FLAG(output) = "xml:test.xml";
    {
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret != 0 ) return 1;
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("iutest::detail::None")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find(xml_type_param1)) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find(xml_type_param2)) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        FileIO::s_io.clear();
    }

    ::iutest::IUTEST_FLAG(output) = "junit:test.xml";
    {
        const int ret = IUTEST_RUN_ALL_TESTS();

        if( ret != 0 ) return 1;
        IUTEST_ASSERT_EQ(::std::string::npos, FileIO::s_io.find("iutest::detail::None")) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find(xml_type_param1)) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
        IUTEST_ASSERT_NE(::std::string::npos, FileIO::s_io.find(xml_type_param2)) << FileIO::s_io << ::iutest::AssertionReturn<int>(1);
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
