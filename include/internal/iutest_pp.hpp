//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_pp.hpp
 * @brief		iris unit test プリプロセッサ 定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_pp_HPP_E8F72184_9C72_4e74_B581_A1F51F291F3A_
#define INCG_IRIS_iutest_pp_HPP_E8F72184_9C72_4e74_B581_A1F51F291F3A_

//======================================================================
// define

/**
 * @brief	コピー禁止定義
*/
#define IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeName)	\
	TypeName( const TypeName& );						\
	TypeName& operator = ( const TypeName& )

/**
 * @brief	コピー/ムーブ禁止定義
*/
#if defined(IUTEST_HAS_RVALUE_REFS) && IUTEST_HAS_RVALUE_REFS
#  define IUTEST_PP_DISALLOW_MOVE_AND_COPY_AND_ASSIGN(TypeName)	\
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeName);				\
	TypeName( TypeName&& rhs );									\
	TypeName& operator = ( TypeName&& )
#else
#  define IUTEST_PP_DISALLOW_MOVE_AND_COPY_AND_ASSIGN(TypeName)	\
	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeName)
#endif

#ifndef IUTEST_PP_TOSTRING
#  define IUTEST_PP_TOSTRING(z_)	IUTEST_PP_TOSTRING_(z_)
#endif
#define IUTEST_PP_TOSTRING_(z_)		#z_

#ifndef IUTEST_PP_CAT
#  define IUTEST_PP_CAT(a_, b_)		IUTEST_PP_CAT_(a_, b_)
#endif
#define IUTEST_PP_CAT_(a_, b_)		a_##b_

#define IUTEST_PP_EXPAND(x)			x
#define IUTEST_PP_EMPTY

#ifdef IUTEST_HAS_COUNTER_MACRO
#  define IUTEST_PP_COUNTER			__COUNTER__
#else
#  define IUTEST_PP_COUNTER			__LINE__
#endif

#define IUTEST_UNUSED_VAR(x)		(void)(x)

#define IUTEST_PP_DEC(n)	IUTEST_PP_DEC_I(n)
#define IUTEST_PP_DEC_I(n)	IUTEST_PP_DEC_##n
#define IUTEST_PP_DEC_1		0
#define IUTEST_PP_DEC_2		1
#define IUTEST_PP_DEC_3		2
#define IUTEST_PP_DEC_4		3
#define IUTEST_PP_DEC_5		4
#define IUTEST_PP_DEC_6		5
#define IUTEST_PP_DEC_7		6
#define IUTEST_PP_DEC_8		7
#define IUTEST_PP_DEC_9		8
#define IUTEST_PP_DEC_10	9
#define IUTEST_PP_DEC_11	10
#define IUTEST_PP_DEC_12	11
#define IUTEST_PP_DEC_13	12
#define IUTEST_PP_DEC_14	13
#define IUTEST_PP_DEC_15	14
#define IUTEST_PP_DEC_16	15
#define IUTEST_PP_DEC_17	16
#define IUTEST_PP_DEC_18	17
#define IUTEST_PP_DEC_19	18
#define IUTEST_PP_DEC_20	19
#define IUTEST_PP_DEC_21	20
#define IUTEST_PP_DEC_22	21
#define IUTEST_PP_DEC_23	22
#define IUTEST_PP_DEC_24	23
#define IUTEST_PP_DEC_25	24
#define IUTEST_PP_DEC_26	25
#define IUTEST_PP_DEC_27	26
#define IUTEST_PP_DEC_28	27
#define IUTEST_PP_DEC_29	28
#define IUTEST_PP_DEC_30	29
#define IUTEST_PP_DEC_31	30
#define IUTEST_PP_DEC_32	31
#define IUTEST_PP_DEC_33	32
#define IUTEST_PP_DEC_34	33
#define IUTEST_PP_DEC_35	34
#define IUTEST_PP_DEC_36	35
#define IUTEST_PP_DEC_37	36
#define IUTEST_PP_DEC_38	37
#define IUTEST_PP_DEC_39	38
#define IUTEST_PP_DEC_40	39
#define IUTEST_PP_DEC_41	40
#define IUTEST_PP_DEC_42	41
#define IUTEST_PP_DEC_43	42
#define IUTEST_PP_DEC_44	43
#define IUTEST_PP_DEC_45	44
#define IUTEST_PP_DEC_46	45
#define IUTEST_PP_DEC_47	46
#define IUTEST_PP_DEC_48	47
#define IUTEST_PP_DEC_49	48
#define IUTEST_PP_DEC_50	49
#define IUTEST_PP_DEC_51	50
#define IUTEST_PP_DEC_52	51
#define IUTEST_PP_DEC_53	52
#define IUTEST_PP_DEC_54	53
#define IUTEST_PP_DEC_55	54
#define IUTEST_PP_DEC_56	55
#define IUTEST_PP_DEC_57	56
#define IUTEST_PP_DEC_58	57
#define IUTEST_PP_DEC_59	58
#define IUTEST_PP_DEC_60	59
#define IUTEST_PP_DEC_61	60
#define IUTEST_PP_DEC_62	61
#define IUTEST_PP_DEC_63	62
#define IUTEST_PP_DEC_64	63
#define IUTEST_PP_DEC_65	64
#define IUTEST_PP_DEC_66	65
#define IUTEST_PP_DEC_67	66
#define IUTEST_PP_DEC_68	67
#define IUTEST_PP_DEC_69	68
#define IUTEST_PP_DEC_70	69
#define IUTEST_PP_DEC_71	70
#define IUTEST_PP_DEC_72	71
#define IUTEST_PP_DEC_73	72
#define IUTEST_PP_DEC_74	73
#define IUTEST_PP_DEC_75	74
#define IUTEST_PP_DEC_76	75
#define IUTEST_PP_DEC_77	76
#define IUTEST_PP_DEC_78	77
#define IUTEST_PP_DEC_79	78
#define IUTEST_PP_DEC_80	79
#define IUTEST_PP_DEC_81	80
#define IUTEST_PP_DEC_82	81
#define IUTEST_PP_DEC_83	82
#define IUTEST_PP_DEC_84	83
#define IUTEST_PP_DEC_85	84
#define IUTEST_PP_DEC_86	85
#define IUTEST_PP_DEC_87	86
#define IUTEST_PP_DEC_88	87
#define IUTEST_PP_DEC_89	88
#define IUTEST_PP_DEC_90	89
#define IUTEST_PP_DEC_91	90
#define IUTEST_PP_DEC_92	91
#define IUTEST_PP_DEC_93	92
#define IUTEST_PP_DEC_94	93
#define IUTEST_PP_DEC_95	94
#define IUTEST_PP_DEC_96	95
#define IUTEST_PP_DEC_97	96
#define IUTEST_PP_DEC_98	97
#define IUTEST_PP_DEC_99	98
#define IUTEST_PP_DEC_100	99

#define IUTEST_PP_INC(n)	IUTEST_PP_INC_I(n)
#define IUTEST_PP_INC_I(n)	IUTEST_PP_INC_##n
#define IUTEST_PP_INC_0		1
#define IUTEST_PP_INC_1		2
#define IUTEST_PP_INC_2		3
#define IUTEST_PP_INC_3		4
#define IUTEST_PP_INC_4		5
#define IUTEST_PP_INC_5		6
#define IUTEST_PP_INC_6		7
#define IUTEST_PP_INC_7		8
#define IUTEST_PP_INC_8		9
#define IUTEST_PP_INC_9		10
#define IUTEST_PP_INC_10	11
#define IUTEST_PP_INC_11	12
#define IUTEST_PP_INC_12	13
#define IUTEST_PP_INC_13	14
#define IUTEST_PP_INC_14	15
#define IUTEST_PP_INC_15	16
#define IUTEST_PP_INC_16	17
#define IUTEST_PP_INC_17	18
#define IUTEST_PP_INC_18	19
#define IUTEST_PP_INC_19	20
#define IUTEST_PP_INC_20	21
#define IUTEST_PP_INC_21	22
#define IUTEST_PP_INC_22	23
#define IUTEST_PP_INC_23	24
#define IUTEST_PP_INC_24	25
#define IUTEST_PP_INC_25	26
#define IUTEST_PP_INC_26	27
#define IUTEST_PP_INC_27	28
#define IUTEST_PP_INC_28	29
#define IUTEST_PP_INC_29	30
#define IUTEST_PP_INC_30	31
#define IUTEST_PP_INC_31	32
#define IUTEST_PP_INC_32	33
#define IUTEST_PP_INC_33	34
#define IUTEST_PP_INC_34	35
#define IUTEST_PP_INC_35	36
#define IUTEST_PP_INC_36	37
#define IUTEST_PP_INC_37	38
#define IUTEST_PP_INC_38	39
#define IUTEST_PP_INC_39	40
#define IUTEST_PP_INC_40	41
#define IUTEST_PP_INC_41	42
#define IUTEST_PP_INC_42	43
#define IUTEST_PP_INC_43	44
#define IUTEST_PP_INC_44	45
#define IUTEST_PP_INC_45	46
#define IUTEST_PP_INC_46	47
#define IUTEST_PP_INC_47	48
#define IUTEST_PP_INC_48	49
#define IUTEST_PP_INC_49	50
#define IUTEST_PP_INC_50	51
#define IUTEST_PP_INC_51	52
#define IUTEST_PP_INC_52	53
#define IUTEST_PP_INC_53	54
#define IUTEST_PP_INC_54	55
#define IUTEST_PP_INC_55	56
#define IUTEST_PP_INC_56	57
#define IUTEST_PP_INC_57	58
#define IUTEST_PP_INC_58	59
#define IUTEST_PP_INC_59	60
#define IUTEST_PP_INC_60	61
#define IUTEST_PP_INC_61	62
#define IUTEST_PP_INC_62	63
#define IUTEST_PP_INC_63	64
#define IUTEST_PP_INC_64	65
#define IUTEST_PP_INC_65	66
#define IUTEST_PP_INC_66	67
#define IUTEST_PP_INC_67	68
#define IUTEST_PP_INC_68	69
#define IUTEST_PP_INC_69	70
#define IUTEST_PP_INC_70	71
#define IUTEST_PP_INC_71	72
#define IUTEST_PP_INC_72	73
#define IUTEST_PP_INC_73	74
#define IUTEST_PP_INC_74	75
#define IUTEST_PP_INC_75	76
#define IUTEST_PP_INC_76	77
#define IUTEST_PP_INC_77	78
#define IUTEST_PP_INC_78	79
#define IUTEST_PP_INC_79	80
#define IUTEST_PP_INC_80	81
#define IUTEST_PP_INC_81	82
#define IUTEST_PP_INC_82	83
#define IUTEST_PP_INC_83	84
#define IUTEST_PP_INC_84	85
#define IUTEST_PP_INC_85	86
#define IUTEST_PP_INC_86	87
#define IUTEST_PP_INC_87	88
#define IUTEST_PP_INC_88	89
#define IUTEST_PP_INC_89	90
#define IUTEST_PP_INC_90	91
#define IUTEST_PP_INC_91	92
#define IUTEST_PP_INC_92	93
#define IUTEST_PP_INC_93	94
#define IUTEST_PP_INC_94	95
#define IUTEST_PP_INC_95	96
#define IUTEST_PP_INC_96	97
#define IUTEST_PP_INC_97	98
#define IUTEST_PP_INC_98	99
#define IUTEST_PP_INC_99	100

#define IUTEST_PP_ENUM_SHIFTED_PARAMS(n, param)			IUTEST_PP_ENUM_SHIFTED_PARAMS_M(n, IUTEST_PP_ENUM_SHIFTED_PARAM_MACRO, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAM_MACRO(param, i)	IUTEST_PP_CAT(param, i)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_M(n, m, param)	IUTEST_PP_ENUM_SHIFTED_PARAMS_I(n, m, param)

#define IUTEST_PP_ENUM_SHIFTED_PARAMS_I(n, m, param)	IUTEST_PP_CAT(IUTEST_PP_ENUM_SHIFTED_PARAMS_, IUTEST_PP_DEC(n))(0, m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_0(i, m, param)	m(param, i)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_1(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_0 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_2(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_1 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_3(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_2 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_4(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_3 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_5(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_4 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_6(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_5 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_7(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_6 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_8(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_7 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_9(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_8 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_10(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_9 (IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_11(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_10(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_12(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_11(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_13(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_12(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_14(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_13(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_15(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_14(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_16(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_15(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_17(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_16(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_18(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_17(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_19(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_18(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_20(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_19(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_21(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_20(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_22(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_21(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_23(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_22(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_24(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_23(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_25(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_24(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_26(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_25(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_27(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_26(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_28(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_27(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_29(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_28(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_30(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_29(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_31(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_30(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_32(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_31(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_33(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_32(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_34(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_33(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_35(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_34(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_36(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_35(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_37(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_36(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_38(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_37(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_39(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_38(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_40(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_39(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_41(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_40(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_42(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_41(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_43(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_42(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_44(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_43(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_45(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_44(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_46(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_45(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_47(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_46(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_48(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_47(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_49(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_48(IUTEST_PP_INC(i), m, param)
#define IUTEST_PP_ENUM_SHIFTED_PARAMS_50(i, m, param)	m(param, i), IUTEST_PP_ENUM_SHIFTED_PARAMS_49(IUTEST_PP_INC(i), m, param)

#endif
