/**
 ******************************************************************************
 * @file    main.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   drOctopus firmware for STM32.
 * @todo I2C.
 * @todo OLED.
 * @todo Buttons.
 * @todo ESP8266.
 * @todo Self-test functions.
 * @todo BTS diagnostics.
 * @todo Test modes.
 ******************************************************************************
 */

#include "stm32f30x.h"
#include "config.h"
#include "debug.h"
#include "sysTick.h"
#include "outputs.h"
#include "servo.h"
#include "adc.h"
#include "i2c.h"

int main(void) {
	debugSource_t debugMain;
	FunctionalState led = ENABLE;
	int i, j;
	int_fast32_t dir, pos = 0;
	uint16_t adc;
	uint64_t time;
	uint8_t addr;

	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	servoInit();
	adcInit();
	i2cInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	debugPrintln(debugMain, "Hello!");

	time = 0;
	addr = 1;
	for (;;) {
		servoLoop();
		adcLoop();
		if (time <= getTime()) {
			time = getTime() + 1;
			I2C_TransferHandling(I2C, addr, 0, I2C_SoftEnd_Mode,
			I2C_Generate_Start_Write);
			I2C_SendData(I2C, 0);
			addr += 2;
			if (addr == 0)
				addr = 1;
		}
	}
}
