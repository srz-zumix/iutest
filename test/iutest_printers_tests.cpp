//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_printers_tests.cpp
 * @brief		iutest_printers.hpp ƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#include <vector>

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedPrintToTest : public ::iutest::Test {};
typedef ::iutest::Types<char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long, int*> PrintStringTestTypes;
IUTEST_TYPED_TEST_CASE(TypedPrintToTest, PrintStringTestTypes);

IUTEST_TYPED_TEST(TypedPrintToTest, Print)
{
	TypeParam a = 0;
	TypeParam& b = a;
	const TypeParam c = a;
	const volatile TypeParam d = a;

	IUTEST_SUCCEED() << ::iutest::PrintToString(a);
	IUTEST_SUCCEED() << ::iutest::PrintToString(b);
	IUTEST_SUCCEED() << ::iutest::PrintToString(c);
	IUTEST_SUCCEED() << ::iutest::PrintToString(d);
}

#endif

IUTEST(PrintToTest, RawArray)
{
	{
		unsigned char a[3] = {0, 1, 2};
		const unsigned char b[3] = {0, 1, 2};
		const volatile unsigned char c[3] = {0, 1, 2};
		volatile unsigned char d[3] = {0, 1, 2};

		IUTEST_SUCCEED() << ::iutest::PrintToString(a);
		IUTEST_SUCCEED() << ::iutest::PrintToString(b);
		IUTEST_SUCCEED() << ::iutest::PrintToString(c);
		IUTEST_SUCCEED() << ::iutest::PrintToString(d);
	}
	{
		char a[3] = {0, 1, 2};
		const char b[3] = {0, 1, 2};
		const volatile char c[3] = {0, 1, 2};
		volatile char d[3] = {0, 1, 2};

		IUTEST_SUCCEED() << ::iutest::PrintToString(a);
		IUTEST_SUCCEED() << ::iutest::PrintToString(b);
		IUTEST_SUCCEED() << ::iutest::PrintToString(c);
		IUTEST_SUCCEED() << ::iutest::PrintToString(d);
	}
}

IUTEST(PrintToTest, Std)
{
	const int a[] = {0, 1, 2};
	::std::pair<int, int> p(0, 1);
	::std::vector<int> v(a, a+(sizeof(a)/sizeof(a[0])));

	IUTEST_SUCCEED() << ::iutest::PrintToString(p);
	IUTEST_SUCCEED() << ::iutest::PrintToString(v);
}

struct Point0
{
	unsigned int x,y;
};
struct Point1
{
	int x,y;
};
struct Point2
{
	int x,y;
};

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Point1& x)
{
	return os << x.x << ", " << x.y << "(operator overload)";
}

void PrintTo(const Point2& x, ::iutest::iu_ostream* os)
{
	*os << x.x << ", " << x.y << "(function overload)";
}

IUTEST(PrintToTest, Overload)
{
	Point0 p0 = { 0x12345678, 0x9ABCDEF0 };
	Point1 p1 = {0, 0};
	Point2 p2 = {1, 1};
	IUTEST_SUCCEED() << ::iutest::PrintToString(p0);
	IUTEST_SUCCEED() << ::iutest::PrintToString(p1);
	IUTEST_SUCCEED() << ::iutest::PrintToString(p2);
}

#if IUTEST_HAS_TUPLE
IUTEST(PrintToTest, Tuple)
{
	::iutest::tuples::tuple<bool, int, char> t(false, 100, 'a');
	
	IUTEST_SUCCEED() << ::iutest::PrintToString(t);
}
#endif

