#include "E2E.h"

#define POLYNOMAIL 0x2F
#define INIT_VALUE 0xFF
#define XOR_VALUE  0xFF

void E2E_InfoInit(E2E_Info_t *e2eInfo)
{
  e2eInfo->count = 0x00;
  e2eInfo->stateMask = E2E_UNINIT;
}

void E2E_PreTransmit(E2E_Info_t *e2eInfo, unsigned char *count, unsigned char *checksum, unsigned char *pData, unsigned short length)
{
  *count = (*count & 0x0F) | (e2eInfo->count << 4);
  *checksum = calcCRC8(POLYNOMAIL, INIT_VALUE, XOR_VALUE, pData, length);
  if(e2eInfo->stateMask == E2E_UNINIT)
  {
    e2eInfo->stateMask = 0x00;
  }
}

void E2E_TransmitConfirmation(E2E_Info_t *e2eInfo)
{
  e2eInfo->count = (e2eInfo->count + 1) & 0x0F;
}

void E2E_PreCopyCheck(E2E_Info_t *e2eInfo, unsigned char count, unsigned char checksum, unsigned char *pData, unsigned short length)
{
  if(e2eInfo->stateMask == E2E_UNINIT)
  {
    e2eInfo->count = count;
    e2eInfo->stateMask = 0x00;
  }
  else
  {
    if(count != e2eInfo->count)
    {
      e2eInfo->stateMask |= E2E_ALIVEOUNT_FAILED;
    }
    else
    {
      e2eInfo->stateMask &= ~E2E_ALIVEOUNT_FAILED;
    }
  }
  if(checksum != calcCRC8(POLYNOMAIL, INIT_VALUE, XOR_VALUE, pData, length))
  {
    e2eInfo->stateMask |= E2E_CHECKSUM_FAILED;
  }
  else
  {
    e2eInfo->stateMask &= ~E2E_CHECKSUM_FAILED;
  }
  e2eInfo->count = (e2eInfo->count + 1) & 0x0F;
}

unsigned char E2E_GetE2EState(E2E_Info_t *e2eInfo)
{
  return e2eInfo->stateMask;
}

unsigned char calcCRC8(unsigned char polynomial, unsigned char initial, unsigned char xorValue, unsigned char *pData, unsigned short length)
{
  unsigned short byte_index;
  unsigned char bit_index;
  unsigned char crc;
  
  crc = initial;//FF
  for( byte_index = 0; byte_index < length; ++byte_index ) 
  { 
    crc ^= pData[byte_index]; 
    for( bit_index = 0; bit_index < 8; ++bit_index ) 
    { 
      if( (crc & 0x80) != 0 ) 
        crc = (crc << 1) ^ polynomial; //2F
      else 
        crc = (crc << 1); 
    } 
  }
  crc ^= xorValue;//FF
  
  return crc;
}
