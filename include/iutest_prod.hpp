//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_prod.hpp
 * @brief       iris unit test production code 対応用 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PROD_HPP_7A316C18_042D_4E48_BC31_E6AE8B6C2E28_
#define INCG_IRIS_IUTEST_PROD_HPP_7A316C18_042D_4E48_BC31_E6AE8B6C2E28_

//======================================================================
// define
/**
 * @brief   テストから見えるように fried 登録
*/
#define IUTEST_FRIEND_TEST(testsuitename_, testname_)       \
    friend class IUTEST_TEST_CLASS_NAME_(testsuitename_, testname_)

#if !defined(_MSC_VER) || _MSC_VER > 1200

#if IUTEST_HAS_TYPED_TEST

/**
 * @brief   テストから見えるように fried 登録(IUTEST_TYPED_TEST 用)
*/
#define IUTEST_FRIEND_TYPED_TEST(testsuitename_, testname_) \
    template<typename T>IUTEST_FRIEND_TEST(testsuitename_, testname_)

#endif

#if IUTEST_HAS_TYPED_TEST_P

/**
 * @brief   テストから見えるように fried 登録するための宣言
*/
#define IUTEST_FRIEND_TYPED_TEST_P_DECLARATION(testsuitename_, testname_)   \
    namespace IIUT_TYPED_TEST_P_NAMESPACE_(testsuitename_) { template<typename T>class testname_; }

/**
 * @brief   テストから見えるように fried 登録(IUTEST_TYPED_TEST_P 用)
*/
#define IUTEST_FRIEND_TYPED_TEST_P(testsuitename_, testname_)   \
    template<typename T>friend class IIUT_TYPED_TEST_P_NAMESPACE_(testsuitename_)::testname_

#endif

#endif

/**
 * @brief   private メンバーへのアクセス権を作成
 * @param   member_type = 型
 * @param   class_name  = クラス
 * @param   member_name = メンバー名
*/
#define IUTEST_MAKE_PEEP(member_type, class_name, member_name)      \
    IUTEST_MAKE_PEEP_TAG_(member_type, class_name, member_name)

/**
 * @brief   private メンバーへのアクセス
 * @param   v           = オブジェクトインスタンス
 * @param   class_name  = クラス名
 * @param   member_name = メンバー名
*/
#define IUTEST_PEEP_GET(v, class_name, member_name)     \
    (v.*::iutest::detail::peep_tag< IIUT_PEEP_TAG_NAME_(class_name, member_name)<class_name> >::value)

/**
 * @brief   static private  メンバーへのアクセス
 * @param   class_name  = クラス名
 * @param   member_name = メンバー名
*/
#define IUTEST_PEEP_STATIC_GET(class_name, member_name) \
    (*::iutest::detail::peep_tag< IIUT_PEEP_TAG_NAME_(class_name, member_name)<class_name> >::value)

#if IUTEST_HAS_PEEP_CLASS

/**
 * @brief   private メンバーへのアクセスクラス宣言
 * @param   class_name  = クラス名
 * @param   member_name = メンバー名
*/
#define IUTEST_PEEP(class_name, member_name)            \
    ::iutest::detail::peep::Peep< class_name, IIUT_PEEP_TAG_NAME_(class_name, member_name)<class_name> >::type

#endif

/**
 * @private
 * @{
*/
#define IUTEST_MAKE_PEEP_TAG_(member_type, class_name, member_name)                             \
    template<typename T>struct IIUT_PEEP_TAG_NAME_(class_name, member_name);                    \
    template<>struct IIUT_PEEP_TAG_NAME_(class_name, member_name)<class_name> {                 \
                        typedef ::iutest_type_traits::identity<member_type>::type type; };      \
    template<typename T, typename Tag, typename Tag::type X>                                    \
    struct IIUT_PEEP_SETTER_NAME_(class_name, member_name) {                                    \
        IIUT_PEEP_SETTER_NAME_(class_name, member_name)() {                                     \
            ::iutest::detail::peep_tag<Tag>::value = X; }                                       \
        static IIUT_PEEP_SETTER_NAME_(class_name, member_name) instance;                        \
    };                                                                                          \
    template<typename T, typename Tag, typename Tag::type X>                                    \
    IIUT_PEEP_SETTER_NAME_(class_name, member_name)<T, Tag, X>                                  \
        IIUT_PEEP_SETTER_NAME_(class_name, member_name)<T, Tag, X>::instance;                   \
    template struct IIUT_PEEP_SETTER_NAME_(class_name, member_name)<class_name                  \
        , IIUT_PEEP_TAG_NAME_(class_name, member_name)<class_name>, &class_name::member_name>

#define IIUT_PEEP_TAG_NAME_(class_name, member_name)        iu_peep_tag_##member_name
#define IIUT_PEEP_SETTER_NAME_(class_name, member_name)     \
    IUTEST_PP_CAT(IUTEST_PP_CAT(iu_peep_set_, member_name), __LINE__)

/**
 * @}
*/

namespace iutest {

//======================================================================
// class
namespace detail
{

/**
 * @brief   private メンバー保持構造体
*/
template<typename Tag>
struct peep_tag
{
    static typename Tag::type value;
};
template<typename Tag>
typename Tag::type peep_tag<Tag>::value;

#if IUTEST_HAS_PEEP_CLASS

namespace peep
{

/**
 * @brief   private メンバーアクセスオブジェクト
*/
template<typename T, typename Tag>
class Peep
{
private:
    typedef Tag peep_tag;
    typedef typename Tag::type peep_type;

private:
    template<typename U, typename Type>
    class peep_member_function_impl
    {
    private:
        typedef typename type_traits::function_return_type<Type>::type return_type;

    private:
        U* m_ptr;
    public:
        explicit peep_member_function_impl(U* ptr) : m_ptr(ptr) {}

#if IUTEST_HAS_VARIADIC_TEMPLATES
    public:
        template<typename ...Args>
        return_type operator () (Args... args)
        {
            return ((*m_ptr).*detail::peep_tag<peep_tag>::value)( ::std::forward<Args>(args)... );
        }
#else

#define IIUT_DECL_PEEP_MEMBER_FUNC_(n)   \
    template<IUTEST_PP_ENUM_PARAMS(n, typename T)>return_type operator () (     \
        IUTEST_PP_ENUM_BINARY_PARAMS(n, T, t)) {                \
        return ((*m_ptr).*detail::peep_tag<peep_tag>::value)(IUTEST_PP_ENUM_PARAMS(n, t)); }

        return_type operator () () { return ((*m_ptr).*detail::peep_tag<peep_tag>::value)(); }

        IIUT_DECL_PEEP_MEMBER_FUNC_(1)
        IIUT_DECL_PEEP_MEMBER_FUNC_(2)
        IIUT_DECL_PEEP_MEMBER_FUNC_(3)
        IIUT_DECL_PEEP_MEMBER_FUNC_(4)
        IIUT_DECL_PEEP_MEMBER_FUNC_(5)
        IIUT_DECL_PEEP_MEMBER_FUNC_(6)
        IIUT_DECL_PEEP_MEMBER_FUNC_(7)
        IIUT_DECL_PEEP_MEMBER_FUNC_(8)
        IIUT_DECL_PEEP_MEMBER_FUNC_(9)
        IIUT_DECL_PEEP_MEMBER_FUNC_(10)
        IIUT_DECL_PEEP_MEMBER_FUNC_(11)
        IIUT_DECL_PEEP_MEMBER_FUNC_(12)
        IIUT_DECL_PEEP_MEMBER_FUNC_(13)
        IIUT_DECL_PEEP_MEMBER_FUNC_(14)
        IIUT_DECL_PEEP_MEMBER_FUNC_(15)
        IIUT_DECL_PEEP_MEMBER_FUNC_(16)
        IIUT_DECL_PEEP_MEMBER_FUNC_(17)
        IIUT_DECL_PEEP_MEMBER_FUNC_(18)
        IIUT_DECL_PEEP_MEMBER_FUNC_(19)
        IIUT_DECL_PEEP_MEMBER_FUNC_(20)

#undef IIUT_DECL_PEEP_MEMBER_FUNC_
#endif
    };
    template<typename U, typename Type, bool is_const>
    class peep_member_object_impl
    {
        typedef Type value_type;
    private:
        U* m_ptr;
    public:
        explicit peep_member_object_impl(U* ptr) : m_ptr(ptr) {}
    private:
        peep_member_object_impl(const peep_member_object_impl&);
    public:
        operator value_type () const { return (*m_ptr).*detail::peep_tag<peep_tag>::value; }
        peep_member_object_impl& operator = (const value_type& value) IUTEST_CXX_DELETED_FUNCTION;
    };
    template<typename U, typename Type>
    class peep_member_object_impl<U, Type, false>
    {
        typedef Type value_type;
    private:
        U* m_ptr;
    public:
        explicit peep_member_object_impl(U* ptr) : m_ptr(ptr) {}
    private:
        peep_member_object_impl(const peep_member_object_impl&);
    public:
        operator value_type () const { return (*m_ptr).*detail::peep_tag<peep_tag>::value; }
        operator value_type& () { return (*m_ptr).*detail::peep_tag<peep_tag>::value; }
        peep_member_object_impl& operator = (const value_type& value)
        {
            (*m_ptr).*detail::peep_tag<peep_tag>::value = value;
            return *this;
        }
    };


    template<typename U, typename Type, bool Func>
    struct peep_member_impl
    {
        typedef peep_member_function_impl<U, Type> type;
    };
    template<typename U, typename Type>
    struct peep_member_impl<U, Type U::*, false>
    {
        typedef peep_member_object_impl<U, Type, type_traits::is_const<Type>::value> type;
    };

private:
    template<typename U, typename Type, bool Func>
    class peep_static_impl
    {
        typedef typename type_traits::remove_pointer<Type>::type value_type;
    public:
        peep_static_impl() {}
        peep_static_impl(const value_type& value) { *detail::peep_tag<peep_tag>::value = value; }   // NOLINT
        peep_static_impl(const peep_static_impl&) {}
    public:
        operator value_type () const { return *detail::peep_tag<peep_tag>::value; }
        operator value_type& () { return *detail::peep_tag<peep_tag>::value; }
        peep_static_impl& operator = (const value_type& value)
        {
            *detail::peep_tag<peep_tag>::value = value;
            return *this;
        }
    };

    template<typename U, typename Type>
    class peep_static_impl<U, Type, true>
    {
    public:
        operator Type () { return *detail::peep_tag<peep_tag>::value; }
    };
private:
    template<typename U, typename Type, bool is_member_ptr>
    struct peep_impl
    {
        typedef peep_static_impl<U, Type, type_traits::is_function_pointer<Type>::value > type;
    };
    template<typename U, typename Type>
    struct peep_impl<U, Type, true>
    {
        typedef typename peep_member_impl<U, Type
            , type_traits::is_member_function_pointer<Type>::value >::type type;
    };
public:
    //! private メンバーアクセスオブジェクト型
    typedef typename peep_impl<T, peep_type
        , type_traits::is_member_pointer<peep_type>::value >::type type;
};

}   // end of namespace peep

#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_PROD_HPP_7A316C18_042D_4E48_BC31_E6AE8B6C2E28_
