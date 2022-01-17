//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_internal.hpp
 * @brief       iris unit test internal definition
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_INTERNAL_HPP_A5BD9FBB_B57A_4C1D_B205_0ADB7798DBF9_
#define INCG_IRIS_IUTEST_INTERNAL_HPP_A5BD9FBB_B57A_4C1D_B205_0ADB7798DBF9_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_pred.hpp"
#include "../iutest_package.hpp"
// IWYU pragma: end_exports

#if defined(__clang_analyzer__)
#  include <assert.h>
#endif

//======================================================================
// define
/**
 * @private
 * @{
*/
#define IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)  IIUT_TEST_CLASS_NAME_I(IIUT_TO_VARNAME_(testsuite_), IIUT_TO_VARNAME_(testname_))
#define IIUT_TEST_CLASS_NAME_I(testsuite_, testname_)   IIUT_TEST_CLASS_NAME_I_(testsuite_, testname_)
#define IIUT_TEST_CLASS_NAME_I_(testsuite_, testname_)  iu_##testsuite_##_x_iutest_x_##testname_##_Test

#define IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_)   IIUT_TEST_INSTANCE_NAME_I(IIUT_TO_VARNAME_(testsuite_), IIUT_TO_VARNAME_(testname_))
#define IIUT_TEST_INSTANCE_NAME_I(testsuite_, testname_)    IIUT_TEST_INSTANCE_NAME_I_(testsuite_, testname_)
#define IIUT_TEST_INSTANCE_NAME_I_(testsuite_, testname_)   s_##testsuite_##_x_iutest_x_##testname_##_Instance

#if IUTEST_HAS_TESTNAME_ALIAS

#define IIUT_TO_VARNAME_(name_)                 IIUT_TO_VARNAME_I( (IIUT_ALIAS_TESTNAME_PP_##name_, name_, dummy_) )
#define IIUT_TO_VARNAME_I(tuple_)               IUTEST_PP_EXPAND( IIUT_TO_VARNAME_I_ tuple_ )
#define IIUT_TO_VARNAME_I_(dummy, name_, ...)   name_

#define IIUT_TO_NAME_(name_)                    IIUT_TO_NAME_I( (IIUT_ALIAS_TESTNAME_PP_##name_, name_, name_, dummy_) )
#define IIUT_TO_NAME_I(tuple_)                  IUTEST_PP_EXPAND( IIUT_TO_NAME_I_ tuple_ )
#define IIUT_TO_NAME_I_(d1_, d2_, name_, ...)   name_

#define IIUT_TO_NAME_STR_(name_)                IUTEST_PP_TOSTRING( IIUT_TO_NAME_(name_) )

#define IIUT_ALIAS_TESTNAME_PP_UNPAREN_(...)    __VA_ARGS__

#if defined(_MSC_VER) && !defined(__clang__)
#  define IUTEST_ALIAS_TESTNAME_(name_)         name_
#  define IUTEST_ALIAS_TESTNAME_F_(name_, var_) UNPAREN_(dummy, var_, name_)
#else
#  define IUTEST_ALIAS_TESTNAME_(name_)         UNPAREN_(dummy, IUTEST_PP_CAT(iutest_japanese_var, __LINE__), name_)
#  define IUTEST_ALIAS_TESTNAME_F_(name_, var_) UNPAREN_(dummy, var_, name_)
#endif

#else

#define IIUT_TO_VARNAME_(name_)     name_
#define IIUT_TO_NAME_(name_)        name_
#define IIUT_TO_NAME_STR_(name_)    #name_

#endif

#if IUTEST_HAS_IF_EXISTS
#  define IIUT_CHECK_TESTFIXTURE_I(testfixture_)        \
    IUTEST_IF_EXISTS(testfixture_, IUTEST_IF_EXISTS(testfixture_::SetUp,                \
        IUTEST_STATIC_ASSERT_MSG(                                                       \
            (!::iutest_type_traits::is_base_of< ::iutest::Test, testfixture_ >::value)  \
            , #testfixture_ " is fixture class, mistake the IUTEST_F?");                \
    ) )
#elif !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
#  define IIUT_CHECK_TESTFIXTURE_I(testfixture_)        \
    IUTEST_STATIC_ASSERT_MSG(                       \
            (! ::iutest::detail::is_useful_testfixture< void (int (testfixture_)) >::value) \
            , #testfixture_ " is fixture class, mistake the IUTEST_F?");
#else
#  define IIUT_CHECK_TESTFIXTURE_I(testfixture_)
#endif
#define IIUT_CHECK_TESTFIXTURE_(testfixture_)   IIUT_CHECK_TESTFIXTURE_I(testfixture_)
#define IIUT_CHECK_TESTFIXTURE(testfixture_)    IIUT_CHECK_TESTFIXTURE_(IIUT_TO_VARNAME_(testfixture_))

#if !defined(IUTEST_TEST_STRICT_)
#if IUTEST_CHECK_STRICT
#  define IUTEST_TEST_STRICT_(testsuite_, testname_, parent_class_, type_id_)   \
            IIUT_CHECK_TESTFIXTURE(testsuite_)                                  \
            IUTEST_TEST_(testsuite_, testname_, parent_class_, type_id_)
#else
#  define IUTEST_TEST_STRICT_   IUTEST_TEST_
#endif
#endif

#define IIUT_TEST_F_(macro, testfixture_, testname_)                            \
    macro(testfixture_, testname_, IIUT_TO_VARNAME_(testfixture_)               \
        , ::iutest::internal::GetTypeId< IIUT_TO_VARNAME_(testfixture_) >())

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

#define IIUT_TEST_F_A_(macro, testfixture_, testname_)                          \
    IIUT_TEST_F_( macro, IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testfixture_)  \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testfixture_, testname_)

#define IUTEST_TEST_F_(testfixture_, testname_)                                 \
    IIUT_TEST_F_A_(IUTEST_TEST_, testfixture_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TEST_F_IGNORE_(testfixture_, testname_)                          \
    IIUT_TEST_F_A_( IUTEST_TEST_IGNORE_, testfixture_, testname_)

#endif

#else

#define IUTEST_TEST_F_(testfixture_, testname_)                                 \
    IIUT_TEST_F_(IUTEST_TEST_, testfixture_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TEST_F_IGNORE_(testfixture_, testname_)                          \
    IIUT_TEST_F_( IUTEST_TEST_IGNORE_, testfixture_, testname_)

#endif

#endif

/**
 * @}
*/

/**
 * @internal
 * @brief   Test class defined macro
*/
#define IUTEST_TEST_(testsuite_, testname_, parent_class_, type_id_)                        \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testsuite_)) > 1, "testsuite_ must not be empty");   \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testname_)) > 1, "testname_ must not be empty");     \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(IIUT_TO_NAME_(testsuite_))) > 1, "testsuite alias name must not be empty");     \
    class IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) IUTEST_CXX_FINAL : public parent_class_ {          \
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_));     \
        public: IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)() {}                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;                                 \
    };                                                                                      \
    ::iutest::detail::TestInstance<IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)>          \
    IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_)(                                      \
        IUTEST_CONCAT_PACKAGE_(IIUT_TO_NAME_(testsuite_)), IIUT_TO_NAME_STR_(testname_)     \
        , type_id_, IUTEST_GET_SETUP_TESTSUITE(parent_class_, __FILE__, __LINE__)           \
        , IUTEST_GET_TEARDOWN_TESTSUITE(parent_class_, __FILE__, __LINE__));                \
    void IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)::Body()

#if IUTEST_HAS_IGNORE_TEST

/**
 * @internal
 * @brief   Test class defined macro
 *          関数の中はコンパイルできなくてもよい
*/
#define IUTEST_TEST_IGNORE_(testsuite_, testname_, parent_class_, type_id_)                 \
    class IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) IUTEST_CXX_FINAL : public parent_class_ {  \
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN( IUTEST_TEST_CLASS_NAME_(testsuite_, testname_) );   \
        public: IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)() {}                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }  \
        template<typename T>void Body();                                                    \
    };                                                                                      \
    ::iutest::detail::TestInstance<IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)>          \
    IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_)(                                      \
        IUTEST_CONCAT_PACKAGE_(IIUT_TO_NAME_(testsuite_)), IIUT_TO_NAME_STR_(testname_)     \
        , type_id_, IUTEST_GET_SETUP_TESTSUITE(parent_class_, __FILE__, __LINE__)           \
        , IUTEST_GET_TEARDOWN_TESTSUITE(parent_class_, __FILE__, __LINE__));                \
    template<typename T>void IUTEST_TEST_CLASS_NAME_(testsuite_, testname_ )::Body()

#endif

#if !defined(IUTEST_NO_VARIADIC_MACROS)

/**
 * @private
 * @{
*/
#define IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_)  IIUT_PMZ_TEST_CLASS_NAME_I(IIUT_TO_VARNAME_(testsuite_), IIUT_TO_VARNAME_(testname_))
#define IIUT_PMZ_TEST_CLASS_NAME_I(testsuite_, testname_)   IIUT_PMZ_TEST_CLASS_NAME_I_(testsuite_, testname_)
#define IIUT_PMZ_TEST_CLASS_NAME_I_(testsuite_, testname_)  IUTEST_PP_CAT( IUTEST_PP_CAT(iu_##testsuite_##_x_Test_, testname_), __LINE__)
/**
 * @}
*/

/**
 * @internal
 * @brief   Parameterized test class defined macro
*/
#define IIUT_TEST_PMZ_(testsuite_, testname_, method_, parent_class_, type_id_, ...)            \
    class IUTEST_TEST_CLASS_NAME_(testsuite_, testname_);                                       \
    class IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_) IUTEST_CXX_FINAL : public parent_class_ {  \
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_));     \
        public: IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_)() {}                         \
        static ::std::string MakeTestName() { return ::iutest::detail::MakeIndexTestName(       \
            IIUT_TO_NAME_STR_(testname_), ::iutest::detail::GetTypeUniqueCounter<               \
                IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)>()); }                           \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { method_(__VA_ARGS__); }            \
    };                                                                                          \
    ::iutest::detail::TestInstance<IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_)>          \
    IUTEST_PP_CAT( IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_), __LINE__)(                \
        IUTEST_CONCAT_PACKAGE_(IIUT_TO_NAME_(testsuite_))                                       \
        , IUTEST_PMZ_TEST_CLASS_NAME_(testsuite_, testname_)::MakeTestName().c_str()            \
        , #__VA_ARGS__, type_id_, IUTEST_GET_SETUP_TESTSUITE(parent_class_, __FILE__, __LINE__) \
        , IUTEST_GET_TEARDOWN_TESTSUITE(parent_class_, __FILE__, __LINE__))

#endif

/**
 * @internal
 * @brief   Assertion message
*/
#define IUTEST_MESSAGE_AT(file_, line_, msg_, result_type_) \
    ::iutest::AssertionHelper(file_, line_, msg_, result_type_) = ::iutest::AssertionHelper::Fixed()
#define IUTEST_MESSAGE(msg_, result_type_)                  \
    IUTEST_MESSAGE_AT(__FILE__, __LINE__, msg_, result_type_)

/**
 * @internal
 * @brief   ASSERT message
*/
#define IUTEST_ASSERT_FAILURE(msg)                  IUTEST_ASSERT_FAILURE_AT(msg, __FILE__, __LINE__)

#if !defined(IUTEST_NO_VOID_RETURNS)
#  define IUTEST_ASSERT_FAILURE_AT(msg, file, line) return IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kFatalFailure)
#else
#  define IUTEST_ASSERT_FAILURE_AT(msg, file, line) IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kFatalFailure)
#endif

/**
 * @internal
 * @brief   EXPECT message
*/
#define IUTEST_EXPECT_FAILURE(msg)                  IUTEST_EXPECT_FAILURE_AT(msg, __FILE__, __LINE__)

#define IUTEST_EXPECT_FAILURE_AT(msg, file, line)   IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kNonFatalFailure)

/**
 * @internal
 * @brief   INFORM message
*/
#define IUTEST_INFORM_FAILURE(msg)                  IUTEST_INFORM_FAILURE_AT(msg, __FILE__, __LINE__)

#define IUTEST_INFORM_FAILURE_AT(msg, file, line)   IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kWarning)

/**
 * @internal
 * @brief   ASSUME message
*/
#define IUTEST_ASSUME_FAILURE(msg)                  IUTEST_ASSUME_FAILURE_AT(msg, __FILE__, __LINE__)

#if !defined(IUTEST_NO_VOID_RETURNS)
#  define IUTEST_ASSUME_FAILURE_AT(msg, file, line) \
        return IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kAssumeFailure)
#else
#  define IUTEST_ASSUME_FAILURE_AT(msg, file, line) \
        IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kAssumeFailure)
#endif

/**
 * @internal
 * @brief   SKIP message
*/
#define IUTEST_SKIP_MESSAGE(msg)                    IUTEST_SKIP_MESSAGE_AT(msg, __FILE__, __LINE__)

#if !defined(IUTEST_NO_VOID_RETURNS)
#  define IUTEST_SKIP_MESSAGE_AT(msg, file, line)   \
        return IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kSkip)
#else
#  define IUTEST_SKIP_MESSAGE_AT(msg, file, line)   \
        IUTEST_MESSAGE_AT(file, line, msg, ::iutest::TestPartResult::kSkip)
#endif

#ifndef IUTEST_MAKE_ASSERTIONRESULT_
#  define IUTEST_MAKE_ASSERTIONRESULT_(ar)          ar
#endif

/**
 * @internal
 * @brief   比較検証マクロ
*/
#define IUTEST_TEST_ASSERT_(expression, on_failure) \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                  \
    if( const ::iutest::AssertionResult iutest_ar = IUTEST_MAKE_ASSERTIONRESULT_(expression) )  \
        ;                                           \
    else                                            \
        on_failure(iutest_ar.message())

#if IUTEST_HAS_EXCEPTIONS

#if IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION

#define IIUT_SEH_THROUGH(statement)    ::iutest::detail::seh_passthrough([&](){ (void)(statement); })

#else

#define IIUT_SEH_THROUGH(statement)    (void)(statement)

#endif

/**
 * @internal
 * @brief   throw assertion defined macro
*/
#define IUTEST_TEST_THROW_(statement, expected_exception, on_failure)       \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
    if( const char* msg = "" ) {                                            \
        try {                                                               \
            IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(IIUT_SEH_THROUGH(statement));  \
            msg = "\nExpected: " #statement " throws an exception of type " \
                #expected_exception ".\n  Actual: it throws nothing.";      \
            goto IUTEST_PP_CAT(iutest_label_throw, __LINE__);               \
        } catch( expected_exception const& ) {                              \
        } catch( ... ) {                                                    \
            msg = "\nExpected: " #statement " throws an exception of type " \
                #expected_exception ".\n  Actual: it throws a different type.";     \
            goto IUTEST_PP_CAT(iutest_label_throw, __LINE__);               \
        }                                                                   \
    } else                                                                  \
        IUTEST_PP_CAT(iutest_label_throw, __LINE__):                        \
        on_failure(msg)

/**
 * @internal
 * @brief   throw value assertion defined macro
*/
#define IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure, pred_formatter)   \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                                      \
    if( ::iutest::AssertionResult iutest_ar = ::iutest::AssertionSuccess() ) {          \
        try {                                                                           \
            IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(IIUT_SEH_THROUGH(statement));      \
            iutest_ar << "\nExpected: " #statement " throws an exception of type "      \
                #expected_exception ".\n  Actual: it throws nothing.";                  \
            goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);                     \
        } catch( expected_exception const& e) {                                         \
            if( const ::iutest::AssertionResult ar                                      \
                = pred_formatter("e", #expected_exception_value, e, expected_exception_value) ) {           \
            } else {                                                                    \
                iutest_ar << "\nExpected: " #statement " throws an exception of value\n" << ar.message();   \
                goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);                 \
            }                                                                           \
        } catch( ... ) {                                                                \
            iutest_ar << "\nExpected: " #statement " throws an exception of type "      \
                #expected_exception ".\n  Actual: it throws a different type.";         \
            goto IUTEST_PP_CAT(iutest_label_throw_value, __LINE__);                     \
        }                                                                               \
    } else                                                                              \
        IUTEST_PP_CAT(iutest_label_throw_value, __LINE__):                              \
        on_failure(iutest_ar.message())

#define IUTEST_TEST_THROW_VALUE_EQ_(statement, expected_exception, expected_exception_value, on_failure)    \
    IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure            \
        , ::iutest::internal::backward::EqHelper<IUTEST_IS_NULLLITERAL(expected_exception_value)>::Compare)
#define IUTEST_TEST_THROW_VALUE_NE_(statement, expected_exception, expected_exception_value, on_failure)    \
    IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure            \
        , ::iutest::internal::backward::NeHelper<IUTEST_IS_NULLLITERAL(expected_exception_value)>::Compare)
#define IUTEST_TEST_THROW_VALUE_STREQ_(statement, expected_exception, expected_exception_value, on_failure) \
    IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure            \
        , ::iutest::internal::CmpHelperSTREQ)
#define IUTEST_TEST_THROW_VALUE_STRCASEEQ_(statement, expected_exception, expected_exception_value, on_failure) \
    IUTEST_TEST_THROW_VALUE_(statement, expected_exception, expected_exception_value, on_failure                \
        , ::iutest::internal::CmpHelperSTRCASEEQ)

/**
 * @internal
 * @brief   any throw assertion defined macro
*/
#define IUTEST_TEST_ANY_THROW_(statement, on_failure)                       \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
    if( ::iutest::detail::AlwaysTrue() ) {                                  \
        try {                                                               \
            IIUT_SEH_THROUGH(statement);                                    \
            goto IUTEST_PP_CAT(iutest_label_anythrow, __LINE__);            \
        } catch( ... ) {                                                    \
        }                                                                   \
    } else                                                                  \
        IUTEST_PP_CAT(iutest_label_anythrow, __LINE__):                     \
        on_failure("\nExpected: " #statement " throws an exception.\n  Actual: it doesn's throws.")

/**
 * @internal
 * @brief   no throw assertion defined macro
*/
#define IUTEST_TEST_NO_THROW_(statement, on_failure)                        \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
    if( ::iutest::AssertionResult iutest_ar = ::iutest::AssertionSuccess() ) {  \
        try {                                                               \
            IIUT_SEH_THROUGH(statement);                                    \
        } catch( const ::std::exception& e ) {                              \
            iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws. what is \""  \
                << e.what() << "\"";                                        \
            goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);             \
        } catch( const char *e ) {                                          \
            iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws. \""  \
                << e << "\"";                                               \
            goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);             \
        } catch( ... ) {                                                    \
            iutest_ar << "\nExpected: " #statement " doesn't throw an exception.\n  Actual: it throws.";    \
            goto IUTEST_PP_CAT(iutest_label_nothrow, __LINE__);             \
        }                                                                   \
    } else                                                                  \
        IUTEST_PP_CAT(iutest_label_nothrow, __LINE__):                      \
        on_failure(iutest_ar.message())

#endif

#define IUTEST_TEST_BOOLEAN_(expression, text, actual, expected, on_failure)    \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                              \
    if( const ::iutest::AssertionResult iutest_ar = ::iutest::AssertionResult::Is(expression) ) \
        IUTEST_ATTRIBUTE_LIKELY_;                                               \
    else                                                                        \
        on_failure(::iutest::internal::GetBooleanAssertionFailureMessage(       \
            iutest_ar, text, #actual, #expected).c_str() )

/**
 * @internal
 * @brief   assert
*/
#define IUTEST_TERMINATE_ON_FAILURE(cond)   do { if IUTEST_COND_UNLIKELY( !(cond) ) {                           \
                                                IUTEST_MESSAGE(#cond, ::iutest::TestPartResult::kFatalFailure); \
                                                exit(1);                                                        \
                                            } } while(::iutest::detail::AlwaysFalse())

/**
 * @internal
 * @brief   明示的な成功
*/
#define IIUT_SUCCEED()                      IUTEST_MESSAGE("Succeeded.\n", ::iutest::TestPartResult::kSuccess)
/**
 * @internal
 * @brief   明示的な失敗
*/
#define IIUT_FAIL()                         IUTEST_ASSERT_FAILURE("Failed.\n")
#define IIUT_ADD_FAILURE()                  IUTEST_EXPECT_FAILURE("Failed.\n")
#define IIUT_ADD_FAILURE_AT(file_, line_)   IUTEST_EXPECT_FAILURE_AT("Failed.\n", file_, line_)

/**
 * @internal
 * @brief   メッセージロギング
*/
#define IIUT_SCOPED_MESSAGE(msg_)   \
    const ::iutest::AssertionHelper::ScopedMessage IUTEST_PP_CAT(scoped_message_, IUTEST_PP_COUNTER) =  \
            ::iutest::detail::iuCodeMessage(__FILE__, __LINE__, ::iutest::Message() << (msg_))

/**
 * @internal
 * @brief   IUTEST_ANALYSIS_ASSUME_ を通す
*/
#if IUTEST_HAS_ANALYSIS_ASSUME
#  define IUTEST_ANALYSIS_ASSUME_DELEGATE   IUTEST_ANALYSIS_ASSUME
#elif defined(__clang_analyzer__)
#  define IUTEST_ANALYSIS_ASSUME_DELEGATE   assert
#endif

#if defined(IUTEST_ANALYSIS_ASSUME_DELEGATE)
#define IUTEST_THROUGH_ANALYSIS_ASSUME_(expr, todo)                 \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                  \
    if( bool iu_b_ = true ) {                                       \
        IUTEST_UNUSED_VAR(iu_b_);                                   \
        IUTEST_ANALYSIS_ASSUME_DELEGATE(expr);                      \
        goto IUTEST_PP_CAT(iutest_label_analysis_assume, __LINE__); \
    } else                                                          \
        IUTEST_PP_CAT(iutest_label_analysis_assume, __LINE__):      \
        todo

#else

#define IUTEST_THROUGH_ANALYSIS_ASSUME_(expr, todo) todo

#endif

/**
 * @internal
 * @brief   all flavor assertion macro
 * @{
*/
#define IUTEST_TEST_EQ(expected, actual, on_failure)        \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::backward::EqHelper<IUTEST_IS_NULLLITERAL(expected)>::Compare    \
        , expected, actual, on_failure )

#define IUTEST_TEST_ALMOST_EQ(expected, actual, on_failure)        \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::backward::AlmostEqHelper<IUTEST_IS_NULLLITERAL(expected)>::Compare    \
        , expected, actual, on_failure )

#define IUTEST_TEST_NE(v1, v2, on_failure)                  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::backward::NeHelper<IUTEST_IS_NULLLITERAL(v1)>::Compare          \
        , v1, v2, on_failure )

#define IUTEST_TEST_LE(v1, v2, on_failure)                  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperLE   \
        , v1, v2, on_failure )

#define IUTEST_TEST_LT(v1, v2, on_failure)                  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperLT   \
        , v1, v2, on_failure )

#define IUTEST_TEST_GE(v1, v2, on_failure)                  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperGE   \
        , v1, v2, on_failure )

#define IUTEST_TEST_GT(v1, v2, on_failure)                  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperGT   \
        , v1, v2, on_failure )

#define IUTEST_TEST_TRUE(expr, text, on_failure)            \
    IUTEST_TEST_BOOLEAN_( expr, text, false, true, on_failure)

#define IUTEST_TEST_FALSE(expr, text, on_failure)           \
    IUTEST_TEST_BOOLEAN_( !(expr), text, true, false, on_failure)

#define IUTEST_TEST_FLOAT_EQ(expected, actual, on_failure)  \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointEQ<float>   \
        , expected, actual, on_failure )

#define IUTEST_TEST_DOUBLE_EQ(expected, actual, on_failure) \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointEQ<double>  \
        , expected, actual, on_failure )

#if IUTEST_HAS_LONG_DOUBLE

#define IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, on_failure) \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointEQ<long double>  \
        , expected, actual, on_failure )

#endif

#define IUTEST_TEST_COMPLEX_EQ(expected, actual, on_failure) \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperFloatingPointComplexEQ   \
        , expected, actual, on_failure )

#define IUTEST_TEST_NEAR(v1, v2, abs_v, on_failure)         \
    IUTEST_PRED_FORMAT3_( ::iutest::internal::CmpHelperNear \
        , v1, v2, abs_v, on_failure )

#define IUTEST_TEST_STREQ(expected, actual, on_failure)         \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTREQ    \
        , expected, actual, on_failure )

#define IUTEST_TEST_STRNE(v1, v2, on_failure)                   \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRNE    \
        , v1, v2, on_failure )

#define IUTEST_TEST_STRCASEEQ(expected, actual, on_failure)         \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRCASEEQ    \
        , expected, actual, on_failure )

#define IUTEST_TEST_STRCASENE(v1, v2, on_failure)                   \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSTRCASENE    \
        , v1, v2, on_failure )

#if defined(IUTEST_OS_WINDOWS)

#define IUTEST_TEST_HRESULT_SUCCEEDED(hr, on_failure)           \
    IUTEST_PRED_FORMAT1_( ::iutest::internal::IsHRESULTSuccess  \
        , hr, on_failure )

#define IUTEST_TEST_HRESULT_FAILED(hr, on_failure)              \
    IUTEST_PRED_FORMAT1_( ::iutest::internal::IsHRESULTFailure  \
        , hr, on_failure )

#endif

#define IUTEST_TEST_SAME(v1, v2, on_failure)                    \
    IUTEST_PRED_FORMAT2_( ::iutest::internal::CmpHelperSame     \
        , v1, v2, on_failure )

#define IUTEST_TEST_NULL(v, on_failure)                     \
    IUTEST_THROUGH_ANALYSIS_ASSUME_(v==IUTEST_NULLPTR       \
        , IUTEST_PRED_FORMAT1_( ::iutest::internal::NullHelper<IUTEST_IS_NULLLITERAL(v)>::CompareEq \
            , v, on_failure ))

#define IUTEST_TEST_NOTNULL(v, on_failure)                  \
    IUTEST_THROUGH_ANALYSIS_ASSUME_(v!=IUTEST_NULLPTR       \
        , IUTEST_PRED_FORMAT1_( ::iutest::internal::NullHelper<IUTEST_IS_NULLLITERAL(v)>::CompareNe \
            , v, on_failure ))

#define IUTEST_TEST_NO_FAILURE_(statement, on_failure)                      \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
    if( ::iutest::detail::AlwaysTrue() ) {                                  \
        ::iutest::detail::NewTestPartResultCheckHelper::Counter<            \
            ::iutest::detail::NewTestPartResultCheckHelper::CondGt<         \
            ::iutest::TestPartResult::kSuccess> > iutest_failure_checker;   \
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING( { (void)0; statement; } ) \
        if( iutest_failure_checker.count() > 0 ) {                          \
            goto IUTEST_PP_CAT(iutest_label_test_no_failure_, __LINE__);    \
        }                                                                   \
    } else                                                                  \
        IUTEST_PP_CAT(iutest_label_test_no_failure_, __LINE__):             \
        on_failure("\nExpected: " #statement " doesn't generate new failure.\n  Actual: it does.")

#define IUTEST_TEST_NO_FATAL_FAILURE_(statement, on_failure)                \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_                                          \
    if( ::iutest::detail::AlwaysTrue() ) {                                  \
        ::iutest::detail::NewTestPartResultCheckHelper::Counter<            \
            ::iutest::detail::NewTestPartResultCheckHelper::CondEq<         \
            ::iutest::TestPartResult::kFatalFailure> > iutest_failure_checker;  \
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING( { (void)0; statement; } ) \
        if( iutest_failure_checker.count() > 0 ) {                          \
            goto IUTEST_PP_CAT(iutest_label_test_no_fatalfailure_, __LINE__);   \
        }                                                                   \
    } else                                                                  \
        IUTEST_PP_CAT(iutest_label_test_no_fatalfailure_, __LINE__):        \
        on_failure("\nExpected: " #statement " doesn't generate new fatal failure.\n  Actual: it does.")

#define IUTEST_TEST_SKIP()                  \
    IUTEST_AMBIGUOUS_ELSE_BLOCKER_          \
    if( ::iutest::detail::AlwaysTrue() )    \
        IUTEST_SKIP_MESSAGE( ::iutest::UnitTest::SkipTest() ? "Skipped. " : "Skipped. but already failed. " )

/**
 * @}
*/

/**
 * @brief   コンパイルエラーチェックタグ
 * @param   e = error message regexp
*/
#if defined(_MSC_VER) && !defined(__clang__)
#  define IUTEST_TEST_COMPILEERROR(e)   \
    IUTEST_PRAGMA_MESSAGE(__FILE__ "(" IUTEST_PP_TOSTRING(__LINE__) "): note : " "IUTEST_TEST_COMPILEERROR( " e " )")
#else
#  define IUTEST_TEST_COMPILEERROR(e)   \
    IUTEST_PRAGMA_MESSAGE("IUTEST_TEST_COMPILEERROR( " e " )")
#endif

/**
 * @brief   static_assert チェックタグ
 * @param   e = error message regexp
 * @{
*/
#if IUTEST_HAS_STATIC_ASSERT
#  define IUTEST_TEST_STATICASSERT(e)   IUTEST_TEST_COMPILEERROR(e)
#else
#  define IUTEST_TEST_STATICASSERT(e)   IUTEST_TEST_COMPILEERROR("static_assert")
#endif
/**
 * @}
*/

#endif // INCG_IRIS_IUTEST_INTERNAL_HPP_A5BD9FBB_B57A_4C1D_B205_0ADB7798DBF9_
