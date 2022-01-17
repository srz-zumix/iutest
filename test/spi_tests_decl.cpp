//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        spi_tests_decl.cpp
 * @brief       iutest spi test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#ifndef FAILURE_MACRO
#  error FAILURE_MACRO
#endif

#ifndef FLAVOR
#  error FLAVOR
#endif

#if !defined(IUTEST_USE_GTEST)
#  define EXPECT_NULL_STR   "(null)"
#else
#  define EXPECT_NULL_STR   ""
#endif

    FAILURE_MACRO( FLAVOR(_TRUE)(false), "" );
    FAILURE_MACRO( FLAVOR(_FALSE)(true), "" );
    FAILURE_MACRO( FLAVOR(_NULL)(reinterpret_cast<void*>(1)), "" );
    FAILURE_MACRO( FLAVOR(_NOTNULL)(reinterpret_cast<void*>(0)), "" );
    FAILURE_MACRO( FLAVOR(_SAME)(a, b), "" );
#if IUTEST_HAS_ASSERTION_NOEQUALTO_OBJECT
    FAILURE_MACRO( FLAVOR(_EQ)(ox, oy), "" );
    FAILURE_MACRO( FLAVOR(_NE)(ox, ox), "" );
#endif
    FAILURE_MACRO( FLAVOR(_EQ)(0, 1), "" );
    FAILURE_MACRO( FLAVOR(_NE)(1, 1), "" );
    FAILURE_MACRO( FLAVOR(_LE)(1, 0), "" );
    FAILURE_MACRO( FLAVOR(_LT)(1, 0), "" );
    FAILURE_MACRO( FLAVOR(_GE)(0, 1), "" );
    FAILURE_MACRO( FLAVOR(_GT)(0, 1), "" );
#if !defined(IUTEST_USE_GTEST)
    FAILURE_MACRO( FLAVOR(_FLOAT_EQ)(0, 1), "(0x" );
    FAILURE_MACRO( FLAVOR(_DOUBLE_EQ)(0, 1), "(0x" );
    FAILURE_MACRO( FLAVOR(_FLOAT_EQ)(Div(0.0f, fa), Div(0.0f, fa)), "(0x" );
    FAILURE_MACRO( FLAVOR(_DOUBLE_EQ)(Div(0.0, da), Div(0.0, da)), "(0x" );
    FAILURE_MACRO( FLAVOR(_PRED_FORMAT2)(::iutest::FloatLE , 2, 0), "(0x" );
    FAILURE_MACRO( FLAVOR(_PRED_FORMAT2)(::iutest::DoubleLE, 2, 0), "(0x" );
#else
    FAILURE_MACRO( FLAVOR(_FLOAT_EQ)(0, 1), "" );
    FAILURE_MACRO( FLAVOR(_DOUBLE_EQ)(0, 1), "" );
    FAILURE_MACRO( FLAVOR(_FLOAT_EQ)(Div(0.0f, fa), Div(0.0f, fa)), "" );
    FAILURE_MACRO( FLAVOR(_DOUBLE_EQ)(Div(0.0, da), Div(0.0, da)), "" );
    FAILURE_MACRO( FLAVOR(_PRED_FORMAT2)(::iutest::FloatLE , 2, 0), "" );
    FAILURE_MACRO( FLAVOR(_PRED_FORMAT2)(::iutest::DoubleLE, 2, 0), "" );
#endif
#if IUTEST_HAS_LONG_DOUBLE
    FAILURE_MACRO( FLAVOR(_LONG_DOUBLE_EQ)(0, 1), "(0x" );
    FAILURE_MACRO( FLAVOR(_LONG_DOUBLE_EQ)(Div(0.0l, lda), Div(0.0l, lda)), "(0x" );
    // FAILURE_MACRO( FLAVOR(_PRED_FORMAT2)(::iutest::LongDoubleLE, 2, 0), "(0x" );
#endif
    FAILURE_MACRO( FLAVOR(_COMPLEX_EQ)(::std::complex<float>(1.0f, 1.0f), 1.0f), "" );
    FAILURE_MACRO( FLAVOR(_NEAR)(0, 100, 2), "" );

    FAILURE_MACRO( FLAVOR(_STREQ)("A", "a"), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)("A", null_str), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)(null_str, "a"), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)(NULL, "a"), EXPECT_NULL_STR );
    FAILURE_MACRO( FLAVOR(_STREQ)(sa, "A"), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)("A", sa), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)(sa, sb), "" );
    FAILURE_MACRO( FLAVOR(_STREQ)(L"A", L"a"), "" );
    FAILURE_MACRO( FLAVOR(_STRNE)("a", "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRNE)(NULL, null_str), EXPECT_NULL_STR );
    FAILURE_MACRO( FLAVOR(_STRNE)(null_str, NULL), EXPECT_NULL_STR );
    FAILURE_MACRO( FLAVOR(_STRNE)(null_str, null_str), EXPECT_NULL_STR );
    FAILURE_MACRO( FLAVOR(_STRNE)(sa, "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRNE)("a", sa), "" );
    FAILURE_MACRO( FLAVOR(_STRNE)(sa, sa), "" );
    FAILURE_MACRO( FLAVOR(_STRNE)(L"a", L"a"), "" );

    FAILURE_MACRO( FLAVOR(_STRCASEEQ)("b", "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)("b", null_str), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)(null_str, "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)(sa, "b"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)("b", sa), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)(sa, sb), "" );
    FAILURE_MACRO( FLAVOR(_STRCASEEQ)(L"a", L"b"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)("a", "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)("A", "a"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)(null_str, null_str), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)(sa, "A"), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)("A", sa), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)(sa, sa), "" );
    FAILURE_MACRO( FLAVOR(_STRCASENE)(L"A", L"a"), "" );

    FAILURE_MACRO( FLAVOR(_PRED1)(IsOdd, 2), "evaluates to false, where" );
    FAILURE_MACRO( FLAVOR(_PRED2)(IsGreater, 0, 1), "evaluates to false, where" );
    FAILURE_MACRO( FLAVOR(_PRED3)(PredTest3, 0, 1, 3), "evaluates to false, where" );
    FAILURE_MACRO( FLAVOR(_PRED4)(PredTest4, 0, 1, 2, 4), "evaluates to false, where" );
    FAILURE_MACRO( FLAVOR(_PRED5)(PredTest5, 0, 1, 2, 3, 5), "evaluates to false, where" );
#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_VARIADIC_MACROS) && IUTEST_HAS_VARIADIC_TEMPLATES
    FAILURE_MACRO( FLAVOR(_PRED)(PredTest6, 0, 1, 2, 3, 4, 6), "evaluates to false, where" );
#endif

#if defined(IUTEST_OS_WINDOWS)
    FAILURE_MACRO( FLAVOR(_HRESULT_SUCCEEDED)(-1), "" );
    FAILURE_MACRO( FLAVOR(_HRESULT_FAILED)(0), "" );
    FAILURE_MACRO( FLAVOR(_HRESULT_FAILED)(100), "" );
#endif

    FAILURE_MACRO( FLAVOR(_STRIN)("b", "a"), "strstr" );
    FAILURE_MACRO( FLAVOR(_STRIN)("b", null_str), "strstr" );
    FAILURE_MACRO( FLAVOR(_STRIN)(null_str, "a"), "strstr" );

    FAILURE_MACRO( FLAVOR(_STRNOTIN)("a", "a"), "strstr" );

    FAILURE_MACRO( FLAVOR(_STRLNEQ)(1, "ab"), "strlen" );
    FAILURE_MACRO( FLAVOR(_STRLNEQ)(4, sa), "strlen" );

    FAILURE_MACRO( FLAVOR(_EQ_COLLECTIONS)(aa, aa+(sizeof(aa)/sizeof(aa[0])), ab, ab+(sizeof(ab)/sizeof(ab[0]))), "Mismatch element" );
    FAILURE_MACRO( FLAVOR(_EQ_COLLECTIONS)(ab, ab+(sizeof(ab)/sizeof(ab[0])), aa, aa+(sizeof(aa)/sizeof(aa[0]))), "Mismatch element" );
    FAILURE_MACRO( FLAVOR(_EQ_COLLECTIONS)(aa, aa+(sizeof(aa)/sizeof(aa[0])), ac, ac+(sizeof(ac)/sizeof(ac[0]))), "Mismatch in a position" );

    FAILURE_MACRO( FLAVOR(_NE_COLLECTIONS)(aa, aa+(sizeof(aa)/sizeof(aa[0])), aa2, aa2+(sizeof(aa2)/sizeof(aa2[0]))), "!=" );

    FAILURE_MACRO( FLAVOR(_EQ_RANGE)(aa, ab), "Mismatch element" );
    FAILURE_MACRO( FLAVOR(_EQ_RANGE)(ab, aa), "Mismatch element" );
    FAILURE_MACRO( FLAVOR(_EQ_RANGE)(aa, ac), "Mismatch in a position" );

    FAILURE_MACRO( FLAVOR(_NE_RANGE)(aa, aa2), "!=" );

    FAILURE_MACRO( FLAVOR(_NAN)(1), "Expected: NaN" );

#if IUTEST_HAS_REGEX
    FAILURE_MACRO( FLAVOR(_MATCHES_REGEXEQ)("te[0-9]*st", "te0123sta"), "Matches Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_MATCHES_REGEXEQ)("te[0-9]*st", null_str), "Matches Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_MATCHES_REGEXNE)("te[0-9]*st", "te0123st"), "Not Matches Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_CONTAINS_REGEXEQ)("te[0-9]*st", "a"), "Contains Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_CONTAINS_REGEXEQ)("te[0-9]*st", null_str), "Contains Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_CONTAINS_REGEXNE)("te[0-9]*st", "te0123sta"), "Contains Regex (\"te[0-9]*st\")" );
    FAILURE_MACRO( FLAVOR(_CONTAINS_REGEXNE)("te[0-9]*st", "te0123st"), "Contains Regex (\"te[0-9]*st\")" );
#endif

#if IUTEST_HAS_CXX_HDR_VARIANT
    FAILURE_MACRO( FLAVOR(_EQ)(v, 0), "Which is: 1" );
    FAILURE_MACRO( FLAVOR(_EQ)(0.1f, v), "Actual: 1" );
#endif

#undef FLAVOR

