//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_platform.hpp
 * @brief       iris unit test platform detection
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PLATFORM_HPP_38809F61_271D_4B85_A51E_211004A99F5A_
#define INCG_IRIS_IUTEST_PLATFORM_HPP_38809F61_271D_4B85_A51E_211004A99F5A_

//======================================================================
// define

// os
#if   defined(__CYGWIN__)
#  define IUTEST_OS_CYGWIN              1
#  define IUTEST_PLATFORM               "CYGWIN"
#elif defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(WINAPI_FAMILY)
#  define IUTEST_OS_WINDOWS             1
#  if !defined(WIN32_LEAN_AND_MEAN)
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <Windows.h>
#  if defined(_WIN32_WCE)
#    define IUTEST_OS_WINDOWS_MOBILE    1
#    define IUTEST_PLATFORM             "Windows CE"
#  elif defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
#    define IUTEST_OS_WINDOWS_MINGW     1
#  elif defined(__WINE__)
#    define IUTEST_OS_WINDOWS_WINE      1
#    define IUTEST_PLATFORM             "WINE"
#  elif defined(__CUDACC__)
#    define IUTEST_OS_WINDOWS_CUDA      1
#  elif defined(WINAPI_FAMILY)
#    if defined(WINAPI_FAMILY_PHONE_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#      define IUTEST_OS_WINDOWS_PHONE   1
#      define IUTEST_PLATFORM           "Windows Phone"
#    elif defined(WINAPI_FAMILY_APP) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
#      define IUTEST_OS_WINDOWS_RT      1
#      define IUTEST_PLATFORM           "Windows RT"
#    else
#      define IUTEST_OS_WINDOWS_DESKTOP 1
#    endif
#  else
#    define IUTEST_OS_WINDOWS_DESKTOP   1
#  endif
#  if !defined(IUTEST_PLATFORM)
#    define IUTEST_PLATFORM             "Windows"
#  endif
#elif defined(__APPLE__)
#  include "TargetConditionals.h"
#  if TARGET_OS_IPHONE
#    define IUTEST_OS_IOS               1
#    define IUTEST_PLATFORM             "iOS"
#  else
#    define IUTEST_OS_MAC               1
#    define IUTEST_PLATFORM             "Mac OS"
#  endif
#elif defined(__FreeBSD__)
#  define IUTEST_OS_FREEBSD             1
#  define IUTEST_PLATFORM               "FreeBSD"
#elif defined(sun) || defined(__sun)
#  define IUTEST_OS_SOLARIS             1
#  define IUTEST_PLATFORM               "Solaris"
#elif defined(__linux__)
#  define IUTEST_OS_LINUX               1
#  if defined(ANDROID) || defined(__ANDROID__)
#    define IUTEST_OS_LINUX_ANDROID     1
#    define IUTEST_PLATFORM             "Android"
#  else
#    define IUTEST_PLATFORM             "LINUX"
#  endif
#elif defined(__native_client__)
#  define IUTEST_OS_NACL                1   //!< @deprecated native client to eol
#  define IUTEST_PLATFORM               "Google Native Client"
#elif defined(__AVR32__) || defined(__avr32__)
#  define IUTEST_OS_AVR32               1
#  define IUTEST_PLATFORM               "AVR32"
#endif

#if defined(IUTEST_OS_LINUX_ANDROID)
#  include <android/api-level.h>
#endif

#endif // INCG_IRIS_IUTEST_PLATFORM_HPP_38809F61_271D_4B85_A51E_211004A99F5A_
