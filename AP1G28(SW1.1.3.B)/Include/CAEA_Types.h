/******************************************************************************
|  File Name :  CAEA_Types.h
|  Description: Company standard definition
|------------------------------------------------------------------------------
| (c) This software is the proprietary of Wenzhou Changjiang AutoMobile (CAEA)
|     All rights are reserved by CAEA.
|------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|------------------------------------------------------------------------------
| Date         Version    Author       Description
| ----------   --------   ------       ----------------------------------------
| 2015-06-02    1.0.0     linbei       Initial
| 2015-06-17    1.0.1     linbei       
******************************************************************************/
#ifndef CAEA_TYPES_H
#define CAEA_TYPES_H
#
/******************************************************************************
 * Description:     : Include File Section                                  
******************************************************************************/
typedef signed char         sint8;   /*                 -128 .. +127                 */
typedef unsigned char       uint8;   /*                    0 .. 255                  */
typedef signed short        sint16;  /*               -32768 .. +32767               */
typedef unsigned short      uint16;  /*                    0 .. 65535                */
typedef signed long         sint32;  /*          -2147483648 .. +2147483647          */
typedef unsigned long       uint32;  /*                    0 .. 4294967295           */

typedef unsigned char   bool1;
/******************************************************************************
 * Description:     : Macro Description Section
******************************************************************************/
#define GLOBAL_SCREEN_TYPE  SCREEN_TYPE_ENTERTAINMENT       /*Board Type*/

#define GLOBAL_SW_TYPE      SCREEN_TYPE_ENTERTAINMENT       /*Software Type*/
#define GLOBAL_TOUCH_TYPE   TOUCH_TYPE_PASS                 /*Touch data Transfer Mode*/


#define TOUCH_TYPE_PASS      0xA5u
#define TOUCH_TYPE_PACK      0x5Au

#define SCREEN_TYPE_INSTRUMENT      0xA5u
#define SCREEN_TYPE_ENTERTAINMENT   0x5Au

#define PROJECT_MR         PRO_U1EI21_L
/*left screen*/
#define PRO_U1EI21_L     0xA5u
/*right screen*/
#define PRO_U1EI21_R     0x5Au

#define HMI_DISPLAY_CONFIG_ENABLE                  0x0u
#define HMI_DISPLAY_CONFIG_DISABLE                 0x1u
#define HMI_DISPLAY_CONFIG_STA                     HMI_DISPLAY_CONFIG_DISABLE


#define TEST_SOFTWARE_FUNC_EXHIBITION         TEST_SOFTWARE_FUNC_DISABLE

#define TEST_SOFTWARE_FUNC_ENABLE     0xA5u/*ALL CONFIG,no toast,light up without CAN signal*/
#define TEST_SOFTWARE_FUNC_DISABLE     0x5Au

#endif
