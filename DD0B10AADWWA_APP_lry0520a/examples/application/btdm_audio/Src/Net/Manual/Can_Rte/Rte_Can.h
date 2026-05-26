#ifndef __RTE_CAN_H__
#endif
#define __RTE_CAN_H __

#include "fr30xx.h"

//#include "can_Drv.h"
#include "drv_par.h"
#include "il_par.h"


/****************** Receive *********************/

//EHB_Status (0x125) variables

extern float    Rte_Read_EHB_VehicleSpeed(void);
extern uint8_t  Rte_Read_EHB_VehicleSpeedInvalid(void);

//IPK_TotalOdometer (0x3F1) variables
extern uint32_t  Rte_Read_IPK_IPKTotalOdometer(void);


//PMS_VIN (0x610) variables 
extern uint8_t  Rte_Read_PMS_VINCode7_14_S(void);
extern uint8_t  Rte_Read_PMS_VINCode6_13_S(void);
extern uint8_t  Rte_Read_PMS_VINCode5_12_S(void);
extern uint8_t  Rte_Read_PMS_VINCode4_11_S(void);
extern uint8_t  Rte_Read_PMS_VINCode3_10_17_S(void);
extern uint8_t  Rte_Read_PMS_VINCode2_9_16_S(void);
extern uint8_t  Rte_Read_PMS_VINCode1_8_15_S(void);
extern uint8_t  Rte_Read_PMS_VINMessageNum_S(void);


//TBOX_DateTime_Info (0x3E0) variables
extern uint8_t  Rte_Read_TBOX_Second(void);
extern uint8_t  Rte_Read_TBOX_Minute(void);
extern uint8_t  Rte_Read_TBOX_Hour(void);
extern uint8_t  Rte_Read_TBOX_Day(void);
extern uint8_t  Rte_Read_TBOX_Month(void);
extern uint16_t  Rte_Read_TBOX_Year(void);









/****************** write *********************/


//MMI_Status_Info (0x2A4) variables
extern  void RteCan_Write_MMI_WorkMode( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_ReturnSwStatus( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_ConfirmSwStatus( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_DownSwStatus( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_UpSwStatus( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_LeftSwStatus( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_MMI_RightSwStatus( uint32_t LeRteCan_u_Value );

//MMI_TextBTData (0x0F9) variables
extern  void RteCan_Write_MMI_TextBTDataFrame( vuint8* LeRteCan_u_Value );

//MMI_TextMMData (0x0FB) variables
extern  void RteCan_Write_MMI_TextMultDataFrame( vuint8* LeRteCan_u_Value );

//TTS_Status (0x249) variables
extern  void RteCan_Write_TTS_BluetoothFunction( uint32_t LeRteCan_u_Value );
extern  void RteCan_Write_TTS_BluetoothConnect( uint32_t LeRteCan_u_Value );