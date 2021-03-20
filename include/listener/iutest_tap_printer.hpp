//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_tap_printer.hpp
 * @brief       iris unit test Test Anything Protocol 出力イベントリスナー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
#define INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_core.hpp"
#include "../internal/iutest_log_stream.hpp"
#include "../internal/iutest_filepath.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// class
/**
 * @brief   TAP出力イベントリスナー
*/
class TAPPrintListener : public EmptyTestEventListener
{
public:
    TAPPrintListener() {}
public:
    virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
    virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

protected:
    /// TestSuite 毎の処理
    void OnReportTestSuite(detail::IOutStream* const stream, const TestSuite& test_suite, int top=1);

public:
    /**
    * @brief    TAPPrintListener に切り替え
    */
    static TestEventListener* SetUp()
    {
        TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
        delete listeners.Release(listeners.default_result_printer());
        TestEventListener* p = new TAPPrintListener;
        listeners.Append(p);
        return p;
    }
};

/**
 * @brief   TAPファイル出力イベントリスナー
*/
class TAPFileGeneratorListener : public TAPPrintListener
{
    ::std::string m_output_path;
public:
    /**
     * @brief   コンストラクタ
     * @param [in]  directory = 出力ディレクトリ
    */
    explicit TAPFileGeneratorListener(const char* directory=NULL)
    {
        SetFilePath(directory);
    }
public:
    /**
     * @brief   出力パスの取得
    */
    const ::std::string& GetFilePath() const { return m_output_path; }
private:
    /**
     * @brief   出力パスの設定
    */
    void SetFilePath(const char* directory)
    {
        if( directory == NULL || *directory == '\0' )
        {
            m_output_path = internal::posix::GetCWD();
        }
        else
        {
            detail::iuFilePath path(directory);
            if( path.IsDirectory() )
            {
                m_output_path = directory;
            }
            else
            {
                m_output_path = path.RemoveFileName().ToString();
            }
        }
    }
public:
    virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE
    {
        IUTEST_UNUSED_VAR(test);
    }
    virtual void OnTestRecordProperty(const TestProperty& test_property) IUTEST_CXX_OVERRIDE
    {
        IUTEST_UNUSED_VAR(test_property);
    }
    virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

public:
    /**
     * @brief   TAPFileGeneratorListener に切り替え
    */
    static TestEventListener* SetUp()
    {
        TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
        const ::std::string& output =  TestEnv::get_output_option();
        TestEventListener* p = new TAPFileGeneratorListener(output.c_str());
        listeners.Append(p);
        return p;
    }
};

inline void TAPPrintListener::OnTestProgramStart(const UnitTest& test)
{
    IUTEST_UNUSED_VAR(test);
    // フィルタリング
    if( TestFlag::IsEnableFlag(TestFlag::FILTERING_TESTS) )
    {
        detail::iuConsole::color_output(detail::iuConsole::yellow
            , "# Note: iutest filter = %s\n", TestEnv::test_filter());
    }
}
inline void TAPPrintListener::OnTestProgramEnd(const UnitTest& test)
{
    detail::LogStream stream;

    int number = 1;
    for( int k=0, count=test.total_test_suite_count(); k < count; ++k )
    {
        const TestSuite& test_suite = *test.GetTestSuite(k);

        OnReportTestSuite(&stream, test_suite, number);

        number += test_suite.total_test_count();
    }
    detail::iuConsole::output("1..%d\n", number-1);
}
inline void TAPPrintListener::OnReportTestSuite(detail::IOutStream* const stream, const TestSuite& test_suite, int top)
{
    stream->Printf("# %s started.\n", test_suite.name());

    for( int i=0, test_count=test_suite.total_test_count(); i < test_count; ++i )
    {
        const TestInfo* test_info = test_suite.GetTestInfo(i);
        if( !test_info->should_run() )
        {
            // スキップ
            stream->Printf("ok %d # SKIP - %s\n", top+i, test_info->name());
        }
        else
        {
            if( test_info->HasFailure() )
            {
                stream->Printf("not ok %d - %s ", top+i, test_info->name() );
                for( int j=0, part_count=test_info->result()->total_part_count(); j < part_count; ++j )
                {
                    const TestPartResult& part = test_info->result()->GetTestPartResult(j);
                    ::std::string summary = part.make_message();
                    // 改行を置き換え
                    detail::StringReplace(summary, '\n', ", ");
                    stream->Printf("%s. ", summary.c_str() );
                }
                stream->Printf("\n");
            }
            else
            {
                stream->Printf("ok %d - %s\n", top+i, test_info->name() );
            }
        }
    }

    stream->Printf("# %s ended.\n", test_suite.name());
}

inline void TAPFileGeneratorListener::OnTestProgramEnd(const UnitTest& test)
{
    for( int k=0, count=test.total_test_suite_count(); k < count; ++k )
    {
        const TestSuite& test_suite = *test.GetTestSuite(k);

        IUTEST_UNUSED_VAR(test);
        IFile* fp = detail::IFileSystem::New();
        if( fp == NULL )
        {
            return;
        }

        ::std::string filepath = m_output_path;
        ::std::string name = test_suite.name();
        detail::StringReplace(name, '/', "_");
        filepath += detail::GetPathSeparator();
        filepath += name;
        filepath += ".tap";

        if( !fp->Open(filepath.c_str(), IFile::OpenWrite) )
        {
            fprintf(stderr, "Unable to open file \"%s\".\n", filepath.c_str());
            fflush(stderr);
        }

        OnReportTestSuite(fp, test_suite);

        fp->Printf("1..%d\n", test_suite.total_test_count());

        fp->Close();
        detail::IFileSystem::Free(fp);
    }
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_TAP_PRINTER_HPP_77055C2B_AAE1_4944_A61C_26C58B04B37B_
