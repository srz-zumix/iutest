//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        cxx_feature_tests.cpp
 * @brief       iutest c++ feature test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "logger_tests.hpp"

#if IUTEST_HAS_CXX_HDR_ARRAY
#  include <array>  // NOLINT
#endif

#if IUTEST_HAS_NOEXCEPT_FUNCTION_TYPE

namespace
{

int f1()
{
    return 1;
}
int n1() noexcept
{
    return 1;
}
int f2()
{
    return 2;
}
int n2() noexcept
{
    return 2;
}

}   // namespace

IUTEST(NoexceptFounctionType, Assert)
{
    IUTEST_EXPECT_EQ(f1(), n1());
    IUTEST_EXPECT_LE(f1(), n1());
    IUTEST_EXPECT_GE(f1(), n1());
    IUTEST_EXPECT_LT(f1(), n2());
    IUTEST_EXPECT_GT(f2(), n1());
    IUTEST_EXPECT_NE(f1(), n2());
}

IUTEST(NoexceptFounctionType, ExpressionAssert)
{
    IUTEST_EXPECT(f1() == n1());
}

#endif

#if IUTEST_HAS_CXX_HDR_STRING_VIEW

IUTEST(StringView, Compare)
{
    ::std::string_view view = "Hello";
    IUTEST_ASSERT_EQ("Hello", view);
}

#endif

#if IUTEST_HAS_CXX_HDR_OPTIONAL

IUTEST(Optional, Compare)
{
    {
        ::std::optional<int> opt = 0;
        IUTEST_EXPECT_TRUE(opt);
        IUTEST_EXPECT_EQ(0, opt);
    }
    {
        ::std::optional<int> opt = ::std::nullopt;
        IUTEST_EXPECT_EQ(::std::nullopt, opt);
    }
    {
        static const ::std::optional<int> opt = ::std::nullopt;
        IUTEST_EXPECT_FALSE(opt);
        IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(1234, opt), "1234");
    }
}

IUTEST(Optional, PrintTo)
{
    {
        PrintToLogChecker ck("1234");
        ::std::optional<int> opt = 1234;
        IUTEST_SUCCEED() << ::iutest::PrintToString(opt);
    }
    {
        PrintToLogChecker ck("nullopt");
        ::std::optional<int> opt = ::std::nullopt;
        IUTEST_SUCCEED() << ::iutest::PrintToString(opt);
    }
}

#endif

#if IUTEST_HAS_CXX_HDR_VARIANT

IUTEST(Variant, Compare)
{
    {
        ::std::variant<int, float, ::std::string> v1 = 1234;
        ::std::variant<int, float, ::std::string> v2 = 1234;
        IUTEST_EXPECT_EQ(v1, v2);
    }
}

IUTEST(Variant, CompareRawType)
{
    ::std::variant<int, float, ::std::string> v = 1;
    IUTEST_EXPECT_EQ(1, v);
    IUTEST_EXPECT_EQ(v, 1);
    IUTEST_EXPECT_NE(0, v);
    IUTEST_EXPECT_NE(v, 0);
    IUTEST_EXPECT_LE(1, v);
    IUTEST_EXPECT_LE(v, 1);
    IUTEST_EXPECT_LT(0, v);
    IUTEST_EXPECT_LT(v, 2);
    IUTEST_EXPECT_GE(1, v);
    IUTEST_EXPECT_GE(v, 1);
    IUTEST_EXPECT_GT(2, v);
    IUTEST_EXPECT_GT(v, 0);
}

#if IUTEST_HAS_EXCEPTIONS
struct AlwaysThrow
{
    AlwaysThrow() = default;
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow(const AlwaysThrow &)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow(AlwaysThrow &&)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow &operator=(const AlwaysThrow &)
    {
        throw std::exception();
    }
    IUTEST_ATTRIBUTE_NORETURN_ AlwaysThrow &operator=(AlwaysThrow &&)
    {
        throw std::exception();
    }
};
#endif

IUTEST(Variant, PrintTo)
{
    {
        PrintToLogChecker ck("1234");
        ::std::variant<int, float, ::std::string> v = 1234;
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
    {
        PrintToLogChecker ck("test");
        ::std::variant<int, float, ::std::string> v("test");
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
    {
        PrintToLogChecker ck("monostate");
        ::std::variant<std::monostate, int, float, std::string> v;
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
#if IUTEST_HAS_EXCEPTIONS
    {
        PrintToLogChecker ck("valueless_by_exception");
        ::std::variant<int, float, AlwaysThrow> v = 0.2f;
        try
        {
            struct S { operator int() { throw 42; } };
            v.emplace<0>(S());
        }
        catch(...)
        {
            IUTEST_INFORM_TRUE(v.valueless_by_exception());
        }
        if( !v.valueless_by_exception() )
        {
            try
            {
                v = AlwaysThrow();
            }
            catch(...)
            {
                IUTEST_INFORM_TRUE(v.valueless_by_exception());
            }
        }

        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
#endif
}

#endif

#if IUTEST_HAS_CXX_HDR_ARRAY

IUTEST(StdArray, PrintTo)
{
    PrintToLogChecker ck("3, 1, 4");
    ::std::array<int, 3> ar = { { 3, 1, 4 } };
    IUTEST_SUCCEED() << ::iutest::PrintToString(ar);
}

#endif

#if IUTEST_HAS_CXX_HDR_ANY

//IUTEST(Any, Compare)
//{
//    {
//        ::std::any v1 = 1;
//        ::std::any v2 = 1;
//        IUTEST_EXPECT_EQ(v1, v2);
//    }
//}

IUTEST(Any, PrintTo)
{
    {
        //PrintToLogChecker ck("1234");
        ::std::any v = 1234;
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

#endif

IUTEST(FileSystem, Info)
{
#if defined(__cpp_lib_filesystem)
    IUTEST_SUCCEED() << "__cpp_lib_filesystem: " << __cpp_lib_filesystem;
#endif
#if defined(__cpp_lib_experimental_filesystem)
    IUTEST_SUCCEED() << "__cpp_lib_experimental_filesystem: " << __cpp_lib_experimental_filesystem;
#endif
}

#if IUTEST_HAS_STD_FILESYSTEM

IUTEST(FileSystem, PathCompare)
{
    {
        ::std::filesystem::path v1 = "a";
        ::std::filesystem::path v2 = "a";
        IUTEST_EXPECT_EQ(v1, v2);
    }
}

IUTEST(FileSystem, PathPrintTo)
{
    {
        PrintToLogChecker ck("/cxx_feature_tests.cpp");
        ::std::filesystem::path v = ::std::filesystem::absolute(__FILE__);
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

#if IUTEST_HAS_CXX2A

IUTEST(FileSystem, StatusCompare)
{
    {
        ::std::filesystem::file_status v1 = ::std::filesystem::status(__FILE__);
        ::std::filesystem::file_status v2 = ::std::filesystem::status(__FILE__);
        IUTEST_EXPECT_EQ(v1, v2);
    }
}

#endif

IUTEST(FileSystem, StatusPrintTo)
{
    {
        PrintToLogChecker ck("regular: 0");
        ::std::filesystem::file_status v = ::std::filesystem::status(__FILE__);
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

IUTEST(FileSystem, SpaceInfoPrintTo)
{
    {
        PrintToLogChecker ck("cpacity");
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::space_info v = ::std::filesystem::space(path.remove_filename());
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
    {
        PrintToLogChecker ck("free");
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::space_info v = ::std::filesystem::space(path.remove_filename());
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
    {
        PrintToLogChecker ck("available");
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::space_info v = ::std::filesystem::space(path.remove_filename());
        IUTEST_SUCCEED() << ::iutest::PrintToString(v);
    }
}

IUTEST(FileSystem, DirectoryEntryCompare)
{
    {
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::directory_entry x = *::std::filesystem::directory_iterator(path.remove_filename());
        ::std::filesystem::directory_entry v1 = x;
        ::std::filesystem::directory_entry v2 = x;
        IUTEST_EXPECT_EQ(v1, v2);
    }
}

IUTEST(FileSystem, DirectoryEntryPrintTo)
{
    {
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::path directory = path.remove_filename().append("testdata");
        PrintToLogChecker ck(directory.generic_string());
        ::std::filesystem::directory_entry x = *::std::filesystem::directory_iterator(directory);
        IUTEST_SUCCEED() << ::iutest::PrintToString(x);
    }
}

IUTEST(FileSystem, DirectoryIteratorPrintTo)
{
    {
        ::std::filesystem::path path = ::std::filesystem::absolute(__FILE__);
        ::std::filesystem::path directory = path.remove_filename().append("testdata");
        PrintToLogChecker ck(directory.generic_string());
        ::std::filesystem::directory_iterator x = ::std::filesystem::directory_iterator(directory);
        IUTEST_SUCCEED() << ::iutest::PrintToString(x);
    }
}

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
