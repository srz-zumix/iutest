//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        container_printers_tests.cpp
 * @brief       gtest-compatible container printer selection tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
 */
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"
#include <vector>

#if defined(IUTEST_USE_GTEST)
#  define IUTEST_TEST_CONTAINER_EXPRESSIONS (GTEST_VER >= 0x01110000)
#  if GTEST_VER >= 0x01060000
#    define IUTEST_TEST_CONTAINER_PRINTERS 1
#  else
#    define IUTEST_TEST_CONTAINER_PRINTERS 0
#  endif
#elif !defined(IUTEST_NO_SFINAE) \
    && (!defined(_MSC_VER) || _MSC_VER >= 1910) \
    && (!defined(__GNUC__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 4) \
        || (defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 5))))
#  define IUTEST_TEST_CONTAINER_EXPRESSIONS 1
#  define IUTEST_TEST_CONTAINER_PRINTERS 1
#else
#  define IUTEST_TEST_CONTAINER_EXPRESSIONS 0
#  define IUTEST_TEST_CONTAINER_PRINTERS 1
#endif

namespace container_printer_test
{

class ConstContainer
{
public:
    typedef const int* const_iterator;

    ConstContainer() { values_[0] = 1; values_[1] = 2; }
    const_iterator begin() const { return values_; }
    const_iterator end() const { return values_ + 2; }

private:
    int values_[2];
};

struct StreamableContainer : ConstContainer {};
struct CustomContainer : StreamableContainer {};
struct NonContainer { unsigned char value; };
struct Streamable { unsigned char value; };
struct Custom : Streamable {};
struct IteratorOnly { typedef const int* const_iterator; unsigned char value; };
struct MutableOnly
{
    typedef const int* const_iterator;
    const_iterator begin() { return &value; }
    const_iterator end() { return &value + 1; }
    int value;
};

struct MissingEnd
{
    typedef const int* const_iterator;
    const_iterator begin() const;
};

struct MissingBegin
{
    typedef const int* const_iterator;
    const_iterator end() const;
};

struct NoIncrement
{
    int operator * () const;
    bool operator != (const NoIncrement&) const;
};

template<typename Iterator>
struct InvalidRange
{
    typedef Iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
};

struct NoComparison
{
    NoComparison& operator ++ ();
    int operator * () const;
};

struct WrongIterator : ConstContainer
{
    typedef const long* const_iterator;
};

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const StreamableContainer&)
{
    return os << "stream";
}

void PrintTo(const CustomContainer&, ::iutest::iu_ostream* os)
{
    *os << "custom";
}

::iutest::iu_ostream& operator << (::iutest::iu_ostream& os, const Streamable&)
{
    return os << "stream";
}

void PrintTo(const Custom&, ::iutest::iu_ostream* os)
{
    *os << "custom";
}

}   // namespace container_printer_test

#if IUTEST_TEST_CONTAINER_PRINTERS
#if IUTEST_TEST_CONTAINER_EXPRESSIONS
IUTEST(ContainerPrintersTest, ConstOnly)
{
    const container_printer_test::ConstContainer value;
    IUTEST_EXPECT_STREQ("{ 1, 2 }", ::iutest::PrintToString(value));
}
#endif

IUTEST(ContainerPrintersTest, StandardContainers)
{
    ::std::vector<int> values;
    IUTEST_EXPECT_STREQ("{}", ::iutest::PrintToString(values));
    values.push_back(1);
    values.push_back(2);
    IUTEST_EXPECT_STREQ("{ 1, 2 }", ::iutest::PrintToString(values));
}

#if defined(IUTEST_USE_GTEST) || !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
IUTEST(ContainerPrintersTest, SelectionOrder)
{
#if IUTEST_TEST_CONTAINER_EXPRESSIONS
    IUTEST_EXPECT_STREQ("{ 1, 2 }", ::iutest::PrintToString(container_printer_test::StreamableContainer()));
    IUTEST_EXPECT_STREQ("custom", ::iutest::PrintToString(container_printer_test::CustomContainer()));
#endif
    IUTEST_EXPECT_STREQ("stream", ::iutest::PrintToString(container_printer_test::Streamable()));
    IUTEST_EXPECT_STREQ("custom", ::iutest::PrintToString(container_printer_test::Custom()));
}
#endif

IUTEST(ContainerPrintersTest, NonContainers)
{
    const container_printer_test::NonContainer value = { 0 };
    const container_printer_test::IteratorOnly iterator_only = { 0 };
    const container_printer_test::MutableOnly mutable_only = { 0 };
#if defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("1-byte object <00>", ::iutest::PrintToString(value));
    IUTEST_EXPECT_STREQ("1-byte object <00>", ::iutest::PrintToString(iterator_only));
#else
    IUTEST_EXPECT_STREQ("1-Byte object < 00 >", ::iutest::PrintToString(value));
    IUTEST_EXPECT_STREQ("1-Byte object < 00 >", ::iutest::PrintToString(iterator_only));
#endif
    IUTEST_EXPECT_STRIN("object <", ::iutest::PrintToString(mutable_only));
    IUTEST_EXPECT_STRIN("object <", ::iutest::PrintToString(container_printer_test::MissingBegin()));
    IUTEST_EXPECT_STRIN("object <", ::iutest::PrintToString(container_printer_test::MissingEnd()));
    IUTEST_EXPECT_STRIN("object <", ::iutest::PrintToString(container_printer_test::InvalidRange<int>()));
    IUTEST_EXPECT_STRIN("object <",
        ::iutest::PrintToString(container_printer_test::InvalidRange<container_printer_test::NoIncrement>()));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(ContainerPrintersTest, InvalidIteratorOperations)
{
    IUTEST_EXPECT_STRIN("object <",
        ::iutest::PrintToString(container_printer_test::InvalidRange<container_printer_test::NoComparison>()));
    IUTEST_EXPECT_STRIN("object <", ::iutest::PrintToString(container_printer_test::WrongIterator()));
}
#endif

IUTEST(ContainerPrintersTest, PointersAndArrays)
{
    const int values[] = { 1, 2 };
    IUTEST_EXPECT_STREQ("{ 1, 2 }", ::iutest::PrintToString(values));
    const container_printer_test::ConstContainer container;
    const container_printer_test::ConstContainer* pointer = &container;
    IUTEST_EXPECT_EQ(::std::string::npos, ::iutest::PrintToString(pointer).find("{"));
    IUTEST_EXPECT_EQ(::std::string::npos, ::iutest::PrintToString(pointer).find("object"));
    const char text[] = "text";
    IUTEST_EXPECT_STREQ("\"text\"", ::iutest::PrintToString(text));
}
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
