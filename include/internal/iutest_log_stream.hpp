﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_log_stream.hpp
 * @brief       iris unit test log io stream
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_LOG_STREAM_HPP_090644E7_9AA3_48DA_A526_BD4060DB52CF_
#define INCG_IRIS_IUTEST_LOG_STREAM_HPP_090644E7_9AA3_48DA_A526_BD4060DB52CF_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_env.hpp"
#include "iutest_console.hpp"
#include "iutest_stream.hpp"
// IWYU pragma: end_exports

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief   ログ出力ストリームインターフェイス
*/
class LogStream : public IOutStream
{
public:
    /**
     * @brief   書き込み
     * @param [in]  buf     = 書き込みバッファ
     * @param [in]  size    = バッファサイズ
     * @param [in]  cnt     = 書き込み回数
    */
    virtual bool Write(const void* buf, size_t size, size_t cnt) IUTEST_CXX_OVERRIDE
    {
        IUTEST_UNUSED_VAR(size);
        const char* str = static_cast<const char*>(buf);
        for( size_t i=0; i < cnt; ++i )
        {
            iuConsole::output("%s", str);
        }
        return true;
    }
    virtual int Printf(const char* fmt, ...) IUTEST_CXX_OVERRIDE IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 3)
    {
        va_list va;
        va_start(va, fmt);
        iuConsole::voutput(fmt, va);
        va_end(va);
        return 0;
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_LOG_STREAM_HPP_090644E7_9AA3_48DA_A526_BD4060DB52CF_
