//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        environment_skip_tests.cpp
 * @brief       Skip all tests from global environment setup
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

static int test_runs = 0;
static int teardown_runs = 0;
static int test_starts = 0;
static int test_ends = 0;

class SkippingEnvironment : public ::iutest::Environment
{
public:
    virtual void SetUp() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "skip all from environment"; }
    virtual void TearDown() IUTEST_CXX_OVERRIDE { ++teardown_runs; }
};

class SkipEventCounter : public ::iutest::EmptyTestEventListener
{
public:
    virtual void OnTestStart(const ::iutest::TestInfo&) IUTEST_CXX_OVERRIDE { ++test_starts; }
    virtual void OnTestEnd(const ::iutest::TestInfo&) IUTEST_CXX_OVERRIDE { ++test_ends; }
};

IUTEST(EnvironmentSkip, First) { ++test_runs; }
IUTEST(EnvironmentSkip, Second) { ++test_runs; }

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
class EnvironmentSkipXmlFile : public ::iutest::StringStreamFile
{
public:
    static ::std::string xml;
    virtual void Close() IUTEST_CXX_OVERRIDE { xml = ss.str(); }
};

::std::string EnvironmentSkipXmlFile::xml;
IUTEST_FILESYSTEM_INSTANTIATE(EnvironmentSkipXmlFile);
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(IUTEST_USE_GTEST) && GTEST_VER < 0x010A0000 && !GTEST_LATEST
    return 0;
#else
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    ::iutest::AddGlobalTestEnvironment(new SkippingEnvironment);
    ::iutest::UnitTest::GetInstance()->listeners().Append(new SkipEventCounter);
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
    ::iutest::IUTEST_FLAG(output) = "xml:environment_skip.xml";
#endif
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
    IUTEST_TERMINATE_ON_FAILURE(test_runs == 0);
    IUTEST_TERMINATE_ON_FAILURE(teardown_runs == 1);
    IUTEST_TERMINATE_ON_FAILURE(test_starts == 0);
    IUTEST_TERMINATE_ON_FAILURE(test_ends == 0);
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
    for( int format = 0; format < 2; ++format )
    {
        const ::std::string& xml = EnvironmentSkipXmlFile::xml;
        IUTEST_TERMINATE_ON_FAILURE(xml.find("<failure") == ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("1970-01-01") == ::std::string::npos);
#if IUTEST_HAS_REPORT_SKIPPED
        IUTEST_TERMINATE_ON_FAILURE(xml.find("skipped=\"2\"") != ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("<skipped ") != ::std::string::npos);
#endif
        if( format == 0 )
        {
            ::iutest::IUTEST_FLAG(output) = "junit:environment_skip.xml";
            IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
        }
    }
    IUTEST_TERMINATE_ON_FAILURE(teardown_runs == 2);
    IUTEST_TERMINATE_ON_FAILURE(test_runs == 0);
    IUTEST_TERMINATE_ON_FAILURE(test_starts == 0);
    IUTEST_TERMINATE_ON_FAILURE(test_ends == 0);
#endif
    printf("*** Successful ***\n");
    return 0;
#endif
}
