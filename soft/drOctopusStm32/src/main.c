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
#include "oled.h"
#include "ESP8266.h"

debugSource_t debugMain;

#ifndef TEST_MODE
// Standard main function. TEST_MODE symbol must not be defined.
int main(void) {
	defaultInit();
	oledInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	debugPrintln(debugMain, "Hello!");

	for (;;) {
		servoLoop();
		adcLoop();
	}
}
#endif

uint_fast8_t defaultInit() {

	portInit(); // Initialize peripheral clocks etc. Must be called before any other init.
	delayInit();
	debugInit();
	outputsInit();
	servoInit();
	adcInit();
	// OLED and I2C is not initialized here.
	//espInit();

	return 0;
}
