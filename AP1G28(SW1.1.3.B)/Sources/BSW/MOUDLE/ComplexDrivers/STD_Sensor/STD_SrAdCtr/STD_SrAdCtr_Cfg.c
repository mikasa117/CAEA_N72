/* polyspace<MISRA-C3:1.1:Not a defect:Justified> NO fluence */
/*******************************************************************************
|  File Name:  STD_SrAdCtr_Cfg.h
|  Description:  Implementation of the Sensor Config Management
|-------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA).
|     All rights are reserved by CAEA.
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| XYJ           XiaYaJun          CAEA
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   -----------------------------------------
| 2018-05-23    01.00.00     XYJ       Creation
| 2019-12-27       /         XJW       Modified for AC-DI18
|******************************************************************************/

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "STD_SrAdCtr.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Enum Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    Global variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local KAM variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Static local variables Declaration
|******************************************************************************/

/*******************************************************************************
|    Table Const Definition
|******************************************************************************/

/*******************************************************************************
|    Static Local Functions Declaration
|******************************************************************************/
#if (SRM_TYPE_AD_TABLE_CLASS == SRM_ENABLE)
/*******************************************************************************
|    Function Source Code
|******************************************************************************/
#if 0
/*TFT*/
const uint32 KaSRCTR_dw_DatSensorRes[167]=
{
	166,
	195652 	,  //-40
	184917 	,
	174845 	,
	165391 	,
	156512 	,
	148171 	,
	140330 	,
	132957 	,
	126021 	,
	119493 	,
	113347 	,
	107564 	,
	102115 	,
	96977 	,
	92131 	,
	87558 	,
	83242 	,
	79166 	,
	75315 	,
	71676 	,
	68236 	,
	64990 	,
	61919 	,
	59011 	,
	56257 	,
	53649 	,
	51177 	,
	48834 	,
	46613 	,
	44505 	,
	42506 	,
	40599 	,
	38790 	,
	37072 	,
	35441 	,
	33892 	,
    32419 	,
	31020 	,
	29689 	,
	28423 	,
	27219 	,
	26076 	,
	24988 	,
	23951 	,
	22963 	,
	22021 	,
	21123 	,
	20267 	,
	19450 	,
	18670 	,
	17925 	,
	17213 	,
	16534 	,
	15885 	,
	15265 	,
	14673 	,
	14107 	,
	13566 	,
	13048 	,
	12554 	,
	12080 	,
	11628 	,
	11194 	,
	10779 	,
	10381 	,
	10000 	,
	9634 	,
	9284 	,
	8947 	,
	8624 	,
	8315 	,//30
	8018 	,
	7734 	,
	7461 	,
	7199 	,
	6948 	,
	6707 	,
	6475 	,
	6253 	,
	6039 	,
	5834 	,//40
	5636 	,
	5445 	,
	5262 	,
	5086 	,
	4917 	,
	4754 	,
	4597 	,
	4446 	,
	4301 	,
	4161 	,//50
	4026 	,
	3896 	,
	3771 	,
	3651 	,
	3535 	,
	3423 	,
	3315 	,
	3211 	,
	3111 	,
	3014 	,//60
	2922 	,
	2834 	,
	2748 	,//63
	2666 	,
	2586 	,
	2509 	,
	2435 	,//67
	2364 	,
	2294 	,
	2228 	,//70
	2163 	,
	2100 	,
	2040 	,
	1981 	,
	1925 	,
	1870 	,
	1817 	,
	1766 	,
	1716 	,
	1669 	,//80
	1622 	,
	1578 	,
	1535 	,
	1493 	,
	1452 	,//85
	1413 	,
	1375 	,
	1338 	,
	1303 	,
	1268 	,
	1234 	,
	1202 	,
	1170 	,
	1139 	,
	1110 	,
	1081 	,
	1053 	,
	1026 	,
	999 	,
	974 	,
	949 	,
	925 	,
	902 	,
	880 	,
	858 	,
	837 	,
	816 	,
	796 	,
	777 	,
	758 	,
	740 	,
	722 	,
	705 	,
	688 	,
	672 	,
	656 	,
	640 	,
	625 	,
	611 	,
	596 	,
	583 	,
	569 	,
	556 	,
	544 	,
	531
};
#endif 

/*TS2*/
const uint32 KaSRCTR_dw_DatSensorRes_TS2[148]=
{
	147,
	35520,//-40
	33640,
	31870,
	30210,
	28650,
	27180,
	25790,
	24480,
	23250,
	22090,
	20990,//-30
	19960,
	18980,
	18060,
	17190,
	16360,
	15580,
	14840,
	14150,
	13490,
	12860,//-20
	12270,
	11710,
	11180,
	10670,
	10200,
	9743,
	9312,
	8903,
	8514,
	8144,//-10
	7792,
	7458,
	7139,
	6836,
	6548,
	6273,
	6012,
	5763,
	5525,//-1
	5299,//0
	5086,
	4884,
	4690,
	4504,
	4327,
	4157,
	3995,
	3839,
	3690,
	3548,//10
	3411,
	3281,
	3155,
	3035,
	2920,
	2810,
	2704,
	2603,
	2506,
	2413,//20
	2323,
	2237,
	2155,
	2076,
	2000,
	1927,
	1857,
	1790,
	1725,
	1663,//30
	1604,
	1547,
	1492,
	1439,
	1388,
	1339,
	1392,
	1247,
	1203,
	1161,//40
	1121,
	1082,
	1045,
	1009,
	974,
	941,
	909,
	878,
	848,
	820,//50
	793,
	767,
	742,
	718,
	694,
	672,
	651,
	630,
	610,
	590,//60
	572,
	554,
	537,
	520,
	504,
	488,
	473,
	459,
	445,
	431,//70
	418,
	406,
	394,
	382,
	371,
	360,
	349,
	339,
	329,
	319,//80
	310,
	301,
	293,
	284,
	276,
	268,
	261,
	254,
	247,
	240,//90
	233,
	227,
	221,
	215,
	209,
	203,
	198,
	192,
	187,
	182,//100
	177,
	173,
	168,
	164,
	160,
	156,//106
	
};
/*TS1*/
const uint32 KaSRCTR_dw_DatSensorRes_TS1[148]=
{
	147,
	189400,//-40
	179300,
	169900,
	160900,
	152500,
	144600,
	137200,
	130100,
	123500,
	117300,
	111400,//-30
	105800,
	100600,
	95630,
	90950,
	86520,
	82340,
	78380,
	74640,
	71090,
	67740,//-20
	64540,
	61510,
	58630,
	55910,
	53340,
	50890,
	48580,
	46380,
	44290,
	42310,//-10
	40430,
	38650,
	36950,
	35340,
	33810,
	32350,
	30960,
	29640,
	28390,//-1
	27190,//0
	26050,
	24960,
	23930,
	22940,
	22000,
	21100,
	20250,
	19430,
	18650,
	17910,//10
	17200,
	16520,
	15880,
	15260,
	14670,
	14100,
	13560,
	13050,
	12550,
	12080,//20
	11630,
	11190,
	10780,
	10380,
	10000,
	9635,
	9285,
	8950,
	8629,
	8320,//30
	8024,
	7741,
	7468,
	7207,
	6956,
	6715,
	6483,
	6261,
	6047,
	5842,//40
	5644,
	5454,
	5272,
	5096,
	4927,
	4765,
	4608,
	4458,
	4313,
	4173,//50
	4039,
	3910,
	3785,
	3666,
	3550,
	3439,
	3332,
	3228,
	3128,
	3032,//60
	2939,
	2850,
	2763,
	2680,
	2599,
	2522,
	2446,
	2374,
	2304,
	2236,//70
	2171,
	2108,
	2047,
	1988,
	1931,
	1875,
	1822,
	1770,
	1720,
	1672,//80
	1625,
	1579,
	1535,
	1493,
	1451,
	1411,
	1373,
	1335,
	1299,
	1263,//90
	1229,
	1196,
	1164,
	1133,
	1103,
	1073,
	1045,
	1018,
	991,
	965,//100
	940,
	915,
	892,
	869,
	847,
	825,
	
};
/*PCB TEMP*/
const uint32 KaSRCTR_dw_DatSensorRes_PCB_TEMP[207]=
{
	206,
	470122,//-55
	442600,
	416797,
	392600,
	369907,
	348618,//-50
	328643,
	309896,
	292299,
	275777,
	260262,
	245688,
	231997,
	219130,
	207037,
	195652,//-40
	184917,
	174845,
	165391,
	156512,
	148171,
	140330,
	132957,
	126021,
	119493,
	113347,//-30
	107564,
	102115,
	96977,
	92131,
	87558,
	83242,
	79166,
	75315,
	71676,
	68236,//-20
	64990,
	61919,
	59011,
	56257,
	53649,
	51177,
	48834,
	46613,
	44505,
	42506,//-10
	40599,
	38790,
	37072,
	35441,
	33892,
	32419,
	31020,
	29689,
	28423,
	27218,//0
	26076,
	24987,
	23950,
	22962,
	22021,
	21123,
	20266,
	19449,
	18669,
	17925,//10
	17213,
	16534,
	15885,
	15265,
	14673,
	14107,
	13566,
	13048,
	12554,
	12080,//20
	11628,
	11194,
	10779,
	10381,
	10000,
	9634,
	9283,
	8947,
	8624,
	8314,//30
	8018,
	7733,
	7460,
	7199,
	6947,
	6706,
	6475,
	6252,
	6039,
	5833,//40
	5635,
	5445,
	5262,
	5086,
	4916,
	4753,
	4597,
	4446,
	4300,
	4160,//50
	4026,
	3896,
	3771,
	3651,
	3535,
	3423,
	3315,
	3211,
	3111,
	3014,//60
	2922,
	2833,
	2748,
	2665,
	2586,
	2509,
	2435,
	2363,
	2294,
	2227,//70
	2162,
	2100,
	2039,
	1981,
	1924,
	1869,
	1817,
	1765,
	1716,
	1668,//80
	1622,
	1577,
	1534,
	1492,
	1452,
	1412,
	1374,
	1338,
	1302,
	1268,//90
	1234,
	1201,
	1170,
	1139,
	1109,
	1080,
	1052,
	1025,
	999,
	973,//100
	949,
	925,
	902,
	879,
	858,
	836,
	816,
	796,
	776,
	758,//110
	739,
	721,
	704,
	687,
	671,
	655,
	640,
	625,
	610,
	596,//120
	582,
	569,
	556,
	543,
	531,
	519,
	507,
	496,
	485,
	474,//130
	463,
	453,
	443,
	433,
	424,
	415,
	406,
	397,
	388,
	380,//140
	372,
	364,
	357,
	349,
	342,
	335,
	328,
	321,
	315,
	308,//150

};
/*const*/ SrCtrAdTableCfg_Struct stSrCtrAdTableCfg[SRADCTR_TABLE_CH_MAX_NUM] = /*PRQA S 3211*/
	{
#if (SRCFG_TEMP_TS1_NTC_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT1_AD_CH,
		 SRCTRCFG_TEMP_DAT1_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT1_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT1_PULL_STA,
		 SRCTRCFG_TEMP_DAT1_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT1_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT1_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT1_DTC_BITMASK,
		 SRDIAG_TEMP_DAT1_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT1_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT1_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT1_MAX_TEMPERATURE},
#endif
#if (SRCFG_TEMP_TS2_NTC_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT2_AD_CH,
		 SRCTRCFG_TEMP_DAT2_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT2_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT2_PULL_STA,
		 SRCTRCFG_TEMP_DAT2_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT2_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT2_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT2_DTC_BITMASK,
		 SRDIAG_TEMP_DAT2_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT2_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT2_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT2_MAX_TEMPERATURE},
#endif
#if (SRCFG_TEMP_PCB_NTC_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT3_AD_CH,
		 SRCTRCFG_TEMP_DAT3_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT3_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT3_PULL_STA,
		 SRCTRCFG_TEMP_DAT3_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT3_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT3_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT3_DTC_BITMASK,
		 SRDIAG_TEMP_DAT3_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT3_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT3_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT3_MAX_TEMPERATURE},
#endif
#if (SRCFG_TEMP_TFT_NTC_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT1_AD_CH,
		 SRCTRCFG_TEMP_DAT1_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT1_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT1_PULL_STA,
		 SRCTRCFG_TEMP_DAT1_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT1_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT1_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT1_DTC_BITMASK,
		 SRDIAG_TEMP_DAT1_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT1_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT1_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT1_MAX_TEMPERATURE},
#endif

#if (SRCFG_TEMP_DAT2_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT2_AD_CH,
		 SRCTRCFG_TEMP_DAT2_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT2_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT2_PULL_STA,
		 SRCTRCFG_TEMP_DAT2_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT2_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT2_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT2_DTC_BITMASK,
		 SRDIAG_TEMP_DAT2_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT2_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT2_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT2_MAX_TEMPERATURE},
#endif

#if (SRCFG_TEMP_DAT3_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT3_AD_CH,
		 SRCTRCFG_TEMP_DAT3_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT3_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT3_PULL_STA,
		 SRCTRCFG_TEMP_DAT3_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT3_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT3_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT3_DTC_BITMASK,
		 SRDIAG_TEMP_DAT3_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT3_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT3_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT3_MAX_TEMPERATURE},
#endif

#if (SRCFG_TEMP_DAT4_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT4_AD_CH,
		 SRCTRCFG_TEMP_DAT4_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT4_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT4_PULL_STA,
		 SRCTRCFG_TEMP_DAT4_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT4_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT4_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT4_DTC_BITMASK,
		 SRDIAG_TEMP_DAT4_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT4_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT4_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT4_MAX_TEMPERATURE},
#endif

#if (SRCFG_TEMP_DAT5_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT5_AD_CH,
		 SRCTRCFG_TEMP_DAT5_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT5_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT5_PULL_STA,
		 SRCTRCFG_TEMP_DAT5_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT5_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT5_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT5_DTC_BITMASK,
		 SRDIAG_TEMP_DAT5_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT5_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT5_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT5_MAX_TEMPERATURE},
#endif

#if (SRCFG_TEMP_DAT6_ENABLE == SRCFG_ENABLE)
		{SRCTRCFG_TEMP_DAT6_AD_CH,
		 SRCTRCFG_TEMP_DAT6_AD_PRECISION,
		 SRCTRCFG_TEMP_DAT6_TABLE_TYPE,
		 SRCTRCFG_TEMP_DAT6_PULL_STA,
		 SRCTRCFG_TEMP_DAT6_PULL_UP_RES,
		 SRCTRCFG_TEMP_DAT6_RT_ADDRESS,
		 SRCTRCFG_TEMP_DAT6_RT2_ADDRESS,
		 SRDIAG_TEMP_DAT6_DTC_BITMASK,
		 SRDIAG_TEMP_DAT6_OPEN_THRESHOLD,
		 SRDIAG_TEMP_DAT6_SHORT_THRESHOLD,
		 SRDIAG_TEMP_DAT6_MIN_TEMPERATURE,
		 SRDIAG_TEMP_DAT6_MAX_TEMPERATURE},
#endif

};

#if (SRCFG_ENABLE == SRCTRCFG_AD_LINE_CLASS)/*unused*/
const SrCtrAdLineCfg_Struct stSrCtrAdLineCfg[SRADCTR_LINE_CH_MAX_NUM ] =
{
#if (SRCFG_SOLAR_L_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
    {
        SRCTRCFG_SOLAR_L_INDENSITY_AD_CH,
        SRCTRCFG_SOLAR_L_INDENSITY_AD_PRECISION,
        SRCTRCFG_SOLAR_L_INDENSITY_PULL_STA,
        SRCTRCFG_SOLAR_L_INDENSITY_PULL_UP_RES,
        SRCTRCFG_SOLAR_L_INDENSITY_AD_LOW,
        SRCTRCFG_SOLAR_L_INDENSITY_AD_HIGH,
        SRCTRCFG_SOLAR_L_INDENSITY_MAX,
        SRDIAG_SOLAR_L_INDENSITY_DTC_BITMASK,
        SRDIAG_SOLAR_L_INDENSITY_OPEN_THRESHOLD,
        SRDIAG_SOLAR_L_INDENSITY_SHORT_THRESHOLD
    },
#endif
#if (SRCFG_SOLAR_R_INDENSITY_SH_ENABLE == SRCFG_ENABLE)
    {
        SRCTRCFG_SOLAR_R_INDENSITY_AD_CH,
        SRCTRCFG_SOLAR_R_INDENSITY_AD_PRECISION,
        SRCTRCFG_SOLAR_R_INDENSITY_PULL_STA,
        SRCTRCFG_SOLAR_R_INDENSITY_PULL_UP_RES,
        SRCTRCFG_SOLAR_R_INDENSITY_AD_LOW,
        SRCTRCFG_SOLAR_R_INDENSITY_AD_HIGH,
        SRCTRCFG_SOLAR_R_INDENSITY_MAX,
        SRDIAG_SOLAR_R_INDENSITY_DTC_BITMASK,
        SRDIAG_SOLAR_R_INDENSITY_OPEN_THRESHOLD,
        SRDIAG_SOLAR_R_INDENSITY_SHORT_THRESHOLD
    },
#endif
#if (SRCFG_HUMIDITY_ENABLE == SRCFG_ENABLE)
    {
        SRCTRCFG_HUMIDITY_AD_CH,
        SRCTRCFG_HUMIDITY_AD_PRECISION,
        SRCTRCFG_HUMIDITY_PULL_STA,
        SRCTRCFG_HUMIDITY_PULL_UP_RES,
        SRCTRCFG_HUMIDITY_VOLT_LOW,
        SRCTRCFG_HUMIDITY_VOLT_HIGH,
        SRCTRCFG_HUMIDITY_MAX,
        SRDIAG_HUMIDITY_DTC_BITMASK,
        SRDIAG_HUMIDITY_OPEN_THRESHOLD,
        SRDIAG_HUMIDITY_SHORT_THRESHOLD
    },
#endif

#if (SRCFG_TWILIGHT_ENABLE == SRCFG_ENABLE)
    {
        SRCTRCFG_TWILIGHT_AD_CH,
        SRCTRCFG_TWILIGHT_AD_PRECISION,
        SRCTRCFG_TWILIGHT_PULL_STA,
        SRCTRCFG_TWILIGHT_PULL_UP_RES,
        SRCTRCFG_TWILIGHT_AD_LOW,
        SRCTRCFG_TWILIGHT_AD_HIGH,
        SRCTRCFG_TWILIGHT_MAX,
        SRDIAG_TWILIGHT_DTC_BITMASK,
        SRDIAG_TWILIGHT_OPEN_THRESHOLD,
        SRDIAG_TWILIGHT_SHORT_THRESHOLD
    }
#endif

};
#endif
#endif


/*EOF*/
