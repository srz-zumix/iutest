//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_regex.hpp
 * @brief		iris unit test 用 regex ファイル
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
#ifndef INCG_IRIS_iutest_regex_HPP_1575CB44_189A_4248_B305_DB4882E3BFC2_
#define INCG_IRIS_iutest_regex_HPP_1575CB44_189A_4248_B305_DB4882E3BFC2_

//======================================================================
// include

namespace iutest {
namespace detail
{

/**
 * @brief	regex クラス
*/
class iuRegex
{
	static bool	match_impl(const char* begin, const char* end, const char* src);
public:
	static bool	match(const char* regex, const char* src);
};

inline bool	iuRegex::match(const char* regex, const char* src)
{
	const char* tp = regex;

	while( *tp != '\0' )
	{
		const char* end = tp;
		while( *end != '\0' && *end != ':' ) ++end;

		{
			bool match = true;
			const char* end2 = tp;
			while( end2 != end )
			{
				++end2;
				while( *end2 != '-' && end2 != end ) ++end2;
				if( *tp == '-' )
				{
					if( match_impl(tp+1, end2, src) ) match = false;
				}
				else
				{
					if( !match_impl(tp, end2, src) ) match = false;
				}
				tp = end2;
			}
			if( match ) return true;
		}
		tp = end;
	}
	return false;
}

inline bool	iuRegex::match_impl(const char* begin, const char* end, const char* src)
{
	const char* tp = begin;
	if( *tp == '\0' ) return false;
	while( tp != end )
	{
		if( *tp == '*' )	// 任意の文字列にマッチ
		{
			++tp;
			while( *tp == '*' ) ++tp;
			if( tp == end ) return true;

			{
				const char nc = *tp;
				if( nc == '\0' ) return true;

				for( ; ; )
				{
					while( *src != nc )
					{
						++src;
						if( *src == '\0' ) return false;
					}
					// つづきを検査
					if( match_impl(tp+1, end, ++src) ) return true;
				}
			}
		}
		else if( *tp == '?' )	// 任意の一文字にマッチ
		{
			if( *src == '\0' ) return false;
		}
		else	// 指定文字にマッチ
		{
			if( *tp != *src ) return false;
		}
		++tp;
		++src;
	}
	if( *src != '\0' ) return false;
	return true;
}

}	// end of namespace detail
}	// end of namespace iutest

#endif
