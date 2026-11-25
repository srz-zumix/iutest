//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_stdlib.hpp
 * @brief       stdlib
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_
#define INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_stdlib_defs.hpp"
// IWYU pragma: end_exports
#include "iutest_type_traits.hpp"
#include <new>
#if IUTEST_HAS_RVALUE_REFS && IUTEST_HAS_CXX_HDR_TYPE_TARITS && !defined(IUTEST_NO_SFINAE) \
    && (!defined(IUTEST_LIBSTDCXX_VERSION) || IUTEST_LIBSTDCXX_VERSION >= 40700) \
    && (!defined(_MSC_VER) || _MSC_VER >= 1900)
#  define IIUT_HAS_OPTIONAL_VALUE_MOVE_ 1
#  include <utility>
#else
#  define IIUT_HAS_OPTIONAL_VALUE_MOVE_ 0
#endif
#if IUTEST_HAS_EXCEPTIONS
#  include <exception>
#endif

//======================================================================
// declare

//! using begin,end
#if !defined(IUTEST_USING_BEGIN_END)
#  if IUTEST_HAS_STD_BEGIN_END
#    define IUTEST_USING_BEGIN_END()    \
    using ::std::begin; using ::std::end
#  else
#    define IUTEST_USING_BEGIN_END()    \
    using ::iutest::detail::cxx::begin; using ::iutest::detail::cxx::end
#  endif
#endif

namespace iutest {
namespace detail {
namespace cxx
{

#if IUTEST_HAS_STD_BEGIN_END

using ::std::begin;
using ::std::end;

#else

template<typename T> typename T::iterator begin(T& x) { return x.begin(); }
template<typename T> typename T::iterator end  (T& x) { return x.end(); }

template<typename T> typename T::const_iterator begin(const T& x) { return x.begin(); }
template<typename T> typename T::const_iterator end  (const T& x) { return x.end(); }

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
template<typename T, size_t SIZE> T* begin(T (&x)[SIZE]) { return &x[0]; }
template<typename T, size_t SIZE> T* end  (T (&x)[SIZE]) { return begin(x) + SIZE; }

template<typename T, size_t SIZE> const T* begin(const T (&x)[SIZE]) { return &x[0]; }
template<typename T, size_t SIZE> const T* end  (const T (&x)[SIZE]) { return begin(x) + SIZE; }
#endif

#endif

}   // end of namespace cxx
}   // end of namespace detail
}   // end of namespace iutest

#if IUTEST_HAS_TUPLE
// IWYU pragma: begin_exports
#if !IUTEST_USE_EXTERNAL_STD_TUPLE && !IUTEST_USE_EXTERNAL_TR1_TUPLE
#  if   IUTEST_HAS_STD_TUPLE
#    include <tuple>
#  elif IUTEST_HAS_TR1_TUPLE
#    if (defined(__GNUC__) && (__GNUC__ >= 4))
#      include <tr1/tuple>
#    else
#      include <tuple>
#    endif
#  endif
#endif
// IWYU pragma: end_exports

namespace iutest {
namespace tuples
{

#if   IUTEST_HAS_STD_TUPLE
namespace alias = ::std;
#elif IUTEST_HAS_TR1_TUPLE
namespace alias = ::std::tr1;
#endif

using alias::tuple;
using alias::tuple_element;
using alias::make_tuple;
using alias::get;

template<typename T>struct tuple_size : public alias::tuple_size<T> {};
template<typename T>struct tuple_size<const T> : public alias::tuple_size<T> {};
template<typename T>struct tuple_size<volatile T> : public alias::tuple_size<T>{};
template<typename T>struct tuple_size<const volatile T> : public alias::tuple_size<T>{};

namespace detail
{

template<typename T, typename F, int Begin>
struct tuple_foreach_impl
{
    template<int N, int I>
    struct impl
    {
        static void do_something(T& t, F fn)
        {
            fn(I, get<I>(t));
            impl<N, I + 1>::do_something(t, fn);
        }
    };
    template<int N>
    struct impl<N, N>
    {
        static void do_something(T&, F) {}
    };

    static void do_something(T& t, F fn)
    {
        impl<tuple_size<T>::value, Begin>::do_something(t, fn);
    }
};

template<typename T, typename U>
struct tuple_cast_copy_impl
{
    template<int N, int I>
    struct impl
    {
        static void copy(T& dst, const U& src)
        {
            get<I>(dst) = static_cast<typename tuple_element<I, T>::type>(get<I>(src));
            impl<N, I + 1>::copy(dst, src);
        }
    };
    template<int N>
    struct impl<N, N>
    {
        static void copy(T&, const U&) {}
    };

    static void copy(T& dst, const U& src)
    {
        impl<tuple_size<T>::value, 0>::copy(dst, src);
    }
};

}   // end of namespace detail

template<int I, typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, F& fn)
{
    detail::tuple_foreach_impl<tuple_t, F&, I>::do_something(t, fn);
}
template<typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, F& fn)
{
    tuple_foreach<0>(t, fn);
}
template<int I, typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, const F& fn)
{
    detail::tuple_foreach_impl<tuple_t, const F&, I>::do_something(t, fn);
}
template<typename tuple_t, typename F>
void tuple_foreach(tuple_t& t, const F& fn)
{
    tuple_foreach<0>(t, fn);
}
template<typename T, typename U>
void tuple_cast_copy(T& dst, const U& src)
{
    detail::tuple_cast_copy_impl<T, U>::copy(dst, src);
}

}   // end of namespace tuples

using tuples::tuple;
using tuples::tuple_size;
using tuples::tuple_element;
using tuples::tuple_foreach;
using tuples::make_tuple;
using tuples::get;

}   // end of namespace iutest

#endif

namespace iutest
{

namespace stl
{

#if IUTEST_HAS_EXCEPTIONS
/**
 * @brief   Exception thrown when accessing an empty optional.
*/
class bad_optional_access : public ::std::exception {};
#endif

class nullpot_t {};

#if defined(__GNUC__) || defined(__clang__) || (defined(_MSC_VER) && _MSC_VER >= 1300) || IUTEST_HAS_CXX11
#  define IIUT_OPTIONAL_INLINE_STORAGE_
#endif

template<typename T>
class optional
{
public:
    typedef T value_type;
public:
    optional() IUTEST_CXX_NOEXCEPT_SPEC : m_value(NULL) {}
    explicit optional(nullpot_t) IUTEST_CXX_NOEXCEPT_SPEC : m_value(NULL) {}
    explicit optional(const T& rhs) : m_value(NULL) { construct(rhs); }
    template<typename U>
    explicit optional(const U& rhs) : m_value(NULL) { construct(rhs); }
    optional(const optional& rhs) : m_value(NULL)
    {
        if( rhs.has_value() ) {
            construct(*rhs.ptr());
        }
    }
#if IIUT_HAS_OPTIONAL_VALUE_MOVE_
    template<typename U>
    explicit optional(U&& rhs, typename ::std::enable_if<
        ::std::is_same<T, U>::value && ::std::is_move_constructible<T>::value>::type* = NULL)
        : m_value(NULL) { construct(::std::move(rhs)); }
#endif
    ~optional() { reset(); }

public:
    optional& operator = (const optional& rhs)
    {
        if( this != &rhs ) {
            if( rhs.has_value() ) {
                assign(*rhs.ptr());
            } else {
                reset();
            }
        }
        return *this;
    }
    optional& operator = (const T& rhs) { assign(rhs); return *this; }
#if IIUT_HAS_OPTIONAL_VALUE_MOVE_
    template<typename U>
    typename ::std::enable_if< ::std::is_same<T, U>::value
        && ::std::is_move_constructible<T>::value && ::std::is_move_assignable<T>::value, optional&>::type
    operator = (U&& rhs) { assign(::std::move(rhs)); return *this; }
#endif
    optional& operator = (nullpot_t) { reset(); return *this; }
    operator bool () const { return has_value(); }
    const T& operator * () const { return value(); }
    T& operator * () { return value(); }
    const T* operator -> () const { check_value(); return ptr(); }
    T* operator -> () { check_value(); return ptr(); }

public:
    bool has_value() const { return m_value != NULL; }
    void reset()
    {
        if( has_value() ) {
            destroy(m_value);
            m_value = NULL;
        }
    }

    //! Returns NULL when empty.
    const T* ptr() const { return m_value; }
    T* ptr() { return m_value; }

    //! value(), operator* and operator-> throw on empty access, or abort without exceptions.
    const T& value() const { check_value(); return *m_value; }
    T& value() { check_value(); return *m_value; }

    template<typename U>
    T value_or(const U& v) const
    {
        if( !has_value() ) {
            return v;
        }
        return *ptr();
    }

private:
    void check_value() const
    {
        if( !has_value() ) {
#if IUTEST_HAS_EXCEPTIONS
            throw bad_optional_access();
#else
            ::std::abort();
#endif
        }
    }

    static void destroy(T* p)
    {
#if defined(IIUT_OPTIONAL_INLINE_STORAGE_)
        p->~T();
#else
        // Use ordinary allocation on compilers without an alignment facility.
        ::delete p;
#endif
    }

    template<typename U>
#if IIUT_HAS_OPTIONAL_VALUE_MOVE_
    void construct(U&& rhs)
#else
    void construct(const U& rhs)
#endif
    {
#if defined(IIUT_OPTIONAL_INLINE_STORAGE_)
        m_value = ::new (storage())
#else
        m_value = ::new
#endif
#if IIUT_HAS_OPTIONAL_VALUE_MOVE_
            T(::std::forward<U>(rhs));
#else
            T(rhs);
#endif
    }

    template<typename U>
#if IIUT_HAS_OPTIONAL_VALUE_MOVE_
    void assign(U&& rhs)
    {
        if( has_value() ) {
            *m_value = ::std::forward<U>(rhs);
        } else {
            construct(::std::forward<U>(rhs));
        }
    }
#else
    void assign(const U& rhs)
    {
        if( has_value() ) {
            *m_value = rhs;
        } else {
            construct(rhs);
        }
    }
#endif

#if defined(__GNUC__) && __GNUC__ < 4 && !defined(__clang__)
    unsigned char m_storage[sizeof(T) + __alignof__(T) - 1];
    void* storage()
    {
        const size_t misalignment = reinterpret_cast<size_t>(m_storage) % __alignof__(T);
        return m_storage + (misalignment == 0 ? 0 : __alignof__(T) - misalignment);
    }
#elif defined(__GNUC__) || defined(__clang__)
    unsigned char m_storage[sizeof(T)] __attribute__((aligned(__alignof__(T))));
    void* storage() { return m_storage; }
#elif (defined(_MSC_VER) && _MSC_VER >= 1900) || (!defined(_MSC_VER) && IUTEST_HAS_CXX11)
    alignas(T) unsigned char m_storage[sizeof(T)];
    void* storage() { return m_storage; }
#elif defined(_MSC_VER) && _MSC_VER >= 1300
    // Older MSVC cannot use a dependent alignment in __declspec(align).
    unsigned char m_storage[sizeof(T) + __alignof(T) - 1];
    void* storage()
    {
        const size_t misalignment = reinterpret_cast<size_t>(m_storage) % __alignof(T);
        return m_storage + (misalignment == 0 ? 0 : __alignof(T) - misalignment);
    }
#endif
    T* m_value;
};

#undef IIUT_OPTIONAL_INLINE_STORAGE_

inline bool uncaught_exception()
{
#if IUTEST_HAS_CXX1Z && (!defined(IUTEST_LIBSTDCXX_VERSION) || (IUTEST_LIBSTDCXX_VERSION >= 60000))
    return ::std::uncaught_exceptions() > 0;
#else
    return ::std::uncaught_exception();
#endif
}

}   // end of namespace stl

namespace detail
{

//======================================================================
// struct

namespace type_t_helper
{

/**
 * @brief   type_fit_t
*/
template<size_t SIZE>
struct type_fit_t {};

/** type_fit_t<1> */
template<>
struct type_fit_t<1>
{
#if defined(INT8_MIN)
    typedef int8_t              Int;
    typedef uint8_t             UInt;
#else
    typedef char                Int;
    typedef unsigned char       UInt;
#endif
};

/** type_fit_t<2> */
template<>
struct type_fit_t<2>
{
#if defined(INT16_MIN)
    typedef int16_t             Int;
    typedef uint16_t            UInt;
#else
    typedef short               Int;
    typedef unsigned short      UInt;
#endif
};

/** type_fit_t<4> */
template<>
struct type_fit_t<4>
{
#if defined(INT32_MIN)
    typedef int32_t             Int;
    typedef uint32_t            UInt;
#else
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
private:
    template<typename T, typename F, bool b>
    struct impl { typedef T type; };
    template<typename T, typename F>
    struct impl<T, F, false> { typedef F type; };

public:
    typedef impl<long, int
        , sizeof(int) != 4 && sizeof(long) == 4>::type Int;
    typedef impl<unsigned long, unsigned int
        , sizeof(int) != 4 && sizeof(long) == 4>::type UInt;
#else
    typedef int                 Int;
    typedef unsigned int        UInt;
#endif
#endif
};

/** type_fit_t<8> */
template<>
struct type_fit_t<8>
{
#if defined(INT64_MIN)
    typedef int64_t             Int;
    typedef uint64_t            UInt;
#else
#if defined(_MSC_VER)
    typedef __int64             Int;
    typedef unsigned __int64    UInt;
#else
    typedef long long           Int;
    typedef unsigned long long  UInt;
#endif
#endif
};

/** type_fit_t<16> */
template<>
struct type_fit_t<16>
{
#if IUTEST_HAS_INT128
#if defined(_MSC_VER)
    typedef __int128            Int;
    typedef unsigned __int128   UInt;
#else
    typedef __int128_t  Int;
    typedef __uint128_t UInt;
#endif
#endif
};

/**
 * @brief   type_least_t
*/
template<size_t SIZE>
struct type_least_t {};

/** type_least_t<1> */
template<>
struct type_least_t<1>
{
#if defined(INT_LEAST8_MIN)
    typedef int_least8_t        Int;
    typedef uint_least8_t       UInt;
#else
    typedef char                Int;
    typedef unsigned char       UInt;
#endif
};

/** type_least_t<2> */
template<>
struct type_least_t<2>
{
#if defined(INT_LEAST16_MIN)
    typedef int_least16_t       Int;
    typedef uint_least16_t      UInt;
#else
    typedef short               Int;
    typedef unsigned short      UInt;
#endif
};

/** type_least_t<4> */
template<>
struct type_least_t<4>
{
#if defined(INT_LEAST32_MIN)
    typedef int_least32_t       Int;
    typedef uint_least32_t      UInt;
#else
    typedef int                 Int;
    typedef unsigned int        UInt;
#endif
};

/** type_least_t<8> */
template<>
struct type_least_t<8>
{
#if defined(INT_LEAST64_MIN)
    typedef int_least64_t       Int;
    typedef uint_least64_t      UInt;
#else
#if defined(_MSC_VER)
    typedef __int64             Int;
    typedef unsigned __int64    UInt;
#else
    typedef long long           Int;
    typedef unsigned long long  UInt;
#endif
#endif
};

/** type_least_t<16> */
template<>
struct type_least_t<16> : public type_fit_t<16>
{
};

template<bool B, typename T, typename U>
class conditional
{
    template<bool X, typename TMP>
    struct impl { typedef T type; };
    template<typename TMP>
    struct impl<false, TMP> { typedef U type; };
public:
    typedef typename impl<B, void>::type type;
};

template<size_t SIZE>
struct type_fit_t_select
{
    typedef typename conditional<(SIZE & (SIZE - 1)) == 0, type_fit_t<SIZE>
        , typename conditional<(SIZE > 8), type_fit_t<16>
            , typename conditional<(SIZE > 4), type_fit_t<8>
                , typename conditional<(SIZE > 2), type_fit_t<4>
                    , typename conditional<(SIZE > 1), type_fit_t<2>
                        , type_fit_t<1>
                    >::type
                >::type
            >::type
        >::type
    >::type type;
};

template<size_t SIZE>
struct type_least_t_select
{
    typedef typename conditional<(SIZE & (SIZE - 1)) == 0, type_least_t<SIZE>
        , typename conditional<(SIZE > 8), type_least_t<16>
            , typename conditional<(SIZE > 4), type_least_t<8>
                , typename conditional<(SIZE > 2), type_least_t<4>
                    , typename conditional<(SIZE > 1), type_least_t<2>
                        , type_least_t<1>
                    >::type
                >::type
            >::type
        >::type
    >::type type;
};

}   // end of namespace type_t_helper

/**
 * @brief   type_fit_t
*/
template<size_t SIZE>
struct type_fit_t : public type_t_helper::type_fit_t_select<SIZE>::type {};

/**
 * @brief   type_least_t
*/
template<size_t SIZE>
struct type_least_t : public type_t_helper::type_least_t_select<SIZE>::type {};

//======================================================================
// function
/**
 * @internal
 * @brief   mbtowc
*/
inline int iu_mbtowc(wchar_t* dst, const char* src, size_t size)
{
#if defined(IUTEST_OS_LINUX_ANDROID) || defined(IUTEST_OS_WINDOWS_MOBILE)
    // unimplimented
    IUTEST_UNUSED_VAR(dst);
    IUTEST_UNUSED_VAR(src);
    IUTEST_UNUSED_VAR(size);
    return 0;
#else
    return mbtowc(dst, src, size);
#endif
}

template<typename T>
T numeric_min()
{
    return (::std::numeric_limits<T>::min)();
}

template<typename T>
T numeric_max()
{
    return (::std::numeric_limits<T>::max)();
}

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STDLIB_HPP_54D4BEEE_7B6B_4AF4_B1F6_138560480D55_
