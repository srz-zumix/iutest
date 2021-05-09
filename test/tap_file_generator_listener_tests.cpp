//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        tap_file_generator_listener_tests.cpp
 * @brief       TAPPrintListener test
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
#include "../include/listener/iutest_tap_printer.hpp"

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM && IUTEST_HAS_ASSERTION_RETURN
#  define TAP_TEST  1
#else
#  define TAP_TEST  0
#endif

#if TAP_TEST

class FileIO IUTEST_CXX_FINAL : public ::iutest::StringStreamFile
{
public:
    static ::std::string s_io;

    virtual void Close() IUTEST_CXX_OVERRIDE
    {
        s_io += ss.str();
    }
};

::std::string FileIO::s_io;

IUTEST_FILESYSTEM_INSTANTIATE(FileIO);


const char tap_test_str[] =
"# Foo started.\n"
"ok 1 - Ok\n"
"# Foo ended.\n"
"1..1\n"
"# Bar started.\n"
"ok 1 # SKIP - DISABLED_Ng\n"
"# Bar ended.\n"
"1..1\n";

IUTEST(Foo, Ok)
{
    IUTEST_SUCCEED() << "not show.";
    RecordProperty("foo", "A");
}

IUTEST(Bar, DISABLED_Ng)
{
    IUTEST_FAIL() << "show failed.\n test.";
}

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if TAP_TEST

    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    {
        ::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
        {
            ::iutest::IUTEST_FLAG(output) = "test/";
            ::iutest::TAPFileGeneratorListener* listener
                = reinterpret_cast< ::iutest::TAPFileGeneratorListener*>( ::iutest::TAPFileGeneratorListener::SetUp() );
            IUTEST_ASSERT_EQ("test/", listener->GetFilePath() ) << ::iutest::AssertionReturn<int>(1);
            delete listeners.Release(listener);
        }
        {
            ::iutest::IUTEST_FLAG(output) = ".";
            ::iutest::TAPFileGeneratorListener* listener
                = reinterpret_cast< ::iutest::TAPFileGeneratorListener*>( ::iutest::TAPFileGeneratorListener::SetUp() );
            IUTEST_ASSERT_EQ(".", listener->GetFilePath() ) << ::iutest::AssertionReturn<int>(1);
            delete listeners.Release(listener);
        }
        {
            ::iutest::IUTEST_FLAG(output) = "hoge/test.tap";
            ::iutest::detail::iuFilePath path("hoge/");
            ::iutest::TAPFileGeneratorListener* listener
                = reinterpret_cast< ::iutest::TAPFileGeneratorListener*>( ::iutest::TAPFileGeneratorListener::SetUp() );
            IUTEST_ASSERT_EQ(path.ToString(), listener->GetFilePath() ) << ::iutest::AssertionReturn<int>(1);
            delete listeners.Release(listener);
        }
    }
#endif

    // xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#if !defined(IUTEST_USE_GTEST)
    ::iutest::TAPFileGeneratorListener::SetUp();
#endif

    {
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;

#if !defined(IUTEST_USE_GTEST)
        IUTEST_EXPECT_STREQ(tap_test_str, FileIO::s_io.c_str());
        FileIO::s_io.clear();
#endif
        if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;
    }

    {
        ::iutest::IUTEST_FLAG(filter) = "*Hoge*";
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = false;
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
        IUTEST_EXPECT_STRIN("*Hoge*", FileIO::s_io.c_str()) << ::iutest::AssertionReturn<int>(1);
        FileIO::s_io.clear();
#endif
    }

    {
        ::iutest::IUTEST_FLAG(filter) = NULL;
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
        IUTEST_EXPECT_STRIN("not ok", FileIO::s_io.c_str()) << ::iutest::AssertionReturn<int>(1);
        IUTEST_EXPECT_STRIN("show failed., test.", FileIO::s_io.c_str()) << ::iutest::AssertionReturn<int>(1);
        FileIO::s_io.clear();
#endif
    }

    printf("*** Successful ***\n");
#else
    (void)argc;
    (void)argv;
    printf("*** TAP_TEST=0 ***\n");
#endif
    return 0;
}
