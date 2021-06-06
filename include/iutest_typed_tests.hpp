//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_typed_tests.hpp
 * @brief       iris unit test typed test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_
#define INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "internal/iutest_typed_util.hpp"

#if IUTEST_HAS_TYPED_TEST_P
#  include "internal/iutest_pool.hpp"
#endif
// IWYU pragma: end_exports

//======================================================================
// define

#if IUTEST_HAS_TYPED_TEST
/**
 * @defgroup    TYPED_TEST  型付けテスト
*/

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_TYPED_TEST_SUITE(testsuite_, types_)
 * @brief   型付けTestSuite の登録
 * @param   testsuite_  = TestSuite 名
 * @param   ...         = タイプリスト
*/
#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IUTEST_TYPED_TEST_SUITE(testsuite_, ...)      IIUT_TYPED_TEST_SUITE_(testsuite_, __VA_ARGS__)
#else
#  define IUTEST_TYPED_TEST_SUITE(testsuite_, types_)   IIUT_TYPED_TEST_SUITE_(testsuite_, types_)
#endif

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_TYPED_TEST(testsuite_, testname_)
 * @brief   型付けテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST_TYPED_TEST(testsuite_, testname_)        IUTEST_TYPED_TEST_(testsuite_, testname_)

/**
 * @ingroup TYPED_TEST
 * @def     IUTEST_T(testsuite_, testname_)
 * @brief   型付けテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST_T(testsuite_, testname_)                 IUTEST_TYPED_TEST_(testsuite_, testname_)


/**
 * @private
 * @{
*/
#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
#define IIUT_TYPED_TEST_PARAMS_(testsuite_)                                          \
    IIUT_TYPED_TEST_PARAMS_I_( IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testsuite_)   \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testsuite_)
#else
#define IIUT_TYPED_TEST_PARAMS_(testsuite_)         IIUT_TYPED_TEST_PARAMS_I_(testsuite_)
#endif

#define IIUT_TYPED_TEST_PARAMS_I_(testsuite_)       IIUT_TYPED_TEST_PARAMS_II_(IIUT_TO_VARNAME_(testsuite_))
#define IIUT_TYPED_TEST_PARAMS_II_(testsuite_)      IIUT_TYPED_TEST_PARAMS_III_(testsuite_)
#define IIUT_TYPED_TEST_PARAMS_III_(testsuite_)     iutest_types_params_##testsuite_

#if !defined(IUTEST_NO_VARIADIC_MACROS)
#  define IIUT_TYPED_TEST_SUITE_(testsuite_, ...)       \
    typedef ::iutest::detail::TypeList< __VA_ARGS__ >::type IIUT_TYPED_TEST_PARAMS_(testsuite_)
#else
#  define IIUT_TYPED_TEST_SUITE_(testsuite_, types_)    \
    typedef ::iutest::detail::TypeList< types_ >::type  IIUT_TYPED_TEST_PARAMS_(testsuite_)
#endif

#define IIUT_TYPED_TEST_I(classname_, testsuite_, testsuitename_, testname_)        \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testsuite_)) > 1, "testsuite_ must not be empty");   \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testname_)) > 1, "testname_ must not be empty");     \
    template<typename iutest_TypeParam>                                             \
    class classname_ : public testsuite_<iutest_TypeParam> {                        \
        typedef testsuite_<iutest_TypeParam> TestFixture;                           \
        typedef iutest_TypeParam TypeParam;                                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;                         \
    };                                                                              \
    ::iutest::detail::TypeParamTestInstance< classname_, IIUT_TYPED_TEST_PARAMS_(testsuite_) >      \
        IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_)(                          \
        IUTEST_CONCAT_PACKAGE_(testsuitename_), IIUT_TO_NAME_STR_(testname_)        \
        , __FILE__, __LINE__);                                                      \
    template<typename iutest_TypeParam>                                             \
    void classname_<iutest_TypeParam>::Body()

#if IUTEST_HAS_IGNORE_TEST

#define IIUT_TYPED_TEST_I_IGNORE(classname_, testsuite_, testsuitename_, testname_) \
    template<typename iutest_TypeParam>                                             \
    class classname_ : public testsuite_<iutest_TypeParam> {                        \
        typedef testsuite_<iutest_TypeParam> TestFixture;                           \
        typedef iutest_TypeParam TypeParam;                                         \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }  \
        template<typename T>void Body();                                            \
    };                                                                              \
    ::iutest::detail::TypeParamTestInstance< classname_, IIUT_TYPED_TEST_PARAMS_(testsuite_) >      \
        IUTEST_TEST_INSTANCE_NAME_(testsuite_, testname_)(                          \
        IUTEST_CONCAT_PACKAGE_(testsuitename_), IIUT_TO_NAME_STR_(testname_)        \
        , __FILE__, __LINE__);                                                      \
    template<typename iutest_TypeParam> template<typename T>                        \
    void classname_<iutest_TypeParam>::Body()

#endif

#define IIUT_TYPED_TEST_(macro, testsuite_, testname_)                   \
    macro(IUTEST_TEST_CLASS_NAME_(testsuite_, testname_)                 \
        , IIUT_TO_VARNAME_(testsuite_), IIUT_TO_NAME_(testsuite_)        \
        , testname_)

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

#define IIUT_TYPED_TEST_A_(macro, testsuite_, testname_)                         \
    IIUT_TYPED_TEST_( macro, IUTEST_PP_IF( IUTEST_PP_IS_BEGIN_PARENS(testsuite_) \
        , IUTEST_ALIAS_TESTNAME_F_, IUTEST_PP_EMPTY() ) testsuite_, testname_)

#define IUTEST_TYPED_TEST_(testsuite_, testname_)           \
    IIUT_TYPED_TEST_A_(IIUT_TYPED_TEST_I, testsuite_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TYPED_TEST_IGNORE_(testsuite_, testname_)    \
    IIUT_TYPED_TEST_A_(IIUT_TYPED_TEST_I_IGNORE, testsuite_, testname_)

#endif

#else

#define IUTEST_TYPED_TEST_(testsuite_, testname_)           \
    IIUT_TYPED_TEST_(IIUT_TYPED_TEST_I, testsuite_, testname_)

#if IUTEST_HAS_IGNORE_TEST

#define IUTEST_TYPED_TEST_IGNORE_(testsuite_, testname_)    \
    IIUT_TYPED_TEST_(IIUT_TYPED_TEST_I_IGNORE, testsuite_, testname_)

#endif

#endif

/**
 * @}
*/

#endif

#if IUTEST_HAS_TYPED_TEST_P
/**
 * @defgroup    TYPE_PARAMETERIZED_TEST 型のパラメータ化テスト
*/

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TYPED_TEST_SUITE_P(testsuite_)
 * @brief   型パラメータTestSuite の登録
 * @param   testsuite_  = TestSuite 名
*/
#define IUTEST_TYPED_TEST_SUITE_P(testsuite_)           IIUT_TYPED_TEST_SUITE_P_(testsuite_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TYPED_TEST_P(testsuite_, testname_)
 * @brief   型パラメータテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST_TYPED_TEST_P(testsuite_, testname_)      IIUT_TYPED_TEST_P_(testsuite_, testname_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_TP(testsuite_, testname_)
 * @brief   型パラメータテスト関数定義マクロ
 * @param   testsuite_  = TestSuite 名
 * @param   testname_   = テスト名
*/
#define IUTEST_TP(testsuite_, testname_)                IIUT_TYPED_TEST_P_(testsuite_, testname_)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_REGISTER_TYPED_TEST_SUITE_P(testsuite_, ...)
 * @brief   型パラメータテスト関数登録マクロ
 * @param   testsuite_  = TestSuite 名
*/
#define IUTEST_REGISTER_TYPED_TEST_SUITE_P(testsuite_, ...)     \
    IIUT_REGISTER_TYPED_TEST_SUITE_P_(testsuite_, __VA_ARGS__)

/**
 * @ingroup TYPE_PARAMETERIZED_TEST
 * @def     IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(prefix_, testsuite_, types_)
 * @brief   型パラメータテスト登録マクロ
 * @param   prefix_     = インスタンス名
 * @param   testsuite_  = TestSuite 名
 * @param   ...         = タイプリスト
*/
#define IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(prefix_, testsuite_, ...) \
    IIUT_INSTANTIATE_TYPED_TEST_SUITE_P_(prefix_, testsuite_, __VA_ARGS__)


/**
 * @private
 * @{
*/

#define IIUT_TYPED_TEST_SUITE_PSTATE_NAME_(testsuite_)  s_iutest_typed_test_suite_p_state_##testsuite_##_
#define IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_)        iutest_typed_test_suite_p_name_##testsuite_##_
#define IIUT_TYPED_TEST_P_ADDTESTNAME(testsuite_, testname_)                            \
    static const int s_iutest_##testname_##_defined_dummy_  IUTEST_ATTRIBUTE_UNUSED_ =  \
    IIUT_TYPED_TEST_SUITE_PSTATE_NAME_(testsuite_).AddTestName(__FILE__, __LINE__, #testsuite_, #testname_)


#define IIUT_TYPED_TEST_SUITE_P_(testsuite_)    \
    static ::iutest::detail::TypedTestSuitePState IIUT_TYPED_TEST_SUITE_PSTATE_NAME_(testsuite_)

#define IIUT_TYPED_TEST_P_(testsuite_, testname_)               \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testsuite_)) > 1, "testsuite_ must not be empty");   \
    IUTEST_STATIC_ASSERT_MSG(sizeof(IUTEST_PP_TOSTRING(testname_)) > 1, "testname_ must not be empty");     \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_) {        \
    template<typename iutest_TypeParam>                         \
    class testname_ IUTEST_CXX_FINAL : public testsuite_<iutest_TypeParam> {     \
        typedef testsuite_<iutest_TypeParam> TestFixture;       \
        typedef iutest_TypeParam TypeParam;                     \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE;     \
    }; IIUT_TYPED_TEST_P_ADDTESTNAME(testsuite_, testname_);    \
    }                                                           \
    template<typename iutest_TypeParam>                         \
    void IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_)::testname_<iutest_TypeParam>::Body()

#if IUTEST_HAS_IGNORE_TEST

#define IIUT_TYPED_TEST_P_IGNORE_(testsuite_, testname_)        \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_) {        \
    template<typename iutest_TypeParam>                         \
    class testname_ IUTEST_CXX_FINAL : public testsuite_<iutest_TypeParam> {     \
        typedef testsuite_<iutest_TypeParam> TestFixture;       \
        typedef iutest_TypeParam TypeParam;                     \
        protected: virtual void Body() IUTEST_CXX_OVERRIDE { IUTEST_SKIP() << "ignored test..."; }  \
        template<typename T>void Body();                        \
    }; IIUT_TYPED_TEST_P_ADDTESTNAME(testsuite_, testname_);    \
    }                                                           \
    template<typename iutest_TypeParam>template<typename T>     \
    void IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_)::testname_<iutest_TypeParam>::Body()

#endif

#define IIUT_REGISTER_TYPED_TEST_SUITE_P_(testsuite_, ...)                                  \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_) {                                    \
        typedef ::iutest::detail::Templates< __VA_ARGS__ >::type iutest_AllTests_;          \
    }                                                                                       \
    static const bool s_iutest_##testsuite_##_register_dummy_ IUTEST_ATTRIBUTE_UNUSED_ =    \
    IIUT_TYPED_TEST_SUITE_PSTATE_NAME_(testsuite_).VerifyTestNames(__FILE__, __LINE__, #__VA_ARGS__)

#define IIUT_INSTANTIATE_TYPED_TEST_SUITE_P_(prefix_, testsuite_, ...)          \
    const bool iutest_##prefix_##_##testsuite_ IUTEST_ATTRIBUTE_UNUSED_ =       \
        ::iutest::detail::TypeParameterizedTestSuite< testsuite_                \
        , IIUT_TYPED_TEST_P_NAMESPACE_(testsuite_)::iutest_AllTests_            \
        , ::iutest::detail::TypeList< __VA_ARGS__ >::type >::Register(          \
            #prefix_, IIUT_TO_NAME_STR_(testsuite_), IUTEST_GET_PACKAGENAME_()  \
            , IIUT_TYPED_TEST_SUITE_PSTATE_NAME_(testsuite_).names(), __FILE__, __LINE__)

/**
 * @}
*/

#endif

namespace iutest
{

//======================================================================
// class
namespace detail
{

#if IUTEST_HAS_TYPED_TEST
/**
 * @private
 * @internal
 * @brief   Typeパラメータ単体テストインスタンス
 * @tparam  Tester      = テストクラス
 * @tparam  TypeParams  = 型
*/
template<template<typename T> class Tester, typename TypeParams>
class TypeParamTestInstance
{
    /**
     * @brief   各テストのインスタンス
    */
    template<typename TT, typename DMY>
    class EachTest
    {
        typedef typename TT::Head           TypeParam;
        typedef Tester<TypeParam>           TestBody;
        typedef TypedTestSuite<TypeParam>    _MyTestSuite;
    public:
        // コンストラクタ
        EachTest(const char* testsuite, const char* name, size_t index, const char* file, int line)
            : m_mediator(AddTestSuite(testsuite, index, file, line))
            , m_info(&m_mediator, name, &m_factory)
            , m_next(testsuite, name, index+1, file, line)
        {
        }
        EachTest(const ::std::string& testsuite, const char* name, size_t index, const char* file, int line)
            : m_mediator(AddTestSuite(testsuite, index, file, line))
            , m_info(&m_mediator, name, &m_factory)
            , m_next(testsuite, name, index+1, file, line)
        {
        }

    private:
        static TestSuite* AddTestSuite(const char* testsuite, size_t index, const char* file, int line)
        {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            return UnitTest::instance().AddTestSuite<_MyTestSuite>(
#else
            return UnitTest::instance().AddTestSuite(
#endif
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
                detail::MakeIndexTypedTestName<TypeParam>(testsuite, index)
#else
                detail::MakeIndexTestName(testsuite, index)
#endif
                , internal::GetTypeId<detail::None>()   // TypeId を統一するためダミー引数を渡す
                , IUTEST_GET_SETUP_TESTSUITE(TestBody, file, line)
                , IUTEST_GET_TEARDOWN_TESTSUITE(TestBody, file, line)
#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
                , detail::explicit_type<_MyTestSuite>()
#endif
                );
        }
        static TestSuite* AddTestSuite(const ::std::string& testsuite, size_t index, const char* file, int line)
        {
            return AddTestSuite(testsuite.c_str(), index, file, line);
        }

    public:
        // テストの登録
        void AddTest()
        {
            // 順番通りになるように前から登録
            UnitTest::instance().AddTestInfo(m_mediator.ptr(), &m_info);
            m_next.AddTest();
        }
    private:
        TestSuiteMediator           m_mediator;
        TestInfo                    m_info;
        detail::iuFactory<TestBody> m_factory;

        EachTest<typename TT::Tail, void> m_next;
    };

    // 終端
    template<typename DMY>
    class EachTest<detail::TypeList0, DMY>
    {
    public:
        EachTest(const char* /*testsuite*/, const char* /*name*/, size_t /*index*/, const char* /*file*/, int /*line*/) {}
        EachTest(const ::std::string& /*testsuite*/, const char* /*name*/, size_t /*index*/, const char* /*file*/, int /*line*/) {}
        void AddTest() {}
    };

public:
    // コンストラクタ
    TypeParamTestInstance(const char* testsuite, const char* name, const char* file, int line)
        : m_tests(testsuite, name, 0, file, line)
    {
        m_tests.AddTest();
    }
    TypeParamTestInstance(const std::string& testsuite, const char* name, const char* file, int line)
        : m_tests(testsuite, name, 0, file, line)
    {
        m_tests.AddTest();
    }

private:
    EachTest<TypeParams, void> m_tests;

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeParamTestInstance);
};

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @private
 * @internal
 * @brief   Typed TestSuite 設定保持
*/
class TypedTestSuitePState
{
#if IUTEST_TYPED_TEST_P_STRICT
    typedef ::std::set<const char*> nameset_t;
#endif

public:
    TypedTestSuitePState() : m_names(NULL) {}
public:
    const char* names() const { return m_names; }

public:
    bool AddTestName(const char* file, int line, const char* testsuite_name, const char* test_name)
    {
        if( m_names != NULL )
        {
            IUTEST_LOG_(WARNING) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" must be defined before IUTEST_REGISTER_TYPED_TEST_SUITE_P("
                << testsuite_name << ", ...).\n";
        }
#if IUTEST_TYPED_TEST_P_STRICT
        m_list.insert(test_name);
#endif
        return true;
    }
    bool VerifyTestNames(const char* file, int line, const char* test_names)
    {
        m_names = test_names;
        IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
#if IUTEST_TYPED_TEST_P_STRICT
        bool ret = true;
        for( nameset_t::iterator it=m_list.begin(), end=m_list.end(); it != end; ++it )
        {
            const char* test_name = *it;
            const char* p = strstr(test_names, test_name);
            if( p != NULL )
            {
                const size_t len = strlen(test_name);
                if( p[len] == '\0' || p[len] == ',' || detail::IsSpace(p[len]) )
                {
                    continue;
                }
                IUTEST_LOG_(FATAL) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" is find in \"" << test_names
                    << "\". expected whitespace or comma : " << p[len] << "(" << static_cast<int>(p[len]) <<  ")\n";
            }
            IUTEST_LOG_(WARNING) << detail::FormatCompilerIndependentFileLocation(file, line)
                << ": Test \"" << test_name << "\" has not been registered.\n" << "    TestNames: " << test_names;
            ret = false;
        }
        return ret;
#else
        IUTEST_UNUSED_VAR(file);
        IUTEST_UNUSED_VAR(line);
        return true;
#endif
        IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
    }

private:
    const char* m_names;

#if IUTEST_TYPED_TEST_P_STRICT
    nameset_t m_list;
#endif

    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypedTestSuitePState);
};

/**
 * @private
 * @brief   型パラメータテストのインスタンス化クラス
*/
template<template<typename T> class Fixture, typename Tests, typename Types>
class TypeParameterizedTestSuite
{
    template<typename TypeParam, typename TestsList>
    class EachTest : public iuIObject
    {
        typedef typename TestsList::Head        TypeSel;
        typedef typename TypeSel::template bind<TypeParam>::type    TestBody;
        typedef detail::iuFactory<TestBody>     Factory;
        typedef EachTest<TypeParam, TestsList>  _Myt;

        EachTest(TestSuite* testsuite, const ::std::string& name)
            : m_mediator(testsuite)
            , m_info(&m_mediator, name, &m_factory)
        {
            UnitTest::instance().AddTestInfo(testsuite, &m_info);
        }
    public:
        // テストの登録
        static void Register(TestSuite* testsuite, const char* test_names)
        {
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
            IUTEST_CHECK_(test_names != NULL);
            const char* str = detail::SkipSpace(test_names);
            const char* comma = strchr(str, ',');
            ::std::string test_name;
            if( comma == NULL )
            {
                test_name = str;
            }
            else
            {
                test_name = ::std::string(str, static_cast<size_t>(comma - str));
                ++comma;
            }
            _Myt* test = new EachTest(testsuite, StripTrailingSpace(test_name));
            // new オブジェクトを管理してもらう
            detail::iuPool::GetInstance().push(test);

            EachTest<TypeParam, typename TestsList::Tail>::Register(testsuite, detail::SkipSpace(comma));
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
        }
    private:
        TestSuiteMediator    m_mediator;
        Factory             m_factory;
        TestInfo            m_info;
    };

    template<typename TypeParam>
    class EachTest<TypeParam, detail::TemplateTypeList0>
    {
    public:
        static void Register(TestSuite* /*testsuite*/, const char* /*test_names*/) {}
    };

public:
    /**
     * @brief   テストの登録
    */
    static bool Register(const char* prefix, const char* testsuite_name
        , const ::std::string& package_name, const char* names
        , const char* file, int line
        , size_t index=0)
    {
#if IUTEST_HAS_EXCEPTIONS
        try
        {
            return Register_(prefix, testsuite_name, package_name, names, file, line, index);
        }
        catch (const ::std::exception& e)
        {
            IUTEST_LOG_(FATAL) << "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed... (what: "
                << e.what() << ")\n";
        }
        catch(...)
        {
            IUTEST_LOG_(FATAL) << "IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P register tests failed...\n";
        }
        return false;
#else
        return Register_(prefix, testsuite_name, package_name, names, file, line, index);
#endif
    }

private:
    static bool Register_(const char* prefix, const char* testsuite_name
        , const ::std::string& package_name, const char* names
        , const char* file, int line
        , size_t index)
    {
        typedef typename Types::Head        TypeParam;
        typedef typename Tests::Head        Head;
        typedef Fixture<Head>               FixtureClass;
        typedef TypedTestSuite<TypeParam>   _MyTestSuite;
        ::std::string full_testsuite_name = package_name;
        full_testsuite_name +=
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
            detail::MakePrefixedIndexTypedTestName<TypeParam>(prefix, testsuite_name, index);
#else
            detail::MakePrefixedIndexTestName(prefix, testsuite_name, index);
#endif
        TestSuite* testsuite =
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            UnitTest::instance().AddTestSuite<_MyTestSuite>(
#else
            UnitTest::instance().AddTestSuite(
#endif
            full_testsuite_name
            , internal::GetTypeId<FixtureClass>()
            , IUTEST_GET_SETUP_TESTSUITE(FixtureClass, file, line)
            , IUTEST_GET_TEARDOWN_TESTSUITE(FixtureClass, file, line)
#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
            , detail::explicit_type<_MyTestSuite>()
#endif
            );

        EachTest<TypeParam, Tests>::Register(testsuite, names);

        return TypeParameterizedTestSuite<Fixture, Tests, typename Types::Tail>::Register(
            prefix, testsuite_name, package_name, names, file, line, index + 1);
    }
};

/**
 * @private
 * @brief   型パラメータテストのインスタンス化クラス
 *          終端特殊化
*/
template<template<typename T> class Fixture, typename Tests>
class TypeParameterizedTestSuite<Fixture, Tests, detail::TypeList0>
{
public:
    static bool Register(const char* /*prefix*/, const char* /*testsuite_name*/
        , const ::std::string& /*package_name*/, const char* /*names*/
        , const char* /*file*/, int /*line*/
        , size_t /*index*/=0)
    {
        return true;
    }
};

#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_TYPED_TESTS_HPP_DA9562C6_8CAB_4242_9E9E_22FFB490DE30_
