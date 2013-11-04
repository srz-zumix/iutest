//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_default_xml_generator.hpp
 * @brief		iris unit test xml 出力イベントリスナー ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_default_xml_generator_HPP_791DCB98_05CC_49ba_8518_0EC9CA2B5450_
#define INCG_IRIS_iutest_default_xml_generator_HPP_791DCB98_05CC_49ba_8518_0EC9CA2B5450_

//======================================================================
// include
#include "../iutest_core.hpp"

namespace iutest
{

//======================================================================
// class
/**
 * @brief	xml出力イベントリスナー
*/
class DefaultXmlGeneratorListener : public EmptyTestEventListener
{
	::std::string	m_output_path;
	IFile*	m_fp;
public:
	/**
	 * @brief	コンストラクタ
	 * @param [in] path = 出力パス
	*/
	DefaultXmlGeneratorListener(const char* path=NULL)
		: m_fp(NULL)
	{
		SetFilePath(path);
	}
	virtual ~DefaultXmlGeneratorListener(void)
	{
		FileClose();
		TestEnv::event_listeners().set_default_xml_generator(NULL);
	}
public:
	/**
	 * @brief	出力ファイルの設定
	*/
	void	SetFilePath(const char* path)
	{
		if( path == NULL || *path == '\0' )
		{
			m_output_path = detail::kStrings::DefaultXmlReportFileName;
		}
		else
		{
			m_output_path = path;
			if( strchr(path, '.') == NULL )
			{
				m_output_path += "\\";
				m_output_path += detail::kStrings::DefaultXmlReportFileName;
			}
		}
	}
public:
	virtual void OnTestProgramStart(const UnitTest& test) IUTEST_CXX_OVERRIDE;
	virtual void OnTestProgramEnd(const UnitTest& test) IUTEST_CXX_OVERRIDE;

private:
	static void OnReportTestCase(IFile* file, const TestCase& test_case);
	static void OnReportTestInfo(IFile* file, const TestInfo& test_info);
	static void OnReportTestProperty(IFile* file, const TestResult& test_result
		, bool (*pfnValidate)(const ::std::string&));
	static void OnReportTestSkipped(IFile* file, const TestInfo& test_info);

private:
	bool FileOpen(const char* path);
	void FileClose(void);

private:
	static void	OutputXmlCDataSection(IFile* file, const char* data);
	static void OutputXmlAttribute(IFile* file, const char* name, const char* value);

private:
	static ::std::string EscapeXmlAttribute(const char* str)
	{
		return EscapeXml(str, true);
	}
	static ::std::string EscapeXmlText(const char* str)
	{
		return EscapeXml(str, false);
	}
	/**
	 * @brief	xml で使えない文字を置き換え
	*/
	static ::std::string EscapeXml(const char* str, bool is_attribute);

	/**
	 * @brief	空白かどうか
	 * @return	真偽値
	*/
	static IUTEST_CXX_CONSTEXPR bool IsWhitespace(char c)
	{
		return c == 0x9 || c == 0xA || c == 0xD;
	}
	/**
	 * @brief	xml に利用可能な文字かどうか
	 * @return	真偽値
	*/
	static IUTEST_CXX_CONSTEXPR bool IsValidXmlCharacter(char c)
	{
		return IsWhitespace(c) || c >= 0x20;
	}
};

}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_default_xml_generator.ipp"
#endif

#endif
