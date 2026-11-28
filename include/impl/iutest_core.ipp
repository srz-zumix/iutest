//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_core.ipp
 * @brief       iris unit test core
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
#define INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_

//======================================================================
// include
#include "../iutest_core.hpp"
#include <errno.h>
#include <limits>

namespace iutest
{

namespace detail
{

IUTEST_IPP_INLINE bool ParseShardEnvironment(const char* name, const ::std::string& value, int& result)
{
    char* end = NULL;
    errno = 0;
    const long n = strtol(value.c_str(), &end, 10);
    if( errno == ERANGE || end == NULL || end == value.c_str() || *end != '\0'
        || n < 0 || n > (::std::numeric_limits<int>::max)() )
    {
        iuConsole::color_output(iuConsole::red, "Invalid %s: %s\n", name, value.c_str());
        return false;
    }
    result = static_cast<int>(n);
    return true;
}

IUTEST_IPP_INLINE bool GetShardConfiguration(int& total_shards, int& shard_index)
{
    ::std::string total, index;
    const bool has_total = GetEnvironmentVariable("GTEST_TOTAL_SHARDS", total);
    const bool has_index = GetEnvironmentVariable("GTEST_SHARD_INDEX", index);
    if( !has_total && !has_index )
    {
        return true;
    }
    if( has_total != has_index
        || !ParseShardEnvironment("GTEST_TOTAL_SHARDS", total, total_shards)
        || !ParseShardEnvironment("GTEST_SHARD_INDEX", index, shard_index)
        || total_shards == 0 || shard_index >= total_shards )
    {
        iuConsole::color_output(iuConsole::red,
            "GTEST_TOTAL_SHARDS and GTEST_SHARD_INDEX must satisfy 0 <= index < total.\n");
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE bool CreateRunnerFile(const char* variable, ::std::string& path)
{
    if( !GetEnvironmentVariable(variable, path) || path.empty() )
    {
        return true;
    }
#if IUTEST_HAS_FOPEN
    FILE* fp = internal::posix::FileOpen(path.c_str(), "w");
    if( fp != NULL )
    {
        return fclose(fp) == 0;
    }
#endif
    iuConsole::color_output(iuConsole::red, "Unable to create %s: %s\n", variable, path.c_str());
    return false;
}

class ScopedPrematureExitFile
{
public:
    explicit ScopedPrematureExitFile(const ::std::string& path) : m_path(path) {}
    ~ScopedPrematureExitFile()
    {
        if( !m_path.empty() )
        {
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
            for( int i = 0; i < 1000; ++i )
            {
                if( ::DeleteFileA(m_path.c_str()) )
                {
                    break;
                }
                const DWORD error = ::GetLastError();
                if( error != ERROR_ACCESS_DENIED && error != ERROR_SHARING_VIOLATION )
                {
                    break;
                }
                ::Sleep(1);
            }
#elif IUTEST_HAS_FOPEN
            remove(m_path.c_str());
#endif
        }
    }

private:
    const ::std::string m_path;
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(ScopedPrematureExitFile);
};

}   // end of namespace detail

IUTEST_IPP_INLINE int UnitTest::reportable_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_test_count);
}

IUTEST_IPP_INLINE int UnitTest::failed_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::failed_test_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_disabled_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_disabled_test_count);
}

IUTEST_IPP_INLINE int UnitTest::successful_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::successful_test_count);
}

IUTEST_IPP_INLINE int UnitTest::skip_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::skip_test_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_skip_test_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_skip_test_count);
}

IUTEST_IPP_INLINE int UnitTest::test_run_skipped_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::test_run_skipped_count);
}

IUTEST_IPP_INLINE int UnitTest::reportable_test_run_skipped_count() const
{
    return detail::SumOverList(m_testsuites, &TestSuite::reportable_test_run_skipped_count);
}

IUTEST_IPP_INLINE int UnitTest::test_suite_to_run_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::should_run);
}

IUTEST_IPP_INLINE int UnitTest::successful_test_suite_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::Passed);
}

IUTEST_IPP_INLINE int UnitTest::failed_test_suite_count() const
{
    return detail::CountIfOverList(m_testsuites, &TestSuite::Failed);
}

IUTEST_IPP_INLINE bool UnitTest::Passed() const
{
    if( m_ad_hoc_testresult.Failed() )
    {
        return false;
    }
    for( iuTestSuites::const_iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
    {
        if( (*it)->Failed() )
        {
            return false;
        }
    }
    return true;
}

IUTEST_IPP_INLINE int UnitTest::Run()
{
    if( m_init_iutest_count == 0 )
    {
//#if IUTEST_HAS_PARAM_TEST
//      if( m_param_testsuite_holder.count() )
//#endif
        {
            detail::iuConsole::output(
                "This test program did NOT call ::iutest::InitIrisUnitTest before calling IUTEST_RUN_ALL_TESTS().  Please fix it.\n"
            );
            return 1;
        }
    }

    ::std::string shard_status_file;
    if( !detail::CreateRunnerFile("GTEST_SHARD_STATUS_FILE", shard_status_file) )
    {
        return 1;
    }

    if( !PreRunner() )
    {
        return Passed() ? 0 : 1;
    }

    int total_shards = 1;
    int shard_index = 0;
    if( !detail::GetShardConfiguration(total_shards, shard_index) )
    {
        return 1;
    }
    ::std::string premature_exit_file;
    if( !detail::CreateRunnerFile("TEST_PREMATURE_EXIT_FILE", premature_exit_file) )
    {
        return 1;
    }
    const detail::ScopedPrematureExitFile premature_exit_guard(premature_exit_file);

#if IUTEST_HAS_EXCEPTIONS
    if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_GLOBAL) )
    {
        int ret = 1;
        try
        {
#if IUTEST_HAS_SEH
            ret = RunOnMSC(total_shards, shard_index);
#else
            ret = RunImpl(total_shards, shard_index);
#endif
        }
        //catch( ::std::exception& e )
        //{
        //  iutest::AssertionHelper(NULL, -1, detail::FormatCxxException(e.what()), TestPartResult::kFatalFailure) = AssertionHelper::Fixed();
        //}
        catch( ... )
        {
        }
        return ret;
    }
#endif
    return RunImpl(total_shards, shard_index);
}

#if IUTEST_HAS_SEH && IUTEST_HAS_EXCEPTIONS
IUTEST_IPP_INLINE int UnitTest::RunOnMSC(int total_shards, int shard_index)
{
    _EXCEPTION_POINTERS* ep = NULL;
    int ret = 1;
    __try
    {
        ret = RunImpl(total_shards, shard_index);
    }
    __except (ep = GetExceptionInformation()
#if IUTEST_HAS_MINIDUMP
        , detail::MiniDump::Create("minidump.dump", ep)
#endif
        , detail::seh_exception::should_process_through_break_and_cppexceptions(GetExceptionCode()))
    {
        detail::seh_exception::translator(GetExceptionCode(), ep);
    }
    return ret;
}
#endif

IUTEST_IPP_INLINE int UnitTest::RunImpl(int total_shards, int shard_index)
{
    m_repeat_counter = 0;
    int repeat = TestEnv::get_repeat_count();
    const bool recreate_environments = repeat < 0 || IUTEST_FLAG(recreate_environments_when_repeating);
    bool result = true;
    if( repeat != 0 )
    {
        m_start_timestamp = detail::GetWallTimeInMillis();
        TestProgramStart(total_shards, shard_index);

        while( repeat )
        {
            SetUpTestIteration();

            listeners().OnTestIterationStart(*this, m_repeat_counter);
            if( !RunOnce(recreate_environments || m_repeat_counter == 0, recreate_environments || repeat == 1) )
            {
                result = false;
            }
            listeners().OnTestIterationEnd(*this, m_repeat_counter);

            ++m_repeat_counter;
            if( !result && TestFlag::IsEnableFlag(TestFlag::FAIL_FAST) )
            {
                break;
            }
            if( repeat > 0 )
            {
                --repeat;
            }
        }

        TestProgramEnd();
    }
    if( !result )
    {
        return 1;
    }
    if( detail::IUTestLog::HasError() )
    {
        return 1;
    }
    if( IUTEST_FLAG(warning_into_error) )
    {
        if( detail::IUTestLog::HasWarning() )
        {
            return 1;
        }
    }
    if( IUTEST_FLAG(fail_if_no_test_linked) && total_test_count() == 0 )
    {
        return 1;
    }
    if( IUTEST_FLAG(fail_if_no_test_selected) && test_to_run_count() == 0 )
    {
        return 1;
    }
    return 0;
}

IUTEST_IPP_INLINE bool UnitTest::RunOnce(bool set_up_environment, bool tear_down_environment)
{
    m_elapsedmsec = 0;

    // テスト結果のクリア
    ClearNonAdHocTestResult();

    // 実行対象のテストがない場合は何もしない
    if( test_to_run_count() == 0 )
    {
        for( iuTestSuites::iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
        {
            (*it)->Run();
        }
        return Passed();
    }

    // シャッフル
    if( TestFlag::IsEnableFlag(TestFlag::SHUFFLE_TESTS) )
    {
        detail::RandomShuffle(m_testsuites, TestEnv::genrand());
    }

    // グローバル環境セット
    if( set_up_environment )
    {
        EnvironmentSetUp();
    }

    if( m_ad_hoc_testresult.HasFatalFailure() || m_ad_hoc_testresult.Skipped() )
    {
        for( iuTestSuites::iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
        {
            m_current_testsuite = *it;
            m_current_testsuite->Skip(m_ad_hoc_testresult.HasFatalFailure());
            m_current_testsuite = NULL;
        }
    }
    else
    {
        detail::iuStopWatch sw;
        sw.start();
        for( iuTestSuites::iterator it=m_testsuites.begin(), end=m_testsuites.end(); it != end; ++it )
        {
            m_current_testsuite = *it;
            m_current_testsuite->Run();
            m_current_testsuite = NULL;
            if( TestFlag::IsEnableFlag(TestFlag::FAIL_FAST) && (*it)->Failed() )
            {
                break;
            }
        }
        m_elapsedmsec = sw.stop();
    }

    // グローバル環境セット
    if( tear_down_environment || (TestFlag::IsEnableFlag(TestFlag::FAIL_FAST) && !Passed()) )
    {
        EnvironmentTearDown();
    }

    return Passed();
}

IUTEST_IPP_INLINE void UnitTest::TestProgramStart(int total_shards, int shard_index)
{
//#if IUTEST_HAS_EXCEPTIONS && defined(_MSC_VER) && IUTEST_HAS_SEH
//  // /EHa オプションが必要
//  if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION) )
//  {
//      // SEH 例外に対応する
//      _set_se_translator(detail::seh_exception::translator);
//  }
//#endif

    // フィルタリング
    m_should_run_num = 0;
    m_disable_num = 0;
    int runnable_test_id = 0;
    for( ::std::vector<TestSuite*>::iterator it = m_registered_testsuites.begin()
        , end = m_registered_testsuites.end(); it != end; ++it )
    {
        TestSuite* testsuite = *it;
        testsuite->filter(total_shards, shard_index, &runnable_test_id);
        m_should_run_num += testsuite->test_to_run_count();
        m_disable_num += testsuite->disabled_test_count();
    }

    atexit(OnExit);
#if IUTEST_HAS_STD_QUICK_EXIT
    ::std::at_quick_exit(OnExit);
#endif

    m_test_started = true;

    listeners().OnTestProgramStart(*this);
}

IUTEST_IPP_INLINE void UnitTest::SetUpTestIteration()
{
    TestEnv::SetUp();
}

IUTEST_IPP_INLINE void UnitTest::EnvironmentSetUp()
{
    listeners().OnEnvironmentsSetUpStart(*this);
    for( iuEnvironmentList::iterator it = TestEnv::environments().begin(), end=TestEnv::environments().end(); it != end; ++it )
    {
#if IUTEST_HAS_EXCEPTIONS
        if( TestFlag::IsEnableFlag(TestFlag::CATCH_EXCEPTION_EACH) )
        {
            try
            {
                (*it)->SetUp();
            }
            catch( const TestPartResult::Type& eType )
            {
                if( TestPartResult::type_is_failed(eType) && TestFlag::IsEnableFlag(TestFlag::THROW_ON_FAILURE) )
                {
                    throw;
                }
            }
        }
        else
#endif
        {
            (*it)->SetUp();
        }
    }
    listeners().OnEnvironmentsSetUpEnd(*this);
}

IUTEST_IPP_INLINE void UnitTest::EnvironmentTearDown()
{
    listeners().OnEnvironmentsTearDownStart(*this);
    for( iuEnvironmentList::reverse_iterator it = TestEnv::environments().rbegin(), end=TestEnv::environments().rend(); it != end; ++it )
    {
        (*it)->TearDown();
    }
    listeners().OnEnvironmentsTearDownEnd(*this);
}

IUTEST_IPP_INLINE void UnitTest::TestProgramEnd()
{
    if( !m_test_started )
    {
        return;
    }
    if( current_test_info() != NULL )
    {
        IUTEST_EXPECT_FAILURE("program exit.");
    }
    listeners().OnTestProgramEnd(*this);
    m_test_started = false;
}

IUTEST_IPP_INLINE void UnitTest::Initialize()
{
    m_init_iutest_count++;

    ClearAdHocTestResult();

    // ファイルシステムの初期化
    if( detail::IFileSystem::GetInstance() == NULL )
    {
#if defined(IUTEST_FILE)
        static FileSystem<IUTEST_FILE> filesystem;
        filesystem.Initialize();
#elif IUTEST_HAS_FOPEN
        static FileSystem<StdioFile> filesystem;
        filesystem.Initialize();
#endif
    }

    // 以降初回のみ
    if( m_init_iutest_count != 1 )
    {
        return;
    }

    char cwd[IUTEST_MAX_PATH] = { 0 };
    const char* const dir = internal::posix::GetCWD(cwd, sizeof(cwd));
    if( dir != NULL )
    {
        m_original_working_dir = dir;
    }

#if IUTEST_HAS_PARAM_TEST
    ::std::vector< ::std::string > uninstantiated;
    m_param_testsuite_holder.RegisterTests(uninstantiated);
#  if IUTEST_HAS_UNINSTANTIATED_PARAMETERIZED_TEST
    for( ::std::vector< ::std::string >::const_iterator it=uninstantiated.begin(); it != uninstantiated.end(); ++it )
    {
        detail::RegisterUninstantiatedParameterizedTest(*it, false);
    }
#  endif
#endif
#if IUTEST_HAS_TYPED_TEST_P && IUTEST_HAS_UNINSTANTIATED_PARAMETERIZED_TEST
    const ::std::vector<detail::UninstantiatedParameterizedTestRegistry::TypedSuite*>& typed_suites =
        detail::UninstantiatedParameterizedTestRegistry::GetInstance().typed_suites();
    for( ::std::vector<detail::UninstantiatedParameterizedTestRegistry::TypedSuite*>::const_iterator it=typed_suites.begin();
        it != typed_suites.end(); ++it )
    {
        if( !(*it)->instantiated )
        {
            detail::RegisterUninstantiatedParameterizedTest((*it)->name, true);
        }
    }
#endif
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_CORE_IPP_33560431_783B_4AE7_8FC8_6E78355CAF87_
