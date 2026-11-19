//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        environment_failure_tests.cpp
 * @brief       Skip tests after fatal global environment setup failure
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
#include "logger_tests.hpp"

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01120000 || GTEST_LATEST

static int test_runs = 0;
static int suite_runs = 0;
static int fixture_runs = 0;
static int teardown_runs = 0;
static int test_starts = 0;
static int test_ends = 0;
static int skipped_results = 0;

class FailingEnvironment : public ::iutest::Environment
{
public:
    virtual void SetUp() IUTEST_CXX_OVERRIDE { IUTEST_FAIL() << "fatal environment setup failure"; }
    virtual void TearDown() IUTEST_CXX_OVERRIDE { ++teardown_runs; }
};

class EnvironmentFailure : public ::iuutil::backward::Test<EnvironmentFailure>
{
public:
    EnvironmentFailure() { ++fixture_runs; }
    static void SetUpTestSuite() { ++suite_runs; }
    static void TearDownTestSuite() { ++suite_runs; }
};

IUTEST_F(EnvironmentFailure, First) { ++test_runs; }
IUTEST(EnvironmentFailureOther, Second) { ++test_runs; }
IUTEST_F(EnvironmentFailure, DISABLED_NotSelected) { ++test_runs; }
IUTEST(FilteredOut, NotSelected) { ++test_runs; }

class FailureEventCounter : public ::iutest::EmptyTestEventListener
{
public:
    virtual void OnTestStart(const ::iutest::TestInfo&) IUTEST_CXX_OVERRIDE { ++test_starts; }
    virtual void OnTestEnd(const ::iutest::TestInfo& info) IUTEST_CXX_OVERRIDE
    {
        ++test_ends;
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x010A0000 || GTEST_LATEST
        if( info.result()->Skipped() ) ++skipped_results;
#else
        IUTEST_UNUSED_VAR(info);
#endif
    }
};

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
class EnvironmentXmlFile : public ::iutest::StringStreamFile
{
public:
    static ::std::string xml;
    virtual void Close() IUTEST_CXX_OVERRIDE { xml = ss.str(); }
};

::std::string EnvironmentXmlFile::xml;
IUTEST_FILESYSTEM_INSTANTIATE(EnvironmentXmlFile);
#endif

void CheckFailure()
{
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
    const ::iutest::UnitTest* const unit = ::iutest::UnitTest::GetInstance();
    IUTEST_TERMINATE_ON_FAILURE(test_runs == 0);
    IUTEST_TERMINATE_ON_FAILURE(suite_runs == 0);
    IUTEST_TERMINATE_ON_FAILURE(fixture_runs == 0);
    IUTEST_TERMINATE_ON_FAILURE(unit->failed_test_count() == 0);
    IUTEST_TERMINATE_ON_FAILURE(unit->test_to_run_count() == 2);
#if defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE(unit->ad_hoc_test_result().HasFatalFailure());
#else
    IUTEST_TERMINATE_ON_FAILURE(unit->ad_hoc_test_result()->HasFatalFailure());
#endif
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x010A0000 || GTEST_LATEST
    IUTEST_TERMINATE_ON_FAILURE(skipped_results == test_ends);
#endif
    IUTEST_TERMINATE_ON_FAILURE(test_starts == test_ends);
    IUTEST_TERMINATE_ON_FAILURE(test_ends == 2 * teardown_runs);
#if defined(IUTEST_USE_GTEST)
#if GTEST_VER >= 0x010A0000 || GTEST_LATEST
    IUTEST_TERMINATE_ON_FAILURE(unit->skipped_test_count() == 2);
#endif
#else
    IUTEST_TERMINATE_ON_FAILURE(unit->reportable_test_run_skipped_count() == 2);
    IUTEST_TERMINATE_ON_FAILURE(unit->start_timestamp() > 0);
    IUTEST_TERMINATE_ON_FAILURE(::iuutil::GetTestSuite(0)->start_timestamp() > 0);
#endif
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(IUTEST_USE_GTEST) && GTEST_VER < 0x01120000 && !GTEST_LATEST
    return 0;
#else
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    ::iutest::IUTEST_FLAG(filter) = "EnvironmentFailure*.*";
    ::iutest::AddGlobalTestEnvironment(new FailingEnvironment);
    ::iutest::UnitTest::GetInstance()->listeners().Append(new FailureEventCounter);
#if !defined(IUTEST_USE_GTEST)
    static TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
    ::iutest::IUTEST_FLAG(color) = "no";
#if IUTEST_HAS_STRINGSTREAM
    ::iutest::IUTEST_FLAG(output) = "xml:environment.xml";
#endif
#endif
    CheckFailure();
    IUTEST_TERMINATE_ON_FAILURE(teardown_runs == 1);
#if !defined(IUTEST_USE_GTEST)
    IUTEST_TERMINATE_ON_FAILURE(::std::string(logger.c_str()).find("[  SKIPPED ] EnvironmentFailure.First")
        != ::std::string::npos);
    IUTEST_TERMINATE_ON_FAILURE(::std::string(logger.c_str()).find("[  SKIPPED ] EnvironmentFailureOther.Second")
        != ::std::string::npos);
    IUTEST_TERMINATE_ON_FAILURE(::std::string(logger.c_str()).find("[  SKIPPED ] 2 tests.") != ::std::string::npos);
    IUTEST_TERMINATE_ON_FAILURE(::std::string(logger.c_str()).find("Global test environment or ad hoc test failure")
        != ::std::string::npos);
    IUTEST_TERMINATE_ON_FAILURE(::std::string(logger.c_str()).find("0 FAILED TESTS") == ::std::string::npos);
#if IUTEST_HAS_STRINGSTREAM
    for( int format = 0; format < 2; ++format )
    {
        const ::std::string& xml = EnvironmentXmlFile::xml;
#if IUTEST_HAS_REPORT_SKIPPED
        IUTEST_TERMINATE_ON_FAILURE(xml.find("skipped=\"2\"") != ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("<skipped ") != ::std::string::npos);
#endif
        IUTEST_TERMINATE_ON_FAILURE(xml.find("Not Run") == ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("1970-01-01") == ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("FilteredOut") == ::std::string::npos);
        IUTEST_TERMINATE_ON_FAILURE(xml.find("fatal environment setup failure") != ::std::string::npos);
        if( format == 0 )
        {
            ::iutest::IUTEST_FLAG(output) = "junit:environment.xml";
            ::iutest::IUTEST_FLAG(fail_fast) = true;
            CheckFailure();
        }
    }
#endif
#endif
    printf("*** Successful ***\n");
    return 0;
#endif
}
