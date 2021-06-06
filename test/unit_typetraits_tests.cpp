//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_typetraits_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

class Base {};
class Derived : public Base {};
class Hoge {};

typedef int inttype;

IUTEST(UnitTest, is_class)
{
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_class<int>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_class<Base>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_class<Derived>::value );
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_class<void (*)()>::value );
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

IUTEST(UnitTest, is_void)
{
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_void<void*>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_void<void>::value );
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_void<int>::value );
}

#endif

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) || IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION

IUTEST(UnitTest, is_same)
{
    IUTEST_STATIC_ASSERT( !(::iutest_type_traits::is_same<int, char>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_same<int, int>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_same<int, inttype>::value) );
}

IUTEST(UnitTest, is_base_of)
{
    IUTEST_STATIC_ASSERT( !(::iutest_type_traits::is_base_of<int, Base>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_base_of<Base, Derived>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_base_of<Base, const Derived>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_base_of<const volatile Base, Derived>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_base_of<volatile Base, volatile Derived const>::value) );
    IUTEST_STATIC_ASSERT( !(::iutest_type_traits::is_base_of<Base, Hoge>::value) );
    IUTEST_STATIC_ASSERT(  (::iutest_type_traits::is_base_of<Derived, Derived>::value) );
}

#endif

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

struct X
{
    int a, b, c;
};
struct Y
{
    int a, b, c;
    bool operator == (const Y&) const { return true; }
};

struct Z
{
    int a, b, c;
};

bool operator == (const Z&, const Z&) { return true; }

IUTEST(UnitTest, has_equal_to)
{
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to<int>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to<float>::value );
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::has_equal_to<X>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to<Y>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to<Z>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to< ::std::vector<int> >::value );
}

#if IUTEST_HAS_TUPLE
typedef ::iutest::tuples::tuple<bool, int, int> Tuple;

IUTEST(UnitTest, has_equal_to_tuple)
{
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::has_equal_to<Tuple>::value );
}
#endif

IUTEST(UnitTest, is_signed)
{
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_signed<int>::value );
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_signed<unsigned int>::value );
}

IUTEST(UnitTest, is_unsigned)
{
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_unsigned<int>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_unsigned<unsigned int>::value );
}

IUTEST(UnitTest, is_signed_wchar_t)
{
#if IUTEST_WCHAR_UNSIGNED
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_signed<wchar_t>::value );
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_unsigned<wchar_t>::value );
#else
    IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_signed<wchar_t>::value );
    IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_unsigned<wchar_t>::value );
#endif
}



#endif
