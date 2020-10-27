//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_regex.hpp
 * @brief       regex
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_REGEX_HPP_1575CB44_189A_4248_B305_DB4882E3BFC2_
#define INCG_IRIS_IUTEST_REGEX_HPP_1575CB44_189A_4248_B305_DB4882E3BFC2_

//======================================================================
// include
#if IUTEST_HAS_CXX_HDR_REGEX
#  include <regex>
#endif

namespace iutest {
namespace detail
{

/**
 * @brief   filter regex クラス
*/
class iuFilterRegex
{
    static bool match_impl(const char* begin, const char* end, const char* src);
    static bool match_impl_list(const char* begin, const char* end, const char* src);
public:
    static bool match(const char* regex, const char* src);
};

#if IUTEST_HAS_CXX_HDR_REGEX

/**
* @brief    regex クラス
*/
class iuRegex
{
public:
    iuRegex(const char* pattern) { Init(pattern); }                     // NOLINT
    iuRegex(const ::std::string& pattern) { Init(pattern.c_str()); }    // NOLINT
    iuRegex(const iuRegex & rhs) : m_re(rhs.m_re), m_pattern(rhs.m_pattern) {}
public:
    bool FullMatch(const char* str) const;
    bool PartialMatch(const char* str) const;

    const char* pattern() const { return m_pattern.c_str(); }

private:
    void Init(const char* pattern);

private:
    ::std::regex m_re;
    ::std::string m_pattern;

    IUTEST_PP_DISALLOW_ASSIGN(iuRegex);
};

#endif

}   // end of namespace detail

namespace internal
{

#if IUTEST_HAS_CXX_HDR_REGEX

class RE : public detail::iuRegex
{
public:
    RE(const char* pattern) : detail::iuRegex(pattern) {}           // NOLINT
    RE(const ::std::string& pattern) : detail::iuRegex(pattern) {}  // NOLINT
public:
    static bool FullMatch(const ::std::string& str, const RE& re)
    {
        return FullMatch(str.c_str(), re);
    }
    static bool PartialMatch(const ::std::string& str, const RE& re)
    {
        return PartialMatch(str.c_str(), re);
    }
    static bool FullMatch(const char* str, const RE& re)
    {
        const detail::iuRegex& r = re;
        return r.FullMatch(str);
    }
    static bool PartialMatch(const char* str, const RE& re)
    {
        const detail::iuRegex& r = re;
        return r.PartialMatch(str);
    }
};

#endif

}   // end of namespace internal
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_regex.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_REGEX_HPP_1575CB44_189A_4248_B305_DB4882E3BFC2_
