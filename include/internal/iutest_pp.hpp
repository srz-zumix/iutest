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
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_pp_HPP_E8F72184_9C72_4e74_B581_A1F51F291F3A_
#define INCG_IRIS_iutest_pp_HPP_E8F72184_9C72_4e74_B581_A1F51F291F3A_

//======================================================================
// define

#define IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(TypeName)	\
	TypeName( const TypeName& );						\
	TypeName& operator = ( const TypeName& )

#ifndef IUTEST_PP_TOSTRING
#  define IUTEST_PP_TOSTRING(z_)	IUTEST_PP_TOSTRING_(z_)
#endif
#define IUTEST_PP_TOSTRING_(z_)		#z_

#ifndef IUTEST_PP_CAT
#  define IUTEST_PP_CAT(a_, b_)		IUTEST_PP_CAT_(a_, b_)
#endif
#define IUTEST_PP_CAT_(a_, b_)		a_##b_

#define IUTEST_UNUSED_VAR(x)		(void)x

#define IUTEST_PP_DEC(n)	IUTEST_PP_DEC_##n
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

#endif
