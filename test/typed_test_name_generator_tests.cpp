//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        typed_test_name_generator_tests.cpp
 * @brief       typed test custom name generator compatibility
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
#include "../include/gtest/iutest_switch.hpp"
#include "main.cpp"

#if IUTEST_HAS_TYPED_TEST

template<typename T>
struct NamedType;

template<>
struct NamedType<int>
{
    static const char* Name() { return "Int"; }
    static const char* Index() { return "0"; }
};

template<>
struct NamedType<long>
{
    static const char* Name() { return "Long"; }
    static const char* Index() { return "1"; }
};

typedef ::iutest::Types<int, long> NamedTypes;

template<typename T>
class DefaultTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(DefaultTypedNames, NamedTypes);

IUTEST_TYPED_TEST(DefaultTypedNames, NumericNames)
{
    const ::std::string expected = ::std::string("DefaultTypedNames/") + NamedType<TypeParam>::Index();
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
    IUTEST_EXPECT_EQ(0u, ::std::string(::iuutil::GetCurrentTestSuite()->name()).find(expected));
#else
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
#endif
}

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_VARIADIC_MACROS)
template<typename T>
class DirectDefaultTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(DirectDefaultTypedNames, ::iutest::Types<int, long>);

IUTEST_TYPED_TEST(DirectDefaultTypedNames, NumericNames)
{
    const ::std::string expected = ::std::string("DirectDefaultTypedNames/") + NamedType<TypeParam>::Index();
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
    IUTEST_EXPECT_EQ(0u, ::std::string(::iuutil::GetCurrentTestSuite()->name()).find(expected));
#else
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
#endif
}
#endif

#if IUTEST_HAS_TYPED_TEST_P
template<typename T>
class ParameterizedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(ParameterizedNames);

IUTEST_TYPED_TEST_P(ParameterizedNames, First)
{
    const ::std::string name = ::iuutil::GetCurrentTestSuite()->name();
    const ::std::string suffix = name.substr(name.rfind('/') + 1);
    if( name.find("Default/") == 0 )
    {
        const ::std::string expected = ::std::string("Default/ParameterizedNames/") + NamedType<TypeParam>::Index();
#if IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
        IUTEST_EXPECT_EQ(0u, name.find(expected));
#else
        IUTEST_EXPECT_STREQ(expected.c_str(), name.c_str());
#endif
    }
    else if( name.find("Indexed/") == 0 )
    {
        const ::std::string expected = ::std::string(NamedType<TypeParam>::Name()) + NamedType<TypeParam>::Index();
        IUTEST_EXPECT_STREQ(expected.c_str(), suffix.c_str());
    }
    else
    {
        IUTEST_EXPECT_STREQ(NamedType<TypeParam>::Name(), suffix.c_str());
    }
}

IUTEST_TYPED_TEST_P(ParameterizedNames, Second)
{
    IUTEST_EXPECT_EQ(2, TypeParam(1) + TypeParam(1));
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(ParameterizedNames, First, Second);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(Default, ParameterizedNames, NamedTypes);
#endif

#if IUTEST_HAS_TYPED_TEST_NAME_GENERATOR

struct TypeNameGenerator
{
    template<typename T>
    static ::std::string GetName(int) { return NamedType<T>::Name(); }
};

struct IndexedNameGenerator
{
    template<typename T>
    static ::std::string GetName(int index)
    {
        return ::std::string(NamedType<T>::Name()) + static_cast<char>('0' + index);
    }
};

template<typename T>
class CustomTypedNames : public ::iutest::Test {};

#if defined(TYPED_TEST_SUITE)
TYPED_TEST_SUITE(CustomTypedNames, NamedTypes, TypeNameGenerator);
#else
IUTEST_TYPED_TEST_SUITE(CustomTypedNames, NamedTypes, TypeNameGenerator);
#endif

TYPED_TEST(CustomTypedNames, First)
{
    const ::std::string expected = ::std::string("CustomTypedNames/") + NamedType<TypeParam>::Name();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}

TYPED_TEST(CustomTypedNames, Second)
{
    const ::std::string expected = ::std::string("CustomTypedNames/") + NamedType<TypeParam>::Name();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}

template<typename T>
class IndexedTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(IndexedTypedNames, NamedTypes, IndexedNameGenerator);

IUTEST_TYPED_TEST(IndexedTypedNames, UsesTypeAndIndex)
{
    const ::std::string expected = ::std::string("IndexedTypedNames/")
        + NamedType<TypeParam>::Name() + NamedType<TypeParam>::Index();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}

#if IUTEST_HAS_TYPED_TEST_P
#if defined(INSTANTIATE_TYPED_TEST_SUITE_P)
INSTANTIATE_TYPED_TEST_SUITE_P(Named, ParameterizedNames, NamedTypes, TypeNameGenerator);
#else
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(Named, ParameterizedNames, NamedTypes, TypeNameGenerator);
#endif
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(Indexed, ParameterizedNames, NamedTypes, IndexedNameGenerator);
#endif

#if !defined(IUTEST_USE_GTEST)
template<typename T>
class DirectCustomTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(DirectCustomTypedNames, ::iutest::Types<int, long>, TypeNameGenerator);

IUTEST_TYPED_TEST(DirectCustomTypedNames, Names)
{
    const ::std::string expected = ::std::string("DirectCustomTypedNames/") + NamedType<TypeParam>::Name();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}

#if IUTEST_HAS_TYPED_TEST_P
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(Direct, ParameterizedNames, ::iutest::Types<int, long>, TypeNameGenerator);
#endif

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
template<typename T>
class AliasTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE((Renamed, AliasTypedNames), NamedTypes, TypeNameGenerator);

IUTEST_TYPED_TEST((Renamed, AliasTypedNames), Names)
{
    const ::std::string expected = ::std::string("Renamed/") + NamedType<TypeParam>::Name();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}
#endif

#if IUTEST_HAS_TESTCASE
template<typename T>
class LegacyTypedNames : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE(LegacyTypedNames, NamedTypes, TypeNameGenerator);

IUTEST_TYPED_TEST(LegacyTypedNames, Names)
{
    const ::std::string expected = ::std::string("LegacyTypedNames/") + NamedType<TypeParam>::Name();
    IUTEST_EXPECT_STREQ(expected.c_str(), ::iuutil::GetCurrentTestSuite()->name());
}

#if IUTEST_HAS_TYPED_TEST_P
IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(Legacy, ParameterizedNames, NamedTypes, TypeNameGenerator);
#endif
#endif
#endif
#endif
#endif
