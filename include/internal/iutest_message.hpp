//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_message.hpp
 * @brief		iris unit test メッセージ ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_message_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_
#define INCG_IRIS_iutest_message_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_

//======================================================================
// include
#include "iutest_charcode.hpp"
#include "iutest_constant.hpp"

namespace iutest {
namespace detail
{

//======================================================================
// declare
/**
 * @brief	ファイル名と行番号を連結した文字列を生成(コンパイラを考慮する)
*/
::std::string FormatFileLocation(const char* file, int line);
/**
 * @brief	ファイル名と行番号を連結した文字列を生成
*/
::std::string FormatCompilerIndependentFileLocation(const char* file, int line);

//======================================================================
// class
/**
 * @brief	メッセージクラス
*/
class iuMessage
{
	::std::string	m_message;	//!< メッセージ
public:
	iuMessage(void) {}
	explicit iuMessage(const char* message) : m_message(message) {}
	iuMessage(const iuMessage& rhs) : m_message(rhs.m_message) {}

	const char*		message(void)	const	{ return m_message.c_str(); }	//!< メッセージの取得

public:
	::std::string GetString(void)	const { return m_message; }
public:
	template<typename T>
	iuMessage&	operator << (const T& value) 
	{
		detail::iuStringStream::type strm;
		strm << value;
		m_message += strm.str();
		return *this;
	}
	template<typename T>
	iuMessage&	operator << (T* const& value) 
	{
		if( value == NULL ) 
		{
			m_message += "(null)";
		}
		else
		{
			detail::iuStringStream::type strm;
			strm << value;
			m_message += strm.str();
		}
		return *this;
	}
	iuMessage&	operator << (bool b) 
	{
		m_message += b ? "true" : "false";
		return *this;
	}
	iuMessage&	operator << (char* str)
	{
		append(str);
		return *this;
	}
	iuMessage&	operator << (const char* str)
	{
		append(str);
		return *this;
	}
	iuMessage&	operator << (wchar_t* str)
	{
		m_message += ShowWideCString(str);
		return *this;
	}
	iuMessage&	operator << (const wchar_t* str)
	{
		m_message += ShowWideCString(str);
		return *this;
	}
	iuMessage&	operator << (const iuMessage& message)
	{
		m_message += message.m_message;
		return *this;
	}
public:
	/**
	 * @brief	メッセージの追記
	*/
	void	add_message(const char* str) { append(str); }
private:
	void	append(const char* str);
};

inline iu_ostream& operator << (iu_ostream& os, const iuMessage& msg)
{
	return os << msg.message();
}

/**
 * @brief	ファイル/ライン/メッセージクラス
*/
class iuCodeMessage : public iuMessage
{
	const char*	m_file;		//!< ファイル名
	int			m_line;		//!< ライン
public:
	iuCodeMessage(const char* file, int line, const char* message)
		: iuMessage(message)
		, m_file(file ? file : kStrings::UnkownFile)
		, m_line(line)
	{}
	iuCodeMessage(const char* file, int line, const iuMessage& message)
		: iuMessage(message)
		, m_file(file ? file : kStrings::UnkownFile)
		, m_line(line)
	{}
	iuCodeMessage(const iuCodeMessage& rhs)
		: iuMessage(rhs)
		, m_file(rhs.m_file)
		, m_line(rhs.m_line)
	{}
public:
	template<typename T>
	iuCodeMessage&		operator << (T value)
	{
		iuMessage::operator << (value);
		return *this;
	}
public:
	const char*		file_name(void)		const	{ return m_file; }				//!< ファイル名の取得
	int				line_number(void)	const	{ return m_line; }				//!< ライン番号の取得
public:
	/** @private */
	::std::string	make_message(void) const
	{
		::std::string str = FormatFileLocation(m_file, m_line);
		str += ": ";
		str += message();
		return str;
	}
	::std::string	make_newline_message(void) const
	{
		return make_message() + "\n";
	}
};

//======================================================================
// function
inline void iuMessage::append(const char* str)
{
	if( str == NULL )
	{
		m_message += "(null)";
	}
	else
	{
		m_message += str;
	}
}

inline ::std::string FormatFileLocation(const char* file, int line)
{
	const char* const file_name = file == NULL ? kStrings::UnkownFile : file;
	if( line < 0 ) return file;
	iuStringStream::type strm;
#ifdef _MSC_VER
	strm << file_name << "(" << line << ")";
#else
	strm << file_name << ":" << line;
#endif
	return strm.str();
}

inline ::std::string FormatCompilerIndependentFileLocation(const char* file, int line)
{
	const char* const file_name = file == NULL ? kStrings::UnkownFile : file;
	if( line < 0 ) return file;
	iuStringStream::type strm;
	strm << file_name << ":" << line;
	return strm.str();
}

}	// end of namespace detail
}	// end of namespace iutest

#endif
