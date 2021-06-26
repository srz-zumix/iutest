//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_console.hpp
 * @brief       iris unit test console
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CONSOLE_HPP_DCAC5025_B7BB_424E_A849_9E6FE0A3B460_
#define INCG_IRIS_IUTEST_CONSOLE_HPP_DCAC5025_B7BB_424E_A849_9E6FE0A3B460_

//======================================================================
// include
#include <stdio.h>
#include <stdarg.h>

namespace iutest {
namespace detail
{

//======================================================================
// define
#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)  vprintf(f, a)   //!< vprintf 呼び出しマクロ
#endif

#ifndef IUTEST_HAS_COLORCONSOLE
#  if defined(IUTEST_OS_WINDOWS_MOBILE) || defined(IUTEST_OS_NACL)
#    define IUTEST_HAS_COLORCONSOLE 0   //!< 色つきターミナルが使用可能かどうか
#  else
#    define IUTEST_HAS_COLORCONSOLE 1   //!< 色つきターミナルが使用可能かどうか
#  endif
#endif

#ifndef IUTEST_FORCE_COLORCONSOLE
# define IUTEST_FORCE_COLORCONSOLE  0
#endif

//======================================================================
// class
/**
 * @internal
 * @brief   カスタム Logger クラス
*/
class iuLogger
{
public:
    virtual ~iuLogger() IUTEST_CXX_DEFAULT_FUNCTION
    virtual void output(const char* fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 3)
    {
        va_list va;
        va_start(va, fmt);
        voutput(fmt, va);
        va_end(va);
    }
    virtual void voutput(const char* fmt, va_list va) = 0;
};

/**
 * @internal
 * @brief   コンソールクラス
*/
class iuConsole
{
public:
    //! コンソール文字色
    enum Color
    {
        black,
        red,
        green,
        yellow,
        blue,
        magenta,
        cyan,
        white
    };
public:
    /**
     * @brief   標準出力
    */
    static inline void output(const char *fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 2);

    /**
     * @brief   標準出力
    */
    static inline void voutput(const char* fmt, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 0);

    /**
     * @brief   色指定で標準出力
     * @param [in]  color   = 文字色
    */
    static inline void color_output(Color color, const char *fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 3);

public:
    /**
     * @brief   標準出力
     * @note    no logger
    */
    static inline void nl_output(const char *fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 2);

    /**
     * @brief   標準出力
     * @note    no logger
    */
    static inline void nl_voutput(const char* fmt, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 0);

public:
    //! Logger のセット
    static iuLogger* SetLogger(iuLogger* logger)
    {
        iuLogger* pre = GetLoggerInstanceVariable().pInstance;
        GetLoggerInstanceVariable().pInstance = logger;
        return pre;
    }

public:
    /**
     * @brief 色付き表示が無効かどうか
     * @return 真偽値
    */
    static bool IsColorModeOff()
    {
#if defined(INCG_IRIS_IUTEST_HPP_) && !defined(IUTEST_USE_GTEST)
        return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_OFF);
#else
        return IUTEST_FLAG(color) == "no";
#endif
    }
    /**
     * @brief 色付き表示が有効かどうか
     * @return 真偽値
    */
    static bool IsColorModeOn()
    {
#if defined(INCG_IRIS_IUTEST_HPP_) && !defined(IUTEST_USE_GTEST)
        return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ON);
#else
        return IUTEST_FLAG(color) == "yes";
#endif
    }
    /**
     * @brief 色付き表示が ANSI エスケープかどうか
     * @return 真偽値
    */
    static bool IsColorModeAnsi()
    {
#if defined(INCG_IRIS_IUTEST_HPP_) && !defined(IUTEST_USE_GTEST)
        return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ANSI);
#else
        return false;
#endif
    }

private:
    static inline void color_output_impl(Color color, const char* fmt, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(2, 0);
    static inline bool IsShouldUseColor(bool use_color);
    static inline bool HasColorConsole();
#if IUTEST_HAS_COLORCONSOLE && !IUTEST_FORCE_COLORCONSOLE
    static inline bool IsStringEqual(const char* str1, const char* str2) { return strcmp(str1, str2) == 0; }
#endif

private:
    struct LoggerInstanceVariable
    {
        iuLogger* pInstance;
    };

    static LoggerInstanceVariable& GetLoggerInstanceVariable() { static LoggerInstanceVariable sLogger; return sLogger; }
    static iuLogger* GetLogger() { return GetLoggerInstanceVariable().pInstance; }
};

inline void iuConsole::output(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    voutput(fmt, va);
    va_end(va);
}
inline void iuConsole::voutput(const char* fmt, va_list va)
{
    iuLogger* pLogger = GetLogger();
    if(pLogger != NULL)
    {
        pLogger->voutput(fmt, va);
    }
    else
    {
        nl_voutput(fmt, va);
    }
}
inline void iuConsole::color_output(Color color, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    if( IsShouldUseColor(true) )
    {
        color_output_impl(color, fmt, va);
    }
    else
    {
        voutput(fmt, va);
    }

    va_end(va);
}
inline void iuConsole::nl_output(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    nl_voutput(fmt, va);
    va_end(va);
}
inline void iuConsole::nl_voutput(const char* fmt, va_list va)
{
    IUTEST_VPRINTF(fmt, va);
}

inline void iuConsole::color_output_impl(Color color, const char* fmt, va_list va)
{
    (void)(fmt);
    (void)(va);
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) \
        && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
    if( !IsColorModeAnsi() )
    {
        const WORD attr[] = {
            0,
            FOREGROUND_RED,
            FOREGROUND_GREEN,
            FOREGROUND_GREEN | FOREGROUND_RED,
            FOREGROUND_BLUE,
            FOREGROUND_RED | FOREGROUND_BLUE,
            FOREGROUND_GREEN | FOREGROUND_BLUE,
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
        };
        const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if( stdout_handle != INVALID_HANDLE_VALUE )
        {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if( ::GetConsoleScreenBufferInfo(stdout_handle, &csbi) )
            {
                const WORD wAttributes = csbi.wAttributes;

                fflush(stdout);
                ::SetConsoleTextAttribute(stdout_handle, attr[color] | FOREGROUND_INTENSITY);

                voutput(fmt, va);

                fflush(stdout);
                ::SetConsoleTextAttribute(stdout_handle, wAttributes);
                return;
            }
        }
    }
#endif
    {
        output("\033[1;3%cm", '0' + color);
        voutput(fmt, va);
        output("\033[m");
    }
}

inline bool iuConsole::IsShouldUseColor(bool use_color)
{
    if( IsColorModeOn() )
    {
        return true;
    }
    else if( IsColorModeOff() )
    {
        return false;
    }
    static bool has_color = HasColorConsole();
    return use_color && has_color;
}

inline bool iuConsole::HasColorConsole()
{
#if   !IUTEST_HAS_COLORCONSOLE
    return false;
#elif IUTEST_FORCE_COLORCONSOLE
    return true;
#else
#if defined(IUTEST_OS_WINDOWS)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if( ::GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) )
        {
            return true;
        }
    }
#endif
    const char* env = internal::posix::GetEnv("TERM");
    const bool term_conf = (env != NULL) && (
        IsStringEqual(env, "xterm")
        || IsStringEqual(env, "xterm-color")
        || IsStringEqual(env, "xterm-256color")
        || IsStringEqual(env, "screen")
        || IsStringEqual(env, "screen-256color")
        || IsStringEqual(env, "tmux")
        || IsStringEqual(env, "tmux-256color")
        || IsStringEqual(env, "rxvt-unicode")
        || IsStringEqual(env, "rxvt-unicode-256color")
        || IsStringEqual(env, "linux")
        || IsStringEqual(env, "cygwin")
        );
    if( term_conf )
    {
        return true;
    }
    // for CI
    if( internal::posix::GetEnv("GITHUB_ACTIONS") != NULL )
    {
        return true;
    }
    return false;
#endif
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_CONSOLE_HPP_DCAC5025_B7BB_424E_A849_9E6FE0A3B460_
