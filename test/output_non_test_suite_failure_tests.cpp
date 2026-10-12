//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_non_test_suite_failure_tests.cpp
 * @brief       XML output for failures outside test suites
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2025, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"
#include <cstdio>
#include <fstream>
#include <sstream>

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
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

class FailingEnvironment : public ::iutest::Environment
{
    virtual void SetUp() IUTEST_CXX_OVERRIDE
    {
        IUTEST_ADD_FAILURE() << "global setup <&";
    }
};

IUTEST(NonTestSuiteFailureOutput, Test)
{
}

static bool CheckOutput(const char* path, bool junit)
{
#if defined(IUTEST_USE_GTEST) || IUTEST_HAS_FOPEN || IUTEST_HAS_STRINGSTREAM
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
    const ::std::string xml = FileIO::s_io;
#else
    ::std::ifstream file(path);
    ::std::ostringstream stream;
    stream << file.rdbuf();
    const ::std::string xml = stream.str();
    ::std::remove(path);
#endif

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000
    if( xml.find(junit ? "<testsuites tests=\"2\" failures=\"1\""
                       : "<testsuites tests=\"1\" failures=\"0\"") == ::std::string::npos
        || xml.find("<testsuite name=\"NonTestSuiteFailure\" tests=\"1\" failures=\"1\"")
            == ::std::string::npos
        || xml.find("<testcase name=\"\"") == ::std::string::npos
        || xml.find("<failure message=\"") == ::std::string::npos
        || xml.find("global setup &lt;&amp;") == ::std::string::npos )
    {
        fprintf(stderr, "Missing global setup failure in %s:\n%s\n", path, xml.c_str());
        return false;
    }
#else
    (void)junit;
#endif
    return !xml.empty();
#else
    (void)path;
    (void)junit;
    return true;
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    ::iutest::IUTEST_FLAG(output) = "xml:output_non_test_suite_failure.xml";
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(output) = "xml:output_non_test_suite_failure.xml";
#endif
    ::iutest::AddGlobalTestEnvironment(new FailingEnvironment());

    const ::std::string path = ::std::string(::iutest::IUTEST_FLAG(output).c_str()).substr(4);
    if( IUTEST_RUN_ALL_TESTS() == 0 || !CheckOutput(path.c_str(), false) )
    {
        return 1;
    }

#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(output) = "junit:output_non_test_suite_failure.xml";
    if( IUTEST_RUN_ALL_TESTS() == 0 || !CheckOutput(path.c_str(), true) )
    {
        return 1;
    }
#endif
    return 0;
}
