#ifndef _AMB_CFG_H_
#define _AMB_CFG_H_

#define MOTOR_RPM_SCALE (float)(60.f*16000.f/(PI_2)/MOTOR_NP)
#define MOTOR_OMEGA2RPM(x) (float)((float)(x)*MOTOR_RPM_SCALE)
/* TIM1 参数 */
#define TIM1_CLK_FREQ           (120000000.0)        /* Hz */ /* float ¹̶¨ֵ */
#define TIM1_CLK_SEC           (0.000000000833) /* s */  /* Copy */
#define EPWM_FREQ               (16000.0)           /* Hz */ /* float [+0.1, +TIM1_CLK_FREQ] */
#define EPWM_PERIOD_SEC        (0.0000625)  /* s */  /* Copy */
#define EPWM_DEADTIME_SEC       (0.000001)          /* s */  /* float [+0.0, +0.00001] */
#define EPWM_PERIOD            (3750) /* Ticks */ /* Copy */

/* SVPWM */
#define PWM_WINDOW_SEC          (0.000000)         /* s */  /* float [+0.0, +0.00001] */
#define EPWM_WINDOW             (int32_t)(PWM_WINDOW_SEC/TIM1_CLK_SEC)     /* Ticks */ /* Copy */

/* ADC */
#define ADC_VREF                (5.0)              /* V ADC参考电县*/     /* float 固定倿*/
#define ADC_BITS                (int32_t)(12)      /* bits ADC有效位数 */  /* int32_t 固定倿*/

/* 板卡硬件 母线采样 功率桿*/
#define PEAK_VOLATGE           (55.0) /* V ADC可测量的最大母线电县*/  /* Copy */
#define PEAK_CURRENT           (25.0)      /* A ADC可测量的最大母线电浿*/  /* Copy */
#define MOS_RS                 (0.0)   /* ohm MOSFET内阻  */            /* float [+0.0001, +100.0] */

// /*  DW-NEO-OK */
// #define MOTOR_NP               (2.0)
// #define MOTOR_RS               (0.625f/2.f)//(1.2f/2.f)
// #define MOTOR_LD               (0.00265f/2.f)//(0.0449f/2.f)
// #define MOTOR_LQ               (0.00362f/2.f)//(0.0593f/2.f)
// #define MOTOR_LS               ((MOTOR_LD+MOTOR_LQ)/2.f)
// #define MOTOR_KFI              (0.005237f)//(0.01254f)
// #define BOOT_STALL_CURRENT_TH (int16_t)((float)BOOT_MAX_CURRENT*1.5f) /* 启动堵转检测电流阈值 */
// #define BOOT_MAX_CURRENT 4000   /* 最大启动电流 */
// #define ACCE_MAX_CURRENT 16000   /* 最大工作电流 */
// #define EQ_COFF          299
// #define ED_COFF          299
// #define FW_ID            -7000  /* pu */

// /* DW-NEO-OK D轴PI参数 */
// #define D_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
// #define D_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
// #define D_CURRENT_KI_FINE      (int32_t)(1000)     /* int32_t [+0, +32767] */
// #define D_CURRENT_OUTMAX       (int32_t)(31500)    /* int32_t [-32768, +32767] */
// #define D_CURRENT_OUTMIN       (int32_t)(-31500)   /* int32_t [-32768, +32767] */

// /* DW-NEO-OK Q轴PI参数 */
// #define Q_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
// #define Q_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
// #define Q_CURRENT_KI_FINE      (int32_t)(10)     /* int32_t [+0, +32767] */
// #define Q_CURRENT_OUTMAX       (int32_t)(30500)    /* int32_t [-32768, +32767] */
// #define Q_CURRENT_OUTMIN       (int32_t)(-30500)   /* int32_t [-32768, +32767] */

///*  LG-BCA015-OK */
//#define MOTOR_NP               (2.0)
//#define MOTOR_RS               (0.21f/2.f)
//#define MOTOR_LD               (0.00033f/2.f)
//#define MOTOR_LQ               (0.00046f/2.f)
//#define MOTOR_LS               ((MOTOR_LD+MOTOR_LQ)/2.f)
//#define MOTOR_KFI              (0.005099f)
//#define BOOT_STALL_CURRENT_TH (int16_t)((float)BOOT_MAX_CURRENT*1.5f) /* 启动堵转检测电流阈值 */
//#define BOOT_MAX_CURRENT 4000   /* 最大启动电流 */
//#define ACCE_MAX_CURRENT 17000  /* 最大工作电流 */
//#define EQ_COFF          299
//#define ED_COFF          6
//#define FW_ID            -7000  /* pu */

///* LG-BCA015 D轴PI参数 */
//#define D_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
//#define D_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
//#define D_CURRENT_KI_FINE      (int32_t)(1000)     /* int32_t [+0, +32767] */
//#define D_CURRENT_OUTMAX       (int32_t)(31500)    /* int32_t [-32768, +32767] */
//#define D_CURRENT_OUTMIN       (int32_t)(-31500)   /* int32_t [-32768, +32767] */

///* LG-BCA015 Q轴PI参数 */
//#define Q_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
//#define Q_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
//#define Q_CURRENT_KI_FINE      (int32_t)(10)     /* int32_t [+0, +32767] */
//#define Q_CURRENT_OUTMAX       (int32_t)(30500)    /* int32_t [-32768, +32767] */
//#define Q_CURRENT_OUTMIN       (int32_t)(-30500)   /* int32_t [-32768, +32767] */

/*  LG-BCK015 */
#define MOTOR_NP               (3.0)
#define MOTOR_RS               (0.21f/2.f)
#define MOTOR_LD               (0.000270/2.f)//(0.0002/2.f)//(0.000155/2.f)
#define MOTOR_LQ               (0.000340/2.f)//(0.0002/2.f)//(0.000210/2.f) 
#define MOTOR_LS               ((MOTOR_LD+MOTOR_LQ)/2.f) 
#define MOTOR_KFI              (0.005099f)//(0.004814f)
#define BOOT_MAX_CURRENT 4000   /* 最大启动电流 */
#define ACCE_MAX_CURRENT 17000  /* 最大工作电流 */
#define EQ_COFF          299
#define ED_COFF          99
#define FW_ID            -7000  /* pu */

/* LG-BCK015 D轴PI参数 */
#define D_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
#define D_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
#define D_CURRENT_KI_FINE      (int32_t)(1000)     /* int32_t [+0, +32767] */
#define D_CURRENT_OUTMAX       (int32_t)(31500)    /* int32_t [-32768, +32767] */
#define D_CURRENT_OUTMIN       (int32_t)(-31500)   /* int32_t [-32768, +32767] */

/* LG-BCK015 /BCA015 Q轴PI参数 */
#define Q_CURRENT_KP           (int32_t)(32000)//25000        /* int32_t [+0, +32767] */
#define Q_CURRENT_KI           (int32_t)(1000)//500        /* int32_t [+0, +32767] */
#define Q_CURRENT_KI_FINE      (int32_t)(1000)     /* int32_t [+0, +32767] */
#define Q_CURRENT_OUTMAX       (int32_t)(30500)    /* int32_t [-32768, +32767] */
#define Q_CURRENT_OUTMIN       (int32_t)(-30500)   /* int32_t [-32768, +32767] */

///*  GMCC-ME17ME14M1P-B */
//#define MOTOR_NP               (3.0)
//#define MOTOR_RS               (0.139f/2.f)
//#define MOTOR_LD               (0.00012/3.f)//
//#define MOTOR_LQ               (0.00023/3.f)//
//#define MOTOR_LS               ((MOTOR_LD+MOTOR_LQ)/2.f) 
//#define MOTOR_KFI              (0.00475f)//@1.9Vrms//
//#define BOOT_STALL_CURRENT_TH (int16_t)((float)BOOT_MAX_CURRENT*1.15f) /* 启动堵转检测电流阈值 */
//#define BOOT_MAX_CURRENT 4000   /* 最大启动电流 */
//#define ACCE_MAX_CURRENT 17000  /* 最大工作电流 */
//#define EQ_COFF          999
//#define ED_COFF          99
//#define FW_ID            -3000  /* pu */

///* GMCC-ME17ME14M1P-B  D轴PI参数 */
//#define D_CURRENT_KP           (int32_t)(32000)    /* int32_t [+0, +32767] */
//#define D_CURRENT_KI           (int32_t)(1000)     /* int32_t [+0, +32767] */
//#define D_CURRENT_KI_FINE      (int32_t)(1000)     /* int32_t [+0, +32767] */
//#define D_CURRENT_OUTMAX       (int32_t)(31500)    /* int32_t [-32768, +32767] */
//#define D_CURRENT_OUTMIN       (int32_t)(-31500)   /* int32_t [-32768, +32767] */

///* GMCC-ME17ME14M1P-B  Q轴PI参数 */
//#define Q_CURRENT_KP           (int32_t)(32000)    /* int32_t [+0, +32767] */
//#define Q_CURRENT_KI           (int32_t)(1000)     /* int32_t [+0, +32767] */
//#define Q_CURRENT_KI_FINE      (int32_t)(10)       /* int32_t [+0, +32767] */
//#define Q_CURRENT_OUTMAX       (int32_t)(30500)    /* int32_t [-32768, +32767] */
//#define Q_CURRENT_OUTMIN       (int32_t)(-30500)   /* int32_t [-32768, +32767] */


///* WG */
//#define MOTOR_NP               (3.0)   /* 极对敿*/               /* float(保证是正敿 [+1.0, +100.0] */
//#define MOTOR_RS               (0.7f/2.f)         /* ohm 相电阿 */          /* float [+0.0001, +10000.0] */
//#define MOTOR_LD               (0.00045/2.f)   /* H 相电愿*/             /* float [+0.00000001, +10.0] */
//#define MOTOR_LQ               (0.00070/2.f)   /* H 相电愿*/             /* float [+0.00000001, +10.0] */
//#define MOTOR_LS               (0.00070/2.f)//((MOTOR_LD+MOTOR_LQ)/2.f)   /* H 相电愿*/  /* float 被动计算倿*/
//#define MOTOR_KFI              (0.00673f)         /* Vs/rad 反电势系敿 0.175v/rpm*/   /* float [+0.0001, +1000.0] */

///*  DE14M1P-B */
//#define MOTOR_NP               (3.0)   /* ¼«¶Ԕ¼*/               /* float(±£֤ʇս¼ [+1.0, +100.0] */
//#define MOTOR_RS               (0.139f/2.f)         /* ohm Ϡµ簢 */          /* float [+0.0001, +10000.0] */
//#define MOTOR_LD               (0.000063)   /* H Ϡµ甸*/             /* float [+0.00000001, +10.0] */
//#define MOTOR_LQ               (0.000117)   /* H Ϡµ甸*/             /* float [+0.00000001, +10.0] */
//#define MOTOR_LS               (0.000117)//((MOTOR_LD+MOTOR_LQ)/2.f)   /* H Ϡµ甸*/  /* float ±»¶¯¼Ƌゞ*/
//#define MOTOR_KFI              (0.004961f/1.414)         /* Vs/rad ·´µ犆ϵ¼ 0.175v/rpm*/   /* float [+0.0001, +1000.0] */


/* 位置观测器参敿*/
#define ESTIM_LOOPTIME_N        (1.0)          /* float(保证是正敿 [+1.0, +100.0] */
#define ESTIM_LOOPTIME_SEC     (0.00006250000)  /* s 电流控制环时闿*/  /* Copy */
#define PI_2                   (6.2832)  /* 2倍PI() */         /* Copy */
//#define SQRT3                  (1.73205)  /* sqrt(3) */         /* Copy */
#define KFILTER_ESDQ            (0.244)  /* 滤波系数 q15 */ /* int32_t [+1, +32767] */



#endif /* _AMB_CFG_H_ */
