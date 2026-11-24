//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        optional_tests.cpp
 * @brief       Internal optional tests
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

#if IUTEST_HAS_CXX11 && IIUT_HAS_OPTIONAL_VALUE_MOVE_
#  include <memory>
#endif

namespace {

using ::iutest::stl::nullpot_t;
using ::iutest::stl::optional;

struct Tracked
{
    static int constructions;
    static int destructions;

    explicit Tracked(int v) : data(v) { ++constructions; }
    Tracked(const Tracked& rhs) : data(rhs.data) { ++constructions; }
    ~Tracked() { ++destructions; }

    Tracked& operator = (const Tracked& rhs) { data = rhs.data; return *this; }

    int data;
};

int Tracked::constructions = 0;
int Tracked::destructions = 0;

IUTEST(Optional, Basics)
{
    optional<int> empty, value(1);
    optional<int> tagged((nullpot_t()));
    optional<int> copied_empty(empty), copy(value);
    const optional<int>& cvalue = value;
    const optional<int>& cempty = empty;

    IUTEST_EXPECT_FALSE(empty.has_value());
    IUTEST_EXPECT_FALSE(tagged);
    IUTEST_EXPECT_FALSE(copied_empty);
    IUTEST_EXPECT_TRUE(value);
    IUTEST_EXPECT_NULL(empty.ptr());
    IUTEST_EXPECT_NULL(cempty.ptr());
    IUTEST_EXPECT_EQ(9, cempty.value_or(9));
    IUTEST_EXPECT_EQ(1, cvalue.value_or(9));
    IUTEST_EXPECT_EQ(1, copy.value());
    IUTEST_EXPECT_EQ(1, *cvalue);
    IUTEST_EXPECT_EQ(&cvalue.value(), cvalue.ptr());
    IUTEST_EXPECT_EQ(&value.value(), value.ptr());

    *value = 2;
    empty = value;
    IUTEST_ASSERT_TRUE(empty.has_value());
    IUTEST_EXPECT_EQ(2, empty.value());
    copy = value;
    IUTEST_EXPECT_EQ(2, copy.value());
    value = cvalue;
    IUTEST_EXPECT_EQ(2, value.value());

    empty = tagged;
    IUTEST_EXPECT_FALSE(empty);
    empty = cempty;
    IUTEST_EXPECT_FALSE(empty);
    empty = 3;
    IUTEST_EXPECT_EQ(3, empty.value());
    empty = 4;
    IUTEST_EXPECT_EQ(4, empty.value());
    empty = nullpot_t();
    IUTEST_EXPECT_FALSE(empty);
}

IUTEST(Optional, Lifetime)
{
    Tracked::constructions = Tracked::destructions = 0;
    {
        optional<Tracked> empty;
        optional<Tracked> copied_empty(empty);
        empty.reset();
        IUTEST_EXPECT_FALSE(copied_empty);
        IUTEST_EXPECT_EQ(0, Tracked::constructions);
        IUTEST_EXPECT_EQ(0, Tracked::destructions);

        optional<Tracked> value(3);
        IUTEST_ASSERT_TRUE(value.has_value());
        IUTEST_EXPECT_EQ(3, value->data);
        const optional<Tracked> copy(value);
        IUTEST_EXPECT_EQ(3, copy->data);
        IUTEST_EXPECT_NE(value.ptr(), copy.ptr());
        empty = copy;
        IUTEST_EXPECT_EQ(3, Tracked::constructions);
        IUTEST_EXPECT_EQ(0, Tracked::destructions);
        value->data = 5;
        empty = value;
        IUTEST_EXPECT_EQ(5, empty->data);
        empty.reset();
        empty.reset();
        IUTEST_EXPECT_NULL(empty.ptr());
        IUTEST_EXPECT_EQ(3, Tracked::constructions);
        IUTEST_EXPECT_EQ(1, Tracked::destructions);
        value = optional<Tracked>();
        IUTEST_EXPECT_FALSE(value);
        IUTEST_EXPECT_EQ(2, Tracked::destructions);
    }
    IUTEST_EXPECT_EQ(3, Tracked::destructions);
}

#if defined(__GNUC__) || defined(__clang__) || (defined(_MSC_VER) && _MSC_VER >= 1300)
#  if defined(__GNUC__) || defined(__clang__)
struct __attribute__((aligned(64))) Aligned
#  else
struct __declspec(align(64)) Aligned
#  endif
{
    explicit Aligned(int v) : data(v) {}
    int data;
    char padding[60];
};

IUTEST(Optional, Alignment)
{
    optional<Aligned> values[3];
    const Aligned source(42);
    for( int i = 0; i < 3; ++i ) {
        values[i] = source;
        IUTEST_EXPECT_EQ(0U, reinterpret_cast<size_t>(values[i].ptr()) % 64U);
        IUTEST_EXPECT_EQ(42, values[i]->data);
    }
}
#endif

#if IUTEST_HAS_EXCEPTIONS
struct Throwing
{
    static bool fail;
    explicit Throwing(int v) : data(v) {}
    Throwing(const Throwing& rhs) : data(rhs.data) { if( fail ) { throw 1; } }
    Throwing& operator = (const Throwing& rhs)
    {
        if( fail ) { throw 1; }
        data = rhs.data;
        return *this;
    }
    int data;
};

bool Throwing::fail = false;

IUTEST(Optional, EmptyAccess)
{
    optional<Tracked> empty;
    const optional<Tracked>& cempty = empty;
    IUTEST_EXPECT_THROW(empty.value(), ::iutest::stl::bad_optional_access);
    IUTEST_EXPECT_THROW(cempty.value(), ::iutest::stl::bad_optional_access);
    IUTEST_EXPECT_THROW(*empty, ::iutest::stl::bad_optional_access);
    IUTEST_EXPECT_THROW(cempty.operator->(), ::iutest::stl::bad_optional_access);
}

IUTEST(Optional, FailedConstructionAndAssignment)
{
    const Throwing source(7);
    const optional<Throwing> original(source);
    optional<Throwing> empty, engaged(3);
    Throwing::fail = true;
    IUTEST_EXPECT_THROW((optional<Throwing>(source)), int);
    IUTEST_EXPECT_THROW((optional<Throwing>(original)), int);
    IUTEST_EXPECT_THROW(empty = source, int);
    IUTEST_EXPECT_FALSE(empty);
    IUTEST_EXPECT_THROW(empty = original, int);
    IUTEST_EXPECT_NULL(empty.ptr());
    IUTEST_EXPECT_THROW(engaged = source, int);
    IUTEST_EXPECT_THROW(engaged = original, int);
    IUTEST_EXPECT_TRUE(engaged.has_value());
    Throwing::fail = false;
    IUTEST_ASSERT_TRUE(engaged.has_value());
    IUTEST_EXPECT_EQ(3, engaged->data);
    empty = original;
    IUTEST_EXPECT_EQ(7, empty->data);
}
#endif

#if IUTEST_HAS_CXX11 && IIUT_HAS_OPTIONAL_VALUE_MOVE_
IUTEST(Optional, MoveOnlyValue)
{
    typedef ::std::unique_ptr<int> Pointer;
    Pointer source(new int(5));
    optional<Pointer> value(::std::move(source));
    IUTEST_EXPECT_NULL(source.get());
    IUTEST_EXPECT_EQ(5, **value);

    optional<Pointer> empty;
    empty = Pointer(new int(6));
    IUTEST_EXPECT_EQ(6, **empty);
    empty = Pointer();
    IUTEST_EXPECT_TRUE(empty);
    IUTEST_EXPECT_NULL(empty->get());
    empty.reset();
    IUTEST_EXPECT_FALSE(empty);
}
#endif

#if IUTEST_HAS_RVALUE_REFS && IUTEST_HAS_DELETED_FUNCTIONS
struct CopyOnly
{
    explicit CopyOnly(int v) : data(v) {}
    CopyOnly(const CopyOnly& rhs) : data(rhs.data) {}
    CopyOnly& operator = (const CopyOnly& rhs) { data = rhs.data; return *this; }
    CopyOnly(CopyOnly&&) = delete;
    CopyOnly& operator = (CopyOnly&&) = delete;
    int data;
};

IUTEST(Optional, CopyOnlyTemporary)
{
    optional<CopyOnly> value((CopyOnly(5)));
    IUTEST_EXPECT_EQ(5, value->data);
    optional<CopyOnly> empty;
    empty = CopyOnly(6);
    IUTEST_EXPECT_EQ(6, empty->data);
    empty = CopyOnly(7);
    IUTEST_EXPECT_EQ(7, empty->data);
}
#endif

} // namespace

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
