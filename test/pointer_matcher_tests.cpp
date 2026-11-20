//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        pointer_matcher_tests.cpp
 * @brief       Pointer matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01110000)

#if IUTEST_HAS_CXX11
#include <memory>
#endif

using ::iutest::matchers::Eq;
using ::iutest::matchers::IsNull;
using ::iutest::matchers::NotNull;
using ::iutest::matchers::Pointer;

namespace {

struct Holder
{
    typedef int element_type;
    explicit Holder(int* p) : ptr(p) {}
    int* get() const { return ptr; }
    int* ptr;
};

int failure_value = 1;
int failure_other = 1;
int* failure_ptr = &failure_value;
#if IUTEST_HAS_CXX11
::std::unique_ptr<int> failure_unique(new int(1));
::std::shared_ptr<int> failure_shared(new int(1));
#endif

} // namespace

IUTEST(PointerMatcher, RawPointer)
{
    int value = 1;
    int other = 1;
    int* ptr = &value;
    IUTEST_EXPECT_THAT(ptr, Pointer(Eq(&value)));
    IUTEST_EXPECT_THAT(ptr, Pointer(&value));
    IUTEST_EXPECT_THAT(ptr, Pointer(NotNull()));
    IUTEST_EXPECT_THAT(static_cast<int*>(NULL), Pointer(IsNull()));
    IUTEST_EXPECT_THAT(&other, Pointer(Eq(&other)));
}

IUTEST(PointerMatcher, PointerLike)
{
    int value = 1;
    const Holder holder(&value);
    IUTEST_EXPECT_THAT(holder, Pointer(Eq(&value)));
}

#if IUTEST_HAS_CXX11
IUTEST(PointerMatcher, UniquePtr)
{
    ::std::unique_ptr<int> ptr(new int(1));
    IUTEST_EXPECT_THAT(ptr, Pointer(Eq(ptr.get())));
    IUTEST_EXPECT_THAT(ptr, Pointer(NotNull()));
    ptr.reset();
    IUTEST_EXPECT_THAT(ptr, Pointer(IsNull()));
}

IUTEST(PointerMatcher, SharedPtr)
{
    ::std::shared_ptr<int> ptr(new int(1));
    IUTEST_EXPECT_THAT(ptr, Pointer(Eq(ptr.get())));
    IUTEST_EXPECT_THAT(ptr, Pointer(NotNull()));
    ptr.reset();
    IUTEST_EXPECT_THAT(ptr, Pointer(IsNull()));
}
#endif

#if !defined(IUTEST_USE_GMOCK)
#  define CHECK_POINTER_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE(x, str)
#else
#  define CHECK_POINTER_FAILURE(x, str) IUTEST_EXPECT_FATAL_FAILURE(x, "")
#endif

IUTEST(PointerMatcher, FailureMessage)
{
    CHECK_POINTER_FAILURE(IUTEST_ASSERT_THAT(failure_ptr, Pointer(Eq(&failure_other))), "Pointer:");
    CHECK_POINTER_FAILURE(IUTEST_ASSERT_THAT(failure_ptr, Pointer(IsNull())), "Pointer: Is Null");
#if IUTEST_HAS_CXX11
    CHECK_POINTER_FAILURE(IUTEST_ASSERT_THAT(failure_unique, Pointer(IsNull())), "Pointer: Is Null");
    CHECK_POINTER_FAILURE(IUTEST_ASSERT_THAT(failure_shared, Pointer(IsNull())), "Pointer: Is Null");
#endif
}

#undef CHECK_POINTER_FAILURE

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
