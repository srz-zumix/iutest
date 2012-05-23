//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_debug.h
 * @brief		iris unit test debug 用定義 ファイル
 *
 * @author		t.sirayanagi
 * @debugsion		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_debug_H_A63366D4_2112_4269_9BAF_BD30A5F2C7F2_
#define INCG_IRIS_iutest_debug_H_A63366D4_2112_4269_9BAF_BD30A5F2C7F2_

//======================================================================
// include
#include <streambuf>
#include <xlocnum>
#include <xtree>

#ifdef _IUTEST_DEBUG
// iutest 自体のデバッグ用定義

#if	defined(_MSC_VER) && !defined(IUTEST_OS_WINDOWS_MOBILE)
#  include <crtdbg.h>
#  ifndef _DEBUG_NEW_
#    define _DEBUG_NEW_		new ( _NORMAL_BLOCK , __FILE__, __LINE__)
#    pragma push_macro("new")
#    define new _DEBUG_NEW_
#  endif
#endif

#endif

namespace iutest {
namespace detail
{

static void	iuDebugInitialize(void)
{
#ifdef _IUTEST_DEBUG
#  if	defined(_MSC_VER) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#  endif
#endif
}

static void iuDebugBreakAlloc(long n)
{
#ifdef _IUTEST_DEBUG
#  if	defined(_MSC_VER) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	_CrtSetBreakAlloc(n);
#  endif
#endif
}

}	// end of namespace detail
}	// end of namespace iutest

#endif
