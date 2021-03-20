//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_matcher.hpp
 * @brief       iris unit test matcher 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_
#define INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_

#if IUTEST_HAS_MATCHERS

//======================================================================
// define
/**
 * @private
 * @{
*/
#define IUTEST_TEST_THAT(actual, matcher, on_failure)                   \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                      \
    if( ::iutest::AssertionResult iutest_ar = matcher(actual) ) {       \
    } else                                                              \
        on_failure(::iutest::detail::MatcherAssertionFailureMessage(    \
            ::iutest::PrintToString(actual).c_str(), #matcher, iutest_ar))

/**
 * @}
*/

namespace iutest {
namespace detail
{

//======================================================================
// function
/**
 * @brief   Matcher Assertion Failure Message
*/
inline ::std::string MatcherAssertionFailureMessage(const char* actual, const char* matcher_str
                                                    , const AssertionResult& ar)
{
    iu_global_format_stringstream strm;
    strm << "error: Expected: " << matcher_str
        << "\n  Actual: " << actual
        << "\nWhich is: " << ar.message();
    return strm.str();
}

//======================================================================
// class

IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_BEGIN()

/**
 * @brief   matcher interface
*/
class IMatcher
{
    IMatcher& operator=(const IMatcher&);
public:
    template<typename T>
    struct is_matcher : public iutest_type_traits::is_base_of<IMatcher, T> {};
public:
    IMatcher() {}
    IMatcher(const IMatcher&) {}
    virtual ~IMatcher() {}
    virtual ::std::string WhichIs() const = 0;
};

#if !defined(IUTEST_NO_SFINAE)
template<typename T>
inline typename detail::enable_if_t< IMatcher::is_matcher<T>, iu_ostream>::type& operator << (iu_ostream& os, const T& m)
{
    return os << m.WhichIs();
}
#else
inline iu_ostream& operator << (iu_ostream& os, const IMatcher& m)
{
    return os << m.WhichIs();
}
#endif

/**
 * @private
 * @{
 */

#define IIUT_DECL_COMPARE_MATCHER(name, op)  \
    template<typename T>                                                        \
    class IUTEST_PP_CAT(name, Matcher) IUTEST_CXX_FINAL : public IMatcher {     \
    public: explicit IUTEST_PP_CAT(name, Matcher)(const T& v) : m_expected(v) {}\
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                         \
        iu_global_format_stringstream strm;                                     \
        strm << #name ": " << m_expected; return strm.str();                    \
    }                                                                           \
    template<typename U>AssertionResult operator ()(const U& actual) const {    \
        if IUTEST_COND_LIKELY( actual op m_expected ) return AssertionSuccess();\
        return AssertionFailure() << WhichIs();                                 \
    }                                                                           \
    private: const T& m_expected;                                               \
    }

#define IIUT_DECL_COMPARE_MATCHER2(name, op) \
    class IUTEST_PP_CAT(Twofold, IUTEST_PP_CAT(name, Matcher)) IUTEST_CXX_FINAL : public IMatcher{  \
    public: ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return #name; }                     \
    template<typename T, typename U>AssertionResult operator ()                                     \
        (const T& actual, const U& expected) const {                                                \
        if IUTEST_COND_LIKELY( actual op expected ) return AssertionSuccess();                      \
        return AssertionFailure() << WhichIs() << ": " << actual << " vs " << expected;             \
    }                                                                                               \
    }


IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()

IIUT_DECL_COMPARE_MATCHER(Ne, !=);
IIUT_DECL_COMPARE_MATCHER(Le, <=);
IIUT_DECL_COMPARE_MATCHER(Lt, < );
IIUT_DECL_COMPARE_MATCHER(Ge, >=);
IIUT_DECL_COMPARE_MATCHER(Gt, > );

IIUT_DECL_COMPARE_MATCHER2(Eq, ==);
IIUT_DECL_COMPARE_MATCHER2(Ne, !=);
IIUT_DECL_COMPARE_MATCHER2(Le, <=);
IIUT_DECL_COMPARE_MATCHER2(Lt, < );
IIUT_DECL_COMPARE_MATCHER2(Ge, >=);
IIUT_DECL_COMPARE_MATCHER2(Gt, > );

IUTEST_PRAGMA_WARN_POP()

#undef IIUT_DECL_COMPARE_MATCHER
#undef IIUT_DECL_COMPARE_MATCHER2

#define IIUT_DECL_STR_COMPARE_MATCHER(name)  \
    template<typename T>                                                        \
    class IUTEST_PP_CAT(name, Matcher) IUTEST_CXX_FINAL : public IMatcher {     \
    public: IUTEST_PP_CAT(name, Matcher)(const T& value) : m_expected(value) {} \
    template<typename U>AssertionResult operator ()(const U& actual) const {    \
        if IUTEST_COND_LIKELY( internal::IUTEST_PP_CAT(name, Helper)::Compare(  \
            actual, m_expected) ) { return AssertionSuccess(); }                \
        return AssertionFailure() << WhichIs();                                 \
    }                                                                           \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                         \
        iu_global_format_stringstream strm; strm << #name ": " << m_expected;   \
        return strm.str();                                                      \
    }                                                                           \
    private:                                                                    \
    const T& m_expected;                                                        \
    }

IIUT_DECL_STR_COMPARE_MATCHER(StrEq);
IIUT_DECL_STR_COMPARE_MATCHER(StrNe);
IIUT_DECL_STR_COMPARE_MATCHER(StrCaseEq);
IIUT_DECL_STR_COMPARE_MATCHER(StrCaseNe);

#undef IIUT_DECL_COMPARE_MATCHER

/**
 * @}
*/

/**
 * @brief   IsNull matcher
*/
class IsNullMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( actual == IUTEST_NULLPTR )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "Is Null";
    }
};

/**
 * @brief   NotNull matcher
*/
class NotNullMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( actual != IUTEST_NULLPTR )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "Not Null";
    }
};

/**
 * @brief   Floating point Eq matcher
*/
template<typename T>
class FloatingPointEqMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit FloatingPointEqMatcher(const T& value) : m_expected(value) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        const floating_point<T> f2(actual);
        if IUTEST_COND_LIKELY( m_expected.AlmostEquals(f2) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Eq: " << PrintToString(m_expected);
        return strm.str();
    }
private:
    floating_point<T> m_expected;
};

/**
 * @brief   Floating point Eq matcher (NanSensitive)
*/
template<typename T>
class NanSensitiveFloatingPointEqMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit NanSensitiveFloatingPointEqMatcher(const T& value) : m_expected(value) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        const floating_point<T> f2(actual);
        if IUTEST_COND_LIKELY( m_expected.NanSensitiveAlmostEquals(f2) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "NanSensitive Eq: " << PrintToString(m_expected);
        return strm.str();
    }
private:
    floating_point<T> m_expected;
};

/**
 * @brief   Floating point Near matcher
*/
template<typename T>
class FloatingPointNearMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit FloatingPointNearMatcher(const T& value, const T& abs_error)
        : m_expected(value), m_max_abs_error(abs_error) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        const floating_point<T> a(actual);
        if IUTEST_COND_LIKELY( m_expected.AlmostNear(a, m_max_abs_error) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Near: " << PrintToString(m_expected) << "(abs error <= " << m_max_abs_error << ")";
        return strm.str();
    }
private:
    floating_point<T> m_expected;
    T m_max_abs_error;
};

/**
 * @brief   Floating point Near matcher (NanSensitive)
*/
template<typename T>
class NanSensitiveFloatingPointNearMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit NanSensitiveFloatingPointNearMatcher(const T& value, const T& abs_error)
        : m_expected(value), m_max_abs_error(abs_error) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        const floating_point<T> a(actual);
        if IUTEST_COND_LIKELY( m_expected.NanSensitiveAlmostNear(a, m_max_abs_error) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "NanSensitive Near: " << PrintToString(m_expected) << "(abs error <= " << m_max_abs_error << ")";
        return strm.str();
    }
private:
    floating_point<T> m_expected;
    T m_max_abs_error;
};

/**
 * @brief   StartsWith matcher
*/
template<typename T>
class StartsWithMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit StartsWithMatcher(T str) : m_expected(str) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( StartsWith(actual, m_expected) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "StartsWith: " << m_expected;
        return strm.str();
    }
private:
    static bool StartsWith(const char* actual, const char* start)
    {
        return strstr(actual, start) == actual;
    }
    static bool StartsWith(const ::std::string& actual, const char* start)
    {
        const char* p = actual.c_str();
        return StartsWith(p, start);
    }
    static bool StartsWith(const char* actual, const ::std::string& start)
    {
        const char* p = start.c_str();
        return StartsWith(actual, p);
    }
    static bool StartsWith(const ::std::string& actual, const ::std::string& start)
    {
        const char* p = start.c_str();
        return StartsWith(actual, p);
    }
private:
    T m_expected;
};

/**
 * @brief   Has substr matcher
*/
template<typename T>
class HasSubstrMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit HasSubstrMatcher(T expected) : m_expected(expected) {}
public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( HasSubstr(actual, m_expected) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "HasSubstr: " << m_expected;
        return strm.str();
    }
private:
    static bool HasSubstr(const char* actual, const char* expected)
    {
        return strstr(actual, expected) != NULL;
    }
    static bool HasSubstr(const ::std::string& actual, const char* expected)
    {
        const char* p = actual.c_str();
        return HasSubstr(p, expected);
    }
    static bool HasSubstr(const char* actual, const ::std::string& expected)
    {
        const char* p = expected.c_str();
        return HasSubstr(actual, p);
    }
    static bool HasSubstr(const ::std::string& actual, const ::std::string& expected)
    {
        const char* p = expected.c_str();
        return HasSubstr(actual, p);
    }

private:
    T m_expected;
};

/**
 * @brief   EndsWith matcher
*/
template<typename T>
class EndsWithMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit EndsWithMatcher(T str) : m_expected(str) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( EndsWith(actual, m_expected) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "EndsWith: " << m_expected;
        return strm.str();
    }
private:
    static bool EndsWith(const char* actual, const char* end)
    {
        const size_t len = strlen(end);
        const size_t actual_len = strlen(actual);
        if( len > actual_len )
        {
            return false;
        }
        const char* p = actual + actual_len - 1;
        const char* q = end + len - 1;
        for( size_t i=0; i < len; ++i, --p, --q )
        {
            if( *p != *q )
            {
                return false;
            }
        }
        return true;
    }
    static bool EndsWith(const ::std::string& actual, const char* end)
    {
        const char* p = actual.c_str();
        return EndsWith(p, end);
    }
    static bool EndsWith(const char* actual, const ::std::string& end)
    {
        const char* p = end.c_str();
        return EndsWith(actual, p);
    }
    static bool EndsWith(const ::std::string& actual, const ::std::string& end)
    {
        const char* p = end.c_str();
        return EndsWith(actual, p);
    }
private:
    T m_expected;
};

/**
 * @brief   Equals matcher
*/
template<typename T>
class EqMatcher : public IMatcher
{
public:
    explicit EqMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( Equals(actual, m_expected) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Eq: " << PrintToString(m_expected);
        return strm.str();
    }
private:
    template<typename A, typename B>
    static bool Equals(const A& actual, const B& expected)
    {
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()
        return actual == expected;
IUTEST_PRAGMA_WARN_POP()
    }
    static bool Equals(const char* actual, const char* expected)
    {
        return strcmp(actual, expected) == 0;
    }
    static bool Equals(const ::std::string& actual, const char* expected)
    {
        const char* p = actual.c_str();
        return Equals(p, expected);
    }
    static bool Equals(const ::std::string& actual, const ::std::string& expected)
    {
        const char* p = expected.c_str();
        return Equals(actual, p);
    }
private:
    const T& m_expected;
};

/**
 * @brief   TypedEq matcher
*/
template<typename T>
class TypedEqMatcher IUTEST_CXX_FINAL : public EqMatcher<T>
{
public:
    explicit TypedEqMatcher(T expected) : EqMatcher<T>(m_expected), m_expected(expected) {}
public:
    AssertionResult operator ()(const T& actual)
    {
        return EqMatcher<T>::operator ()(actual);
    }
    template<typename U>
    AssertionResult operator ()(const U&) const;

private:
    T m_expected;
};

/**
 * @brief   Cast to matcher
*/
#if !defined(IUTEST_NO_SFINAE)

template<typename T>
T& CastToMatcher(T& matcher
    , typename detail::enable_if_t< IMatcher::is_matcher<T> >::type*& = detail::enabler::value)
{
    return matcher;
}
/** @overload */
template<typename T>
EqMatcher<T> CastToMatcher(const T& value
    , typename detail::disable_if_t< IMatcher::is_matcher<T> >::type*& = detail::enabler::value)
{
    return EqMatcher<T>(value);
}

#else

template<typename T>
T& CastToMatcher(T& matcher)
{
    return matcher;
}

#endif


/**
 * @brief   Contains matcher
*/
template<typename T>
class ContainsMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit ContainsMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        if IUTEST_COND_LIKELY( Contains(begin(actual), end(actual)) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Contains: " << m_expected;
        return strm.str();
    }
private:
    template<typename Ite>
    bool Contains(Ite begin, Ite end)
    {
        for( Ite it = begin; it != end; ++it )
        {
            if( CastToMatcher(m_expected)(*it) )
            {
                return true;
            }
        }
        return false;
    }

private:
    T m_expected;
};

#if IUTEST_HAS_MATCHER_EACH

/**
 * @brief   Each matcher
*/
template<typename T>
class EachMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit EachMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        if IUTEST_COND_LIKELY( Each(begin(actual), end(actual)) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Each: " << m_expected;
        return strm.str();
    }
private:
    template<typename Ite>
    bool Each(Ite begin, Ite end)
    {
        for( Ite it = begin; it != end; ++it )
        {
            if( !CastToMatcher(m_expected)(*it) )
            {
                return false;
            }
        }
        return true;
    }

private:
    T m_expected;
};

#endif

/**
 * @brief   ContainerEq matcher
*/
template<typename T>
class ContainerEqMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit ContainerEqMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        if IUTEST_COND_LIKELY( Check(begin(m_expected), end(m_expected)
            , begin(actual), end(actual)) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "ContainerEq: " << PrintToString(m_expected);
        strm << " (" << m_whichIs << ")";
        return strm.str();
    }
private:
    template<typename Ite1, typename Ite2>
    bool Check(Ite1 b1, Ite1 e1, Ite2 b2, Ite2 e2)
    {
        size_t elem=0;
        bool result = true;
        Message ar;
        for( elem=0; b1 != e1 && b2 != e2; ++b1, ++b2, ++elem )
        {
            if( !internal::backward::EqHelper<false>::Compare("", "", *b1, *b2) )
            {
                result = false;
                ar << "\nMismatch in a position " << elem << ": "
                    << ::iutest::internal::FormatForComparisonFailureMessage(*b1, *b2)
                    << " vs " << ::iutest::internal::FormatForComparisonFailureMessage(*b2, *b1);
            }
        }
        if( b1 != e1 || b2 != e2 )
        {
            const size_t elem1 = elem + ::std::distance(b1, e1);
            const size_t elem2 = elem + ::std::distance(b2, e2);
            result = false;
            ar << "\nMismatch element : " << elem1 << " vs " << elem2;
        }
        m_whichIs = ar.GetString();
        return result;
    }

private:
    const T& m_expected;
    ::std::string m_whichIs;
};


#if IUTEST_HAS_MATCHER_POINTWISE

/**
 * @brief   Pointwise matcher
*/
template<typename M, typename T>
class PointwiseMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    PointwiseMatcher(const M& matcher, const T& expected)
        : m_matcher(matcher), m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        if IUTEST_COND_LIKELY( Check(begin(m_expected), end(m_expected)
            , begin(actual), end(actual)) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Pointwise: " << m_matcher << ": " << PrintToString(m_expected);
        strm << " (" << m_whichIs << ")";
        return strm.str();
    }
private:
    template<typename Ite1, typename Ite2>
    bool Check(Ite1 b1, Ite1 e1, Ite2 b2, Ite2 e2)
    {
        size_t elem=0;
        bool result = true;
        Message ar;
        for( elem=0; b1 != e1 && b2 != e2; ++b1, ++b2, ++elem )
        {
            const AssertionResult r = m_matcher(*b2, *b1);
            if( r.failed() )
            {
                result = false;
                ar << "\nMismatch in a position " << elem << ": " << r.message();
            }
        }
        if( b1 != e1 || b2 != e2 )
        {
            const size_t elem1 = elem + ::std::distance(b1, e1);
            const size_t elem2 = elem + ::std::distance(b2, e2);
            result = false;
            ar << "\nMismatch element : " << elem1 << " vs " << elem2;
        }
        m_whichIs = ar.GetString();
        return result;
    }

private:
    M m_matcher;
    const T& m_expected;
    ::std::string m_whichIs;
};

#endif

#if IUTEST_HAS_MATCHER_OPTIONAL

/**
 * @brief   Optional matcher
*/
template<typename T>
class OptionalMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit OptionalMatcher(const T& expected)
        : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

private:
    template<typename U>
    bool Check(const U& actual)
    {
        bool result = true;
        Message ar;
        if( !actual )
        {
            result = false;
            ar << "which is not engaged";
        }
        else if( !CastToMatcher(m_expected)(*actual) )
        {
            result = false;
            ar << actual;
        }
        m_whichIs = ar.GetString();
        return result;
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Optional: " << PrintToString(m_expected);
        strm << " (" << m_whichIs << ")";
        return strm.str();
    }
private:
    const T& m_expected;
    ::std::string m_whichIs;
};

#endif


/**
 * @brief   IsEmpty matcher
*/
class IsEmptyMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( (actual).empty() )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "Is Empty";
    }
};


/**
 * @brief   SizeIs matcher
*/
template<typename T>
class SizeIsMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit SizeIsMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Size is: " << m_expected;
        return strm.str();
    }
private:
    template<typename Container>
    bool Check(const Container& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual.size()));
    }
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
    template<typename U, size_t SIZE>
    bool Check(const U(&)[SIZE])
    {
        return static_cast<bool>(CastToMatcher(m_expected)(SIZE));
    }
#endif

private:
    T m_expected;
};

/**
 * @brief   At matcher
*/
template<typename T>
class AtMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    AtMatcher(size_t index, const T& expected) : m_index(index), m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( CastToMatcher(m_expected)(actual[m_index]) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "At " << m_index << ": " << m_expected;
        return strm.str();
    }

private:
    size_t m_index;
    T m_expected;
};

/**
 * @brief   ElementsAreArray matcher
*/
template<typename T>
class ElementsAreArrayMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename It>
    ElementsAreArrayMatcher(It begin, It end, bool expected_elem_count=true)
        : m_expected_elem_count(expected_elem_count)
    {
        m_expected.insert(m_expected.end(), begin, end);
    }

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        return Check(begin(actual), end(actual));
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return WhichIs(PrintToString(m_expected));
    }
    ::std::string WhichIs(const ::std::string& msg) const
    {
        iu_global_format_stringstream strm;
        if( m_expected_elem_count )
        {
            strm << "ElementsAreArray: ";
        }
        else
        {
            strm << "ElementsAreArrayForward: ";
        }
        strm << msg;
        return strm.str();
    }
private:
    template<typename Ite>
    AssertionResult Check(Ite actual_begin, Ite actual_end)
    {
        const size_t actual_cnt = ::std::distance(actual_begin, actual_end);
        const size_t expected_cnt = m_expected.size();
        if IUTEST_COND_UNLIKELY( actual_cnt < expected_cnt )
        {
            iu_global_format_stringstream stream;
            stream << "actual argument[" << actual_cnt << "] is less than " << expected_cnt;
            return AssertionFailure() << WhichIs(stream.str());
        }
        if IUTEST_COND_UNLIKELY( m_expected_elem_count && actual_cnt > expected_cnt )
        {
            iu_global_format_stringstream stream;
            stream << "actual argument[" << actual_cnt << "] is greater than " << expected_cnt;
            return AssertionFailure() << WhichIs(stream.str());
        }

        Ite it_a=actual_begin;
        typename ::std::vector<T>::iterator it_e=m_expected.begin();
        for( int i=0; it_a != actual_end && it_e != m_expected.end(); ++it_e, ++it_a, ++i )
        {
            (void)i;
            if IUTEST_COND_UNLIKELY( *it_a != *it_e )
            {
                return AssertionFailure() << WhichIs();
            }
        }
        return AssertionSuccess();
    }

private:
    ::std::vector<T> m_expected;
    bool m_expected_elem_count;
};

#if IUTEST_HAS_MATCHER_ELEMENTSARE

/**
 * @brief   ElementsAre matcher base class
*/
class ElementsAreMatcherBase : public IMatcher
{
protected:
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        return Check<0, tuples::tuple_size<T>::value - 1>(begin(actual), end(actual), matchers);
    }
    template<int N, typename T>
    static ::std::string WhichIs(const T& matchers)
    {
        ::std::string str = "ElementsAre: {";
        str += WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
        str += "}";
        return str;
    }
private:
    template<int N, int LAST, typename Ite, typename M>
    static AssertionResult Check(Ite it, Ite end, M& matchers)
    {
        const size_t cnt = ::std::distance(it, end);
        if IUTEST_COND_UNLIKELY( cnt < LAST+1 )
        {
            return AssertionFailure() << "ElementsAre: argument[" << cnt << "] is less than " << LAST+1;
        }
        return CheckElem<N, LAST>(it, end, matchers);
    }

    template<int N, int LAST, typename Ite, typename M>
    static AssertionResult CheckElem(Ite it, Ite end, M& matchers
        , typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        for( int index=N; it != end; ++it, ++index )
        {
            AssertionResult ar = CastToMatcher(tuples::get<N>(matchers))(*it);
            if IUTEST_COND_UNLIKELY( !ar )
            {
                return AssertionFailure() << WhichIsElem<N>(matchers, index);
            }
        }
        return AssertionSuccess();
    }

    template<int N, int LAST, typename Ite, typename M>
    static AssertionResult CheckElem(Ite it, Ite end, M& matchers
        , typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        AssertionResult ar = CastToMatcher(tuples::get<N>(matchers))(*it);
        if IUTEST_COND_LIKELY( ar )
        {
            return CheckElem<N + 1, LAST>(++it, end, matchers);
        }
        return AssertionFailure() << WhichIsElem<N>(matchers, N);
    }

    template<int N, typename T>
    static ::std::string WhichIsElem(const T& matchers, int index)
    {
        iu_global_format_stringstream strm;
        strm << "ElementsAre(" << index << "): " << tuples::get<N>(matchers);
        return strm.str();
    }

    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers
        , typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return StreamableToString(tuples::get<N>(matchers));
    }
    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers
        , typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return StreamableToString(tuples::get<N>(matchers)) + ", " + WhichIs_<T, N + 1, LAST>(matchers);
    }
};

#if IUTEST_HAS_MATCHER_VARIADIC

/**
* @brief    ElementsAre matcher
*/
template<typename ...T>
class ElementsAreMatcher IUTEST_CXX_FINAL : public ElementsAreMatcherBase
{
public:
    explicit ElementsAreMatcher(T... t) : m_matchers(t...) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return ElementsAreMatcherBase::WhichIs<0>(m_matchers);
    }

private:
    tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class ElementsAreMatcher IUTEST_CXX_FINAL : public ElementsAreMatcherBase
{
public:
    ElementsAreMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return ElementsAreMatcherBase::WhichIs<0>(m_matchers);
    }
private:
    tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ELEMENTSARE_MATCHER(n)                                                \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                    \
    class IUTEST_PP_CAT(ElementsAreMatcher, n) IUTEST_CXX_FINAL : public ElementsAreMatcherBase {   \
    public: IUTEST_PP_CAT(ElementsAreMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m)) \
        : m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}                                    \
    template<typename U>AssertionResult operator ()(const U& actual) {                  \
        return Check(m_matchers, actual); }                                             \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                                 \
        return ElementsAreMatcherBase::WhichIs<0>(m_matchers); }                        \
    private:                                                                            \
    tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;                            \
    }

IIUT_DECL_ELEMENTSARE_MATCHER(1);
IIUT_DECL_ELEMENTSARE_MATCHER(2);
IIUT_DECL_ELEMENTSARE_MATCHER(3);
IIUT_DECL_ELEMENTSARE_MATCHER(4);
IIUT_DECL_ELEMENTSARE_MATCHER(5);
IIUT_DECL_ELEMENTSARE_MATCHER(6);
IIUT_DECL_ELEMENTSARE_MATCHER(7);
IIUT_DECL_ELEMENTSARE_MATCHER(8);
IIUT_DECL_ELEMENTSARE_MATCHER(9);
IIUT_DECL_ELEMENTSARE_MATCHER(10);

#undef IIUT_DECL_ELEMENTSARE_MATCHER

#endif

#endif

/**
 * @brief   Field matcher
*/
template<typename F, typename T>
class FieldMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    FieldMatcher(const F& field, const T& expected) : m_field(field), m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Field: " << m_expected;
        //strm << "Field: (" << detail::GetTypeNameProxy<F>::GetTypeName() << ") " << m_expected;
        return strm.str();
    }
private:
#if !defined(IUTEST_NO_SFINAE)
    template<typename U>
    bool Check(const U& actual
        , typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual.*m_field));
    }
    template<typename U>
    bool Check(const U& actual
        , typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual->*m_field));
    }
#else
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual->*m_field));
    }
#endif

private:
    const F& m_field;
    T m_expected;
};

/**
 * @brief   Property matcher
*/
template<typename F, typename T>
class PropertyMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    PropertyMatcher(const F& prop, const T& expected) : m_property(prop), m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Property: " << m_expected;
        //strm << "Property: (" << detail::GetTypeNameProxy<F>::GetTypeName() << ") " << m_expected;
        return strm.str();
    }
private:
#if !defined(IUTEST_NO_SFINAE)
    template<typename U>
    bool Check(const U& actual
        , typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return static_cast<bool>(CastToMatcher(m_expected)((actual.*m_property)()));
    }
    template<typename U>
    bool Check(const U& actual
        , typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return static_cast<bool>(CastToMatcher(m_expected)((actual->*m_property)()));
    }
#else
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)((actual->*m_property)()));
    }
#endif

private:
    const F& m_property;
    T m_expected;
};

/**
 * @brief   Key matcher
*/
template<typename T>
class KeyMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit KeyMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( CastToMatcher(m_expected)(actual.first) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Key: " << m_expected;
        return strm.str();
    }

private:
    const T& m_expected;
};

/**
 * @brief   Pair matcher
*/
template<typename T1, typename T2>
class PairMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    PairMatcher(const T1& m1, const T2& m2) : m_m1(m1), m_m2(m2) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_UNLIKELY( !CheckElem(actual.first, m_m1) )
        {
            return AssertionFailure() << WhichIs();
        }
        if IUTEST_COND_UNLIKELY( !CheckElem(actual.second, m_m2) )
        {
            return AssertionFailure() << WhichIs();
        }
        return AssertionSuccess();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Pair: (" << m_m1 << ", " << m_m2 << ")";
        return strm.str();
    }
private:
    template<typename T, typename U>
    bool CheckElem(const T& actual, U& matcher)
    {
        return static_cast<bool>(CastToMatcher(matcher)(actual));
    }

private:
    T1 m_m1;
    T2 m_m2;
};

/**
 * @brief   ResultOf matcher
*/
template<typename F, typename T>
class ResultOfMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    ResultOfMatcher(F& func, const T& expected) : m_func(func), m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Result of: " << m_expected;
        //strm << "Result of " << detail::GetTypeNameProxy<F>::GetTypeName() << "(): " << m_expected;
        return strm.str();
    }
private:
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)((*m_func)(actual)));
    }
private:
    F& m_func;
    T m_expected;
};

/**
 * @brief   Pointee matcher
*/
template<typename T>
class PointeeMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit PointeeMatcher(const T& expected) : m_expected(expected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( Check(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Points To: " << m_expected;
        return strm.str();
    }
private:
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(*actual));
    }
private:
    T m_expected;
};

/**
 * @brief   Not matcher
*/
template<typename T>
class NotMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit NotMatcher(const T& unexpected) : m_unexpected(unexpected) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        if IUTEST_COND_LIKELY( !CastToMatcher(m_unexpected)(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Not: (" << m_unexpected << ")";
        return strm.str();
    }

private:
    T m_unexpected;
};

/**
 * @brief   Any matcher
*/
template<typename T>
class AnyMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    AssertionResult operator ()(const T&) const
    {
        return AssertionSuccess();
    }
    template<typename U>
    AssertionResult operator ()(const U&) const;

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "A: " << detail::GetTypeNameProxy<T>::GetTypeName();
        return strm.str();
    }
};

/**
 * @brief   Anything matcher
*/
class AnythingMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    AnythingMatcher() {}
public:
    template<typename U>
    AssertionResult operator ()(const U&) const
    {
        return AssertionSuccess();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "_";
    }
};

#if IUTEST_HAS_MATCHER_REGEX

/**
 * @brief   Regex matcher
*/
class RegexMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    RegexMatcher(const detail::iuRegex& expected, bool full_match) : m_expected(expected), m_full_match(full_match) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( Regex(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        if( m_full_match )
        {
            strm << "MatchesRegex: " << m_expected.pattern();
        }
        else
        {
            strm << "ContainsRegex: " << m_expected.pattern();
        }
        return strm.str();
    }
private:
    bool Regex(const char* actual) const
    {
        return m_full_match ? m_expected.FullMatch(actual)
            : m_expected.PartialMatch(actual);
    }
    bool Regex(const ::std::string& actual) const
    {
        return m_full_match ? m_expected.FullMatch(actual.c_str())
            : m_expected.PartialMatch(actual.c_str());
    }

private:
    detail::iuRegex m_expected;
    bool m_full_match;
};

#endif

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

/**
 * @brief   AllOf matcher base class
*/
class AllOfMatcherBase : public IMatcher
{
protected:
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
    }
    template<int N, typename T>
    static ::std::string WhichIs(const T& matchers)
    {
        return WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
    }
private:
    template<typename T, typename U, int N, int LAST>
    static AssertionResult Check_(T& matchers, const U& actual, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        AssertionResult ar = tuples::get<N>(matchers)(actual);
        if IUTEST_COND_LIKELY( ar )
        {
            return ar;
        }
        return AssertionFailure() << WhichIs_<T, 0, N>(matchers);
    }
    template<typename T, typename U, int N, int LAST>
    static AssertionResult Check_(T& matchers, const U& actual, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        AssertionResult ar = tuples::get<N>(matchers)(actual);
        if IUTEST_COND_LIKELY( ar )
        {
            return Check_<T, U, N + 1, LAST>(matchers, actual);
        }
        return AssertionFailure() << WhichIs_<T, 0, N>(matchers);
    }

    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return tuples::get<N>(matchers).WhichIs();
    }
    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return tuples::get<N>(matchers).WhichIs() + " and " + WhichIs_<T, N + 1, LAST>(matchers);
    }
};

#if IUTEST_HAS_MATCHER_VARIADIC

/**
 * @brief   AllOf matcher
*/
template<typename ...T>
class AllOfMatcher IUTEST_CXX_FINAL : public AllOfMatcherBase
{
public:
    explicit AllOfMatcher(T... t) : m_matchers(t...) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AllOfMatcherBase::WhichIs<0>(m_matchers);
    }

private:
    tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class AllOfMatcher IUTEST_CXX_FINAL : public AllOfMatcherBase
{
public:
    AllOfMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AllOfMatcherBase::WhichIs<0>(m_matchers);
    }
private:
    tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ALLOF_MATCHER(n)                                                  \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                \
    class IUTEST_PP_CAT(AllOfMatcher, n) IUTEST_CXX_FINAL : public AllOfMatcherBase {   \
    public: IUTEST_PP_CAT(AllOfMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m))   \
        : m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}                                \
    template<typename U>AssertionResult operator ()(const U& actual) {              \
        return Check(m_matchers, actual); }                                         \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                             \
        return AllOfMatcherBase::WhichIs<0>(m_matchers); }                          \
    private:                                                                        \
    tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;                        \
    }

IIUT_DECL_ALLOF_MATCHER(2);
IIUT_DECL_ALLOF_MATCHER(3);
IIUT_DECL_ALLOF_MATCHER(4);
IIUT_DECL_ALLOF_MATCHER(5);
IIUT_DECL_ALLOF_MATCHER(6);
IIUT_DECL_ALLOF_MATCHER(7);
IIUT_DECL_ALLOF_MATCHER(8);
IIUT_DECL_ALLOF_MATCHER(9);
IIUT_DECL_ALLOF_MATCHER(10);

#undef IIUT_DECL_ALLOF_MATCHER

#endif

/**
 * @brief   AnyOf matcher base class
*/
class AnyOfMatcherBase : public IMatcher
{
protected:
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
    }
    template<int N, typename T>
    static ::std::string WhichIs(const T& matchers)
    {
        return WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
    }
private:
    template<typename T, typename U, int N, int LAST>
    static AssertionResult Check_(T& matchers, const U& actual, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        AssertionResult ar = tuples::get<N>(matchers)(actual);
        if IUTEST_COND_LIKELY( ar )
        {
            return ar;
        }
        return AssertionFailure() << WhichIs_<T, 0, N>(matchers);
    }
    template<typename T, typename U, int N, int LAST>
    static AssertionResult Check_(T& matchers, const U& actual, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        AssertionResult ar = tuples::get<N>(matchers)(actual);
        if IUTEST_COND_LIKELY( ar )
        {
            return ar;
        }
        return Check_<T, U, N + 1, LAST>(matchers, actual);
    }

    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers, typename detail::enable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return tuples::get<N>(matchers).WhichIs();
    }
    template<typename T, int N, int LAST>
    static ::std::string WhichIs_(const T& matchers, typename detail::disable_if<N == LAST, void>::type*& = detail::enabler::value)
    {
        return tuples::get<N>(matchers).WhichIs() + " or " + WhichIs_<T, N + 1, LAST>(matchers);
    }
};

#if IUTEST_HAS_MATCHER_VARIADIC

/**
 * @brief   AnyOf matcher
*/
template<typename ...T>
class AnyOfMatcher IUTEST_CXX_FINAL : public AnyOfMatcherBase
{
public:
    explicit AnyOfMatcher(T... t) : m_matchers(t...) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AnyOfMatcherBase::WhichIs<0>(m_matchers);
    }

private:
    tuples::tuple<T...> m_matchers;
};

#else

/*
template<typename T0, typename T1>
class AnyOfMatcher IUTEST_CXX_FINAL : public AnyOfMatcherBase
{
public:
    AnyOfMatcher(T0 m0, T1 m1) : m_matchers(m0, m1) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AnyOfMatcherBase::WhichIs<0>(m_matchers);
    }
private:
    tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_DECL_ANYOF_MATCHER(n)                                                  \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                \
    class IUTEST_PP_CAT(AnyOfMatcher, n) IUTEST_CXX_FINAL : public AnyOfMatcherBase {   \
    public: IUTEST_PP_CAT(AnyOfMatcher, n)(IUTEST_PP_ENUM_BINARY_PARAMS(n, T, m))   \
        : m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}                                \
    template<typename U>AssertionResult operator ()(const U& actual) {              \
        return Check(m_matchers, actual); }                                         \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                             \
        return AnyOfMatcherBase::WhichIs<0>(m_matchers); }                          \
    private:                                                                        \
    tuples::tuple< IUTEST_PP_ENUM_PARAMS(n, T) > m_matchers;                        \
    }

IIUT_DECL_ANYOF_MATCHER(2);
IIUT_DECL_ANYOF_MATCHER(3);
IIUT_DECL_ANYOF_MATCHER(4);
IIUT_DECL_ANYOF_MATCHER(5);
IIUT_DECL_ANYOF_MATCHER(6);
IIUT_DECL_ANYOF_MATCHER(7);
IIUT_DECL_ANYOF_MATCHER(8);
IIUT_DECL_ANYOF_MATCHER(9);
IIUT_DECL_ANYOF_MATCHER(10);

#undef IIUT_DECL_ANYOF_MATCHER

#endif

#endif

IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_END()

}   // end of namespace detail

/**
 * @brief iutest matchers namespace
*/
namespace matchers
{

/**
 * @defgroup    MATCHERS    Matchers
 * @brief       Matchers
 * @{
*/

/**
 * @brief   Make Equals matcher
 * @details argument == expected
*/
template<typename T>
detail::EqMatcher<T> Equals(const T& expected)
{
    return detail::EqMatcher<T>(expected);
}

/**
 * @brief   Make Eq matcher
 * @details argument == expected
*/
template<typename T>
detail::EqMatcher<T> Eq(const T& expected)
{
    return detail::EqMatcher<T>(expected);
}

/**
 * @brief   Make Ne matcher
 * @details argument != expected
*/
template<typename T>
detail::NeMatcher<T> Ne(const T& expected)
{
    return detail::NeMatcher<T>(expected);
}

/**
 * @brief   Make Le matcher
 * @details argument <= expected
*/
template<typename T>
detail::LeMatcher<T> Le(const T& expected)
{
    return detail::LeMatcher<T>(expected);
}

/**
 * @brief   Make Lt matcher
 * @details argument < expected
*/
template<typename T>
detail::LtMatcher<T> Lt(const T& expected)
{
    return detail::LtMatcher<T>(expected);
}

/**
 * @brief   Make Ge matcher
 * @details argument >= expected
*/
template<typename T>
detail::GeMatcher<T> Ge(const T& expected)
{
    return detail::GeMatcher<T>(expected);
}

/**
 * @brief   Make Gt matcher
 * @details argument > expected
*/
template<typename T>
detail::GtMatcher<T> Gt(const T& expected)
{
    return detail::GtMatcher<T>(expected);
}

/**
 * @brief   Make Twofold Eq matcher
 * @details argument == expected
*/
inline detail::TwofoldEqMatcher Eq()
{
    return detail::TwofoldEqMatcher();
}

/**
 * @brief   Make Twofold Ne matcher
 * @details argument != expected
*/
inline detail::TwofoldNeMatcher Ne()
{
    return detail::TwofoldNeMatcher();
}

/**
 * @brief   Make Twofold Le matcher
 * @details argument <= expected
*/
inline detail::TwofoldLeMatcher Le()
{
    return detail::TwofoldLeMatcher();
}

/**
 * @brief   Make Twofold Lt matcher
 * @details argument < expected
*/
inline detail::TwofoldLtMatcher Lt()
{
    return detail::TwofoldLtMatcher();
}

/**
 * @brief   Make Twofold Ge matcher
 * @details argument >= expected
*/
inline detail::TwofoldGeMatcher Ge()
{
    return detail::TwofoldGeMatcher();
}

/**
 * @brief   Make Twofold Gt matcher
 * @details argument > expected
*/
inline detail::TwofoldGtMatcher Gt()
{
    return detail::TwofoldGtMatcher();
}

/**
 * @brief   Make IsNull matcher
 * @details argument == nullptr
*/
inline detail::IsNullMatcher IsNull()
{
    return detail::IsNullMatcher();
}

/**
 * @brief   Make NotNull matcher
 * @details argument != nullptr
*/
inline detail::NotNullMatcher NotNull()
{
    return detail::NotNullMatcher();
}

/**
 * @brief   Make TypedEq matcher
 * @details argument == (T)expected
*/
template<typename T, typename U>
detail::TypedEqMatcher<T> TypedEq(const U& expected)
{
    return detail::TypedEqMatcher<T>(static_cast<T>(expected));
}

/**
 * @brief   Make FloatingPoint Eq matcher
 * @details argument は expected とおよそ等しい
*/
template<typename T>
inline detail::FloatingPointEqMatcher<T> FloatingPointEq(T expected)
{
    return detail::FloatingPointEqMatcher<T>(expected);
}

/**
 * @brief   Make Float Eq matcher
 * @details argument は expected とおよそ等しい
*/
inline detail::FloatingPointEqMatcher<float> FloatEq(float expected)
{
    return detail::FloatingPointEqMatcher<float>(expected);
}

/**
 * @brief   Make Double Eq matcher
 * @details argument は expected とおよそ等しい
*/
inline detail::FloatingPointEqMatcher<double> DoubleEq(double expected)
{
    return detail::FloatingPointEqMatcher<double>(expected);
}

#if IUTEST_HAS_LONG_DOUBLE

/**
 * @brief   Make Long Double Eq matcher
 * @details argument は expected とおよそ等しい
*/
inline detail::FloatingPointEqMatcher<long double> LongDoubleEq(long double expected)
{
    return detail::FloatingPointEqMatcher<long double>(expected);
}

#endif

/**
 * @brief   Make FloatingPoint Eq matcher
 * @details argument は expected とおよそ等しい
*/
template<typename T>
inline detail::NanSensitiveFloatingPointEqMatcher<T> NanSensitiveFloatingPointEq(T expected)
{
    return detail::NanSensitiveFloatingPointEqMatcher<T>(expected);
}

/**
 * @brief   Make NanSensitive Float Eq matcher
 * @details argument は expected とおよそ等しい（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointEqMatcher<float> NanSensitiveFloatEq(float expected)
{
    return detail::NanSensitiveFloatingPointEqMatcher<float>(expected);
}

/**
 * @brief   Make NanSensitive Double Eq matcher
 * @details argument は expected とおよそ等しい（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointEqMatcher<double> NanSensitiveDoubleEq(double expected)
{
    return detail::NanSensitiveFloatingPointEqMatcher<double>(expected);
}

#if IUTEST_HAS_LONG_DOUBLE

/**
 * @brief   Make NanSensitive LongDouble Eq matcher
 * @details argument は expected とおよそ等しい（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointEqMatcher<long double> NanSensitiveLongDoubleEq(long double expected)
{
    return detail::NanSensitiveFloatingPointEqMatcher<long double>(expected);
}

#endif

#if IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR

/**
 * @brief   Make FloatingPoint Near matcher
 * @details argument は expected と max_abs_error 以内の差分
*/
template<typename T>
inline detail::FloatingPointNearMatcher<T> FloatingPointNear(T expected, T max_abs_error)
{
    return detail::FloatingPointNearMatcher<T>(expected, max_abs_error);
}

/**
 * @brief   Make Float Near matcher
 * @details argument は expected と max_abs_error 以内の差分
*/
inline detail::FloatingPointNearMatcher<float> FloatNear(float expected, float max_abs_error)
{
    return detail::FloatingPointNearMatcher<float>(expected, max_abs_error);
}

/**
 * @brief   Make Double Near matcher
 * @details argument は expected と max_abs_error 以内の差分
*/
inline detail::FloatingPointNearMatcher<double> DoubleNear(double expected, double max_abs_error)
{
    return detail::FloatingPointNearMatcher<double>(expected, max_abs_error);
}

#if IUTEST_HAS_LONG_DOUBLE

/**
 * @brief   Make Long Double Near matcher
 * @details argument は expected と max_abs_error 以内の差分
*/
inline detail::FloatingPointNearMatcher<long double> LongDoubleNear(long double expected, long double max_abs_error)
{
    return detail::FloatingPointNearMatcher<long double>(expected, max_abs_error);
}

#endif

/**
 * @brief   Make FloatingPoint Near matcher
 * @details argument は expected と max_abs_error 以内の差分
*/
template<typename T>
inline detail::NanSensitiveFloatingPointNearMatcher<T> NanSensitiveFloatingPointNear(T expected, T max_abs_error)
{
    return detail::NanSensitiveFloatingPointNearMatcher<T>(expected, max_abs_error);
}

/**
 * @brief   Make NanSensitive Float Near matcher
 * @details argument は expected と max_abs_error 以内の差分（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointNearMatcher<float> NanSensitiveFloatNear(float expected, float max_abs_error)
{
    return detail::NanSensitiveFloatingPointNearMatcher<float>(expected, max_abs_error);
}

/**
 * @brief   Make NanSensitive Double Near matcher
 * @details argument は expected と max_abs_error 以内の差分（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointNearMatcher<double> NanSensitiveDoubleNear(double expected, double max_abs_error)
{
    return detail::NanSensitiveFloatingPointNearMatcher<double>(expected, max_abs_error);
}

#if IUTEST_HAS_LONG_DOUBLE

/**
 * @brief   Make NanSensitive LongDouble Near matcher
 * @details argument は expected と max_abs_error 以内の差分（NaN 同士は等しいとされる）
*/
inline detail::NanSensitiveFloatingPointNearMatcher<long double> NanSensitiveLongDoubleNear(long double expected, long double max_abs_error)
{
    return detail::NanSensitiveFloatingPointNearMatcher<long double>(expected, max_abs_error);
}

#endif

#endif

/**
 * @brief   Make StrEq matcher
 * @details argument == expected
*/
template<typename T>
detail::StrEqMatcher<T> StrEq(const T& expected)
{
    return detail::StrEqMatcher<T>(expected);
}

/**
 * @brief   Make StrNe matcher
 * @details argument != expected
*/
template<typename T>
detail::StrNeMatcher<T> StrNe(const T& expected)
{
    return detail::StrNeMatcher<T>(expected);
}

/**
 * @brief   Make StrCaseEq matcher
 * @details argument == expected (ignore case)
*/
template<typename T>
detail::StrCaseEqMatcher<T> StrCaseEq(const T& expected)
{
    return detail::StrCaseEqMatcher<T>(expected);
}

/**
 * @brief   Make StrCaseNe matcher
 * @details argument != expected (ignore case)
*/
template<typename T>
detail::StrCaseNeMatcher<T> StrCaseNe(const T& expected)
{
    return detail::StrCaseNeMatcher<T>(expected);
}

/**
 * @brief   Make StartsWith matcher
 * @details argument の先頭が str である
*/
template<typename T>
detail::StartsWithMatcher<const T&> StartsWith(const T& str)
{
    return detail::StartsWithMatcher<const T&>(str);
}

/**
 * @brief   Make HasSubstr matcher
 * @details argument が str を含む
*/
template<typename T>
detail::HasSubstrMatcher<const T&> HasSubstr(const T& str)
{
    return detail::HasSubstrMatcher<const T&>(str);
}

/**
 * @brief   Make EndsWith matcher
 * @details argument の末尾が str である
*/
template<typename T>
detail::EndsWithMatcher<const T&> EndsWith(const T& str)
{
    return detail::EndsWithMatcher<const T&>(str);
}

/**
 * @brief   Make Contains matcher
 * @details argument は expected にマッチする要素を含む
*/
template<typename T>
detail::ContainsMatcher<T> Contains(const T& expected)
{
    return detail::ContainsMatcher<T>(expected);
}

#if IUTEST_HAS_MATCHER_EACH

/**
 * @brief   Make Each matcher
 * @details argument はすべての要素が expected にマッチする
*/
template<typename T>
detail::EachMatcher<T> Each(const T& expected)
{
    return detail::EachMatcher<T>(expected);
}

#endif

/**
 * @brief   Make ContainerEq matcher
 * @details argument コンテナは expected コンテナにマッチする
*/
template<typename T>
detail::ContainerEqMatcher<T> ContainerEq(const T& expected)
{
    return detail::ContainerEqMatcher<T>(expected);
}

#if IUTEST_HAS_MATCHER_POINTWISE

/**
 * @brief   Make Pointwise matcher
 * @details argument コンテナは expected コンテナの各要素と matcher にマッチする
*/
template<typename M, typename T>
detail::PointwiseMatcher<M, T> Pointwise(const M& matcher, const T& expected)
{
    return detail::PointwiseMatcher<M, T>(matcher, expected);
}

#endif

#if IUTEST_HAS_MATCHER_OPTIONAL

/**
 * @brief   Make Optional matcher
 * @details argument は expected にマッチする
*/
template<typename T>
detail::OptionalMatcher<T> Optional(const T& expected)
{
    return detail::OptionalMatcher<T>(expected);
}

#endif

/**
 * @brief   Make IsEmpty matcher
 * @details argument.empty()
*/
inline detail::IsEmptyMatcher IsEmpty()
{
    return detail::IsEmptyMatcher();
}

/**
 * @brief   Make SizeIs matcher
 * @details argument の要素数が expected にマッチする
*/
template<typename T>
detail::SizeIsMatcher<T> SizeIs(const T& expected)
{
    return detail::SizeIsMatcher<T>(expected);
}

/**
 * @brief   Make At matcher
 * @details argument[index] は expected にマッチする
*/
template<typename T>
detail::AtMatcher<T> At(size_t index, const T& expected)
{
    return detail::AtMatcher<T>(index, expected);
}

/**
 * @brief   Make ElementsAreArray matcher
 * @details argument はの各要素が a の要素とマッチする
*/
template<typename Container>
detail::ElementsAreArrayMatcher< typename Container::value_type > ElementsAreArray(const Container& container)
{
    IUTEST_USING_BEGIN_END();
    return detail::ElementsAreArrayMatcher<typename Container::value_type>(container.begin(), container.end());
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
/** @overload */
template<typename T, size_t SIZE>
detail::ElementsAreArrayMatcher<T> ElementsAreArray(const T(&v)[SIZE])
{
    return detail::ElementsAreArrayMatcher<T>(v, v + SIZE);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/** @overload */
template<typename Ite>
detail::ElementsAreArrayMatcher< typename detail::IteratorTraits<Ite>::type > ElementsAreArray(Ite begin, Ite end)
{
    return detail::ElementsAreArrayMatcher< typename detail::IteratorTraits<Ite>::type >(begin, end);
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArray(::std::initializer_list<T> l)
{
    return detail::ElementsAreArrayMatcher<T>(l.begin(), l.end());
}
#endif

#endif

/**
 * @brief   Make ElementsAreArray matcher
 * @details argument は count 個の要素があり、 a の要素とマッチする
*/
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArray(const T* a, int count)
{
    return detail::ElementsAreArrayMatcher<T>(a, a + count);
}

#if IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD

/**
 * @brief   Make ElementsAreArrayForward matcher
 * @details argument の各要素が a の要素とマッチする
*/
template<typename Container>
detail::ElementsAreArrayMatcher< typename Container::value_type > ElementsAreArrayForward(const Container& container)
{
    return detail::ElementsAreArrayMatcher<typename Container::value_type>(container.begin(), container.end(), false);
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
/** @overload */
template<typename T, size_t SIZE>
detail::ElementsAreArrayMatcher<T> ElementsAreArrayForward(const T(&v)[SIZE])
{
    return detail::ElementsAreArrayMatcher<T>(v, v + SIZE, false);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/** @overload */
template<typename Ite>
detail::ElementsAreArrayMatcher< typename detail::IteratorTraits<Ite>::type > ElementsAreArrayForward(Ite begin, Ite end)
{
    return detail::ElementsAreArrayMatcher< typename detail::IteratorTraits<Ite>::type >(begin, end, false);
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArrayForward(::std::initializer_list<T> l)
{
    return detail::ElementsAreArrayMatcher<T>(l.begin(), l.end(), false);
}
#endif

#endif

/**
 * @brief   Make ElementsAreArrayForward matcher
 * @details argument は count 個の以上の要素があり、 a の要素とマッチする
*/
template<typename T>
detail::ElementsAreArrayMatcher<T> ElementsAreArrayForward(const T* a, int count)
{
    return detail::ElementsAreArrayMatcher<T>(a, a + count, false);
}

#endif

#if IUTEST_HAS_MATCHER_ELEMENTSARE

#if IUTEST_HAS_MATCHER_VARIADIC

/**
 * @brief   Make ElementsAre matcher
*/
template<typename ...T>
detail::ElementsAreMatcher<T...> ElementsAre(const T&... m)
{
    return detail::ElementsAreMatcher<T...>(m...);
}

#else

#define IIUT_ELEMENTSARE_MATCHER_NAME(n)    IUTEST_PP_CAT(ElementsAreMatcher, n)
#define IIUT_DECL_ELEMENTSARE(n)                                                \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                            \
    detail:: IIUT_ELEMENTSARE_MATCHER_NAME(n)< IUTEST_PP_ENUM_PARAMS(n, T) >    \
    ElementsAre( IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &m) ) { return        \
    detail:: IIUT_ELEMENTSARE_MATCHER_NAME(n)< IUTEST_PP_ENUM_PARAMS(n, T) >    \
        ( IUTEST_PP_ENUM_PARAMS(n, m) ); }


IIUT_DECL_ELEMENTSARE(1)
IIUT_DECL_ELEMENTSARE(2)
IIUT_DECL_ELEMENTSARE(3)
IIUT_DECL_ELEMENTSARE(4)
IIUT_DECL_ELEMENTSARE(5)
IIUT_DECL_ELEMENTSARE(6)
IIUT_DECL_ELEMENTSARE(7)
IIUT_DECL_ELEMENTSARE(8)
IIUT_DECL_ELEMENTSARE(9)
IIUT_DECL_ELEMENTSARE(10)

#undef IIUT_ELEMENTSARE_MATCHER_NAME
#undef IIUT_DECL_ELEMENTSARE
#endif

#endif

/**
 * @brief   Make Key matcher
 * @details argument.first は expedted にマッチする
*/
template<typename T>
detail::KeyMatcher<T> Key(const T& expected)
{
    return detail::KeyMatcher<T>(expected);
}

/**
 * @brief   Make Pair matcher
 * @details argument.first は m1 にマッチし、arugment.second が m2 にマッチする
*/
template<typename T1, typename T2>
detail::PairMatcher<T1, T2> Pair(const T1& m1, const T2& m2)
{
    return detail::PairMatcher<T1, T2>(m1, m2);
}

/**
 * @brief   Make Field matcher
 * @details argument.*field は expedted にマッチする
*/
template<typename F, typename T>
detail::FieldMatcher<F, T> Field(const F& field, const T& expected)
{
    return detail::FieldMatcher<F, T>(field, expected);
}

/**
 * @brief   Make Property matcher
 * @details argument.*property() は expedted にマッチする
*/
template<typename P, typename T>
detail::PropertyMatcher<P, T> Property(const P& prop, const T& expected)
{
    return detail::PropertyMatcher<P, T>(prop, expected);
}

/**
 * @brief   Make ResultOf matcher
 * @details func(argument) の戻り値は expedted にマッチする
*/
template<typename F, typename T>
detail::ResultOfMatcher<F, T> ResultOf(const F& func, const T& expected)
{
    return detail::ResultOfMatcher<F, T>(func, expected);
}

/**
 * @brief   Make Pointee matcher
*/
template<typename T>
detail::PointeeMatcher<T> Pointee(const T& expected)
{
    return detail::PointeeMatcher<T>(expected);
}

/**
 * @brief   Make Not matcher
*/
template<typename T>
detail::NotMatcher<T> Not(const T& unexpected)
{
    return detail::NotMatcher<T>(unexpected);
}

/**
 * @brief   Make Any matcher
*/
template<typename T>
detail::AnyMatcher<T> A()
{
    return detail::AnyMatcher<T>();
}


/**
 * @brief   Anything matcher
*/
const detail::AnythingMatcher _;

#if IUTEST_HAS_MATCHER_REGEX

/**
 * @brief   Make MatchesRegex matcher
*/
inline detail::RegexMatcher MatchesRegex(const ::std::string& str)
{
    return detail::RegexMatcher(detail::iuRegex(str), true);
}

/**
 * @brief   Make ContainsRegex matcher
*/
inline detail::RegexMatcher ContainsRegex(const ::std::string& str)
{
    return detail::RegexMatcher(detail::iuRegex(str), false);
}

#endif

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF

#if IUTEST_HAS_MATCHER_VARIADIC

/**
 * @brief   Make AllOf matcher
 * @details argument が全ての matcher にマッチする
*/
template<typename ...T>
detail::AllOfMatcher<T...> AllOf(const T&... m)
{
    return detail::AllOfMatcher<T...>(m...);
}

/**
 * @brief   Make AnyOf matcher
 * @details argument がいずれかの matcher にマッチする
*/
template<typename ...T>
detail::AnyOfMatcher<T...> AnyOf(const T&... m)
{
    return detail::AnyOfMatcher<T...>(m...);
}

#else

#define IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)  IUTEST_PP_CAT( IUTEST_PP_CAT(name, Matcher), n)
#define IIUT_DECL_ANYOF_AND_ALLOF(name, n)                                              \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                    \
    detail:: IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)< IUTEST_PP_ENUM_PARAMS(n, T) >  \
    name( IUTEST_PP_ENUM_BINARY_PARAMS(n, const T, &m) ) { return                       \
    detail:: IIUT_ANYOF_AND_ALLOF_MATCHER_NAME(name, n)< IUTEST_PP_ENUM_PARAMS(n, T) >  \
        ( IUTEST_PP_ENUM_PARAMS(n, m) ); }


IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 2)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 3)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 4)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 5)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 6)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 7)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 8)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 9)
IIUT_DECL_ANYOF_AND_ALLOF(AllOf, 10)

IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 2)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 3)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 4)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 5)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 6)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 7)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 8)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 9)
IIUT_DECL_ANYOF_AND_ALLOF(AnyOf, 10)

#undef IIUT_ANYOF_AND_ALLOF_MATCHER_NAME
#undef IIUT_DECL_ANYOF_AND_ALLOF

#endif

#endif

/**
 * @brief   Value predicate
*/
template<typename T, typename M>
bool Value(const T& value, const M& expected)
{
    return static_cast<bool>(detail::CastToMatcher(expected)(value));
}

/**
 * @}
*/

}   // end of namespace matchers

using namespace matchers; // NOLINT

}   // end of namespace iutest

#endif  // IUTEST_HAS_MATCHERS

#endif // INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_
