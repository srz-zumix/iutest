//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_stderr_xml_generator.hpp
 * @brief		output stderr (junit) xml event listener
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_
#define INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_

//======================================================================
// include
#include "iutest_junit_xml_generator.hpp"

namespace iutest
{

//======================================================================
// class

namespace detail
{

/**
 * @brief	xml result output to stderr
*/
template<typename T>
class StderrXmlGeneratorListenerBase : public T
{
	StdErrorFile m_stderr;
private:
	virtual bool FileOpen(const char* path)
	{
		if( m_stderr.Open(path, IFile::OpenReadWrite) )
		{
			m_fp = &m_stderr;
			return true;
		}
		return false;
	}
	virtual void FileClose()
	{
		m_fp = nullptr;
	}

public:
	/** @private */
	static void SetUp()
	{
		TestEnv::event_listeners().set_default_xml_generator(new StderrXmlGeneratorListener());
	}
};

}	// end of namespace detail

typedef detail::StderrXmlGeneratorListenerBase<DefaultXmlGeneratorListener> StderrXmlGeneratorListener;
typedef detail::StderrXmlGeneratorListenerBase<JunitXmlGeneratorListener> StderrJunitXmlGeneratorListener;

}	// end of namespace iutest

#endif // INCG_IRIS_IUTEST_STDERR_XML_GENERATOR_HPP_44748A14_3446_49D5_8ECE_05ABED0FFF33_
