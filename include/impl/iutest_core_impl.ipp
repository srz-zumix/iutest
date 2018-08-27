﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_core_impl.ipp
 * @brief       iris unit test UnitTest 実装 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CORE_IMPL_IPP_D5ABC7DE_C751_4AC0_922F_547880163891_
#define INCG_IRIS_IUTEST_CORE_IMPL_IPP_D5ABC7DE_C751_4AC0_922F_547880163891_

//======================================================================
// include
#include "../internal/iutest_core_impl.hpp"

namespace iutest
{

IUTEST_IPP_INLINE TestResult* UnitTestImpl::current_test_result()
{
    if( Test::GetCurrentTestInfo() )
    {
        return &(Test::GetCurrentTest()->m_test_info->ptr()->m_test_result);
    }
    UnitTestImpl* p = ptr();
    if( p == NULL )
    {
        return NULL;
    }
    if( p->m_current_testcase != NULL )
    {
        return &p->m_current_testcase->m_ad_hoc_testresult;
    }
    return &p->m_ad_hoc_testresult;
}

IUTEST_IPP_INLINE void UnitTestImpl::AddTestInfo(TestCase* pCase, TestInfo* pInfo)
{
    ++m_total_test_num;
    pCase->push_back(pInfo);
}

IUTEST_IPP_INLINE void UnitTestImpl::SkipTest()
{
    const Test* test = Test::GetCurrentTest();
    if( test != NULL && test->m_test_info->ptr() != NULL )
    {
        test->m_test_info->ptr()->skip();
    }
}

IUTEST_IPP_INLINE int UnitTestImpl::Listup() const
{
    detail::iuConsole::output("%d tests from %d testcase\n", m_total_test_num, m_testcases.size() );
    for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
    {
        detail::iuConsole::output((it)->name());
        detail::iuConsole::output("\n");

        for( TestCase::iuTestInfos::const_iterator it2 = (it)->begin(), end2=(it)->end(); it2 != end2; ++it2 )
        {
            detail::iuConsole::output("  ");
            detail::iuConsole::output((it2)->name());
            detail::iuConsole::output("\n");
        }
    }
    return 0;
}

IUTEST_IPP_INLINE int UnitTestImpl::ListupWithWhere() const
{
    detail::iuConsole::output("%d tests from %d testcase\n", m_total_test_num, m_testcases.size() );
    for( iuTestCases::const_iterator it = m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
    {
        detail::iuConsole::output((it)->testcase_name_with_where().c_str());
        detail::iuConsole::output("\n");

        for( TestCase::iuTestInfos::const_iterator it2 = (it)->begin(), end2=(it)->end(); it2 != end2; ++it2 )
        {
            detail::iuConsole::output("  ");
            detail::iuConsole::output((it2)->test_name_with_where().c_str());
            detail::iuConsole::output("\n");
        }
    }
    return 0;
}

IUTEST_IPP_INLINE bool UnitTestImpl::PreRunner()
{
    InitializeImpl();

    if( DoInfoOptions() )
    {
        TestFlag::SetFlag(0, ~TestFlag::SHOW_MASK);
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE void UnitTestImpl::ClearNonAdHocTestResult()
{
    for( iuTestCases::iterator it=m_testcases.begin(), end=m_testcases.end(); it != end; ++it )
    {
        (it)->clear();
    }
}

IUTEST_IPP_INLINE void UnitTestImpl::RecordProperty(const TestProperty& prop)
{
    UnitTestImpl* p = ptr();
    TestResult* tr = NULL;
    if( Test::GetCurrentTestInfo() )
    {
        tr = &(Test::GetCurrentTest()->m_test_info->ptr()->m_test_result);
        // 不正なキーのチェック
        if( !TestInfo::ValidateTestPropertyName(prop.key()) )
        {
            IIUT_ADD_FAILURE() << "Reserved key used in RecordProperty(): " << prop.key();
            return;
        }
    }
    else if( p->m_current_testcase != NULL )
    {
        tr = &p->m_current_testcase->m_ad_hoc_testresult;
        // 不正なキーのチェック
        if( !TestCase::ValidateTestPropertyName(prop.key()) )
        {
            IIUT_ADD_FAILURE() << "Reserved key used in RecordProperty(): " << prop.key();
            return;
        }
    }
    else
    {
        tr =&p->m_ad_hoc_testresult;
        // 不正なキーのチェック
        if( !ValidateTestPropertyName(prop.key()) )
        {
            IIUT_ADD_FAILURE() << "Reserved key used in RecordProperty(): " << prop.key();
            return;
        }
    }
    tr->RecordProperty(prop);
    TestEnv::event_listeners().OnTestRecordProperty(prop);
}

IUTEST_IPP_INLINE TestCase* UnitTestImpl::FindTestCase(const ::std::string& testcase_name, TestTypeId id)
{
    TestCase::FindOp func ={ id, testcase_name.c_str() };
    return detail::FindList(m_testcases, func);
}

IUTEST_IPP_INLINE bool UnitTestImpl::DoInfoOptions()
{
    if( TestFlag::IsEnableFlag(TestFlag::SHOW_INFO_MASK) )
    {
        if( TestFlag::IsEnableFlag(TestFlag::SHOW_HELP) )
        {
            detail::iuOptionMessage::ShowHelp();
        }
        if( TestFlag::IsEnableFlag(TestFlag::SHOW_VERSION) )
        {
            detail::iuOptionMessage::ShowVersion();
        }
        if( TestFlag::IsEnableFlag(TestFlag::SHOW_FEATURE) )
        {
            detail::iuOptionMessage::ShowFeature();
        }
        if( TestFlag::IsEnableFlag(TestFlag::SHOW_SPEC) )
        {
            detail::iuOptionMessage::ShowSpec();
        }
        return true;
    }
    if( TestFlag::IsEnableFlag(TestFlag::SHOW_TESTS_LIST_WITH_WHERE) )
    {
        ListupWithWhere();
        return true;
    }
    if( TestFlag::IsEnableFlag(TestFlag::SHOW_TESTS_LIST) )
    {
        Listup();
        return true;
    }
    return false;
}

IUTEST_IPP_INLINE void UnitTestImpl::InitializeImpl()
{
#if IUTEST_HAS_SEH

#if !defined(IUTEST_OS_WINDOWS_MOBILE) && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif

#if (defined(_MSC_VER) || defined(IUTEST_OS_WINDOWS_MINGW)) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    _set_error_mode(_OUT_TO_STDERR);
#endif

#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400 && !defined(IUTEST_OS_WINDOWS_MOBILE)
    if( !TestFlag::IsEnableFlag(TestFlag::BREAK_ON_FAILURE) )
    {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    }
#endif

#if IUTEST_HAS_EXCEPTIONS && (defined(_MSC_VER) && (_MSC_VER >= 1400)) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    _set_invalid_parameter_handler(OnInvalidParameter);
#endif
}

IUTEST_IPP_INLINE void UnitTestImpl::TerminateImpl()
{
    for( iuTestCases::iterator it = m_testcases.begin(); it != m_testcases.end(); it = m_testcases.begin())
    {
        TestCase* p = (it);
        m_testcases.erase(it);
        delete p;
    }
}

#if IUTEST_HAS_EXCEPTIONS && (defined(_MSC_VER) && (_MSC_VER >= 1400)) && !defined(IUTEST_OS_WINDOWS_MOBILE)

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

    // _invalid_parameter_handler
IUTEST_IPP_INLINE void UnitTestImpl::OnInvalidParameter(const wchar_t * expression, const wchar_t * function
    , const wchar_t * file, unsigned int line, uintptr_t pReserved)
{
    IUTEST_UNUSED_VAR(file);
    IUTEST_UNUSED_VAR(line);
    IUTEST_UNUSED_VAR(pReserved);
    char func[260];
    wcstombs(func, function, 260);
    char expr[260];
    wcstombs(expr, expression, 260);
    ::std::string msg = func;
    msg += expr;
    throw ::std::invalid_argument(msg);
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#endif

namespace detail
{

IUTEST_IPP_INLINE ::std::string MakeIndexName(size_t index)
{
    iu_stringstream strm;
    strm << index;
    return strm.str();
}

IUTEST_IPP_INLINE ::std::string MakeIndexTestName(const char* basename, size_t index)
{
    ::std::string name = basename;
    name += "/";
    name += MakeIndexName(index);
    return name;
}

IUTEST_IPP_INLINE::std::string MakeParamTestName(const ::std::string& basename, const ::std::string& param_name)
{
    if( param_name.empty() )
    {
        return basename;
    }
    ::std::string name = basename;
    name += "/";
    name += param_name;
    return name;
}

IUTEST_IPP_INLINE ::std::string MakePrefixedIndexTestName(const char* prefix, const char* basename, size_t index)
{
    ::std::string name = prefix;
    if( !name.empty() )
    {
        name += "/";
    }
    name += MakeIndexTestName(basename, index);
    return name;
}

}   // end of namespace detail

IUTEST_IPP_INLINE void Test::TestRecordPropertyHelper::RecordProperty(const TestProperty& prop)
{
    iutest::UnitTestImpl::RecordProperty(prop);
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_CORE_IMPL_IPP_D5ABC7DE_C751_4AC0_922F_547880163891_
