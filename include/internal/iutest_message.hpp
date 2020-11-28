//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_message.hpp
 * @brief       iris unit test メッセージ ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MESSAGE_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_
#define INCG_IRIS_IUTEST_MESSAGE_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_env.hpp"
#include "../iutest_printers.hpp"
// IWYU pragma: end_exports

namespace iutest {
namespace detail
{

//======================================================================
// declare
/**
 * @brief   ファイル名と行番号を連結した文字列を生成(コンパイラを考慮する)
*/
::std::string FormatFileLocation(const char* file, int line);
/**
 * @brief   ファイル名と行番号を連結した文字列を生成
*/
::std::string FormatCompilerIndependentFileLocation(const char* file, int line);

//======================================================================
// class
/**
 * @brief   メッセージクラス
*/
class iuStreamMessage
{
public:
    iuStreamMessage() {}
    explicit iuStreamMessage(const char* message) : m_stream(message) {}
    iuStreamMessage(const iuStreamMessage& rhs) : m_stream(rhs.GetString()) {}

public:
    ::std::string GetString() const { return m_stream.str(); }
public:
    template<typename T>
    iuStreamMessage& operator << (const T& value)
    {
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
        m_stream << PrintToString(value);
#else
        m_stream << value;
#endif
        return *this;
    }

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    template<typename T, size_t SIZE>
    iuStreamMessage& operator << (const T(&value)[SIZE])
    {
        m_stream << PrintToString(value);
        return *this;
    }
#else
    iuStreamMessage& operator << (bool b)
    {
        m_stream << (b ? "true" : "false");
        return *this;
    }
#endif

#if IUTEST_HAS_IOMANIP
    iuStreamMessage& operator << (iu_basic_iomanip val)
    {
        m_stream << val;
        return *this;
    }
#endif

public:
    /**
     * @brief   メッセージの追記
    */
    void add_message(const char* str) { append(str); }
private:
    void append(const char* str);

private:
    iuStreamMessage& operator = (const iuStreamMessage&);

private:
    iu_global_format_stringstream m_stream;
};

inline iu_ostream& operator << (iu_ostream& os, const iuStreamMessage& msg)
{
    return os << msg.GetString();
}

/**
 * @brief   ファイル/ライン/メッセージクラス
*/
class iuCodeMessage
{
    ::std::string   m_message;  //!< メッセージ
    const char*     m_file;     //!< ファイル名
    int             m_line;     //!< ライン
public:
    iuCodeMessage(const char* file, int line, const char* message)
        : m_message(message)
        , m_file(file ? file : kStrings::UnknownFile)
        , m_line(line)
    {}
    iuCodeMessage(const char* file, int line, const iuStreamMessage& message)
        : m_message(message.GetString())
        , m_file(file ? file : kStrings::UnknownFile)
        , m_line(line)
    {}
public:
    const char*     message() const { return m_message.c_str(); }       //!< メッセージの取得
    const char*     file_name() const IUTEST_CXX_NOEXCEPT_SPEC { return m_file; }   //!< ファイル名の取得
    int             line_number() const IUTEST_CXX_NOEXCEPT_SPEC { return m_line; } //!< ライン番号の取得


public:
    template<typename T>
    iuCodeMessage& operator << (const T& value)
    {
        m_message += (iuStreamMessage() << value).GetString();
        return *this;
    }

public:
    /**
     * @brief   メッセージの追記
    */
    void add_message(const ::std::string& str);

public:
    /** @private */
    ::std::string make_message() const;
    ::std::string make_newline_message() const
    {
        return make_message() + "\n";
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_message.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_MESSAGE_HPP_0A05C876_F204_41F5_895F_F8454AB283B1_
