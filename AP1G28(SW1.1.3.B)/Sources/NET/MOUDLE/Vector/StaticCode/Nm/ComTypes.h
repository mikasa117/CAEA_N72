
#if !defined(COM_TYPE_H)
#define COM_TYPE_H

typedef unsigned char CanIf_WakeUpSourceType;   /*at most,support 8 wakeupsources*/
typedef unsigned char CanIf_PduIdType;
typedef unsigned char CanIf_HwHandleType;
typedef unsigned char CanIf_CanDlcType;
typedef unsigned char CanIf_CanDataType;
typedef unsigned int  CanIf_CanIdType;
typedef unsigned char CanIf_uint8Type;
typedef unsigned int  CanIf_CanTxCycleType;

typedef unsigned char ComUint8;
typedef unsigned short ComUint16;
typedef unsigned long ComUint32;
typedef unsigned char ComStd_ReturnType;

typedef signed short Comint16;
typedef signed char Comint8;

typedef enum 
{
    CANIF_ERROR_ACTIVE = 0,
    CANIF_ERROR_PASSIVE,
    CANIF_ERROR_BUSOFF	
}CanIf_ControllerErrorType;

#define COM_E_OK       0U
#define COM_E_NOT_OK   1U
#define COM_E_PENDING  2U

#define COM_TRUE       1U
#define COM_FALSE      0U

# ifndef COM_NULL_PTR
#  define COM_NULL_PTR  0L
# endif

# ifndef COM_STD_ON
#  define COM_STD_ON  1U
# endif

# ifndef COM_STD_OFF
#  define COM_STD_OFF  0U
# endif

#endif

