//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_locale.hpp
 * @brief       iris unit test locale utilities
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_LOCALE_HPP_5C778CDA_7432_4554_B06F_B74AE65CF59C_
#define INCG_IRIS_IUTEST_LOCALE_HPP_5C778CDA_7432_4554_B06F_B74AE65CF59C_

//======================================================================
// include
#include "iutest_stdlib.hpp"
#include <locale>

namespace iutest {
namespace detail
{

class ScopedLocale
{
    int m_Category;
    const char* m_pLocale;
public:
    ScopedLocale(int category, const char* locale)
        : m_Category(category)
        , m_pLocale(setlocale(category, locale))
    {
    }
    ~ScopedLocale()
    {
        if( m_pLocale != NULL )
        {
            setlocale(m_Category, m_pLocale);
        }
    }
    operator bool() const { return m_pLocale != NULL; }
};

class IuLocalUtil
{
private:
    static ::std::string GetLocaleWithEncoding_(int category, const char* encoding)
    {
        const char* curr = setlocale(category, NULL);
        if( curr != NULL )
        {
            const char* p = strchr(curr, '.');
            ::std::string locale = p == NULL ? curr : ::std::string(curr, p + 1);
            locale += encoding;
            ScopedLocale loc(category, locale.c_str());
            if( loc )
            {
                return locale;
            }
        }
        return "";
    }
public:
    static ::std::string GetWithEncoding(int category, const char* encoding)
    {
        {
            ::std::string locale = GetLocaleWithEncoding_(category, encoding);
            if( !locale.empty() )
            {
                return locale;
            }
        }
        const char* list[] = { "", "en_US" };
        for( size_t i=0; i < IUTEST_PP_COUNTOF(list); ++i )
        {
            ScopedLocale loc(category, list[i]);
            ::std::string locale = GetLocaleWithEncoding_(category, encoding);
            if( !locale.empty() )
            {
                return locale;
            }
        }
        return "";
    }
};

class ScopedEncoding : public ScopedLocale
{
public:
    ScopedEncoding(int category, const char* encoding)
    : ScopedLocale(category, IuLocalUtil::GetWithEncoding(category, encoding).c_str())
    {
    }
    ~ScopedEncoding()
    {
    }
};


}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_LOCALE_HPP_5C778CDA_7432_4554_B06F_B74AE65CF59C_
