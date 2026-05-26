/*
 ******************************************************************************
 * @file    driver_aes.c
 * @author  FreqChip Firmware Team
 * @version V1.0.0
 * @date    2022
 * @brief   IIR module driver.
 *          This file provides firmware functions to manage the 
 *          SEC AES peripheral
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 FreqChip.
 * All rights reserved.
 ******************************************************************************
*/
#include "fr30xx.h"

/*********************************************************************
* @fn      aes_config
*
* @brief   config the aes mode and Endia.
*
* @param   fe_Mode : select AES mode.
* @param   fe_Endian: select AES Endian.
*/
void aes_config(enum_AES_KEY_MODE_t fe_Key_Mode, enum_AES_STU_MODE_t fe_Stu_Mode)
{
    /* Reset AES */
    SEC_AES->Command = SRESET;
    SEC_AES->INT_CTRL.INTEN = 0;
    /* AES Mode */
    SEC_AES->AES_CTRL.KEY_MODE = fe_Key_Mode;
    SEC_AES->AES_CTRL.STU_MODE = fe_Stu_Mode;
}

/*********************************************************************
* @fn      aes_set_encrypt_key
*
* @brief   Set AES encryption key.
*
* @param   key : points to the AES key.
*/
void aes_set_encrypt_key(uint8_t *key)
{
    uint32_t *lp_Key = (void *)key;
    
    SEC_AES->KEY_7 = __REV(*lp_Key++);
    SEC_AES->KEY_6 = __REV(*lp_Key++);
    SEC_AES->KEY_5 = __REV(*lp_Key++);
    SEC_AES->KEY_4 = __REV(*lp_Key++);
    
    switch(SEC_AES->AES_CTRL.KEY_MODE)
    {
        case AES_192:{
            SEC_AES->KEY_3 = __REV(*lp_Key++);
            SEC_AES->KEY_2 = __REV(*lp_Key++);
        }break;

        case AES_256:{            
            SEC_AES->KEY_3 = __REV(*lp_Key++);
            SEC_AES->KEY_2 = __REV(*lp_Key++);
            SEC_AES->KEY_1 = __REV(*lp_Key++);
            SEC_AES->KEY_0 = __REV(*lp_Key++);
        }break;

        default:break;
    }
}

/*********************************************************************
* @fn      aes_set_encrypt_iv
*
* @brief   Set IV for the encrypt/decrypt.
*
* @param   key : points to the AES key.
*/
void aes_set_encrypt_iv(uint8_t *iv)
{
    uint32_t *lp_IV = (void *)iv;

    SEC_AES->IV_3 = __REV(*lp_IV++);
    SEC_AES->IV_2 = __REV(*lp_IV++);
    SEC_AES->IV_1 = __REV(*lp_IV++);
    SEC_AES->IV_0 = __REV(*lp_IV++);
}

/*********************************************************************
* @fn      aes_encrypt
*
* @brief   aes encrypt. 
*
* @param   fp_Data_In:  the pointer of data which is to encrypt.
* @param   fu32_Size:   encrypt size.
* @param   fp_Data_Out: the pointer of data which saves the encryption data.
*/
void aes_encrypt(uint8_t *fp_Data_In, uint32_t fu32_Size, uint8_t *fp_Data_Out)
{
    uint32_t *DataIN  = (uint32_t *)fp_Data_In;
    uint32_t *DataOUT = (uint32_t *)fp_Data_Out;
    
    uint32_t InIndex = 0;
    uint32_t lu32_size;

    lu32_size = fu32_Size/16;
    if (fu32_Size % 16)
        lu32_size++;    
    
    SEC_AES->AES_CTRL.CALC_MODE = AES_ENCRYPT;
    SEC_AES->Command = KEY_RDY;
    
    SEC_AES->DATA_CONSTR = fu32_Size;
    
    /* Block 16 byte */
    while(InIndex < lu32_size)
    {
        __AES_IS_FIFO_STATUS(AES_TX_FIFO_FULL);
        
        for(int i = 0; i < 4;i++)
        {
            SEC_AES->FIFO_DATA = *DataIN++;   
        }

        while(!__AES_IS_FLAG_STATUS(AES_CALC_DONE));
        SEC_AES->INT_CTRL.INTCLR = 0;
        SEC_AES->Command = STATE_FLAG_CLR;        

        for(int i = 0; i < 4;i++)
        {
            *DataOUT++ = SEC_AES->FIFO_DATA;             
        } 
        InIndex++;    
    }
    /* Reset AES */
    SEC_AES->Command = SRESET;    
}

/*********************************************************************
* @fn      aes_decrypt
*
* @brief   aes decrypt
* 
* @param   fp_Data_In:  the pointer of data which is to decrypt.
* @param   fu32_Size:   decrypt size.
* @param   fp_Data_Out: the pointer of data which saves the decryption data.
*/
void aes_decrypt(uint8_t *fp_Data_In, uint32_t fu32_Size, uint8_t *fp_Data_Out)
{
    uint32_t *DataIN  = (uint32_t *)fp_Data_In;
    uint32_t *DataOUT = (uint32_t *)fp_Data_Out;
    
    uint32_t InIndex = 0;
    uint32_t lu32_size;

    lu32_size = fu32_Size/16;
    if (fu32_Size % 16)
        lu32_size++;    
    
    SEC_AES->AES_CTRL.CALC_MODE = AES_DECRYPE;
    SEC_AES->Command = KEY_RDY;
    
    SEC_AES->DATA_CONSTR = fu32_Size;
    
    /* Block 16 byte */
    while(InIndex < lu32_size)
    {
        __AES_IS_FIFO_STATUS(AES_TX_FIFO_FULL);
        
        for(int i = 0; i < 4;i++)
        {
            SEC_AES->FIFO_DATA = *DataIN++;
        }

        while(!__AES_IS_FLAG_STATUS(AES_CALC_DONE));
        SEC_AES->INT_CTRL.INTCLR = 0;
        SEC_AES->Command = STATE_FLAG_CLR;  
        
        for(int i = 0; i < 4;i++)
        {
            *DataOUT++ = SEC_AES->FIFO_DATA;             
        } 
        InIndex++;        
    }
        /* Reset AES */
    SEC_AES->Command = SRESET;
}
