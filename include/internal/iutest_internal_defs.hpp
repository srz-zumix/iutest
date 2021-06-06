//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_internal_defs.hpp
 * @brief       internal definition
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_INTERNAL_DEFS_HPP_4B0AF5C2_8E8D_43EF_BFC5_F385E68F18DB_
#define INCG_IRIS_IUTEST_INTERNAL_DEFS_HPP_4B0AF5C2_8E8D_43EF_BFC5_F385E68F18DB_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "../iutest_defs.hpp"
#include "iutest_string_stream.hpp"
#include "iutest_string_view.hpp"
#include "iutest_type_traits.hpp"
#include "iutest_compatible_defs.hpp"
#include "iutest_exception.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_HDR_CXXABI
#  include <cxxabi.h>
#endif

//======================================================================
// define

/**
 * @brief   曖昧な else 文の警告抑制
*/
#ifdef __INTEL_COMPILER
#  define IUTEST_AMBIGUOUS_ELSE_BLOCKER_
#else
#  define IUTEST_AMBIGUOUS_ELSE_BLOCKER_    switch(::iutest::detail::AlwaysZero()) case 0: default:
#endif

#define IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(statement) if( ::iutest::detail::AlwaysTrue() ) statement

// console
#define IUTEST_MBS_CODE_UNKNOWN     0
#define IUTEST_MBS_CODE_UTF8        1
#define IUTEST_MBS_CODE_WINDOWS31J  2
#ifndef IUTEST_MBS_CODE
#  if defined(IUTEST_OS_WINDOWS)
#    define IUTEST_MBS_CODE IUTEST_MBS_CODE_WINDOWS31J
#  else
#    define IUTEST_MBS_CODE IUTEST_MBS_CODE_UTF8
#  endif
#endif


#ifndef NULL
#  ifdef    __cplusplus
#    define NULL    0
#  else
#    define NULL    (void*)0
#  endif
#endif

#ifndef IUTEST_BREAK
#  if   defined(__MINGW32__)
#    define IUTEST_BREAK()  DebugBreak()
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1310
#      define IUTEST_BREAK()    __debugbreak()
#    else
#      define IUTEST_BREAK()    DebugBreak()
#    endif
#  elif defined(IUTEST_OS_MAC)
// https://www.cocoawithlove.com/2008/03/break-into-debugger.html
#    if defined(__ppc64__) || defined(__ppc__)
#      define IUTEST_BREAK()    __asm__("li r0, 20\nsc\nnop\nli r0, 37\nli r4, 2\nsc\nnop\n" : : : "memory", "r0", "r3", "r4" )
#    else
#      define IUTEST_BREAK()    __asm__("int $3\n" : : )
#    endif
#  elif defined(__GUNC__) && (defined (__i386__) || defined (__x86_64__))
#    define IUTEST_BREAK()  do { __asm { int 3 } } while(::iutest::detail::AlwaysFalse())
#  elif defined(__clang__) || defined(__GNUC__)
#    define IUTEST_BREAK()  __builtin_trap()
#  elif defined(__ARMCC_VERSION)
#    define IUTEST_BREAK()  do { __breakpoint(0xF02C); } while(::iutest::detail::AlwaysFalse())
#  else
#    define IUTEST_BREAK()  *static_cast<volatile int*>(NULL) = 1
//#    define IUTEST_BREAK()    (void)0
#  endif
#endif

#if IUTEST_HAS_IF_EXISTS
#  define IUTEST_IF_EXISTS(identifier_, statement_)     __if_exists(identifier_) { statement_ }
#  define IUTEST_IF_NOT_EXISTS(identifier_, statement_) __if_not_exists(identifier_) { statement_ }
#  define IUTEST_STATIC_EXISTS(identifier_)             IUTEST_IF_EXISTS(identifier_, true) IUTEST_IF_NOT_EXISTS(identifier_, false)
#else
#  define IUTEST_IF_EXISTS(identifier_, statement_)
#  define IUTEST_IF_NOT_EXISTS(identifier_, statement_)
#  define IUTEST_STATIC_EXISTS(identifier_)
#endif

#if IUTEST_HAS_LIB && IUTEST_HAS_EXTERN_TEMPLATE

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()

extern template class ::std::vector< ::std::basic_string<char> >;
extern template class ::std::vector< ::std::basic_string<wchar_t> >;

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()

#endif

namespace iutest
{

namespace type_traits = iutest_type_traits;

namespace detail
{

//======================================================================
// types
#if IUTEST_HAS_NULLPTR && !defined(IUTEST_NO_NULL_TO_NULLPTR_T)
typedef ::std::nullptr_t iu_nullptr_convertible_t;
#else
typedef ::iutest_compatible::IsNullLiteralHelper::Object* iu_nullptr_convertible_t;
#endif

//======================================================================
// function

/**
 * @brief   true を返す(警告対策用)
*/
inline bool AlwaysTrue() { return true; }

/**
 * @brief   false を返す(警告対策用)
*/
inline bool AlwaysFalse() { return !AlwaysTrue(); }

/**
 * @brief   0 を返す(警告対策用)
*/
inline int  AlwaysZero() { return 0; }

/**
 * @brief   真偽値を返す(警告対策用)
*/
inline bool IsTrue(bool b) { return b; }

//======================================================================
// class

// detail から使えるようにする
using namespace iutest_type_traits; // NOLINT
using namespace iutest_compatible;  // NOLINT

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

/**
 * @brief   iterator traits
*/
template<typename Ite>
struct IteratorTraits
{
    typedef typename Ite::value_type type;
};
template<typename T>
struct IteratorTraits<T*>
{
    typedef T type;
};
template<typename T>
struct IteratorTraits<const T*>
{
    typedef T type;
};

#endif

/**
 * @brief   delete
*/
template<typename T>
inline void Delete(T* ptr)
{
    delete ptr;
}

/**
 * @internal
 * @brief   空オブジェクト
*/
class None {};
template<typename T>
class NoneT1 {};

/**
 * @internal
 * @brief   MSVC 用ダミー型
*/
template<typename T>
struct explicit_type_t {};

#if defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#  define IUTEST_EXPLICIT_TEMPLATE_TYPE_(t)         ::iutest::detail::explicit_type_t<t>*
#  define IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(t)  , ::iutest::detail::explicit_type_t<t>*
#else
#  define IUTEST_EXPLICIT_TEMPLATE_TYPE_(t)
#  define IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(t)
#endif

template<typename T>
inline explicit_type_t<T>* explicit_type() { return NULL; }

/**
 * @brief   型に依存したユニークなカウンタ
*/
template<typename T>
class TypeUniqueCounter
{
    static size_t value;
public:
    static size_t count() { return value++; }
};
template<typename T>size_t TypeUniqueCounter<T>::value = 0;

template<typename T>
inline size_t GetTypeUniqueCounter() { return TypeUniqueCounter<T>::count(); }

/**
 * @internal
 * @brief   auto_ptr
*/
template<typename T>
class auto_ptr
{
    mutable T* m_ptr;
public:
    explicit auto_ptr(T* p = NULL) : m_ptr(p) {}
    auto_ptr(const auto_ptr& rhs) : m_ptr(rhs.m_ptr) { rhs.m_ptr = NULL; }
    ~auto_ptr() { if( m_ptr != NULL ) delete m_ptr; }

    T& operator *  () const { return *m_ptr; }
    T* operator -> () const { return m_ptr; }

    auto_ptr& operator = (auto_ptr& rhs) { m_ptr = rhs.m_ptr; rhs.m_ptr = NULL; return *this; }

    T* get() { return m_ptr; }
};

/**
 * @internal
 * @brief   scoped_ptr
*/
template<typename T>
class scoped_ptr
{
    T* m_ptr;
public:
    explicit scoped_ptr(T* p=NULL) : m_ptr(p) {}
    ~scoped_ptr() { reset(); }

    T& operator *  () const { return *m_ptr; }
    T* operator -> () const { return m_ptr; }

    T* get() const { return m_ptr; }
    T* release()
    {
        T* const p = m_ptr;
        m_ptr = NULL;
        return p;
    }

    void reset(T* p=NULL)
    {
        if( m_ptr != p )
        {
            if( IsTrue(sizeof(T) > 0) )
            {
                delete m_ptr;
            }
            m_ptr = p;
        }
    }
private:
    IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(scoped_ptr);
};

/**
 * @internal
 * @brief   NULL リテラルかどうか
*/
#define IUTEST_IS_NULLLITERAL(x)    \
    (sizeof(::iutest::detail::IsNullLiteralHelper::IsNullLiteral(x)) == 1)

/**
 * @internal
 * @brief   stl コンテナかどうか
*/
struct IsContainerHelper
{
    typedef int  yes_t;
    typedef char no_t;

    template<typename T>
    static IUTEST_CXX_CONSTEXPR yes_t IsContainer(int IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T)
        , typename T::iterator* =NULL, typename T::const_iterator* =NULL) { return 0; }

    template<typename T>
    static IUTEST_CXX_CONSTEXPR no_t  IsContainer(long IUTEST_APPEND_EXPLICIT_TEMPLATE_TYPE_(T)) { return 0; }
};

/**
 * @brief   型名の取得
*/
template<typename T>
inline ::std::string GetTypeName()
{
#if IUTEST_HAS_RTTI
    const char* const name = typeid(T).name();

#if IUTEST_HAS_HDR_CXXABI
    using abi::__cxa_demangle;
    int status=1;
    char* const read_name = __cxa_demangle(name, 0, 0, &status);
    ::std::string str(status == 0 ? read_name : name);
#if defined(_IUTEST_DEBUG)
    if( status != 0 ) {
        fprintf(stderr, "Unable to demangle \"%s\" -> \"%s\". (status=%d)\n", name, read_name ? read_name : "", status);
        fflush(stderr);
    }
#endif
    free(read_name);
    return str;
#else
    return name;
#endif

#else
    return "<type>";
#endif
}

#if !IUTEST_HAS_RTTI

#define IIUT_GeTypeNameSpecialization(type) \
    template<>inline ::std::string GetTypeName<type>() { return #type; }    \
    template<>inline ::std::string GetTypeName<type*>() { return #type "*"; }

#define IIUT_GeTypeNameSpecialization2(type)    \
    IIUT_GeTypeNameSpecialization(type)         \
    IIUT_GeTypeNameSpecialization(unsigned type)

IIUT_GeTypeNameSpecialization2(char)    // NOLINT
IIUT_GeTypeNameSpecialization2(short)   // NOLINT
IIUT_GeTypeNameSpecialization2(int)     // NOLINT
IIUT_GeTypeNameSpecialization2(long)    // NOLINT
IIUT_GeTypeNameSpecialization(float)    // NOLINT
IIUT_GeTypeNameSpecialization(double)   // NOLINT
IIUT_GeTypeNameSpecialization(bool)     // NOLINT

#undef IIUT_GeTypeNameSpecialization
#undef IIUT_GeTypeNameSpecialization2

#endif

/**
 * @brief   型名の取得
*/
template<typename T>
struct GetTypeNameProxy
{
    static ::std::string    GetTypeName() { return detail::GetTypeName<T>(); }
};

}   // end of namespace detail
}   // end of namespace iutest


#endif // INCG_IRIS_IUTEST_INTERNAL_DEFS_HPP_4B0AF5C2_8E8D_43EF_BFC5_F385E68F18DB_
