#include <stdio.h>

#include "fr30xx.h"
#include "flashdb.h"
#include "fdb_app.h"

/* KVDB object */
static struct fdb_kvdb kvdb = {0};
static struct fdb_kvdb kvdb_ext;

/* critical zone protection */
static CPU_SR cpu_sr = 0;

static void lock(fdb_db_t db)
{
    /* used to avoid reentry */
    if (cpu_sr & 0xff00)
    {
        while (1)
            ;
    }

    cpu_sr = CPU_SR_Save(0x20);
    cpu_sr |= 0xff00;
}

static void unlock(fdb_db_t db)
{
    cpu_sr &= 0xff;
    CPU_SR_Restore(cpu_sr);
}

int flashdb_init(void)
{
    fdb_err_t result;

    /* set the lock and unlock function if you want */
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_LOCK, (void *)lock);
    fdb_kvdb_control(&kvdb, FDB_KVDB_CTRL_SET_UNLOCK, (void *)unlock);

    /* Key-Value database initialization
     *
     *       &kvdb: database object
     *       "env": database name
     * "fdb_kvdb1": The flash partition name base on FAL. Please make sure it's in FAL partition table.
     *              Please change to YOUR partition name.
     * &default_kv: The default KV nodes. It will auto add to KVDB when first initialize successfully.
     *        NULL: The user data if you need, now is empty.
     */

    result = fdb_kvdb_init(&kvdb, "env", "FlashEnv", NULL, NULL);

    if (result != FDB_NO_ERR)
    {
        return -1;
    }

    //fdb_kvdb_init(&kvdb_ext, "ext", "ExtEnv", NULL, NULL);

    return 0;
}

fdb_err_t flashdb_set(uint32_t key, uint8_t *value, uint32_t length)
{
    struct fdb_blob blob;

    return fdb_kv_set_blob(&kvdb, key, fdb_blob_make(&blob, value, length));
}

size_t flashdb_get(uint32_t key, uint8_t *value, uint32_t length)
{
    struct fdb_blob blob;

    return fdb_kv_get_blob(&kvdb, key, fdb_blob_make(&blob, value, length));
}

size_t flashdb_get_length(uint32_t key)
{
    struct fdb_kv kv;

    if (fdb_kv_get_obj(&kvdb, key, &kv) == NULL)
    {
        return 0;
    }
    else
    {
        return kv.value_len;
    }
}

fdb_err_t flashdb_del(uint32_t key)
{
    return fdb_kv_del(&kvdb, key);
}

//////////////////exter flash///////////////////////////////
fdb_err_t flashdb_exter_set(uint32_t key, uint8_t *value, uint32_t length)
{
    struct fdb_blob blob;

    return fdb_kv_set_blob(&kvdb_ext, key, fdb_blob_make(&blob, value, length));
}

size_t flashdb_exter_get(uint32_t key, uint8_t *value, uint32_t length)
{
    struct fdb_blob blob;

    return fdb_kv_get_blob(&kvdb_ext, key, fdb_blob_make(&blob, value, length));
}

size_t flashdb_exter_get_length(uint32_t key)
{
    struct fdb_kv kv;

    if (fdb_kv_get_obj(&kvdb_ext, key, &kv) == NULL)
    {
        return 0;
    }
    else
    {
        return kv.value_len;
    }
}

fdb_err_t flashdb_exter_del(uint32_t key)
{
    return fdb_kv_del(&kvdb_ext, key);
}

/*
 * Function : get user id according to fdb key
 *  Input params : key: fdb key
 *  Return:
 *     0: Not found
 *     >0: user id
 *
 * Author: chuzewei on 2026/03/02
 */
uint16_t get_userid_from_fdbkey(uint32_t key)
{
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    /* determin whether key is from user id */
    if ((key >> 16) != (FDB_KEY_USER_BASE >> 16))
    {
        return 0;
    }
    
    for (int i = 0; i < sizeof(userid)/sizeof(uint16_t); i++)
    {
        if ((userid[i] & 0xFF) == (key & 0xFF))
        {
            return userid[i];
        }
    }
    return 0;
}

/*
 * Function: Write DID data to internal flash.
 * Author: chuzewei 
 * Date: 2026/03/31
 */
uint8_t uds_flash_set(uint16_t id, uint8_t *value, uint32_t length)
{
    fdb_err_t ret = FDB_NO_ERR;
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    if (!value)
    {
        printf("Params value is NULL!\r\n");
        return 1;
    }
    
    for (uint8_t i = 0; i < sizeof(userid)/sizeof(userid[0]); i++)
    {
        if (id == userid[i])
        {
            uint32_t len = USERID_DATA_LEN(userid[i]);
            
            if (length > len)
            {
                printf("Data to write is too large. length = %u\r\n", length);
                length = len;
            }
            ret = flashdb_set(FDB_KEY_USER_1+i, (void*)value, length);
            if (FDB_NO_ERR == ret)
            {
                // success
                return 0;
            }
            else
            {
                // fails
                return (uint8_t)ret;
            }
            //return length;
        }
    }
    
    printf("Uds id is error.\r\n");
    return 2;
}

uint8_t uds_flash_get(uint16_t id, uint8_t *value, uint32_t length)
{
    size_t ret = 0;
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    if (!value)
    {
        printf("Params value is NULL!\r\n");
        return 1;
    }
    
    for (uint8_t i = 0; i < sizeof(userid)/sizeof(userid[0]); i++)
    {
        if (id == userid[i])
        {
            uint32_t len = USERID_DATA_LEN(userid[i]);
            
            if (length < len)
            {
                printf("Buffer is too small. length = %u\r\n", length);
                //length = len;
            }
            else if (length > len)
            {
                length = len;
            }
            ret = flashdb_get(FDB_KEY_USER_1+i, (void*)value, length);
            if (ret > 0)
            {
                // success
                return 0;
            }
            else
            {
                printf("Read out 0 byte !\r\n");
                return 1;
            }
            //return length;
        }
    }
  
    printf("uds id is error!\r\n");
    return 2;
}

uint8_t uds_flash_del(uint16_t id)
{
    fdb_err_t ret = FDB_NO_ERR;
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    for (uint8_t i = 0; i < sizeof(userid)/sizeof(userid[0]); i++)
    {
        if (id == userid[i])
        {
            ret = flashdb_del(FDB_KEY_USER_1+i);
            if (FDB_NO_ERR == ret)
            {
                //success
                return 0;
            }
            else
            {
                // fail
                return (uint8_t)ret;
            }
        }
    }
    
    printf("uds id is error!\r\n");
    return 2;
}

void uds_flash_test_write(void)
{
    size_t ret = 0;
 //   uint8_t read_data[25] = {0};
    uint8_t write_data[25] = {0};
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    //USER_ID_UDS_U300616
    
    printf("flashdb_write_test:\r\n");
    for (uint8_t k = 0; k < sizeof(userid)/sizeof(userid[0]); k++)
    {
        uint32_t len;
        len = USERID_DATA_LEN(userid[k]);
        for (uint8_t i = 0; i < (len & 0xFF); i++)
        {
            write_data[i] = k + i;
            printf("%02X ", write_data[i]);
        } 
        printf("\r\n");
        
        //flashdb_set(FDB_KEY_USER_1+k, (void*)write_data, sizeof(write_data));
        uds_flash_set(userid[k], (void*)write_data, len);
    }
    printf("\r\n");
#if 0    
    printf("\r\n");
    printf("\r\n");
    printf("flashdb_read_test:\r\n");
    for (uint8_t i = 0; i < 15; i++)
    {
        memset(read_data, 0, sizeof(read_data));
        uds_flash_get(userid[i], (void*)read_data, sizeof(read_data));
        //flashdb_get(FDB_KEY_USER_1 + i, (void*)read_data, sizeof(read_data));        
        //flashdb_exter_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        for (uint8_t j = 0; j < 25; j++)
        {
            printf("%02X ", read_data[j]);
        }
        printf("\r\n");
    }
#endif    
    printf("\r\nend data\r\n");
}

void uds_flash_test_read(void)
{
    size_t ret = 0;
    uint8_t read_data[25] = {0};
    //uint8_t write_data[25] = {0};
    uint16_t userid[] = USER_ID_UDS_TABLE;
    
    //USER_ID_UDS_U300616
#if 0
    printf("flashdb_write_test:\r\n");
    for (uint8_t k = 0; k < 15; k++)
    {
        for (uint8_t i = 0; i < 25; i++)
        {
            write_data[i] = k + i;
            printf("%d ", write_data[i]);
        }
        
        //flashdb_set(FDB_KEY_USER_1+k, (void*)write_data, sizeof(write_data));
        uds_flash_set(userid[k], (void*)write_data, sizeof(write_data));
    }
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
#endif    
    printf("flashdb_read_test:\r\n");
    for (uint8_t i = 0; i < sizeof(userid)/sizeof(userid[0]); i++)
    {
        uint32_t len;
                
        memset(read_data, 0, sizeof(read_data));
        len = USERID_DATA_LEN(userid[i]);
        uds_flash_get(userid[i], (void*)read_data, len);
        //flashdb_get(FDB_KEY_USER_1 + i, (void*)read_data, sizeof(read_data));        
        //flashdb_exter_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        for (uint8_t j = 0; j < (len & 0xFF); j++)
        {
            printf("%02X ", read_data[j]);
        }
        printf("\r\n");
    }
    printf("\r\nend data\r\n");
}

void uds_flash_test_del(uint16_t id)
{
    uint8_t ret;
    
    ret = uds_flash_del(id);
    if (ret)
    {
        printf("Failed to delete: 0x%X\r\n", id);
    }
    else
    {
        printf("Succeeded in deleting: 0x%X\r\n", id);
    }
}

void uds_flash_test_add(uint16_t id)
{
    uint8_t wdata[25] = {0};
    uint8_t len = USERID_DATA_LEN(id);
    uint8_t ret;
    
    for (uint8_t i = 0; i < len; i++)
    {
        wdata[i] = (i+1)* (id & 0xFF);
    }
    
    ret = uds_flash_set(id, (void*)wdata, (uint32_t)len);
    if (ret)
    {
        printf("Failed to add: 0x%X, ret = %u\r\n", id, ret);
        return;
    }
    
    // read again
    uint8_t rdata[25] = {0};
    ret = uds_flash_get(id, (void*)rdata, (uint32_t)len);
    if (ret)
    {
        printf("Failed to read again after added: 0x%X, ret = %u\r\n", id, ret);
    }
    else
    {
        printf("Succeeded in adding: 0x%X \r\n", id);
        
        for (uint8_t i = 0; i < len; i++)
        {
            printf("%02X ", rdata[i]);
        }
        printf("\r\n\r\n\r\n");
    }
}

void uds_flash_test_lookup(uint16_t id)
{
    uint8_t ret, rdata[25] = {0};
    uint8_t len = USERID_DATA_LEN(id);
    
    ret = uds_flash_get(id, (void*)rdata, (uint32_t)len);
    if (ret)
    {
        printf("Failed to read: 0x%X, ret = %u\r\n", id, ret);
    }
    else
    {
        printf("Succeeded in lookuping: 0x%X \r\n", id);
        
        for (uint8_t i = 0; i < len; i++)
        {
            printf("%02X ", rdata[i]);
        }
        printf("\r\n\r\n\r\n");
    }
}

#if 0
/*
 * Notes: This part of testing codes is supplied by Yachuang Co.
 *        And it may be masked but deleted !
 * By chuzewei on 20260401
 */
void w25q_ext_flash_test()
{
    uint16_t data_fls_db_write[25] = {0};
    printf("flashdb_write_test:\r\n");
    #if 0
    for (uint8_t i = 0; i < 15; i++)
    {
        for (uint8_t j = 0; j < 25; j++)
        {
            data_fls_db_write[j] = i*23+j;
            printf("%d ", data_fls_db_write[j]);
        }
        printf("\r\n");
        flashdb_set(FDB_KEY_USER_1 + i, (void*)data_fls_db_write, sizeof(data_fls_db_write));
        //flashdb_exter_set(FDB_KEY_USER_1 + i, (void*)data_fls_db_write, sizeof(data_fls_db_write));        
    }
    #endif
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    uint16_t data_fls_db_read[25] = {0};
    printf("flashdb_read_test:\r\n");
    for (uint8_t i = 0; i < 15; i++)
    {
        flashdb_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        //flashdb_exter_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        for (uint8_t j = 0; j < 25; j++)
        {
            printf("%d ", data_fls_db_read[j]);
        }
        printf("\r\n");
    }
}

void w25q_ext_flash_write_test(void)
{
    uint16_t data_fls_db_write[25] = {0};
    printf("flashdb_write_test:\r\n");

    for (uint8_t i = 0; i < 15; i++)
    {
        for (uint8_t j = 0; j < 25; j++)
        {
            data_fls_db_write[j] = i*23+j;
            printf("%d ", data_fls_db_write[j]);
        }
        printf("\r\n");
        flashdb_set(FDB_KEY_USER_1 + i, (void*)data_fls_db_write, sizeof(data_fls_db_write));
        //flashdb_exter_set(FDB_KEY_USER_1 + i, (void*)data_fls_db_write, sizeof(data_fls_db_write));        
    }
}

void w25q_ext_flash_read_test(void)
{
    uint16_t data_fls_db_read[25] = {0};
    printf("flashdb_read_test:\r\n");
    for (uint8_t i = 0; i < 15; i++)
    {
        flashdb_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        //flashdb_exter_get(FDB_KEY_USER_1 + i, (void*)data_fls_db_read, sizeof(data_fls_db_read));
        for (uint8_t j = 0; j < 25; j++)
        {
            printf("%d ", data_fls_db_read[j]);
        }
        printf("\r\n");
    }
}
#endif
