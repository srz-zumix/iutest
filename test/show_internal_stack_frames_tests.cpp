//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        show_internal_stack_frames_tests.cpp
 * @brief       Internal stack frame flag compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000

namespace
{

bool initial_flag = false;

class InternalStackFramesFlag : public ::iutest::Test
{
protected:
    virtual void SetUp() IUTEST_CXX_OVERRIDE
    {
        IUTEST_EXPECT_EQ(initial_flag, IUTEST_FLAG_GET(show_internal_stack_frames));
    }

#if defined(IUTEST_USE_GTEST)
    virtual void TearDown() IUTEST_CXX_OVERRIDE
    {
        // GoogleTest's ordinary flag saver does not include this flag.
        IUTEST_FLAG_SET(show_internal_stack_frames, initial_flag);
    }
#endif
};

}   // namespace

IUTEST_F(InternalStackFramesFlag, FlagAPI)
{
    IUTEST_FLAG_SET(show_internal_stack_frames, true);
    IUTEST_EXPECT_TRUE(GTEST_FLAG_GET(show_internal_stack_frames));
    GTEST_FLAG_SET(show_internal_stack_frames, false);
    IUTEST_EXPECT_FALSE(IUTEST_FLAG_GET(show_internal_stack_frames));
    GTEST_FLAG_SET(show_internal_stack_frames, true);
    IUTEST_EXPECT_TRUE(IUTEST_FLAG_GET(show_internal_stack_frames));
    IUTEST_FLAG_SET(show_internal_stack_frames, false);
    IUTEST_EXPECT_FALSE(GTEST_FLAG_GET(show_internal_stack_frames));
    IUTEST_FLAG_SET(show_internal_stack_frames, !initial_flag);
}

IUTEST_F(InternalStackFramesFlag, Restored)
{
    IUTEST_EXPECT_EQ(initial_flag, GTEST_FLAG_GET(show_internal_stack_frames));
}

#if !defined(IUTEST_USE_GTEST)
IUTEST_F(InternalStackFramesFlag, ScopedRestoration)
{
    {
        ::iutest::TestFlag::ScopedGuard guard;
        IUTEST_FLAG_SET(show_internal_stack_frames, !initial_flag);
    }
    IUTEST_EXPECT_EQ(initial_flag, IUTEST_FLAG_GET(show_internal_stack_frames));
}
#endif

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    IUTEST_TERMINATE_ON_FAILURE(!IUTEST_FLAG_GET(show_internal_stack_frames));
    const int result = IUTEST_RUN_ALL_TESTS();
    IUTEST_TERMINATE_ON_FAILURE(!IUTEST_FLAG_GET(show_internal_stack_frames));
    initial_flag = true;
    GTEST_FLAG_SET(show_internal_stack_frames, true);
    const int true_result = IUTEST_RUN_ALL_TESTS();
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_FLAG_GET(show_internal_stack_frames));
    return result != 0 ? result : true_result;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}
