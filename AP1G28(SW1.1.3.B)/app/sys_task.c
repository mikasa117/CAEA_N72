
#include "sys_task.h"
#include "arm_math.h"
#include "motor.h"

#include "main.h"

#include "amb_cfg.h"
#include "hardware.h"
#include "estimator.h"
#define sys_timertask1ms_cntProc      (sizeof(sys_timertask1ms_callback)/3)
#define sys_timertask10ms_cntProc     (sizeof(sys_timertask10ms_callback)/3)
#define sys_timertask100ms_cntProc    (sizeof(sys_timertask100ms_callback)/3)


extern volatile uint32_t syscoun;

 volatile uint32_t init_count;
/***************************************************************************************************
 * function declaration
 **************************************************************************************************/

/*user task function*/
void task_1ms(void);
void task_10ms(void);
void task_100ms(void);
void task_200ms(void);
void task_1s(void);

/*system task function*/
void sys_timerTask_1ms(void);
void sys_timerTask_10ms(void);
void sys_timerTask_100ms(void);


static void DiagFunVol();
/***************************************************************************************************
 * variable definition
 **************************************************************************************************/
uint16_t system_1ms_TCF;
uint16_t system_10ms_TCF;
uint16_t system_100ms_TCF;

uint16_t sys_cntProc_1ms;
uint16_t sys_cntProc_10ms;
uint16_t sys_cntProc_100ms;

uint16_t task_cnt1ms = 0;
uint16_t task_cnt10ms = 0;
uint16_t task_cnt100ms = 0;
uint16_t task_cnt10min = 0;

uint16_t task_cnt1min = 0;

uint8_t user_request_state = 0; 
uint8_t user_request_current_state = 0;
/*
**************************************************************************************************
 * Scheduling function definition
 **************************************************************************************************
 */

void sys_TaskInit(void)
{
    task_cnt1ms = 0;
    task_cnt10ms = 0;
    task_cnt100ms = 0;
    task_cnt10min = 0;

    system_1ms_TCF = 0;
    system_10ms_TCF = 0;
    system_100ms_TCF = 0;
    pwmStop();
}

volatile uint32_t syscount;
uint32_t _syscoun;
void sys_LoopTask(void)
{
        if ((syscoun != _syscoun) && ((syscoun & 0xF) == 0)) {
            _syscoun = syscoun;
            syscount++;
            task_1ms();
            if(syscount%10 ==0) {
                task_10ms();
            }
            if(syscount%100 ==0) {
                syscount = 0;
                task_100ms();
            }
        }
}


/*task functions */
void task_1ms(void)
{
    float tmpslide;
    float tmpierrmax;
    static uint8_t readyflag = 0;
    static uint16_t readycount = 0;
    static uint8_t wdcount;
    wdcount++;
    if(SysState == 0) {
				motor_stop();
        if( dcBus_init() == 1){
					motor_param_init();
            motor_info_init((MOTOR_RS+2*MOS_RS), MOTOR_LS, MOTOR_KFI, MOTOR_NP); /* ¨®??¡ì¡Á??¡§¨°?2?¨ºy */
					SysState++;
				}
    } else if(SysState >= 1) {
        motor_loop();
    }

    slowProtect();
}

void task_10ms(void)
{
//    if (init_count < 300) {
//        if (init_count == 298) {
//            motor_start();
//        }
//        init_count += 1;
//    } 
//    else if (init_count <= 205) {
//        setValue0(205-200);
//        
//        init_count += 1;
//    }
        
    
}

void task_100ms(void)
{
    static uint32_t delay;
    task_cnt100ms++;
    if (task_cnt100ms%2==0) {
        task_200ms();
    }
    if (task_cnt100ms%10==0) {
        task_cnt100ms = 0;
        task_1s();
    }
}

void task_200ms(void)
{
    if (user_request_state != user_request_current_state) {
        if (user_request_state == 1) {
            motor_start();
        } else if (user_request_state == 0) {
            motor_stop();
        }
        user_request_current_state = user_request_state;
    }
    slowProtect200ms();
}

void task_1s(void)
{
//		task_cnt1min++;
//    if(task_cnt1min > 90){
//			task_cnt1min = 0;
//      gs.error = 0;
//		}
    //RUNLED_Toggle();
}


