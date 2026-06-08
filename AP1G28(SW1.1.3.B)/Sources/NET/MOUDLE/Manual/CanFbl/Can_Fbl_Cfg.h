#if !defined(__FBL_CFG_H__)
#define __FBL_CFG_H__

#include "CAEA_Types.h"
# define kFblStartMagicByte0     0x50u /* 'P' */
# define kFblStartMagicByte1     0x72u /* 'r' */
# define kFblStartMagicByte2     0x6Fu /* 'o' */
# define kFblStartMagicByte3     0x67u /* 'g' */
# define kFblStartMagicByte4     0x53u /* 'S' */
# define kFblStartMagicByte5     0x69u /* 'i' */
# define kFblStartMagicByte6     0x67u /* 'g' */
# define kFblStartMagicByte7     0x6Eu /* 'n' */

typedef struct tagFblInfo
{
  uint8 fblStartMagicFlag[8];    /*40000080*/
  uint8 fblProgmedMagicFlag[4];  /*40000088*/  
  uint8 SecurAccessFAAFlag;      /*4000008C*/
  uint8 :8;                    
  uint8 :8;
  uint8 :8;
  uint8 SecMagicFlag[4];         /*40000090*/     
  uint8 CanTp_FblMagicFlag[4];   /*40000094*/    
}tFblInfo;

#endif
