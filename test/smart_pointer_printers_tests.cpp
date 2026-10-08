//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        smart_pointer_printers_tests.cpp
 * @brief       smart pointer printer test
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

#if IUTEST_HAS_CXX11 && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)

#include <memory>

void ExpectPointerPrint(const ::std::string& result, const ::std::string& prefix, const ::std::string& suffix)
{
    IUTEST_ASSERT_GT(result.size(), prefix.size() + suffix.size());
    IUTEST_EXPECT_EQ(prefix, result.substr(0, prefix.size()));
    IUTEST_EXPECT_EQ(suffix, result.substr(result.size() - suffix.size()));
    const ::std::string address = result.substr(prefix.size(), result.size() - prefix.size() - suffix.size());
    IUTEST_EXPECT_EQ(::std::string::npos, address.find_first_not_of("0123456789abcdefABCDEF"));
}

struct VoidDeleter
{
    void operator () (void* ptr) const { delete static_cast<int*>(ptr); }
};

IUTEST(SmartPointerPrintersTest, Null)
{
    IUTEST_EXPECT_STREQ("(nullptr)", ::iutest::PrintToString(::std::unique_ptr<int>()));
    IUTEST_EXPECT_STREQ("(nullptr)", ::iutest::PrintToString(::std::shared_ptr<int>()));
    IUTEST_EXPECT_STREQ("(nullptr)", ::iutest::PrintToString(::std::unique_ptr<int[]>()));
    IUTEST_EXPECT_STREQ("(nullptr)", ::iutest::PrintToString(::std::shared_ptr<void>()));
}

IUTEST(SmartPointerPrintersTest, Value)
{
    ::std::unique_ptr<int> unique(new int(42));
    ::std::shared_ptr<int> shared(new int(42));
    ExpectPointerPrint(::iutest::PrintToString(unique), "(ptr = 0x", ", value = 42)");
    ExpectPointerPrint(::iutest::PrintToString(shared), "(ptr = 0x", ", value = 42)");

    ::std::unique_ptr< ::std::unique_ptr<int> > nested(new ::std::unique_ptr<int>(new int(42)));
    const ::std::string nested_result = ::iutest::PrintToString(nested);
    IUTEST_EXPECT_NE(::std::string::npos, nested_result.find(", value = (ptr = 0x"));
    IUTEST_EXPECT_EQ(", value = 42))", nested_result.substr(nested_result.size() - 14));
}

IUTEST(SmartPointerPrintersTest, VoidAndArray)
{
    ::std::unique_ptr<void, VoidDeleter> unique_void(new int(42));
    ::std::shared_ptr<void> shared_void(new int(42), VoidDeleter());
    ::std::unique_ptr<int[]> unique_array(new int[2]);
    ExpectPointerPrint(::iutest::PrintToString(unique_void), "(0x", ")");
    ExpectPointerPrint(::iutest::PrintToString(shared_void), "(0x", ")");
    ExpectPointerPrint(::iutest::PrintToString(unique_array), "(0x", ")");
#if IUTEST_HAS_CXX17
    ::std::shared_ptr<int[]> shared_array(new int[2]);
    ExpectPointerPrint(::iutest::PrintToString(shared_array), "(0x", ")");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
