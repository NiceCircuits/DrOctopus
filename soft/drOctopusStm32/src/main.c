/**
 ******************************************************************************
 * @file    main.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   drOctopus firmware for STM32.
 ******************************************************************************
 */

#include "stm32f30x.h"
#include "config.h"
#include "debug.h"
#include "sysTick.h"
#include "outputs.h"
#include "servo.h"
#include "adc.h"

int main(void) {
	debugSource_t debugMain;
	FunctionalState led = ENABLE;
	int i, j;
	int_fast32_t dir, pos = 0;
	uint16_t adc;
	uint64_t time;

	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	servoInit();
	adcInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	debugPrintln(debugMain, "Hello!");
	delayMs(10);

	servoEnable(0, ENABLE);

	time = 0;
	for (;;) {
		servoLoop();
		adcLoop();
		if (time <= getTime()) {
			time = getTime() + 20;
			uint16_t adc = ADC_GetConversionValue(ADC);
			servoCmd(0, adc  - 2048, 50);
		}
	}
}
