//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        override_printers_tests.cpp
 * @brief       iutest user defined PrintTo test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

#if IUTEST_HAS_CXX_HDR_ARRAY
#  include <array>  // NOLINT
#endif

// #if IUTEST_HAS_CXX_HDR_STRING_VIEW

// IUTEST(StringView, PrintTo)
// {
//     LogChecker ck("Hello");
//     ::std::string_view view = "Hello";
//     IUTEST_SUCCEED() << ::iutest::PrintToString(view);
// }

// #endif

// #if IUTEST_HAS_CXX_HDR_OPTIONAL

// IUTEST(Optional, PrintTo)
// {
//     LogChecker ck("1234");
//     ::std::optional<int> opt = 1234;
//     IUTEST_SUCCEED() << ::iutest::PrintToString(opt);
// }

// #endif

// #if IUTEST_HAS_CXX_HDR_VARIANT

// IUTEST(Variant, PrintTo)
// {
//     LogChecker ck("1234");
//     ::std::variant<int, float, ::std::string> v = 1234;
//     IUTEST_SUCCEED() << ::iutest::PrintToString(v);
// }

// #endif

// #if IUTEST_HAS_CXX_HDR_ARRAY

// IUTEST(StdArray, PrintTo)
// {
//     LogChecker ck("3, 1, 4");
//     ::std::array<int, 3> ar = { { 3, 1, 4 } };
//     IUTEST_SUCCEED() << ::iutest::PrintToString(ar);
// }

// #endif

#if IUTEST_HAS_CXX_HDR_ANY

void PrintTo(const ::std::any&, ::iutest::iu_ostream* os)
{
    *os << "{242f0229-6f27-450d-861b-67716eb9a693}";
}

IUTEST(Any, PrintTo)
{
    LogChecker ck("{242f0229-6f27-450d-861b-67716eb9a693}");
    ::std::any v = 1234;
    IUTEST_SUCCEED() << ::iutest::PrintToString(v);
}

#endif

// #if IUTEST_USE_CXX_FILESYSTEM

// IUTEST(FileSystem, PathPrintTo)
// {
//     LogChecker ck("/cxx_feature_tests.cpp");
//     ::std::filesystem::path v = __FILE__;
//     IUTEST_SUCCEED() << ::iutest::PrintToString(v);
// }

// IUTEST(FileSystem, StatusPrintTo)
// {
//     LogChecker ck("regular: 0");
//     ::std::filesystem::file_status v = ::std::filesystem::status(__FILE__);
//     IUTEST_SUCCEED() << ::iutest::PrintToString(v);
// }

// IUTEST(FileSystem, SpaceInfoPrintTo)
// {
//     LogChecker ck("cpacity");
//     ::std::filesystem::path path = __FILE__;
//     ::std::filesystem::space_info v = ::std::filesystem::space(path.remove_filename());
//     IUTEST_SUCCEED() << ::iutest::PrintToString(v);
// }

// IUTEST(FileSystem, DirectoryEntryPrintTo)
// {
//     ::std::filesystem::path path = __FILE__;
//     ::std::filesystem::path directory = path.remove_filename().append("testdata");
//     LogChecker ck(directory.generic_string());
//     ::std::filesystem::directory_entry x = *::std::filesystem::directory_iterator(directory);
//     IUTEST_SUCCEED() << ::iutest::PrintToString(x);
// }

// IUTEST(FileSystem, DirectoryIteratorPrintTo)
// {
//     ::std::filesystem::path path = __FILE__;
//     ::std::filesystem::path directory = path.remove_filename().append("testdata");
//     LogChecker ck(directory.generic_string());
//     ::std::filesystem::directory_iterator x = ::std::filesystem::directory_iterator(directory);
//     IUTEST_SUCCEED() << ::iutest::PrintToString(x);
// }

// #endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
