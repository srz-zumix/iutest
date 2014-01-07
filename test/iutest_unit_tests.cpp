//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_unit_tests.cpp
 * @brief		iutest test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

class Base {};
class Derived : public Base {};
class Hoge {};
void Func(void) {}

typedef int inttype;

IUTEST(UnitTest, is_class)
{
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_class<int>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_class<Base>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_class<Derived>::value );
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_class<void (*)()>::value );
}

IUTEST(UnitTest, is_same)
{
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_same<int, char>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_same<int, int>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_same<int, inttype>::value );
}

IUTEST(UnitTest, is_void)
{
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_void<void*>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_void<void>::value );
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_void<int>::value );
}

IUTEST(UnitTest, is_base_of)
{
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_base_of<int, Base>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_base_of<Base, Derived>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_base_of<Base, const Derived>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_base_of<const volatile Base, Derived>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_base_of<volatile Base, volatile Derived const>::value );
	IUTEST_STATIC_ASSERT( !::iutest_type_traits::is_base_of<Base, Hoge>::value );
	IUTEST_STATIC_ASSERT(  ::iutest_type_traits::is_base_of<Derived, Derived>::value );
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

