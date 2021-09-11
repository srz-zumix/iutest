//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_cmphelper.hpp
 * @brief       compare helper for gtest
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_CMPHELPER_HPP_0378DF29_2DE7_4C60_8E12_32FEA8BEAA7C_
#define INCG_IRIS_IUTEST_SWITCH_CMPHELPER_HPP_0378DF29_2DE7_4C60_8E12_32FEA8BEAA7C_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define

#else // !defined(IUTEST_USE_GTEST)

namespace testing
{

namespace internal
{

#if GTEST_VER > 0x01080100 || GTEST_LATEST
using ::std::is_pointer;
using ::std::enable_if;
#else
using ::iutest_type_traits::enable_if;
#endif

template<typename RawType>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , const ::std::complex<RawType>& val1, const ::std::complex<RawType>& val2)
{
    AssertionResult real = CmpHelperFloatingPointEQ<RawType>(expr1, expr2, val1.real(), val2.real());
    AssertionResult imag = CmpHelperFloatingPointEQ<RawType>(expr1, expr2, val1.imag(), val2.imag());
    if( real && imag )
    {
        return real;
    }
    return EqFailure(expr1, expr2
        , FormatForComparisonFailureMessage(val1, val2).c_str()
        , FormatForComparisonFailureMessage(val2, val1).c_str()
        , true);
}

template<typename R1, typename R2>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , const ::std::complex<R1>& val1, const ::std::complex<R2>& val2)
{
    if( sizeof(R1) > sizeof(R2) )
    {
        return CmpHelperFloatingPointComplexEQ<R1>(expr1, expr2, val1, val2);
    }
    else
    {
        return CmpHelperFloatingPointComplexEQ<R2>(expr1, expr2, val1, val2);
    }
}

template<typename R1, typename R2>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , R1 val1, const ::std::complex<R2>& val2)
{
    return CmpHelperFloatingPointComplexEQ(expr1, expr2, ::std::complex<R2>(val1, R2()), val2);
}
template<typename R1, typename R2>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , const ::std::complex<R1>& val1, R2 val2)
{
    return CmpHelperFloatingPointComplexEQ(expr1, expr2, val1, ::std::complex<R1>(val2, R1()));
}

namespace backward
{

#if defined(GTEST_IS_NULL_LITERAL_)

template<bool lhs_is_null_literal>
class EqHelper : public internal::EqHelper<lhs_is_null_literal> {};

#else

template<bool lhs_is_null_literal>
class EqHelper : public internal::EqHelper {};

#endif

template<bool lhs_is_null_literal>
class NeHelper {
public:
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expected_expression,
        const char* actual_expression,
        const T1& expected,
        const T2& actual) {
            return CmpHelperNE(expected_expression, actual_expression, expected,
                actual);
    }

    static AssertionResult Compare(const char* expected_expression,
        const char* actual_expression,
        BiggestInt expected,
        BiggestInt actual) {
            return CmpHelperNE(expected_expression, actual_expression, expected,
                actual);
    }
};

template<>
class NeHelper<true> {
public:
    template<typename T1, typename T2>
    static AssertionResult Compare(
        const char* expected_expression,
        const char* actual_expression,
        const T1& expected,
        const T2& actual,
        typename enable_if<!is_pointer<T2>::value>::type* = 0) {
            return CmpHelperNE(expected_expression, actual_expression, expected,
                actual);
    }

    template<typename T>
    static AssertionResult Compare(
        const char* expected_expression,
        const char* actual_expression,
        Secret* /* expected (NULL) */,
        T* actual) {
            return CmpHelperNE(expected_expression, actual_expression,
                static_cast<T*>(NULL), actual);
    }
};

template<bool lhs_is_null_literal>
class AlmostEqHelper : public EqHelper<lhs_is_null_literal>
{
    struct CmpHelper
    {
        template<typename T1, typename T2>
        static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
        {
            return EqHelper<false>::Compare(expr1, expr2, val1, static_cast<T1>(val2));
        }
        template<typename T>
        static AssertionResult Compare(const char* expr1, const char* expr2, const float& val1, const T& val2)
        {
            return CmpHelperFloatingPointEQ<float>(expr1, expr2, val1, static_cast<float>(val2));
        }
        template<typename T>
        static AssertionResult Compare(const char* expr1, const char* expr2, const double& val1, const T& val2)
        {
            return CmpHelperFloatingPointEQ<double>(expr1, expr2, val1, static_cast<double>(val2));
        }
    };
public:
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return CmpHelper::Compare(expr1, expr2, val1, val2);
    }
    template<typename T, typename U>
    static AssertionResult Compare(const char* expr1, const char* expr2, const ::std::complex<T>& val1, const ::std::complex<U>& val2)
    {
        return CmpHelperFloatingPointComplexEQ(expr1, expr2, val1, val2);
    }
    template<typename T, typename U>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const ::std::complex<U>& val2)
    {
        return CmpHelperFloatingPointComplexEQ(expr1, expr2, val1, val2);
    }
    template<typename T, typename U>
    static AssertionResult Compare(const char* expr1, const char* expr2, const ::std::complex<T>& val1, const U& val2)
    {
        return CmpHelperFloatingPointComplexEQ(expr1, expr2, val1, val2);
    }
};

template<>
class AlmostEqHelper<true> : public EqHelper<true>
{
};

}   // end of namespace backward

template<typename T1, typename T2>
inline AssertionResult  CmpHelperSame(const char* expected_str, const char* actual_str
    , const T1& expected, const T2& actual)
{
    return ::testing::internal::backward::EqHelper<false>::Compare(expected_str, actual_str, &expected, &actual);
}

template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTREQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
    , const Elem* val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTREQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const Elem* val2)
{
    return CmpHelperSTREQ(expr1, expr2, val1.c_str(), val2);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRNE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
    , const Elem* val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRNE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const Elem* val2)
{
    return CmpHelperSTRNE(expr1, expr2, val1.c_str(), val2);
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
    , const wchar_t* val1, const wchar_t* val2)
{
    if( val1 == NULL || val2 == NULL )
    {
        if( val1 == val2 )
        {
            return AssertionSuccess();
        }
    }
    else
    {
        if( iu_wcsicmp(val1, val2) == 0 )
        {
            return AssertionSuccess();
        }
    }
    return EqFailure(expr1, expr2
        , FormatForComparisonFailureMessage(val1, val2).c_str()
        , FormatForComparisonFailureMessage(val2, val1).c_str()
        , true);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
    , const Elem* val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const Elem* val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2);
}

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
    , const wchar_t* val1, const wchar_t* val2)
{
    if( val1 == NULL || val2 == NULL )
    {
        if( val1 != val2 )
        {
            return AssertionSuccess();
        }
    }
    else
    {
        if( iu_wcsicmp(val1, val2) != 0 )
        {
            return AssertionSuccess();
        }
    }
    return AssertionFailure() << "error: Value of: " << expr1 << " != " << expr2
        << "\n  Actual: " << FormatForComparisonFailureMessage(val2, val1) << "\nExpected: " << FormatForComparisonFailureMessage(val1, val2);
}

template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
    , const Elem* val1
    , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(const char* expr1, const char* expr2
    , const ::std::basic_string<Elem, Traits, Ax>& val1
    , const Elem* val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2);
}

}   // end of namespace internal
}   // end of namespace testing

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_CMPHELPER_HPP_0378DF29_2DE7_4C60_8E12_32FEA8BEAA7C_
