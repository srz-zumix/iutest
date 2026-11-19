//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_name_tests.cpp
 * @brief       gtest-compatible type name tests
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
#include <utility>

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000

#if defined(IUTEST_USE_GTEST)
namespace type_name_internal = ::testing::internal;
#else
namespace type_name_internal = ::iutest::detail;
#endif

IUTEST(TypeNameTest, CanonicalizeForStdLibVersioning)
{
    const char* const inputs[] = {
        "", "int", "std::__1::pair<int, bool>", "std::__cxx11::basic_string<char>",
        "std::__2::pair<int, bool>", "std::__debug::vector<int>",
        "std::__1::pair<std::__1::string, bool>", "std::__1", "std::__",
        "user::__1::Type", "user::Wrapper<std::__1::pair<int, bool> >",
        "notstd::__1::Type", "user::Pair<int, bool>", "std::pair<int,  bool>",
        "std::pair<int,\tbool>", "std::pair<int , bool>", "std::vector<std::pair<int, bool> >"
    };
    const char* const expected[] = {
        "", "int", "std::pair<int,bool>", "std::basic_string<char>",
        "std::pair<int,bool>", "std::vector<int>",
        "std::pair<std::__1::string,bool>", "std::__1", "std::__",
        "user::__1::Type", "user::Wrapper<std::__1::pair<int,bool> >",
        "notstd::__1::Type", "user::Pair<int,bool>", "std::pair<int, bool>",
        "std::pair<int,\tbool>", "std::pair<int ,bool>", "std::vector<std::pair<int,bool> >"
    };
    for( size_t i = 0; i < sizeof(inputs)/sizeof(inputs[0]); ++i )
    {
        IUTEST_SCOPED_TRACE(inputs[i]);
        IUTEST_EXPECT_STREQ(expected[i], type_name_internal::CanonicalizeForStdLibVersioning(inputs[i]));
    }
}

namespace type_name_test {
template<typename T, typename U>
struct Pair {};
} // namespace type_name_test

IUTEST(TypeNameTest, GetTypeName)
{
    typedef ::std::pair<int, bool> StdPair;
    typedef type_name_test::Pair<int, bool> UserPair;
#if IUTEST_HAS_RTTI
    IUTEST_EXPECT_STREQ("std::pair<int,bool>", type_name_internal::GetTypeName<StdPair>());
    IUTEST_EXPECT_STREQ("type_name_test::Pair<int,bool>", type_name_internal::GetTypeName<UserPair>());
    IUTEST_EXPECT_EQ(type_name_internal::GetTypeName<StdPair>(), type_name_internal::GetTypeName(typeid(StdPair)));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_EQ(type_name_internal::GetTypeName<StdPair>(), ::iutest::detail::PrintTypeName(typeid(StdPair)));
    IUTEST_EXPECT_EQ(type_name_internal::GetTypeName<UserPair>(), ::iutest::detail::PrintTypeName(typeid(UserPair)));
#endif
#else
    IUTEST_EXPECT_STREQ("<type>", type_name_internal::GetTypeName<StdPair>());
    IUTEST_EXPECT_STREQ("<type>", type_name_internal::GetTypeName<UserPair>());
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("int", type_name_internal::GetTypeName<int>());
    IUTEST_EXPECT_STREQ("int*", type_name_internal::GetTypeName<int*>());
#else
    IUTEST_EXPECT_STREQ("<type>", type_name_internal::GetTypeName<int>());
#endif
#endif
}

#if IUTEST_HAS_TYPED_TEST
template<typename T>
class TypeNameTypedTest : public ::iutest::Test {};

typedef ::iutest::Types< ::std::pair<int, bool> > TypeNameTypes;
IUTEST_TYPED_TEST_SUITE(TypeNameTypedTest, TypeNameTypes);

IUTEST_TYPED_TEST(TypeNameTypedTest, TypeParam)
{
#if IUTEST_HAS_RTTI
    const char* const expected = "std::pair<int,bool>";
#else
    const char* const expected = "<type>";
#endif
    const ::iutest::UnitTest* const unit_test = ::iutest::UnitTest::GetInstance();
    IUTEST_EXPECT_STREQ(expected, type_name_internal::GetTypeName<TypeParam>());
    IUTEST_EXPECT_STREQ(expected, unit_test->current_test_info()->type_param());
    IUTEST_EXPECT_STREQ(expected, unit_test->current_test_suite()->type_param());
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
