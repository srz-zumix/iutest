//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_default_xml_generator.hpp
 * @brief       iris unit test xml 出力イベントリスナー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_HPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_
#define INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_HPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_

namespace iutest
{

//======================================================================
// class
/**
 * @brief   xml出力イベントリスナー
*/
class DefaultXmlGeneratorListener : public EmptyTestEventListener
{
    ::std::string m_output_path_format;
    ::std::string m_output_path;
protected:
    IFile* m_fp;
public:
    /**
     * @brief   コンストラクタ
     * @param [in] path = 出力パス
    */
    explicit DefaultXmlGeneratorListener(const ::std::string& path)
        : m_fp(NULL)
    {
        SetFilePath(path);
    }
    virtual ~DefaultXmlGeneratorListener()
    {
        FileClose();
        TestEnv::event_listeners().set_default_xml_generator(NULL);
    }
public:
    /**
     * @brief   出力ファイルパスの取得
    */
    const ::std::string& GetFilePath() const { return m_output_path; }

private:
    /**
     * @brief   出力ファイルの設定
    */
    void SetFilePath(const ::std::string& path)
    {
        if( path.empty() )
        {
            m_output_path_format.clear();
            m_output_path = detail::kStrings::DefaultXmlReportFileName;
        }
        else
        {
            m_output_path_format = path;
            const ::std::string::size_type pos = path.find('.');
            if( pos == ::std::string::npos
                || pos == path.length()-1 )
            {
                m_output_path_format += detail::GetPathSeparator();
                m_output_path_format += detail::kStrings::DefaultXmlReportFileName;
            }
            m_output_path = m_output_path_format;
        }
    }

public:
    virtual void OnTestIterationStart(const UnitTest& test, int iteration) IUTEST_CXX_OVERRIDE;
    virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

private:
    virtual bool IsReportable(const UnitTest& test) { IUTEST_UNUSED_VAR(test); return true; }
    virtual void OnReportTest(IFile* file, const UnitTest& test);

private:
    static void OnReportTestSuite(IFile* file, const TestSuite& test_suite);
    static void OnReportTestInfo(IFile* file, const TestInfo& test_info);
    static void OnReportTestProperty(IFile* file, const TestResult& test_result
        , bool (*pfnValidate)(const ::std::string&));
    static void OnReportTestSkipped(IFile* file, const TestInfo& test_info);

private:
    virtual bool FileOpen(const char* path);
    virtual void FileClose();

protected:
    static void OutputXmlCDataSection(IFile* file, const char* data);
    static void OutputXmlAttribute(IFile* file, const char* name, const char* value);

protected:
    static ::std::string EscapeXmlAttribute(const char* str)
    {
        return EscapeXml(str, true);
    }
    static ::std::string EscapeXmlAttribute(const ::std::string str)
    {
        return EscapeXml(str.c_str(), true);
    }
    static ::std::string EscapeXmlText(const char* str)
    {
        return EscapeXml(str, false);
    }
    /**
     * @brief   xml で使えない文字を置き換え
    */
    static ::std::string EscapeXml(const char* str, bool is_attribute);

    /**
     * @brief   空白かどうか
     * @return  真偽値
    */
    static IUTEST_CXX_CONSTEXPR bool IsWhitespace(char c)
    {
        return c == 0x9 || c == 0xA || c == 0xD;
    }
    /**
     * @brief   xml に利用可能な文字かどうか
     * @return  真偽値
    */
    static IUTEST_CXX_CONSTEXPR bool IsValidXmlCharacter(char c)
    {
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
        return IsWhitespace(c) || c >= 0x20;
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
    }

public:
    /** @private */
    static bool SetUp()
    {
        ::std::string xmlpath = TestEnv::get_report_xml_filepath();
        if( !xmlpath.empty() )
        {
            TestEnv::event_listeners().set_default_xml_generator(new DefaultXmlGeneratorListener(xmlpath));
            return true;
        }
        return false;
    }
};

}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_default_xml_generator.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_DEFAULT_XML_GENERATOR_HPP_791DCB98_05CC_49BA_8518_0EC9CA2B5450_
