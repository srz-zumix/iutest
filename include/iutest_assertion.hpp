//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_assertion.hpp
 * @brief       iris unit test assertion 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_ASSERTION_HPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_
#define INCG_IRIS_IUTEST_ASSERTION_HPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_result.hpp"
#include "iutest_printers.hpp"
#include "internal/iutest_list.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// typedef
//! Message クラス
typedef detail::iuStreamMessage Message;

//======================================================================
// function
template<typename T>
inline ::std::string StreamableToString(const T& value)
{
    return (Message() << value).GetString();
}

//======================================================================
// declare
namespace detail
{

//! TestPartResultReporter がない場合の処理関数
void DefaultReportTestPartResult(const TestPartResult& test_part_result);

class UncaughtScopedTrace
{
public:
    static void Add(const detail::iuCodeMessage& msg);
    static bool Has();
    static ::std::string Get();
};

}   // end of namespace detail

//======================================================================
// class
/**
 * @brief   Assertion Result
*/
class AssertionResult
{
public:
    /**
     * @brief   コンストラクタ
     * @param [in] result = テスト結果真偽値
    */
    AssertionResult(bool result) : m_result(result) {}  // NOLINT
    //! コピーコンストラクタ
    AssertionResult(const AssertionResult& rhs) : m_message(rhs.m_message), m_result(rhs.m_result) {}

    /**
     * @brief   成否
    */
    bool failed() const IUTEST_CXX_NOEXCEPT_SPEC { return !m_result; }

    /**
     * @brief   成否
    */
    bool passed() const IUTEST_CXX_NOEXCEPT_SPEC { return m_result; }

    /**
     * @brief   メッセージの取得
    */
    const char* message() const { return m_message.c_str(); }

    /**
     * @brief   メッセージの取得
     * @deprecated please use message() instead.
    */
    const char* failure_message() const { return message(); }

    /** @private */
    IUTEST_CXX_EXPLICIT_CONVERSION operator bool() const { return m_result; }

public:
    /**
     * @brief   メッセージ追加
    */
    template<typename T>
    AssertionResult& operator << (const T& value)
    {
        Message msg;
        msg << value;
        m_message += msg.GetString();
        return *this;
    }
public:
    AssertionResult operator ! () const
    {
        return AssertionResult(failed()) << message();
    }
    AssertionResult operator && (const AssertionResult& rhs) const
    {
        return AssertionResult(m_result && rhs.passed()) << message() << " && " << rhs.message();
    }
    AssertionResult operator || (const AssertionResult& rhs) const
    {
        return AssertionResult(m_result || rhs.passed()) << message() << " || " << rhs.message();
    }

public:
    /**
     * @brief   成功結果の作成
    */
    static AssertionResult Success() { return AssertionResult(true); }
    /**
     * @brief   失敗結果の作成
    */
    static AssertionResult Failure() { return AssertionResult(false); }
    /**
     * @brief   成否の取得
    */
    template<typename T>
    static AssertionResult Is(const T& b) { return AssertionResult(b ? true : false); }
    /** @overload */
    static AssertionResult Is(const AssertionResult& ar) { return AssertionResult(ar); }

private:
    IUTEST_PP_DISALLOW_ASSIGN(AssertionResult);

    ::std::string m_message;
    bool m_result;
};

#if IUTEST_HAS_ASSERTION_RETURN
/**
 * @brief   Assetion Return Type
*/
template<typename R>
struct AssertionReturnType
{
    R value;    //!< 戻り値
    //! コンストラクタ
    AssertionReturnType() {}
    /**
     * @brief   コンストラクタ
     * @param [in]  v : 戻り値の値
    */
    AssertionReturnType(const R& v) : value(v) {}   // NOLINT
};
/**
 * @brief   Assetion Return Type (void)
*/
template<>
struct AssertionReturnType<void>
{
    //! コンストラクタ
    AssertionReturnType() {}
};

/**
 * @brief   Assetion Return 設定
*/
template<typename T>
inline AssertionReturnType<T> AssertionReturn(const T& ret) { return AssertionReturnType<T>(ret); }

/** @overload */
inline AssertionReturnType<void> AssertionReturn(void) { return AssertionReturnType<void>(); }

#endif

/**
 * @private
 * @brief   Assertion Helper
*/
class AssertionHelper
{
public:
    /**
     * @brief   コンストラクタ
     * @param [in]  file    = ファイル名
     * @param [in]  line    = 行番号
     * @param [in]  message = メッセージ
     * @param [in]  type    = テスト結果のタイプ
    */
    AssertionHelper(const char* file, int line, const char* message, TestPartResult::Type type)
        : m_part_result(file, line, message, type)
    {}
    /**
     * @brief   コンストラクタ
     * @param [in]  file    = ファイル名
     * @param [in]  line    = 行番号
     * @param [in]  message = メッセージ
     * @param [in]  type    = テスト結果のタイプ
    */
    AssertionHelper(const char* file, int line, const ::std::string& message, TestPartResult::Type type)
        : m_part_result(file, line, message.c_str(), type)
    {}

public:
    /** @private */
    class ScopedMessage
        : public detail::iuCodeMessage
#if IUTEST_USE_OWN_LIST
        , public detail::iu_list_node<ScopedMessage>
#endif
    {
    public:
        ScopedMessage(const detail::iuCodeMessage& msg) // NOLINT
            : detail::iuCodeMessage(msg)
        {
            ScopedTrace::GetInstance().list.push_back(this);
        }
        ~ScopedMessage()
        {
            ScopedTrace::GetInstance().list.remove(this);
            if( stl::uncaught_exception() )
            {
                detail::UncaughtScopedTrace::Add(*this);
            }
        }
    };
private:
    class ScopedTrace
    {
    public:
#if IUTEST_USE_OWN_LIST
        typedef detail::iu_list<ScopedMessage> msg_list;
#else
        typedef ::std::list<ScopedMessage*> msg_list;
#endif
        msg_list list;

        static ScopedTrace& GetInstance() { static ScopedTrace inst; return inst; }
    public:
        void append_message(TestPartResult& part_result, bool isException)
        {
            if( !list.empty() || detail::UncaughtScopedTrace::Has() )
            {
                part_result.add_message("\niutest trace:");
                // TODO : 追加メッセージとして保存するべき
                // 現状はテスト結果のメッセージに追加している。
                for( msg_list::iterator it = list.begin(), end=list.end(); it != end; ++it )
                {
                    part_result.add_message("\n");
                    part_result.add_message((*it)->make_message().c_str());
                }
                if( isException )
                {
                    part_result.add_message(detail::UncaughtScopedTrace::Get());
                }
            }
        }
    };

#if defined(IUTEST_NO_PRIVATE_IN_AGGREGATE)
    friend class ScopedMessage;
#endif

#if IUTEST_HAS_ASSERTION_RETURN
private:
    template<typename R>struct ReturnTypedFixed;
#endif

public:
    /** @private */
    class Fixed : public Message
    {
    public:
        template<typename T>
        Fixed& operator << (T val)
        {
            Message::operator << (val);
            return *this;
        }
        template<typename T, size_t SIZE>
        Fixed& operator << (const T(&val)[SIZE])
        {
            Message::operator << (val);
            return *this;
        }
#if IUTEST_HAS_IOMANIP
        Fixed& operator << (iu_basic_iomanip val)
        {
            Message::operator << (val);
            return *this;
        }
#endif
#if IUTEST_HAS_ASSERTION_RETURN
        Fixed& operator << (const AssertionReturnType<void>&)
        {
            return *this;
        }
        template<typename R>
        ReturnTypedFixed<R> operator << (const AssertionReturnType<R>& ret)
        {
            return ReturnTypedFixed<R>(*this, ret);
        }
#endif
    };

#if IUTEST_HAS_ASSERTION_RETURN
private:
    template<typename R>
    struct ReturnTypedFixed
    {
        Fixed fixed;
        AssertionReturnType<R> ret;
        ReturnTypedFixed(const Fixed& f, const AssertionReturnType<R>& r) : fixed(f), ret(r) {}
    };
#endif

public:
    /** @private */
    void operator = (const Fixed& fixed)
    {
        OnFixed(fixed);
#if IUTEST_HAS_EXCEPTIONS && IUTEST_USE_THROW_ON_ASSERTION_FAILURE
        {
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SWITCH_ENUM()
            switch( m_part_result.type() )
            {
            case TestPartResult::kSkip:
            case TestPartResult::kAssumeFailure:
            case TestPartResult::kFatalFailure:
                throw m_part_result.type();
            default:
                break;
            }
IUTEST_PRAGMA_WARN_POP()
        }
#endif
    }
#if IUTEST_HAS_ASSERTION_RETURN
    /** @private */
    template<typename R>
    R operator = (const ReturnTypedFixed<R>& fixed) // lgtm [cpp/assignment-does-not-return-this]
    {
        this->operator=(fixed.fixed);
        return fixed.ret.value;
    }
#endif

private:
    void OnFixed(const Fixed& fixed, bool isException = false)
    {
        // OnFixed で throw しないこと！テスト側の例外キャッチにかからなくなる
        const ::std::string append_message = fixed.GetString();
        if( !append_message.empty() )
        {
            m_part_result.add_message(" " + append_message);
        }
        ScopedTrace::GetInstance().append_message(m_part_result, isException);

        if( TestEnv::GetGlobalTestPartResultReporter() != IUTEST_NULLPTR )
        {
            TestEnv::GetGlobalTestPartResultReporter()->ReportTestPartResult(m_part_result);
        }
        else
        {
            detail::DefaultReportTestPartResult(m_part_result);
        }

        if IUTEST_COND_UNLIKELY(m_part_result.failed()
            && TestFlag::IsEnableFlag(iutest::TestFlag::BREAK_ON_FAILURE))
        {
            IUTEST_BREAK();
        }
    }

private:
    friend class TestInfo;
    TestPartResult m_part_result;

private:
    IUTEST_PP_DISALLOW_MOVE_AND_COPY_AND_ASSIGN(AssertionHelper);
};

}   // end of namespace iutest

namespace iutest
{

//======================================================================
// function
/**
 * @brief   テスト成功を示す AssertionResult オブジェクトの取得
*/
inline AssertionResult AssertionSuccess() { return AssertionResult::Success(); }
/**
 * @brief   テスト失敗を示す AssertionResult オブジェクトの取得
*/
inline AssertionResult AssertionFailure() { return AssertionResult::Failure(); }

/**
 * @brief   テスト結果のメッセージを取得する（for compatible）
*/
inline const char* GetAssertionResultMessage(const AssertionResult& ar)
{
    return ar.message();
}

namespace internal
{

/**
 * @brief   比較テストの値を文字列にフォーマット
*/
template<typename T1, typename T2>
inline ::std::string FormatForComparisonFailureMessage(const T1& value, const T2& /*other_operand*/)
{
    return PrintToString(value);
}

/**
 * @brief   boolean テストの失敗メッセージの出力
*/
inline ::std::string GetBooleanAssertionFailureMessage(const AssertionResult& ar
    , const char* expr, const char* actual, const char* expected)
{
    ::std::string str = "error: Value of: ";
    str += expr;
    str += "\n  Actual: ";
    str += actual;
    if( !detail::IsEmpty(ar.message()) )
    {
        str += " (";
        str += ar.message();
        str += ")";
    }
    str += "\nExpected: ";
    str += expected;
    return str;
}

/**
 * @brief   Eq 系アサーション
*/
inline AssertionResult EqFailure(const char* expected_expression, const char* actual_expression
    , const ::std::string& expected, const ::std::string& actual, bool ignoring_case = false)
{
    iu_global_format_stringstream strm;
    strm << "error: Value of " << actual_expression
        << "\n  Actual: " << actual
        << "\nExpected: " << expected_expression;
    if( ignoring_case )
    {
        strm << " (ignoring case)";
    }
    if( !detail::IsStringEqual(expected_expression, expected.c_str()) )
    {
        strm << "\nWhich is: " << expected;
    }
    return AssertionFailure() << strm.str();
}

template<typename T1, typename T2>
inline AssertionResult CmpHelperOpFailure(const char* expr1, const char* expr2, const char* op
    , const T1& val1, const T2& val2)
{
    return AssertionFailure() << "error: Expected: " << expr1 << " " << op << " " << expr2
        << "\n  Actual: " << FormatForComparisonFailureMessage(val1, val2)
        << " vs " << FormatForComparisonFailureMessage(val2, val1);
}

/**
 * @private
 * @{
 */

#define IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_BASE_(op_name, op)    \
    template<typename T1, typename T2>                              \
    bool iuOperator##op_name(const T1& v1, const T2& v2) {          \
        IUTEST_PRAGMA_WARN_PUSH()                                   \
        IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()          \
        return v1 op v2;                                            \
        IUTEST_PRAGMA_WARN_POP()                                    \
    }

#if IUTEST_HAS_CXX_HDR_VARIANT && IUTEST_HAS_VARIADIC_TEMPLATES
#define IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_VARIANT_(op_name, op)             \
    template<typename ...V1, typename ...V2>                                    \
    bool iuOperator##op_name(const ::std::variant<V1...>&& v1, const ::std::variant<V2...>& v2) {    \
        return v1 op v2;                                                        \
    }                                                                           \
    template<typename T1, typename ...V>                                        \
    bool iuOperator##op_name(const T1& v1, const ::std::variant<V...>& v2       \
        , typename detail::enable_if< !detail::is_variant<T1>::value, void>::type*& = detail::enabler::value ) {    \
        ::std::variant<V...> vv1(v1); return vv1 op v2;                         \
    }                                                                           \
    template<typename ...V, typename T2>                                        \
    bool iuOperator##op_name(const ::std::variant<V...>& v1, const T2& v2       \
        , typename detail::enable_if< !detail::is_variant<T2>::value, void>::type*& = detail::enabler::value ) {    \
        ::std::variant<V...> vv2(v2); return v1 op vv2;                         \
    }
#else
#define IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_VARIANT_(op_name, op)
#endif

#define IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_(op_name, op)     \
    IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_BASE_(op_name, op)    \
    IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_VARIANT_(op_name, op)

#define IIUT_DECL_COMPARE_HELPER_I_(op_name, op, type1, type2)                  \
    inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelper##op_name(         \
            const char* expr1, const char* expr2, type1 val1, type2 val2) {     \
        if IUTEST_COND_LIKELY(iuOperator##op_name(val1, val2)) { return AssertionSuccess();      \
        } else { return CmpHelperOpFailure(expr1, expr2, #op, val1, val2); }    \
    }

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

#define IIUT_DECL_COMPARE_HELPER_(op_name, op)                      \
    IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_(op_name, op)             \
    template<typename T1, typename T2>                              \
    IIUT_DECL_COMPARE_HELPER_I_(op_name, op, const T1&, const T2&)  \
    IIUT_DECL_COMPARE_HELPER_I_(op_name, op, BiggestInt, BiggestInt)

#else

#define IIUT_DECL_COMPARE_HELPER_(op_name, op)                      \
    IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_(op_name, op)             \
    template<typename T1, typename T2>                              \
    IIUT_DECL_COMPARE_HELPER_I_(op_name, op, const T1&, const T2&)

#endif

template<typename T1, typename T2>
bool iuOperatorEQ(const T1& v1, const T2& v2)
{
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()
IUTEST_PRAGMA_WARN_DISABLE_IMPLICIT_INT_FLOAT_CONVERSION()
    return v1 == v2;
IUTEST_PRAGMA_WARN_POP()
}
IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_VARIANT_(EQ, ==)

IIUT_DECL_COMPARE_HELPER_(NE, !=)
IIUT_DECL_COMPARE_HELPER_(LE, <=)
IIUT_DECL_COMPARE_HELPER_(LT, < )
IIUT_DECL_COMPARE_HELPER_(GE, >=)
IIUT_DECL_COMPARE_HELPER_(GT, > )


#undef IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_
#undef IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_BASE
#undef IIUT_DECL_COMPARE_HELPER_EXTEND_POINT_VARIANT
#undef IIUT_DECL_COMPARE_HELPER_I_
#undef IIUT_DECL_COMPARE_HELPER_

/**
 * @}
*/

/**
 * @brief   Null Helper
 * @tparam  IsNullLiteral   = val が NULL リテラルかどうか
*/
template<bool IsNullLiteral>
class NullHelper
{
public:
    template<typename T>
    static AssertionResult CompareEq(const char* expr, const T* val)
    {
        if IUTEST_COND_LIKELY( IUTEST_NULLPTR == val )
        {
            return AssertionSuccess();
        }

        return AssertionFailure() << "error: Value of " << expr
            << "\n  Actual: " << val
            << "\nExpected: NULL";
    }
    template<typename T>
    static AssertionResult CompareNe(const char* expr, const T* val)
    {
        if IUTEST_COND_LIKELY( IUTEST_NULLPTR != val )
        {
            return AssertionSuccess();
        }

        return AssertionFailure() << "error: Value of " << expr
            << "\n  Actual: NULL\nExpected: not NULL";
    }
};

/**
 * @brief   NullHelper 特殊化
*/
template<>
class NullHelper<true>
{
public:
    static AssertionResult CompareEq(const char*, void*)
    {
        return AssertionSuccess();
    }
    static AssertionResult CompareNe(const char* expr, void*)
    {
        return AssertionFailure() << "error: Value of " << expr
            << "\n  Actual: NULL\nExpected: not NULL";
    }
};

template<typename T1, typename T2>
inline AssertionResult CmpHelperSame(const char* expected_str, const char* actual_str
                                    , const T1& expected, const T2& actual)
{
    if IUTEST_COND_LIKELY( &expected == &actual )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: &(" << expected_str << ") == &(" << actual_str
        << ")\n  Actual: " << FormatForComparisonFailureMessage(&expected, &actual)
        << " vs " << FormatForComparisonFailureMessage(&actual, &expected);
}

template<typename T1, typename T2>
inline AssertionResult CmpHelperEQ(const char* expected_str, const char* actual_str
    , const T1& expected, const T2& actual)
{
    if IUTEST_COND_LIKELY( iuOperatorEQ(actual, expected) )
    {
        return AssertionSuccess();
    }

    return EqFailure(expected_str, actual_str
        , FormatForComparisonFailureMessage(expected, actual)
        , FormatForComparisonFailureMessage(actual, expected)
        );
}

template<typename T>
inline AssertionResult CmpHelperMemCmpEQ(const char* expected_str, const char* actual_str
    , const T& expected, const T& actual)
{
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()

    if IUTEST_COND_LIKELY( memcmp(&actual, &expected, sizeof(T)) == 0 )
    {
        return AssertionSuccess();
    }

    return EqFailure(expected_str, actual_str
        , FormatForComparisonFailureMessage(expected, actual)
        , FormatForComparisonFailureMessage(actual, expected)
        );

IUTEST_PRAGMA_WARN_POP()
}

template<typename T>
inline AssertionResult CmpHelperMemCmpNE(const char* expected_str, const char* actual_str
    , const T& expected, const T& actual)
{
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_SIGN_COMPARE()

    if IUTEST_COND_LIKELY( memcmp(&actual, &expected, sizeof(T)) != 0 )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: " << expected_str << " != " << actual_str
        << "\n  Actual: " << FormatForComparisonFailureMessage(expected, actual);

IUTEST_PRAGMA_WARN_POP()
}

template<typename RawType>
inline AssertionResult CmpHelperFloatingPointEQ(const char* expr1, const char* expr2
                                                , RawType val1, RawType val2)
{
    floating_point<RawType> f1(val1), f2(val2);
    if IUTEST_COND_LIKELY( f1.AlmostEquals(f2) )
    {
        return AssertionSuccess();
    }
    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(f1, f2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(f2, f1)));
}

template<typename RawType>
inline AssertionResult CmpHelperFloatingPointLE(const char* expr1, const char* expr2
                                                , RawType val1, RawType val2)
{
    if IUTEST_COND_LIKELY( val1 < val2 )
    {
        return AssertionSuccess();
    }
    floating_point<RawType> f1(val1), f2(val2);
    if IUTEST_COND_LIKELY( f1.AlmostEquals(f2) )
    {
        return AssertionSuccess();
    }
    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(f1, f2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(f2, f1)));
}

template<typename RawType>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , const ::std::complex<RawType>& val1, const ::std::complex<RawType>& val2)
{
    floating_point<RawType> real1(val1.real()), real2(val2.real());
    floating_point<RawType> imag1(val1.imag()), imag2(val2.imag());
    if IUTEST_COND_LIKELY( real1.AlmostEquals(real2) && imag1.AlmostEquals(imag2) )
    {
        return AssertionSuccess();
    }
    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)));
}

template<typename R1, typename R2>
inline AssertionResult CmpHelperFloatingPointComplexEQ(const char* expr1, const char* expr2
                                                , const ::std::complex<R1>& val1, const ::std::complex<R2>& val2)
{
    typedef typename detail::conditional<(sizeof(R1) > sizeof(R2)), R1, R2>::type RawType;
    return CmpHelperFloatingPointComplexEQ<RawType>(expr1, expr2, ::std::complex<RawType>(val1), ::std::complex<RawType>(val2));
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


/**
 * @brief   backward
*/
namespace backward
{

/**
 * @brief   Equal Helper
 * @tparam  IsNullLiteral   = val1 が NULL リテラルかどうか
*/
template<bool IsNullLiteral>
class EqHelper
{
#if IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT
    template<typename T, bool has_equal_to_operator>
    struct CmpHelper
    {
        static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
        {
            return CmpHelperEQ(expr1, expr2, val1, val2);
        }
    };
    template<typename T>
    struct CmpHelper<T, false>
    {
        static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
        {
            return CmpHelperMemCmpEQ(expr1, expr2, val1, val2);
        }
    };

public:
    template<typename T>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
    {
        return CmpHelper<T, detail::has_equal_to<T>::value>::Compare(expr1, expr2, val1, val2);
    }
#endif

public:
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return CmpHelperEQ(expr1, expr2, val1, val2);
    }
};

/**
 * @brief   EqHelper 特殊化
*/
template<>
class EqHelper<true>
{
public:
#if !defined(IUTEST_NO_SFINAE)
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2
        , typename detail::enable_if< !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value)
    {
        return CmpHelperEQ(expr1, expr2, val1, val2);
    }
    template<typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2
        , detail::IsNullLiteralHelper::Object* val1, T2* val2)
    {
        IUTEST_UNUSED_VAR(val1);
        return CmpHelperEQ(expr1, expr2, static_cast<T2*>(IUTEST_NULLPTR), val2);
    }
#else
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return CmpHelperEQ(expr1, expr2, (T2)(val1), val2); // NOLINT
    }
#endif
};

/**
 * @brief   Almost Equal Helper
 * @tparam  IsNullLiteral   = val1 が NULL リテラルかどうか
*/
template<bool IsNullLiteral>
class AlmostEqHelper : public EqHelper<false>
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

/**
 * @brief   EqHelper 特殊化
*/
template<>
class AlmostEqHelper<true> : public EqHelper<true>
{
};

/**
 * @brief   Not Equal Helper
 * @tparam  IsNullLiteral   = val1 が NULL リテラルかどうか
*/
template<bool IsNullLiteral>
class NeHelper
{
#if IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT
    template<typename T, bool has_not_equal_to_operator>
    struct CmpHelper
    {
        static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
        {
            return CmpHelperNE(expr1, expr2, val1, val2);
        }
    };
    template<typename T>
    struct CmpHelper<T, false>
    {
        static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
        {
            return CmpHelperMemCmpNE(expr1, expr2, val1, val2);
        }
    };

public:
    template<typename T>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T& val1, const T& val2)
    {
        return CmpHelper<T, detail::has_not_equal_to<T>::value>::Compare(expr1, expr2, val1, val2);
    }

#endif

public:
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return CmpHelperNE(expr1, expr2, val1, val2);
    }
};

/**
 * @brief   NeHelper 特殊化
*/
template<>
class NeHelper<true>
{
public:
#if !defined(IUTEST_NO_SFINAE)
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2
        , typename detail::enable_if< !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value)
    {
        return CmpHelperNE(expr1, expr2, val1, val2);
    }
    template<typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2
        , detail::IsNullLiteralHelper::Object* val1, T2* val2)
    {
        IUTEST_UNUSED_VAR(val1);
        return CmpHelperNE(expr1, expr2, static_cast<T2*>(IUTEST_NULLPTR), val2);
    }
#else
    template<typename T1, typename T2>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return CmpHelperNE(expr1, expr2, (T2)(val1), val2); // NOLINT
    }
#endif
};

}   // end of namespace backward

#if IUTEST_HAS_NULLPTR && IUTEST_HAS_CXX_HDR_TYPE_TARITS && 0

/**
 * @brief   Equal Helper
*/
class EqHelper
{
    template<typename T1, typename T2, typename detail::enable_if<
        !detail::is_integral<T1>::value || !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return backward::EqHelper<false>::Compare(expr1, expr2, val1, val2);
    }
    template<typename T>
    static AssertionResult Compare(const char* expr1, const char* expr2, ::std::nullptr_t, T* val2)
    {
        return CmpHelperEQ(expr1, expr2, static_cast<T*>(IUTEST_NULLPTR), val2);
    }
};

/**
 * @brief   Not Equal Helper
*/
class NeHelper
{
    template<typename T1, typename T2, typename detail::enable_if<
        !detail::is_integral<T1>::value || !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value>
    static AssertionResult Compare(const char* expr1, const char* expr2, const T1& val1, const T2& val2)
    {
        return backward::NeHelper<false>::Compare(expr1, expr2, val1, val2);
    }
    template<typename T>
    static AssertionResult Compare(const char* expr1, const char* expr2, ::std::nullptr_t, T* val2)
    {
        return CmpHelperNE(expr1, expr2, static_cast<T*>(IUTEST_NULLPTR), val2);
    }
};

#else

using backward::EqHelper;
using backward::AlmostEqHelper;
using backward::NeHelper;

#endif

template<typename RawType>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNearFloatingPoint(
    const char* expr1, const char* expr2, const char* absc
        , RawType val1, RawType val2, RawType abs_v)
{
    const RawType diff = val1 > val2 ? val1 - val2 : val2 - val1;
    if IUTEST_COND_LIKELY( diff < abs_v )
    {
        return AssertionSuccess();
    }
    floating_point<RawType> f1(diff), f2(abs_v);
    if IUTEST_COND_LIKELY( f1.AlmostEquals(f2) )
    {
        return AssertionSuccess();
    }
    return AssertionFailure() << "error: Value of: abs(" << expr1 << " - " << expr2 << ") <= " << absc
        << "\n  Actual: abs(" << val1 << " - " << val2 << ") : " << diff
        << "\nExpected: " << FormatForComparisonFailureMessage(abs_v, diff);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ DoubleNearPredFormat(
    const char* expr1, const char* expr2, const char* absc
        , double val1, double val2, double abs_v)
{
    return CmpHelperNearFloatingPoint(expr1, expr2, absc, val1, val2, abs_v);
}
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
template<typename T, typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(
    const char* expr1, const char* expr2, const char* absc
        , const T& val1, const T& val2, const A& abs_v)
{
    const T diff = val1 > val2 ? val1 - val2 : val2 - val1;
    if IUTEST_COND_LIKELY( diff <= abs_v )
    {
        return AssertionSuccess();
    }
    return AssertionFailure() << "error: Value of: abs(" << expr1 << " - " << expr2 << ") <= " << absc
        << "\n  Actual: abs(" << val1 << " - " << val2 << ") : " << diff
        << "\nExpected: " << FormatForComparisonFailureMessage(abs_v, diff);
}
template<typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(
    const char* expr1, const char* expr2, const char* absc
        , double val1, double val2, const A& abs_v)
{
    return CmpHelperNearFloatingPoint<double>(expr1, expr2, absc, val1, val2, static_cast<double>(abs_v));
}
#endif
template<typename A>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperNear(
    const char* expr1, const char* expr2, const char* absc
        , float val1, float val2, const A& abs_v)
{
    return CmpHelperNearFloatingPoint<float>(expr1, expr2, absc, val1, val2, static_cast<float>(abs_v));
}


namespace StrEqHelper
{

#if IUTEST_HAS_NULLPTR && 0
#define IIUT_DECL_STREQ_COMPARE_HELPER_NULL_(T)   \
    inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(::std::nullptr_t, const T* val2) {     \
        return val2 == IUTEST_NULLPTR;                                                  \
    }
#else
#define IIUT_DECL_STREQ_COMPARE_HELPER_NULL_(T)
#endif

#define IIUT_DECL_STREQ_COMPARE_HELPER_SV_(T)   \
    inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(detail::iu_nullable_basic_string_view<T> val1  \
        , detail::iu_nullable_basic_string_view<T> val2) {                                      \
        return val1 == val2;                                                                    \
    }                                                                                           \
    inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T* val1, const T* val2) {                \
        if( val1 == IUTEST_NULLPTR || val2 == IUTEST_NULLPTR ) { return val1 == val2; }         \
        return Compare(detail::iu_nullable_basic_string_view<T>(val1)                           \
            , detail::iu_nullable_basic_string_view<T>(val2));                                  \
    }

#define IIUT_DECL_STREQ_COMPARE_HELPER_(T)      \
    IIUT_DECL_STREQ_COMPARE_HELPER_SV_(T)       \
    IIUT_DECL_STREQ_COMPARE_HELPER_NULL_(T)

IIUT_DECL_STREQ_COMPARE_HELPER_(char)
IIUT_DECL_STREQ_COMPARE_HELPER_(wchar_t)
#if IUTEST_HAS_CHAR16_T
IIUT_DECL_STREQ_COMPARE_HELPER_(char16_t)
#endif
#if IUTEST_HAS_CHAR32_T
IIUT_DECL_STREQ_COMPARE_HELPER_(char32_t)
#endif

#undef IIUT_DECL_STREQ_COMPARE_HELPER_
#undef IIUT_DECL_STREQ_COMPARE_HELPER_SV_

}   // end of namespace StrEqHelper

template<typename T1, typename T2>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(
    const char* expr1, const char* expr2
    , T1 val1, T2 val2, typename detail::enable_if<
        !detail::is_integral<T1>::value || !detail::is_pointer<T2>::value, void>::type*& = detail::enabler::value)
{
    if IUTEST_COND_LIKELY( StrEqHelper::Compare(val1, val2) )
    {
        return AssertionSuccess();
    }

    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1)));
}

template<typename T>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTREQ(
    const char* expr1, const char* expr2
    , detail::iu_nullptr_convertible_t, T val2)
{
    if IUTEST_COND_LIKELY( StrEqHelper::Compare(IUTEST_NULLPTR, val2) )
    {
        return AssertionSuccess();
    }

    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(IUTEST_NULLPTR, val2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(val2, IUTEST_NULLPTR)));
}

namespace StrNeHelper
{

template<typename T1, typename T2>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T1& val1, const T2& val2)
{
    return !StrEqHelper::Compare(val1, val2);
}

}   // end of namespace StrNeHelper

template<typename T1, typename T2>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(
    const char* expr1, const char* expr2
    , T1 val1, T2 val2, typename detail::enable_if<
        ((!detail::is_integral<T2>::value || !detail::is_pointer<T1>::value) &&
        (!detail::is_integral<T1>::value || !detail::is_pointer<T2>::value)), void>::type*& = detail::enabler::value)
{
    if IUTEST_COND_LIKELY( StrNeHelper::Compare(val1, val2) )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
        << "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
        << " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}

template<typename T>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(
    const char* expr1, const char* expr2
    , detail::iu_nullptr_convertible_t, T val2)
{
    if IUTEST_COND_LIKELY( !StrEqHelper::Compare(IUTEST_NULLPTR, val2) )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
        << "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(val2, IUTEST_NULLPTR))
        << " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(IUTEST_NULLPTR, val2));
}

template<typename T>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRNE(
    const char* expr1, const char* expr2
    , T val1, detail::iu_nullptr_convertible_t)
{
    if IUTEST_COND_LIKELY( !StrEqHelper::Compare(val1, IUTEST_NULLPTR) )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2
        << "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(IUTEST_NULLPTR, val1))
        << " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage<T, T>(val1, IUTEST_NULLPTR));
}

namespace StrCaseEqHelper
{

inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const char* val1, const char* val2)
{
    if( val1 == IUTEST_NULLPTR || val2 == IUTEST_NULLPTR )
    {
        return val1 == val2;
    }
    return detail::iu_stricmp(val1, val2) == 0;
}

inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const wchar_t* val1, const wchar_t* val2)
{
    if( val1 == IUTEST_NULLPTR || val2 == IUTEST_NULLPTR )
    {
        return val1 == val2;
    }
    return detail::iu_wcsicmp(val1, val2) == 0;
}

template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(
    const ::std::basic_string<Elem, Traits, Ax>& val1
        , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return Compare(val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(
    const Elem* val1
        , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return Compare(val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(
    const ::std::basic_string<Elem, Traits, Ax>& val1
        , const Elem* val2)
{
    return Compare(val1.c_str(), val2);
}

template<typename T1, typename T2>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(
    const char* expr1, const char* expr2
        , const T1& val1, const T2& val2)
{
    if IUTEST_COND_LIKELY( Compare(val1, val2) )
    {
        return AssertionSuccess();
    }

    return EqFailure(expr1, expr2
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2))
        , detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
        , true);
}

}   // end of namespace StrCaseEqHelper

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(
    const char* expr1, const char* expr2
        , const char* val1, const char* val2)
{
    return StrCaseEqHelper::Assertion(expr1, expr2, val1, val2);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(
    const char* expr1, const char* expr2
        , const wchar_t* val1, const wchar_t* val2)
{
    return StrCaseEqHelper::Assertion(expr1, expr2, val1, val2);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(
    const char* expr1, const char* expr2
        , const ::std::basic_string<Elem, Traits, Ax>& val1
        , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(
    const char* expr1, const char* expr2
        , const Elem* val1, const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASEEQ(
    const char* expr1, const char* expr2
        , const ::std::basic_string<Elem, Traits, Ax>& val1, const Elem* val2)
{
    return CmpHelperSTRCASEEQ(expr1, expr2, val1.c_str(), val2);
}

namespace StrCaseNeHelper
{

template<typename T1, typename T2>
inline bool IUTEST_ATTRIBUTE_UNUSED_ Compare(const T1& val1, const T2& val2)
{
    return !StrCaseEqHelper::Compare(val1, val2);
}

template<typename T1, typename T2>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ Assertion(
    const char* expr1, const char* expr2
        , const T1& val1, const T2& val2)
{
    if IUTEST_COND_LIKELY( Compare(val1, val2) )
    {
        return AssertionSuccess();
    }

    return AssertionFailure() << "error: Expected: " << expr1 << " != " << expr2 << " (ignoring case)"
        << "\n  Actual: " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val2, val1))
        << " vs " << detail::ShowStringQuoted(FormatForComparisonFailureMessage(val1, val2));
}

}   // end of namespace StrCaseNeHelper

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(
    const char* expr1, const char* expr2
        , const char* val1, const char* val2)
{
    return StrCaseNeHelper::Assertion(expr1, expr2, val1, val2);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(
    const char* expr1, const char* expr2
        , const wchar_t* val1, const wchar_t* val2)
{
    return StrCaseNeHelper::Assertion(expr1, expr2, val1, val2);
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(
    const char* expr1, const char* expr2
        , const ::std::basic_string<Elem, Traits, Ax>& val1
        , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(
    const char* expr1, const char* expr2
        , const Elem* val1
        , const ::std::basic_string<Elem, Traits, Ax>& val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1, val2.c_str());
}
template<typename Elem, typename Traits, typename Ax>
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ CmpHelperSTRCASENE(
    const char* expr1, const char* expr2
        , const ::std::basic_string<Elem, Traits, Ax>& val1
        , const Elem* val2)
{
    return CmpHelperSTRCASENE(expr1, expr2, val1.c_str(), val2);
}

#if defined(IUTEST_OS_WINDOWS)

inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ IsHRESULTSuccess(const char* expr, HRESULT hr)
{
    if IUTEST_COND_LIKELY( SUCCEEDED(hr) )
    {
        return AssertionSuccess();
    }
    return AssertionFailure() << "error: Expected: SUCCEEDED(" << expr << ")"
        << "\n  Actual: " << hr << ": " << detail::win::GetHResultString(hr);
}
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ IsHRESULTFailure(const char* expr, HRESULT hr)
{
    if IUTEST_COND_LIKELY( FAILED(hr) )
    {
        return AssertionSuccess();
    }
    return AssertionFailure() << "error: Expected : FAILED(" << expr << ")"
        << "\n  Actual: " << hr;
}

#endif

}   // end of namespace internal

/**
 * @brief   Float LE Formatter
 * @note    IUTEST_ASSERT_PRED_FORMAT2(::iutest::FloatLE , 0, 1);
*/
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ FloatLE(
    const char* expr1, const char* expr2
        , float val1, float val2)
{
    return internal::CmpHelperFloatingPointLE<float>(expr1, expr2, val1, val2);
}

/**
 * @brief   Double LE Formatter
 * @note    IUTEST_ASSERT_PRED_FORMAT2(::iutest::DoubleLE , 0, 1);
*/
inline AssertionResult IUTEST_ATTRIBUTE_UNUSED_ DoubleLE(
    const char* expr1, const char* expr2
        , double val1, double val2)
{
    return internal::CmpHelperFloatingPointLE<double>(expr1, expr2, val1, val2);
}


}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_ASSERTION_HPP_E6AF3476_DA81_46F7_A961_ACCEF7363932_
