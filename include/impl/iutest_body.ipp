﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_body.ipp
 * @brief       iris unit test テスト単体クラス ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_BODY_IPP_3EEA6706_9954_4330_B292_129667FA6B96_
#define INCG_IRIS_IUTEST_BODY_IPP_3EEA6706_9954_4330_B292_129667FA6B96_

//======================================================================
// include
#include "../iutest_body.hpp"

namespace iutest
{

IUTEST_IPP_INLINE void Test::RecordPropertyString(const ::std::string& key, const ::std::string& value)
{
    TestProperty prop(key, value);
    TestRecordPropertyHelper::RecordProperty(prop);
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
IUTEST_IPP_INLINE void Test::RecordProperty(const ::std::string& key, const ::std::string& value)
{
    RecordPropertyString(key, value);
}
#endif

IUTEST_IPP_INLINE void Test::Run(detail::iuITestInfoMediator* test_info)
{
    m_test_info = test_info;
    test_info_ = test_info->ptr();

#if IUTEST_HAS_GENRAND
    unsigned int seed = TestEnv::get_random_seed();
    if( seed == 0 )
    {
        seed = detail::GetIndefiniteValue();
    }
    m_random_seed = seed;
    m_random.init(seed);
#endif

    SetUp();

    if( !HasFailure() && !IsSkipped() )
    {
        Body();
    }

    TearDown();

    test_info_ = NULL;
    m_test_info = NULL;
}

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_BODY_IPP_3EEA6706_9954_4330_B292_129667FA6B96_
