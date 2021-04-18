#include "ds18b20.h"
//-----------------------------------------------------------------------------------
/* PRIVATE FUNCTIONS DECLARATIONS */
//-----------------------------------------------------------------------------------
static uint8_t ds18b20ResetDevice(void);
static void ds18b20WriteBit(uint8_t bit);
static uint8_t ds18b20ReadBit(void);
static void ds18b20WriteByte(uint8_t data);
static uint8_t ds18b20ReadByte(void);
//-----------------------------------------------------------------------------------
/* PUBLIC FUNCTIONS DECLARATIONS */
//-----------------------------------------------------------------------------------
__STATIC_INLINE void delayMicroSec(__IO uint32_t microSec)
{
	microSec *= (SystemCoreClock / 1000000) / 8;
	while (microSec--) ;
}
//--------------------------------------------------
uint8_t ds18b20Init(uint8_t mode)
{
	/* Send Reset pulse then wait for Presence Pulse */
	if(ds18b20ResetDevice())
	{
		return 1;
	}

	/* If skip rom then we adress all devices on one line
	 * with the same setting */
	if(mode==SKIP_ROM)
	{
		ds18b20WriteByte(COM_SKIP_ROM);

		ds18b20WriteByte(COM_WRITE_SCRATCHPAD);
		ds18b20WriteByte(0x14); /* Set Th high temp alarm for 50 */
		ds18b20WriteByte(0x8A);	/* Set Tl low temp alarm for -10 */
		ds18b20WriteByte(RESOLUTION_12BIT);
	}
	return 0;
}
//--------------------------------------------------
void ds18b20DevConTemp(uint8_t mode, uint8_t deviceNumber)
{
	ds18b20ResetDevice();

	if(mode == SKIP_ROM)
	{
		ds18b20WriteByte(COM_SKIP_ROM);
	}
	ds18b20WriteByte(COM_CONVERT_T);

	/*
	 * Delay to wait for convert temperature finish.
	 * With resolution of 12, time to end is give or take 750ms
	 * */
//	HAL_Delay(800);
    vTaskDelay(800);
}
//--------------------------------------------------
void ds18b20ReadScratchpad(uint8_t mode, uint8_t *data, uint8_t deviceNumber)
{
	uint8_t i;
	ds18b20ResetDevice();

	if(mode==SKIP_ROM)
	{
		ds18b20WriteByte(COM_SKIP_ROM);
	}
	ds18b20WriteByte(COM_READ_SCRATCHPAD);

	for(i=0;i<8;i++)
	{
		data[i] = ds18b20ReadByte();
	}
}
//--------------------------------------------------
uint8_t ds18b20ReadSign(uint16_t data)
{
	if ( data & (1<<11)) 	{	return 1;	}
	else					{	return 0;	}
}
//--------------------------------------------------
float ds18b20GetTemp(uint16_t data)
{
	float t;

	/* delete all not needed data */
	t = (float)((data & 0x07FF)>>4);
	/* add fraction part */
	t += (float)(data & 0x000F) / 16.0f;
	return t;
}
//-----------------------------------------------------------------------------------
/* PRIVATE FUNCTIONS DEFINITION */
//-----------------------------------------------------------------------------------
static uint8_t ds18b20ResetDevice(void)
{
    uint16_t status = 0;
    uint8_t check = 0;

    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delayMicroSec(480);
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
    delayMicroSec(70);

    status = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);

    if(status == 0) {   check++;    }

    delayMicroSec(300);
    status = HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN);

    if(status == 1) {   check++;    }

    if(check == 2) {    return 1;   }
    else           {    return 0;   }
}
//-----------------------------------------------------------------------------------
static void ds18b20WriteBit(uint8_t bit)
{
	if(bit == 0)
	{
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
		delayMicroSec(65);
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
		delayMicroSec(10);
	}
	else
	{
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
		delayMicroSec(10);
		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
		delayMicroSec(65);
	}
}
//-----------------------------------------------------------------------------------
static uint8_t ds18b20ReadBit(void)
{
	uint8_t bit = 0;

	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
	delayMicroSec(5);

	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
	delayMicroSec(5);

	bit = (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN) ? 1 : 0);
	delayMicroSec(45);

	return bit;
}
//-----------------------------------------------------------------------------------
static void ds18b20WriteByte(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		ds18b20WriteBit((data >> i) & 0x01);
		delayMicroSec(5);
	}
}
//-----------------------------------------------------------------------------------
static uint8_t ds18b20ReadByte(void)
{
	uint8_t data = 0;

	for (uint8_t i = 0; i <= 7; i++)
	{
		data += ds18b20ReadBit() << i;
	}

	return data;
}
//-----------------------------------------------------------------------------------
