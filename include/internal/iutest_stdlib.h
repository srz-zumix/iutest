//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_stdlib.h
 * @brief		iris unit test stdlib ˆË‘¶‚Ì‹zŽû ƒtƒ@ƒCƒ‹
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_stdlib_H_54D4BEEE_7B6B_4af4_B1F6_138560480D55_
#define INCG_IRIS_iutest_stdlib_H_54D4BEEE_7B6B_4af4_B1F6_138560480D55_

//======================================================================
// include

//======================================================================
// define

// chrono
#ifndef IUTEST_HAS_CXX11_HDR_CHRONO

#if		defined(__GLIBCXX__)
#  if defined(__GNUC__)
#    if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define IUTEST_HAS_CXX11_HDR_CHRONO	1
#    endif
#  else
#  endif
#elif	defined(_MSC_VER)
#  if _MSC_VER > 1600
#    define IUTEST_HAS_CXX11_HDR_CHRONO		1
#  endif
#endif

#endif

#ifndef IUTEST_HAS_CXX11_HDR_CHRONO
#  define IUTEST_HAS_CXX11_HDR_CHRONO	0
#endif

#endif
