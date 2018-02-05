//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_regex.ipp
 * @brief       regex
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_REGEX_IPP_1575CB44_189A_4248_B305_DB4882E3BFC2_
#define INCG_IRIS_IUTEST_REGEX_IPP_1575CB44_189A_4248_B305_DB4882E3BFC2_

//======================================================================
// include
#include "../internal/iutest_regex.hpp"

namespace iutest {
namespace detail
{

IUTEST_IPP_INLINE bool iuFilterRegex::match_impl(const char* begin, const char* end, const char* src)
{
    const char* tp = begin;
    if( *tp == '\0' )
    {
        return false;
    }
    while( tp != end )
    {
        if( *tp == '*' )    // 任意の文字列にマッチ
        {
            ++tp;
            while( *tp == '*' )
            {
                ++tp;
            }
            if( tp == end )
            {
                return true;
            }

            {
                const char nc = *tp;
                if( nc == '\0' )
                {
                    return true;
                }

                for( ; ; )
                {
                    while( *src != nc )
                    {
                        ++src;
                        if( *src == '\0' )
                        {
                            return false;
                        }
                    }
                    // つづきを検査
                    if( match_impl(tp + 1, end, ++src) )
                    {
                        return true;
                    }
                }
            }
        }
        else if( *tp == '?' )   // 任意の一文字にマッチ
        {
            if( *src == '\0' )
            {
                return false;
            }
        }
        else    // 指定文字にマッチ
        {
            if( *tp != *src )
            {
                return false;
            }
        }
        ++tp;
        ++src;
    }
    if( *src != '\0' )
    {
        return false;
    }
    return true;
}

IUTEST_IPP_INLINE bool iuFilterRegex::match_impl_list(const char* begin, const char* end, const char* src)
{
    const char* tp = begin;
    const char* end2 = tp;
    while( end2 != end )
    {
        ++end2;
        while( *end2 != ':' && end2 != end )
        {
            ++end2;
        }
        if( match_impl(tp, end2, src) )
        {
            return true;
        }

        tp = end2;
        if( *tp == ':' )
        {
            ++tp;
        }
    }
    return false;
}

IUTEST_IPP_INLINE bool iuFilterRegex::match(const char* regex, const char* src)
{
    const char* tp = regex;
    const char* end = tp;
    while( *end != '\0' && *end != '-' )
    {
        ++end;
    }

    if( *end == '-' )
    {
        if( tp != end && !match_impl_list(tp, end, src) )
        {
            return false;
        }
        tp = end + 1;
        while( *end != '\0' )
        {
            ++end;
        }
        if( match_impl_list(tp, end, src) )
        {
            return false;
        }
        return true;
    }
    return match_impl_list(tp, end, src);
}

#if IUTEST_HAS_CXX_HDR_REGEX

IUTEST_IPP_INLINE bool iuRegex::FullMatch(const char* str) const
{
    return (str != NULL) ? ::std::regex_match(str, m_re) : false;
}

IUTEST_IPP_INLINE bool iuRegex::PartialMatch(const char* str) const
{
    return (str != NULL) ? ::std::regex_search(str, m_re) : false;
}

IUTEST_IPP_INLINE void iuRegex::Init(const char* str)
{
    m_re.assign(str);
    m_pattern = str;
}

#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_REGEX_IPP_1575CB44_189A_4248_B305_DB4882E3BFC2_
