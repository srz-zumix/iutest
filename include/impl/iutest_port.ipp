//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_port.ipp
 * @brief       portable
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PORT_IPP_7893F685_A1A9_477A_82E8_BF06237697FF_
#define INCG_IRIS_IUTEST_PORT_IPP_7893F685_A1A9_477A_82E8_BF06237697FF_

//======================================================================
// include
#include "../internal/iutest_port.hpp"

#ifdef IUTEST_OS_NACL
#  include <ppapi/cpp/var.h>
#  include <ppapi/cpp/instance.h>
#  include <ppapi/cpp/module.h>
#endif

namespace iutest {

#ifdef IUTEST_OS_NACL
namespace nacl
{

namespace detail
{

IUTEST_IPP_INLINE void PostMessage(const pp::Var& var)
{
    ::pp::Module* module = ::pp::Module::Get();
    if( module != NULL )
    {
        if( module->current_instances().size() > 0 )
        {
            module->current_instances().begin()->second->PostMessage(var);
        }
    }
}

}   // end of namespace detail

IUTEST_IPP_INLINE void vprint_message(const char *fmt, va_list va)
{
    char msg[1024];
    vsnprintf(msg, sizeof(msg), fmt, va);
    char* tp = strtok(msg, "\n");   // NOLINT
    while( tp != NULL )
    {
        detail::PostMessage(pp::Var(tp));
        tp = strtok(NULL, "\n");    // NOLINT
    }
}
IUTEST_IPP_INLINE void print_message(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vprint_message(fmt, va);
    va_end(va);
}

}   // end of namespace nacl
#endif

namespace internal {
namespace posix
{

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

IUTEST_IPP_INLINE const char* GetEnv(const char* name)
{
#if defined(IUTEST_NO_GETENV) \
    || defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE)
    IUTEST_UNUSED_VAR(name);
    return NULL;
#elif defined(__BORLANDC__) || defined(__SunOS)
    const char* env = getenv(name);
    return (env != NULL && env[0] != '\0') ? env : NULL;
#else
    return getenv(name);
#endif
}

IUTEST_IPP_INLINE int PutEnv(const char* expr)
{
#if defined(IUTEST_NO_PUTENV) \
    || defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE) \
    || defined(IUTEST_OS_WINDOWS_MINGW)
    IUTEST_UNUSED_VAR(expr);
    return -1;
#elif defined(IUTEST_OS_WINDOWS)
    return _putenv(expr);
#else

#if (defined(__SVID_VISIBLE) && !__SVID_VISIBLE) \
    && (defined(__XSI_VISIBLE) && !__XSI_VISIBLE)
    IUTEST_UNUSED_VAR(expr);
    return -1;
#else
    return putenv(const_cast<char*>(expr));
#endif

#endif
}

IUTEST_IPP_INLINE int SetEnv(const char* name, const char* value, int overwrite)
{
#if defined(IUTEST_NO_SETENV) \
    || defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE)
    IUTEST_UNUSED_VAR(name);
    IUTEST_UNUSED_VAR(value);
    IUTEST_UNUSED_VAR(overwrite);
    return -1;
#elif defined(IUTEST_OS_WINDOWS)
    if( overwrite == 0 )
    {
        if( GetEnv(name) != NULL )
        {
            return 0;
        }
    }
    ::std::string expr = name;
    expr += "=";
    expr += value;
    return PutEnv(expr.c_str());
#else

#if (defined(__BSD_VISIBLE) && !__BSD_VISIBLE) \
    && (defined(__POSIX_VISIBLE) && __POSIX_VISIBLE < 200112)
    IUTEST_UNUSED_VAR(name);
    IUTEST_UNUSED_VAR(value);
    IUTEST_UNUSED_VAR(overwrite);
    return -1;
#else
    return setenv(name, value, overwrite);
#endif

#endif
}


IUTEST_IPP_INLINE const char* GetCWD(char* buf, size_t length)
{
#if   defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE) \
        || defined(IUTEST_OS_AVR32) || defined(__arm__) || defined(IUTEST_NO_GETCWD)
    if( buf == NULL || length < 3 )
    {
        return NULL;
    }
    buf[0] = '.';
    buf[1] = '/';
    buf[2] = '\0';
    return buf;
#elif defined(IUTEST_OS_WINDOWS)
    return ::GetCurrentDirectoryA(static_cast<DWORD>(length), buf) == 0 ? NULL : buf;
#else
    const char* result = getcwd(buf, length);
    if( result == NULL && buf != NULL && length >= 1 )
    {
#if defined(IUTEST_OS_NACL)
        if( length < 3 )
        {
            return NULL;
        }
        buf[0] = '.';
        buf[1] = '/';
        buf[2] = '\0';
        return buf;
#else
        buf[0] = '\0';
        return buf;
#endif
    }
    return result;
#endif
}

IUTEST_IPP_INLINE ::std::string GetCWD()
{
    char buf[260] = { 0 };
    return GetCWD(buf, sizeof(buf));
}

IUTEST_IPP_INLINE int SleepMillisecFor(unsigned int millisec)
{
    volatile int x=0;
    for( unsigned int i=0; i < millisec; ++i )
    {
        x = x + 1;
    }
    return x;
}

IUTEST_IPP_INLINE void SleepMillisec(unsigned int millisec)
{
#if   defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
    Sleep(millisec);
#elif defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN)

#if   defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309L
    const timespec time = { 0, static_cast<long>(millisec) * 1000 * 1000 };
    nanosleep(&time, NULL);
#elif (defined(_BSD_SOURCE) && _BSD_SOURCE)
    || (defined(_XOPEN_SOURCE)
        && (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED)
        && (!defined(_POSIX_C_SOURCE) || !(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)) )
    usleep(millisec*1000);
#else
    (void)SleepMillisecFor(millisec);
#endif

#else
    (void)SleepMillisecFor(millisec);
#endif
}

#if defined(IUTEST_OS_WINDOWS_MOBILE)
void Abort()
{
    DebugBreak();
    TerminateProcess(GetCurrentProcess(), 1);
}
#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace posix
}   // end of namespace internal

namespace detail
{

IUTEST_IPP_INLINE char GetPathSeparator() IUTEST_CXX_NOEXCEPT_SPEC
{
#ifdef IUTEST_OS_WINDOWS
    return '\\';
#else
    return '/';
#endif
}

IUTEST_IPP_INLINE bool IsPathSeparator(char c) IUTEST_CXX_NOEXCEPT_SPEC
{
#ifdef IUTEST_OS_WINDOWS
    if( c == '\\' )
    {
        return true;
    }
#endif
    return c == '/';
}

IUTEST_IPP_INLINE bool IsAltPathSeparator(char c) IUTEST_CXX_NOEXCEPT_SPEC
{
#ifdef IUTEST_OS_WINDOWS
    if( c == '/' )
    {
        return true;
    }
#else
    IUTEST_UNUSED_VAR(c);
#endif
    return false;
}

IUTEST_IPP_INLINE const char* FindLastPathSeparator(const char* path, size_t length) IUTEST_CXX_NOEXCEPT_SPEC
{
    const char* ps = path;
    const char* pe = ps + length - 1;
    while( pe >= ps )
    {
        if( IsPathSeparator(*pe) )
        {
            if( (*(pe - 1) & 0x80) == 0 )
            {
                return pe;
            }
            --pe;
        }
        --pe;
    }
    return NULL;
}

IUTEST_IPP_INLINE size_t FindLastPathSeparatorPosition(const char* path, size_t length) IUTEST_CXX_NOEXCEPT_SPEC
{
    const char* p = FindLastPathSeparator(path, length);
    if( p == NULL )
    {
        return ::std::string::npos;
    }
    return static_cast<size_t>(p - path);
}

IUTEST_IPP_INLINE bool SetEnvironmentVariable(const char* name, const char* value)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
    return ::SetEnvironmentVariableA(name, value) ? true : false;
#else
    return internal::posix::SetEnv(name, value, 1) == 0 ? true : false;
#endif
}

IUTEST_IPP_INLINE bool GetEnvironmentVariable(const char* name, char* buf, size_t size)
{
    if( buf == NULL )
    {
        return false;
    }
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE) && !defined(IUTEST_OS_WINDOWS_PHONE) && !defined(IUTEST_OS_WINDOWS_RT)
    const DWORD ret = ::GetEnvironmentVariableA(name, buf, static_cast<DWORD>(size));
    if( ret == 0 )
    {
        return false;
    }
    if( ret > size )
    {
        return false;
    }
    return true;
#else
    const char* env = internal::posix::GetEnv(name);
    if( env == NULL )
    {
        return false;
    }
    const int n = iu_snprintf(buf, size, "%s", env);
    if( n < 0 || static_cast<size_t>(n) >= size )
    {
        return false;
    }
    return true;
#endif
}

IUTEST_IPP_INLINE bool GetEnvironmentVariable(const char* name, ::std::string& var)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    char buf[4096];
    if( GetEnvironmentVariable(name, buf, sizeof(buf)) )
    {
        var = buf;
        return true;
    }
#endif
    const char* env = internal::posix::GetEnv(name);
    if( env == NULL )
    {
        return false;
    }
    var = env;
    return true;
}

IUTEST_IPP_INLINE bool GetEnvironmentInt(const char* name, int& var)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    char buf[128] = {0};
    if( !GetEnvironmentVariable(name, buf, sizeof(buf)) )
    {
        return false;
    }
    char* end = NULL;
    var = static_cast<int>(strtol(buf, &end, 0));
    return true;
#else
    const char* env = internal::posix::GetEnv(name);
    if( env == NULL )
    {
        return false;
    }
    char* end = NULL;
    var = static_cast<int>(strtol(env, &end, 0));
    return true;
#endif
}

#if defined(IUTEST_OS_WINDOWS)
namespace win
{

IUTEST_IPP_INLINE ::std::string WideStringToMultiByteString(const wchar_t* wide_c_str)
{
    if( wide_c_str == NULL ) return "";
    ::std::string str;
    const int length = static_cast<int>(wcslen(wide_c_str)) * 2 + 1;
    char* mbs = new char [length];
    WideCharToMultiByte(932, 0, wide_c_str, static_cast<int>(wcslen(wide_c_str))+1, mbs, length, NULL, NULL);
    str = mbs;
    delete [] mbs;
    return str;
}

IUTEST_IPP_INLINE ::std::string GetHResultString(HRESULT hr)
{
#if !defined(IUTEST_OS_WINDOWS_MOBILE)

#if defined(FORMAT_MESSAGE_ALLOCATE_BUFFER)
    LPSTR buf = NULL;
#else
    CHAR buf[4096];
#endif
    if( FormatMessageA(
#if defined(FORMAT_MESSAGE_ALLOCATE_BUFFER)
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
#endif
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
        , NULL
        , hr
        , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) // デフォルト ユーザー言語
#if defined(FORMAT_MESSAGE_ALLOCATE_BUFFER)
        , (LPSTR)&buf
        , 0
#else
        , buf
        , IUTEST_PP_COUNTOF(buf)
#endif
        , NULL ) == 0 )
    {
        return "";
    }

    ::std::string str = (buf == NULL) ? "" : buf;
#if defined(FORMAT_MESSAGE_ALLOCATE_BUFFER)
    LocalFree(buf);
#endif
#else
    LPWSTR buf = NULL;
    if( FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
        , NULL
        , hr
        , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) // デフォルト ユーザー言語
        , (LPWSTR)&buf
        , 0
        , NULL ) == 0 )
    {
        return "";
    }

    ::std::string str = (buf == NULL) ? "" : WideStringToMultiByteString(buf);
    LocalFree(buf);
#endif
    return str;
}

}   // end of namespace win
#endif

// declare
::std::string FormatFileLocation(const char* file, int line);

IUTEST_IPP_INLINE IUTestLog::IUTestLog(Level level, const char* file, int line)
    : kLevel(level)
{
    CountUp(level);
    const char* const tag =
        ( level == LOG_INFO    ) ?  "[  INFO ] ":
        ( level == LOG_WARNING ) ?  "[WARNING] ":
        ( level == LOG_ERROR   ) ?  "[ ERROR ] ":
                                    "[ FATAL ] ";
    GetStream() << "\n" << tag << FormatFileLocation(file, line).c_str() << ": ";
}

IUTEST_IPP_INLINE IUTestLog::~IUTestLog()
{
    GetStream() << "\n";
    fprintf(stderr, "%s", m_stream.str().c_str());
    if( kLevel == LOG_FATAL )
    {
        fflush(stderr);
        IUTEST_ABORT();
    }
}

IUTEST_IPP_INLINE void IUTestLog::CountUp(int level)
{
    if( level < LOG_LEVEL_NUM && level >= 0 )
    {
        ++GetCountTable().count[level];
    }
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_PORT_IPP_7893F685_A1A9_477A_82E8_BF06237697FF_
