﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_port.hpp
 * @brief       portable 定義切り替え ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_PORT_HPP_2B432CD6_18CE_4D0C_B0CD_4E4D5B8E34F4_
#define INCG_IRIS_IUTEST_SWITCH_PORT_HPP_2B432CD6_18CE_4D0C_B0CD_4E4D5B8E34F4_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#if defined(GTEST_INCLUDE_GTEST_GTEST_H_)

#ifdef GTEST_OS_CYGWIN
#  undef GTEST_OS_CYGWIN
#endif
#ifdef GTEST_OS_WINDOWS
#  undef GTEST_OS_WINDOWS
#  ifdef GTEST_OS_WINDOWS_MOBILE
#    undef GTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef GTEST_OS_WINDOWS_MINGW
#    undef GTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef GTEST_OS_WINDOWS_DESKTOP
#    undef GTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef GTEST_OS_MAC
#  undef GTEST_OS_MAC
#  ifdef GTEST_OS_IOS
#    undef GTEST_OS_IOS
#  endif
#endif
#ifdef GTEST_OS_FREEBSD
#  undef GTEST_OS_FREEBSD
#endif
#ifdef GTEST_OS_SOLARIS
#  undef GTEST_OS_SOLARIS
#endif
#ifdef GTEST_OS_LINUX
#  undef GTEST_OS_LINUX
#  ifdef GTEST_OS_LINUX_ANDROID
#    undef GTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  undef IUTEST_OS_NACL
#endif

#define GTEST_ATTRIBUTE_UNUSED_         IUTEST_ATTRIBUTE_UNUSED_

#endif

//======================================================================
// define
#ifdef IUTEST_OS_CYGWIN
#  define GTEST_OS_CYGWIN               IUTEST_OS_CYGWIN
#endif
#ifdef IUTEST_OS_WINDOWS
#  define GTEST_OS_WINDOWS              IUTEST_OS_WINDOWS
#  ifdef IUTEST_OS_WINDOWS_MOBILE
#    define GTEST_OS_WINDOWS_MOBILE     IUTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef IUTEST_OS_WINDOWS_MINGW
#    define GTEST_OS_WINDOWS_MINGW      IUTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef IUTEST_OS_WINDOWS_DESKTOP
#    define GTEST_OS_WINDOWS_DESKTOP    IUTEST_OS_WINDOWS_DESKTOP
#  endif
#  ifdef IUTEST_OS_WINDOWS_PHONE
#    define GTEST_OS_WINDOWS_PHONE      IUTEST_OS_WINDOWS_PHONE
#  endif
#  ifdef IUTEST_OS_WINDOWS_RT
#    define GTEST_OS_WINDOWS_RT         IUTEST_OS_WINDOWS_RT
#  endif
#  ifdef IUTEST_OS_WINDOWS_WINE
#    define GTEST_OS_WINDOWS_WINE       IUTEST_OS_WINDOWS_WINE
#  endif
#endif
#ifdef IUTEST_OS_MAC
#  define GTEST_OS_MAC                  IUTEST_OS_MAC
#endif
#ifdef IUTEST_OS_IOS
#  define GTEST_OS_IOS                  IUTEST_OS_IOS
#endif
#ifdef IUTEST_OS_FREEBSD
#  define GTEST_OS_FREEBSD              IUTEST_OS_FREEBSD
#endif
#ifdef IUTEST_OS_SOLARIS
#  define GTEST_OS_SOLARIS              IUTEST_OS_SOLARIS
#endif
#ifdef IUTEST_OS_LINUX
#  define GTEST_OS_LINUX                IUTEST_OS_LINUX
#  ifdef IUTEST_OS_LINUX_ANDROID
#    define GTEST_OS_LINUX_ANDROID      IUTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  define GTEST_OS_NACL                 IUTEST_OS_NACL
#endif

#else // !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#ifdef IUTEST_OS_CYGWIN
#  undef IUTEST_OS_CYGWIN
#endif
#ifdef IUTEST_OS_WINDOWS
#  undef IUTEST_OS_WINDOWS
#  ifdef IUTEST_OS_WINDOWS_PHONE
#    undef IUTEST_OS_WINDOWS_PHONE
#  endif
#  ifdef IUTEST_OS_WINDOWS_RT
#    undef IUTEST_OS_WINDOWS_RT
#  endif
#  ifdef IUTEST_OS_WINDOWS_MOBILE
#    undef IUTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef IUTEST_OS_WINDOWS_MINGW
#    undef IUTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef IUTEST_OS_WINDOWS_DESKTOP
#    undef IUTEST_OS_WINDOWS_DESKTOP
#  endif
#endif
#ifdef IUTEST_OS_MAC
#  undef IUTEST_OS_MAC
#  ifdef IUTEST_OS_IOS
#    undef IUTEST_OS_IOS
#  endif
#endif
#ifdef IUTEST_OS_FREEBSD
#  undef IUTEST_OS_FREEBSD
#endif
#ifdef IUTEST_OS_SOLARIS
#  undef IUTEST_OS_SOLARIS
#endif
#ifdef IUTEST_OS_LINUX
#  undef IUTEST_OS_LINUX
#  ifdef IUTEST_OS_LINUX_ANDROID
#    undef IUTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef IUTEST_OS_NACL
#  undef IUTEST_OS_NACL
#endif

#undef IUTEST_ATTRIBUTE_UNUSED_

//======================================================================
// define
#ifdef GTEST_OS_CYGWIN
#  define IUTEST_OS_CYGWIN      GTEST_OS_CYGWIN
#endif
#ifdef GTEST_OS_WINDOWS
#  include <windows.h>
#  define IUTEST_OS_WINDOWS             GTEST_OS_WINDOWS
#  ifdef GTEST_OS_WINDOWS_PHONE
#    define IUTEST_OS_WINDOWS_PHONE     GTEST_OS_WINDOWS_PHONE
#  endif
#  ifdef GTEST_OS_WINDOWS_RT
#    define IUTEST_OS_WINDOWS_RT        GTEST_OS_WINDOWS_RT
#  endif
#  ifdef GTEST_OS_WINDOWS_MOBILE
#    define IUTEST_OS_WINDOWS_MOBILE    GTEST_OS_WINDOWS_MOBILE
#  endif
#  ifdef GTEST_OS_WINDOWS_MINGW
#    define IUTEST_OS_WINDOWS_MINGW     GTEST_OS_WINDOWS_MINGW
#  endif
#  ifdef GTEST_OS_WINDOWS_DESKTOP
#    define IUTEST_OS_WINDOWS_DESKTOP   GTEST_OS_WINDOWS_DESKTOP
#  endif
#  ifdef GTEST_OS_WINDOWS_PHONE
#    define IUTEST_OS_WINDOWS_PHONE     GTEST_OS_WINDOWS_PHONE
#  endif
#  ifdef GTEST_OS_WINDOWS_RT
#    define IUTEST_OS_WINDOWS_RT        GTEST_OS_WINDOWS_RT
#  endif
#endif
#ifdef GTEST_OS_MAC
#  define IUTEST_OS_MAC                 GTEST_OS_MAC
#endif
#ifdef GTEST_OS_IOS
#  define IUTEST_OS_IOS                 GTEST_OS_IOS
#endif
#ifdef GTEST_OS_FREEBSD
#  define IUTEST_OS_FREEBSD             GTEST_OS_FREEBSD
#endif
#ifdef GTEST_OS_SOLARIS
#  define IUTEST_OS_SOLARIS             GTEST_OS_SOLARIS
#endif
#ifdef GTEST_OS_LINUX
#  define IUTEST_OS_LINUX               GTEST_OS_LINUX
#  ifdef GTEST_OS_LINUX_ANDROID
#    define IUTEST_OS_LINUX_ANDROID     GTEST_OS_LINUX_ANDROID
#  endif
#endif
#ifdef GTEST_OS_NACL
#  define IUTEST_OS_NACL                GTEST_OS_NACL
#endif

#define IUTEST_ATTRIBUTE_UNUSED_        GTEST_ATTRIBUTE_UNUSED_

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

//======================================================================
// function
namespace testing {
namespace internal {
namespace posix
{

inline int PutEnv(const char* expr)
{
#if defined(IUTEST_NO_PUTENV) || defined(__STRICT_ANSI__) \
    || defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE)
    (void)(expr);
    return -1;
#elif defined(IUTEST_OS_WINDOWS)
    return _putenv(expr);
#else
    return putenv(const_cast<char*>(expr));
#endif
}

inline int SetEnv(const char* name, const char* value, int overwrite)
{
#if defined(IUTEST_NO_SETENV) || defined(__STRICT_ANSI__) \
    || defined(IUTEST_OS_WINDOWS_PHONE) || defined(IUTEST_OS_WINDOWS_RT) || defined(IUTEST_OS_WINDOWS_MOBILE)
    (void)(name);
    (void)(value);
    (void)(overwrite);
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
    return setenv(name, value, overwrite);
#endif
}

}   // end of namespace posix
}   // end of namespace internal

inline int iu_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
#if   defined(_MSC_VER)
    return _wcsicmp(str1, str2);
#elif defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID)
    return wcscasecmp(str1, str2);
#else
    const wchar_t* l = str1;
    const wchar_t* r = str2;
    while(*l)
    {
        wchar_t ul = towupper(*l);
        wchar_t ur = towupper(*r);
        if( ul < ur )
        {
            return -1;
        }
        if( ul > ur )
        {
            return 1;
        }
        ++l;
        ++r;
    }
    if( *l < *r )
    {
        return -1;
    }
    if( *l > *r )
    {
        return 1;
    }
    return 0;
#endif
}

}   // end of namespace testing

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_PORT_HPP_2B432CD6_18CE_4D0C_B0CD_4E4D5B8E34F4_
