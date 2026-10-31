//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_matcher.hpp
 * @brief       iris unit test matcher 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2023, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_
#define INCG_IRIS_IUTEST_MATCHER_HPP_23746E00_1A4B_4778_91AD_45C6DEFEEFA7_

#if IUTEST_HAS_MATCHERS

#if IUTEST_HAS_MATCHER_DISTANCEFROM
#include <cmath>
#endif

#if IUTEST_HAS_CXX11
#include <memory>
#include <utility>
#endif

#include <list>
#include <sstream>

#if IUTEST_HAS_MATCHER_FIELDSARE
#include <tuple>
#include <type_traits>
#endif

//======================================================================
// define
/**
 * @private
 * @{
*/
#define IIUT_MATCHER_ASSERTION_(actual, matcher) ::iutest::detail::MatcherAssertion(actual, matcher)

#define IUTEST_TEST_THAT(actual, matcher, on_failure)                   \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                      \
    if( ::iutest::AssertionResult iutest_ar = IIUT_MATCHER_ASSERTION_(actual, matcher) ) { \
    } else                                                              \
        on_failure(::iutest::detail::MatcherAssertionFailureMessage(    \
            ::iutest::PrintToString(actual).c_str(), #matcher, iutest_ar))

/**
 * @}
*/

#if IUTEST_HAS_MATCHER_MACROS

/**
 * @ingroup MATCHERS
 * @brief Define a polymorphic matcher. The body can use arg, arg_type and
 *        result_listener (supporting streaming, IsInterested() and stream()).
 *        Descriptions can use negation.
*/
#define IUTEST_MATCHER(name, description) \
    class name##Matcher : public ::iutest::detail::MatcherMacroBase { \
    public: \
        IIUT_MATCHER_METHODS_(name, description, ::std::string()) \
    }; \
    inline name##Matcher IUTEST_ATTRIBUTE_UNUSED_ name() { return name##Matcher(); } \
    template<typename arg_type> \
    bool name##Matcher::MatchAndExplainImpl(const arg_type& arg IUTEST_ATTRIBUTE_UNUSED_, \
        ::iutest::detail::MatcherMacroListener* result_listener IUTEST_ATTRIBUTE_UNUSED_) const

/** @brief Define matchers with one through ten parameters, stored by value and moved when supported. */
#define IUTEST_MATCHER_P(name, p0, description) \
    IIUT_MATCHER_P_(1, name, description, \
        (p0, _, _, _, _, _, _, _, _, _), (#p0, "", "", "", "", "", "", "", "", ""))
#define IUTEST_MATCHER_P2(name, p0, p1, description) \
    IIUT_MATCHER_P_(2, name, description, \
        (p0, p1, _, _, _, _, _, _, _, _), (#p0, #p1, "", "", "", "", "", "", "", ""))
#define IUTEST_MATCHER_P3(name, p0, p1, p2, description) \
    IIUT_MATCHER_P_(3, name, description, \
        (p0, p1, p2, _, _, _, _, _, _, _), (#p0, #p1, #p2, "", "", "", "", "", "", ""))
#define IUTEST_MATCHER_P4(name, p0, p1, p2, p3, description) \
    IIUT_MATCHER_P_(4, name, description, \
        (p0, p1, p2, p3, _, _, _, _, _, _), (#p0, #p1, #p2, #p3, "", "", "", "", "", ""))
#define IUTEST_MATCHER_P5(name, p0, p1, p2, p3, p4, description) \
    IIUT_MATCHER_P_(5, name, description, \
        (p0, p1, p2, p3, p4, _, _, _, _, _), (#p0, #p1, #p2, #p3, #p4, "", "", "", "", ""))
#define IUTEST_MATCHER_P6(name, p0, p1, p2, p3, p4, p5, description) \
    IIUT_MATCHER_P_(6, name, description, \
        (p0, p1, p2, p3, p4, p5, _, _, _, _), (#p0, #p1, #p2, #p3, #p4, #p5, "", "", "", ""))
#define IUTEST_MATCHER_P7(name, p0, p1, p2, p3, p4, p5, p6, description) \
    IIUT_MATCHER_P_(7, name, description, \
        (p0, p1, p2, p3, p4, p5, p6, _, _, _), (#p0, #p1, #p2, #p3, #p4, #p5, #p6, "", "", ""))
#define IUTEST_MATCHER_P8(name, p0, p1, p2, p3, p4, p5, p6, p7, description) \
    IIUT_MATCHER_P_(8, name, description, \
        (p0, p1, p2, p3, p4, p5, p6, p7, _, _), (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7, "", ""))
#define IUTEST_MATCHER_P9(name, p0, p1, p2, p3, p4, p5, p6, p7, p8, description) \
    IIUT_MATCHER_P_(9, name, description, \
        (p0, p1, p2, p3, p4, p5, p6, p7, p8, _), (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7, #p8, ""))
#define IUTEST_MATCHER_P10(name, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, description) \
    IIUT_MATCHER_P_(10, name, description, \
        (p0, p1, p2, p3, p4, p5, p6, p7, p8, p9), (#p0, #p1, #p2, #p3, #p4, #p5, #p6, #p7, #p8, #p9))

/** @private */
#define IIUT_MATCHER_METHODS_(name, description, params) \
    ::std::string FormatDescription(bool negation IUTEST_ATTRIBUTE_UNUSED_) const { \
        const ::std::string iutest_description = (description); \
        return iutest_description.empty() \
            ? ::iutest::detail::FormatMatcherDescription(negation, #name, params) : iutest_description; \
    } \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return FormatDescription(false); } \
    void DescribeTo(::std::ostream* iutest_os) const IUTEST_CXX_OVERRIDE { *iutest_os << FormatDescription(false); } \
    void DescribeNegationTo(::std::ostream* iutest_os) const IUTEST_CXX_OVERRIDE { *iutest_os << FormatDescription(true); } \
    template<typename iutest_actual_type> \
    ::iutest::AssertionResult operator()(const iutest_actual_type& iutest_actual) const { \
        ::std::ostringstream iutest_explanation; \
        if( MatchAndExplain(iutest_actual, &iutest_explanation) ) return ::iutest::AssertionSuccess(); \
        return ::iutest::AssertionFailure() << WhichIs() << "\n" << iutest_explanation.str(); \
    } \
    template<typename iutest_actual_type> \
    bool MatchAndExplain(const iutest_actual_type& iutest_actual, ::std::ostream* iutest_stream) const { \
        ::iutest::detail::MatcherMacroListener iutest_listener(iutest_stream); \
        return MatchAndExplainImpl(iutest_actual, &iutest_listener); \
    } \
    template<typename arg_type> bool MatchAndExplainImpl(const arg_type& arg, \
        ::iutest::detail::MatcherMacroListener* result_listener) const;

#define IIUT_MATCHER_PARAM_0(a, b, c, d, e, f, g, h, i, j) a
#define IIUT_MATCHER_PARAM_1(a, b, c, d, e, f, g, h, i, j) b
#define IIUT_MATCHER_PARAM_2(a, b, c, d, e, f, g, h, i, j) c
#define IIUT_MATCHER_PARAM_3(a, b, c, d, e, f, g, h, i, j) d
#define IIUT_MATCHER_PARAM_4(a, b, c, d, e, f, g, h, i, j) e
#define IIUT_MATCHER_PARAM_5(a, b, c, d, e, f, g, h, i, j) f
#define IIUT_MATCHER_PARAM_6(a, b, c, d, e, f, g, h, i, j) g
#define IIUT_MATCHER_PARAM_7(a, b, c, d, e, f, g, h, i, j) h
#define IIUT_MATCHER_PARAM_8(a, b, c, d, e, f, g, h, i, j) i
#define IIUT_MATCHER_PARAM_9(a, b, c, d, e, f, g, h, i, j) j
#define IIUT_MATCHER_PARAM_(i, params) IIUT_MATCHER_PARAM_II_(i, params)
#define IIUT_MATCHER_PARAM_II_(i, params) IIUT_MATCHER_PARAM_CAT_(IIUT_MATCHER_PARAM_, i) params
#define IIUT_MATCHER_PARAM_CAT_(a, b) IIUT_MATCHER_PARAM_CAT_I_(a, b)
#define IIUT_MATCHER_PARAM_CAT_I_(a, b) IIUT_MATCHER_PARAM_CAT_II_(a ## b)
#define IIUT_MATCHER_PARAM_CAT_II_(result) result
#define IIUT_MATCHER_TYPE_(i, params) IIUT_MATCHER_TYPE_II_(IIUT_MATCHER_PARAM_(i, params))
#define IIUT_MATCHER_TYPE_II_(param) IUTEST_PP_CAT(param, _type)
#define IIUT_MATCHER_TYPENAME_(i, params) typename IIUT_MATCHER_TYPE_(i, params)
#define IIUT_MATCHER_ARG_(i, params) IIUT_MATCHER_TYPE_(i, params) IUTEST_PP_CAT(iutest_p, i)
#define IIUT_MATCHER_TRANSFER_TYPE_(i, params) \
    typename ::iutest::detail::MatcherMacroParameter<IIUT_MATCHER_TYPE_(i, params)>::type
#define IIUT_MATCHER_TRANSFER_ARG_(i, params) IIUT_MATCHER_TRANSFER_TYPE_(i, params) IUTEST_PP_CAT(iutest_p, i)
// std::is_move_constructible is unavailable before libstdc++ 4.7
#if IUTEST_HAS_RVALUE_REFS && IUTEST_HAS_CXX_HDR_TYPE_TARITS \
    && (!defined(IUTEST_LIBSTDCXX_VERSION) || IUTEST_LIBSTDCXX_VERSION >= 40700)
#  define IIUT_HAS_MATCHER_PARAMETER_MOVE_  1
#else
#  define IIUT_HAS_MATCHER_PARAMETER_MOVE_  0
#endif
#if IIUT_HAS_MATCHER_PARAMETER_MOVE_
#define IIUT_MATCHER_FORWARD_(i, params) \
    ::iutest::detail::MatcherMacroParameter<IIUT_MATCHER_TYPE_(i, params)>::Forward( \
        ::std::move(IUTEST_PP_CAT(iutest_p, i)))
#else
#define IIUT_MATCHER_FORWARD_(i, params) IUTEST_PP_CAT(iutest_p, i)
#endif
#define IIUT_MATCHER_INIT_(i, params) IIUT_MATCHER_PARAM_(i, params)(IIUT_MATCHER_FORWARD_(i, params))
#define IIUT_MATCHER_MEMBER_(i, params) const IIUT_MATCHER_TYPE_(i, params) IIUT_MATCHER_PARAM_(i, params);
#define IIUT_MATCHER_PRINT_(i, params, names) \
    ::iutest::detail::MatcherMacroBase::PrintParameter(&iutest_os, i != 0, \
        IIUT_MATCHER_PARAM_(i, names), this->IIUT_MATCHER_PARAM_(i, params));
#define IIUT_MATCHER_CLASS_(name, n) IUTEST_PP_CAT(name, IUTEST_PP_CAT(MatcherP, n))
#define IIUT_MATCHER_P_(n, name, description, params, names) \
    template<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPENAME_, params)> \
    class IIUT_MATCHER_CLASS_(name, n) : public ::iutest::detail::MatcherMacroBase { \
    public: \
        explicit IIUT_MATCHER_CLASS_(name, n)(IUTEST_PP_ENUM(n, IIUT_MATCHER_ARG_, params)) \
            : IUTEST_PP_ENUM(n, IIUT_MATCHER_INIT_, params) {} \
        explicit IIUT_MATCHER_CLASS_(name, n)(::iutest::detail::MatcherMacroFactoryTag, \
            IUTEST_PP_ENUM(n, IIUT_MATCHER_TRANSFER_ARG_, params)) \
            : IUTEST_PP_ENUM(n, IIUT_MATCHER_INIT_, params) {} \
        ::std::string Parameters() const { \
            ::std::ostringstream iutest_os; iutest_os << " ("; \
            IUTEST_PP_REPEAT_BINARY(n, IIUT_MATCHER_PRINT_, params, names) \
            iutest_os << ")"; return iutest_os.str(); \
        } \
        IIUT_MATCHER_METHODS_(name, description, Parameters()) \
        IUTEST_PP_REPEAT(n, IIUT_MATCHER_MEMBER_, params) \
    }; \
    template<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPENAME_, params)> \
    inline IIUT_MATCHER_CLASS_(name, n)<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPE_, params)> \
    name(IUTEST_PP_ENUM(n, IIUT_MATCHER_ARG_, params)) { \
        return IIUT_MATCHER_CLASS_(name, n)<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPE_, params)>( \
            ::iutest::detail::MatcherMacroFactoryTag(), IUTEST_PP_ENUM(n, IIUT_MATCHER_FORWARD_, params)); \
    } \
    template<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPENAME_, params)> \
    template<typename arg_type> \
    bool IIUT_MATCHER_CLASS_(name, n)<IUTEST_PP_ENUM(n, IIUT_MATCHER_TYPE_, params)>::MatchAndExplainImpl( \
        const arg_type& arg IUTEST_ATTRIBUTE_UNUSED_, \
        ::iutest::detail::MatcherMacroListener* result_listener IUTEST_ATTRIBUTE_UNUSED_) const

#endif

namespace iutest {
namespace detail
{

#if IUTEST_HAS_MATCHER_MACROS
// Preserve the by-value constructor while avoiding an intermediate copy in the factory.
struct MatcherMacroFactoryTag {};

#if IIUT_HAS_MATCHER_PARAMETER_MOVE_
template<typename T>
struct MatcherMacroParameter
{
    typedef typename ::std::conditional< ::std::is_move_constructible<T>::value, T&&, const T&>::type type;
    static type Forward(typename ::std::remove_reference<type>::type&& value)
    {
        return static_cast<type>(value);
    }
};
#else
template<typename T>
struct MatcherMacroParameter
{
    typedef const T& type;
};

template<typename T>
struct MatcherMacroParameter<T&>
{
    typedef T& type;
};
#endif

class MatcherMacroListener
{
public:
    explicit MatcherMacroListener(::std::ostream* os) : m_stream(os) {}
    bool IsInterested() const { return m_stream != NULL; }
    ::std::ostream* stream() { return m_stream; }
    template<typename T>
    MatcherMacroListener& operator << (const T& value)
    {
        if( IsInterested() ) *m_stream << value;
        return *this;
    }
private:
    ::std::ostream* m_stream;
};

inline ::std::string MatcherNameToWords(const char* name)
{
    ::std::string words;
    for( size_t i = 0; name[i] != '\0'; ++i )
    {
        const char c = name[i];
        const bool upper = c >= 'A' && c <= 'Z';
        const bool lower = c >= 'a' && c <= 'z';
        const bool digit = c >= '0' && c <= '9';
        if( !upper && !lower && !digit ) continue;
        const char previous = i == 0 ? '\0' : name[i-1];
        const bool previous_alpha = (previous >= 'a' && previous <= 'z') || (previous >= 'A' && previous <= 'Z');
        const bool previous_digit = previous >= '0' && previous <= '9';
        if( !words.empty() && (upper || (lower && !previous_alpha) || (digit && !previous_digit)) ) words += ' ';
        words += upper ? static_cast<char>(c - 'A' + 'a') : c;
    }
    return words;
}

inline ::std::string FormatMatcherDescription(bool negation, const char* name, const ::std::string& params)
{
    ::std::string description;
    if( negation ) description += "not (";
    description += MatcherNameToWords(name);
    description += params;
    if( negation ) description += ')';
    return description;
}
#endif

//======================================================================
// function
/**
 * @brief   Matcher Assertion Failure Message
*/
inline ::std::string MatcherAssertionFailureMessage(const char* actual, const char* matcher_str
                                                    , const AssertionResult& ar)
{
    iu_global_format_stringstream strm;
    const ::std::string message(ar.message());
    const ::std::string::size_type separator = message.find('\n');
    strm << "error: Expected: " << matcher_str
        << "\n  Actual: " << actual;
    if( separator != ::std::string::npos && separator + 1 < message.size() )
    {
        strm << ", " << message.substr(separator + 1);
    }
    strm << "\nWhich is: " << message.substr(0, separator);
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
    virtual void DescribeTo(::std::ostream* os) const { *os << WhichIs(); }
    virtual void DescribeNegationTo(::std::ostream* os) const { *os << "not (" << WhichIs() << ")"; }
};

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template<typename T>
struct MatcherConstReference
{
    typedef const T& type;
};

template<typename T>
struct MatcherConstReference<T&>
{
    typedef T& type;
};
#else
template<typename T>
struct MatcherConstReference
{
    typedef T type;
};
#endif

#if IUTEST_HAS_MATCHER_MACROS
class MatcherMacroBase : public IMatcher
{
protected:
    template<typename T>
    static void PrintParameter(::std::ostream* os, bool separator, const char* name, const T& value)
    {
        if( separator ) *os << ", ";
        *os << name << ": ";
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        PrintParameterValue(os, value, iutest_type_traits::is_function_pointer<T*>());
#else
        *os << ::iutest::PrintToString(value);
#endif
    }
private:
    template<typename T>
    static void PrintParameterValue(::std::ostream* os, const T& value, iutest_type_traits::false_type)
    {
        *os << ::iutest::PrintToString(value);
    }
    template<typename T>
    static void PrintParameterValue(::std::ostream* os, const T&, iutest_type_traits::true_type)
    {
        *os << "<function>";
    }
};
#endif

#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
template<typename M, typename U>
struct is_gtest_matcher
{
    template<typename T>
    static auto Check(int) -> decltype(
        ((const T*)0)->DescribeTo((::std::ostream*)0),
        ((const T*)0)->MatchAndExplain(*((const U*)0), (::std::ostream*)0),
        iutest_type_traits::true_type());
    template<typename T>
    static iutest_type_traits::false_type Check(...);

    enum { value = !IMatcher::is_matcher<M>::value && decltype(Check<M>(0))::value };
};

template<typename U, typename M>
typename iutest_type_traits::enable_if<
    is_gtest_matcher<M, U>::value, AssertionResult>::type MatcherAssertion(const U& actual, const M& matcher)
{
    ::std::ostringstream explanation;
    const bool matched = matcher.MatchAndExplain(actual, &explanation);
    if( matched ) return AssertionSuccess();
    ::std::ostringstream description;
    matcher.DescribeTo(&description);
    return AssertionFailure() << description.str() << "\n" << explanation.str();
}
#endif

template<typename T>
inline const T& MatcherStringValue(const T& value)
{
    return value;
}

inline ::std::string MatcherStringValue(iu_string_view value)
{
    return value.empty() ? ::std::string() : ::std::string(value.data(), value.size());
}

#if IUTEST_HAS_CHAR8_T
inline ::std::string MatcherStringValue(const char8_t* value)
{
    return ::std::string(reinterpret_cast<const char*>(value));
}

inline ::std::string MatcherStringValue(char8_t* value)
{
    return MatcherStringValue(static_cast<const char8_t*>(value));
}

inline ::std::string MatcherStringValue(const ::std::u8string& value)
{
    return ::std::string(reinterpret_cast<const char*>(value.data()), value.size());
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
inline ::std::string MatcherStringValue(::std::u8string_view value)
{
    return ::std::string(reinterpret_cast<const char*>(value.data()), value.size());
}
#endif
#endif

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
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is " #op " " << m_expected; } \
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "isn't " #op " " << m_expected; } \
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
    public: IUTEST_PP_CAT(name, Matcher)(T value) : m_expected(value) {}        \
    template<typename U>AssertionResult operator ()(const U& actual) const {    \
        if IUTEST_COND_LIKELY( internal::IUTEST_PP_CAT(name, Helper)::Compare(  \
            MatcherStringValue(actual), m_expected) ) { return AssertionSuccess(); } \
        return AssertionFailure() << WhichIs();                                 \
    }                                                                           \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                         \
        iu_global_format_stringstream strm; strm << #name ": " << m_expected;   \
        return strm.str();                                                      \
    }                                                                           \
    private:                                                                    \
    T m_expected;                                                               \
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
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is NULL"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "isn't NULL"; }
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
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "isn't NULL"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is NULL"; }
};

/**
 * @brief   IsTrue matcher
*/
class IsTrueMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( static_cast<bool>(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "Is True"; }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is true"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is false"; }
};

/**
 * @brief   IsFalse matcher
*/
class IsFalseMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if IUTEST_COND_LIKELY( !static_cast<bool>(actual) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "Is False"; }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is false"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is true"; }
};

/**
 * @brief   IsNan matcher
*/
class IsNanMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename T>
    AssertionResult operator ()(const T& actual) const
    {
        if IUTEST_COND_LIKELY( floating_point<T>(actual).is_nan() )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "Is NaN";
    }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is NaN"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "isn't NaN"; }
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
        if IUTEST_COND_LIKELY( StartsWith(MatcherStringValue(actual), m_expected) )
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
        return actual.compare(0, strlen(start), start) == 0;
    }
    static bool StartsWith(const char* actual, const ::std::string& start)
    {
        return StartsWith(::std::string(actual), start);
    }
    static bool StartsWith(const ::std::string& actual, const ::std::string& start)
    {
        return actual.compare(0, start.size(), start) == 0;
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
        if IUTEST_COND_LIKELY( HasSubstr(MatcherStringValue(actual), m_expected) )
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
        return actual.find(expected) != ::std::string::npos;
    }
    static bool HasSubstr(const char* actual, const ::std::string& expected)
    {
        return HasSubstr(::std::string(actual), expected);
    }
    static bool HasSubstr(const ::std::string& actual, const ::std::string& expected)
    {
        return actual.find(expected) != ::std::string::npos;
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
        if IUTEST_COND_LIKELY( EndsWith(MatcherStringValue(actual), m_expected) )
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
        return EndsWith(actual, ::std::string(end));
    }
    static bool EndsWith(const char* actual, const ::std::string& end)
    {
        return EndsWith(::std::string(actual), end);
    }
    static bool EndsWith(const ::std::string& actual, const ::std::string& end)
    {
        return actual.size() >= end.size()
            && actual.compare(actual.size() - end.size(), end.size(), end) == 0;
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
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE
    {
        *os << "is equal to " << PrintToString(m_expected);
    }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE
    {
        *os << "isn't equal to " << PrintToString(m_expected);
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
 * @brief   TypedEq matcher value holder
 * @note    EqMatcher holds a reference, so the value must be constructed before it
*/
template<typename T>
class TypedEqMatcherValueHolder
{
protected:
    explicit TypedEqMatcherValueHolder(const T& expected) : m_expected(expected) {}
    T m_expected;
};

/**
 * @brief   TypedEq matcher
*/
template<typename T>
class TypedEqMatcher IUTEST_CXX_FINAL : private TypedEqMatcherValueHolder<T>, public EqMatcher<T>
{
    typedef TypedEqMatcherValueHolder<T> _Holder;
public:
    explicit TypedEqMatcher(T expected) : _Holder(expected), EqMatcher<T>(_Holder::m_expected) {}
public:
    AssertionResult operator ()(const T& actual)
    {
        return EqMatcher<T>::operator ()(actual);
    }
    template<typename U>
    AssertionResult operator ()(const U&) const;
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

#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
template<typename M>
struct has_gtest_description
{
    template<typename T>
    static auto Check(int) -> decltype(
        ((const T*)0)->DescribeTo((::std::ostream*)0),
        ((const T*)0)->DescribeNegationTo((::std::ostream*)0),
        iutest_type_traits::true_type());
    template<typename T>
    static iutest_type_traits::false_type Check(...);
    enum { value = !IMatcher::is_matcher<M>::value && decltype(Check<M>(0))::value };
};

template<typename T>
typename iutest_type_traits::enable_if<has_gtest_description<T>::value, void>::type
DescribeMatcherTo(const T& matcher, ::std::ostream* os) { matcher.DescribeTo(os); }

template<typename T>
typename iutest_type_traits::enable_if<has_gtest_description<T>::value, void>::type
DescribeMatcherNegationTo(const T& matcher, ::std::ostream* os) { matcher.DescribeNegationTo(os); }
#endif

template<typename T>
void DescribeNativeMatcherTo(const T& matcher, ::std::ostream* os, iutest_type_traits::true_type)
{
    matcher.DescribeTo(os);
}
template<typename T>
void DescribeNativeMatcherTo(const T& value, ::std::ostream* os, iutest_type_traits::false_type)
{
    EqMatcher<T>(value).DescribeTo(os);
}
template<typename T>
void DescribeNativeMatcherNegationTo(const T& matcher, ::std::ostream* os, iutest_type_traits::true_type)
{
    matcher.DescribeNegationTo(os);
}
template<typename T>
void DescribeNativeMatcherNegationTo(const T& value, ::std::ostream* os, iutest_type_traits::false_type)
{
    EqMatcher<T>(value).DescribeNegationTo(os);
}

template<typename T>
#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
typename iutest_type_traits::disable_if<has_gtest_description<T>::value, void>::type
#else
void
#endif
DescribeMatcherTo(const T& matcher, ::std::ostream* os)
{
    DescribeNativeMatcherTo(matcher, os, iutest_type_traits::bool_constant<IMatcher::is_matcher<T>::value>());
}

template<typename T>
#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
typename iutest_type_traits::disable_if<has_gtest_description<T>::value, void>::type
#else
void
#endif
DescribeMatcherNegationTo(const T& matcher, ::std::ostream* os)
{
    DescribeNativeMatcherNegationTo(matcher, os, iutest_type_traits::bool_constant<IMatcher::is_matcher<T>::value>());
}

template<typename M, typename U>
struct has_match_explanation
{
#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
    template<typename T>
    static auto Check(int) -> decltype(
        (static_cast<T*>(0))->MatchAndExplain(*static_cast<const U*>(0), static_cast< ::std::ostream*>(0)),
        iutest_type_traits::true_type());
    template<typename T>
    static iutest_type_traits::false_type Check(...);
    enum { value = decltype(Check<M>(0))::value };
#elif !defined(IUTEST_NO_SFINAE) \
    && !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 4)
    template<typename T>
    static char Check(char (*)[sizeof((static_cast<T*>(0))->MatchAndExplain(*static_cast<const U*>(0), static_cast< ::std::ostream*>(0)))]);
    template<typename T>
    static long Check(...);
    enum { value = sizeof(Check<M>(0)) == sizeof(char) };
#else
    enum { value = false };
#endif
};

template<typename M, typename U>
#if !defined(IUTEST_NO_SFINAE)
typename iutest_type_traits::enable_if<has_match_explanation<M, U>::value, bool>::type
ExplainMatch(M& matcher, const U& actual, ::std::ostream* listener)
{
    return matcher.MatchAndExplain(actual, listener);
}

template<typename M, typename U>
typename iutest_type_traits::disable_if<has_match_explanation<M, U>::value, bool>::type
ExplainMatch(M& matcher, const U& actual, ::std::ostream*)
#else
bool ExplainMatch(M& matcher, const U& actual, ::std::ostream*)
#endif
{
    return static_cast<bool>(CastToMatcher(matcher)(actual));
}

template<typename U, typename M>
AssertionResult MatcherAssertionNative(const U& actual, M& matcher, iutest_type_traits::false_type)
{
    return matcher(actual);
}

template<typename U, typename M>
AssertionResult MatcherAssertionNative(const U& actual, M& matcher, iutest_type_traits::true_type)
{
    ::std::ostringstream explanation;
    if( ExplainMatch(matcher, actual, &explanation) ) return AssertionSuccess();
    ::std::string message;
    message.append(matcher.WhichIs()).append("\n").append(explanation.str());
    for( ::std::string::size_type pos = 0;
        (pos = message.find('\0', pos)) != ::std::string::npos; pos += 2 )
    {
        message.replace(pos, 1, "\\0");
    }
    return AssertionFailure() << message;
}

template<typename U, typename M>
#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
typename iutest_type_traits::disable_if<
    is_gtest_matcher<typename iutest_type_traits::remove_reference<M>::type, U>::value,
    AssertionResult>::type
MatcherAssertion(const U& actual, M&& matcher)
#else
AssertionResult MatcherAssertion(const U& actual, M& matcher)
#endif
{
    return MatcherAssertionNative(actual, matcher,
        iutest_type_traits::bool_constant<
            has_match_explanation<typename iutest_type_traits::remove_reference<M>::type, U>::value>());
}

#if !(IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE))
template<typename U, typename M>
AssertionResult MatcherAssertion(const U& actual, const M& matcher)
{
    M copy(matcher);
    return MatcherAssertion(actual, copy);
}
#endif

/**
 * @brief   Contains matcher with a match count
*/
template<typename T, typename N>
class ContainsTimesMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    ContainsTimesMatcher(const T& expected, const N& times) : m_expected(expected), m_times(times) {}

    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        const size_t count = Count(begin(actual), end(actual));
        if( CastToMatcher(m_times)(count) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs() << ", matched " << count << " times";
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Contains: " << m_expected << ", Times: " << m_times;
        return strm.str();
    }

private:
    template<typename Ite>
    size_t Count(Ite begin, Ite end)
    {
        size_t count = 0;
        for( Ite it = begin; it != end; ++it )
        {
            if( CastToMatcher(m_expected)(*it) )
            {
                ++count;
            }
        }
        return count;
    }

    T m_expected;
    N m_times;
};

/**
 * @brief   Contains matcher
*/
template<typename T>
class ContainsMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit ContainsMatcher(const T& expected) : m_expected(expected) {}

    template<typename N>
    ContainsTimesMatcher<T, N> Times(const N& times) const
    {
        return ContainsTimesMatcher<T, N>(m_expected, times);
    }

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

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        IUTEST_USING_BEGIN_END();
        return Each(begin(actual), end(actual), listener);
    }

private:
    template<typename Ite>
    bool Each(Ite it, Ite end, ::std::ostream* listener)
    {
        size_t index = 0;
        for( ; it != end; ++it, ++index )
        {
            ::std::ostringstream inner;
            if( !ExplainMatch(m_expected, *it, &inner) )
            {
                *listener << "whose element #" << index << " doesn't match";
                if( !inner.str().empty() ) *listener << ", " << inner.str();
                return false;
            }
        }
        return true;
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
            ar << PrintToString(*actual);
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

#if IUTEST_HAS_CXX_HDR_ANY

/**
 * @brief   AnyWith matcher
*/
template<typename T, typename M>
class AnyWithMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit AnyWithMatcher(const M& matcher) : m_matcher(matcher) {}

    AssertionResult operator ()(const ::std::any& actual) const
    {
        const T* value = ::std::any_cast<T>(&actual);
        if( value == NULL )
        {
            return AssertionFailure() << WhichIs()
                << (actual.has_value() ? " (actual type does not match)" : " (empty)");
        }
        M matcher(m_matcher);
        const AssertionResult ar = CastToMatcher(matcher)(*value);
        if( ar )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs() << " (value = " << PrintToString(*value) << "): " << ar.message();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "AnyWith<" << detail::GetTypeNameProxy<T>::GetTypeName()
            << ">: " << PrintToString(m_matcher);
        return strm.str();
    }

private:
    M m_matcher;
};

#endif

#if IUTEST_HAS_CXX_HDR_VARIANT

/**
 * @brief   VariantWith matcher
*/
template<typename T, typename M>
class VariantWithMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit VariantWithMatcher(const M& matcher) : m_matcher(matcher) {}

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        if( !::std::holds_alternative<T>(actual) )
        {
            return AssertionFailure() << WhichIs() << " (actual index = " << actual.index() << ")";
        }
        M matcher(m_matcher);
        const AssertionResult ar = CastToMatcher(matcher)(::std::get<T>(actual));
        if( ar )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs() << " (actual index = " << actual.index()
            << ", value = " << PrintToString(::std::get<T>(actual)) << "): " << ar.message();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "VariantWith<" << detail::GetTypeNameProxy<T>::GetTypeName()
            << ">: " << PrintToString(m_matcher);
        return strm.str();
    }

private:
    M m_matcher;
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
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "is empty"; }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE { *os << "isn't empty"; }
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

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return ExplainSize(actual.size(), listener);
    }
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
    template<typename U, size_t SIZE>
    bool MatchAndExplain(const U(&)[SIZE], ::std::ostream* listener)
    {
        return ExplainSize(SIZE, listener);
    }
#endif

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Size is: " << m_expected;
        return strm.str();
    }
private:
    bool ExplainSize(size_t size, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        const bool matched = ExplainMatch(m_expected, size, &inner);
        if( !matched )
        {
            *listener << "whose size is " << size;
            if( !inner.str().empty() ) *listener << ", " << inner.str();
        }
        return matched;
    }
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
 * @brief   Maximum matching for an element-to-expectation bipartite graph
*/
class BipartiteMatcher
{
public:
    typedef ::std::vector< ::std::vector<bool> > Graph;

    static size_t FindMaximumMatching(const Graph& graph, size_t expected_count)
    {
        ::std::vector<size_t> matches(expected_count, graph.size());
        size_t count = 0;
        for( size_t i = 0; i < graph.size(); ++i )
        {
            ::std::vector<bool> visited(expected_count, false);
            if( Augment(graph, i, visited, matches) ) ++count;
        }
        return count;
    }

private:
    static bool Augment(const Graph& graph, size_t actual, ::std::vector<bool>& visited,
                        ::std::vector<size_t>& matches)
    {
        for( size_t i = 0; i < matches.size(); ++i )
        {
            if( !graph[actual][i] || visited[i] ) continue;
            visited[i] = true;
            if( matches[i] == graph.size() || Augment(graph, matches[i], visited, matches) )
            {
                matches[i] = actual;
                return true;
            }
        }
        return false;
    }
};

/**
 * @brief   IsSubsetOf matcher
*/
template<typename T>
class IsSubsetOfMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename It>
    IsSubsetOfMatcher(const It& begin, const It& end) : m_expected(begin, end) {}

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        ::std::ostringstream explanation;
        if( MatchAndExplain(actual, &explanation) ) return AssertionSuccess();
        return AssertionFailure() << WhichIs() << "\n" << explanation.str();
    }

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener) const
    {
        IUTEST_USING_BEGIN_END();
        return Check(begin(actual), end(actual), listener);
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return "IsSubsetOf: " + PrintToString(m_expected);
    }

private:
    template<typename It>
    bool Check(It begin, It end, ::std::ostream* listener) const
    {
        BipartiteMatcher::Graph graph;
        for( ; begin != end; ++begin )
        {
            graph.push_back(::std::vector<bool>(m_expected.size(), false));
            for( size_t i = 0; i < m_expected.size(); ++i )
            {
                ::std::ostringstream inner;
                T expected(m_expected[i]);
                graph.back()[i] = ExplainMatch(expected, *begin, &inner);
            }
        }
        if( graph.size() > m_expected.size() )
        {
            *listener << "whose element count " << graph.size()
                      << " exceeds the expected count " << m_expected.size();
            return false;
        }
        const size_t matched = BipartiteMatcher::FindMaximumMatching(graph, m_expected.size());
        if( matched == graph.size() ) return true;
        *listener << "whose elements cannot be matched to distinct expectations (matched "
                  << matched << " of " << graph.size() << " elements)";
        return false;
    }

private:
    ::std::vector<T> m_expected;
};

/**
 * @brief   AllOfArray / AnyOfArray matcher
*/
template<typename T, bool ALL>
class LogicalArrayMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    template<typename It>
    LogicalArrayMatcher(const It& begin, const It& end)
    {
        m_expected.insert(m_expected.end(), begin, end);
    }

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        ::std::ostringstream explanation;
        if( MatchAndExplain(actual, &explanation) ) return AssertionSuccess();
        return AssertionFailure() << WhichIs() << "\n" << explanation.str();
    }

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener) const
    {
        typename ExpectedMatchers::const_iterator it = m_expected.begin();
        for( size_t i = 0; it != m_expected.end(); ++it, ++i )
        {
            T expected(*it);
            ::std::ostringstream inner;
            if( ExplainMatch(expected, actual, &inner) != ALL )
            {
                if( ALL )
                {
                    *listener << "whose matcher #" << i << " doesn't match";
                    if( !inner.str().empty() ) *listener << ", " << inner.str();
                }
                return !ALL;
            }
        }
        if( !ALL ) *listener << "which matches none of the " << m_expected.size() << " matchers";
        return ALL;
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return (ALL ? "AllOfArray: " : "AnyOfArray: ") + PrintToString(m_expected);
    }

private:
    typedef ::std::list<T> ExpectedMatchers;
    ExpectedMatchers m_expected;
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
    static bool Explain(T& matchers, const U& actual, ::std::ostream* listener)
    {
        IUTEST_USING_BEGIN_END();
        const size_t size = ::std::distance(begin(actual), end(actual));
        if( size < tuples::tuple_size<T>::value )
        {
            *listener << "ElementsAre: argument[" << size << "] is less than "
                << tuples::tuple_size<T>::value << ", whose size is " << size;
            return false;
        }
        return ExplainElem<0, tuples::tuple_size<T>::value - 1>(begin(actual), end(actual), matchers, listener);
    }
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        IUTEST_USING_BEGIN_END();
        return Check<0, tuples::tuple_size<T>::value - 1>(begin(actual), end(actual), matchers);
    }
    template<int N, typename T>
    static ::std::string WhichIsT(const T& matchers)
    {
        ::std::string str = "ElementsAre: {";
        str += WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
        str += "}";
        return str;
    }
private:
    template<int N, int LAST, typename Ite, typename M>
    static bool ExplainElem(Ite it, Ite end, M& matchers, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        if( !ExplainMatch(tuples::get<N>(matchers), *it, &inner) )
        {
            *listener << WhichIsElem<N>(matchers, N) << ", whose element #" << N << " doesn't match";
            if( !inner.str().empty() ) *listener << ", " << inner.str();
            return false;
        }
        return ExplainNext<N, LAST>(++it, end, matchers, listener);
    }
    template<int N, int LAST, typename Ite, typename M>
    static typename detail::enable_if<N == LAST, bool>::type
    ExplainNext(Ite it, Ite end, M& matchers, ::std::ostream* listener)
    {
        int index = N + 1;
        for( ; it != end; ++it, ++index )
        {
            ::std::ostringstream inner;
            if( !ExplainMatch(tuples::get<N>(matchers), *it, &inner) )
            {
                *listener << WhichIsElem<N>(matchers, index) << ", whose element #"
                    << index << " doesn't match";
                if( !inner.str().empty() ) *listener << ", " << inner.str();
                return false;
            }
        }
        return true;
    }
    template<int N, int LAST, typename Ite, typename M>
    static typename detail::disable_if<N == LAST, bool>::type
    ExplainNext(Ite it, Ite end, M& matchers, ::std::ostream* listener)
    {
        return ExplainElem<N + 1, LAST>(it, end, matchers, listener);
    }
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
    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return Explain(m_matchers, actual, listener);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return ElementsAreMatcherBase::WhichIsT<0>(m_matchers);
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
        return ElementsAreMatcherBase::WhichIsT<0>(m_matchers);
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
    template<typename U>bool MatchAndExplain(const U& actual, ::std::ostream* listener) { \
        return Explain(m_matchers, actual, listener); }                                 \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                                 \
        return ElementsAreMatcherBase::WhichIsT<0>(m_matchers); }                       \
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

#if IUTEST_HAS_MATCHER_FIELDSARE

template<size_t N>
struct FieldsAreBindings;

template<>
struct FieldsAreBindings<0>
{
    template<typename T>
    static ::std::tuple<> Get(const T&)
    {
        static_assert(::std::is_empty<T>::value, "FieldsAre() requires an empty object");
        return ::std::tuple<>();
    }
    template<typename ...T>
    static ::std::tuple<> Get(const ::std::tuple<T...>&)
    {
        static_assert(sizeof...(T) == 0, "FieldsAre requires one matcher per field");
        return ::std::tuple<>();
    }
};

#define IIUT_DECL_FIELDSARE_BINDINGS(n)                                      \
    template<> struct FieldsAreBindings<n> {                                \
        template<typename T> static auto Get(const T& actual) {             \
            const auto& [IUTEST_PP_ENUM_PARAMS(n, field)] = actual;          \
            return ::std::tie(IUTEST_PP_ENUM_PARAMS(n, field));              \
        }                                                                   \
    }

IIUT_DECL_FIELDSARE_BINDINGS(1);
IIUT_DECL_FIELDSARE_BINDINGS(2);
IIUT_DECL_FIELDSARE_BINDINGS(3);
IIUT_DECL_FIELDSARE_BINDINGS(4);
IIUT_DECL_FIELDSARE_BINDINGS(5);
IIUT_DECL_FIELDSARE_BINDINGS(6);
IIUT_DECL_FIELDSARE_BINDINGS(7);
IIUT_DECL_FIELDSARE_BINDINGS(8);
IIUT_DECL_FIELDSARE_BINDINGS(9);
IIUT_DECL_FIELDSARE_BINDINGS(10);
IIUT_DECL_FIELDSARE_BINDINGS(11);
IIUT_DECL_FIELDSARE_BINDINGS(12);
IIUT_DECL_FIELDSARE_BINDINGS(13);
IIUT_DECL_FIELDSARE_BINDINGS(14);
IIUT_DECL_FIELDSARE_BINDINGS(15);
IIUT_DECL_FIELDSARE_BINDINGS(16);

#undef IIUT_DECL_FIELDSARE_BINDINGS

/**
 * @brief   FieldsAre matcher
*/
template<typename ...T>
class FieldsAreMatcher IUTEST_CXX_FINAL : public IMatcher
{
    static_assert(sizeof...(T) <= 16, "FieldsAre supports at most 16 fields");
public:
    explicit FieldsAreMatcher(const T&... matchers) : m_matchers(matchers...) {}

    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        const auto fields = FieldsAreBindings<sizeof...(T)>::Get(actual);
        return Check<0>(fields);
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "FieldsAre: {";
        Describe<0>(strm);
        strm << "}";
        return strm.str();
    }

private:
    template<size_t N, typename U>
    AssertionResult Check(const U& fields)
    {
        if constexpr( N == sizeof...(T) )
        {
            return AssertionSuccess();
        }
        else
        {
            const AssertionResult ar = CastToMatcher(::std::get<N>(m_matchers))(::std::get<N>(fields));
            if( !ar )
            {
                return AssertionFailure() << "FieldsAre: field #" << N << " does not match ("
                    << PrintToString(::std::get<N>(fields)) << "): " << ar.message();
            }
            return Check<N + 1>(fields);
        }
    }

    template<size_t N>
    void Describe(iu_global_format_stringstream& strm) const
    {
        if constexpr( N < sizeof...(T) )
        {
            if constexpr( N != 0 ) strm << ", ";
            strm << StreamableToString(::std::get<N>(m_matchers));
            Describe<N + 1>(strm);
        }
    }

    ::std::tuple<T...> m_matchers;
};

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

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return CheckExplain(actual, listener);
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
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener
        , typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return ExplainField(actual.*m_field, listener);
    }
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener
        , typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        if( !actual ) { *listener << "which is NULL"; return false; }
        return ExplainField(actual->*m_field, listener);
    }
#else
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual->*m_field));
    }
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener)
    {
        if( !actual ) { *listener << "which is NULL"; return false; }
        return ExplainField(actual->*m_field, listener);
    }
#endif
    template<typename U>
    bool ExplainField(const U& value, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        const bool matched = ExplainMatch(m_expected, value, &inner);
        if( !matched )
        {
            *listener << "whose field is " << PrintToString(value);
            if( !inner.str().empty() ) *listener << ", " << inner.str();
        }
        return matched;
    }

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

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return CheckExplain(actual, listener);
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
    // GCC 13 misdiagnoses this member-function call as an array-bounds violation.
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ >= 13
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener
        , typename detail::disable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        return ExplainProperty((actual.*m_property)(), listener);
    }
#if defined(__GNUC__) && !defined(__clang__) && __GNUC__ >= 13
#pragma GCC diagnostic pop
#endif
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener
        , typename detail::enable_if_t< detail::is_pointer<U> >::type*& = detail::enabler::value)
    {
        if( !actual ) { *listener << "which is NULL"; return false; }
        return ExplainProperty((actual->*m_property)(), listener);
    }
#else
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)((actual->*m_property)()));
    }
    template<typename U>
    bool CheckExplain(const U& actual, ::std::ostream* listener)
    {
        if( !actual ) { *listener << "which is NULL"; return false; }
        return ExplainProperty((actual->*m_property)(), listener);
    }
#endif
    template<typename U>
    bool ExplainProperty(const U& value, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        const bool matched = ExplainMatch(m_expected, value, &inner);
        if( !matched )
        {
            *listener << "whose property is " << PrintToString(value);
            if( !inner.str().empty() ) *listener << ", " << inner.str();
        }
        return matched;
    }

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
    ResultOfMatcher(F& func, const T& expected)
        : m_func(func), m_expected(expected), m_description(), m_has_description(false) {}
    ResultOfMatcher(const ::std::string& description, F& func, const T& expected)
        : m_func(func), m_expected(expected), m_description(description), m_has_description(true) {}

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
        strm << "Result of: ";
        if( m_has_description )
        {
            strm << m_description << " ";
        }
        strm << m_expected;
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
    ::std::string m_description;
    bool m_has_description;
};

inline int Base64Digit(char c)
{
    if( c >= 'A' && c <= 'Z' ) return c - 'A';
    if( c >= 'a' && c <= 'z' ) return c - 'a' + 26;
    if( c >= '0' && c <= '9' ) return c - '0' + 52;
    if( c == '+' || c == '-' ) return 62;
    if( c == '/' || c == '_' ) return 63;
    return -1;
}

inline bool Base64Unescape(const ::std::string& encoded, ::std::string* decoded)
{
    decoded->clear();
    const ::std::string::size_type size = encoded.size();
    ::std::string::size_type end = size;
    while( end > 0 && encoded[end - 1] == '=' ) --end;
    const ::std::string::size_type padding = size - end;
    const ::std::string::size_type remainder = end % 4;
    if( padding > 2 || remainder == 1 ||
        (padding != 0 && (size % 4 != 0 || padding + remainder != 4)) )
    {
        return false;
    }

    unsigned int bits = 0;
    int bit_count = 0;
    for( ::std::string::size_type i = 0; i < end; ++i )
    {
        const int digit = Base64Digit(encoded[i]);
        if( digit < 0 ) return false;
        bits = (bits << 6) | static_cast<unsigned int>(digit);
        bit_count += 6;
        if( bit_count >= 8 )
        {
            bit_count -= 8;
            decoded->push_back(static_cast<char>(bits >> bit_count));
            bits &= (1u << bit_count) - 1;
        }
    }
    return bits == 0;
}

/**
 * @brief   WhenBase64Unescaped matcher
*/
template<typename T>
class WhenBase64UnescapedMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit WhenBase64UnescapedMatcher(const T& expected) : m_expected(expected) {}

    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        ::std::string decoded;
        if( !Base64Unescape(MatcherStringValue(actual), &decoded) )
        {
            return AssertionFailure() << "invalid base64";
        }
        if( CastToMatcher(m_expected)(decoded) ) return AssertionSuccess();
        return AssertionFailure() << "decoded to " << ::iutest::PrintToString(decoded)
                                  << ", which does not match " << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "WhenBase64Unescaped: " << m_expected;
        return strm.str();
    }

private:
    T m_expected;
};

#if IUTEST_HAS_MATCHER_DISTANCEFROM
template<typename T, typename M>
class DistanceFromMatcherBase : public IMatcher
{
public:
    DistanceFromMatcherBase(const T& target, const M& matcher) : m_target(target), m_matcher(matcher) {}

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << m_matcher << " away from " << PrintToString(m_target);
        return strm.str();
    }

protected:
    template<typename D>
    AssertionResult CheckDistance(const D& distance) const
    {
        if( CastToMatcher(m_matcher)(distance) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << "which is " << PrintToString(distance)
            << " away from " << PrintToString(m_target);
    }

    T m_target;
    M m_matcher;
};

template<typename T, typename M>
class DistanceFromMatcher IUTEST_CXX_FINAL : public DistanceFromMatcherBase<T, M>
{
public:
    DistanceFromMatcher(const T& target, const M& matcher) : DistanceFromMatcherBase<T, M>(target, matcher) {}

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        using ::std::abs;
        return this->CheckDistance(abs(actual - this->m_target));
    }
};

template<typename T, typename F, typename M>
class DistanceFromFunctionMatcher IUTEST_CXX_FINAL : public DistanceFromMatcherBase<T, M>
{
public:
    DistanceFromFunctionMatcher(const T& target, const F& get_distance, const M& matcher)
        : DistanceFromMatcherBase<T, M>(target, matcher), m_get_distance(get_distance) {}

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
        return this->CheckDistance(m_get_distance(actual, this->m_target));
    }

private:
    F m_get_distance;
};
#endif

#if IUTEST_HAS_EXCEPTIONS
template<typename E>
class ThrowsMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE { return "Throws expected exception"; }

    template<typename F>
    AssertionResult operator ()(const F& actual) const
    {
        try
        {
            actual();
        }
        catch( const E& )
        {
            return AssertionSuccess();
        }
        catch( ... )
        {
            return AssertionFailure() << "threw an exception of a different type";
        }
        return AssertionFailure() << "did not throw an exception";
    }
};

template<typename E, typename M, bool message>
class ThrowsMatchingMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit ThrowsMatchingMatcher(const M& matcher) : m_matcher(matcher) {}

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << (message ? "ThrowsMessage: " : "Throws: ") << m_matcher;
        return strm.str();
    }

    template<typename F>
    AssertionResult operator ()(const F& actual) const
    {
        try
        {
            actual();
        }
        catch( const E& e )
        {
            if( Match(e) )
            {
                return AssertionSuccess();
            }
            return AssertionFailure() << "threw the expected exception, but its "
                << (message ? "message" : "value") << " did not match " << WhichIs();
        }
        catch( ... )
        {
            return AssertionFailure() << "threw an exception of a different type";
        }
        return AssertionFailure() << "did not throw an exception";
    }

private:
    bool Match(const E& e) const
    {
        return MatchImpl(e, iutest_type_traits::bool_constant<message>());
    }

    bool MatchImpl(const E& e, iutest_type_traits::false_type) const
    {
        return static_cast<bool>(CastToMatcher(m_matcher)(e));
    }

    bool MatchImpl(const E& e, iutest_type_traits::true_type) const
    {
        return static_cast<bool>(CastToMatcher(m_matcher)(e.what()));
    }

    M m_matcher;
};
#endif

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

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        if( IsNullPointer(actual) )
        {
            *listener << "which is NULL";
            return false;
        }
        ::std::ostringstream inner;
        const bool matched = ExplainMatch(m_expected, *actual, &inner);
        if( !matched )
        {
            *listener << "which points to " << PrintToString(*actual);
            if( !inner.str().empty() ) *listener << ", " << inner.str();
        }
        return matched;
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
    struct has_null_test
    {
        template<typename V>
        static char Check(char (*)[sizeof(!*((const V*)0))]);
        template<typename V>
        static long Check(...);
        enum { value = sizeof(Check<U>(0)) == sizeof(char) };
    };
    template<typename U>
    static bool IsNullPointer(const U& actual)
    {
        return CheckNull(actual, iutest_type_traits::bool_constant<has_null_test<U>::value>());
    }
    template<typename U, size_t N>
    static bool IsNullPointer(const U (&)[N]) { return false; }
    template<typename U>
    static bool CheckNull(const U& actual, iutest_type_traits::true_type) { return !actual; }
    template<typename U>
    static bool CheckNull(const U&, iutest_type_traits::false_type) { return false; }
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(*actual));
    }
private:
    T m_expected;
};

/**
 * @brief   Address matcher
*/
template<typename T>
class AddressMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit AddressMatcher(const T& expected) : m_expected(expected) {}

    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
#if IUTEST_HAS_CXX11
        const U* address = ::std::addressof(actual);
#else
        const U* address = reinterpret_cast<const U*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(actual)));
#endif
        if IUTEST_COND_LIKELY( CastToMatcher(m_expected)(address) )
        {
            return AssertionSuccess();
        }
        return AssertionFailure() << WhichIs();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "Address: " << m_expected;
        return strm.str();
    }
private:
    T m_expected;
};

/**
 * @brief   Reference identity matcher
*/
template<typename T>
class RefMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit RefMatcher(T& expected)
        : m_expected(
#if IUTEST_HAS_CXX11
            ::std::addressof(expected)
#else
            reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(expected)))
#endif
        ) {}

    template<typename U>
    AssertionResult operator ()(const U& actual) const
    {
#if IUTEST_HAS_CXX11
        const U* address = ::std::addressof(actual);
#else
        const U* address = reinterpret_cast<const U*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(actual)));
#endif
        if IUTEST_COND_LIKELY( static_cast<const volatile void*>(address)
            == static_cast<const volatile void*>(m_expected) )
        {
            return AssertionSuccess();
        }
        iu_global_format_stringstream strm;
        strm << const_cast<const void*>(static_cast<const volatile void*>(address));
        return AssertionFailure() << WhichIs() << "\nActual address: " << strm.str();
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        iu_global_format_stringstream strm;
        strm << "References address: "
            << const_cast<const void*>(static_cast<const volatile void*>(m_expected));
        return strm.str();
    }
private:
    T* m_expected;
};

/**
 * @brief   Pointer matcher
*/
template<typename T>
class PointerMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    explicit PointerMatcher(const T& expected) : m_expected(expected) {}

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
        strm << "Pointer: " << m_expected;
        return strm.str();
    }
private:
    template<typename U>
    bool Check(U* actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual));
    }
    template<typename U>
    bool Check(const U& actual)
    {
        return static_cast<bool>(CastToMatcher(m_expected)(actual.get()));
    }
private:
    T m_expected;
};

template<typename U, typename M>
#if IUTEST_HAS_CXX11 && IUTEST_HAS_DECLTYPE && !defined(IUTEST_NO_SFINAE)
typename iutest_type_traits::enable_if<is_gtest_matcher<M, U>::value, bool>::type
MatchForNot(const U& actual, M& matcher)
{
    ::std::ostringstream explanation;
    return matcher.MatchAndExplain(actual, &explanation);
}

template<typename U, typename M>
typename iutest_type_traits::disable_if<is_gtest_matcher<M, U>::value, bool>::type
#else
bool
#endif
MatchForNot(const U& actual, M& matcher)
{
    return static_cast<bool>(CastToMatcher(matcher)(actual));
}

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
        if IUTEST_COND_LIKELY( !MatchForNot(actual, m_unexpected) )
        {
            return AssertionSuccess();
        }
        ::std::ostringstream description;
        DescribeTo(&description);
        return AssertionFailure() << description.str();
    }

    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        if( !ExplainMatch(m_unexpected, actual, &inner) ) return true;
        *listener << "which matches";
        if( !inner.str().empty() ) *listener << ", " << inner.str();
        return false;
    }

public:
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        ::std::ostringstream description;
        DescribeTo(&description);
        return description.str();
    }
    void DescribeTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE
    {
        DescribeMatcherNegationTo(m_unexpected, os);
    }
    void DescribeNegationTo(::std::ostream* os) const IUTEST_CXX_OVERRIDE
    {
        DescribeMatcherTo(m_unexpected, os);
    }

private:
    T m_unexpected;
};

/**
 * @brief   Conditional matcher
*/
template<typename T1, typename T2>
class ConditionalMatcher IUTEST_CXX_FINAL : public IMatcher
{
public:
    ConditionalMatcher(bool condition, const T1& if_true, const T2& if_false)
        : m_condition(condition), m_if_true(if_true), m_if_false(if_false) {}

    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return m_condition ? CastToMatcher(m_if_true)(actual) : CastToMatcher(m_if_false)(actual);
    }

    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return m_condition ? CastToMatcher(m_if_true).WhichIs() : CastToMatcher(m_if_false).WhichIs();
    }

private:
    bool m_condition;
    T1 m_if_true;
    T2 m_if_false;
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
        if IUTEST_COND_LIKELY( Regex(MatcherStringValue(actual)) )
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
    static bool Explain(T& matchers, const U& actual, ::std::ostream* listener)
    {
        return Explain_<T, U, 0, tuples::tuple_size<T>::value - 1>(matchers, actual, listener);
    }
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
    }
    template<int N, typename T>
    static ::std::string WhichIsT(const T& matchers)
    {
        return WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
    }
private:
    template<typename T, typename U, int N, int LAST>
    static bool Explain_(T& matchers, const U& actual, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        if( !ExplainMatch(tuples::get<N>(matchers), actual, &inner) )
        {
            *listener << "whose matcher #" << N << " doesn't match";
            if( !inner.str().empty() ) *listener << ", " << inner.str();
            return false;
        }
        return ExplainNext<T, U, N, LAST>(matchers, actual, listener);
    }
    template<typename T, typename U, int N, int LAST>
    static typename detail::enable_if<N == LAST, bool>::type
    ExplainNext(T&, const U&, ::std::ostream*) { return true; }
    template<typename T, typename U, int N, int LAST>
    static typename detail::disable_if<N == LAST, bool>::type
    ExplainNext(T& matchers, const U& actual, ::std::ostream* listener)
    {
        return Explain_<T, U, N + 1, LAST>(matchers, actual, listener);
    }
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
    explicit AllOfMatcher(typename MatcherConstReference<T>::type... t) : m_matchers(t...) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return Explain(m_matchers, actual, listener);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AllOfMatcherBase::WhichIsT<0>(m_matchers);
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
    AllOfMatcher(const T0& m0, const T1& m1) : m_matchers(m0, m1) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AllOfMatcherBase::WhichIsT<0>(m_matchers);
    }
private:
    tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_MATCHER_CONST_REFERENCE_PARAM_(i, unused)                              \
    typename MatcherConstReference<IUTEST_PP_CAT(T, i)>::type                      \
        IUTEST_PP_CAT(m, i)

#define IIUT_DECL_ALLOF_MATCHER(n)                                                  \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                \
    class IUTEST_PP_CAT(AllOfMatcher, n) IUTEST_CXX_FINAL : public AllOfMatcherBase {   \
    public: IUTEST_PP_CAT(AllOfMatcher, n)(IUTEST_PP_ENUM(n, IIUT_MATCHER_CONST_REFERENCE_PARAM_, ~)) \
        : m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}                                \
    template<typename U>AssertionResult operator ()(const U& actual) {              \
        return Check(m_matchers, actual); }                                         \
    template<typename U>bool MatchAndExplain(const U& actual, ::std::ostream* listener) { \
        return Explain(m_matchers, actual, listener); }                             \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                             \
        return AllOfMatcherBase::WhichIsT<0>(m_matchers); }                         \
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
#undef IIUT_MATCHER_CONST_REFERENCE_PARAM_

#endif

/**
 * @brief   AnyOf matcher base class
*/
class AnyOfMatcherBase : public IMatcher
{
protected:
    template<typename T, typename U>
    static bool Explain(T& matchers, const U& actual, ::std::ostream* listener)
    {
        ::std::ostringstream failures;
        if( Explain_<T, U, 0, tuples::tuple_size<T>::value - 1>(matchers, actual, &failures) ) return true;
        *listener << failures.str();
        return false;
    }
    template<typename T, typename U>
    static AssertionResult Check(T& matchers, const U& actual)
    {
        return Check_<T, U, 0, tuples::tuple_size<T>::value-1>(matchers, actual);
    }
    template<int N, typename T>
    static ::std::string WhichIsT(const T& matchers)
    {
        return WhichIs_<T, N, tuples::tuple_size<T>::value-1>(matchers);
    }
private:
    template<typename T, typename U, int N, int LAST>
    static bool Explain_(T& matchers, const U& actual, ::std::ostream* listener)
    {
        ::std::ostringstream inner;
        if( ExplainMatch(tuples::get<N>(matchers), actual, &inner) ) return true;
        PrintSeparator<N>(listener);
        *listener << "matcher #" << N << " doesn't match";
        if( !inner.str().empty() ) *listener << ", " << inner.str();
        return ExplainNext<T, U, N, LAST>(matchers, actual, listener);
    }
    template<int N>
    static typename detail::enable_if<N == 0, void>::type PrintSeparator(::std::ostream*) {}
    template<int N>
    static typename detail::disable_if<N == 0, void>::type PrintSeparator(::std::ostream* listener)
    {
        *listener << "; ";
    }
    template<typename T, typename U, int N, int LAST>
    static typename detail::enable_if<N == LAST, bool>::type
    ExplainNext(T&, const U&, ::std::ostream*) { return false; }
    template<typename T, typename U, int N, int LAST>
    static typename detail::disable_if<N == LAST, bool>::type
    ExplainNext(T& matchers, const U& actual, ::std::ostream* listener)
    {
        return Explain_<T, U, N + 1, LAST>(matchers, actual, listener);
    }
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
    explicit AnyOfMatcher(typename MatcherConstReference<T>::type... t) : m_matchers(t...) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    template<typename U>
    bool MatchAndExplain(const U& actual, ::std::ostream* listener)
    {
        return Explain(m_matchers, actual, listener);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AnyOfMatcherBase::WhichIsT<0>(m_matchers);
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
    AnyOfMatcher(const T0& m0, const T1& m1) : m_matchers(m0, m1) {}

public:
    template<typename U>
    AssertionResult operator ()(const U& actual)
    {
        return Check(m_matchers, actual);
    }
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE
    {
        return AnyOfMatcherBase::WhichIsT<0>(m_matchers);
    }
private:
    tuples::tuple<T0, T1> m_matchers;
};
*/

#define IIUT_MATCHER_CONST_REFERENCE_PARAM_(i, unused)                              \
    typename MatcherConstReference<IUTEST_PP_CAT(T, i)>::type                      \
        IUTEST_PP_CAT(m, i)

#define IIUT_DECL_ANYOF_MATCHER(n)                                                  \
    template< IUTEST_PP_ENUM_PARAMS(n, typename T) >                                \
    class IUTEST_PP_CAT(AnyOfMatcher, n) IUTEST_CXX_FINAL : public AnyOfMatcherBase {   \
    public: IUTEST_PP_CAT(AnyOfMatcher, n)(IUTEST_PP_ENUM(n, IIUT_MATCHER_CONST_REFERENCE_PARAM_, ~)) \
        : m_matchers(IUTEST_PP_ENUM_PARAMS(n, m)) {}                                \
    template<typename U>AssertionResult operator ()(const U& actual) {              \
        return Check(m_matchers, actual); }                                         \
    template<typename U>bool MatchAndExplain(const U& actual, ::std::ostream* listener) { \
        return Explain(m_matchers, actual, listener); }                             \
    ::std::string WhichIs() const IUTEST_CXX_OVERRIDE {                             \
        return AnyOfMatcherBase::WhichIsT<0>(m_matchers); }                         \
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
#undef IIUT_MATCHER_CONST_REFERENCE_PARAM_

#endif

#endif

IUTEST_PRAGMA_ASSIGNMENT_OPERATOR_COULD_NOT_GENERATE_WARN_DISABLE_END()

}   // end of namespace detail

/**
 * @brief iutest matchers namespace
*/
namespace matchers
{

template<typename M, typename U>
bool ExplainMatchResult(M matcher, const U& actual, ::std::ostream* listener)
{
    return detail::ExplainMatch(matcher, actual, listener);
}

#if IUTEST_HAS_MATCHER_MACROS
template<typename M, typename U>
typename iutest_type_traits::enable_if<
    iutest_type_traits::is_base_of<detail::MatcherMacroBase, M>::value, bool>::type
ExplainMatchResult(M matcher, const U& actual, detail::MatcherMacroListener* listener)
{
    ::std::ostringstream ignored;
    return matcher.MatchAndExplain(actual, listener->IsInterested() ? listener->stream() : &ignored);
}

template<typename M, typename U>
typename iutest_type_traits::disable_if<
    iutest_type_traits::is_base_of<detail::MatcherMacroBase, M>::value, bool>::type
ExplainMatchResult(M matcher, const U& actual, detail::MatcherMacroListener* listener)
{
    ::std::ostringstream ignored;
    return detail::ExplainMatch(matcher, actual, listener->IsInterested() ? listener->stream() : &ignored);
}
#endif

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
 * @brief   Make IsTrue matcher
 * @details argument converts to true
*/
inline detail::IsTrueMatcher IsTrue()
{
    return detail::IsTrueMatcher();
}

/**
 * @brief   Make IsFalse matcher
 * @details argument converts to false
*/
inline detail::IsFalseMatcher IsFalse()
{
    return detail::IsFalseMatcher();
}

/**
 * @brief   Make IsNan matcher
 * @details argument is NaN
*/
inline detail::IsNanMatcher IsNan()
{
    return detail::IsNanMatcher();
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
detail::StrEqMatcher<const T&> StrEq(const T& expected)
{
    return detail::StrEqMatcher<const T&>(expected);
}

/**
 * @brief   Make StrNe matcher
 * @details argument != expected
*/
template<typename T>
detail::StrNeMatcher<const T&> StrNe(const T& expected)
{
    return detail::StrNeMatcher<const T&>(expected);
}

/**
 * @brief   Make StrCaseEq matcher
 * @details argument == expected (ignore case)
*/
template<typename T>
detail::StrCaseEqMatcher<const T&> StrCaseEq(const T& expected)
{
    return detail::StrCaseEqMatcher<const T&>(expected);
}

/**
 * @brief   Make StrCaseNe matcher
 * @details argument != expected (ignore case)
*/
template<typename T>
detail::StrCaseNeMatcher<const T&> StrCaseNe(const T& expected)
{
    return detail::StrCaseNeMatcher<const T&>(expected);
}

#define IIUT_DECL_STRING_VIEW_MATCHER(name) \
    inline detail::IUTEST_PP_CAT(name, Matcher)< ::std::string > name(detail::iu_string_view value) { \
        return detail::IUTEST_PP_CAT(name, Matcher)< ::std::string >(detail::MatcherStringValue(value)); \
    }

IIUT_DECL_STRING_VIEW_MATCHER(StrEq)
IIUT_DECL_STRING_VIEW_MATCHER(StrNe)
IIUT_DECL_STRING_VIEW_MATCHER(StrCaseEq)
IIUT_DECL_STRING_VIEW_MATCHER(StrCaseNe)
IIUT_DECL_STRING_VIEW_MATCHER(StartsWith)
IIUT_DECL_STRING_VIEW_MATCHER(HasSubstr)
IIUT_DECL_STRING_VIEW_MATCHER(EndsWith)

#undef IIUT_DECL_STRING_VIEW_MATCHER

#if IUTEST_HAS_CHAR8_T
#define IIUT_DECL_CHAR8_MATCHER(name) \
    inline detail::IUTEST_PP_CAT(name, Matcher)< ::std::string > name(const char8_t* value) { \
        return detail::IUTEST_PP_CAT(name, Matcher)< ::std::string >(detail::MatcherStringValue(value)); \
    } \
    inline detail::IUTEST_PP_CAT(name, Matcher)< ::std::string > name(char8_t* value) { \
        return detail::IUTEST_PP_CAT(name, Matcher)< ::std::string >(detail::MatcherStringValue(value)); \
    } \
    inline detail::IUTEST_PP_CAT(name, Matcher)< ::std::string > name(const ::std::u8string& value) { \
        return detail::IUTEST_PP_CAT(name, Matcher)< ::std::string >(detail::MatcherStringValue(value)); \
    }

IIUT_DECL_CHAR8_MATCHER(StrEq)
IIUT_DECL_CHAR8_MATCHER(StrNe)
IIUT_DECL_CHAR8_MATCHER(StrCaseEq)
IIUT_DECL_CHAR8_MATCHER(StrCaseNe)
IIUT_DECL_CHAR8_MATCHER(StartsWith)
IIUT_DECL_CHAR8_MATCHER(HasSubstr)
IIUT_DECL_CHAR8_MATCHER(EndsWith)

#undef IIUT_DECL_CHAR8_MATCHER

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
#define IIUT_DECL_CHAR8_VIEW_MATCHER(name) \
    inline detail::IUTEST_PP_CAT(name, Matcher)< ::std::string > name(::std::u8string_view value) { \
        return detail::IUTEST_PP_CAT(name, Matcher)< ::std::string >(detail::MatcherStringValue(value)); \
    }

IIUT_DECL_CHAR8_VIEW_MATCHER(StrEq)
IIUT_DECL_CHAR8_VIEW_MATCHER(StrNe)
IIUT_DECL_CHAR8_VIEW_MATCHER(StrCaseEq)
IIUT_DECL_CHAR8_VIEW_MATCHER(StrCaseNe)
IIUT_DECL_CHAR8_VIEW_MATCHER(StartsWith)
IIUT_DECL_CHAR8_VIEW_MATCHER(HasSubstr)
IIUT_DECL_CHAR8_VIEW_MATCHER(EndsWith)

#undef IIUT_DECL_CHAR8_VIEW_MATCHER
#endif
#endif

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
 * @brief   Make WhenBase64Unescaped matcher
 * @details argument を base64 デコードして expected にマッチする
*/
template<typename T>
detail::WhenBase64UnescapedMatcher<T> WhenBase64Unescaped(const T& expected)
{
    return detail::WhenBase64UnescapedMatcher<T>(expected);
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

#if IUTEST_HAS_CXX_HDR_ANY

/**
 * @brief   Make AnyWith matcher
 * @details Matches an any holding type T whose value matches matcher.
*/
template<typename T, typename M>
detail::AnyWithMatcher<T, M> AnyWith(M matcher)
{
    return detail::AnyWithMatcher<T, M>(matcher);
}

#endif

#if IUTEST_HAS_CXX_HDR_VARIANT

/**
 * @brief   Make VariantWith matcher
 * @details Matches a variant holding type T whose value matches matcher.
*/
template<typename T, typename M>
detail::VariantWithMatcher<T, M> VariantWith(M matcher)
{
    return detail::VariantWithMatcher<T, M>(matcher);
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
 * @brief   Make IsSubsetOf matcher
 * @details Each actual element must match a distinct expectation; unused expectations are allowed.
*/
template<typename Container>
detail::IsSubsetOfMatcher<typename Container::value_type> IsSubsetOf(const Container& container)
{
    return detail::IsSubsetOfMatcher<typename Container::value_type>(container.begin(), container.end());
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
/** @overload */
template<typename T, size_t SIZE>
detail::IsSubsetOfMatcher<T> IsSubsetOf(const T(&values)[SIZE])
{
    const T* first = values;
    return detail::IsSubsetOfMatcher<T>(first, first + SIZE);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/**
 * @overload
 * @note    Pass by value to decay arrays to pointers.
*/
template<typename It>
// @infer-ignore PULSE_CONST_REFABLE
detail::IsSubsetOfMatcher<typename detail::IteratorTraits<It>::type> IsSubsetOf(It begin, It end)
{
    return detail::IsSubsetOfMatcher<typename detail::IteratorTraits<It>::type>(begin, end);
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
detail::IsSubsetOfMatcher<T> IsSubsetOf(::std::initializer_list<T> values)
{
    return detail::IsSubsetOfMatcher<T>(values.begin(), values.end());
}
#endif
#endif

/**
 * @brief   Make AllOfArray matcher
 * @details Matches all expectations; an empty range always matches. Values are treated as Eq.
*/
template<typename Container>
detail::LogicalArrayMatcher<typename Container::value_type, true> AllOfArray(const Container& container)
{
    return detail::LogicalArrayMatcher<typename Container::value_type, true>(container.begin(), container.end());
}

/**
 * @brief   Make AnyOfArray matcher
 * @details Matches any expectation; an empty range never matches. Values are treated as Eq.
*/
template<typename Container>
detail::LogicalArrayMatcher<typename Container::value_type, false> AnyOfArray(const Container& container)
{
    return detail::LogicalArrayMatcher<typename Container::value_type, false>(container.begin(), container.end());
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
/** @overload */
template<typename T, size_t SIZE>
detail::LogicalArrayMatcher<T, true> AllOfArray(const T(&values)[SIZE])
{
    const T* first = values;
    return detail::LogicalArrayMatcher<T, true>(first, first + SIZE);
}

/** @overload */
template<typename T, size_t SIZE>
detail::LogicalArrayMatcher<T, false> AnyOfArray(const T(&values)[SIZE])
{
    const T* first = values;
    return detail::LogicalArrayMatcher<T, false>(first, first + SIZE);
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
/**
 * @overload
 * @note    Pass by value to decay arrays to pointers.
*/
template<typename It>
// @infer-ignore PULSE_CONST_REFABLE
detail::LogicalArrayMatcher<typename detail::IteratorTraits<It>::type, true> AllOfArray(It begin, It end)
{
    return detail::LogicalArrayMatcher<typename detail::IteratorTraits<It>::type, true>(begin, end);
}

/**
 * @overload
 * @note    Pass by value to decay arrays to pointers.
*/
template<typename It>
// @infer-ignore PULSE_CONST_REFABLE
detail::LogicalArrayMatcher<typename detail::IteratorTraits<It>::type, false> AnyOfArray(It begin, It end)
{
    return detail::LogicalArrayMatcher<typename detail::IteratorTraits<It>::type, false>(begin, end);
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST
/** @overload */
template<typename T>
detail::LogicalArrayMatcher<T, true> AllOfArray(::std::initializer_list<T> values)
{
    return detail::LogicalArrayMatcher<T, true>(values.begin(), values.end());
}

/** @overload */
template<typename T>
detail::LogicalArrayMatcher<T, false> AnyOfArray(::std::initializer_list<T> values)
{
    return detail::LogicalArrayMatcher<T, false>(values.begin(), values.end());
}
#endif
#endif

/** @overload */
template<typename T>
detail::LogicalArrayMatcher<T, true> AllOfArray(const T* values, size_t count)
{
    return detail::LogicalArrayMatcher<T, true>(values, count == 0 ? values : values + count);
}

/** @overload */
template<typename T>
detail::LogicalArrayMatcher<T, false> AnyOfArray(const T* values, size_t count)
{
    return detail::LogicalArrayMatcher<T, false>(values, count == 0 ? values : values + count);
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

#if IUTEST_HAS_MATCHER_FIELDSARE

/**
 * @brief   Match each field of an aggregate, tuple or pair
 * @details Requires C++17 structured bindings and one matcher per field (at most 16).
 *          Values are treated as equality matchers. Failure messages use zero-based field indices.
*/
template<typename ...T>
detail::FieldsAreMatcher<T...> FieldsAre(T... matchers)
{
    return detail::FieldsAreMatcher<T...>(matchers...);
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

template<typename F, typename T>
detail::ResultOfMatcher<F, T> ResultOf(const ::std::string& description, const F& func, const T& expected)
{
    return detail::ResultOfMatcher<F, T>(description, func, expected);
}

#if IUTEST_HAS_MATCHER_DISTANCEFROM
template<typename T, typename M>
detail::DistanceFromMatcher<T, M> DistanceFrom(const T& target, const M& matcher)
{
    return detail::DistanceFromMatcher<T, M>(target, matcher);
}

template<typename T, typename F, typename M>
detail::DistanceFromFunctionMatcher<T, F, M> DistanceFrom(const T& target, const F& get_distance, const M& matcher)
{
    return detail::DistanceFromFunctionMatcher<T, F, M>(target, get_distance, matcher);
}

template<typename T, typename R, typename A, typename B, typename M>
detail::DistanceFromFunctionMatcher<T, R (*)(A, B), M> DistanceFrom(
    const T& target, R (*get_distance)(A, B), const M& matcher)
{
    return detail::DistanceFromFunctionMatcher<T, R (*)(A, B), M>(target, get_distance, matcher);
}
#endif

#if IUTEST_HAS_EXCEPTIONS
template<typename E>
detail::ThrowsMatcher<E> Throws()
{
    return detail::ThrowsMatcher<E>();
}

template<typename E, typename M>
detail::ThrowsMatchingMatcher<E, M, false> Throws(const M& matcher)
{
    return detail::ThrowsMatchingMatcher<E, M, false>(matcher);
}

template<typename E, typename M>
detail::ThrowsMatchingMatcher<E, M, true> ThrowsMessage(const M& matcher)
{
    return detail::ThrowsMatchingMatcher<E, M, true>(matcher);
}
#endif

/**
 * @brief   Make Pointee matcher
*/
template<typename T>
detail::PointeeMatcher<T> Pointee(const T& expected)
{
    return detail::PointeeMatcher<T>(expected);
}

/**
 * @brief   Make Address matcher
*/
template<typename T>
detail::AddressMatcher<T> Address(const T& expected)
{
    return detail::AddressMatcher<T>(expected);
}

/**
 * @brief   Make Ref matcher
*/
template<typename T>
detail::RefMatcher<T> Ref(T& expected)
{
    return detail::RefMatcher<T>(expected);
}

/**
 * @brief   Make Pointer matcher
*/
template<typename T>
detail::PointerMatcher<T> Pointer(const T& expected)
{
    return detail::PointerMatcher<T>(expected);
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
 * @brief   Make Conditional matcher
 * @note    Pass by value to decay arrays (including string literals) to pointers.
*/
template<typename T1, typename T2>
// @infer-ignore PULSE_CONST_REFABLE
detail::ConditionalMatcher<T1, T2> Conditional(bool condition, T1 if_true, T2 if_false)
{
    return detail::ConditionalMatcher<T1, T2>(condition, if_true, if_false);
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
 * @brief   Make Any matcher (alias of A)
*/
template<typename T>
detail::AnyMatcher<T> An()
{
    return A<T>();
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
inline detail::RegexMatcher MatchesRegex(const char* str)
{
    return MatchesRegex(::std::string(str));
}
inline detail::RegexMatcher MatchesRegex(detail::iu_string_view str)
{
    return MatchesRegex(detail::MatcherStringValue(str));
}

/**
 * @brief   Make ContainsRegex matcher
*/
inline detail::RegexMatcher ContainsRegex(const ::std::string& str)
{
    return detail::RegexMatcher(detail::iuRegex(str), false);
}
inline detail::RegexMatcher ContainsRegex(const char* str)
{
    return ContainsRegex(::std::string(str));
}
inline detail::RegexMatcher ContainsRegex(detail::iu_string_view str)
{
    return ContainsRegex(detail::MatcherStringValue(str));
}

#if IUTEST_HAS_CHAR8_T
inline detail::RegexMatcher MatchesRegex(const char8_t* str)
{
    return MatchesRegex(detail::MatcherStringValue(str));
}
inline detail::RegexMatcher ContainsRegex(const char8_t* str)
{
    return ContainsRegex(detail::MatcherStringValue(str));
}
inline detail::RegexMatcher MatchesRegex(const ::std::u8string& str)
{
    return MatchesRegex(detail::MatcherStringValue(str));
}
inline detail::RegexMatcher ContainsRegex(const ::std::u8string& str)
{
    return ContainsRegex(detail::MatcherStringValue(str));
}
#if IUTEST_HAS_CXX_HDR_STRING_VIEW
inline detail::RegexMatcher MatchesRegex(::std::u8string_view str)
{
    return MatchesRegex(detail::MatcherStringValue(str));
}
inline detail::RegexMatcher ContainsRegex(::std::u8string_view str)
{
    return ContainsRegex(detail::MatcherStringValue(str));
}
#endif
#endif

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
