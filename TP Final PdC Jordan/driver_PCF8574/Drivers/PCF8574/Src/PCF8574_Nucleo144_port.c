/*
 * PCF8574_Nucleo144_port.c
 *
 *  Created on: 15 jun. 2022
 *      Author: Win10
 */

#include "PCF8574.h"

extern I2C_HandleTypeDef hi2c1;


void PCF8574_Delay_Init(void)
{
	CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
	CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk;

	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
	DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

	DWT->CYCCNT = 0;

	/* 3 NO OPERATION instructions */
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
	__ASM volatile ("NOP");
}

void PCF8574_Delay_us(uint32_t us)
{
	uint32_t cycles = (SystemCoreClock/1000000L)*us;
	uint32_t start = DWT->CYCCNT;
	volatile uint32_t cnt;
	do
	{
		cnt = DWT->CYCCNT - start;
	} while(cnt < cycles);
}

void PCF8574_Delay_ms(uint32_t Delay)
{
	HAL_Delay(Delay);
}

void PCF8574_ExpanderWrite(uint8_t _data, uint8_t dpBacklight)
{
	uint8_t data = _data | dpBacklight;
	HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDR, (uint8_t*)&data, 1, 10);
}



