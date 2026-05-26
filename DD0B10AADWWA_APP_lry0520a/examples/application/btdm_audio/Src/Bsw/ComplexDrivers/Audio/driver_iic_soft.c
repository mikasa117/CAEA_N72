
#include <stdio.h>
#include <stdint.h>

#include "driver_gpio.h"

#include "driver_iic_soft.h"

// #include "printf.h"

#define IO_I2C_TEST

#ifdef IO_I2C_TEST
#define I2C_SCL_PIN GPIO_PIN_6
#define I2C_SCL_DIR_OUT                               \
	(SYSTEM->PortB_InputOpenCircuit) &= ~I2C_SCL_PIN; \
	(GPIOD->GPIO_OutputEN &= ~I2C_SCL_PIN) // gpio_set_dir((I2C_SCL_PIN/8),(I2C_SCL_PIN%8),0)
#define I2C_SCL_DIR_IN                               \
	(SYSTEM->PortB_InputOpenCircuit) |= I2C_SCL_PIN; \
	lu32_Current_Pin(GPIOD->GPIO_OutputEN |= I2C_SCL_PIN)
#define I2C_SCL_OUT_H (GPIOD->GPIO_BIT_SET = I2C_SCL_PIN)
#define I2C_SCL_OUT_L (GPIOD->GPIO_BIT_CLEAR = I2C_SCL_PIN)
#define I2C_SCL_IN_VAL (GPIOD->GPIO_IN_DATA & I2C_SCL_PIN)

#define I2C_SDA_PIN GPIO_PIN_7
#define I2C_SDA_DIR_OUT                               \
	(SYSTEM->PortD_InputOpenCircuit) &= ~I2C_SDA_PIN; \
	(GPIOD->GPIO_OutputEN &= ~I2C_SDA_PIN) // gpio_set_dir((I2C_SCL_PIN/8),(I2C_SCL_PIN%8),0)
#define I2C_SDA_DIR_IN                               \
	(SYSTEM->PortD_InputOpenCircuit) |= I2C_SDA_PIN; \
	(GPIOD->GPIO_OutputEN |= I2C_SDA_PIN)
#define I2C_SDA_OUT_H (GPIOD->GPIO_BIT_SET = I2C_SDA_PIN)
#define I2C_SDA_OUT_L (GPIOD->GPIO_BIT_CLEAR = I2C_SDA_PIN)
#define I2C_SDA_IN_VAL (GPIOD->GPIO_IN_DATA & I2C_SDA_PIN)

#endif

#define DELAY_TIME1 1 // 2
#define DELAY_TIME2 2 // 4
#define DELAY_TIME3 3 // 6
#define DELAY_TIME4 4 // 8

#ifdef IO_I2C_TEST
__attribute__((section("ram_code"))) void I2c_Delay(uint32_t us)
{
	//    return;
	//	volatile uint32_t i = 0;
	//    while(i++ < us )
	//        __NOP();
	switch (us)
	{
	case DELAY_TIME1:
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		// __NOP();
		system_delay_us(1);    // 10
		break;
	case DELAY_TIME2:
		__NOP();
		__NOP();
		break;
	case DELAY_TIME3:
		__NOP();
		__NOP();
		break;
	case DELAY_TIME4:
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		break;
	default:
		break;
	}
}

void Send_Ack(void)
{
	I2C_SDA_OUT_L;
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_H;
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_L;
	// I2C_SDA_OUT_H;
}

__attribute__((section("ram_code"))) void Send_NAck(void)
{
	I2C_SDA_OUT_H;
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_H;
	// I2c_Delay(5);
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_L;
}

__attribute__((section("ram_code"))) uint8_t Read_NAck(void)
{
	uint8_t ack_state = 0;
	uint8_t ack_wait_cnt = 0;

	I2C_SCL_OUT_L;
	I2C_SDA_DIR_IN;
	while (!I2C_SDA_IN_VAL)
	{
		I2c_Delay(DELAY_TIME1);
		ack_wait_cnt++;
		if (ack_wait_cnt > 5)
		{
			ack_wait_cnt = 0;
			break;
		}
	}
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_H;
	I2c_Delay(DELAY_TIME1);

	if (I2C_SDA_IN_VAL)
		ack_state = 1;
	else
		ack_state = 0;
	// I2c_Delay(5);
	I2C_SCL_OUT_L;
	I2C_SDA_DIR_OUT;
	I2c_Delay(DELAY_TIME1);

	return ack_state;
}

__attribute__((section("ram_code"))) uint8_t Read_Ack(void)
{
	uint8_t ack_state = 0;

	I2C_SDA_DIR_IN;
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_H;
	I2c_Delay(DELAY_TIME1);

#if 1
	if (I2C_SDA_IN_VAL)
		ack_state = 0;
	else
		ack_state = 1;
#endif
	// I2c_Delay(5);
	I2C_SCL_OUT_L;
	I2C_SDA_DIR_OUT;
	I2C_SDA_OUT_L;
	// I2c_Delay(DELAY_TIME1);

	return ack_state;
}

__attribute__((section("ram_code"))) void Start_I2c(void)
{
	I2C_SCL_OUT_H;
	I2C_SDA_OUT_H;
	I2c_Delay(DELAY_TIME1);
	I2C_SDA_OUT_L;
	I2c_Delay(DELAY_TIME1);
	I2C_SCL_OUT_L;
}

__attribute__((section("ram_code"))) void Stop_I2c(void)
{
	I2C_SDA_OUT_L;
	I2C_SCL_OUT_L;
	I2c_Delay(DELAY_TIME3 /*5*/);

	I2C_SCL_OUT_H;
	I2c_Delay(DELAY_TIME2 /*5*/);
	I2C_SDA_OUT_H;
}

__attribute__((section("ram_code"))) void Write_One_Byte(uint8_t data)
{
	uint8_t send_count = 0;

	I2C_SCL_OUT_L;
	for (send_count = 0; send_count < 8; send_count++)
	{
		I2c_Delay(DELAY_TIME1);
		if ((data << send_count) & 0x80)
		{
			// os_printf("1");
			I2C_SDA_OUT_H;
		}
		else
		{
			// os_printf("0");
			I2C_SDA_OUT_L;
		}
		I2c_Delay(DELAY_TIME1);
		I2C_SCL_OUT_H;
		I2c_Delay(DELAY_TIME1);
		I2C_SCL_OUT_L;
	}
}

__attribute__((section("ram_code"))) uint8_t Read_One_Byte(void)
{
	uint8_t data = 0, i = 0;

	// I2C_SDA_OUT_H;
	I2C_SDA_DIR_IN;
	for (i = 0; i < 8; i++)
	{
		I2c_Delay(DELAY_TIME1);
		I2C_SCL_OUT_H;
		if (I2C_SDA_IN_VAL)
			data |= (1 << (7 - i));
		// else
		// data &= ~(1<<i);
		I2c_Delay(DELAY_TIME1);
		I2C_SCL_OUT_L;
	}
	I2C_SDA_DIR_OUT;

	return data;
}

uint8_t iic_Read_handle(uint8_t iic_addr, uint8_t read_reg, uint8_t *buff, uint8_t len)
{
	uint8_t i = 0;
	uint8_t write_addr = 0, read_addr = 0;
	write_addr = (iic_addr << 1);
	read_addr = (iic_addr << 1) | 0x01;
	Start_I2c();

	Write_One_Byte(write_addr);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	// I2c_Delay(200/*10*/);

	Write_One_Byte(read_reg);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	I2c_Delay(DELAY_TIME4);

	Start_I2c();
	Write_One_Byte(read_addr);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	for (i = 0; i < len; i++)
	{
		buff[i] = Read_One_Byte();
		if ((i + 1) < len)
			Send_Ack();
		// I2c_Delay(DELAY_TIME1);
	}
	// Read_NAck();
	Send_NAck();
	Stop_I2c();
	return 1;
}

uint8_t iic_Write_handle(uint8_t iic_addr, uint8_t write_reg, uint8_t *buff, uint8_t len)
{
	uint8_t i = 0;
	uint8_t write_addr = 0, read_addr = 0;
	write_addr = (iic_addr << 1);
	read_addr = (iic_addr << 1) | 0x01;
	Start_I2c();

	Write_One_Byte(write_addr);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	// I2c_Delay(200/*40*//*10*/);
	Write_One_Byte(write_reg);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}

	for (i = 0; i < len; i++)
	{
		Write_One_Byte(buff[i]);
		if (!Read_Ack())
		{
			printf("No ack\r\n");
			Stop_I2c();
			return 0;
		}
		// I2c_Delay(DELAY_TIME1);
	}

	Stop_I2c();

	return 1;
}

uint8_t iic_Read_NoRegAddr_handle(uint8_t iic_addr, uint8_t *buff, uint8_t len)
{
	uint8_t i = 0;
	uint8_t write_addr = 0, read_addr = 0;
	write_addr = (iic_addr << 1);
	read_addr = (iic_addr << 1) | 0x01;

	Start_I2c();
	Write_One_Byte(read_addr);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	for (i = 0; i < len; i++)
	{
		buff[i] = Read_One_Byte();
		if ((i + 1) < len)
			Send_Ack();
#if 0
        if((i < len-1) && !Read_Ack())
    	{
            printf("No ack\r\n");
    		Stop_I2c();
    		return 0;
    	}
#endif
		// I2c_Delay(DELAY_TIME1);
	}
	// Read_NAck();
	Send_NAck();
	Stop_I2c();
	return 1;
}

uint8_t iic_Write_NoRegAddr_handle(uint8_t iic_addr, uint8_t *buff, uint8_t len)
{
	uint8_t i = 0;
	uint8_t write_addr = 0, read_addr = 0;
	write_addr = (iic_addr << 1);
	read_addr = (iic_addr << 1) | 0x01;
	Start_I2c();

	Write_One_Byte(write_addr);
	if (!Read_Ack())
	{
		printf("No ack\r\n");
		Stop_I2c();
		return 0;
	}
	// I2c_Delay(200/*40*//*10*/);

	for (i = 0; i < len; i++)
	{
		Write_One_Byte(buff[i]);
		if (!Read_Ack())
		{
			printf("No ack\r\n");
			Stop_I2c();
			return 0;
		}
		// I2c_Delay(DELAY_TIME1);
	}

	Stop_I2c();

	return 1;
}

#endif

void user_i2c_init(void)
{

	GPIO_InitTypeDef GPIO_Handle;
	// __SYSTEM_GPIO_CLK_SELECT_COREH();
	__SYSTEM_GPIOD_CLK_ENABLE();
	GPIO_Handle.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_Handle.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Handle.Pull = GPIO_PULLUP;
	GPIO_Handle.Alternate = GPIO_FUNCTION_0;
	gpio_init(GPIOD, &GPIO_Handle);

	/* I2C_SCL_DIR_OUT;
	I2C_SCL_OUT_H;

	I2C_SDA_DIR_OUT;
	I2C_SDA_OUT_H; */
}
