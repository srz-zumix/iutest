//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_os.h
 * @brief		iris unit test os 依存関数 ファイル
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
#ifndef INCG_IRIS_iutest_os_H_7893F685_A1A9_477a_82E8_BF06237697FF_
#define INCG_IRIS_iutest_os_H_7893F685_A1A9_477a_82E8_BF06237697FF_

//======================================================================
// include
#if defined(__MWERKS__)
#  define _MSL_USING_NAMESPACE
#endif

#include "iutest_internal_defs.h"
#include <stdlib.h>

#ifdef IUTEST_OS_NACL
#  include <ppapi/cpp/var.h>
#  include <ppapi/cpp/instance.h>
#  include <ppapi/cpp/module.h>
#endif

namespace iutest {

#ifdef IUTEST_OS_NACL
namespace nacl
{

/**
 * @brief	PostMessage
*/
inline void	PostMessage(const pp::Var& var)
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
inline void	vprint_message(const char *fmt, va_list va)
{
	char msg[1024];
	vsnprintf(msg, sizeof(msg), fmt, va);
	char* tp = strtok(msg, "\n");
	while( tp != NULL )
	{
		PostMessage(pp::Var(tp));
		tp = strtok(NULL, "\n");
	}
}
inline void	print_message(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	vprint_message(fmt, va);
	va_end(va);
}

}
#endif

namespace internal {
namespace posix
{

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

inline const char* GetEnv(const char* name)
{
#if defined(IUTEST_OS_WINDOWS_MOBILE) || defined(IUTEST_NO_GETENV)
	IUTEST_UNUSED_VAR(name);
	return NULL;
#elif defined(__BORLANDC__) || defined(__SunOS_5_8) || defined(__SunOS_5_9)
	const char* env = getenv(name);
	return (env != NULL && env[0] != '\0') ? env : NULL;
#else
	return getenv(name);
#endif
}

inline int PutEnv(const char* expr)
{
#if defined(IUTEST_OS_WINDOWS_MOBILE) || defined(IUTEST_NO_PUTENV)
	IUTEST_UNUSED_VAR(expr);
	return -1;
#else
	return putenv(const_cast<char*>(expr));
#endif
}

inline const char* GetCWD(char* buf, size_t length)
{
#if	defined(IUTEST_OS_WINDOWS_MOBILE) || defined(IUTEST_NO_GETCWD)
	IUTEST_UNUSED_VAR(buf);
	IUTEST_UNUSED_VAR(length);
	return NULL;
#elif defined(IUTEST_OS_WINDOWS)
	return ::GetCurrentDirectoryA(static_cast<DWORD>(length), buf) == 0 ? NULL : buf;
#else
	return getcwd(buf, length);
#endif
}

inline std::string GetCWD(void)
{
	char buf[260];
	return GetCWD(buf, 260);
}

#if 0

inline bool MakeDirectory(const char* path)
{
#if defined(IUTEST_OS_WINDOWS)
	return CreateDirectoryA(path, NULL) != 0;
#else
	return ::mkdir(path, 0777) == 0 && ::chmod(path, 0777) == 0;
#endif
}

#endif

inline void SleepMillisec(unsigned int millisec)
{
#if		defined(IUTEST_OS_WINDOWS)
	Sleep(millisec);
#elif	defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN)
	usleep(millisec*1000);
#else
	volatile int x=0;
	for( unsigned int i=0; i < millisec; ++i ) x += 1;
#endif
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}	// end of namespace posix
}	// end of namespace internal

namespace detail
{

/**
 * @brief	環境変数の設定
*/
inline bool SetEnvironmentVariable(const char* name, const char* value)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	return ::SetEnvironmentVariableA(name, value) ? true : false;
#else
	std::string var = name;
	var += "=";
	var += value;
	return internal::posix::PutEnv(var.c_str()) == 0 ? true : false;
#endif
}

/**
 * @brief	環境変数の取得
 * @param [in]	name	= 環境変数名
 * @param [out]	buf		= 出力バッファ
 * @return	成否
*/
template<typename T, size_t SIZE>
inline bool GetEnvironmentVariable(const char* name, T (&buf)[SIZE])
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	DWORD ret = ::GetEnvironmentVariableA(name, buf, SIZE);
	if( ret == 0 ) return false;
	if( ret > SIZE ) return false;
	return true;
#else
	const char* env = internal::posix::GetEnv(name);
	if( env == NULL ) return false;
	strcpy(buf, env);
	return true;
#endif
}

/**
 * @brief	環境変数の取得
 * @param [in]	name	= 環境変数名
 * @param [out]	var		= 出力文字列
 * @return	成否
*/
inline bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentVariable(const char* name, std::string& var)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	char buf[128];
	if( !GetEnvironmentVariable(name, buf) ) return false;
	var = buf;
	return true;
#else
	const char* env = internal::posix::GetEnv(name);
	if( env == NULL ) return false;
	var = env;
	return true;
#endif
}

/**
 * @brief	環境変数の取得
 * @param [in]	name	= 環境変数名
 * @param [out]	var		= 出力数値
 * @return	成否
*/
inline bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentInt(const char* name, int& var)
{
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	char buf[128];
	if( !GetEnvironmentVariable(name, buf) ) return false;
	char* end = NULL;
	var = static_cast<int>(strtol(buf, &end, 0));
	return true;
#else
	const char* env = internal::posix::GetEnv(name);
	if( env == NULL ) return false;
	char* end = NULL;
	var = static_cast<int>(strtol(env, &end, 0));
	return true;
#endif
}

#if defined(IUTEST_OS_WINDOWS)
namespace win
{

/**
 * @brief	文字列変換
*/
inline std::string IUTEST_ATTRIBUTE_UNUSED_ WideStringToMultiByteString(const wchar_t* wide_c_str)
{
	if( wide_c_str == NULL ) return "(null)";
	std::string str;
	const int length = static_cast<int>(wcslen(wide_c_str)) * 2 + 1;
	char* mbs = new char [length];
	WideCharToMultiByte(932, 0, wide_c_str, static_cast<int>(wcslen(wide_c_str))+1, mbs, length, NULL, NULL);
	str = mbs;
	delete [] mbs;
	return str;
}

/**
 * @brief	HRESULT のエラー文字列を取得
 * @param [in]	hr	= エラー値
 * @return	文字列
*/
inline std::string IUTEST_ATTRIBUTE_UNUSED_ GetHResultString(HRESULT hr)
{
#if defined(IUTEST_OS_WINDOWS_MOBILE)
	LPWSTR buf = NULL;
	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト ユーザー言語
		(LPWSTR)&buf,
		0,
		NULL );

	std::string str = (buf == NULL) ? "" : WideStringToMultiByteString(buf);
#else
	LPSTR buf = NULL;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト ユーザー言語
		(LPSTR)&buf,
		0,
		NULL );

	std::string str = (buf == NULL) ? "" : buf;
#endif
	LocalFree(buf);
	return str;
}

}	// end of namespace win
#endif

}	// end of namespace detail
}	// end of namespace iutest

#endif
