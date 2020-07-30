//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_mediator.hpp
 * @brief       iris unit test 仲介者 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MEDIATOR_HPP_BFBE202B_0E60_4E44_8BDA_CB801D264F3E_
#define INCG_IRIS_IUTEST_MEDIATOR_HPP_BFBE202B_0E60_4E44_8BDA_CB801D264F3E_

namespace iutest {

//======================================================================
// declare
class TestInfo;
class TestSuite;
class TestPartResult;

namespace detail
{

//======================================================================
// class
/**
 * @brief   TestInfo 仲介者インターフェイス
*/
class iuITestInfoMediator
{
protected:
    TestInfo* m_test_info;
public:
    explicit iuITestInfoMediator(TestInfo* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_test_info(p) {}
public:
    virtual ~iuITestInfoMediator() IUTEST_CXX_DEFAULT_FUNCTION
    virtual bool HasFatalFailure() const = 0;
    virtual bool HasNonfatalFailure() const = 0;
    virtual bool HasFailure() const = 0;
    virtual bool IsSkipped() const = 0;
    TestInfo* ptr() const IUTEST_CXX_NOEXCEPT_SPEC { return m_test_info; }
};

/**
 * @brief   TestSuite 仲介者インターフェイス
*/
class iuITestSuiteMediator
{
protected:
    TestSuite* m_test_suite;
public:
    explicit iuITestSuiteMediator(TestSuite* p=NULL) IUTEST_CXX_NOEXCEPT_SPEC : m_test_suite(p) {}
public:
    virtual ~iuITestSuiteMediator() IUTEST_CXX_DEFAULT_FUNCTION
    virtual const char* test_suite_name() const = 0;
    virtual const char* type_param() const = 0;
    TestSuite* ptr() const IUTEST_CXX_NOEXCEPT_SPEC { return m_test_suite; }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_MEDIATOR_HPP_BFBE202B_0E60_4E44_8BDA_CB801D264F3E_
