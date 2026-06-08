
#include <stdint.h>
#include "motor.h"
#include "lpf.h"
#include "pi.h"
#include "mclib.h"
#include "amb_cfg.h"

int32_t g_boot_rpm = 3000;       /* ???????rpm */
int32_t g_fb_rpm = 0;            /* ??????? */
uint8_t g_rpm_ramp_cnt = 16;     /* ???Ramp */
int32_t g_vcomp = 0;//120000;    /* ?????????? */
int32_t g_id_ki = D_CURRENT_KI;  /* ???????d???????Ki */
int32_t g_iq_ki = Q_CURRENT_KI;  /* ???????q???????Ki */
int32_t g_id_ki_fine = D_CURRENT_KI_FINE;  /* ???????d???????Ki */
int32_t g_iq_ki_fine = Q_CURRENT_KI_FINE;  /* ???????q???????Ki */
int32_t g_rpm_kp_fine = 140000*4;        /* ???????????Kp LG*4; MZ*8 */
int32_t g_fw_id = FW_ID;                   /* ??????? */

uint8_t g_nvhstop = 0;           /* NVH?????? */
uint32_t g_userstate = 0;        /* ????????? */

int32_t g_boot_max_current = BOOT_MAX_CURRENT;    /* ??????????? */   
int32_t g_acce_max_current = ACCE_MAX_CURRENT;    /* ????????? */

extern t_PIFFParm speed_pi;
extern uint16_t TargetSpeed;
extern t_PIFFParm id_pi;
extern t_PIFFParm iq_pi;
extern t_PIFFParm speed_pi;

/* FOC Task */

/* Call in WORK mode */
void motor_foc_work(uint32_t *state)
{
	static uint32_t cnt = 0;
	static uint8_t stopflag = 0;

	g_fb_rpm = getSpeedInfo();

/* stop at low speed mode for GMCC */
	if(g_nvhstop == 1){
		TargetSpeed = 2700;//2300;
		if(++cnt > 640000 || g_fb_rpm < (TargetSpeed+50)){
			cnt = 0;
			TargetSpeed = g_boot_rpm;
			gs.error = 0x40000000;
			g_nvhstop = 0;
		}
	}

/* stop at low speed mode for LG */
//	if(g_nvhstop == 1){
//		TargetSpeed = 2000;
//		if(++cnt > 64000 || g_fb_rpm < (TargetSpeed+200)){
//			cnt = 0;
//			TargetSpeed = 3000;
//			gs.error = 0x40000000;
//			g_nvhstop = 0;
//		}
//	}
}

/* Call in SOFTSTOP mode for HVH */
void motor_foc_softstop(uint32_t *state)
{

}

/* 1ms Task */
void motor_loop_work(uint32_t *state)
{
	static uint8_t s_cnt = 0;
	if( ++s_cnt >= 2 ){
		s_cnt = 0;
		if (gs.speed > 1800){
			if(id_pi.q15_ki > g_id_ki_fine){
				id_pi.q15_ki--;
			}else if(id_pi.q15_ki < g_id_ki_fine){
				id_pi.q15_ki++;
			}
			if(iq_pi.q15_ki > g_iq_ki_fine){
				iq_pi.q15_ki--;
			}else if(iq_pi.q15_ki < g_iq_ki_fine){
				iq_pi.q15_ki++;
			}
			if(speed_pi.q15_kp > g_rpm_kp_fine){
				speed_pi.q15_kp -= 100;
			}else if(speed_pi.q15_kp < g_rpm_kp_fine){
				speed_pi.q15_kp +=100;
			}
			if(gp.vcomp > g_vcomp){
				gp.vcomp -= 10;
			}else if(gp.vcomp < g_vcomp){
				gp.vcomp += 10;
			}
		}
	}
}
			
void motor_loop_softstop(uint32_t *state)
{

}
				
