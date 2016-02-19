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
	i2c.I2C_Timing = (1 << 28) /* PRESC */
	| (4 << 20) /* SCLDEL */
	| (2 << 16) /* SDADEL */
	| (0x15 << 8) /* SCLH */
	| (0x13 << 0); /* SCLL */
	I2C_Init(I2C, &i2c);
	I2C_Cmd(I2C, ENABLE);

	return 0;
}
