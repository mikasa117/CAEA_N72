#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "sdk_project_config.h"

// #define OPEN_LOOP              /* 使能开环启动模式 */

struct state_params {
    int32_t  bemf_acc;    /* 反电势电压幅值积分 */
    int32_t  phase;       /* 当前相位 */
    int32_t  period_60d;  /* 60度相位周期 */
    int32_t  period_30d;  /* 30度相位周期 */
    int32_t  cross_time;  /* 最近过0时间点 */
    int32_t  pbus_current_offset;  /* 母线电流偏置 */
    int32_t  phase_current_offset; /* 相电流偏置 */
    int32_t  phase_current_offset1; /* 相电流偏置 */
    int32_t  pbus_current;/* 母线电流 */
    int32_t  pbus_voltage;/* 母线电压 */
    int32_t  pbus_power;  /* 母线功率 */
    int32_t  pbus_temp;   /* 温度 */
    uint32_t current_state; /* 记录的上次系统状态 */
    uint32_t state;       /* 系统状态 */
    uint32_t error;       /* 错误状态 */
    int16_t  theta;       /* d轴theta角 */
    int16_t  sin;         /* sin(theta) */
    int16_t  cos;         /* cos(theta) */
    int16_t  theta_diff;  /* d轴theta角变化 */
    int16_t  theta_off;   /* 观测器输出角度和当前角度差 */
    int32_t  vd;          /* d轴电压 */
    int32_t  vq;          /* q轴电压 */
    int32_t  valpha;      /* alpha轴电压 */
    int32_t  vbeta;       /* beta轴电压 */
    int16_t  pwma[2];     /* A相PWM */
    int16_t  pwmb[2];     /* B相PWM */
    int16_t  pwmc[2];     /* C相PWM */
    int32_t  c1;          /* 单电阻一次采样 */
    int32_t  c2;          /* 单电阻二次采样 */
    uint8_t  sector;      /* 扇区 */
    int32_t  ia;          /* 重建A相电流 */
    int32_t  ib;          /* 重建B相电流 */
    int32_t  ic;          /* 重建C相电流 */
    int32_t  sample_offset1;
    int32_t  sample_offset2;
    int32_t  ialpha;
    int32_t  ibeta;
    int32_t  id;
    int32_t  iq;
    int32_t  i_lockstep;      /* 锁定阶段电流每PWM周期的增量,=gp.iq_lock/gp.lock_time */
    int32_t  i_accstep;      /* 烁露篓陆锥蔚鐏访縋WM譁茪碌臄枚脕驴,=gp.iq_lock/gp.lock_time */
    int32_t  w_step;      /* 加速阶段速度每PWM周期的增量,=gp.speed/gp.acc_time */
    int32_t  est_sin;
    int32_t  est_cos;
    uint32_t norm_sqr;
    uint32_t norm_sqrt;
    int32_t  v1;          /* SVPWM u1电压 */
    int32_t  v2;          /* SVPWM u2电压 */
    int32_t  v3;          /* SVPWM u3电压 */
    int32_t  speed;
    int32_t  ibus;
		int32_t  speed_hpf;

    int32_t  abvoltage_thresh;    /*  */
    int32_t  min_boot_voltage;       /*  */
    int32_t  max_boot_voltage;
    int32_t  rcvoltage_thresh;        /*  */
    int32_t  abtemper_thresh;        /*  */
    int32_t  abcurrent_thresh;        /*  */
    
    int32_t  abphase_current_a_over_thresh;        /*  */
    int32_t  abphase_current_b_over_thresh;        /*  */   
    int32_t  abphase_current_c_over_thresh;        /*  */

    int32_t  abphase_current_a_lack_thresh;        /*  */
    int32_t  abphase_current_b_lack_thresh;        /*  */   
    int32_t  abphase_current_c_lack_thresh;        /*  */

    int32_t  stall_thresh_count;        /*  */
    
    int32_t  abspeed_thresh;        /*  */
    int32_t  no_cross_retry;        /*  */
    int32_t  no_cross_count;

    int32_t  speed_max_200ms_current;
    int32_t  speed_min_200ms_current;
    int32_t  speed_offset_200ms_thresh;

};

extern struct state_params gs;

struct config_params {
    int32_t direct;            /* 调试用过零方向 */
    int32_t pbus_pid_interval; /* 母线电流PID控制间隔 */
    int32_t pbus_power;        /* 母线目标功率 */
    int32_t mode;              /* 模式 0:PWM模式 1:功率环模式 */
    int32_t min_boot_voltage;  /* 启动最小电压 */
    int32_t max_boot_voltage;  /* 启动最大电压 */
    int32_t min_run_voltage;   /* 运行最小电压 */
    int32_t max_run_voltage;   /* 运行最大电压 */
    int32_t voltage_error_thresh; /* 过压欠压阈值 */
    int32_t voltage_delay_thresh; /* 欠压恢复阈值 */
    int32_t boot_temp;         /* 启动温度极值 */
    int32_t work_temp;         /* 工作温度极值 */
    int32_t temp_error_thresh; /* 过温时间阈值 */
    int32_t max_current;       /* 母线最大电流 */
    int32_t current_error_thresh; /* 母线超最大电流阈值 */

    int32_t phase_max_current; /* 相电流过流电流 */                     
    int32_t phase_current_over_thresh; /* 相电流过流阈值时间 */

    int32_t phase_min_current; /* 相电流缺相阈值电流 */                           
    int32_t phase_current_short_thresh; /* 相电流缺相阈值时间 */
    int32_t stall_error_current;
    int32_t stall_error_speed;
    int32_t stall_error_thresh;
    int32_t no_cross_thresh;   /* 过零超时错误阈值 */
    int32_t offset;                                      
    int32_t iq;                /* 当前Iq */
    int32_t id;                /* 目标Id */
    int32_t iq_lock;           /* 锁定目标Iq */
    int32_t iq_boot_stall;     /* 直接闭环启动的Iq堵转电流阈值 */
    int32_t iq_soft_stop_ramp; /* 缓停Iq电流递减值 */
    int32_t lock_iq_time;     /* 起步电流加速时间 单位:PWM周期次数 */
    int32_t acc_iq_time;          /* 录計賷卤录錉德ノ?PWM譁茪麓螉媒 */
    int32_t lock_time;				 /* 起步锁定时间 单位:PWM周期次数 */
    int32_t acc_time;          /* 加速时间 单位:PWM周期次数 */
    int32_t boot_speed;        /* 加速的目标速度,theta角每PWM周期的增量 */
    int32_t speed;             /* 加速的目标速度,theta角每PWM周期的增量 */
    int32_t close_loop;
    int32_t weaken_scale;
    int32_t rpm;
    int16_t g_pwma1;
    int16_t g_pwmb1;
    int16_t g_pwmc1;
    int16_t g_pwma2;
    int16_t g_pwmb2;
    int16_t g_pwmc2;


    int32_t  boot_max_temp;        /*  */
    int32_t  boot_min_temp;        /*  */
    int32_t  work_max_temp;        /*  */
    int32_t  work_min_temp;        /*  */
    int32_t  min_period_60d;        /*  */
    int32_t  max_period_60d;        /*  */
    int32_t  speed_over_thresh;        /*  */
    int32_t  fw_en;
    int32_t  fw_id;
    int32_t  rx_lowest;        /*  */
		int32_t  vcomp;
		int32_t  rpm_ramp_cnt;
		int32_t  thecomp;
};

extern struct config_params gp;

uint8_t dcBus_init(void);    

// 定义放进RAM
//#define FIXED_RAM __attribute__((section(".FIXED_RAM")))
//FIXED_RAM void foc_ctrl(uint16_t ibus, uint16_t a, uint16_t b, uint16_t v, uint16_t c, uint16_t t, uint16_t eTMR_NUM1, uint16_t eTMR_NUM2, uint16_t eTMR_NUM3); 
void foc_ctrl(uint16_t ibus, uint16_t a, uint16_t b, uint16_t v, uint16_t c, uint16_t t, uint16_t eTMR_NUM1, uint16_t eTMR_NUM2, uint16_t eTMR_NUM3); 

void motor_param_init(void);
void motor_info_init(float rs, float ls, float kfi, float np);

/**
 * 输入 的 电压电流的阈值 量程 参考
 #define PEAK_VOLATGE               (27.7)   V ADC可测量的最大母线电压
 #define PEAK_CURRENT               (16.67)  A ADC可测量的最大母线电流
*/
// 电压阈值设置
void voltageProtectThresholdSet(float boVol_min, float boVol_max, uint16_t boVol_cnt, float runVol_min, float runVol_max, uint16_t runVol_cnt);
// 电压保护开关设置
void voltageProtectSet(bool isOpen);
// 功率保护开关  p.s. 当电压保护为开时，功率保护开关才有作用;当电压保护为关时，功率保护恒关 
void voltagePowerProtectSet(bool isOpen); 
// 电流阈值设置
void currentProtectThresholdSet(float cur_max, uint16_t curOver_cnt, float cur_min, uint16_t curShort_cnt);
// 电流保护开关设置
void currentProtectSet(bool isOpen);
// 转速阈值设置
void speedProtectThresholdSet(uint16_t speed_min, uint16_t speed_max, uint16_t speed_cnt);
// 转速保护开关设置
void speedProtectSet(bool isOpen);
// 堵转阈值设置
void stallProtectThresholdSet(uint16_t speedErr_min, float curErr_max, uint16_t stallErr_cnt);
// 堵转保护开关设置
void stallProtectSet(bool isOpen);

// 弱磁阈值设置   cur_fieldWeak 为负值
void fieldWeakThresholdSet(float cur_fieldWeak);
// 弱磁开关设置
void fieldWeakSet(bool isOpen);

// 最大启动电流
void bootMaxCurrentSet(uint16_t current); 
                                   
// 最大运行电流
void acceMaxCurrentSet(uint16_t current);


// 启动-同时清空错误信息
void motor_start(void);       
// 停止
void motor_stop(void);
// 
void motor_speed(int32_t speed);
void motor_loop(void);

// 外部调用的保护
void slowProtect(void);
void slowProtect200ms(void);

// 外部通知故障信息  USER_REQUEST_STANDBY  0x40000000
void sendProtectInfo(uint32_t info);

// 获取错误信息
uint32_t getErrorInfo();
// 清空错误信息不启动
void clearErrorInfo();

// 获取当前转速反馈
int32_t getSpeedInfo();
// 修改转速PI参数
void setSpeedPi_kp(uint32_t kp);


#endif /* _MOTOR_H_ */
