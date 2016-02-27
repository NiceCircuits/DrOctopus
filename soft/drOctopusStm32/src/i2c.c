/**
 ******************************************************************************
 * @file    i2c.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-17
 * @brief   I2C driver.
 ******************************************************************************
 */

#include "i2c.h"
#include "config.h"
#include "delay.h"
#include "outputs.h"

static GPIO_TypeDef * const i2cGpios[2] = I2C_GPIOS;
static uint16_t const i2cPins[2] = I2C_PINS;

uint_fast8_t i2cInit(void) {

	GPIO_InitTypeDef gpio;
	I2C_InitTypeDef i2c;
	uint_fast8_t i;

	// Init I2C GPIO.
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	for (i = 0; i < 2; i++) {
		gpio.GPIO_Pin = i2cPins[i];
		GPIO_Init(i2cGpios[i], &gpio);
	}

	// Init I2C peripheral.
	I2C_StructInit(&i2c);
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
	// Timing for ~80kHz.
//	i2c.I2C_Timing = (1 << 28) /* PRESC */
//	| (4 << 20) /* SCLDEL */
//	| (2 << 16) /* SDADEL */
//	| (0x15 << 8) /* SCLH */
//	| (0x13 << 0); /* SCLL */
	// Timing for ~10kHz.
	i2c.I2C_Timing = (1 << 28) /* PRESC */
	| (4 << 20) /* SCLDEL */
	| (2 << 16) /* SDADEL */
	| (0xC3 << 8) /* SCLH */
	| (0xC7 << 0); /* SCLL */

	I2C_Init(I2C, &i2c);
	I2C_Cmd(I2C, ENABLE);
	return 0;
}

uint_fast8_t i2cWrite(uint16_t addr, uint8_t count, uint8_t* payload) {
	uint_fast8_t ret = 0;
	I2C_TransferHandling(I2C, addr, count, I2C_SoftEnd_Mode,
	I2C_Generate_Start_Write);
	// transfer bytes of data
	while (count > 0) {
		timerStartUs(I2C_TIMEOUT_US); // (re)start timeout timer
		// wait for transmit buffer flag
		while ((I2C_GetFlagStatus(I2C, I2C_FLAG_TXIS) == 0) && (timerEnd() == 0)) {
		}
		if (timerEnd()) {
			// I2C  timeout
			ret = 1; // set error flag
			break;
		}
		I2C_SendData(I2C, *payload);
		payload++;
		count--;
	}
	timerStartUs(I2C_TIMEOUT_US); // (re)start timeout timer
	// Wait for transfer complete flag.
	while (I2C_GetFlagStatus(I2C, I2C_FLAG_TC) == 0) {
		if (timerEnd()) {
			// I2C  timeout
			return 2; // set error flag
		}
	}
	I2C_ClearFlag(I2C, I2C_FLAG_TC);
	I2C_GenerateSTOP(I2C, ENABLE);
	timerStartUs(I2C_TIMEOUT_US); // (re)start timeout timer
	// Wait for transfer complete flag.
	while (I2C_GetFlagStatus(I2C, I2C_FLAG_STOPF) == 0) {
		if (timerEnd()) {
			// I2C  timeout
			return 3; // set error flag
		}
	}
	I2C_ClearFlag(I2C, I2C_FLAG_STOPF);
	return ret;
}

#if TEST_MODE == TEST_MODE_I2C

int main(void) {
	uint8_t addr;
	uint8_t payload[] = { 1, 2, 3, 4 };

	defaultInit();
	i2cInit();

	addr = 0x76;
	for (;;) {
		i2cWrite(addr, 4, payload);
		addr += 2;
		if (addr >= 0x7C) {
			addr = 0x76;
		}
	}
}
#endif // TEST_MODE == TEST_MODE_I2C
