//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_stream.hpp
 * @brief       io stream
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STREAM_HPP_3A4AF139_9F24_4730_81D0_DADFCE6DCF99_
#define INCG_IRIS_IUTEST_STREAM_HPP_3A4AF139_9F24_4730_81D0_DADFCE6DCF99_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_string.hpp"
// IWYU pragma: end_exports

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief   出力ストリームインターフェイス
*/
class IOutStream
{
public:
    virtual ~IOutStream() {}
public:
    //! 書き込み
    virtual bool Write(const void* buf, size_t size, size_t cnt) = 0;
public:
    virtual int Printf(const char* fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 3)
    {
        va_list va;
        va_start(va, fmt);
        const ::std::string str = StringFormat(fmt, va);
        va_end(va);
        const size_t len = str.length();
        Write(str.c_str(), len, 1);
        return static_cast<int>(len);
    }
};

/**
 * @brief   入力ストリームインターフェイス
*/
class IInStream
{
public:
    virtual ~IInStream() {}
public:
    //! 読み込み
    virtual bool Read(void* buf, size_t size, size_t cnt) = 0;

    //! サイズ取得
    virtual size_t GetSize() = 0;

public:
    //! 全読み込み
    virtual ::std::string ReadAll()
    {
        ::std::string str;
        const size_t size = GetSize();
        if( size != 0 )
        {
            char* buf = new char[size+1];
            buf[size] = '\0';
            if( Read(buf, size, 1) )
            {
                str = buf;
            }
            delete [] buf;
        }
        return str;
    }
};

/**
 * @brief   ファイルIO出力ストリームインターフェイス
*/
class FileOutStream : public IOutStream
{
protected:
    FILE* m_fp;
public:
    explicit FileOutStream(FILE* fp) IUTEST_CXX_NOEXCEPT_SPEC
        : m_fp(fp)
    {}
public:
    /**
     * @brief   書き込み
     * @param [in]  buf     = 書き込みバッファ
     * @param [in]  size    = バッファサイズ
     * @param [in]  cnt     = 書き込み回数
    */
    virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        if( fwrite(buf, size, cnt, m_fp) < cnt )
        {
            return false;
        }
        return true;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STREAM_HPP_3A4AF139_9F24_4730_81D0_DADFCE6DCF99_
