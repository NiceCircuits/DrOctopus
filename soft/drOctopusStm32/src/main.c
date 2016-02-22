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
#include "delay.h"
#include "outputs.h"
#include "servo.h"
#include "adc.h"
#include "i2c.h"
#include "oled.h"

#ifndef TEST_MODE
// Standard main function. TEST_MODE symbol must not be defined.
int main(void) {
	FunctionalState led = ENABLE;
	int i, j;
	int_fast32_t dir, pos = 0;
	uint16_t adc;
	uint64_t time;
	uint8_t addr;

	defaultInit();

	time = 0;
	addr = 1;
	for (;;) {
		servoLoop();
		adcLoop();
//		if (time <= getTime()) {
//			time = getTime() + 1;
//			I2C_TransferHandling(I2C, addr, 0, I2C_SoftEnd_Mode,
//			I2C_Generate_Start_Write);
//			I2C_SendData(I2C, 0);
//			addr += 2;
//			if (addr == 0)
//				addr = 1;
//		}
	}
}
#endif

uint_fast8_t defaultInit() {
	debugSource_t debugMain;

	portInit(); // Initialize peripheral clocks etc. Must be called before any other init.
	delayInit();
	debugInit();
	outputsInit();
	servoInit();
	adcInit();
	i2cInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	debugPrintln(debugMain, "Hello!");

	return 0;
}
