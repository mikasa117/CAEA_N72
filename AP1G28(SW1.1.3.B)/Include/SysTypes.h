#if !defined( _SYS_TYPES_H_ )
#define _SYS_TYPES_H_

#include "Platform_Types.h"

/*=======================================================================*
 * Fixed width word size data types:                                     *
 *   int8, int16, int32     - signed 8, 16, or 32 bit integers     *
 *   uint8, uint16, uint32  - unsigned 8, 16, or 32 bit integers   *
 *=======================================================================*/
typedef signed char S8;
typedef unsigned char U8;
typedef signed short S16;
typedef unsigned short U16;
typedef long S32;
//typedef unsigned long U32;

/*****************************************************************************
|    Bits Data Types
|****************************************************************************/
typedef  struct
{
	unsigned Bit0 : 1;
	unsigned Bit1 : 1;
	unsigned Bit2 : 1;
	unsigned Bit3 : 1;
	unsigned Bit4 : 1;
	unsigned Bit5 : 1;
	unsigned Bit6 : 1;
	unsigned Bit7 : 1;
} BITS8;

typedef struct
{
	unsigned Bit0  : 1;
	unsigned Bit1  : 1;
	unsigned Bit2  : 1;
	unsigned Bit3  : 1;
	unsigned Bit4  : 1;
	unsigned Bit5  : 1;
	unsigned Bit6  : 1;
	unsigned Bit7  : 1;
	unsigned Bit8  : 1;
	unsigned Bit9  : 1;
	unsigned Bit10 : 1;
	unsigned Bit11 : 1;
	unsigned Bit12 : 1;
	unsigned Bit13 : 1;
	unsigned Bit14 : 1;
	unsigned Bit15 : 1;
} BITS16;

/*****************************************************************************
|    Function Pointer
|****************************************************************************/
typedef void ( * FtnPtr )( void );
/*typedef void (* FAR FarFtnPtr)(void);
typedef void (* FAR FarEvtFtnPtr)(uint16);
typedef const FarFtnPtr* FAR FarFtnPtr_Arry;*/

/***
Constant Function pointer
***/
typedef void ( * const CnstFtnPtr )( void );

/*****************************************************************************
|    2 Dimension array pointer
|****************************************************************************/
typedef const uint16 ( * TwoDimCstArryPtr_U16 )[2];
typedef const sint16 ( * TwoDimCstArryPtr_S16 )[2];
typedef const uint8 ( * TwoDimCstArryPtr_U8 )[2];

/*****************************************************************************
|    General Define
|****************************************************************************/
#define Shift8bit      8U
#define Shift16bit     16U
#define Shift24bit     24U

#define SET_BIT_ECC(Data, Offset) 		((Data) |= (uint32)1 << (Offset))
#define RESET_BIT(Data, Offset)   		((Data) &= ~((uint32)1 << (Offset)))
#define GET_BIT(Data, Offset)     		(((Data) >> (Offset)) & (uint32)0x01)

#define SET_UINT32_BIT(Data, Offset) 	(((Data)) |= ((uint32)1 << (Offset)))
#define SET_UINT16_BIT(Data, Offset)   	(((Data)) |= ((uint16)1 << (Offset)))
#define SET_UINT8_BIT(Data, Offset)    	(((Data)) |= ((uint8) 1 << (Offset)))
#define RESET_UINT32_BIT(Data, Offset) 	(((Data)) &= ~((uint32)1 << (Offset)))
#define RESET_UINT16_BIT(Data, Offset) 	(((Data)) &= ~((uint16)1 << (Offset)))
#define RESET_UINT8_BIT(Data, Offset)  	(((Data)) &= ~((uint8) 1 << (Offset)))

#define GET_UINT32_BIT(Data, Offset)  	(((uint8)(((uint32) (Data)) >> (Offset))) & 0x01)
#define GET_UINT16_BIT(Data, Offset)   	(((uint8)(((uint16) (Data)) >> (Offset))) & 0x01)
#define GET_UINT8_BIT(Data, Offset)   	(((uint8)(((uint8 ) (Data)) >> (Offset))) & 0x01)

#define Zero       0u
#define One	       1u
#define Two        2u
#define Three      3u
#define Four       4u

#define S_Zero     0

# define STD_QAC_CHECK_EN 0U

#ifndef STATIC
#define STATIC  static
#endif

/*
#ifndef FAR
#define FAR
#endif
*/

#ifndef RPTR
#define RPTR
#endif

#ifndef NEAR
#define NEAR
#endif

#define LOC_FAR
#define ICCA_32BIT
#define DATATYPE

#ifndef GMLAN_VALID
#define GMLAN_VALID 0
#endif

#ifndef GMLAN_INVALID
#define GMLAN_INVALID 1
#endif

#ifndef INTERRUPTFUC
#define INTERRUPTFUC interrupt
#endif

typedef enum
{
	LOW = 0,                           	/* Default value */
	HIGH
} TeHWIO_e_State;
/*
typedef enum
{
	Fail = 0,                  */        	/* Default value */
/*	Sucess
} Result;
*/
typedef enum
{
	PowerMode_OFF = 0U,                   	    /* Default value */
	PowerMode_ACC,
	PowerMode_RUN,
	PowerMode_CRANK
} PowerMode_Type;


#endif

