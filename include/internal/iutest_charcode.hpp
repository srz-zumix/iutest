//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_charcode.hpp
 * @brief		iris unit test 文字コード対応 ファイル
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
#ifndef INCG_IRIS_iutest_charcode_HPP_D444FB3E_3AFA_46d0_AD69_33FAAF5615E3_
#define INCG_IRIS_iutest_charcode_HPP_D444FB3E_3AFA_46d0_AD69_33FAAF5615E3_

//======================================================================
// include
#include "iutest_port.hpp"

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

//======================================================================
// declare
IUTEST_CONSTEXPR bool	IsUtf16SurrogatePair(wchar_t first, wchar_t second);
IUTEST_CONSTEXPR UInt32 CreateCodePointFromUtf16SurrogatePair(wchar_t first, wchar_t second);
UInt32	ChopLowBits(UInt32* bits, int n);
char*	CodePointToUtf8(UInt32 code_point, char* buf);
::std::string WideStringToUTF8(const wchar_t* str, int num=-1);
::std::string MultiByteStringToUTF8(const char* src, int num=-1);
::std::string ShowWideCString(const wchar_t* wide_c_str);

//======================================================================
// variable
const UInt32 kMaxCodePoint1 = (static_cast<UInt32>(1) << 7) - 1;
const UInt32 kMaxCodePoint2 = (static_cast<UInt32>(1) << (5+6)) - 1;
const UInt32 kMaxCodePoint3 = (static_cast<UInt32>(1) << (4+2*6)) - 1;
const UInt32 kMaxCodePoint4 = (static_cast<UInt32>(1) << (3+3*6)) - 1;

//======================================================================
// struct
/**
 * @brief	mbs_ptr
*/
template<typename CharType>
struct mbs_ptr
{
	struct wcs_impl
	{
		::std::string m_arg;
		const char* ptr(const wchar_t* arg) 
		{
			m_arg = ShowWideCString(arg);
			return m_arg.c_str();
		}
	};
	struct mbs_impl
	{
		const char* ptr(const char* arg) { return arg; }
	};
	template<typename T, typename DMY>
	struct select { typedef mbs_impl type; };
	template<typename DMY>
	struct select<wchar_t, DMY> { typedef wcs_impl type; };

	typedef typename select<typename remove_const<CharType>::type, void>::type	type;
};

//======================================================================
// function
/**
 * @brief	サロゲートペアかどうか
*/
inline IUTEST_CONSTEXPR bool	IsUtf16SurrogatePair(wchar_t first, wchar_t second)
{
	return (sizeof(wchar_t) == 2)
		&& ((first & 0xFC00) == 0xD800) && ((second & 0xFC00) == 0xDC00);
}
/**
 * @brief	サロゲートペアからコードポイントへ変換
*/
inline IUTEST_CONSTEXPR UInt32 CreateCodePointFromUtf16SurrogatePair(wchar_t first, wchar_t second)
{
	//const UInt32 mask = (1<<10) -1;	// 0x3FF
	return (sizeof(wchar_t)==2) ?
		(((first & 0x3FF) << 10) | (second & 0x3FF)) + 0x10000 :
		static_cast<UInt32>(first);	// こっちは未対応
}
/**
 * @brief	下位から指定ビット数のビットを取得してシフトする
*/
inline UInt32 ChopLowBits(UInt32* bits, int n)
{
	const UInt32 lowbits = *bits & ((static_cast<UInt32>(1) << n) - 1);
	*bits >>= n;
	return lowbits;
}
/**
 * @brief	コードポイントからUTF8へ変換
 * @param [in]	code_point	= コードポイント
 * @param [out]	buf			= 出力バッファ(32バイト以上を要求)
 * @return	出力バッファ
*/
inline char* CodePointToUtf8(UInt32 code_point, char* buf)
{
	if( code_point <= kMaxCodePoint1 )
	{
		buf[1] = '\0';
		buf[0] = static_cast<char>(code_point);
	}
	else if( code_point <= kMaxCodePoint2 )
	{
		buf[2] = '\0';
		buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[0] = static_cast<char>(0xC0 | code_point);
	}
	else if( code_point <= kMaxCodePoint3 )
	{
		buf[3] = '\0';
		buf[2] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[0] = static_cast<char>(0xE0 | code_point);
	}
	else if( code_point <= kMaxCodePoint4 )
	{
		buf[4] = '\0';
		buf[3] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[2] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
		buf[0] = static_cast<char>(0xF0 | code_point);
	}
	else
	{
		sprintf(buf, "(Invalid UTF16 0x%X)", code_point);
	}
	return buf;
}
/**
 * @brief	ワイド文字列からUTF8へ変換
 * @param [in]	str	= 入力
 * @param [in]	num = 入力バッファサイズ
 * @return	UTF8 文字列
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_ WideStringToUTF8(const wchar_t* str, int num)
{
	if( num == -1 )
		num = static_cast<int>(wcslen(str));
	iuStringStream::type ss;
	for(int i=0; i < num; ++i )
	{
		UInt32 code_point;
		if( str[i] == L'\0' ) 
		{
			break;
		}
		else if( i + 1 < num && IsUtf16SurrogatePair(str[i], str[i+1]) )
		{
			code_point = CreateCodePointFromUtf16SurrogatePair(str[i], str[i+1]);
			++i;
		}
		else
		{
			code_point = static_cast<UInt32>(str[i]);
		}
		char buf[32];
		ss << CodePointToUtf8(code_point, buf);
	}
	return ss.str();
}

/**
 * @brief	マルチバイト文字からUTF8へ変換
 * @param [in]	str	= 入力
 * @param [in]	num = 入力バッファサイズ
 * @return	UTF8 文字列
*/
inline ::std::string IUTEST_ATTRIBUTE_UNUSED_ MultiByteStringToUTF8(const char* src, int num)
{
#if !defined(IUTEST_OS_WINDOWS_MOBILE)
	if( num == -1 )
		num = static_cast<int>(strlen(src));
	std::string str;
	const char* p = src;
	//char* locale = setlocale(LC_CTYPE, "JPN");
	for(const char* end = src + num; p < end; )
	{
		wchar_t wc=0;
		int len = iu_mbtowc(&wc, p, MB_CUR_MAX);
		if( len > 1 )
		{
			str += WideStringToUTF8(&wc, 1);
			p += len;
		}
		else
		{
			str += *p;
			++p;
		}
	}
	//setlocale(LC_CTYPE, locale);
	return str;
#else
	return src;
#endif
}

inline ::std::string ShowWideCString(const wchar_t* wide_c_str)
{
	if( wide_c_str == NULL ) return "(null)";
#if IUTEST_MBS_CODE == IUTEST_MBS_CODE_UTF8
	return WideStringToUTF8(wide_c_str);
#elif defined(IUTEST_OS_WINDOWS) && IUTEST_MBS_CODE == IUTEST_MBS_CODE_WINDOWS31J
	return win::WideStringToMultiByteString(wide_c_str);
#else
	::std::string str;
	const size_t length = wcslen(wide_c_str) * MB_CUR_MAX + 1;
	char* mbs = new char [length];
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
	if( wcstombs(mbs, wide_c_str, length) == (size_t)-1 )
	{
		delete [] mbs;
		return "(convert error)";
	}
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
	str = mbs;
	delete [] mbs;
	return str;
#endif
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}	// end of namespace detail
}	// end of namespace iutest

#endif
