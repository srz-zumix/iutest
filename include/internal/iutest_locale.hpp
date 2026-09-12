//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_locale.hpp
 * @brief       iris unit test locale utilities
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020-2025, Takazumi Shirayanagi\n
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
    int m_category;
    ::std::string m_prev_locale;
    bool m_valid;
public:
    ScopedLocale(int category, const char* locale)
        : m_category(category)
        , m_prev_locale(GetCurrentLocale(category))
        , m_valid(false)
    {
        if( !SetLocale(category, locale) )
        {
            IUTEST_LOG_(WARNING) << "Failed setlocale: " << category << ", " << locale;
        }
    }
    ~ScopedLocale()
    {
        if( m_valid )
        {
            // IUTEST_LOG_(INFO) << "Restore locale: " << m_category << ", " << m_prev_locale;
            if( setlocale(m_category, m_prev_locale.c_str()) == NULL )
            {
                IUTEST_LOG_(ERROR) << "Failed restore locale: " << m_category << ", " << m_prev_locale;
            }
        }
    }
    operator bool() const { return m_valid; }
    ::std::string GetPrevLocale() const { return m_prev_locale; }
private:
    static ::std::string GetCurrentLocale(int category)
    {
        const char* locale = setlocale(category, IUTEST_NULLPTR);
        return locale == NULL ? ::std::string() : ::std::string(locale);
    }
    bool SetLocale(int category, const char* locale)
    {
        m_valid = (setlocale(category, locale) != NULL);
        return m_valid;
    }
protected:
    ScopedLocale(int category, const char* locale, bool)
        : m_category(category)
        , m_prev_locale(GetCurrentLocale(category))
        , m_valid(false)
    {
        SetLocale(category, locale);
    }

    friend class ScopedEncoding;
};

class ScopedEncoding : public ScopedLocale
{
public:
    ScopedEncoding(int category, const char* encoding)
    : ScopedLocale(category, GetWithEncoding(category, encoding).c_str())
    {
    }
    ~ScopedEncoding()
    {
    }

    static ::std::string GetWithEncoding(int category, const char* encoding)
    {
#if defined(_MSC_VER) && defined(IUTEST_OS_WINDOWS_MINGW)
        IUTEST_UNUSED_VAR(category);
        ::std::string loc = ".";
        loc += encoding;
        return loc;
#else
        {
            ::std::string locale = GetLocaleWithEncoding_(category, encoding);
            if( !locale.empty() )
            {
                return locale;
            }
        }
        const char* list[] = { "", "C", "en_US" };
        for( size_t i=0; i < IUTEST_PP_COUNTOF(list); ++i )
        {
            ScopedLocale loc(category, list[i], true);
            if( !loc )
            {
                // IUTEST_LOG_(INFO) << "Failed setlocale: " << category << ", " << list[i];
                continue;
            }
            ::std::string locale = GetLocaleWithEncoding_(category, encoding);
            if( !locale.empty() )
            {
                return locale;
            }
        }
        return encoding;
#endif
    }

private:
#if !defined(_MSC_VER) || !defined(IUTEST_OS_WINDOWS_MINGW)
    static ::std::string GetLocaleWithEncoding_(int category, const char* encoding)
    {
        const char* curr = setlocale(category, IUTEST_NULLPTR);
        if( curr != IUTEST_NULLPTR )
        {
            const char* p = strchr(curr, '.');
            ::std::string locale = p == IUTEST_NULLPTR ? curr : ::std::string(curr, p);
            locale += ".";
            locale += encoding;
            ScopedLocale loc(category, locale.c_str(), true);
            if( loc )
            {
                return locale;
            }
            // IUTEST_LOG_(INFO) << "Failed setlocale: " << category << ", " << locale;
        }
        return "";
    }
#endif
};

class ScopedUTF8 : public ScopedEncoding
{
public:
    explicit ScopedUTF8(int category)
    : ScopedEncoding(category, "UTF-8")
    {
    }
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_LOCALE_HPP_5C778CDA_7432_4554_B06F_B74AE65CF59C_
