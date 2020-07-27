﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_listener.hpp
 * @brief       iris unit test イベントリスナー 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_LISTENER_HPP_C94B8142_F8B3_413F_B479_8AA2B78604CE_
#define INCG_IRIS_IUTEST_LISTENER_HPP_C94B8142_F8B3_413F_B479_8AA2B78604CE_

//======================================================================
// include
#include <vector>
#include <algorithm>

namespace iutest
{

//======================================================================
// declare
class UnitTest;
class TestInfo;
class TestSuite;
class TestPartResult;
class TestProperty;
class TestEventListener;

namespace detail
{

class DefaultGlobalTestPartResultReporter;
template<typename T, typename ::std::string(*GetXmlPath)()>
class StderrXmlGeneratorListenerBase;

}   // end of namespace detail

}   // end of namespace iutest

#if IUTEST_HAS_LIB && IUTEST_HAS_EXTERN_TEMPLATE

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()

extern template class ::std::vector< ::iutest::TestEventListener* >;

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()

#endif

namespace iutest
{

/**
 * @brief   イベントリスナー
*/
class TestEventListener
{
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TestEventListener);
public:
    TestEventListener() {}
    virtual ~TestEventListener() {}
public:
    virtual void OnTestProgramStart(const UnitTest& test)           = 0;    //!< テストプログラム開始時に呼ばれます
    virtual void OnTestIterationStart(const UnitTest& test
                                    , int iteration)                = 0;    //!< 単体テスト開始時に毎回呼ばれます
    virtual void OnEnvironmentsSetUpStart(const UnitTest& test)     = 0;    //!< グローバル環境設定 SetUp 前に呼ばれます
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& test)       = 0;    //!< グローバル環境設定 SetUp 後に呼ばれます
#if IUTEST_HAS_TESTCASE
    virtual void OnTestSuiteStart(const TestSuite& test_suite)      { OnTestCaseStart(test_suite); }    //!< TestSuite 開始時に呼ばれます
    virtual void OnTestCaseStart(const TestSuite& /*test_suite*/)   {}
#else
    virtual void OnTestSuiteStart(const TestSuite& test_suite)      = 0;    //!< TestSuite 開始時に呼ばれます
#endif
    virtual void OnTestStart(const TestInfo& test_info)             = 0;    //!< テスト開始時に呼ばれます
    virtual void OnTestPartResult(const TestPartResult& test_part_result) = 0;    //!< テスト失敗時に呼ばれます
    virtual void OnTestRecordProperty(const TestProperty& /*test_property*/) {} //!< RecordProperty 時に呼ばれます
    virtual void OnTestEnd(const TestInfo& test_info)               = 0;    //!< テスト終了時にに呼ばれます
#if IUTEST_HAS_TESTCASE
    virtual void OnTestSuiteEnd(const TestSuite& test_suite)        { OnTestCaseEnd(test_suite); }    //!< TestSuite 終了時にに呼ばれます
    virtual void OnTestCaseEnd(const TestSuite& /*test_suite*/)     {}
#else
    virtual void OnTestSuiteEnd(const TestSuite& test_suite)        = 0;    //!< TestSuite 終了時にに呼ばれます
#endif
    virtual void OnEnvironmentsTearDownStart(const UnitTest& test)  = 0;    //!< グローバル環境設定 TearDown 前に呼ばれます
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& test)    = 0;    //!< グローバル環境設定 TearDown 前に呼ばれます
    virtual void OnTestIterationEnd(const UnitTest& test
                                    , int iteration)                = 0;    //!< 単体テスト終了時に毎回呼ばれます
    virtual void OnTestProgramEnd(const UnitTest& test)             = 0;    //!< テストプログラム終了時に呼ばれます
};

/**
 * @brief   空のイベントリスナー
*/
class EmptyTestEventListener : public TestEventListener
{
public:
    virtual void OnTestProgramStart(const UnitTest& /*test*/)           IUTEST_CXX_OVERRIDE {}
    virtual void OnTestIterationStart(const UnitTest& /*test*/
                                    , int /*iteration*/)                IUTEST_CXX_OVERRIDE {}
    virtual void OnEnvironmentsSetUpStart(const UnitTest& /*test*/)     IUTEST_CXX_OVERRIDE {}
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& /*test*/)       IUTEST_CXX_OVERRIDE {}
    virtual void OnTestSuiteStart(const TestSuite& /*test_suite*/)      IUTEST_CXX_OVERRIDE {}
    virtual void OnTestStart(const TestInfo& /*test_info*/)             IUTEST_CXX_OVERRIDE {}
    virtual void OnTestPartResult(const TestPartResult& /*test_part_result*/) IUTEST_CXX_OVERRIDE   {}
    virtual void OnTestRecordProperty(const TestProperty& /*test_propterty*/) IUTEST_CXX_OVERRIDE   {}
    virtual void OnTestEnd(const TestInfo& /*test_info*/)               IUTEST_CXX_OVERRIDE {}
    virtual void OnTestSuiteEnd(const TestSuite& /*test_suite*/)        IUTEST_CXX_OVERRIDE {}
    virtual void OnEnvironmentsTearDownStart(const UnitTest& /*test*/)  IUTEST_CXX_OVERRIDE {}
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& /*test*/)    IUTEST_CXX_OVERRIDE {}
    virtual void OnTestIterationEnd(const UnitTest& /*test*/
                                    , int /*iteration*/)                IUTEST_CXX_OVERRIDE {}
    virtual void OnTestProgramEnd(const UnitTest& /*test*/)             IUTEST_CXX_OVERRIDE {}
};

/**
 * @brief   イベント実行イベントリスナー
*/
class TestEventRepeater : public TestEventListener
{
    typedef ::std::vector<TestEventListener*> ListenerContainer;
public:
    /**
     * @brief   リスナーの追加
    */
    void Append(TestEventListener* listener)
    {
        m_listeners.push_back(listener);
    }

    /**
     * @brief   リスナーの解放
    */
    TestEventListener* Release(TestEventListener* listener);

public:
    // On*End は後ろから実行
    virtual void OnTestProgramStart(const UnitTest& test)           IUTEST_CXX_OVERRIDE;
    virtual void OnTestIterationStart(const UnitTest& test
                                    , int iteration)                IUTEST_CXX_OVERRIDE;
    virtual void OnEnvironmentsSetUpStart(const UnitTest& test)     IUTEST_CXX_OVERRIDE;
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& test)       IUTEST_CXX_OVERRIDE;
    virtual void OnTestSuiteStart(const TestSuite& test_suite)      IUTEST_CXX_OVERRIDE;
    virtual void OnTestStart(const TestInfo& test_info)             IUTEST_CXX_OVERRIDE;
    virtual void OnTestPartResult(const TestPartResult& test_part_result)   IUTEST_CXX_OVERRIDE;
    virtual void OnTestRecordProperty(const TestProperty& test_property)    IUTEST_CXX_OVERRIDE;
    virtual void OnTestEnd(const TestInfo& test_info)               IUTEST_CXX_OVERRIDE;
    virtual void OnTestSuiteEnd(const TestSuite& test_suite)        IUTEST_CXX_OVERRIDE;
    virtual void OnEnvironmentsTearDownStart(const UnitTest& test)  IUTEST_CXX_OVERRIDE;
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& test)    IUTEST_CXX_OVERRIDE;
    virtual void OnTestIterationEnd(const UnitTest& test
                                    , int iteration)                IUTEST_CXX_OVERRIDE;
    virtual void OnTestProgramEnd(const UnitTest& test)             IUTEST_CXX_OVERRIDE;

private:
    ListenerContainer m_listeners;
};

/**
 * @brief   イベントリスナーの管理クラス
*/
class TestEventListeners
{
    typedef ::std::vector<TestEventListener*> ListenerContainer;

public:
    TestEventListeners() : m_default_result_printer(NULL), m_default_xml_generator(NULL) {}

public:
    /**
     * @brief   リスナーの追加
    */
    void Append(TestEventListener* listener) { m_repeater.Append(listener); }

    /**
     * @brief   リスナーの解放
    */
    TestEventListener* Release(TestEventListener* listener) { return m_repeater.Release(listener); }

public:
    /**
     * @brief   デフォルト出力リスナーの取得
    */
    TestEventListener* default_result_printer() const IUTEST_CXX_NOEXCEPT_SPEC { return m_default_result_printer; }
    /**
     * @brief   デフォルトxml出力リスナー取得
    */
    TestEventListener* default_xml_generator()  const IUTEST_CXX_NOEXCEPT_SPEC { return m_default_xml_generator; }

private:
    TestEventListener* repeater() { return &m_repeater; }

    void OnTestProgramStart(const UnitTest& test)                   { m_repeater.OnTestProgramStart(test); }
    void OnTestIterationStart(const UnitTest& test, int iteration)  { m_repeater.OnTestIterationStart(test, iteration); }
    void OnEnvironmentsSetUpStart(const UnitTest& test)             { m_repeater.OnEnvironmentsSetUpStart(test); }
    void OnEnvironmentsSetUpEnd(const UnitTest& test)               { m_repeater.OnEnvironmentsSetUpEnd(test); }

    void OnTestSuiteStart(const TestSuite& test_suite)              { m_repeater.OnTestSuiteStart(test_suite); }
    void OnTestStart(const TestInfo& test_info)                     { m_repeater.OnTestStart(test_info); }
    void OnTestPartResult(const TestPartResult& test_part_result)   { m_repeater.OnTestPartResult(test_part_result); }
    void OnTestRecordProperty(const TestProperty& test_property)    { m_repeater.OnTestRecordProperty(test_property); }
    void OnTestEnd(const TestInfo& test_info)                       { m_repeater.OnTestEnd(test_info); }
    void OnTestSuiteEnd(const TestSuite& test_suite)                { m_repeater.OnTestSuiteEnd(test_suite); }

    void OnEnvironmentsTearDownStart(const UnitTest& test)          { m_repeater.OnEnvironmentsTearDownStart(test); }
    void OnEnvironmentsTearDownEnd(const UnitTest& test)            { m_repeater.OnEnvironmentsTearDownEnd(test); }
    void OnTestIterationEnd(const UnitTest& test, int iteration)    { m_repeater.OnTestIterationEnd(test, iteration); }
    void OnTestProgramEnd(const UnitTest& test)                     { m_repeater.OnTestProgramEnd(test); }

private:
    void set_default_result_printer(TestEventListener* listener);
    void set_default_xml_generator(TestEventListener* listener);

private:
    friend class UnitTestSource;
    friend class UnitTestImpl;
    friend class UnitTest;
    friend class TestInfo;
    friend class TestSuite;
    friend class Test;

    friend class detail::DefaultGlobalTestPartResultReporter;
    friend class DefaultXmlGeneratorListener;
    friend class JunitXmlGeneratorListener;
    friend class DefaultResultPrintListener;
    template<typename T, typename ::std::string(*GetXmlPath)()>
    friend class detail::StderrXmlGeneratorListenerBase;

    TestEventRepeater   m_repeater;
    TestEventListener*  m_default_result_printer;
    TestEventListener*  m_default_xml_generator;
};

}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "impl/iutest_listener.ipp"
#endif

#endif // INCG_IRIS_IUTEST_LISTENER_HPP_C94B8142_F8B3_413F_B479_8AA2B78604CE_
